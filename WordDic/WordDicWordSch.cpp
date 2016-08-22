//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアーアプリケーション　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	Windows Formのアプリケーション
//------------------------------------------------------------------------------
// WordDicWordSch.cpp : 単語検索
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Form1.h"				//単語辞典メインフォーム
#include "WordDicDef.h"			//単語辞典用定義ファイル
#include "WDGroupTreeNode.h"	//分類データ用TreeNode
#include "WDDatasDef.h"			//単語辞典データ定数定義
#include "FJIsamDef.h"			//ISAM用定義ファイル
#include "WordDicException.h"	//単語辞典用例外クラス

using namespace FJIsam;
using namespace WDDatas;

//------------------------------------------------------------------------------
// イベント処理
//------------------------------------------------------------------------------
//***** 検索ボタンクリック（単語検索）
System::Void WordDic::Form1::buttonSchWord_Click(System::Object^  sender, System::EventArgs^  e)
{
	//単語検索
	WordSearch();
}

//***** 検索単語TextBox入力
System::Void WordDic::Form1::textBoxSchWord_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
	//Enterが入力されると、単語検索と行う
	if( e->KeyChar == (Char)Keys::Enter )
	{
		WordSearch();
		e->Handled = true;
	}
}

//------------------------------------------------------------------------------
// 検索処理
//------------------------------------------------------------------------------
//***** 単語検索
void WordDic::Form1::WordSearch( void )
{

	//-- 文字が空ならなにもしない --//
	if( textBoxSchWord->Text->Length == 0 )
	{
		return;
	}

	//-- 初期化 --//
	if(SchWord != nullptr )
	{	
		delete SchWord;
		SchWord = nullptr;
	}
	SchWord = textBoxSchWord->Text;				//検索単語
	SchMethod = 1;								//検索方法(単語)
	if( radioButtonWordA->Checked == true )		//検索言語(A or B)
	{
		SchLanguage = 1;
	}else{
		SchLanguage = 2;
	}
	SchState = 1;								//検索状態(単語のため 1);


	//-- 単語検索 --//
	try
	{
		//単語リストクリア
		try
		{
			schWordLstClear();
		}catch( Exception^ exp ){
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語検索の前処理でエラーが発生しました。", exp );
			tmpWordDicException->ErrorCode = 31101;
			tmpWordDicException->ErrorCode2 = 1;
			throw tmpWordDicException;
		}

		//
		listBoxWordList->BeginUpdate();

		if( SchLanguage == 1 )
		{
			WordSchA();					//言語A 検索
			//ソート
			WordSchListComparer->setSortOrder( WDWordSchListComparer::schWord, 
						WDConfigParm->WordListSortA1, WDConfigParm->WordListSortA2 );
			ArrayList::Adapter( listBoxWordList->Items )->Sort( WordSchListComparer );

		}else{	
			WordSchB();					//言語B 検索
			//ソート
			WordSchListComparer->setSortOrder( WDWordSchListComparer::schWord, 
						WDConfigParm->WordListSortB1, WDConfigParm->WordListSortB2 );
			ArrayList::Adapter( listBoxWordList->Items )->Sort( WordSchListComparer );

		}

		//単語の検索数をステータスバーに表示
		if( listBoxWordList->Items->Count == 0 )
		{
			toolStripStatusLabelSchWordCnt->Text = WDConfigParm->WordSchZero;
		}else{
			toolStripStatusLabelSchWordCnt->Text = String::Format( WDConfigParm->WordSchAny, listBoxWordList->Items->Count );
		}

	}catch( Exception^ exp ){
		ExceptionWrite( exp );

	}finally{
		listBoxWordList->EndUpdate();
	}


}

