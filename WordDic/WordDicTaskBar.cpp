//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアーアプリケーション　ソース
//	Version 1.0			Create date 2006/05/08
//	Version 1.0.3.0		Change date 2010/11/16

//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	Windows Formのアプリケーション
//------------------------------------------------------------------------------
// WordDicTaskBar.cpp : タスクバーに追加したボタンの処理を記述したファイルです。
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
// タスクバー：言語ボタン１からの検索
//------------------------------------------------------------------------------
System::Void WordDic::Form1::ThumbButtonSchLangA_Click(System::Object^  sender, 
							Microsoft::WindowsAPICodePack::Taskbar::ThumbnailButtonClickedEventArgs^  e)
{
	String^	ClipWord;												//クリップボードの単語
	array<String^>^	SchWord;										//検索する単語（改行コード等を整形）
	
	array<String^>^ SplitChar = gcnew array<String^>{ L"\n" };		//抽出する文字の区切り

	//-- クリップボードの文字を取得 --//
	ClipWord = System::Windows::Forms::Clipboard::GetText();

	//クリップボードの文字が空なら何もしない。
	if( String::IsNullOrEmpty( ClipWord ) == true )
	{
		return;
	}
	
	//-- クリップボードの文字を整形する --//
	// 改行がある場合は1行目のみを抽出 //
	SchWord = ClipWord->Split( SplitChar, System::StringSplitOptions::RemoveEmptyEntries );
	


	//-- クリップボードの単語で言語１の検索を行う --//
	textBoxSchWord->Text = SchWord[0]->Trim();						//検索単語設定（前後の空白を除去）
	radioButtonWordA->Checked = true;								//検索対象を言語Ａに設定
	buttonSchWord->PerformClick();									//検索実行（検索ボタンクリック）

	//-- 画面を表示する --//
	tabCtrlSearch->SelectTab(0);									//単語検索のタブを表示する。
	this->Activate();												//ことばの事典をアクティブにする。


}

//------------------------------------------------------------------------------
// タスクバー：言語ボタン２からの検索
//------------------------------------------------------------------------------
System::Void WordDic::Form1::ThumbButtonSchLangB_Click(System::Object^  sender, 
							Microsoft::WindowsAPICodePack::Taskbar::ThumbnailButtonClickedEventArgs^  e)
{
	String^	ClipWord;												//クリップボードの単語
	array<String^>^	SchWord;										//検索する単語（改行コード等を整形）
	
	array<String^>^ SplitChar = gcnew array<String^>{ L"\n" };		//抽出する文字の区切り

	//-- クリップボードの文字を取得 --//
	ClipWord = System::Windows::Forms::Clipboard::GetText();

	//クリップボードの文字が空なら何もしない。
	if( String::IsNullOrEmpty( ClipWord ) == true )
	{
		return;
	}
	
	//-- クリップボードの文字を整形する --//
	// 改行がある場合は1行目のみを抽出 //
	SchWord = ClipWord->Split( SplitChar, System::StringSplitOptions::RemoveEmptyEntries );
	


	//-- クリップボードの単語で言語１の検索を行う --//
	textBoxSchWord->Text = SchWord[0]->Trim();						//検索単語設定（前後の空白を除去）
	radioButtonWordB->Checked = true;								//検索対象を言語Ｂに設定
	buttonSchWord->PerformClick();									//検索実行（検索ボタンクリック）

	//-- 画面を表示する --//
	tabCtrlSearch->SelectTab(0);									//単語検索のタブを表示する。
	this->Activate();												//ことばの事典をアクティブにする。

}
