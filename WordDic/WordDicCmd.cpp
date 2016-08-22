//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアーアプリケーション　ソース
//	Version 1.0.0.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	Windows Formのアプリケーション
//------------------------------------------------------------------------------
// WordDicCmd.cpp : 汎用コマンドを記述します。
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
using namespace WordDic;

//***** 区分取得
WDSegment^	WordDic::Form1::getSegment( List<WDSegment^>^ inSegmentLst,
								Int32 inID, Int32 inNum )
{

	//-- 引数チェック --//
	if( inSegmentLst == nullptr )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"セグメントリストが未指定です。" );
		tmpWordDicException->ErrorCode = 31201;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}
	if( inID < 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"区分IDの指定が間違えています。" );
		tmpWordDicException->ErrorCode = 31201;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	if( inNum < 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"区分番号の指定が間違えています。" );
		tmpWordDicException->ErrorCode = 31201;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}

	for each( WDSegment^ tmpSeg in inSegmentLst )
	{
		if( tmpSeg == nullptr )
		{
			continue;
		}

		if( tmpSeg->getSegmentID() == inID &&
			tmpSeg->getSegmentNo() == inNum )
		{
			return tmpSeg;
		}
	}

	//該当無し
	return nullptr;
}

//***** 分類取得
WDGroupTreeNode^ WordDic::Form1::getGroup( array<Byte>^ inGroupGt, array<Byte>^ inGroupLt )
{
	array<Byte>^ tmpGroupGt;
	array<Byte>^ tmpGroupLt;
	TreeNodeCollection^ tmpNodes;
    System::Collections::IEnumerator^ schNodes;

	//-- 引数チェック --//
	if( inGroupGt == nullptr ||
		inGroupGt->Length < WDMEAN_GROUPGTLEN )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類大IDが未指定です。" );
		tmpWordDicException->ErrorCode = 31202;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}
	if( inGroupLt == nullptr ||
		inGroupLt->Length < WDMEAN_GROUPLTLEN )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類小IDが未指定です。" );
		tmpWordDicException->ErrorCode = 31202;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	try
	{

		tmpNodes = treeViewGroupTree->Nodes;
		schNodes = (safe_cast<System::Collections::IEnumerable^>(tmpNodes))->GetEnumerator();
		while( schNodes->MoveNext() )
		{
			//現在のノードの比較
			WDGroupTreeNode^ tmpWDGroupTreeNode = safe_cast<WDGroupTreeNode^>(schNodes->Current);
			tmpGroupGt = tmpWDGroupTreeNode->getGroupGt( nullptr );
			tmpGroupLt = tmpWDGroupTreeNode->getGroupLt( nullptr );
			if( inGroupGt[0] == tmpGroupGt[0] && inGroupGt[1] == tmpGroupGt[1] &&
				inGroupLt[0] == tmpGroupLt[0] && inGroupLt[1] == tmpGroupLt[1] )
			{
				return tmpWDGroupTreeNode;
			}
			//小ノードの検索
			WDGroupTreeNode^ chldWDGroupTreeNode = getGroupChld( 
						tmpWDGroupTreeNode, inGroupGt, inGroupLt );
			if( chldWDGroupTreeNode != nullptr )
			{
				return chldWDGroupTreeNode;
			}

		}	 
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類検索中にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31202;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		IDisposable^ tmpDisposable = dynamic_cast<System::IDisposable^>(schNodes);
		if ( tmpDisposable != nullptr )
		{
			delete tmpDisposable;
		}
	}

	return nullptr;
}

