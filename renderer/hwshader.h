#pragma once
#include "rendererdef.h"
#include "hwresource.h"

namespace renderer {
	class HWShader : public HWResource {
	public:
		HWShader()
		{

		}

		virtual ~HWShader()
		{

		}

		virtual ShaderType getShaderType () = 0;
	};
}