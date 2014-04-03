// kpiopus.kpi.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "kpiopus.kpi.h"

#define KPIOPUS_VERSION   ((1 << 8) | 1)      // 1.01
#ifdef _DEBUG
#define KPIOPUS_DESC      "Opus decoder plugin for KbMedia Player [DEBUG]"
#else
#define KPIOPUS_DESC      "Opus decoder plugin for KbMedia Player"
#endif
#define KPIOPUS_COPYRIGHT "Copyright (c) 2014 Autch; libopus/libopusfile: Copyright 2001-2011 Xiph.Org, et al; libogg: Copyright (c) 2002, Xiph.org Foundation"

extern "C"
KMPMODULE* APIENTRY kmp_GetTestModule()
{
	static const char* pszExts[] = { ".opus", NULL };
	static KMPMODULE kpiModule =
	{
		KMPMODULE_VERSION,		// DWORD dwVersion;
		KPIOPUS_VERSION,    	// DWORD dwPluginVersion;
		KPIOPUS_COPYRIGHT, 		// const char	*pszCopyright;
		KPIOPUS_DESC,			// const char	*pszDescription;
		pszExts,				// const char	**ppszSupportExts;
		1,						// DWORD dwReentrant;
		kpiInit,				// void (WINAPI *Init)(void);
		kpiDeinit,				// void (WINAPI *Deinit)(void);
		kpiOpen,				// HKMP (WINAPI *Open)(const char *cszFileName, SOUNDINFO *pInfo);
		NULL,	            	// HKMP (WINAPI *OpenFromBuffer)(const BYTE *Buffer, DWORD dwSize, SOUNDINFO *pInfo);
		kpiClose,				// void (WINAPI *Close)(HKMP hKMP);
		kpiRender,				// DWORD (WINAPI *Render)(HKMP hKMP, BYTE* Buffer, DWORD dwSize);
		kpiSetPosition			// DWORD (WINAPI *SetPosition)(HKMP hKMP, DWORD dwPos);
	};
	return &kpiModule;
}

extern "C"
BOOL WINAPI kmp_GetTestTagInfo(const char *cszFileName, IKmpTagInfo *pTagInfo)
{
	return kpiGetTagInfo(cszFileName, pTagInfo);
}
