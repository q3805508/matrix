#pragma once
#include "../math/vector.h"

namespace renderer {

	struct SkyInfo {
		math::vector4 skyLightColor;
		math::vector4 groundLightColor;
	};

}