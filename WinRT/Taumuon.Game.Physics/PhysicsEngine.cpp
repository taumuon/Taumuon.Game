#include "pch.h"
#include "PhysicsEngine.h"
#include "MotionState.h"

#include <algorithm>

namespace Taumuon { namespace Game { namespace Physics {

using namespace std;

PhysicsEngine::PhysicsEngine(void) :
	_broadphase(new btDbvtBroadphase()),
	_collisionConfiguration(new btDefaultCollisionConfiguration()),
	_solver(new btSequentialImpulseConstraintSolver)
{
	_dispatcher = std::unique_ptr<btCollisionDispatcher>(new btCollisionDispatcher(_collisionConfiguration.get()));

	_dynamicsWorld = std::unique_ptr<btDiscreteDynamicsWorld>(new btDiscreteDynamicsWorld(_dispatcher.get(),_broadphase.get(),_solver.get(),_collisionConfiguration.get()));

	_dynamicsWorld->setGravity(btVector3(0,-10,0));
}

PhysicsEngine::~PhysicsEngine(void)
{
	for_each( begin(_rigidBodies), end(_rigidBodies), [&]( const unique_ptr<btRigidBody>& rigidBody )
	{
		_dynamicsWorld->removeRigidBody(rigidBody.get());
		delete rigidBody->getMotionState();
	} );

	_rigidBodies.clear();
}

void PhysicsEngine::Update()
{
    _dynamicsWorld->stepSimulation(1/60.f,10);
}

void PhysicsEngine::AddStaticPlane(ShapeParameters^ params, Vector3^ planeNormal, double planeConstant)
{
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransformFromTransform(params->Transform));
	auto shape = new btStaticPlaneShape(btVectorFromVector3(planeNormal),planeConstant);

	AddPhysicalObject(shape, motionState, 0, btVector3(0,0,0));
}

void PhysicsEngine::AddBox(ShapeParameters^ params, Vector3^ halfExtents)
{
	btMotionState* motionState = new MotionState(params->Transformable, btTransformFromTransform(params->Transform));
	auto shape = new btBoxShape(btVectorFromVector3(halfExtents));

	btScalar mass = 1;
	btVector3 fallInertia(0,0,0);
	shape->calculateLocalInertia(mass,fallInertia);

	AddPhysicalObject(shape, motionState, mass, fallInertia);
}

void PhysicsEngine::AddPhysicalObject(btCollisionShape* collisionShape, btMotionState* motionState, btScalar mass, const btVector3& inertia)
{
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(mass, motionState,collisionShape,inertia);

	auto groundRigidBody = new btRigidBody(groundRigidBodyCI);

	_dynamicsWorld->addRigidBody(groundRigidBody);

	_shapes.push_back(std::unique_ptr<btCollisionShape>(collisionShape));
	_rigidBodies.push_back(std::unique_ptr<btRigidBody>(groundRigidBody));
}

} } }