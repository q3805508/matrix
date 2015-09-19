#pragma once
namespace renderer {
	class IRenderer;
}
typedef renderer::IRenderer* (*PROC_GET_RENDERER)(); 
typedef void (*PROC_RELEASE_RENDERER)(renderer::IRenderer*);

static const char* NAME_GET_RENDERER_PROC = "GetRenderer";
static const char* NAME_RELEASE_RENDERER_PROC = "ReleaseRenderer";