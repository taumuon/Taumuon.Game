#pragma once

#include "ShapeParameters.h"

namespace Taumuon {	namespace Game { namespace Physics {

	using namespace Taumuon::Game::Common;

	public ref class PhysicsEngine sealed
	{
	public:
		PhysicsEngine();
		virtual ~PhysicsEngine();

		void Update();
		void AddStaticPlane(ShapeParameters^ params, Vector3^ planeNormal, double planeConstant);
		void AddBox(ShapeParameters^ params, Vector3^ halfExtents);
	private:
		void AddPhysicalObject(btCollisionShape* collisionShape, btMotionState* motionState, btScalar mass, const btVector3& inertia);

		std::unique_ptr<btBroadphaseInterface> _broadphase;
		std::unique_ptr<btDefaultCollisionConfiguration> _collisionConfiguration;
		std::unique_ptr<btCollisionDispatcher> _dispatcher;
		std::unique_ptr<btSequentialImpulseConstraintSolver> _solver;
		std::unique_ptr<btDiscreteDynamicsWorld> _dynamicsWorld;

		std::vector<std::unique_ptr<btCollisionShape>> _shapes;
		std::vector<std::unique_ptr<btRigidBody>> _rigidBodies;
	};

} } }