// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ KPIOPUSKPI_EXPORTS
// �V���{�����g�p���ăR���p�C������܂��B���̃V���{���́A���� DLL ���g�p����v���W�F�N�g�ł͒�`�ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// KPIOPUSKPI_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B
#ifdef KPIOPUSKPI_EXPORTS
#define KPIOPUSKPI_API __declspec(dllexport)
#else
#define KPIOPUSKPI_API __declspec(dllimport)
#endif

// ���̃N���X�� kpiopus.kpi.dll ����G�N�X�|�[�g����܂����B
class KPIOPUSKPI_API Ckpiopuskpi {
public:
	Ckpiopuskpi(void);
	// TODO: ���\�b�h�������ɒǉ����Ă��������B
};

extern KPIOPUSKPI_API int nkpiopuskpi;

KPIOPUSKPI_API int fnkpiopuskpi(void);
