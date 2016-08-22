//------------------------------------------------------------------------------
//	ことばの辞典　ことばの辞典ビューアアプリケーション　ヘッダ
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDWordSchListComparer : 単語検索結果表示用リストボックスソート
//------------------------------------------------------------------------------
#pragma once

using namespace WDDatas;

namespace WordDic
{
	public ref class WDWordSchListComparer: public System::Collections::IComparer					//単語リスト比較
	{
	public:
		virtual Int32 Compare(Object^ x, Object^ y);

		//-- 定数 --//
		static Int32 schWord = 0;										//単語検索
		static Int32 schGrp = 1;										//分類検索

		//-- ソート方法設定、確認 --//
		void setSortOrder( Int32 inSrtType,								//ソート順設定
							Int32 inSrtWord1, Int32 inSrtWord2 );

		Int32 getSortType( void );										//ソートタイプ
		Int32 getSortWord1( void );										//ソート単語１
		Int32 getSortWord2( void );										//ソート単語２

	private:
		//-- ソートルール用 --//
		Int32	srtType;												//ソートタイプ
		Int32	srtWord1;												//ソート単語１
		Int32	srtWord2;												//ソート単語２

	};
}