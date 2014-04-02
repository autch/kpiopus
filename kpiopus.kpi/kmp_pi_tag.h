
#pragma once

/* http://kbmplaybbs.dip.jp/?md=hf&no=4285&pn=4285&ln=101&sln=x&bm=mv&qt=1 */

/****
・タグ情報とビットレート取得のプラグイン化(未完成)
　・概要は以下の通り
　・エクスポートする関数
　　・BOOL WINAPI kmp_GetTestTagInfo(const char *cszFileName, 
　　　　　　　　　　　　　　　　　　 IKmpTagInfo *pTagInfo);
　　・class IKmpTagInfo
　　　{
　　　　public:
　　　　　　virtual void WINAPI SetValueA(const char *name, 
　　　　　　　　　　　　　　　　　　　　　const char *value)=0;//ANSI
　　　　　　virtual void WINAPI SetValueW(const char *name, 
　　　　　　　　　　　　　　　　　　　　　const WCHAR *value)=0;//UNICODE
　　　　　　virtual void WINAPI SetValueU8(const char *name, 
　　　　　　　　　　　　　　　　　　　　　const char *value)=0;//UTF8
　　　};
　　・name="title", "artist", "album", "comment", "genre", "date", "bitrate"
　　・kmp_GetTestTagInfo の使用前に 1度だけ KMPMODULE::Init が呼ばれる
　　・FreeLibrary 前に KMPMODULE::Deinit が呼ばれる
　・表示する情報の優先度
　　1.実際に使用する(優先度が最も高い)プラグイン
　　2.↑と対応形式が同じ別のプラグイン(優先度順)
　　3.KbMedia Player 内蔵のタグ取得ルーチン
　・2 と 3 を省略するように(使用するプラグインで得た情報しか表示しないように)プ
　　ラグイン側で指定することも可(pTagInfo->SetValue(NULL, NULL) を呼ぶ)
　・再生は複数の拡張子に対応するが、タグ情報取得は一部の拡張子にしか対応しない
　　場合、対応しない形式に対しては何もしないで TRUE を返せば良い
　・あくまでも暫定的なものなので最低限の機能しか提供しない
　・根本的にはプラグイン仕様そのものを一から作り直す必要がある
　・未完成なので仕様変更の可能性大
 */


class IKmpTagInfo
{
public:
	virtual void WINAPI SetValueA(const char *name, const char *value) = 0; //ANSI
	virtual void WINAPI SetValueW(const char *name, const WCHAR *value) = 0; //UNICODE
	virtual void WINAPI SetValueU8(const char *name, const char *value) = 0; //UTF8
};

typedef BOOL (WINAPI *pfnGetTestTagInfo)(const char *cszFileName, IKmpTagInfo *pTagInfo);