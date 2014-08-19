#pragma once

namespace renderer {
	class IHWIndexBuffer {
	public:
		virtual ~IHWIndexBuffer();

		virtual bool createIndexBuffer(int count,bool dynamic);

		virtual int getCount();

		virtual unsigned short* lock();
		virtual void unlock();
	};
}