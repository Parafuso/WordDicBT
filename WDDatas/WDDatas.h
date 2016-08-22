//------------------------------------------------------------------------------
//	単語辞典　単語辞典データ用例外クラス　ヘッダ
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDDatas		: データレコード基本クラス
//		WDWord		: 単語クラス
//		WDMean		: 意味クラス
//		WDGroup		: 分類クラス
//		WDSegment	: 区分クラス
//------------------------------------------------------------------------------
#pragma once

using namespace System;
using namespace FJIsam;

namespace WDDatas {

	//***** ベースクラス
	public ref class WDRec
	{
		//-- デストラクタ --//	
		virtual ~WDRec();
	public :
		//-- データレコード操作 --//
		virtual DataRecord^ getRecord( void );							//データレコード取得
		virtual void setRecord( DataRecord^ inRec );					//データレコード設定
		virtual void Write( void );										//データレコード書込
		virtual void Delete( void );									//データレコード削除

		//-- 情報操作 --//
		static Int32 Length();											//データ部長取得
		virtual Int32 RecLength();										//データレコード長取得

	private :

		DataRecord^	DataRec;
	};

	//***** 単語クラス
	public ref class WDWord : public WDRec
	{
	public :
		//-- コンストラクタ --//	
		WDWord();
		WDWord( DataRecord^ inRec );

		//-- デストラクタ --//	
		~WDWord();

		//-- データレコード操作 --//
		virtual DataRecord^ getRecord( void ) override;					//データレコード取得
		virtual void setRecord( DataRecord^ inRec ) override;			//データレコード設定
		virtual void Write( void ) override;							//データレコード書込
		virtual void Delete( void ) override;							//データレコード削除

		//-- 情報操作 --//
		static Int32 Length();											//データ部長取得
		virtual Int32 RecLength() override;								//データレコード長取得

		//-- アイテム操作 --//
		String^ getWord( String^ inData );								//単語取得
		String^ getRead1( String^ inData );								//読み1取得
		String^ getRead2( String^ inData );								//読み2取得
		Int32	getWordID( void );										//単語ID取得
		Byte	getReadPattern( void );									//読み方取得
		Boolean	getBaseFlg( void );										//基本フラグ取得
		Byte	getPractical( void );									//活用形取得
		Byte	getPlurality( void );									//単数複数取得
		Byte	getGramatical( void );									//人称取得
		Byte	getSex( void );											//性取得
		Int32	getType( void );										//活用タイプ取得
	
		void setWord( String^ inData );									//単語設定
		void setRead1( String^ inData );								//読み1設定
		void setRead2( String^ inData );								//読み2設定
		void setWordID( Int32 inData );									//単語ID設定
		void setReadPattern( Byte inData );								//読み方設定
		void setBaseFlg( Boolean inData );								//基本フラグ設定
		void setPractical( Byte inData );								//活用形設定
		void setPlurality( Byte inData );								//単数複数設定
		void setGramatical( Byte inData );								//人称設定
		void setSex( Byte inData );										//性設定
		void setType( Int32 inData );									//活用タイプ設定

	private :
		//-- データ操作 --//
		array<Byte>^ getData( array<Byte>^ inRec );						//データ取得
		void		 setData( array<Byte>^ inRec );						//データ設定

		String^			Word;						//単語
		String^			Read1;						//読み1
		String^			Read2;						//読み2
		Int32			WordID;						//単語ID
		Byte			ReadPattern;				//読み方
		Boolean			BaseFlg;					//基本フラグ
		Byte			Practical;					//活用形
		Byte			Plurality;					//単数複数
		Byte			Gramatical;					//人称
		Byte			Sex;						//性
		Int32			Type;						//活用タイプ

	};


	//***** 意味クラス用分類構造体
	public ref struct WDMeanGroup
	{
		Int32			MeanFlg;					//意味フラグ
		array<Byte>^	GroupGt;					//分類大
		array<Byte>^	GroupLt;					//分類小
		Int32			GroupRank;					//分類ランク
		DataRecord^		DataRec;					//データレコード
	};

	//意味分類比較
	public ref class WDMeanGrpComparer: System::Collections::Generic::IComparer<WDMeanGroup^>					//意味リスト比較
	{
	public:
		virtual Int32 Compare(WDMeanGroup^ x, WDMeanGroup^ y);		//意味グループ
	};

