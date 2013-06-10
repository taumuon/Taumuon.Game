#pragma once

#include "Vector3.h"
#include "Quaternion.h"

namespace Taumuon { namespace Game { namespace Common {

	// TODO: this should be a value type
	public ref class Transform sealed
	{
	public:
		Transform(Vector3^ location, Quaternion^ quaternion)
			:
			_location(location),
			_quaternion(quaternion)
		{
		}
	public:
		property Vector3^ Location
		{
			Vector3^ get() { return _location; }
		}
		property Quaternion^ Quaternion
		{
			Taumuon::Game::Common::Quaternion^ get() { return _quaternion; }
		}
	private:
		Vector3^ _location;
		Taumuon::Game::Common::Quaternion^ _quaternion;
	};

} } }