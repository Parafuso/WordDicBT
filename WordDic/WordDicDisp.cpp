//------------------------------------------------------------------------------
//	ことばの辞典　ことばの辞典ビューアアプリケーション　ソース
//	Version 1.0.1.0		create date 2006/05/08
//	Version 1.0.1.1		change date 2010/10/22	WordGrpDispA　WordGrpDispB 基本単語表示順を１番目の読みからに変更
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	Windows Formのアプリケーション
//------------------------------------------------------------------------------
// WordDicWordDisp.cpp : 単語表示
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
using namespace System::Xml;

//***** 検索単語リスト ダブルクリック（単語表示）
System::Void WordDic::Form1::listBoxWordList_DoubleClick(System::Object^ sender, System::EventArgs^ e)
{
	WDWordGrp^ selWDWordGrp;

	try
	{
		//-- 選択されている単語を取得
		if( listBoxWordList->SelectedItem == nullptr )
		{
			return;
		}else{
			selWDWordGrp = safe_cast<WDWordGrp^>(listBoxWordList->SelectedItem);
		}

		if( SchLanguage == 1 )
		{
			WordGrpLoadA( selWDWordGrp );
			WordGrpDispA( selWDWordGrp );
		}else{
			WordGrpLoadB( selWDWordGrp );
			WordGrpDispB( selWDWordGrp );
		}

	}catch( Exception^ exp ){
		ExceptionWrite( exp );
	}
}


//***** 単語グループ読込 言語A
void WordDic::Form1::WordGrpLoadA( WDWordGrp^ inWordGrp )
{
	DataRecord^	tmpRecord;
	WDWord^	tmpWord;
	WDMean^ tmpMean;
	WDTrans^ tmpTrans;
	WDRelation^ tmpRelation;
	array<Byte>^ tmpWordID;

	//-- 作成済みのデータの有無をチェック
	try
	{
		//既にXML作成済みなら何もしない
		if( inWordGrp->getXMLFname() != nullptr )
		{
			return;
		}

		//既にXMLデータを作成している履歴がないかチェック
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getWordID() == inWordGrp->getWordID() && 
				tmpWDWordGrp->getSchLang() == inWordGrp->getSchLang() )
			{
				//読込済みデータがあっても、XMLデータがなければ作りなおし
				if( tmpWDWordGrp->getXMLFname() == nullptr ||
					tmpWDWordGrp->getXMLFname()->Length == 0 )
				{
					ReadedWordList->Remove( tmpWDWordGrp );
					delete tmpWDWordGrp;
				}else{

					//表示リスト(履歴)の最後に追加する
					ReadedWordList->Remove( tmpWDWordGrp );
					ReadedWordList->Add( tmpWDWordGrp );
					inWordGrp->setXMLFname( tmpWDWordGrp->getXMLFname() );
					return;
				}
			}
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"既存の単語表示データ検索中にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31303;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//リスト作成
	try
	{
		//-- データ初期化 --//
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordGrp->getWordID(), nullptr, 0 );

		//-- 単語読込 --//
		//1件目
		tmpRecord = WordFileA->ReadRecord( tmpWordID, 2 );
		if( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"単語ID:{0} の単語が見つかりません。", inWordGrp->getWordID() ) );
			tmpWordDicException->ErrorCode = 31303;
			tmpWordDicException->ErrorCode2 = 2;
			throw tmpWordDicException;
		}
		tmpWord = gcnew WDWord( tmpRecord );
		inWordGrp->addWord( tmpWord, false );
		
		//2件以降
		while( true )
		{
			if( tmpWord->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpWord->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
			{
				break;
			}

			tmpRecord = WordFileA->NextRecord( tmpRecord );
			if( tmpRecord == nullptr )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"単語ID:{0} の全ての単語が読み込めません。", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31303;
				tmpWordDicException->ErrorCode2 = 3;
				throw tmpWordDicException;
			}
			tmpWord = gcnew WDWord( tmpRecord );
			inWordGrp->addWord( tmpWord, false );
		}

		//-- 意味読込 --//
		//1件目
		tmpRecord = MeanFileA->ReadRecord( tmpWordID, 1 );
		if( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"単語ID:{0} の意味が見つかりません。", inWordGrp->getWordID() ) );
			tmpWordDicException->ErrorCode = 31303;
			tmpWordDicException->ErrorCode2 = 4;
			throw tmpWordDicException;
		}
		tmpMean = gcnew WDMean( tmpRecord );
		inWordGrp->addMean( tmpMean, false, 0 );
		
		//2件以降
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
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"単語ID:{0} の全ての意味が読み込めません。", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31303;
				tmpWordDicException->ErrorCode2 = 5;
				throw tmpWordDicException;
			}
			tmpMean = gcnew WDMean( tmpRecord );
			inWordGrp->addMean( tmpMean, false, 0 );
		}

		//-- 翻訳読込 --//
		//1件目
		tmpRecord = TransFileA->ReadRecord( tmpWordID, 1 );
		if( tmpRecord != nullptr )
		{
			tmpTrans = gcnew WDTrans( tmpRecord );
			inWordGrp->addTrans( tmpTrans );
		
			//2件以降
			while( true )
			{
				if( tmpTrans->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
					tmpTrans->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )	
				{
					break;
				}

				tmpRecord = TransFileA->NextRecord( tmpRecord );
				if( tmpRecord == nullptr )
				{
					WordDicException^ tmpWordDicException = gcnew WordDicException( 
						String::Format( L"単語ID:{0} の全ての翻訳が読み込めません。", inWordGrp->getWordID() ) );
					tmpWordDicException->ErrorCode = 31303;
					tmpWordDicException->ErrorCode2 = 6;
					throw tmpWordDicException;
				}
				tmpTrans = gcnew WDTrans( tmpRecord );
				inWordGrp->addTrans( tmpTrans );
			}
		}

		//-- 関連語読込 --//
		//1件目
		tmpRecord = RelationFileA->ReadRecord( tmpWordID, 1 );
		if( tmpRecord != nullptr )
		{
			tmpRelation = gcnew WDRelation( tmpRecord );
			inWordGrp->addRelation( tmpRelation );

			//2件以降
			while( true )
			{
				if( tmpRelation->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
					tmpRelation->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
				{
					break;
				}
	
				tmpRecord = RelationFileA->NextRecord( tmpRecord );
				if( tmpRecord == nullptr )
				{
					WordDicException^ tmpWordDicException = gcnew WordDicException( 
						String::Format( L"単語ID:{0} の全ての関連語が読み込めません。", inWordGrp->getWordID() ) );
					tmpWordDicException->ErrorCode = 31303;
					tmpWordDicException->ErrorCode2 = 7;
					throw tmpWordDicException;
				}
				tmpRelation = gcnew WDRelation( tmpRecord );
				inWordGrp->addRelation( tmpRelation );
			}
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語グループの検索中にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31303;
		tmpWordDicException->ErrorCode2 = 8;
		throw tmpWordDicException;

	//-- 終了処理 --//
	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
	}

}

