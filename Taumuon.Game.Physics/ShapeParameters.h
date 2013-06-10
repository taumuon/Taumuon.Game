#pragma once

using namespace Taumuon::Game::Common;

namespace Taumuon {	namespace Game { namespace Physics {

	public ref class ShapeParameters sealed
	{
	public:
		ShapeParameters(Vector3^ inertia,
						Transform^ transform,
			            ITransformable^ transformable);
		virtual ~ShapeParameters(void);
	
		property Vector3^ Inertia { Vector3^ get() { return _inertia; } }
		property Transform^ Transform { Taumuon::Game::Common::Transform^ get() { return _transform; } }
		property ITransformable^ Transformable { ITransformable^ get() { return _transformable; } }
	private:
		Vector3^ _inertia;
		Taumuon::Game::Common::Transform^ _transform;
		ITransformable^ _transformable;
	};

} } }
