//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアー用クラス　ソース
//	Version 1.0		create date 2007/10/07
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDVerDialog : バージョンダイアログ
//------------------------------------------------------------------------------
#include "StdAfx.h"
#include "WDVerDialog.h"

//***** OKボタンクリック時
System::Void WordDic::WDVerDialog::buttonOK_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Close();
}