//***** 単語グループ読込 言語B
void WordDic::Form1::WordGrpLoadB( WDWordGrp^ inWordGrp )
{
	DataRecord^	tmpRecord;
	WDWord^	tmpWord;
	WDMean^ tmpMean;
	WDTrans^ tmpTrans;
	WDRelation^ tmpRelation;
	array<Byte>^ tmpWordID;
	
	//-- 作成済みのデータの有無をチェック
	try
	{
		//既にXML作成済みなら何もしない
		if( inWordGrp->getXMLFname() != nullptr )
		{
			return;
		}

		//既にXMLデータを作成している履歴がないかチェック
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getWordID() == inWordGrp->getWordID() && 
				tmpWDWordGrp->getSchLang() == inWordGrp->getSchLang() )
			{
				//読込済みデータがあっても、XMLデータがなければ作りなおし
				if( tmpWDWordGrp->getXMLFname() == nullptr ||
					tmpWDWordGrp->getXMLFname()->Length == 0 )
				{
					ReadedWordList->Remove( tmpWDWordGrp );
					delete tmpWDWordGrp;
				}else{

					//表示リスト(履歴)の最後に追加する
					ReadedWordList->Remove( tmpWDWordGrp );
					ReadedWordList->Add( tmpWDWordGrp );
					inWordGrp->setXMLFname( tmpWDWordGrp->getXMLFname() );
					return;
				}
			}
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"既存の単語表示データ検索中にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31304;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	try
	{
		//-- データ初期化 --//
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordGrp->getWordID(), nullptr, 0 );

		//-- 単語読込 --//
		//1件目
		tmpRecord = WordFileB->ReadRecord( tmpWordID, 2 );
		if( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"単語ID:{0} の単語が見つかりません。", inWordGrp->getWordID() ) );
			tmpWordDicException->ErrorCode = 31304;
			tmpWordDicException->ErrorCode2 = 2;
			throw tmpWordDicException;
		}
		tmpWord = gcnew WDWord( tmpRecord );
		inWordGrp->addWord( tmpWord, false );
		
		//2件以降
		while( true )
		{
			if( tmpWord->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpWord->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
			{
				break;
			}

			tmpRecord = WordFileB->NextRecord( tmpRecord );
			if( tmpRecord == nullptr )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"単語ID:{0} の全ての単語が読み込めません。", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31304;
				tmpWordDicException->ErrorCode2 = 3;
				throw tmpWordDicException;
			}
			tmpWord = gcnew WDWord( tmpRecord );
			inWordGrp->addWord( tmpWord, false );
		}

		//-- 意味読込 --//
		//1件目
		tmpRecord = MeanFileB->ReadRecord( tmpWordID, 1 );
		if( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"単語ID:{0} の意味が見つかりません。", inWordGrp->getWordID() ) );
			tmpWordDicException->ErrorCode = 31304;
			tmpWordDicException->ErrorCode2 = 4;
			throw tmpWordDicException;
		}
		tmpMean = gcnew WDMean( tmpRecord );
		inWordGrp->addMean( tmpMean, false, 0 );
		
		//2件以降
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
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"単語ID:{0} の全ての意味が読み込めません。", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31304;
				tmpWordDicException->ErrorCode2 = 5;
				throw tmpWordDicException;
			}
			tmpMean = gcnew WDMean( tmpRecord );
			inWordGrp->addMean( tmpMean, false, 0 );
		}

		//-- 翻訳読込 --//
		//1件目
		tmpRecord = TransFileB->ReadRecord( tmpWordID, 1 );
		if( tmpRecord != nullptr )
		{
			tmpTrans = gcnew WDTrans( tmpRecord );
			inWordGrp->addTrans( tmpTrans );
			
			//2件以降
			while( true )
			{
				if( tmpTrans->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
					tmpTrans->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
				{
					break;
				}

				tmpRecord = TransFileB->NextRecord( tmpRecord );
				if( tmpRecord == nullptr )
				{
					WordDicException^ tmpWordDicException = gcnew WordDicException( 
						String::Format( L"単語ID:{0} の全ての単語が読み込めません。", inWordGrp->getWordID() ) );
					tmpWordDicException->ErrorCode = 31304;
					tmpWordDicException->ErrorCode2 = 6;
					throw tmpWordDicException;
				}
				tmpTrans = gcnew WDTrans( tmpRecord );
				inWordGrp->addTrans( tmpTrans );
	
			}
		}

		//-- 関連語読込 --//
		//1件目
		tmpRecord = RelationFileB->ReadRecord( tmpWordID, 1 );
		if( tmpRecord != nullptr )
		{
			tmpRelation = gcnew WDRelation( tmpRecord );
			inWordGrp->addRelation( tmpRelation );
		
			//2件以降
			while( true )
			{
				if( tmpRelation->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
					tmpRelation->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
				{
					break;
				}

				tmpRecord = RelationFileB->NextRecord( tmpRecord );
				if( tmpRecord == nullptr )
				{
					WordDicException^ tmpWordDicException = gcnew WordDicException( 
						String::Format( L"単語ID:{0} の全ての単語が読み込めません。", inWordGrp->getWordID() ) );
					tmpWordDicException->ErrorCode = 31304;
					tmpWordDicException->ErrorCode2 = 7;
					throw tmpWordDicException;
				}
				tmpRelation = gcnew WDRelation( tmpRecord );
				inWordGrp->addRelation( tmpRelation );
			}
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語グループの検索中にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31304;
		tmpWordDicException->ErrorCode2 = 8;
		throw tmpWordDicException;

	//-- 終了処理 --//
	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
	}

}

//***** 単語グループ表示 言語A
void WordDic::Form1::WordGrpDispA( WDWordGrp^ inWordGrp )
{
	String^	XmlFName;
	XmlTextWriter^ XmlFStream;
	WDWord^			tmpWDWord;
	WDWord^			tmpWDSubWord;
	WDMean^			tmpWDMean;
	WDTrans^		tmpWDTrans;
	WDRelation^		tmpWDRelation;
	array<Byte>^	tmpGroup;

	String^			tmpGroupName;				//分類名
	array<Byte>^	tmpGroupID;					//分類ID
	array<Byte>^	tmpGroupIDGt;				//分類ID大
	array<Byte>^	tmpGroupIDLt;				//分類ID小
	System::Text::Encoding^ tmpEnc;				//エンコーダ
	array<Char>^	tmpGroupIDStr;				//分類名(出力用)

	Int32			oldPractical = -1;			//活用形
	Int32			oldPlurality = -1;			//単数複数
	Int32			oldGramatical = -1;			//人称
	Int32			oldSex = -1;				//性

	String^			tmpPrStr;
	String^			oldPrStr;
	String^			tmpRdStr;

	//-- 読込済みデータがあればそれを表示する
	try
	{
		if( inWordGrp->getXMLFname() != nullptr )
		{
				//XMLデータがあれば表示して終了
				webBrowserBook->Url = gcnew Uri( inWordGrp->getXMLFname() );		

				return;
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語データ表示にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31305;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- 新たにXMLファイルを作成する
	try
	{
		//-- 初期設定 --//
		tmpGroup = gcnew array<Byte>( WDMEAN_GROUPGTLEN + WDMEAN_GROUPLTLEN );

		XmlFName = getXMLFname();														//出力XMLファイル名取得

		XmlFStream = gcnew XmlTextWriter( XmlFName, System::Text::Encoding::Unicode );	//出力XMLファイル名セット
		XmlFStream->Formatting = Formatting::Indented;									//インデントあり
		XmlFStream->QuoteChar = L'\"';													//クオータ設定　"
		XmlFStream->WriteStartDocument();												//ドキュメントスタート
		XmlFStream->WriteProcessingInstruction( L"xml-stylesheet",						//XSLT指定
			String::Format( L"type=\"text/xsl\" href=\"{0}\"", WDConfigParm->XSLTFNameA ) );

		//ルート記述
		XmlFStream->WriteStartElement( WORDS_NODE );									

		//-- 基本単語記述 --//
		//１つ目の読み方の基本単語を表示する
		tmpWDWord = tmpWDSubWord = inWordGrp->getBaseWord( 0 );
		if( tmpWDWord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語データがありません。" );
			tmpWordDicException->ErrorCode = 31305;
			tmpWordDicException->ErrorCode2 = 2;
			throw tmpWordDicException;
		}

		XmlFStream->WriteStartElement( BASE_NODE );															//ベース
		XmlFStream->WriteElementString( BASE_WORD_ELE, tmpWDWord->getWord( nullptr ) );						//単語
		XmlFStream->WriteElementString( BASE_READ1_ELE, tmpWDWord->getRead1( nullptr ) );					//読み方１
		XmlFStream->WriteElementString( BASE_READ2_ELE, tmpWDWord->getRead2( nullptr ) );					//読み方２
		XmlFStream->WriteEndElement();

		//--基本単語(他の読み方) --//
		//２つ目以降の読み方の基本単語を表示する
		XmlFStream->WriteStartElement( SUBBASEGRP_NODE );
		for( Int32 i = 1; i < inWordGrp->getReadPatternCnt(); i++ )
		{
			tmpWDSubWord = inWordGrp->getBaseWord( i );

			//基本単語がない読み方は無視する。
			if( tmpWDSubWord == nullptr )
			{
				continue;
			}

			XmlFStream->WriteStartElement( SUBBASE_NODE );															//ベース
			XmlFStream->WriteElementString( SUBBASE_WORD_ELE, tmpWDSubWord->getWord( nullptr ) );						//単語
			XmlFStream->WriteElementString( SUBBASE_READ1_ELE, tmpWDSubWord->getRead1( nullptr ) );					//読み方１
			XmlFStream->WriteElementString( SUBBASE_READ2_ELE, tmpWDSubWord->getRead2( nullptr ) );					//読み方２
			XmlFStream->WriteEndElement();
		}
		XmlFStream->WriteEndElement();
		
		//-- 意味ブロック記述 --//
		XmlFStream->WriteStartElement( MEANS_NODE );														//意味ブロック
	
		for( Int32 i = 0; i < inWordGrp->getMeanCnt(); i++ )
		{
			XmlFStream->WriteStartElement( MEAN_NODE );														//意味
			//意味取得
			tmpWDMean = inWordGrp->getMean( i );
			if( tmpWDMean == nullptr )
			{
				continue;
			}
			//意味番号
			XmlFStream->WriteAttributeString( MEANNO_ELE, tmpWDMean->getMeanNo().ToString() );

			//-- 翻訳記述 --//
			tmpWDTrans = inWordGrp->getTransNo( tmpWDMean->getMeanNo() );

			if( tmpWDTrans != nullptr )
			{
				//翻訳グループノード
				XmlFStream->WriteStartElement( TRANSES_NODE );									

				for( Int32 j = 0; j < tmpWDTrans->CountTransID(); j++ )
				{
					//翻訳ノード
					XmlFStream->WriteStartElement( TRANS_NODE );								

					XmlFStream->WriteElementString( TRANSID_ELE,								//翻訳ID
						String::Format( L"B.{0}", tmpWDTrans->getTransID( j ).ToString() ) );	
					XmlFStream->WriteElementString( TRANSWORD_ELE,								//翻訳単語
						getTransWordA( tmpWDTrans->getTransID( j ) ) );	
				
					//翻訳ノードクローズ
					XmlFStream->WriteEndElement();												
				}

				//翻訳グループノードクローズ
				XmlFStream->WriteEndElement();													
			}

			//-- 意味記述 --//
			tmpGroupID = gcnew array<Byte>(WDMEAN_GROUPGTLEN + WDMEAN_GROUPLTLEN);
			tmpGroupIDGt = gcnew array<Byte>(WDMEAN_GROUPGTLEN);
			tmpGroupIDLt = gcnew array<Byte>(WDMEAN_GROUPLTLEN);
			tmpEnc = System::Text::Encoding::ASCII;
			tmpGroupIDStr = gcnew array<Char>(WDMEAN_GROUPGTLEN + WDMEAN_GROUPLTLEN);;

			//分類ノード
			XmlFStream->WriteStartElement( GROUP_NODE );

			for( Int32 i = 0; i < tmpWDMean->MeanGroupCount(); i++ )
			{
				tmpGroupIDGt = tmpWDMean->getGroupGt( i, tmpGroupIDGt );
				tmpGroupIDLt = tmpWDMean->getGroupLt( i, tmpGroupIDLt );
				Array::Copy( tmpGroupIDGt, tmpGroupID, 2 );
				Array::Copy( tmpGroupIDLt, 0, tmpGroupID, 2, 2 );
				tmpGroupIDStr = tmpEnc->GetChars( tmpGroupID );

				WDGroupTreeNode^ tmpWDGroupTreeNode = getGroup( tmpGroupIDGt, tmpGroupIDLt );			//分類 

				if( tmpWDGroupTreeNode != nullptr )
				{
					tmpGroupName = tmpWDGroupTreeNode->getName( nullptr );
				}else{
					tmpGroupName = L"(分類名が不明です)";
				}

				XmlFStream->WriteStartElement( GROUP_ELE );
				XmlFStream->WriteAttributeString( GROUPID_ELE,  
					String::Format( L"AG.{0} ", gcnew String(tmpGroupIDStr) ) );
				XmlFStream->WriteString( tmpGroupName );
				XmlFStream->WriteEndElement();

				delete tmpGroupIDStr;
				tmpGroupIDStr = nullptr;

			}
			XmlFStream->WriteEndElement();

			XmlFStream->WriteElementString( MSPEECH_ELE,										//意味品詞			
				getSegment( SegmentListA, SPEECH_ID, tmpWDMean->getSpeech() )->getName( nullptr ) );
			XmlFStream->WriteElementString( MRANK_ELE,											//ランク
				getSegment( SegmentListA, RANK_ID, tmpWDMean->getRank() )->getName( nullptr ) );
			XmlFStream->WriteElementString( MEAN_ELE, tmpWDMean->getMean( nullptr ) );			//意味
			XmlFStream->WriteElementString( EXAMPLE_ELE, tmpWDMean->getExample( nullptr ) );	//例文

			//-- 関連語記述 --//
			tmpWDRelation = inWordGrp->getRelationNo( tmpWDMean->getMeanNo() );

			if( tmpWDRelation != nullptr )
			{
				//関連語グループノード
				XmlFStream->WriteStartElement( RELATIONS_NODE );								

				for( Int32 j = 0; j < tmpWDRelation->CountRelation(); j++ )
				{
					XmlFStream->WriteStartElement( RELATION_NODE );								//関連語ノード

					XmlFStream->WriteElementString( RELATIONTYPE_ELE,							//関連語タイプ
						getSegment( SegmentListA, RELATION_ID, tmpWDRelation->getRelationType( j ) )->getName( nullptr ) );	
					XmlFStream->WriteElementString( RELATIONID_ELE,								//関連語ID
						String::Format( L"A.{0}", tmpWDRelation->getRelationID( j ).ToString() ) );	
					XmlFStream->WriteElementString( RELATION_ELE,								//関連語単語
						getRelationWordA( tmpWDRelation->getRelationID( j ) ) );	
				
					//翻訳ノードクローズ
					XmlFStream->WriteEndElement();												
				}

				//翻訳グループノードクローズ
				XmlFStream->WriteEndElement();													
			}

			//意味クローズ
			XmlFStream->WriteEndElement();												
		}

		//意味ブロッククローズ
		XmlFStream->WriteEndElement();													

		//-- 活用形記述 --//
		//活用グループセクションノード		
		XmlFStream->WriteStartElement( PRATICALGRPSEC_ELE );								

		//活用グループノード		
		XmlFStream->WriteStartElement( PRATICALGRP_ELE );								

		//先頭単語取得
		tmpWDWord = inWordGrp->getWord( 0 );
		Int32 tmpReadPattern = tmpWDWord->getReadPattern();

		//活用タイプ
		XmlFStream->WriteElementString( PRATICALTYPE_ELE,										//活用タイプ
			getSegment( SegmentListA, TYPE_ID, tmpWDWord->getType() )->getName( nullptr ) );
		//活用形グループノード
		XmlFStream->WriteStartElement( PRATICALS_NODE );								


		for( Int32 i = 0; i < inWordGrp->getWordCnt(); i++ )
		{
			
			tmpWDWord = inWordGrp->getWord( i );
			if( tmpWDWord == nullptr )
			{
				continue;
			}
			if( tmpReadPattern != tmpWDWord->getReadPattern() )
			{
				tmpReadPattern = tmpWDWord->getReadPattern();
				//活用形グループノードクローズ
				XmlFStream->WriteEndElement();
				//活用グループノードクローズ		
				XmlFStream->WriteEndElement();
				//活用グループノード		
				XmlFStream->WriteStartElement( PRATICALGRP_ELE );								
				//活用タイプ
				XmlFStream->WriteElementString( PRATICALTYPE_ELE,										//活用タイプ
					getSegment( SegmentListA, TYPE_ID, tmpWDWord->getType() )->getName( nullptr ) );
				//活用形グループノード
				XmlFStream->WriteStartElement( PRATICALS_NODE );								
			}

			//活用形ノード
			XmlFStream->WriteStartElement( PRATICALITEM_NODE );

			//活用形
			if( oldPractical != tmpWDWord->getPractical() )
			{
				oldPractical = tmpWDWord->getPractical();
				oldGramatical = -1;
				oldSex = -1;	
				oldPlurality = -1;
				tmpPrStr = getSegment( SegmentListA, PRATICAL_ID, oldPractical )->getName( nullptr );
			}
			//単数複数
			if( oldPlurality != tmpWDWord->getPlurality() )
			{
				oldPlurality = tmpWDWord->getPlurality();
				oldGramatical = -1;
				oldSex = -1;	
				if( tmpPrStr == nullptr ||
					tmpPrStr->Length == 0 )
				{
					if( tmpPrStr != nullptr ) delete tmpPrStr;
					tmpPrStr = getSegment( SegmentListA, PLURALITY_ID, oldPlurality )->getName( nullptr );
				}else{
					tmpRdStr = getSegment( SegmentListA, PLURALITY_ID, oldPlurality )->getName( nullptr );
					if( tmpRdStr->Length > 0 )
					{
						oldPrStr = tmpPrStr;
						tmpPrStr = String::Format( L"{0}・{1}", oldPrStr, tmpRdStr ); 
						delete oldPrStr;
					}
					delete oldPrStr;
				}

			}
			//人称
			if( oldGramatical != tmpWDWord->getGramatical() )
			{
				oldGramatical = tmpWDWord->getGramatical();
				oldSex = -1;	
				if( tmpPrStr == nullptr ||
					tmpPrStr->Length == 0 )
				{
					if( tmpPrStr != nullptr ) delete tmpPrStr;
					tmpPrStr = getSegment( SegmentListA, GRAMATICAL_ID, oldGramatical )->getName( nullptr );
				}else{
					tmpRdStr = getSegment( SegmentListA, GRAMATICAL_ID, oldGramatical )->getName( nullptr ); 
					if( tmpRdStr->Length > 0 )
					{
						oldPrStr = tmpPrStr;
						tmpPrStr = String::Format( L"{0}・{1}", oldPrStr, tmpRdStr ); 
						delete oldPrStr;
					}
					delete tmpRdStr;
				}
			}
			//性
			if( oldSex != tmpWDWord->getSex() )
			{
				oldSex = tmpWDWord->getSex();
				if( tmpPrStr == nullptr ||
					tmpPrStr->Length == 0 )
				{
					if( tmpPrStr != nullptr ) delete tmpPrStr;
					tmpPrStr = getSegment( SegmentListA, SEX_ID, oldSex )->getName( nullptr );
				}else{
					tmpRdStr = getSegment( SegmentListA, SEX_ID, oldSex )->getName( nullptr );
					if( tmpRdStr->Length > 0 )
					{
						oldPrStr = tmpPrStr;
						tmpPrStr = String::Format( L"{0}・{1}", oldPrStr, tmpRdStr ); 
						delete oldPrStr;
					}
					delete tmpRdStr;
				}
			}
			//活用形
			XmlFStream->WriteStartElement( PRATICALTITLE_ELE );
			XmlFStream->WriteAttributeString( PRATICALTYPEID_ELE,									//活用タイプID
										tmpWDWord->getType().ToString() );
			XmlFStream->WriteAttributeString( PRATICALID_ELE,											//活用形ID
										tmpWDWord->getPractical().ToString() );
			XmlFStream->WriteString( tmpPrStr );
			XmlFStream->WriteEndElement();
			delete tmpPrStr;
			tmpPrStr = nullptr;

			XmlFStream->WriteElementString( PRATICALWORD_ELE, tmpWDWord->getWord( nullptr ) );		//単語
			XmlFStream->WriteElementString( PRATICALREAD1_ELE, tmpWDWord->getRead1( nullptr ) );	//読み方１
			XmlFStream->WriteElementString( PRATICALREAD2_ELE, tmpWDWord->getRead2( nullptr ) );	//読み方２

			//活用形クローズ
			XmlFStream->WriteEndElement();													
		}
		//活用形グループクローズ
		XmlFStream->WriteEndElement();													
		//活用グループクローズ
		XmlFStream->WriteEndElement();
		//活用グループセクションクローズ
		XmlFStream->WriteEndElement();

		//-- 終了処理 --//
		//ルートクローズ
		XmlFStream->WriteEndElement();													
		XmlFStream->Flush();
		XmlFStream->Close();

		//単語グループを読込済みリストに追加
		inWordGrp->setXMLFname( XmlFName );
		ReadedWordList->Add( inWordGrp );
		webBrowserBook->Url = gcnew Uri( inWordGrp->getXMLFname() );		

	}catch( Exception^ exp )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"表示データ作成時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31305;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		if( XmlFName != nullptr ) delete XmlFName;
		if( XmlFStream != nullptr ) delete XmlFStream;
		if( tmpGroupName != nullptr ) delete tmpGroupName;
		if( tmpGroupID != nullptr ) delete tmpGroupID;
		if( tmpGroupIDGt != nullptr ) delete tmpGroupIDGt;
		if( tmpGroupIDLt != nullptr ) delete tmpGroupIDLt;
		if( tmpEnc != nullptr ) delete tmpEnc;
		if( tmpGroupIDStr != nullptr ) delete tmpGroupIDStr;
	}

}

//***** 単語グループ表示 言語B
void WordDic::Form1::WordGrpDispB( WDWordGrp^ inWordGrp )
{
	String^			XmlFName;					//XMLファイル名
	XmlTextWriter^	XmlFStream;					//XMLファイルライター
	WDWord^			tmpWDWord;					//単語データ
	WDWord^			tmpWDSubWord;				//サブ単語データ(読み)
	WDMean^			tmpWDMean;					//意味データ
	WDTrans^		tmpWDTrans;					//翻訳データ
	WDRelation^		tmpWDRelation;				//関連語データ

	String^			tmpGroupName;				//分類名
	array<Byte>^	tmpGroupID;					//分類ID
	array<Byte>^	tmpGroupIDGt;				//分類ID大
	array<Byte>^	tmpGroupIDLt;				//分類ID小
	System::Text::Encoding^ tmpEnc;				//エンコーダ
	array<Char>^	tmpGroupIDStr;				//分類名(出力用)

	String^			tmpPrStr;					
	String^			oldPrStr;
	String^			tmpRdStr;

	Int32			oldPractical = -1;			//活用形
	Int32			oldPlurality = -1;			//単数複数
	Int32			oldGramatical = -1;			//人称
	Int32			oldSex = -1;				//性

	//-- 読込済みデータがあればそれを表示する
	try
	{
		if( inWordGrp->getXMLFname() != nullptr )
		{
				//XMLデータがあれば表示して終了
				webBrowserBook->Url = gcnew Uri( inWordGrp->getXMLFname() );		

				return;
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語データ表示にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31306;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- 新たにXMLファイルを作成する
	try
	{
		//-- 初期設定 --//
		XmlFName = getXMLFname();														//出力XMLファイル名取得

		XmlFStream = gcnew XmlTextWriter( XmlFName, System::Text::Encoding::Unicode );	//出力XMLファイル名セット
		XmlFStream->Formatting = Formatting::Indented;									//インデントあり
		XmlFStream->QuoteChar = L'\"';													//クオータ設定　"
		XmlFStream->WriteStartDocument();												//ドキュメントスタート
		XmlFStream->WriteProcessingInstruction( L"xml-stylesheet",						//XSLT指定
			String::Format( L"type=\"text/xsl\" href=\"{0}\"", WDConfigParm->XSLTFNameB ) );

		//ルート記述
		XmlFStream->WriteStartElement( WORDS_NODE );									

		//-- 基本単語記述 --//
		//１つ目の読み方の基本単語を表示する
		tmpWDWord = inWordGrp->getBaseWord( 0 );
		if( tmpWDWord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語データがありません。" );
			tmpWordDicException->ErrorCode = 31306;
			tmpWordDicException->ErrorCode2 = 2;
			throw tmpWordDicException;
		}
		XmlFStream->WriteStartElement( BASE_NODE );															//ベース
		XmlFStream->WriteElementString( BASE_WORD_ELE, tmpWDWord->getWord( nullptr ) );						//単語
		XmlFStream->WriteElementString( BASE_READ1_ELE, tmpWDWord->getRead1( nullptr ) );					//読み方１
		XmlFStream->WriteElementString( BASE_READ2_ELE, tmpWDWord->getRead2( nullptr ) );					//読み方２
		XmlFStream->WriteEndElement();

		//--基本単語(他の読み方) --//
		//２つ目以降の読み方の基本単語を表示する
		XmlFStream->WriteStartElement( SUBBASEGRP_NODE );
		for( Int32 i = 1; i < inWordGrp->getReadPatternCnt(); i++ )
		{
			tmpWDSubWord = inWordGrp->getBaseWord( i );
			if( tmpWDSubWord == nullptr )
			{
				continue;
			}
			XmlFStream->WriteStartElement( SUBBASE_NODE );															//ベース
			XmlFStream->WriteElementString( SUBBASE_WORD_ELE, tmpWDSubWord->getWord( nullptr ) );						//単語
			XmlFStream->WriteElementString( SUBBASE_READ1_ELE, tmpWDSubWord->getRead1( nullptr ) );					//読み方１
			XmlFStream->WriteElementString( SUBBASE_READ2_ELE, tmpWDSubWord->getRead2( nullptr ) );					//読み方２
			XmlFStream->WriteEndElement();
		}
		XmlFStream->WriteEndElement();

		//-- 意味ブロック記述 --//
		XmlFStream->WriteStartElement( MEANS_NODE );														//意味ブロック
	
		for( Int32 i = 0; i < inWordGrp->getMeanCnt(); i++ )
		{
			XmlFStream->WriteStartElement( MEAN_NODE );														//意味
			//意味取得
			tmpWDMean = inWordGrp->getMean( i );
			if( tmpWDMean == nullptr )
			{
				continue;
			}

			//意味番号
			XmlFStream->WriteAttributeString( MEANNO_ELE, tmpWDMean->getMeanNo().ToString() );

			//-- 翻訳記述 --//
			tmpWDTrans = inWordGrp->getTransNo( tmpWDMean->getMeanNo() );

			if( tmpWDTrans != nullptr )
			{
				//翻訳グループノード
				XmlFStream->WriteStartElement( TRANSES_NODE );									

				for( Int32 j = 0; j < tmpWDTrans->CountTransID(); j++ )
				{
					//翻訳ノード
					XmlFStream->WriteStartElement( TRANS_NODE );								

					XmlFStream->WriteElementString( TRANSID_ELE,								//翻訳ID
						String::Format( L"A.{0}", tmpWDTrans->getTransID( j ).ToString() ) );	
					XmlFStream->WriteElementString( TRANSWORD_ELE,								//翻訳単語
						getTransWordB( tmpWDTrans->getTransID( j ) ) );	
				
					//翻訳ノードクローズ
					XmlFStream->WriteEndElement();												
				}

				//翻訳グループノードクローズ
				XmlFStream->WriteEndElement();													
			}

			//-- 意味記述 --//
			tmpGroupID = gcnew array<Byte>(WDMEAN_GROUPGTLEN + WDMEAN_GROUPLTLEN);
			tmpGroupIDGt = gcnew array<Byte>(WDMEAN_GROUPGTLEN);
			tmpGroupIDLt = gcnew array<Byte>(WDMEAN_GROUPLTLEN);
			tmpEnc = System::Text::Encoding::ASCII;
			tmpGroupIDStr = gcnew array<Char>(WDMEAN_GROUPGTLEN + WDMEAN_GROUPLTLEN);;

			//分類ノード
			XmlFStream->WriteStartElement( GROUP_NODE );

			for( Int32 i = 0; i < tmpWDMean->MeanGroupCount(); i++ )
			{
				tmpGroupIDGt = tmpWDMean->getGroupGt( i, tmpGroupIDGt );
				tmpGroupIDLt = tmpWDMean->getGroupLt( i, tmpGroupIDLt );
				Array::Copy( tmpGroupIDGt, tmpGroupID, 2 );
				Array::Copy( tmpGroupIDLt, 0, tmpGroupID, 2, 2 );
				Int32 dummy = tmpEnc->GetCharCount( tmpGroupID,0,4 );
				tmpGroupIDStr = tmpEnc->GetChars( tmpGroupID);

				WDGroupTreeNode^ tmpWDGroupTreeNode = getGroup( tmpGroupIDGt, tmpGroupIDLt );			//分類 

				if( tmpWDGroupTreeNode != nullptr )
				{
					tmpGroupName = tmpWDGroupTreeNode->getName( nullptr );
				}else{
					tmpGroupName = L"(分類名が不明です)";
				}

				XmlFStream->WriteStartElement( GROUP_ELE );
				XmlFStream->WriteAttributeString( GROUPID_ELE,  
					String::Format( L"BG.{0} ", gcnew String(tmpGroupIDStr) ) );
				XmlFStream->WriteString( tmpGroupName );
				XmlFStream->WriteEndElement();

				delete tmpGroupIDStr;
				tmpGroupIDStr = nullptr;
			}
			XmlFStream->WriteEndElement();

			XmlFStream->WriteElementString( MSPEECH_ELE,										//意味品詞			
				getSegment( SegmentListB, SPEECH_ID, tmpWDMean->getSpeech() )->getName( nullptr ) );
			XmlFStream->WriteElementString( MRANK_ELE,											//ランク
				getSegment( SegmentListB, RANK_ID, tmpWDMean->getRank() )->getName( nullptr ) );
			XmlFStream->WriteElementString( MEAN_ELE, tmpWDMean->getMean( nullptr ) );			//意味
			XmlFStream->WriteElementString( EXAMPLE_ELE, tmpWDMean->getExample( nullptr ) );	//例文

			//-- 関連語記述 --//
			tmpWDRelation = inWordGrp->getRelationNo( tmpWDMean->getMeanNo() );

			if( tmpWDRelation != nullptr )
			{
				//関連語グループノード
				XmlFStream->WriteStartElement( RELATIONS_NODE );								

				for( Int32 j = 0; j < tmpWDRelation->CountRelation(); j++ )
				{
					XmlFStream->WriteStartElement( RELATION_NODE );								//関連語ノード

					XmlFStream->WriteElementString( RELATIONTYPE_ELE,							//関連語タイプ
						getSegment( SegmentListB, RELATION_ID, tmpWDRelation->getRelationType( j ) )->getName( nullptr ) );	
					XmlFStream->WriteElementString( RELATIONID_ELE,								//関連語ID
						String::Format( L"B.{0}", tmpWDRelation->getRelationID( j ).ToString() ) );	
					XmlFStream->WriteElementString( RELATION_ELE,								//関連語単語
						getRelationWordB( tmpWDRelation->getRelationID( j ) ) );	
				
					//翻訳ノードクローズ
					XmlFStream->WriteEndElement();												
				}

				//翻訳グループノードクローズ
				XmlFStream->WriteEndElement();													
			}

			//意味クローズ
			XmlFStream->WriteEndElement();												
		}

		//意味ブロッククローズ
		XmlFStream->WriteEndElement();												

		//-- 活用形記述 --//
		//活用グループセクションノード		
		XmlFStream->WriteStartElement( PRATICALGRPSEC_ELE );								
		//活用グループノード		
		XmlFStream->WriteStartElement( PRATICALGRP_ELE );								

		//先頭単語取得
		tmpWDWord = inWordGrp->getWord( 0 );
		Int32 tmpReadPattern = tmpWDWord->getReadPattern();

		//活用タイプ
		XmlFStream->WriteElementString( PRATICALTYPE_ELE,
			getSegment( SegmentListB, TYPE_ID, tmpWDWord->getType() )->getName( nullptr ) );
		//活用形グループノード
		XmlFStream->WriteStartElement( PRATICALS_NODE );								


		for( Int32 i = 0; i < inWordGrp->getWordCnt(); i ++ )
		{
			tmpWDWord = inWordGrp->getWord( i );
			if( tmpWDWord == nullptr )
			{
				continue;
			}

			if( tmpReadPattern != tmpWDWord->getReadPattern() )
			{
				tmpReadPattern = tmpWDWord->getReadPattern();
				//活用形グループノードクローズ
				XmlFStream->WriteEndElement();
				//活用グループノードクローズ		
				XmlFStream->WriteEndElement();
				//活用グループノード		
				XmlFStream->WriteStartElement( PRATICALGRP_ELE );								
				//活用タイプ
				XmlFStream->WriteElementString( PRATICALTYPE_ELE,										//活用タイプ
					getSegment( SegmentListA, TYPE_ID, tmpWDWord->getType() )->getName( nullptr ) );
				//活用形グループノード
				XmlFStream->WriteStartElement( PRATICALS_NODE );								
			}


			//活用形ノード
			XmlFStream->WriteStartElement( PRATICALITEM_NODE );
			
			//活用形
			if( oldPractical != tmpWDWord->getPractical() )
			{
				oldPractical = tmpWDWord->getPractical();
				oldPlurality = -1;
				oldGramatical = -1;
				oldSex = -1;	
				tmpPrStr = getSegment( SegmentListB, PRATICAL_ID, oldPractical )->getName( nullptr );
			}
			//単数複数
			if( oldPlurality != tmpWDWord->getPlurality() )
			{
				oldPlurality = tmpWDWord->getPlurality();
				oldGramatical = -1;
				oldSex = -1;	
				if( tmpPrStr == nullptr || 
					tmpPrStr->Length == 0 )
				{
					if( tmpPrStr != nullptr ) delete tmpPrStr;
					tmpPrStr = getSegment( SegmentListB, PLURALITY_ID, oldPlurality )->getName( nullptr );
				}else{
					tmpRdStr = getSegment( SegmentListB, PLURALITY_ID, oldPlurality )->getName( nullptr );
					if( tmpRdStr->Length > 0 )
					{
						oldPrStr = tmpPrStr;
						tmpPrStr = String::Format( L"{0}・{1}", oldPrStr, tmpRdStr );
						delete oldPrStr;
					}
					delete tmpRdStr;
				}

			}
			//人称
			if( oldGramatical != tmpWDWord->getGramatical() )
			{
				oldGramatical = tmpWDWord->getGramatical();
				oldSex = -1;	
				if( tmpPrStr == nullptr || 
					tmpPrStr->Length == 0 )
				{
					if( tmpPrStr != nullptr ) delete tmpPrStr;
					tmpPrStr = getSegment( SegmentListB, GRAMATICAL_ID, oldGramatical )->getName( nullptr );
				}else{
					tmpRdStr = getSegment( SegmentListB, GRAMATICAL_ID, oldGramatical )->getName( nullptr );
					if( tmpRdStr->Length > 0 )
					{
						oldPrStr = tmpPrStr;
						tmpPrStr = String::Format( L"{0}・{1}", oldPrStr, tmpRdStr );
						delete oldPrStr;
					}
					delete tmpRdStr;
				}

			}
			//性
			if( oldSex != tmpWDWord->getSex() )
			{
				oldSex = tmpWDWord->getSex();
				if( tmpPrStr == nullptr || 
					tmpPrStr->Length == 0 )
				{
					if( tmpPrStr != nullptr ) delete tmpPrStr;
					tmpPrStr = getSegment( SegmentListB, SEX_ID, oldSex )->getName( nullptr );
				}else{
					tmpRdStr = getSegment( SegmentListB, SEX_ID, oldSex )->getName( nullptr );
					if( tmpRdStr->Length > 0 )
					{
						oldPrStr = tmpPrStr;
						tmpPrStr = String::Format( L"{0}・{1}", oldPrStr, tmpRdStr );
						delete oldPrStr;
					}
					delete tmpRdStr;
				}

			}
			//活用形
			XmlFStream->WriteStartElement( PRATICALTITLE_ELE );
			XmlFStream->WriteAttributeString( PRATICALTYPEID_ELE,									//活用方法ID
									tmpWDWord->getType().ToString() );
			XmlFStream->WriteAttributeString( PRATICALID_ELE,										//活用形ID					
									tmpWDWord->getPractical().ToString() );
			XmlFStream->WriteString( tmpPrStr );
			XmlFStream->WriteEndElement();
			delete tmpPrStr;
			tmpPrStr = nullptr;

			XmlFStream->WriteElementString( PRATICALWORD_ELE, tmpWDWord->getWord( nullptr ) );		//単語
			XmlFStream->WriteElementString( PRATICALREAD1_ELE, tmpWDWord->getRead1( nullptr ) );	//読み方１
			XmlFStream->WriteElementString( PRATICALREAD2_ELE, tmpWDWord->getRead2( nullptr ) );	//読み方２

			//活用形クローズ
			XmlFStream->WriteEndElement();													
		}

		//活用形グループクローズ
		XmlFStream->WriteEndElement();													
		//活用グループクローズ
		XmlFStream->WriteEndElement();
		//活用グループセクションクローズ
		XmlFStream->WriteEndElement();
		
		//-- 終了処理 --//
		//ルートクローズ
		XmlFStream->WriteEndElement();													
		XmlFStream->Flush();
		XmlFStream->Close();

		//単語グループを読込済みリストに追加
		inWordGrp->setXMLFname( XmlFName );
		ReadedWordList->Add( inWordGrp );
		webBrowserBook->Url = gcnew Uri( inWordGrp->getXMLFname() );		

	}catch( Exception^ exp )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"表示データ作成時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31306;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;

	}finally{
		if( XmlFName != nullptr ) delete XmlFName;
		if( XmlFStream != nullptr ) delete XmlFStream;
		if( tmpGroupName != nullptr ) delete tmpGroupName;
		if( tmpGroupID != nullptr ) delete tmpGroupID;
		if( tmpGroupIDGt != nullptr ) delete tmpGroupIDGt;
		if( tmpGroupIDLt != nullptr ) delete tmpGroupIDLt;
		if( tmpEnc != nullptr ) delete tmpEnc;
		if( tmpGroupIDStr != nullptr ) delete tmpGroupIDStr;
	}

}

//***** 言語A→言語Bの翻訳語を検索
String^ WordDic::Form1::getTransWordA( Int32 inWordID )
{
	array<Byte>^	tmpWordID;
	DataRecord^		tmpRecord;
	DataRecord^		tmpOldRecord;
	WDWord^			tmpWord;
	String^ rtString;

	if( inWordID <= 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"翻訳IDが不正です。" );
		tmpWordDicException->ErrorCode = 31307;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- XML表示済みのリストから翻訳語を探す --//
	try
	{
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getWordID() == inWordID && 
				tmpWDWordGrp->getSchLang() == 2 )
			{
				tmpWord = tmpWDWordGrp->getBaseWord();

				if( tmpWord == nullptr )
				{
					tmpWord = tmpWDWordGrp->getWord( 0 );
				}
				
				return tmpWord->getWord( nullptr );
			}

		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"翻訳語検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31307;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- 新たに翻訳語を探す --//
	try
	{

		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordID, nullptr, 0 );
		tmpRecord = WordFileB->ReadRecord( tmpWordID, 2);
		while( true )
		{
			if( tmpRecord == nullptr )
			{
				rtString =  L"(翻訳語が不明です。)";
				break;
			}
		
			tmpWord = gcnew WDWord( tmpRecord );
			if( tmpWord->getBaseFlg() == true )
			{
				break;
			}
			if( tmpRecord->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpRecord->getEachKeyFlg() == IS_EACHKEYLST )
			{
				break;
			}
			tmpOldRecord = tmpRecord;
			tmpRecord = WordFileB->NextRecord( tmpOldRecord );
			delete tmpOldRecord;
			delete tmpWord;
		}

		rtString = tmpWord->getWord( nullptr );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"翻訳語検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31307;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
		if( tmpWord != nullptr ) delete tmpWord;
		if( tmpRecord != nullptr ) delete tmpRecord;
	}

	return rtString;

}
//***** 言語B→言語Aの翻訳語を検索
String^ WordDic::Form1::getTransWordB( Int32 inWordID )
{
	array<Byte>^	tmpWordID;
	DataRecord^		tmpRecord;
	DataRecord^		tmpOldRecord;
	WDWord^			tmpWord;
	String^ rtString;

	if( inWordID <= 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"翻訳IDが不正です。" );
		tmpWordDicException->ErrorCode = 31308;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- XML表示済みのリストから翻訳語を探す --//
	try
	{
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getWordID() == inWordID && 
				tmpWDWordGrp->getSchLang() == 1 )
			{
				tmpWord = tmpWDWordGrp->getBaseWord();

				if( tmpWord == nullptr )
				{
					tmpWord = tmpWDWordGrp->getWord( 0 );
				}
				
				return tmpWord->getWord( nullptr );
			}

		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"翻訳語検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31308;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- 新たに翻訳語を探す --//
	try
	{
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordID, nullptr, 0 );
		tmpRecord = WordFileA->ReadRecord( tmpWordID, 2);
		while( true )
		{
			if( tmpRecord == nullptr )
			{
				rtString =  L"(翻訳語が不明です。)";
				break;
			}
		
			tmpWord = gcnew WDWord( tmpRecord );
			if( tmpWord->getBaseFlg() == true )
			{
				break;
			}
			if( tmpRecord->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpRecord->getEachKeyFlg() == IS_EACHKEYLST )
			{
				break;
			}
			tmpOldRecord = tmpRecord;
			tmpRecord = WordFileA->NextRecord( tmpOldRecord );
			delete tmpOldRecord;
			delete tmpWord;
		}

		rtString = tmpWord->getWord( nullptr );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"翻訳語検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31308;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
		if( tmpWord != nullptr ) delete tmpWord;
		if( tmpRecord != nullptr ) delete tmpRecord;
	}

	return rtString;

}

//***** 言語Aの関連語検索
String^ WordDic::Form1::getRelationWordA( Int32 inWordID )
{
	array<Byte>^	tmpWordID;
	DataRecord^		tmpRecord;
	DataRecord^		tmpOldRecord;
	WDWord^			tmpWord;
	String^ rtString;

	if( inWordID <= 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"関連語IDが不正です。" );
		tmpWordDicException->ErrorCode = 31309;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- XML表示済みのリストから関連語を探す --//
	try
	{
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getWordID() == inWordID && 
				tmpWDWordGrp->getSchLang() == 1 )
			{
				tmpWord = tmpWDWordGrp->getBaseWord();

				if( tmpWord == nullptr )
				{
					tmpWord = tmpWDWordGrp->getWord( 0 );
				}
				
				return tmpWord->getWord( nullptr );
			}

		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"関連語検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31309;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- 検索単語リストから関連語を探す --//
	try
	{
		for( Int32 i = 0; i < listBoxWordList->Items->Count; i++ )
		{
			WDWordGrp^ tmpWDWordGrp = safe_cast<WDWordGrp^>( listBoxWordList->Items[i]);
			if( tmpWDWordGrp->getWordID() == inWordID &&
				tmpWDWordGrp->getSchLang() == 1 )
			{
				tmpWord = tmpWDWordGrp->getBaseWord();

				if( tmpWord == nullptr )
				{
					tmpWord = tmpWDWordGrp->getWord( 0 );
				}
				
				return tmpWord->getWord( nullptr );
			}
		}
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"関連語検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31309;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}

	//-- 新たに単語を読込む --//
	try
	{
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordID, nullptr, 0 );
		tmpRecord = WordFileA->ReadRecord( tmpWordID, 2);
		while( true )
		{
			if( tmpRecord == nullptr )
			{
				return L"(関連語が不明です。)";
				break;
			}
		
			tmpWord = gcnew WDWord( tmpRecord );
			if( tmpWord->getBaseFlg() == true )
			{
				break;
			}
			if( tmpRecord->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpRecord->getEachKeyFlg() == IS_EACHKEYLST )
			{
				break;
			}
			tmpOldRecord = tmpRecord;
			tmpRecord = WordFileA->NextRecord( tmpOldRecord );
			delete tmpOldRecord;
			delete tmpWord;
		}

		rtString = tmpWord->getWord( nullptr );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L" 関連語検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31309;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;

	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
		if( tmpWord != nullptr ) delete tmpWord;
		if( tmpRecord != nullptr ) delete tmpRecord;
	}

	return rtString;

}
//***** 言語Bの関連語検索
String^ WordDic::Form1::getRelationWordB( Int32 inWordID )
{
	array<Byte>^	tmpWordID;
	DataRecord^		tmpRecord;
	DataRecord^		tmpOldRecord;
	WDWord^			tmpWord;
	String^			rtString;

	if( inWordID <= 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"関連語IDが不正です。" );
		tmpWordDicException->ErrorCode = 31310;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- XML表示済みのリストから関連語を探す --//
	try
	{
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getWordID() == inWordID && 
				tmpWDWordGrp->getSchLang() == 2 )
			{
				tmpWord = tmpWDWordGrp->getBaseWord();

				if( tmpWord == nullptr )
				{
					tmpWord = tmpWDWordGrp->getWord( 0 );
				}
				
				return tmpWord->getWord( nullptr );
			}

		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"関連語検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31310;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- 検索単語リストから関連語を探す --//
	try
	{
		for( Int32 i = 0; i < listBoxWordList->Items->Count; i++ )
		{
			WDWordGrp^ tmpWDWordGrp = safe_cast<WDWordGrp^>( listBoxWordList->Items[i]);
			if( tmpWDWordGrp->getWordID() == inWordID &&
				tmpWDWordGrp->getSchLang() == 2 )
			{
				tmpWord = tmpWDWordGrp->getBaseWord();

				if( tmpWord == nullptr )
				{
					tmpWord = tmpWDWordGrp->getWord( 0 );
				}
				
				return tmpWord->getWord( nullptr );
			}
		}
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"関連語検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31310;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}

	//-- 新たに関連語を探す --//
	try
	{
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordID, nullptr, 0 );
		tmpRecord = WordFileB->ReadRecord( tmpWordID, 2);
		while( true )
		{
			if( tmpRecord == nullptr )
			{
				rtString =  L"(関連語が不明です。)";
				break;
			}
		
			tmpWord = gcnew WDWord( tmpRecord );
			if( tmpWord->getBaseFlg() == true )
			{
				break;
			}
			if( tmpRecord->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpRecord->getEachKeyFlg() == IS_EACHKEYLST )
			{
				break;
			}
			tmpOldRecord = tmpRecord;
			tmpRecord = WordFileB->NextRecord( tmpOldRecord );
			delete tmpOldRecord;
			delete tmpWord;
		}

		rtString = tmpWord->getWord( nullptr );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L" 関連語検索時にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31310;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;

	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
		if( tmpWord != nullptr ) delete tmpWord;
		if( tmpRecord != nullptr ) delete tmpRecord;
	}

	return rtString;
}
