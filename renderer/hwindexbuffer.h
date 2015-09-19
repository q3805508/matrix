#pragma once
#include "hwresource.h"

namespace renderer {
	class HWIndexBuffer : public HWResource{
	public:
		virtual ~HWIndexBuffer(){}

		virtual int getCount() = 0;

		virtual unsigned short* lock() = 0;
		virtual void unlock() = 0;
	};
}