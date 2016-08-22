//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアー用クラス　ヘッダ
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDWordGrp : 辞典単語情報
//------------------------------------------------------------------------------
#pragma once
using namespace WDDatas;

namespace WordDic
{
	public ref class WDWordComparer: System::Collections::Generic::IComparer<WDWord^>					//単語リスト比較
	{
	public:
		virtual Int32 Compare(WDWord^ x, WDWord^ y);
	};

	public ref class WDMeanComparer: System::Collections::Generic::IComparer<WDMean^>					//意味リスト比較
	{
	public:
		virtual Int32 Compare(WDMean^ x, WDMean^ y);
	};

	public ref class WDTransComparer: System::Collections::Generic::IComparer<WDTrans^>				//翻訳リスト比較
	{
	public:
		virtual Int32 Compare(WDTrans^ x, WDTrans^ y);
	};

	public ref class WDRelationComparer: System::Collections::Generic::IComparer<WDRelation^>			//関連語リスト比較
	{
	public:
		virtual Int32 Compare(WDRelation^ x, WDRelation^ y);
	};

	//***** 単語グループ
	public ref class WDWordGrp 
	{
	public :
		//--  コンストラクタ --//
		WDWordGrp( Int32 inLang, Int32 inDispNum, Int32 inSubDispNum );
		//--  デストラクタ --//
		~WDWordGrp();

		//-- アイテム参照 --//
		WDWord^ getWord( Int32 idx );									//単語取得
		WDWord^ getBaseWord( void );									//基本単語取得
		WDWord^ getBaseWord( Int32 inReadPattern );						//基本単語取得(読み方による)
		WDWord^	getSchWord( void );										//検索単語取得
		WDMean^ getMean( Int32 idx );									//意味取得
		WDMean^ getSchMean( void );										//検索意味取得
		WDTrans^ getTrans( Int32 idx );									//翻訳取得
		WDTrans^ getTransNo( Int32 inNo );								//翻訳取得(意味NOによる)
		WDRelation^ getRelation( Int32 idx );							//関連語取得
		WDRelation^ getRelationNo( Int32 inNo );						//関連語取得(意味NOによる)
		String^		getXMLFname( void );								//XMLファイル名取得

		Int32 getWordID( void );										//単語ID取得
		Int32 getWordCnt( void );										//単語数取得
		Int32 getMeanCnt( void );										//意味数取得
		Int32 getTransCnt( void );										//翻訳数取得
		Int32 getRelationCnt( void );									//関連語数取得

		Int32 getSchMethod( void );										//検索方法取得
		Int32 getSchLang( void );										//検索言語取得
		Int32 getWordListDisp( void );									//ToStringでの表示方法取得
		Int32 getSchGroupRank( void );									//検索意味分類順位
		Int32 getReadPatternCnt( void );								//読み方数取得

		//-- アイテム設定 --//
		void addWord( WDWord^ inWord, Boolean inSch );					//単語追加
		void addMean( WDMean^ inMean, Boolean inSch, Int32 inMeanFlg );	//意味追加
		void addTrans( WDTrans^ inTrans );								//翻訳追加
		void addRelation( WDRelation^ inRelation );						//関連語追加
		void setXMLFname( String^ inXMLFname );							//XMLファイル名設定
		void setWordListDisp( Int32 inDispNum, Int32 inSubDispNum );	//ToStringでの表示方法設定

		//-- リストBox用 --//
		virtual String^ ToString( void ) override;						//文字列取得

	private :
		List<WDWord^>^		WordLst;									//単語リスト
		List<WDMean^>^		MeanLst;									//意味リスト
		List<WDTrans^>^		TransLst;									//翻訳リスト
		List<WDRelation^>^	RelationLst;								//関連語リスト
		List<WDWord^>^		BaseWordLst;								//基本単語リスト
		WDWord^				SchWord;									//検索単語
		WDMean^				SchMean;									//検索単語
		Int32				WordID;										//単語ID
		String^				XMLFname;									//単語情報XMLファイル名
		Int32				SchMethod;									//検索方法( 1:単語 2:意味(分類) )
		Int32				SchLang;									//検索言語( 1:言語A 2:言語B )
		Int32				SchGroupRank;								//分類順位
		Int32				SchReadPattern;								//検索読み方

		Int32				DispNum;									//ToStringでの表示単語( 1:Word 2:Read1 3:Read2 )
		Int32				SubDispNum;									//ToStringでのサブ表示単語( 〃 )

		static WDWordComparer^		WDWordComp = nullptr;				//単語リスト比較
		static WDMeanComparer^		WDMeanComp = nullptr;				//意味リスト比較
		static WDTransComparer^		WDTransComp = nullptr;				//翻訳リスト比較
		static WDRelationComparer^	WDRelationComp = nullptr;			//関連語リスト比較
	};

}