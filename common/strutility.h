#pragma once
#include <stdlib.h>
#include "../math/vector.h"

namespace cn {

	math::vector2 getVector2FromStr(const char* str,bool* ok = NULL)
	{
		math::vector2 ret;
		float* pRet = (float*)&ret;
		for (int i = 0; i < 2;i++)
		{
			if (*str == '\0')
				break;

			float value = strtod(str,NULL);
			pRet[i] = value;

			//move to next ','
			while (*str != ',' || *str != '\0')
			{
				str ++;
			}
		}
		if (ok)
			*ok = true;
		return ret;
	}
	math::vector3 getVector3FromStr(const char* str,bool* ok = NULL)
	{
		math::vector3 ret;
		float* pRet = (float*)&ret;
		for (int i = 0; i < 3;i++)
		{
			if (*str == '\0')
				break;

			float value = strtod(str,NULL);
			pRet[i] = value;

			//move to next ','
			while (*str != ',' || *str != '\0')
			{
				str ++;
			}
		}
		if (ok)
			*ok = true;
		return ret;
	}
	math::vector4 getVector4FromStr(const char* str,bool* ok = NULL)
	{
		math::vector4 ret;
		float* pRet = (float*)&ret;
		for (int i = 0; i < 4;i++)
		{
			if (*str == '\0')
				break;

			float value = strtod(str,NULL);
			pRet[i] = value;

			//move to next ','
			while (*str != ',' || *str != '\0')
			{
				str ++;
			}
		}
		if (ok)
			*ok = true;
		return ret;
	}
}