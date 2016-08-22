//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアーアプリケーション　ヘッダ
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDWordList : 単語検索結果表示用リストボックス
//------------------------------------------------------------------------------
#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace WordDic {

	/// <summary>
	/// WDWordList の概要
	/// </summary>
	public ref class WDWordList : public System::Windows::Forms::ListBox
	{
	public:
		//-- 定数 --//
		static Int32 schWord = 0;										//単語検索
		static Int32 schGrp = 1;										//分類検索

		//-- コンストラクタ --//
		WDWordList(void)
			: ListBox(), srtType(schWord), srtWord1(0), srtWord2(0)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
		}
		//-- ソート方法設定、確認 --//
		void setSortOrder( Int32 inSrtType,								//ソート順設定
							Int32 inSrtWord1, Int32 inSrtWord2 );

		Int32 getSortType( void );										//ソートタイプ
		Int32 getSortWord1( void );										//ソート単語１
		Int32 getSortWord2( void );										//ソート単語２

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~WDWordList()
		{
			if (components)
			{
				delete components;
			}
		}

		//-- ソート --//
		virtual void Sort() override;			

	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

		//-- ソートルール用 --//
		Int32	srtType;												//ソートタイプ
		Int32	srtWord1;												//ソート単語１
		Int32	srtWord2;												//ソート単語２

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
