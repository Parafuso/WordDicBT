//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアー用クラス　ヘッダ
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WordDicCfg : 単語辞典コンフィグ
//------------------------------------------------------------------------------
#pragma once
using namespace WDDatas;

namespace WordDic
{
	public ref class WordDicCfg
	{
	public:
		//***** 区分ファイル情報
		String^ GroupFName;										//分類ファイル名

		//***** 言語A情報
		//ファイル情報
		String^ WordFNameA;										//単語ファイル名 言語A
		String^ MeanFNameA;										//意味ファイル名 言語A
		String^ TransFNameA;									//翻訳ファイル名 言語A
		String^ RelationFNameA;									//関連語ファイル名 言語A
		String^ SegmentFNameA;									//区分ファイル名 言語A

		//単語検索インデックス情報
		Int32 Read1IdxA;										//読み方1インデックス 言語A
		Int32 Read2IdxA;										//読み方2インデックス 言語A

		//単語検索リスト情報
		Int32 WordListSortA1;									//単語リストのソート順１ 言語A( 1:Word、2:Read1,3:Read2 )
		Int32 WordListSortA2;									//単語リストのソート順２ 言語A( 1:Word、2:Read1,3:Read2 )

		//単語リスト表示
		Int32 WordListDispA;									//単語リスト表示 言語A
		Int32 WordListSubDispA;									//単語リストサブ表示 言語A

		//単語表示テンプレート情報
		String^ XSLTFNameA;										//XSLファイル名 言語A

		//***** 言語B情報
		//ファイル情報
		String^ WordFNameB;										//単語ファイル名 言語B
		String^ MeanFNameB;										//意味ファイル名 言語B
		String^ TransFNameB;									//翻訳ファイル名 言語B
		String^ RelationFNameB;									//関連語ファイル名 言語B
		String^ SegmentFNameB;									//区分ファイル名 言語B

		//単語検索インデックス情報
		Int32 Read1IdxB;										//読み方1インデックス 言語B
		Int32 Read2IdxB;										//読み方1インデックス 言語B

		//単語表示テンプレート情報
		String^ XSLTFNameB;										//XSLファイル名 言語B

		//単語検索リストソート情報
		Int32 WordListSortB1;									//単語リストのソート順１ 言語B( 1:Word、2:Read1,3:Read2 )
		Int32 WordListSortB2;									//単語リストのソート順２ 言語B( 1:Word、2:Read1,3:Read2 )

		//単語リスト表示
		Int32 WordListDispB;									//単語リスト表示 言語B
		Int32 WordListSubDispB;									//単語リストサブ表示 言語B1

		//単語検索メッセージ
		String^ WordSchZero;									//単語が見つからない時
		String^ WordSchAny;										//単語が見つかった時

	};
}