//***** 分類取得(小ノード検索)
WDGroupTreeNode^ WordDic::Form1::getGroupChld( WDGroupTreeNode^ inTreeNode, 
							array<Byte>^ inGroupGt, array<Byte>^ inGroupLt )
{
	array<Byte>^ tmpGroupGt;
	array<Byte>^ tmpGroupLt;
    System::Collections::IEnumerator^ schNodes;

	//-- 引数チェック --//
	if( inGroupGt == nullptr ||
		inGroupGt->Length < WDMEAN_GROUPGTLEN )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類大IDが未指定です。" );
		tmpWordDicException->ErrorCode = 31203;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}
	if( inGroupLt == nullptr ||
		inGroupLt->Length < WDMEAN_GROUPLTLEN )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類小IDが未指定です。" );
		tmpWordDicException->ErrorCode = 31203;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}
	if( inTreeNode == nullptr )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"検索ノードが未指定です。" );
		tmpWordDicException->ErrorCode = 31203;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}

	try
	{

		schNodes = (safe_cast<System::Collections::IEnumerable^>(inTreeNode->Nodes))->GetEnumerator();
		while( schNodes->MoveNext() )
		{
			//現在のノードの比較
			WDGroupTreeNode^ tmpWDGroupTreeNode = safe_cast<WDGroupTreeNode^>(schNodes->Current);
			tmpGroupGt = tmpWDGroupTreeNode->getGroupGt( nullptr );
			tmpGroupLt = tmpWDGroupTreeNode->getGroupLt( nullptr );
			if( inGroupGt[0] == tmpGroupGt[0] && inGroupGt[1] == tmpGroupGt[1] &&
				inGroupLt[0] == tmpGroupLt[0] && inGroupLt[1] == tmpGroupLt[1] )
			{
				return tmpWDGroupTreeNode;
			}
			//小ノードの検索
			WDGroupTreeNode^ chldWDGroupTreeNode = getGroupChld( 
						tmpWDGroupTreeNode, inGroupGt, inGroupLt );
			if( chldWDGroupTreeNode != nullptr )
			{
				return chldWDGroupTreeNode;
			}

		}	 
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"分類検索中にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31203;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;

	}finally{
		IDisposable^ tmpDisposable = dynamic_cast<System::IDisposable^>(schNodes);
		if ( tmpDisposable != nullptr )
		{
			delete tmpDisposable;
		}
	}

	return nullptr;
}

//***** XMLファイル名作成
String^ WordDic::Form1::getXMLFname( void )
{
	DateTime tmpDate;
	Int32	tmpDateNum;
	String^ rtString;

	//-- 初期処理 --//

	//単語表示データ格納フォルダが未指定なら例外エラー
	if( DispXMLForder == nullptr || 
		DispXMLForder->Length == 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語表示データ格納フォルダが定義されていません。", nullptr );
		tmpWordDicException->ErrorCode = 31204;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	try
	{

		//-- ファイル名を取得 --//
		while( true )
		{
			tmpDate = DateTime::Now;
			tmpDateNum = (tmpDate.Year + tmpDate.Month + tmpDate.Day ) * 1000 +
					tmpDate.Hour + tmpDate.Minute + tmpDate.Second + tmpDate.Millisecond;
			rtString = String::Format( L"{0}WD{1:d08}.xml", DispXMLForder, tmpDateNum.ToString() );
			if( !File::Exists( rtString ) )
			{
				return rtString;
			}
		}
	
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"単語表示ファイル名生成中にエラーが発生しました。", exp );
		tmpWordDicException->ErrorCode = 31204;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;

	}
}


