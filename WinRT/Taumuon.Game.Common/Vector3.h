#pragma once

namespace Taumuon { namespace Game { namespace Common {

	// TODO: value type
	public ref class Vector3 sealed
	{
	public:
		Vector3(double x, double y, double z)
			: _x(x), _y(y), _z(z)
		{ }
		property double X {double get() { return _x; } }
		property double Y {double get() { return _y; } }
		property double Z {double get() { return _z; } }
	private:
		double _x;
		double _y;
		double _z;
	};

} } }
