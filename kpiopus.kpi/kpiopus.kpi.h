// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された KPIOPUSKPI_EXPORTS
// シンボルを使用してコンパイルされます。このシンボルは、この DLL を使用するプロジェクトでは定義できません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// KPIOPUSKPI_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef KPIOPUSKPI_EXPORTS
#define KPIOPUSKPI_API __declspec(dllexport)
#else
#define KPIOPUSKPI_API __declspec(dllimport)
#endif

// このクラスは kpiopus.kpi.dll からエクスポートされました。
class KPIOPUSKPI_API Ckpiopuskpi {
public:
	Ckpiopuskpi(void);
	// TODO: メソッドをここに追加してください。
};

extern KPIOPUSKPI_API int nkpiopuskpi;

KPIOPUSKPI_API int fnkpiopuskpi(void);
