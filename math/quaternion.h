#pragma once
#include "vector.h"

namespace math {
	struct quaternion {
		union {
			vector3 v;
			struct {float x,y,z;};
		};
		float w;
	};
}