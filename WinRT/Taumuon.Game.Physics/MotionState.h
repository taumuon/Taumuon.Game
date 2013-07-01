#pragma once

#include <btBulletDynamicsCommon.h>

namespace Taumuon {	namespace Game { namespace Physics {

	using namespace Taumuon::Game::Common;

	class MotionState : public btMotionState 
	{
	public:
		MotionState(ITransformable^ transformable, const btTransform &initialTransform);
		virtual ~MotionState(void);

		virtual void getWorldTransform(btTransform &worldTransform) const;
		virtual void setWorldTransform(const btTransform &worldTransform);
	private:
		ITransformable^ _transformable;
		btTransform _initialTransform;
	};

} } }
