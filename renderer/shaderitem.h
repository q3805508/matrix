#pragma once

namespace renderer {
	class HWShader;
	class ShaderResource;
	struct ShaderItem {
		HWShader* pShader;
		ShaderResource* pShaderRes;
	};
}