//***** 単語 言語A検索
void WordDic::Form1::WordSchA( void )
{
	List<DataRecord^>^	tmpList;
	WDWord^				tmpWord;
	WDWordGrp^			tmpWordGrp;

	//-- 単語 --//
	try
	{
		SchState = 1;								//検索状態(単語);

		//レコード検索
		tmpList = WordFileA->ReadRecordWords( SchWord, 1 );
		if( tmpList != nullptr )
		{
			for( Int32 i = 0; i < tmpList->Count; i++ )
			{
				tmpWord = gcnew WDWord( tmpList[i] );
				//重複しない単語IDの場合は処理
				if( chkWordList( tmpWord->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage, 
							WDConfigParm->WordListDispA, WDConfigParm->WordListSubDispA );
					tmpWordGrp->addWord( tmpWord, true );
					ReadBaseWordA( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}
			}
		}
	}catch( Exception^ exp ) {
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31102;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;

	}finally{
		if( tmpList != nullptr )	delete tmpList;
	}

	//-- 読み方１ --//
	try
	{
		SchState = 2;								//検索状態(読み方１);
		
		//1件目のデータ
		if( WDConfigParm->Read1IdxA != 0 )
		{
			tmpList = WordFileA->ReadRecordWords( SchWord, WDConfigParm->Read1IdxA );
		}else{
			tmpList = nullptr;
		}
		
		if( tmpList != nullptr )
		{
			for( Int32 i = 0; i < tmpList->Count; i++ )
			{
				tmpWord = gcnew WDWord( tmpList[i] );
				//重複しない単語IDの場合は処理
				if( chkWordList( tmpWord->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispA, WDConfigParm->WordListSubDispA );
					tmpWordGrp->addWord( tmpWord, true );
					ReadBaseWordA( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}else{
					delete tmpList[i];
					tmpList[i] = nullptr;
				}
			}
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"読み方１検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31102;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;

	}finally{
		if( tmpList != nullptr )	delete tmpList;
	}

	//-- 読み方２ --//
	try
	{
		SchState = 3;								//検索状態(読み方２);
		
		//1件目のデータ
		if( WDConfigParm->Read2IdxA != 0 )
		{
			tmpList = WordFileA->ReadRecordWords( SchWord, WDConfigParm->Read2IdxA );
		}else{
			tmpList = nullptr;
		}

		if( tmpList != nullptr )
		{
			for( Int32 i = 0; i < tmpList->Count; i++ )
			{
				tmpWord = gcnew WDWord( tmpList[i] );
				//重複しない単語IDの場合は処理
				if( chkWordList( tmpWord->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispA, WDConfigParm->WordListSubDispA );
					tmpWordGrp->addWord( tmpWord, true );
					ReadBaseWordA( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}else{
					delete tmpList[i];
					tmpList[i] = nullptr;
				}
			}
		}

	}catch( Exception^ exp ) {
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"読み方２検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31102;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		if( tmpList != nullptr )	delete tmpList;
	}

}

//***** 単語 言語B検索
void WordDic::Form1::WordSchB( void )
{
	List<DataRecord^>^	tmpList;
	WDWord^				tmpWord;
	WDWordGrp^			tmpWordGrp;

	//-- 単語 --//
	try
	{
		SchState = 1;								//検索状態(単語);

		//レコード検索
		tmpList = WordFileB->ReadRecordWords( SchWord, 1 );
		if( tmpList != nullptr )
		{
			for( Int32 i = 0; i < tmpList->Count; i++ )
			{
				tmpWord = gcnew WDWord( tmpList[i] );
				//重複しない単語IDの場合は処理
				if( chkWordList( tmpWord->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispB, WDConfigParm->WordListSubDispB );
					tmpWordGrp->addWord( tmpWord, true );
					ReadBaseWordB( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}
			}
		}

	}catch( Exception^ exp ) {
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31103;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;

	}finally{
		if( tmpList != nullptr )	delete tmpList;
	}

	//-- 読み方１ --//
	try
	{
		SchState = 2;								//検索状態(読み方１);
		
		//レコード検索
		if( WDConfigParm->Read1IdxB != 0 )
		{
			tmpList = WordFileB->ReadRecordWords( SchWord, WDConfigParm->Read1IdxB );
		}else{
			tmpList = nullptr;
		}

		if( tmpList != nullptr )
		{
			for( Int32 i = 0; i < tmpList->Count; i++ )
			{
				tmpWord = gcnew WDWord( tmpList[i] );
				//重複しない単語IDの場合は処理
				if( chkWordList( tmpWord->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispB, WDConfigParm->WordListSubDispB );
					tmpWordGrp->addWord( tmpWord, true );
					ReadBaseWordB( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}
			}
		}

	}catch( Exception^ exp ) {
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"読み方１検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31103;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;

	}finally{
		if( tmpList != nullptr )	delete tmpList;
	}

	//-- 読み方２ --//
	try
	{
		SchState = 3;								//検索状態(読み方２);
		
		//1件目のデータ
		if( WDConfigParm->Read2IdxB != 0 )
		{
			tmpList = WordFileB->ReadRecordWords( SchWord, WDConfigParm->Read2IdxB );
		}else{
			tmpList = nullptr;
		}

		if( tmpList != nullptr )
		{
			for( Int32 i = 0; i < tmpList->Count; i++ )
			{
				tmpWord = gcnew WDWord( tmpList[i] );
				//重複しない単語IDの場合は処理
				if( chkWordList( tmpWord->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispB, WDConfigParm->WordListSubDispB );
					tmpWordGrp->addWord( tmpWord, true );
					ReadBaseWordB( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}
			}
		}

	}catch( Exception^ exp ) {
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"読み方２検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31103;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		if( tmpList != nullptr )	delete tmpList;
	}
}

//***** 単語基本形検索 言語A
void WordDic::Form1::ReadBaseWordA( WDWordGrp^ inWordGrp )
{
	DataRecord^	tmpRecord;
	WDWord^	tmpWord;
	array<Byte>^ tmpWordID;


	//-- 既に基本単語を読込済みならなにもしない --//
	if( inWordGrp->getBaseWord() != nullptr )
	{
		return;
	}

	
	try
	{
		//-- データ初期化 --//
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordGrp->getWordID(), nullptr, 0 );

		//-- 1件目 --//
		tmpRecord = WordFileA->ReadRecord( tmpWordID, 2 );
		if( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"単語ID:{0} のデータが見つかりません。", inWordGrp->getWordID() ) );
			tmpWordDicException->ErrorCode = 31104;
			tmpWordDicException->ErrorCode2 = 1;
			throw tmpWordDicException;
		}
		tmpWord = gcnew WDWord( tmpRecord );
		inWordGrp->addWord( tmpWord, false );
		
		//-- 2件以降 --//
		while( true )
		{
			if( inWordGrp->getBaseWord() != nullptr )
			{
				break;
			}
			if( tmpWord->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpWord->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"単語ID:{0} の単語基本形が見つかりません。", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31104;
				tmpWordDicException->ErrorCode2 = 2;
				throw tmpWordDicException;
			}

			tmpRecord = WordFileA->NextRecord( tmpRecord );
			if( tmpRecord == nullptr )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"単語ID:{0} の単語基本形が見つかりません。", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31103;
				tmpWordDicException->ErrorCode2 = 3;
				throw tmpWordDicException;
			}
			tmpWord = gcnew WDWord( tmpRecord );
			inWordGrp->addWord( tmpWord, false );
		}
	}catch( Exception^ exp )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語基本形の検索中にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31104;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;

	//-- 終了処理 --//
	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
	}

}

//***** 単語基本形検索 言語B
void WordDic::Form1::ReadBaseWordB( WDWordGrp^ inWordGrp )
{
	DataRecord^	tmpRecord;
	WDWord^	tmpWord;
	array<Byte>^ tmpWordID;


	//-- 既に基本単語を読込済みならなにもしない --//
	if( inWordGrp->getBaseWord() != nullptr )
	{
		return;
	}

	
	try
	{
		//-- データ初期化 --//
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordGrp->getWordID(), nullptr, 0 );

		//-- 1件目 --//
		tmpRecord = WordFileB->ReadRecord( tmpWordID, 2 );
		if( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"単語ID:{0} のデータが見つかりません。", inWordGrp->getWordID() ) );
			tmpWordDicException->ErrorCode = 31105;
			tmpWordDicException->ErrorCode2 = 1;
			throw tmpWordDicException;
		}
		tmpWord = gcnew WDWord( tmpRecord );
		inWordGrp->addWord( tmpWord, false );
		
		//-- 2件以降 --//
		while( true )
		{
			if( inWordGrp->getBaseWord() != nullptr )
			{
				break;
			}
			if( tmpWord->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpWord->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"単語ID:{0} の単語基本形が見つかりません。", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31105;
				tmpWordDicException->ErrorCode2 = 2;
				throw tmpWordDicException;
			}

			tmpRecord = WordFileB->NextRecord( tmpRecord );
			if( tmpRecord == nullptr )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"単語ID:{0} の単語基本形が見つかりません。", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31105;
				tmpWordDicException->ErrorCode2 = 3;
				throw tmpWordDicException;
			}
			tmpWord = gcnew WDWord( tmpRecord );
			inWordGrp->addWord( tmpWord, false );
		}
	}catch( Exception^ exp )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語基本形の検索中にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31105;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;

	//-- 終了処理 --//
	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
	}

}

//***** 基本単語ID重複検索
Int32 WordDic::Form1::chkWordList( Int32 inWordID )
{
	//-- 一致すれば 0 --//
	for( Int32 i = 0; i < listBoxWordList->Items->Count; i++ )
	{
		WDWordGrp^ tmpWordGrp = safe_cast<WDWordGrp^>(listBoxWordList->Items[i]);

		if( tmpWordGrp->getWordID() == inWordID )
		{
			return 0;
		}
	}
	//-- 一致無し --//
	return -1;
}

