#pragma once

namespace math {
	struct vector2 {
		vector2(float _x,float _y)
		:x(_x),y(_y)
		{
		}
		vector2()
		:x(0),y(0)
		{
		}
		float x,y;
	};
	struct vector3 {
		vector3(float _x,float _y,float _z)
		:x(_x),y(_y),z(_z)
		{
		}
		vector3()
		:x(0),y(0),z(0)
		{
		}
		float x,y,z;
	};

	struct vector4 {
		vector4(float _x,float _y,float _z,float _w)
		:x(_x),y(_y),z(_z),w(_w)
		{
		}
		vector4()
		:x(0),y(0),z(0),w(0)
		{
		}

		float x,y,z,w;
	};
}