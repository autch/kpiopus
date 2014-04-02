/* kpi.cpp -- Actual handlers of DLL entry points for KbMedia Player plugin.
 * Copyright (c) 2008, 2014, Autch.  Distributed under the terms of zlib/libpng license.
 */

#include "stdafx.h"
#include "kpi.h"

char g_szIniFileName[MAX_PATH];

void WINAPI kpiInit()
{
  char* pDot;

  GetModuleFileName(::g_hModule, ::g_szIniFileName, MAX_PATH);
  pDot = strrchr(g_szIniFileName, '.');
  strncpy_s(pDot, MAX_PATH - (pDot - g_szIniFileName), ".ini", 4);
}

void WINAPI kpiDeinit()
{
}

HKMP WINAPI kpiOpen(const char* cszFileName, SOUNDINFO* pInfo)
{
  CKpiTargetDecoder* d = new CKpiTargetDecoder();
  if(d->Open((LPSTR)cszFileName, pInfo))
    return (HKMP)d;
  return NULL;
}

void WINAPI kpiClose(HKMP hKMP)
{
  if(hKMP)
    delete (CKpiTargetDecoder*)hKMP;
}

DWORD WINAPI kpiRender(HKMP hKMP, BYTE* Buffer, DWORD dwSize)
{
  CKpiTargetDecoder* d = (CKpiTargetDecoder*)hKMP;
  if(d)
    return d->Render(Buffer, dwSize);
  return 0;
}

DWORD WINAPI kpiSetPosition(HKMP hKMP, DWORD dwPos)
{
  CKpiTargetDecoder* d = (CKpiTargetDecoder*)hKMP;
  if(d)
    return d->SetPosition(dwPos);
  return 0;
}

UINT GetMyProfileInt(LPSTR szSectionName, LPSTR szKeyName, INT nDefault)
{
  return ::GetPrivateProfileInt(szSectionName, szKeyName, nDefault, ::g_szIniFileName);
}

BOOL kpiSetTagInfo(const OpusTags* tags, const char* tag, const char* tag_dest, IKmpTagInfo* pTagInfo)
{
	int count;
	const char* value;

	count = opus_tags_query_count(tags, tag);
	if(count <= 0) {
		// ‚È‚¢‚È‚ç‚È‚¢‚Å³í
		return TRUE;
	}

	value = opus_tags_query(tags, tag, 0);
	if(value != NULL) {
		pTagInfo->SetValueU8(tag_dest, value);
	}
	return TRUE;
}

BOOL WINAPI kpiGetTagInfo(const char *cszFileName, IKmpTagInfo *pTagInfo)
{
	OggOpusFile* file = NULL;
	int error = 0;
	const char* value = NULL;
	const OpusTags* tags;

	file = op_open_file(cszFileName, &error);
	if(file == NULL || error != 0) {
		return FALSE;
	}

	tags = op_tags(file, -1);
	if(tags == NULL) {
		op_free(file);
		return TRUE;
	}

	// name="title", "artist", "album", "comment", "genre", "date", "bitrate"
	// http://www.xiph.org/vorbis/doc/v-comment.html

	kpiSetTagInfo(tags, "TITLE", "title", pTagInfo);
	kpiSetTagInfo(tags, "ARTIST", "artist", pTagInfo);
	kpiSetTagInfo(tags, "ALBUM", "album", pTagInfo);
	kpiSetTagInfo(tags, "DESCRIPTION", "comment", pTagInfo);
	kpiSetTagInfo(tags, "GENRE", "genre", pTagInfo);
	kpiSetTagInfo(tags, "DATE", "date", pTagInfo);

	op_free(file);

	return TRUE;
}
