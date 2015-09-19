#include "rendermgr.h"
#include "rendererModule.h"

#ifdef WIN32
#include <Windows.h>
#endif

#include <qdebug.h>

namespace renderer {

	RenderMgr* theRenderMgr = NULL;

	bool initRenderer(const char* rendererModule)
	{
		if (theRenderMgr)
			return true;
		theRenderMgr = new RenderMgr();
		if (theRenderMgr->init(rendererModule))
		{
			return true ;
		} else {
			delete theRenderMgr;
			theRenderMgr = NULL;
			return false;
		}
	}
	void shutdownRenderer()
	{
		if (theRenderMgr)
		{
			theRenderMgr->shutdown();
			delete theRenderMgr;
			theRenderMgr = NULL;
		}
	}
	
	class RenderMgrData {
	public:
		RenderMgrData()
		{
			pRenderer = NULL;
			handle = 0;
			getRendererFunc = NULL;
			releaseRendererFunc = NULL;
		}

		IRenderer* pRenderer;
		HMODULE handle;
		PROC_GET_RENDERER getRendererFunc;
		PROC_RELEASE_RENDERER releaseRendererFunc;
	};

	RenderMgr::RenderMgr()
	{
		this->pData = new RenderMgrData;
	}

	RenderMgr::~RenderMgr()
	{
		delete this->pData;
	}

	bool RenderMgr::init(const char* rendererModule)
	{
		//HMODULE handle = ::LoadLibraryA(rendererModule.toAscii());
		HMODULE handle = ::LoadLibraryA(rendererModule);
		if (!handle)
			return false;

		PROC_GET_RENDERER getRendererFunc 
			= (PROC_GET_RENDERER)::GetProcAddress(handle,NAME_GET_RENDERER_PROC);
		PROC_RELEASE_RENDERER releaseRendererFunc
			= (PROC_RELEASE_RENDERER)::GetProcAddress(handle,NAME_RELEASE_RENDERER_PROC);
		if (!getRendererFunc || !releaseRendererFunc)
		{
			::FreeLibrary(handle);
			return false;
		}
		IRenderer* pRenderer = getRendererFunc();
		if (!pRenderer)
		{
			::FreeLibrary(handle);
			return false;
		}

		this->pData->pRenderer = pRenderer;
		this->pData->handle = handle;
		this->pData->getRendererFunc = getRendererFunc;
		this->pData->releaseRendererFunc = releaseRendererFunc;

		return true;
	}

	void RenderMgr::shutdown()
	{
		this->pData->releaseRendererFunc(this->pData->pRenderer);
		::FreeLibrary(this->pData->handle);
		
		this->pData->handle = NULL;
		this->pData->pRenderer = NULL;
		this->pData->getRendererFunc = NULL;
		this->pData->releaseRendererFunc = NULL;
	}

	IRenderer* RenderMgr::getRenderer()
	{
		return this->pData->pRenderer;
	}
}