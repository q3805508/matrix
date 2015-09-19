#pragma once
#include "..\math\vector.h"

namespace renderer {
	enum ShaderType{SHADER_VS,SHADER_PS,SHADER_END};
	enum ShaderParamType {ST_FLOAT,ST_FLOAT2,ST_FLOAT3,ST_FLOAT4,ST_FLOAT3x3,ST_FLOAT4x4,ST_FLOAT4x3,ST_END};
	enum TextureType {TT_1D,TT_2D,TT_CUBE,TT_3D,TT_END};
	enum TextureFormat {TF_RGBA,TF_RGB,TF_DXT1,TF_DXT5,TF_D24S4,TF_END};

	enum RenderType{RT_TRIANGLELIST,RT_TRIANGLESTRIP,RT_LINELIST,RT_LINESTRIP,RT_POINTLIST,RT_END};

	enum VStream{VS_BASE,VS_SKIN,VS_DEFORM,VS_MAX,VS_END};

	enum GlobalState{GS_FILLMODE,GS_END};

	enum EffectState{};

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

	enum VertexFormat {
		VF_UNKNOWN,
		VF_P3F_N4B_T2F,
		VF_P3F_N4B_TAN4B_T2F,
	};
	
	inline int getVertexSize(VertexFormat fmt)
	{
		switch(fmt)
		{
		case VF_P3F_N4B_T2F:
			return sizeof(SVF_P3F_N4B_T2F);
		case VF_P3F_N4B_TAN4B_T2F:
			return sizeof(SVF_P3F_N4B_TAN4B_T2F);
		default:
			return 0;
		}
	}

}