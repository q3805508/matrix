#pragma once

#ifdef RENDERER_IMP
	#define RENDERER_EXPORT __declspec(dllexport)
#else
	#define RENDERER_EXPORT __declspec(dllimport)
#endif