//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアーアプリケーション　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	Windows Formのアプリケーション
//------------------------------------------------------------------------------
// WordDicSchListAct.cpp : 検索リストのアクション。
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Form1.h"				//単語辞典メインフォーム
#include "WDGroupTreeNode.h"	//分類データ用TreeNode
#include "WDDatasDef.h"			//単語辞典データ定数定義
#include "WordDicException.h"	//単語辞典用例外クラス

using namespace FJIsam;
using namespace WDDatas;

//------------------------------------------------------------------------------
// 検索単語リストボックス処理
//------------------------------------------------------------------------------
//***** クリアボタン クリック
System::Void WordDic::Form1::buttonWordListClear_Click(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		schWordLstClear();

	}catch( Exception^ exp ){
		ExceptionWrite( exp );
	}

}

//***** 検索単語リストクリア
void WordDic::Form1::schWordLstClear( void )
{
	try{
		//-- 初期処理 --//
		listBoxWordList->BeginUpdate();			//リストボックス描画停止

		//-- XMLデータ読込済みデータ以外を削除する --//
		for( Int32 i = 0; i < listBoxWordList->Items->Count; i++ )
		{
			WDWordGrp^ tmpWordGrp = safe_cast<WDWordGrp^>(listBoxWordList->Items[i] );
			
			for each( WDWordGrp^ schWordGrp in ReadedWordList )
			{
				if( schWordGrp != tmpWordGrp )
				{
					delete tmpWordGrp;
					break;
				}
			}

		}
		//-- 検索リストのクリア --//
		listBoxWordList->Items->Clear();

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"検索単語リストクリア時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31402;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;

	}finally{
		listBoxWordList->EndUpdate();			//リストボックス描画開始
	}
}
