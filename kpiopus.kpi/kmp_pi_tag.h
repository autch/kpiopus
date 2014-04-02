
#pragma once

/* http://kbmplaybbs.dip.jp/?md=hf&no=4285&pn=4285&ln=101&sln=x&bm=mv&qt=1 */

/****
�E�^�O���ƃr�b�g���[�g�擾�̃v���O�C����(������)
�@�E�T�v�͈ȉ��̒ʂ�
�@�E�G�N�X�|�[�g����֐�
�@�@�EBOOL WINAPI kmp_GetTestTagInfo(const char *cszFileName, 
�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ IKmpTagInfo *pTagInfo);
�@�@�Eclass IKmpTagInfo
�@�@�@{
�@�@�@�@public:
�@�@�@�@�@�@virtual void WINAPI SetValueA(const char *name, 
�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@const char *value)=0;//ANSI
�@�@�@�@�@�@virtual void WINAPI SetValueW(const char *name, 
�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@const WCHAR *value)=0;//UNICODE
�@�@�@�@�@�@virtual void WINAPI SetValueU8(const char *name, 
�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@const char *value)=0;//UTF8
�@�@�@};
�@�@�Ename="title", "artist", "album", "comment", "genre", "date", "bitrate"
�@�@�Ekmp_GetTestTagInfo �̎g�p�O�� 1�x���� KMPMODULE::Init ���Ă΂��
�@�@�EFreeLibrary �O�� KMPMODULE::Deinit ���Ă΂��
�@�E�\��������̗D��x
�@�@1.���ۂɎg�p����(�D��x���ł�����)�v���O�C��
�@�@2.���ƑΉ��`���������ʂ̃v���O�C��(�D��x��)
�@�@3.KbMedia Player �����̃^�O�擾���[�`��
�@�E2 �� 3 ���ȗ�����悤��(�g�p����v���O�C���œ�����񂵂��\�����Ȃ��悤��)�v
�@�@���O�C�����Ŏw�肷�邱�Ƃ���(pTagInfo->SetValue(NULL, NULL) ���Ă�)
�@�E�Đ��͕����̊g���q�ɑΉ����邪�A�^�O���擾�͈ꕔ�̊g���q�ɂ����Ή����Ȃ�
�@�@�ꍇ�A�Ή����Ȃ��`���ɑ΂��Ă͉������Ȃ��� TRUE ��Ԃ��Ηǂ�
�@�E�����܂ł��b��I�Ȃ��̂Ȃ̂ōŒ���̋@�\�����񋟂��Ȃ�
�@�E���{�I�ɂ̓v���O�C���d�l���̂��̂��ꂩ���蒼���K�v������
�@�E�������Ȃ̂Ŏd�l�ύX�̉\����
 */


class IKmpTagInfo
{
public:
	virtual void WINAPI SetValueA(const char *name, const char *value) = 0; //ANSI
	virtual void WINAPI SetValueW(const char *name, const WCHAR *value) = 0; //UNICODE
	virtual void WINAPI SetValueU8(const char *name, const char *value) = 0; //UTF8
};

typedef BOOL (WINAPI *pfnGetTestTagInfo)(const char *cszFileName, IKmpTagInfo *pTagInfo);