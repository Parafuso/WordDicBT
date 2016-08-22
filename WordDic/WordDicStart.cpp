//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアーアプリケーション　ソース
//	Version 1.0			Create date 2006/05/08
//	Version 1.0.3.0		Change date 2010/11/16

//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	Windows Formのアプリケーション
//------------------------------------------------------------------------------
// WordDicStart.cpp : 初期処理を記述したファイルです。
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
// コンストラクタ
//------------------------------------------------------------------------------
WordDic::Form1::Form1(void)
{
	InitializeComponent();
	try
	{
		CreateDatas();										//データ作成
		InitializeForms();									//フォームの初期化
		ReadConfig();										//コンフィグセットアップ
		LoadGroupFile();									//分類TreeView作成
		LoadSegmentFile();									//区分ファイル読込
		OpenDicFile();										//辞書ファイルオープン

	}catch( Exception^ exp ){
		ExceptionWrite( exp );
	}
}
//------------------------------------------------------------------------------
// 初期処理
//------------------------------------------------------------------------------
//***** データ作成
void WordDic::Form1::CreateDatas( void )
{
	//-- リスト作成 --//
	//辞書表示済みの単語リスト
	ReadedWordList = gcnew List<WDWordGrp^>();

	//検索単語リストソート用関数
	WordSchListComparer = gcnew WDWordSchListComparer();


	//-- 単語表示データ格納フォルダ作成 --//
	DispXMLForder = String::Format( L"{0}\\{1}", 
		System::Environment::GetEnvironmentVariable("TEMP"), XMLFOLDERNAME );
//	DispXMLForder = String::Format( L"{0}\\{1}", 
//				Path::GetDirectoryName( Application::UserAppDataPath  ), XMLFOLDERNAME );
	
	//-- 単語表示データ格納フォルダが存在していなければ、作成する --//
    if (  !Directory::Exists( DispXMLForder ) )
	{
		Directory::CreateDirectory( DispXMLForder );
	//-- 単語表示データ格納フォルダが存在していれば中身を空にする --//
	}else{
		DeleteXmlFiles();
	}

}


//***** フォームの初期化
void WordDic::Form1::InitializeForms( void )
{
	System::OperatingSystem^	tmpOSInf;				//OS情報
	System::Version^		tmpOSVer;				//OSバージョン

	System::Drawing::Icon^	IconSchLangA;			//言語Ａ用アイコン
	System::Drawing::Icon^	IconSchLangB;			//言語Ｂ用アイコン
	String^					IconFName;				//アイコンファイル名

	//-- OSのチェック(Windows 7以前なら何もしない)--//

	tmpOSInf = System::Environment::OSVersion;
	tmpOSVer = tmpOSInf->Version;

	if( (tmpOSVer->Major == 6 && tmpOSVer->Minor == 0) ||
		 tmpOSVer->Major < 6 )
	{
		return;
	}

	//-- 言語Ａボタンの定義 --//
	IconFName = getFilePathName( L"img\\ja_jp.ico" );
	IconSchLangA = gcnew System::Drawing::Icon( IconFName, System::Drawing::Size(16,16 ) );
	ThumbButtonSchLangA = gcnew ThumbnailToolBarButton( IconSchLangA, L"クリップボードの単語で日本語検索" );
	//言語Ａボタンのイベント定義
	ThumbButtonSchLangA->Click += gcnew  System::EventHandler<ThumbnailButtonClickedEventArgs^>( this, &Form1::ThumbButtonSchLangA_Click );


	//-- 言語Ｂボタンの定義 --//
	IconFName = getFilePathName( L"img\\pt_br.ico" );
	IconSchLangB = gcnew System::Drawing::Icon( IconFName, System::Drawing::Size(16,16 ) );
	ThumbButtonSchLangB = gcnew ThumbnailToolBarButton( IconSchLangB, L"クリップボードの単語でポルトガル語検索" );
	//言語Ｂボタンのイベント定義
	ThumbButtonSchLangB->Click += gcnew System::EventHandler<ThumbnailButtonClickedEventArgs^>( this, &Form1::ThumbButtonSchLangB_Click );


	//ボタンをタスクバーにセット
	ThumbnailToolBarManagerWD = Microsoft::WindowsAPICodePack::Taskbar::TaskbarManager::Instance->ThumbnailToolBars;
		ThumbnailToolBarManagerWD->AddButtons(this->Handle ,ThumbButtonSchLangA,ThumbButtonSchLangB);

}

