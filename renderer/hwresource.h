#pragma once
#include <QtGlobal>

namespace renderer {

	class HWResource {
public:
		HWResource()
			:refCount(1)
		{
		}

		virtual ~HWResource() 
		{
			Q_ASSERT(refCount == 0);
		}

		void addReference()
		{
			Q_ASSERT(refCount >= 0);
			this->refCount++;
		}

		void removeReference()
		{
			this->refCount --;
			Q_ASSERT(refCount >= 0);
			if (!refCount)
				this->releaseResource();
		}

	protected:
		virtual void releaseResource() = 0;

	private:
		int refCount;
		
		HWResource(const HWResource& src)//the resource object will only have single copy
		{
			Q_ASSERT(0);
		}
	};
}