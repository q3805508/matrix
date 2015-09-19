#pragma once
#include "renderer_global.h"
#include "qsharedpointer.h"
#include "texture.h"
#include "effect.h"
#include "material.h"

namespace renderer {
	class IRenderer;
	class RenderMgrData;
	
	RENDERER_EXPORT bool initRenderer(const char* rendererModule);
	RENDERER_EXPORT void shutdownRenderer();


	class RENDERER_EXPORT RenderMgr {
	public:
		RenderMgr();
		~RenderMgr();

		IRenderer* getRenderer();

		bool init(const char* rendererModule);
		void shutdown();

		Effect getEffect(QString resID);
		Texture getTexture(QString resID);
		Material getMaterial(QString resID);

	private:
		RenderMgrData* pData;
	};

	extern RENDERER_EXPORT RenderMgr* theRenderMgr;
}