//***** コンフィグセットアップ
void WordDic::Form1::ReadConfig( void )
{
	WDConfigParm = gcnew WordDicCfg();

	WDConfigParm->Read1IdxA = 3;
	WDConfigParm->Read2IdxA = 4;

	WDConfigParm->Read1IdxB = 0;
	WDConfigParm->Read2IdxB = 3;

	//ソート順
	WDConfigParm->WordListSortA1 = 2;				//ひらがな
	WDConfigParm->WordListSortA2 = 1;				//単語

	//表示
	WDConfigParm->WordListDispA =  1;				//単語
	WDConfigParm->WordListSubDispA =  2;			//ひらがな

	//ソート順
	WDConfigParm->WordListSortB1 = 1;				//アルファベット
	WDConfigParm->WordListSortB2 = 3;				//カタカナ

	//表示
	WDConfigParm->WordListDispB =  1;				//アルファベット
	WDConfigParm->WordListSubDispB =  0;				//なし

	WDConfigParm->GroupFName = getFilePathName( L"Dic\\GroupJa-jp.fis" );
	WDConfigParm->SegmentFNameA = getFilePathName( L"Dic\\SegmentJa-jp_Ja-jp.fis" );
	WDConfigParm->SegmentFNameB = getFilePathName( L"Dic\\SegmentPt-br_Ja-jp.fis" );

	//単語ファイル名 言語A
	WDConfigParm->WordFNameA = getFilePathName( L"Dic\\WordJa-jp.fis" );
	//意味ファイル名 言語A
	WDConfigParm->MeanFNameA = getFilePathName( L"Dic\\MeanJa-jp_Ja-jp.fis" );										
	//翻訳ファイル名 言語A
	WDConfigParm->TransFNameA = getFilePathName( L"Dic\\TransJa-jp_Pt-br.fis" );										
	//関連語ファイル名 言語A
	WDConfigParm->RelationFNameA = getFilePathName( L"Dic\\RelationJa-jp.fis" );;									

	//単語ファイル名 言語B
	WDConfigParm->WordFNameB = getFilePathName( L"Dic\\WordPt-br.fis" );										
	//意味ファイル名 言語B
	WDConfigParm->MeanFNameB = getFilePathName( L"Dic\\MeanPt-br_Ja-jp.fis" );										
	//翻訳ファイル名 言語B
	WDConfigParm->TransFNameB = getFilePathName( L"Dic\\TransPt-br_Ja-jp.fis" );
	//関連語ファイル名 言語B
	WDConfigParm->RelationFNameB = getFilePathName( L"Dic\\RelationPt-br.fis" );			

	//XSLTファイル名 言語A
	WDConfigParm->XSLTFNameA =  getFilePathName( L"Japonese1.xslt" );
	//XSLTファイル名 言語B
	WDConfigParm->XSLTFNameB =  getFilePathName( L"Portugues1.xslt" );

	//単語が見つからない時
	WDConfigParm->WordSchZero = L"単語が見つかりません";
	//WDConfigParm見つかった時
	WDConfigParm->WordSchAny = L"{0} 件ありました";


}


