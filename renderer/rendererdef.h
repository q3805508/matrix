#pragma once
#include "..\math\vector.h"

namespace renderer {
	enum ShaderType {ST_FLOAT,ST_FLOAT2,ST_FLOAT3,ST_FLOAT4,ST_FLOAT3x3,ST_FLOAT4x4,ST_FLOAT4x3};
	enum TextureType {TT_1D,TT_2D,TT_CUBE,TT_3D};
	enum TextureFormat {TF_RGBA,TF_RGB,TF_DXT1,TF_DXT5,TF_D24S4};

	enum RenderType{RT_TRIANGLELIST,RT_TRIANGLESTRIP,RT_LINELIST,RT_LINESTRIP,RT_POINTLIST};

	enum VStream{VS_BASE,VS_SKIN,VS_DEFORM,VS_MAX};

	enum GlobalState{GS_FILLMODE,};

	enum EffectState{};

	enum VertexFormat {
		VF_UNKNOWN,
		VF_P3F_N4B_T2F,
		VF_P3F_N4B_TAN4B_T2F,
	};

	const int MAX_STREAM = 8;

	struct SVF_P3F_N4B_T2F {
		math::vector3 pos;
		unsigned char normal[4];
		math::vector2 uv;
	};

	struct SVF_P3F_N4B_TAN4B_T2F {
		math::vector3 pos;
		unsigned char normal[4];
		unsigned char tangent[4];
		math::vector2 uv;
	};
}