//***** 例外情報出力
void WordDic::Form1::ExceptionWrite( Exception^ exp )
{
	String^ tmpExpName;
	StreamWriter^ standardOutput;

	if( File::Exists( getFilePathName( L"debug.txt" ) ) )
	{
		standardOutput = File::AppendText( getFilePathName( L"debug.txt" ) );
	}else{
		standardOutput = File::CreateText( getFilePathName( L"debug.txt" ) );
	}
	standardOutput->AutoFlush = true;
	Console::SetOut( standardOutput );
	

	tmpExpName = exp->GetType()->Name;
	if( String::Compare( tmpExpName, gcnew String( L"FJIsamException" ) ) == 0 )
	{
		FJIsamException^ tmpExp = (FJIsamException^)exp;
		Console::WriteLine( 
				String::Format( L"{0} : {1}-{2} : {3} \n",  tmpExp->GetType()->Name, 
				tmpExp->ErrorCode, tmpExp->ErrorCode2, tmpExp->Message ) );
	}else if( String::Compare( tmpExpName, gcnew String( L"WDDatasException" ) ) == 0){
		WDDatasException^ tmpExp = (WDDatasException^)exp;
		Console::WriteLine( 
				String::Format( L"{0} : {1}-{2} : {3} \n",  tmpExp->GetType()->Name, 
				tmpExp->ErrorCode, tmpExp->ErrorCode2, tmpExp->Message ) );
	}else if( String::Compare( tmpExpName, gcnew String( L"WordDicException" ) ) == 0){
		WordDicException^ tmpExp = (WordDicException^)exp;
		Console::WriteLine( 
				String::Format( L"{0} : {1}-{2} : {3} \n",  tmpExp->GetType()->Name, 
				tmpExp->ErrorCode, tmpExp->ErrorCode2, tmpExp->Message ) );
	}else{
		Console::WriteLine( 
			String::Format( L"{0} : {1} \n", exp->Message, exp->GetType()->Name ) );
	}
	Console::WriteLine( exp->StackTrace );

	//以下、最初の例外発生地点までループ
	while( exp->InnerException != nullptr )
	{
		exp = exp->InnerException;
		tmpExpName = exp->GetType()->Name;
		if( String::Compare( exp->GetType()->Name, gcnew String( L"FJIsamException" ) ) == 0)
		{
			FJIsamException^ tmpExp = (FJIsamException^)exp;
			Console::WriteLine( 
				String::Format( L" + {0} : {1}-{2} : {3} \n",  tmpExp->GetType()->Name,
				tmpExp->ErrorCode, tmpExp->ErrorCode2, tmpExp->Message ) );
		}else if( String::Compare( tmpExpName, gcnew String( L"WDDatasException" ) ) == 0 ){
			WDDatasException^ tmpExp = (WDDatasException^)exp;
			Console::WriteLine( 
				String::Format( L" + {0} : {1}-{2} : {3} \n",  tmpExp->GetType()->Name,
				tmpExp->ErrorCode, tmpExp->ErrorCode2, tmpExp->Message ) );
		}else if( String::Compare( tmpExpName, gcnew String( L"WordDicException" ) ) == 0){
			WordDicException^ tmpExp = (WordDicException^)exp;
			Console::WriteLine( 
				String::Format( L" + {0} : {1}-{2} : {3} \n",  tmpExp->GetType()->Name,
				tmpExp->ErrorCode, tmpExp->ErrorCode2, tmpExp->Message ) );
		}else{
			Console::WriteLine( 
				String::Format( L" + {0} : {1} \n", exp->GetType()->Name, exp->Message ) );
		}
		Console::WriteLine( exp->StackTrace );
	}
	standardOutput->Close();

}

//***** IE7以下の文字修正処理
String^ WordDic::Form1::IE7UnderString( String^ inStr )
{	
	array<Char>^ schChr;
	Int32		i;

	//-- IEコンポーネントのバージョンチェック
	if( webBrowserBook->Version->Major >= 7 )
	{
		return inStr;
	}

	//-- 引数チェック
	if( inStr == nullptr )
	{
		return nullptr;
	}

	//--データチェック
	schChr = inStr->ToCharArray();
	i = 0;
	for each( Char c in schChr )
	{
		switch( c )
		{
		case L'\u0303' :
			schChr[i] = L'~';
			break;

		}

		i++;
	}

	//-- データ返却
	return gcnew String( schChr );
}

//***** ファイルパス名取得
String^ WordDic::Form1::getFilePathName( String^ inStr )
{
	//-- 引数なしなら、プログラム実行パスを返す。
	if( inStr == nullptr )
	{
		return Path::GetDirectoryName( Application::ExecutablePath );
	}

	//-- 絶対パスなら何もしない。
	if( Path::IsPathRooted( inStr ) == true )
	{
		return inStr;
	//-- 相対パスならWordDicの実行Pathを付加する。
	}else{
		return String::Format( L"{0}\\{1}", 
			Path::GetDirectoryName( Application::ExecutablePath ), inStr );
	}

}
