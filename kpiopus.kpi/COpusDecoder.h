
#pragma once

class COpusDecoder: public CAbstractKpiDecoder
{
private:
	SOUNDINFO m_info;
	OggOpusFile* m_file;

	static BOOL kpiSetTagInfo(const OpusTags* tags, const char* tag, const char* tag_dest, IKmpTagInfo* pTagInfo)
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

	static LPSTR kpiShiftJISToUTF8(const LPCSTR szSource)
	{
		int size_u16, size_u8;
		LPWSTR wzU16;
		LPSTR szU8;

		size_u16 = ::MultiByteToWideChar(CP_ACP, 0, szSource, -1, NULL, 0);
		if(size_u16 <= 0) {
			return NULL;
		}

		wzU16 = new WCHAR[size_u16 + 1];
		ZeroMemory(wzU16, sizeof(WCHAR) * (size_u16 + 1));
		::MultiByteToWideChar(CP_ACP, 0, szSource, -1, wzU16, size_u16 + 1);

		size_u8 = ::WideCharToMultiByte(CP_UTF8, 0, wzU16, size_u16 + 1, NULL, 0, NULL, NULL);
		if(size_u8 <= 0) {
			delete[] wzU16;
			return NULL;
		}

		szU8 = new CHAR[size_u8 + 1];
		ZeroMemory(szU8, size_u8 + 1);
		::WideCharToMultiByte(CP_UTF8, 0, wzU16, size_u16 + 1, szU8, size_u8 + 1, NULL, NULL);

		return szU8;
	}

public:

	COpusDecoder() : m_file(NULL)
	{
		ZeroMemory(&m_info, sizeof m_info);
	}

	~COpusDecoder()
	{
		Close();
	}

	void Close()
	{
		if(m_file != NULL) {
			op_free(m_file);
		}
		m_file = NULL;
	}

	BOOL Open(LPSTR szFileName, SOUNDINFO* pInfo)
	{
		int op_error = 0;
		ogg_int64_t totalSamples;
		LPSTR filename_u8;

		filename_u8 = kpiShiftJISToUTF8(szFileName);
		if(filename_u8 == NULL) {
			return FALSE;
		}

		m_file = op_open_file(filename_u8, &op_error);
		delete[] filename_u8;
		if(m_file == NULL) {
			return FALSE;
		}

		ZeroMemory(&m_info, sizeof m_info);

		m_info.dwBitsPerSample = 16;
		m_info.dwChannels = 2;
		m_info.dwSamplesPerSec = 48000;

		totalSamples = op_pcm_total(m_file, -1);
		totalSamples *= 1000;
		totalSamples /= m_info.dwSamplesPerSec;
		m_info.dwLength = totalSamples;

		m_info.dwSeekable = TRUE;
		m_info.dwUnitRender = 11520 * m_info.dwChannels * (m_info.dwBitsPerSample / 8);	// 120ms, recommended by libopusfile

		CopyMemory(pInfo, &m_info, sizeof m_info);

		return TRUE;
	}

	DWORD SetPosition(DWORD dwPosition)
	{
		ogg_int64_t offset;
		int ret;

		if(m_file == NULL) {
			return 0;
		}

		if(dwPosition > m_info.dwLength) {
			op_pcm_seek(m_file, 0);
			return 0;
		}

		offset = dwPosition;
		offset *= m_info.dwSamplesPerSec;
		offset /= 1000;

		ret = op_pcm_seek(m_file, offset);
		if(ret == 0) {
			offset = op_pcm_tell(m_file);
			if(offset != OP_EINVAL) {
				offset *= 1000;
				offset /= m_info.dwSamplesPerSec;
				return offset;
			} else {
				return 0;
			}
		} else {
			return 0;
		}
	}

	DWORD Render(BYTE* pBuffer, DWORD dwSize)
	{
		int ret, size;
		DWORD dwBytesWritten = 0;
		opus_int16* out = (opus_int16*)pBuffer;

		if(m_file == NULL) {
			return 0;
		}
		ZeroMemory(pBuffer, dwSize);

		size = dwSize / (m_info.dwBitsPerSample / 8);
		while(size > 0) {
			ret = op_read_stereo(m_file, out, size);
			if(ret <= 0) {
				break;
			}
			out += ret * m_info.dwChannels;
			size -= ret * m_info.dwChannels;

			ret *= m_info.dwChannels;
			ret *= (m_info.dwBitsPerSample / 8);

			dwBytesWritten += ret;
		}
		return dwBytesWritten;
	}

	static BOOL WINAPI GetTagInfo(const char *cszFileName, IKmpTagInfo *pTagInfo)
	{
		OggOpusFile* file = NULL;
		int error = 0;
		const char* value = NULL;
		const OpusTags* tags;
		LPSTR filename_u8 = NULL;

		filename_u8 = COpusDecoder::kpiShiftJISToUTF8(cszFileName);
		if(filename_u8 == NULL) {
			return FALSE;
		}

		file = op_open_file(filename_u8, &error);
		delete[] filename_u8;
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
};
