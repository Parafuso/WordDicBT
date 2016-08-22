//------------------------------------------------------------------------------
//	ことばの辞典　ことばの辞典ビューアアプリケーション　ヘッダ
//	Version 1.0.0.0		create date 2006/05/08
//	Version 1.0.1.0		create date 2009/09/13
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	Windows Formのアプリケーション
//------------------------------------------------------------------------------
// WordDicMenu.cpp : メニュー動作
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
//　ボタンクリック
//------------------------------------------------------------------------------
//***** 終了ボタンクリック
System::Void WordDic::Form1::終了toolStripButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	//-- アプリケーションを終了する
	this->Close();
}

//***** コピーボタンクリック
System::Void WordDic::Form1::コピーCToolStripButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	BookWordCopy();
}

//***** 設定ボタンクリック
System::Void WordDic::Form1::toolStripButtonConfig_Click(System::Object^  sender, System::EventArgs^  e)
{
	dlgWDConfig->ShowDialog();
}

//***** ヘルプボタンクリック
System::Void WordDic::Form1::ヘルプLToolStripButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	Drawing::Point ^dispPoint;
	//Point ^formPoint;
	Drawing::Size  ^clientSZ;
	Drawing::Size  ^formSZ;

	//メニュー位置を設定
	clientSZ = this->ClientSize;
	formSZ = this->Size;
	//formPoint = this->Location;
	dispPoint = Cursor->Position;

	dispPoint->X -= this->Left + (formSZ->Width - clientSZ->Width);
	dispPoint->Y -= this->Top + (formSZ->Height - clientSZ->Height);

	//-- ヘルプメニューを表示
	contextMenuHelp->Show( this, *dispPoint );
}

//------------------------------------------------------------------------------
//　ヘルプメニュー
//------------------------------------------------------------------------------
//***** ヘルプメニュー：「マニュアル」
System::Void WordDic::Form1::ToolStripMenuItemHelpMan_Click(System::Object^  sender, System::EventArgs^  e)
{
	String ^strFileName;

	strFileName = String::Concat(
					Path::GetDirectoryName( Application::ExecutablePath ) ,
					L"\\ことばの辞典 マニュアル.pdf" );

	//-- マニュアル起動（PDF）
	System::Diagnostics::Process::Start( strFileName );


}
//***** ヘルプメニュー：「バージョン情報」
System::Void WordDic::Form1::ToolStripMenuItemHelpVer_Click(System::Object^  sender, System::EventArgs^  e)
{
	//-- バージョン情報ダイアログ表示
	dlgWDVerDialog->ShowDialog();
}

