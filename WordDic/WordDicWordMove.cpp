//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアーアプリケーション　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	Windows Formのアプリケーション
//------------------------------------------------------------------------------
// WordDicWordMove.cpp : 単語表示移動
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Form1.h"				//単語辞典メインフォーム
#include "WordDicDef.h"			//単語辞典用定義ファイル
#include "WDGroupTreeNode.h"	//分類データ用TreeNode
#include "WDDatasDef.h"			//単語辞典データ定数定義
#include "WordDicException.h"	//単語辞典用例外クラス

using namespace FJIsam;
using namespace WDDatas;
using namespace System::Xml;

//***** 検索単語リスト ダブルクリック（単語表示）
System::Void WordDic::Form1::webBrowserBook_Navigating(System::Object^  sender, System::Windows::Forms::WebBrowserNavigatingEventArgs^  e)
{
	String^ tmpUrl;

	try
	{
		//-- 初期処理 --//
		try
		{
			tmpUrl = Path::GetFileName( e->Url->ToString() );

		}catch( Exception^ exp ){
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"移動先URL取得時にエラーが発生しました。", exp );
			tmpWordDicException->ErrorCode = 31501;
			tmpWordDicException->ErrorCode2 = 1;
			throw tmpWordDicException;
		}

		//-- データの移動先がxmlファイル(単語データ)でない場合、リンクをチェック --//
		if( String::Compare( Path::GetExtension( tmpUrl ), L".xml", true ) != 0 )
		{
			BrowserLinkChk( tmpUrl );
		}

	}catch( Exception^ exp ){
		ExceptionWrite( exp );
	}
}

//***** リンクチェック
void WordDic::Form1::BrowserLinkChk(System::String^ inUrlStr)
{
	String^ tmpStr;
	String^ tmpCmdStr;
	String^ tmpIDStr;
	Int32	tmpWordID;

	//-- 引数チェック --//
	if( inUrlStr == nullptr )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"表示単語情報が未指定です。" );
		tmpWordDicException->ErrorCode = 31502;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;

	}

	//-- 動作コマンドを取得
	tmpCmdStr = Path::GetFileNameWithoutExtension( inUrlStr );
	if( tmpCmdStr->Length == 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"リンクのコマンドが未設定です。" );
		tmpWordDicException->ErrorCode = 31502;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- 対象IDを取得(単語IDまたは分類ID)
	tmpStr = Path::GetExtension( inUrlStr );
	if( tmpStr->Length <= 1 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"リンクのIDが未設定です。" );
		tmpWordDicException->ErrorCode = 31502;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}
	tmpIDStr = tmpStr->TrimStart( L'.' );
	delete tmpStr;

	//--コマンド実行

	//単語移動(言語A)
	if( String::Compare( tmpCmdStr, "A" ) == 0 )
	{
		try
		{
			tmpWordID = Int32::Parse( tmpIDStr );

		}catch( Exception^ exp ){
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語IDの指定が不正です。", exp );
			tmpWordDicException->ErrorCode = 31502;
			tmpWordDicException->ErrorCode2 = 4;
			throw tmpWordDicException;
		}
		WordDispMove( 1, tmpWordID );

	//単語移動(言語B)
	}else if( String::Compare( tmpCmdStr, "B" ) == 0 ) {	
		try
		{
			tmpWordID = Int32::Parse( tmpIDStr );

		}catch( Exception^ exp ){
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語IDの指定が不正です。", exp );
			tmpWordDicException->ErrorCode = 31502;
			tmpWordDicException->ErrorCode2 = 5;
			throw tmpWordDicException;
		}
		WordDispMove( 2, tmpWordID );

	//分類検索(言語A)
	}else if( String::Compare( tmpCmdStr, "AG" ) == 0 ) {
		if( tmpIDStr->Length != 4 )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類IDの指定が不正です。" );
			tmpWordDicException->ErrorCode = 31502;
			tmpWordDicException->ErrorCode2 = 6;
			throw tmpWordDicException;
		}
		WordGroupSch( 1, tmpIDStr );

	//分類検索(言語B)
	}else if( String::Compare( tmpCmdStr, "BG" ) == 0 ) {		
		if( tmpIDStr->Length != 4 )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類IDの指定が不正です。" );
			tmpWordDicException->ErrorCode = 31502;
			tmpWordDicException->ErrorCode2 = 7;
			throw tmpWordDicException;
		}
		WordGroupSch( 2, tmpIDStr );

	//コマンド不正
	}else {
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"コマンドが正しくありません。" );
		tmpWordDicException->ErrorCode = 31502;
		tmpWordDicException->ErrorCode2 = 8;
		throw tmpWordDicException;
	}

}

