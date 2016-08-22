//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアーアプリケーション　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	Windows Formのアプリケーション
//------------------------------------------------------------------------------
// WordDicGroupSch.cpp : 分類検索
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
//***** 分類ツリービュー ダブルクリック
System::Void WordDic::Form1::treeViewGroupTree_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	WDGroupTreeNode^ tmpTreeNode;
	
	//-- アイテムが見選択なら何もしない --//
	if( treeViewGroupTree->SelectedNode == nullptr )
	{
		return;
	}

	//-- 初期化 --//
	tmpTreeNode = safe_cast<WDGroupTreeNode^>(treeViewGroupTree->SelectedNode);
	if( SchGroup != nullptr )
	{
		delete SchGroup;
		SchGroup = nullptr;
	}
	SchGroup = gcnew array<Byte>( WDMEAN_GROUPGTLEN + WDMEAN_GROUPLTLEN );

	tmpTreeNode->getGroupGt( SchGroup );
	Buffer::BlockCopy( tmpTreeNode->getGroupLt( nullptr ), 0, SchGroup, WDMEAN_GROUPGTLEN, WDMEAN_GROUPLTLEN );

	SchMethod = 2;								//検索方法(分類)
	if( radioButtonGroupA->Checked == true )	//検索言語(A or B)
	{
		SchLanguage = 1;
	}else{
		SchLanguage = 2;
	}
	SchState = 0;								//検索状態(分類のため 0);

	//-- 分類検索 --//
	try
	{
		//単語リストクリア
		try
		{
			listBoxWordList->Sorted = false;
			schWordLstClear();
		}catch( Exception^ exp ){
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類検索の前処理でエラーが発生しました。", exp );
			tmpWordDicException->ErrorCode = 31601;
			tmpWordDicException->ErrorCode2 = 1;
			throw tmpWordDicException;
		}

		listBoxWordList->BeginUpdate();

		if( SchLanguage == 1 )
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

//------------------------------------------------------------------------------
// 検索処理
//------------------------------------------------------------------------------
//***** 分類検索 言語A
void WordDic::Form1::GroupSchA( void )
{
	DataRecord^ tmpRecord;
	WDMean^		tmpMean;
	WDWordGrp^	tmpWordGrp;

	//-- 意味 --//
	try
	{
		
		//1件目のデータ
		tmpRecord = MeanFileA->ReadRecord( SchGroup, 2 );
		if( tmpRecord != nullptr )
		{
			tmpMean = gcnew WDMean( tmpRecord );
			tmpWordGrp = gcnew WDWordGrp( SchLanguage,
				WDConfigParm->WordListDispA, WDConfigParm->WordListSubDispA );
			tmpWordGrp->addMean( tmpMean, true, tmpMean->getMeanFlg(0) );
			ReadBaseWordA( tmpWordGrp );

			listBoxWordList->Items->Add( tmpWordGrp );

			while( true )
			{
				if( tmpMean->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
					tmpMean->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
				{
					break;
				}

				tmpRecord = MeanFileA->NextRecord( tmpRecord );
				if( tmpRecord == nullptr )
				{
					break;
				}
				tmpMean = gcnew WDMean( tmpRecord );
				//既に検索済みの単語IDと同一なら何もしない
				if( chkWordList( tmpMean->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispA, WDConfigParm->WordListSubDispA );
					tmpWordGrp->addMean( tmpMean, true, tmpMean->getMeanFlg(0) );
					ReadBaseWordA( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}
			}
		}
	}catch( Exception^ exp )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31602;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

}

//***** 分類検索 言語B
void WordDic::Form1::GroupSchB( void )
{
	DataRecord^ tmpRecord;
	WDMean^		tmpMean;
	WDWordGrp^	tmpWordGrp;

	//-- 意味 --//
	try
	{
		//1件目のデータ
		tmpRecord = MeanFileB->ReadRecord( SchGroup, 2 );
		if( tmpRecord != nullptr )
		{
			tmpMean = gcnew WDMean( tmpRecord );
			tmpWordGrp = gcnew WDWordGrp( SchLanguage,
				WDConfigParm->WordListDispB, WDConfigParm->WordListSubDispB );
			tmpWordGrp->addMean( tmpMean, true, tmpMean->getMeanFlg(0) );
			ReadBaseWordB( tmpWordGrp );

			listBoxWordList->Items->Add( tmpWordGrp );

			while( true )
			{
				if( tmpMean->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
					tmpMean->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
				{
					break;
				}

				tmpRecord = MeanFileB->NextRecord( tmpRecord );
				if( tmpRecord == nullptr )
				{
					break;
				}
				tmpMean = gcnew WDMean( tmpRecord );
				//既に検索済みの単語IDと同一なら何もしない
				if( chkWordList( tmpMean->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispB, WDConfigParm->WordListSubDispB );
					tmpWordGrp->addMean( tmpMean, true, tmpMean->getMeanFlg(0) );
					ReadBaseWordB( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}
			}
		}
	}catch( Exception^ exp )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31603;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

}