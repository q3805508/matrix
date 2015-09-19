#pragma once
#include "../math/matrix.h"

namespace renderer {

	struct Camera {
		math::matrix4x4 viewMatrix;
		math::matrix4x4 projMatrix;
	};
}