	//***** 意味クラス
	public ref class WDMean : public  WDRec
	{
	public :

		//-- コンストラクタ --//	
		WDMean( void );
		WDMean( DataRecord^ inRec );

		//-- デストラクタ --//	
		~WDMean();

		//-- データレコード操作 --//
		virtual DataRecord^ getRecord( void ) override;					//データレコード取得
		virtual void setRecord( DataRecord^ inRec ) override;			//データレコード設定
		virtual void Write( void ) override;							//データレコード書込
		virtual void Delete( void ) override;							//データレコード削除

		DataRecord^ getRecord( Int32 inIdx );							//データレコード取得(idx指定)
		void Write( Int32 inIdx );										//データレコード書込(idx指定)
		void Delete( Int32 inIdx );										//データレコード削除(idx指定)

		//-- 情報操作 --//
		Int32 DataLength( Int32 inIdx );								//データ部長取得
		virtual Int32 RecLength() override;								//データレコード長取得
		Int32	RecLength( Int32 inIdx );								//データレコード長取得(idx指定)

		Int32	getWordID( void );										//単語ID取得
		Int32	getMeanNo( void );										//意味No取得
		WDMeanGroup^	getGroup( Int32 inIdx );						//分類取得
		Int32			getMeanFlg( Int32 inIdx );						//分類フラグ取得
		array<Byte>^	getGroupGt( Int32 inIdx,						//分類大取得 
								array<Byte>^ inData );
		array<Byte>^	getGroupLt( Int32 inIdx		,					//分類小取得
								array<Byte>^ inData );					
		Int32	getGroupRank( Int32 inIdx );							//分類順位取得
		Byte	getSpeech( void );										//品詞取得
		Int32	getRank( void );										//ランク取得
		String^ getMean( String^ inData );								//単語取得
		String^ getExample( String^ inData );							//例文取得
		Int32	MeanGroupCount( void );									//分類数
		
		void setWordID( Int32 inData );									//単語ID設定
		void setMeanNo( Int32 inData );									//意味No設定
		void setGroup( Int32 inMeanFlg, array<Byte>^ inGroupGt, 		//分類設定
						array<Byte>^ inGroupLt, Int32 inGroupRank );
		void setSpeech( Byte inData );									//品詞設定
		void setRank(Byte inData );										//ランク設定
		void setMean( String^ inData );									//意味設定
		void setExample( String^ inData );								//例文設定

		void MergeMean( WDMean^ inData );								//意味マージ

	private :
		Int32 addMeanGrp( WDMeanGroup^ inMeanGrp );						//意味グループ追加

		Int32				WordID;										//単語ID
		Int32				MeanNo;										//意味No
		List<WDMeanGroup^>^	MeanGroup;									//意味グループ
		Byte				Speech;										//品詞
		Int32				Rank;										//ランク
		String^				Mean;										//意味
		String^				Example;									//例文

		//-- 意味グループ比較
		static WDMeanGrpComparer^ WDMeanGrpComp = nullptr;				//意味分類並び替え

	};

	
	//***** 翻訳クラス
	public ref class WDTrans : public  WDRec
	{
	public :
		//-- コンストラクタ --//	
		WDTrans( void );
		WDTrans( DataRecord^ inRec );

		//-- デストラクタ --//	
		~WDTrans();

		//-- データレコード操作 --//
		virtual DataRecord^ getRecord( void ) override;					//データレコード取得
		virtual void setRecord( DataRecord^ inRec ) override;			//データレコード設定
		virtual void Write( void ) override;							//データレコード書込
		virtual void Delete( void ) override;							//データレコード削除

		//-- 情報操作 --//
		Int32 DataLength( void );										//データ部長取得
		virtual Int32 RecLength() override;								//データレコード長取得

		Int32	getWordID( void );										//単語ID取得
		Int32	getMeanNo( void );										//意味No取得
		Int32	getTransID( Int32 inIdx );								//翻訳ID取得
		Int32	getTransNo( Int32 inIdx );								//翻訳意味No取得

		void setWordID( Int32 inData );									//単語ID設定
		void setMeanNo( Int32 inData );									//意味No設定
		void setTransID( Int32 inData, Int32 inIdx );					//翻訳ID設定
		void setTransNo( Int32 inData, Int32 inIdx );					//翻訳意味No設定
		void AddTransID( Int32 inID, Int32 inNo );						//翻訳ID追加
		void RemoveTransID( Int32 inIdx );								//翻訳ID削除
		Int32 CountTransID( void );										//翻訳ID数カウント

	private :
		//-- データ操作 --//
		array<Byte>^ getData( array<Byte>^ inRec );						//データ取得
		void		 setData( array<Byte>^ inRec );						//データ設定

		Int32			WordID;					//単語ID
		Int32			MeanNo;					//意味No
		List<Int32>^	TransID;				//翻訳ID
		List<Int32>^	TransNo;				//翻訳意味No

	};

