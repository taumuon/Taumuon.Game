#include "pch.h"
#include "Physics.h"

#include <algorithm>

using namespace std;
using namespace DirectX;

Physics::Physics(void) :
	m_broadphase(new btDbvtBroadphase()),
	m_collisionConfiguration(new btDefaultCollisionConfiguration()),
	m_solver(new btSequentialImpulseConstraintSolver)
{
	m_dispatcher = std::unique_ptr<btCollisionDispatcher>(new btCollisionDispatcher(m_collisionConfiguration.get()));
	m_dynamicsWorld = std::unique_ptr<btDiscreteDynamicsWorld>(new btDiscreteDynamicsWorld(m_dispatcher.get(),m_broadphase.get(),m_solver.get(),m_collisionConfiguration.get()));

	m_dynamicsWorld->setGravity(btVector3(0,-10,0));
}

void Physics::RemoveRigidBody(btRigidBody* rigidBody)
{
	auto it = std::find_if(begin(m_rigidBodies), end(m_rigidBodies), [&](std::unique_ptr<btRigidBody> const& p)
	{
		return p.get() == rigidBody;
	});

	if (it != end(m_rigidBodies))
	{
		bool active = rigidBody->isActive();

		m_dynamicsWorld->removeRigidBody(rigidBody);
		delete rigidBody->getMotionState();
		m_rigidBodies.erase(it);

		// If the scene is deactivated, give it a 'prod' before removing the rigid body.
		if (!active)
		{
			for(const auto &body : m_rigidBodies)
			{
				body->activate();
			}
		}
	}
}

Physics::~Physics(void)
{
	for_each(begin(m_rigidBodies), end(m_rigidBodies), [&](unique_ptr<btRigidBody> const& rigidBody)
	{
		m_dynamicsWorld->removeRigidBody(rigidBody.get());
		delete rigidBody->getMotionState();
	} );

	m_rigidBodies.clear();
}

void Physics::Update()
{
    m_dynamicsWorld->stepSimulation(1/60.f,10);
}

void Physics::AddPhysicalObject(std::unique_ptr<btCollisionShape> collisionShape, std::unique_ptr<btMotionState> motionState, btScalar mass, const btVector3& inertia)
{
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState.release(), collisionShape.get(), inertia);

	auto rigidBody = new btRigidBody(rigidBodyCI);

	m_dynamicsWorld->addRigidBody(rigidBody);

	// TODO: double-check that we should have ownership of the collision shapes, that the btRigidBody doesn't delete them
	m_shapes.push_back(std::move(collisionShape));

	m_rigidBodies.push_back(std::unique_ptr<btRigidBody>(rigidBody));
}


btRigidBody* Physics::RayTest(XMFLOAT3& rayFromVector, XMFLOAT3& pickRayVector)
{
	auto btRayFrom = btVector3(rayFromVector.x, rayFromVector.y, rayFromVector.z);
	auto btPickRay = btVector3(pickRayVector.x, pickRayVector.y, pickRayVector.z);

	auto btRayTo = btRayFrom + (btPickRay * 1000.0f);

	btCollisionWorld::ClosestRayResultCallback rayCallback(btRayFrom, btRayTo);
	m_dynamicsWorld->rayTest(btRayFrom, btRayTo, rayCallback);
	if (rayCallback.hasHit())
	{
		auto collisionObject = rayCallback.m_collisionObject;
		auto collisionShape = collisionObject->getCollisionShape();

		auto rigidBody = std::find_if(begin(m_rigidBodies), end(m_rigidBodies), [&](std::unique_ptr<btRigidBody> const& p)
		{
			return p.get() == collisionObject;
		});

		if (rigidBody != end(m_rigidBodies))
		{
			return rigidBody[0].get();
		}

		// TODO: assert ? hasHit() returned true but we can't find out what?
		return nullptr;
	}

	return nullptr;
}