
#pragma once

class COpusDecoder: public CAbstractKpiDecoder
{
private:
	SOUNDINFO m_info;
	OggOpusFile* m_file;

public:

	COpusDecoder() : m_file(NULL) {
		ZeroMemory(&m_info, sizeof m_info);
	}

	~COpusDecoder() {
		Close();
	}

	void Close() {
		if(m_file != NULL) {
			op_free(m_file);
		}
		m_file = NULL;
	}

	BOOL Open(LPSTR szFileName, SOUNDINFO* pInfo) {
		int op_error = 0;
		ogg_int64_t totalSamples;

		m_file = op_open_file(szFileName, &op_error);
		if(m_file == NULL) {
			return FALSE;
		}

		ZeroMemory(&m_info, sizeof m_info);

		m_info.dwBitsPerSample = 16;
		m_info.dwChannels = 2;
		m_info.dwSamplesPerSec = 48000;

		totalSamples = op_pcm_total(m_file, -1);
		totalSamples *= 1000;
		//totalSamples /= m_info.dwChannels;
		totalSamples /= m_info.dwSamplesPerSec;
		m_info.dwLength = totalSamples;

		m_info.dwSeekable = TRUE;
		m_info.dwUnitRender = 11520 * m_info.dwChannels * (m_info.dwBitsPerSample / 8);	// 120ms, recommended by libopusfile

		CopyMemory(pInfo, &m_info, sizeof m_info);

		return TRUE;
	}

	DWORD SetPosition(DWORD dwPosition) {
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
		//offset *= m_info.dwChannels;
		offset /= 1000;

		ret = op_pcm_seek(m_file, offset);
		if(ret == 0) {
			offset = op_pcm_tell(m_file);
			if(offset != OP_EINVAL) {
				offset *= 1000;
				//offset /= m_info.dwChannels;
				offset /= m_info.dwSamplesPerSec;
				return offset;
			} else {
				return 0;
			}
		} else {
			return 0;
		}
	}

	DWORD Render(BYTE* pBuffer, DWORD dwSize) {
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
};