	//***** 関連語クラス
	public ref class WDRelation : public  WDRec
	{
	public :
		//-- コンストラクタ --//	
		WDRelation( void );
		WDRelation( DataRecord^ inRec );

		//-- デストラクタ --//	
		~WDRelation();

		//-- データレコード操作 --//
		virtual DataRecord^ getRecord( void ) override;					//データレコード取得
		virtual void setRecord( DataRecord^ inRec ) override;			//データレコード設定
		virtual void Write( void ) override;							//データレコード書込
		virtual void Delete( void ) override;							//データレコード削除

		//-- 情報操作 --//
		Int32 DataLength();												//データ部長取得
		virtual Int32 RecLength() override;								//データレコード長取得

		Int32	getWordID( void );										//単語ID取得
		Int32	getMeanNo( void );										//意味No取得
		Int32	getRelationType( Int32 inIdx );							//関連語タイプ取得
		Int32	getRelationID( Int32 inIdx );							//関連語ID取得
		Int32	getRelationNo( Int32 inIdx );							//関連語意味No取得
	
		void setWordID( Int32 inData );									//単語ID設定
		void setMeanNo( Int32 inData );									//意味No設定
		void setRelationType( Int32 inData, Int32 inIdx );				//関連タイプ設定
		void setRelationID( Int32 inData, Int32 inIdx );				//関連語ID設定
		void setRelationNo( Int32 inData, Int32 inIdx );				//関連語意味No設定
		void AddRelation( Int32 inType, Int32 inID, Int32 inNo );		//関連語追加
		void RemoveRelation( Int32 inIdx );								//関連語削除
		Int32 CountRelation( void );									//関連語数カウント

	private :
		//-- データ操作 --//
		array<Byte>^ getData( array<Byte>^ inRec );						//データ取得
		void		 setData( array<Byte>^ inRec );						//データ設定

		Int32			WordID;					//単語ID
		Int32			MeanNo;					//意味No
		List<Int32>^	RelationType;			//関連語種類
		List<Int32>^	RelationID;				//関連語ID
		List<Int32>^	RelationNo;				//関連語意味No


	};

	//***** 分類クラス
	public ref class WDGroup : public WDRec
	{
	public :
		//-- コンストラクタ --//	
		WDGroup();
		WDGroup( DataRecord^ inRec );

		//-- デストラクタ --//	
		~WDGroup();

		//-- データレコード操作 --//
		virtual DataRecord^ getRecord( void ) override;					//データレコード取得
		virtual void setRecord( DataRecord^ inRec ) override;			//データレコード設定
		virtual void Write( void ) override;							//データレコード書込
		virtual void Delete( void ) override;							//データレコード削除

		//-- 情報操作 --//
		static Int32 Length();											//データ部長取得
		virtual Int32 RecLength() override;								//データレコード長取得

		//-- アイテム操作 --//
		array<Byte>^ getGroupGt( array<Byte>^ inData );					//分類大取得
		array<Byte>^ getGroupLt( array<Byte>^ inData );					//分類小取得
		String^		 getName( String^ inData );							//名称取得
		String^		 getShortName( String^ inData );					//略称取得


		void setGroupGt( array<Byte>^ inData );							//分類大設定
		void setGroupLt( array<Byte>^ inData );							//分類小設定
		void setName( String^ inData );									//名称設定
		void setShortName( String^ inData );							//略称設定

	private :
		//-- データ操作 --//
		array<Byte>^ getData( array<Byte>^ inRec );						//データ取得
		void		 setData( array<Byte>^ inRec );						//データ設定

		array<Byte>^	GroupGt;				//分類大
		array<Byte>^	GroupLt;				//分類小
		String^			Name;					//名称
		String^			ShortName;				//略称
	};

	//***** 分類クラス
	public ref class WDSegment : public WDRec
	{
	public :
		//-- コンストラクタ --//	
		WDSegment();
		WDSegment( DataRecord^ inRec );

		//-- デストラクタ --//	
		~WDSegment();

		//-- データレコード操作 --//
		virtual DataRecord^ getRecord( void ) override;					//データレコード取得
		virtual void setRecord( DataRecord^ inRec ) override;			//データレコード設定
		virtual void Write( void ) override;							//データレコード書込
		virtual void Delete( void ) override;							//データレコード削除

		//-- 情報操作 --//
		static Int32 Length();											//データ部長取得
		virtual Int32 RecLength() override;								//データレコード長取得

		//-- アイテム操作 --//
		Int32	getSegmentID( void );									//区分ID取得
		Int32	getSegmentNo( void );									//区分No取得
		String^	 getName( String^ inData );								//名称取得
		String^	 getShortName( String^ inData );						//略称取得

		void setSegmentID( Int32 inData );								//区分ID設定
		void setSegmentNo( Int32 inData );								//区分No設定
		void setName( String^ inData );									//名称設定
		void setShortName( String^ inData );							//略称設定

	private :
		//-- データ操作 --//
		array<Byte>^ getData( array<Byte>^ inRec );						//データ取得
		void		 setData( array<Byte>^ inRec );						//データ設定

		Int32			SegmentID;				//区分ID
		Int32			SegmentNo;				//区分No
		String^			Name;					//名称
		String^			ShortName;				//略称
	};



}