//***** 分類TreeView作成
void WordDic::Form1::LoadGroupFile( void )
{
	FIsam^ GroupFile;

	DataRecord^ tmpRecord;
	WDGroup^ tmpGroup;
	WDGroupTreeNode^ tmpTreeNode;
	array<Byte>^ tmpGroupLt;

	Int32 tmpItemCnt;

	TreeNode^ BaseNode;

	//-- ファイルオープン --//
	try
	{
		GroupFile = gcnew FIsam( WDConfigParm->GroupFName, 4096, IsamOpenMode::READ_ONLY );
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類ファイルのオープンに失敗しました。", exp );
		tmpWordDicException->ErrorCode = 31001;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- 分類ファイル読込 --//
	try
	{
		//-- ベースノード作成 --//
		tmpRecord = GroupFile->FirstRecord(1);
		if ( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類データがありません。");
			tmpWordDicException->ErrorCode = 31001;
			tmpWordDicException->ErrorCode2 = 2;
		}
		tmpGroup = gcnew WDGroup( tmpRecord );
		BaseNode = gcnew WDGroupTreeNode( tmpGroup );
		treeViewGroupTree->Nodes->Add( BaseNode );

		//-- 1つ目の分類ノード作成 --//
		tmpRecord = GroupFile->NextRecord( tmpRecord );
		if ( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類データの1つ目の情報がありません。" );
			tmpWordDicException->ErrorCode = 31001;
			tmpWordDicException->ErrorCode2 = 3;
		}
		tmpGroup = gcnew WDGroup( tmpRecord );
		tmpTreeNode = gcnew WDGroupTreeNode( tmpGroup );
		BaseNode->Nodes->Add( tmpTreeNode );
		
		WDGroupTreeNode^ tmpParentNode = tmpTreeNode;		
		
		while( true )
		{
			tmpItemCnt++;
			tmpRecord = GroupFile->NextRecord( tmpRecord );
			delete tmpGroup;
			if( tmpRecord == nullptr )
			{
				break;
			}
			tmpGroup = gcnew WDGroup( tmpRecord );
			tmpTreeNode  = gcnew WDGroupTreeNode( tmpGroup );
			tmpGroupLt = tmpTreeNode->getGroupLt( nullptr );
			// 分類小が '00'なら　レベル１（分類の元グループ)にする
			if( tmpGroupLt[0] == '0' && tmpGroupLt[1] == '0' )
			{
				BaseNode->Nodes->Add( tmpTreeNode );
				tmpParentNode = tmpTreeNode;
			}else{
				tmpParentNode->Nodes->Add( tmpTreeNode );
			}
		}
		
		//-- 完了処理 --//
		BaseNode->Expand();					//BaseNodeを展開する

		GroupFile->Close();					//Isamクローズ
		delete GroupFile;

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類TreeView作成に失敗しました。", exp );
		tmpWordDicException->ErrorCode = 31001;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;
	}
}

//***** 区分ファイルロード
void WordDic::Form1::LoadSegmentFile( void )
{
	FIsam^		SegmentFile;			//区分ファイル
	DataRecord^	tmpRecord;				//作業レコード
	WDSegment^	tmpSegment;				//区分データ


	//-- リスト作成 --//
	SegmentListA = gcnew List<WDSegment^>();
	SegmentListB = gcnew List<WDSegment^>();

	//--区分ファイルA読込--//
	//ファイルオープン
	try
	{
		SegmentFile = gcnew FIsam( WDConfigParm->SegmentFNameA, 4096, IsamOpenMode::READ_ONLY );
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"区分ファイルA({0})のオープンに失敗しました。", WDConfigParm->SegmentFNameA ), exp );
		tmpWordDicException->ErrorCode = 31002;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	try
	{
		//1件目読込
		tmpRecord = SegmentFile->FirstRecord(1);
		if ( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"区分データA({0})がありません。",WDConfigParm->SegmentFNameA ) );
			tmpWordDicException->ErrorCode = 31002;
			tmpWordDicException->ErrorCode2 = 2;
		}
		tmpSegment = gcnew WDSegment( tmpRecord );
		SegmentListA->Add( tmpSegment );

		//2件目以降
		while( true )
		{
			tmpRecord = SegmentFile->NextRecord( tmpRecord );
			if( tmpRecord == nullptr )
			{
				break;
			}

			tmpSegment = gcnew WDSegment( tmpRecord );
			SegmentListA->Add( tmpSegment );
		}
		SegmentFile->Close();
		delete SegmentFile;

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"区分リストAの作成に失敗しました。", exp );
		tmpWordDicException->ErrorCode = 31002;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}

	//--区分ファイルA読込--//
	//ファイルオープン
	try
	{
		SegmentFile = gcnew FIsam( WDConfigParm->SegmentFNameB, 4096, IsamOpenMode::READ_ONLY );
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"区分ファイルB({0})のオープンに失敗しました。", WDConfigParm->SegmentFNameB ), exp );
		tmpWordDicException->ErrorCode = 31002;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;
	}

	try
	{
		//1件目読込
		tmpRecord = SegmentFile->FirstRecord(1);
		if ( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"区分データB({0})がありません。",WDConfigParm->SegmentFNameB ) );
			tmpWordDicException->ErrorCode = 31002;
			tmpWordDicException->ErrorCode2 = 2;
		}
		tmpSegment = gcnew WDSegment( tmpRecord );
		SegmentListB->Add( tmpSegment );

		//2件目以降
		while( true )
		{
			tmpRecord = SegmentFile->NextRecord( tmpRecord );
			if( tmpRecord == nullptr )
			{
				break;
			}

			tmpSegment = gcnew WDSegment( tmpRecord );
			SegmentListB->Add( tmpSegment );
		}
		SegmentFile->Close();
		delete SegmentFile;

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"区分リストBの作成に失敗しました。", exp );
		tmpWordDicException->ErrorCode = 31002;
		tmpWordDicException->ErrorCode2 = 6;
		throw tmpWordDicException;
	}

}

