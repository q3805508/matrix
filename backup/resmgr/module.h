#pragma once

#ifdef RESMGR_IMP
	#define RESMGR_EXPORT __declspec(dllexport)
#else
	#define RESMGR_EXPORT __declspec(dllimport)
#endif