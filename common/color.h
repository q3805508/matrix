#pragma once
#include "../math/vector.h"
namespace cn {
	
	struct color32 {
		int c;
		void fromVector4(const math::vector4& src);
		math::vector4 toVector4();
		void fromRGBA(int R,int G,int B,int A);
		int getR();
		int getG();
		int getB();
		int getA();
	};

	
}