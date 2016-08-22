//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアーアプリケーション　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	Windows Formのアプリケーション
//------------------------------------------------------------------------------
// WordDicEnd.cpp : 終了処理を記述したファイルです。
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Form1.h"				//単語辞典メインフォーム
#include "WordDicDef.h"			//単語辞典用定義ファイル
#include "WordDicCfg.h"			//単語辞典コンフィグ
#include "WDGroupTreeNode.h"	//分類データ用TreeNode
#include "WDDatasDef.h"			//単語辞典データ定数定義
#include "FJIsamDef.h"			//ISAM用定義ファイル
#include "WordDicException.h"	//単語辞典用例外クラス

using namespace FJIsam;
using namespace WDDatas;


//------------------------------------------------------------------------------
// デストラクタ
//------------------------------------------------------------------------------
WordDic::Form1::~Form1()
{
	try
	{
		DeleteXmlFiles();
		DeleteDatas();

	}catch( Exception^ exp ){
		ExceptionWrite( exp );
	}

	if (components)
	{
		delete components;
	}
}

//------------------------------------------------------------------------------
// 終了処理
//------------------------------------------------------------------------------
//***** XMLデータ削除処理
void WordDic::Form1::DeleteXmlFiles( void )
{
	DirectoryInfo^				schDir;
	Collections::IEnumerator^	schEnum;

	//-- 単語表示データ格納フォルダがなければ何もしない --//
	if( DispXMLForder == nullptr ||
		DispXMLForder->Length == 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語表示データ格納フォルダが定義されていません。", nullptr );
		tmpWordDicException->ErrorCode = 31701;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- ファイルを削除 --//
	try
	{
		schDir = gcnew DirectoryInfo( DispXMLForder );

		schEnum =  schDir->GetFiles()->GetEnumerator();

		//-- 全データを削除するまで繰り返す
		while( schEnum->MoveNext() )
		{
			FileInfo^ tmpFile = safe_cast<FileInfo^>(schEnum->Current);
			
			tmpFile->Delete();
		}
		schDir->Delete(true);
	
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語表示ファイル削除中にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31701;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;

	}finally{
		if( schDir != nullptr ) delete schDir;
	}
}

//***** データ削除
void WordDic::Form1::DeleteDatas( void )
{
	if( ReadedWordList != nullptr ) delete ReadedWordList;
}
