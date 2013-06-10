#pragma once

#include "Transform.h"

namespace Taumuon { namespace Game { namespace Common {

public interface class ITransformable
	{
	public:
		void Transform(Transform^ transform);
	};

} } }