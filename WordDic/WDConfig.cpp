//------------------------------------------------------------------------------
//	ことばの辞典　ことばの辞典ビューアアプリケーション　ヘッダ
//	Version 1.0		create date 2008/03/15
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDConfig : 設定画面
//------------------------------------------------------------------------------
#include "StdAfx.h"
#include "WDConfig.h"			//設定画面
#include "WDDatasDef.h"			//単語辞典データ定数定義
#include "WDWordGrp.h"			//単語データ用辞書

using namespace WDDatas;

//------------------------------------------------------------------------------
//　ダイアログ初期表示
//------------------------------------------------------------------------------
//***** ダイアログ初期表示
System::Void WordDic::WDConfig::WDConfig_Shown(System::Object^  sender, System::EventArgs^  e)
{
	comboBoxScreenLang->Text = comboBoxScreenLang->Items[0]->ToString();	//言語の選択
	comboBoxWebSearch->Text = comboBoxWebSearch->Items[0]->ToString();		//Webサーチの選択
}


//------------------------------------------------------------------------------
//　ボタンクリック
//------------------------------------------------------------------------------
//***** OKボタンクリック
System::Void WordDic::WDConfig::buttonOK_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Close();
}
