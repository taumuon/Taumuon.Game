#include "pch.h"
#include "MotionState.h"


namespace Taumuon {	namespace Game { namespace Physics {

using namespace Taumuon::Game::Common;

MotionState::MotionState(ITransformable^ transformable, const btTransform &initialTransform)
	: 
	_transformable(transformable),
	_initialTransform(initialTransform)
{
}

MotionState::~MotionState(void)
{
}

void MotionState::getWorldTransform(btTransform &worldTransform) const
{
	worldTransform = _initialTransform;
}

void MotionState::setWorldTransform(const btTransform &worldTransform)
{
	auto rotation = worldTransform.getRotation();

	auto transform = ref new Transform(ref new Vector3(worldTransform.getOrigin().getX(),
													   worldTransform.getOrigin().getY(),
													   worldTransform.getOrigin().getZ()),
									   ref new Quaternion(
									   rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW()));

	_transformable->Transform(transform);
}

} } }
