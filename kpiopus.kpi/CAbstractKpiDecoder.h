
#pragma once

class CAbstractKpiDecoder
{
public:
	virtual void Close() = 0;

	virtual BOOL Open(LPSTR szFileName, SOUNDINFO* pInfo) = 0;
	virtual DWORD SetPosition(DWORD dwPos) = 0;
	virtual DWORD Render(BYTE* pBuffer, DWORD dwSize) = 0;
};