//***** 単語表示移動
void WordDic::Form1::WordDispMove( Int32 inLang, Int32 inWordID )
{
	array<Byte>^ schWordIDKey;
	WDWordGrp^ schWDWordGrp;
	DataRecord^ tmpDataRecord;
	WDWord^ tmpWord;

	//-- 引数チェック --//
	if( inLang != 1 && inLang != 2 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"言語指定が不正です。" );
		tmpWordDicException->ErrorCode = 31503;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}
	if( inWordID <= 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語IDが不正です。" );
		tmpWordDicException->ErrorCode = 31503;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- 既存の表示データを検索する --//
	try
	{
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getSchLang() == inLang &&
				tmpWDWordGrp->getWordID() == inWordID )
			{
				//表示データを最新に移動する
				ReadedWordList->Remove( tmpWDWordGrp );
				ReadedWordList->Add( tmpWDWordGrp );

				//URLを指定する
				webBrowserBook->Url = gcnew Uri( tmpWDWordGrp->getXMLFname() );

				return;
			}
		}
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"既存の単語データ検索中にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31503;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}

	//-- 単語を検索し、表示する --//
	try
	{

		//検索キーを取得する
		schWordIDKey = FJIsam::FJIFuncs::Int32ToArray( inWordID, nullptr, 0 );

		switch( inLang )
		{
		//言語Aを検索する
		case 1:
			tmpDataRecord = WordFileA->ReadRecord( schWordIDKey, 2 );
			if( tmpDataRecord == nullptr )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( L"該当する単語が見つかりません。" );
				tmpWordDicException->ErrorCode = 31503;
				tmpWordDicException->ErrorCode2 = 4;
				throw tmpWordDicException;
			}
			schWDWordGrp = gcnew WDWordGrp( inLang,
				WDConfigParm->WordListDispA, WDConfigParm->WordListSubDispA );
			tmpWord = gcnew WDWord( tmpDataRecord );
			schWDWordGrp->addWord( tmpWord, false );

			WordGrpLoadA( schWDWordGrp );
			WordGrpDispA( schWDWordGrp );
			break;

		//言語Bを検索する
		case 2:
			tmpDataRecord = WordFileB->ReadRecord( schWordIDKey, 2 );
			if( tmpDataRecord == nullptr )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( L"該当する単語が見つかりません。" );
				tmpWordDicException->ErrorCode = 31503;
				tmpWordDicException->ErrorCode2 = 5;
				throw tmpWordDicException;
			}
			schWDWordGrp = gcnew WDWordGrp( inLang,
				WDConfigParm->WordListDispB, WDConfigParm->WordListSubDispB );
			tmpWord = gcnew WDWord( tmpDataRecord );
			schWDWordGrp->addWord( tmpWord, false );

			WordGrpLoadB( schWDWordGrp );
			WordGrpDispB( schWDWordGrp );
			break;

		}
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"移動先の単語データ作成中にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31503;
		tmpWordDicException->ErrorCode2 = 6;
		throw tmpWordDicException;

	}finally{
		if( schWordIDKey != nullptr ) delete schWordIDKey;
	}
}

//***** 単語グループ検索
void WordDic::Form1::WordGroupSch( Int32 inLang, String^ inGroupID )
{
	array<Byte>^ tmpGroupID;
	System::Text::Encoding^ tmpEnc;				//エンコーダ
	
	//-- 引数チェック --//
	if( inLang != 1 && inLang != 2 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"言語指定が不正です。" );
		tmpWordDicException->ErrorCode = 31504;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}
	if( inGroupID == nullptr || 
		inGroupID->Length != 4 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類IDが不正です。" );
		tmpWordDicException->ErrorCode = 31503;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- グループ検索 --//
	tmpEnc = System::Text::Encoding::ASCII;
	tmpGroupID = tmpEnc->GetBytes( inGroupID );

	if( SchGroup != nullptr ) delete SchGroup;
	SchGroup = tmpGroupID;

	SchMethod = 2;
	if( inLang == 1 )
	{

		SchLanguage = 1;
		radioButtonGroupA->Checked = true;
	}else{
		SchLanguage = 2;
		radioButtonGroupB->Checked = true;
	}

	try
	{
		listBoxWordList->BeginUpdate();
		//単語リストクリア
		try
		{

			listBoxWordList->Sorted = false;
			schWordLstClear();
		}catch( Exception^ exp ){
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類検索の前処理でエラーが発生しました。", exp );
			tmpWordDicException->ErrorCode = 31503;
			tmpWordDicException->ErrorCode2 = 3;
			throw tmpWordDicException;
		}

		if( inLang == 1 )
		{
			GroupSchA();					//言語A 検索
			//ソート
			WordSchListComparer->setSortOrder(  WDWordSchListComparer::schGrp, 
						WDConfigParm->WordListSortA1, WDConfigParm->WordListSortA2 );
			ArrayList::Adapter( listBoxWordList->Items )->Sort( WordSchListComparer );
		}else{	
			GroupSchB();					//言語B 検索
			//ソート
			WordSchListComparer->setSortOrder( WDWordSchListComparer::schGrp, 
						WDConfigParm->WordListSortB1, WDConfigParm->WordListSortB2 );
			ArrayList::Adapter( listBoxWordList->Items )->Sort( WordSchListComparer );

		}
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類検索でエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31504;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		listBoxWordList->EndUpdate();
		webBrowserBook->Url = webBrowserBook->Url;
	}
}