#pragma once
#include "rendererd3d9_global.h"
#include "../renderer/rendererModule.h"

namespace renderer {
	class IRenderer;
}

INTERFACE_EXPORT renderer::IRenderer* GetRenderer();
INTERFACE_EXPORT void ReleaseRenderer();