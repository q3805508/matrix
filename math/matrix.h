#pragma once

namespace math {
	struct matrix4x4 {
		float 
			_00,_01,_02,_03,
			_10,_11,_12,_13,
			_20,_21,_22,_23,
			_30,_31,_32,_33;
	};

	struct matrix3x3 {
		float 
			_00,_01,_02,
			_10,_11,_12,
			_20,_21,_22;
	};

	struct matrix3x4 {
		float 
			_00,_01,_02,
			_10,_11,_12,
			_20,_21,_22,
			_30,_31,_32;
	};
}