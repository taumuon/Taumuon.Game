#pragma once

#include <btBulletDynamicsCommon.h>

class Physics
{
public:
	Physics(void);
	virtual ~Physics(void);

	void Update();
	// herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters
	void AddPhysicalObject(std::unique_ptr<btCollisionShape> collisionShape, std::unique_ptr<btMotionState> motionState, btScalar mass, const btVector3& inertia);
	void RemoveRigidBody(btRigidBody* rigidBody);

	btRigidBody* RayTest(DirectX::XMFLOAT3& rayFromVector, DirectX::XMFLOAT3& pickRayVector);
private:
	Physics(const Physics&){}
	Physics& operator=(const Physics&) { return *this; }

	std::unique_ptr<btBroadphaseInterface> m_broadphase;
	std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
	std::unique_ptr<btCollisionDispatcher> m_dispatcher;
	std::unique_ptr<btSequentialImpulseConstraintSolver> m_solver;
	std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;

	std::vector<std::unique_ptr<btCollisionShape>> m_shapes;
	std::vector<std::unique_ptr<btRigidBody>> m_rigidBodies;
};

