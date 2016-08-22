//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアーアプリケーション　ヘッダ
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDWordListBox : 単語検索結果表示用リストボックス
//------------------------------------------------------------------------------
#pragma once
#include "WDWordGrp.h"			//単語データ用辞書

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace WDDatas;



namespace WordDic {

	/// <summary>
	/// WDWordSchListBox の概要
	/// </summary>
	public ref class WDWordSchListBox : public System::Windows::Forms::ListBox
	{
	public:
		WDWordSchListBox(void)
			: ListBox(), srtType(0), srtWord1(0), srtWord2(0)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
		}


	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~WDWordSchListBox()
		{
			if (components)
			{
				delete components;
			}
		}

		//ソート
		{

		}


	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::Container ^components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			//this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion
	};
}
