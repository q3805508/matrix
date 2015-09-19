#include "dllinterface.h"
#include "../renderer/renderer.h"
#include "rendererd3d9.h"

static renderer::IRenderer* theRenderer = NULL;
INTERFACE_EXPORT renderer::IRenderer* GetRenderer()
{
	if (!theRenderer)
		theRenderer = new d3d9::RendererD3D9();
	return theRenderer;
}

INTERFACE_EXPORT void ReleaseRenderer()
{
	delete theRenderer;
	theRenderer = NULL;
}