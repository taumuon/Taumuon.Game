#include "pch.h"
#include "ShapeParameters.h"

namespace Taumuon {	namespace Game { namespace Physics {

ShapeParameters::ShapeParameters(Vector3^ inertia,
								 Taumuon::Game::Common::Transform^ transform,
								 ITransformable^ transformable)
	:
	_inertia(inertia),
	_transform(transform),
	_transformable(transformable)
{
}

ShapeParameters::~ShapeParameters(void)
{
}

} } }