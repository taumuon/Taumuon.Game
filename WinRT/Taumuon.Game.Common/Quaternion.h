#pragma once

namespace Taumuon { namespace Game { namespace Common {

	// TODO: value type
	public ref class Quaternion sealed
	{
	public:
		Quaternion(double x, double y, double z, double w)
			: _x(x), _y(y), _z(z), _w(w)
		{ }
		property double X { double get() { return _x; } }
		property double Y { double get() { return _y; } }
		property double Z { double get() { return _z; } }
		property double W { double get() { return _w; } }
	private:
		double _x;
		double _y;
		double _z;
		double _w;
	};

} } }