//***** 辞書ファイルオープン
void WordDic::Form1::OpenDicFile( void )
{

	//-- 言語A関連ファイルオープン --//
	//単語Aファイル
	try
	{
		WordFileA = gcnew FIsam( WDConfigParm->WordFNameA, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"単語ファイルA({0})のオープンに失敗しました。", WDConfigParm->WordFNameA ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}
	//意味Aファイル
	try
	{
		MeanFileA = gcnew FIsam( WDConfigParm->MeanFNameA, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"意味ファイルA({0})のオープンに失敗しました。", WDConfigParm->MeanFNameA ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}
	//翻訳Aファイル
	try
	{
		TransFileA = gcnew FIsam( WDConfigParm->TransFNameA, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"翻訳ファイルA({0})のオープンに失敗しました。", WDConfigParm->TransFNameA ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}
	//関連語Aファイル
	try
	{
		RelationFileA = gcnew FIsam( WDConfigParm->RelationFNameA, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"関連語ファイルA({0})のオープンに失敗しました。", WDConfigParm->RelationFNameA ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;
	}

	//-- 言語B関連ファイルオープン
	//単語Bファイル
	try
	{
		WordFileB = gcnew FIsam( WDConfigParm->WordFNameB, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"単語ファイルB({0})のオープンに失敗しました。", WDConfigParm->WordFNameB ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 5;
		throw tmpWordDicException;
	}
	//意味Bファイル
	try
	{
		MeanFileB = gcnew FIsam( WDConfigParm->MeanFNameB, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"意味ファイルB({0})のオープンに失敗しました。", WDConfigParm->MeanFNameB ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 6;
		throw tmpWordDicException;
	}
	//翻訳Bファイル
	try
	{
		TransFileB = gcnew FIsam( WDConfigParm->TransFNameB, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"翻訳ファイルB({0})のオープンに失敗しました。", WDConfigParm->TransFNameB ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 7;
		throw tmpWordDicException;
	}
	//関連語Aファイル
	try
	{
		RelationFileB = gcnew FIsam( WDConfigParm->RelationFNameB, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"関連語ファイルB({0})のオープンに失敗しました。", WDConfigParm->RelationFNameB ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 8;
		throw tmpWordDicException;
	}
	

	//-- 設定ダイアログ
	dlgWDConfig = gcnew WDConfig();

	//-- バージョンダイアログ
	dlgWDVerDialog = gcnew WDVerDialog();

}
