//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアーアプリケーション　ソース
//	Version 1.0.0.0		create date 2006/05/08
//	Version 1.0.1.0		create date 2009/09/13
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	Windows Formのアプリケーション
//------------------------------------------------------------------------------
// WordDicClipBorad.cpp : クリップボード操作。
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
// Bookの右クリックメニュー
//------------------------------------------------------------------------------
//***** コピー（選択された文字をコピーする）
System::Void WordDic::Form1::toolStripMenuItemBookCopy_Click(System::Object^  sender, System::EventArgs^  e)
{
	//ブック領域に何も表示されていなければ何もしない。
	if( webBrowserBook->Document->Title == L"" )	return;

	BookWordCopy();
}

//***** Bookの選択テキストコピー
void WordDic::Form1::BookWordCopy( void )
{
	String ^strCopyWord;

	//ブック領域に何も表示されていなければ何もしない。
	if( webBrowserBook->Document->Title == L"" )	return;

	strCopyWord = GetProcWord();
	System::Windows::Forms::Clipboard::SetText( strCopyWord );

}

//***** Bookメニュー：「Bing検索」
System::Void WordDic::Form1::ToolStripMenuItemWebSchSite1_Click(System::Object^  sender, System::EventArgs^  e)
{
	String ^strCopyWord;
	String ^strSearchWord;

	//ブック領域に何も表示されていなければ何もしない。
	if( webBrowserBook->Document->Title == L"" )	return;

	//対象文字を選択
	strCopyWord = GetProcWord();
	strSearchWord = createSearchStrBytes( strCopyWord );

	//ブラウザでWeb検索を実施する
	System::Diagnostics::Process::Start( String::Concat( WEB_BING, strSearchWord ) );

}

//***** Bookメニュー：「Google検索」
System::Void WordDic::Form1::ToolStripMenuItemWebSchSite2_Click(System::Object^  sender, System::EventArgs^  e)
{
	String ^strCopyWord;
	String ^strSearchWord;

	//ブック領域に何も表示されていなければ何もしない。
	if( webBrowserBook->Document->Title == L"" )	return;

	//対象文字を選択
	strCopyWord = GetProcWord();
	strSearchWord = createSearchStrBytes( strCopyWord );

	//ブラウザでWeb検索を実施する
	System::Diagnostics::Process::Start( String::Concat( WEB_GOOGLE, strSearchWord ) );
}

//***** Bookメニュー：「エンカルタ表示」
System::Void WordDic::Form1::ToolStripMenuItemWebEncycro1_Click(System::Object^  sender, System::EventArgs^  e)
{
	String ^strCopyWord;
	String ^strSearchWord;

	//ブック領域に何も表示されていなければ何もしない。
	if( webBrowserBook->Document->Title == L"" )	return;

	//対象文字を選択
	strCopyWord = GetProcWord();
	strSearchWord = createSearchStrBytes( strCopyWord );

	//ブラウザでWeb検索を実施する
	System::Diagnostics::Process::Start( String::Concat( WEB_ENCALTA, strSearchWord ) );

}

//***** Bookメニュー：「Wiki表示」
System::Void WordDic::Form1::ToolStripMenuItemWebEncycro2_Click(System::Object^  sender, System::EventArgs^  e)
{
	String ^strCopyWord;
	String ^strSearchWord;

	//ブック領域に何も表示されていなければ何もしない。
	if( webBrowserBook->Document->Title == L"" )	return;

	//対象文字を選択
	strCopyWord = GetProcWord();
	strSearchWord = createSearchStrBytes( strCopyWord );

	//ブラウザでWeb検索を実施する
	System::Diagnostics::Process::Start( String::Concat( WEB_WIKI, strSearchWord ) );
}

//------------------------------------------------------------------------------
// 関連コマンド
//------------------------------------------------------------------------------
//*****Web検索ワード作成
String^ WordDic::Form1::GetProcWord( void )
{
	String ^rtWord;
	mshtml::IHTMLDocument2 ^IHtmlDoc;
	mshtml::IHTMLSelectionObject ^ IHtmlSelDoc;
	mshtml::IHTMLTxtRange ^IHtmlTxt;

	IHtmlDoc = static_cast<mshtml::IHTMLDocument2^>(webBrowserBook->Document->DomDocument);
	IHtmlSelDoc = IHtmlDoc->selection;
	IHtmlTxt = static_cast<mshtml::IHTMLTxtRange^>(IHtmlSelDoc->createRange());

	//ブックに文字が選択されていれば選択された文字を返す。
	if (IHtmlTxt->text != nullptr )
	{
		rtWord = IHtmlTxt->text;

		//何も選択されていなければ、タイトルを選択する。
	}else{
		rtWord = webBrowserBook->Document->Title;
	}

	return rtWord;

}

//*****Web検索ワード作成
String^ WordDic::Form1::createSearchStrBytes( String^ strSchWord )
{
	System::Text::Encoding^ tmpEnc = System::Text::Encoding::UTF8;
	String^ strTrimWord;										//トリミング後の検索ワード		
	array<Byte>^ tmpBytes;
	array<Char>^ tmpStrArray;

	String^ strRetWord;

	//トリミングを行う。
	strTrimWord = strSchWord->Trim();
	
	//UTF8へコード変換を行う。
	tmpBytes = tmpEnc->GetBytes( strTrimWord );

	//変換領域を作成する
	tmpStrArray = gcnew array<Char>(tmpBytes->Length * 3 +1);

	for( Int32 i = 0; i < tmpBytes->Length; i++ )
	{
		String^ tmpCodeStr = String::Format("%{0:X2}", tmpBytes[i] );
		tmpStrArray[i * 3]		= tmpCodeStr[0];
		tmpStrArray[i * 3 + 1 ]	= tmpCodeStr[1];
		tmpStrArray[i * 3 + 2 ] = tmpCodeStr[2];

	}
	tmpStrArray[tmpBytes->Length * 3] = 0;

	//返却ワードを作成する
	strRetWord = gcnew String(tmpStrArray);

	return strRetWord;
}