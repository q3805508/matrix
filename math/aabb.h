#pragma once
#include "vector.h"

namespace math {

	struct AABB {
		vector3 max;
		vector3 min;
	};
}