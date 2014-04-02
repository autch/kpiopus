// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>



// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#include "kmp_pi.h"
#include "kmp_pi_tag.h"
#include "opusfile-0.5-win32/opusfile.h"
#include "CAbstractKpiDecoder.h"
#include "COpusDecoder.h"
#include "kpi.h"
