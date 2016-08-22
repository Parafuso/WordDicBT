//------------------------------------------------------------------------------
//	単語辞典　単語辞典データクラス　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDRelation		: 関連語クラス
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//単語辞典データ用例外クラス
#include "WDDatas.h"			//単語辞典データクラス
#include "WDDatasDef.h"			//単語辞典データ定数定義
//#include "FJIsamDef.h"			//ISAM用定義ファイル

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDRelation		: 関連語クラス
//------------------------------------------------------------------------------
//***** コンストラクタ１(新規データ)
WDDatas::WDRelation::WDRelation()
 //: WDRec()
{
	//-- 変数定義 --//
	WordID = 0;
	MeanNo = 0;
	RelationType = gcnew List<Int32>();
	RelationID = gcnew List<Int32>();
	RelationNo = gcnew List<Int32>();
}

//***** コンストラクタ２(読込データ)
WDDatas::WDRelation::WDRelation( DataRecord^ inRec )
{

	//-- 変数定義 --//
	WordID = 0;
	MeanNo = 0;
	RelationType = gcnew List<Int32>();
	RelationID = gcnew List<Int32>();
	RelationNo = gcnew List<Int32>();

	if(inRec == nullptr )
	{
		return;
	}

	//-- 引数チェック --//
	if( inRec->getDataLength() < WDRELATION_WORDIDLEN +
			WDRELATION_MEANNOLEN + WDRELATION_RELATIONCNTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードが意味データではありません。" );
		tmpWDDataException->ErrorCode  = 10601;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	
	//-- データ設定 --//
	try
	{
		setRecord( inRec );
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データ設定でエラーが発生しました。", exp );
		tmpWDDataException->ErrorCode  = 10601;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//***** デストラクタ
WDDatas::WDRelation::~WDRelation()
{
	if( RelationType != nullptr ) delete RelationType;
	if( RelationID != nullptr ) delete RelationID;
	if( RelationNo != nullptr ) delete RelationNo;
}

//------------------------------------------------------------------------------
//　データレコード操作
//------------------------------------------------------------------------------
//***** データレコード取得
DataRecord^ WDDatas::WDRelation::getRecord( void )
{
	DataRecord^ tmpRec;
	array<Byte>^ tmpDat;

	if( WDRec::getRecord() == nullptr )
	{
		try
		{
			tmpDat = getData( nullptr );
			tmpRec = gcnew DataRecord();
			tmpRec->setData( tmpDat, DataLength() );
			WDRec::setRecord( tmpRec );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データレコード取得でエラーが発生しました。", exp );
			tmpWDDataException->ErrorCode  = 10602;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}
	}else{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = WDRec::getRecord();
			tmpRec->setData( tmpDat, DataLength()  );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データレコード取得でエラーが発生しました。", exp );
			tmpWDDataException->ErrorCode  = 10602;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}

	delete tmpDat;

	//-- 正常終了 --//
	return tmpRec;
}

//***** データレコード設定
void WDDatas::WDRelation::setRecord(  DataRecord^ inRec )
{
	if( inRec != nullptr )
	{
		try
		{
			array<Byte>^ tmpDat;
			tmpDat = inRec->getData( nullptr );
			setData( tmpDat );
			delete tmpDat;
			WDRec::setRecord( inRec );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データレコード設定でエラーが発生しました。", exp );
			tmpWDDataException->ErrorCode  = 10603;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}
	}else{
		try
		{
			WDRec::setRecord( nullptr );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データレコード設定でエラーが発生しました。", exp );
			tmpWDDataException->ErrorCode  = 10603;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}
}

//***** データレコード書込
void WDDatas::WDRelation::Write( void )
{
	FIsam^ tmpParent;

	//-- データレコードチェック --//
	if( WDRec::getRecord() == nullptr )
	{
		return;
	}

	//-- ISAMファイルチェック --//
	try
	{
		tmpParent = safe_cast<FIsam^>( WDRec::getRecord()->getParentFile() );
		if( tmpParent == nullptr )
		{
			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAMファイルが不正です。", exp );
		tmpWDDataException->ErrorCode  = 10604;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- レコード書込(自動で追加、更新判断) --//
	try
	{
		if( WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_NEW )
		{
			tmpParent->AddRecord( getRecord() );
		}else if( WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_OLD ){
			tmpParent->UpdateRecord( getRecord() );
		}else{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"レコード削除はできません。" );
			tmpWDDataException->ErrorCode  = 10604;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10604;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** データレコード書込
void WDDatas::WDRelation::Delete( void )
{
	FIsam^ tmpParent;

	//-- データレコードチェック --//
	if( WDRec::getRecord() == nullptr )
	{
		//--　データクリア --//
		WordID = 0;
		MeanNo = 0;
		RelationType->Clear();
		RelationID->Clear();
		RelationNo->Clear();
		
		return;
	}

	//-- ISAMファイルチェック --//
	try
	{
		tmpParent = safe_cast<FIsam^>( WDRec::getRecord()->getParentFile() );
		if( tmpParent == nullptr )
		{
			//--　データクリア --//
			WordID = 0;
			MeanNo = 0;
			RelationType->Clear();
			RelationID->Clear();
			RelationNo->Clear();

			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAMファイルが不正です。", exp );
		tmpWDDataException->ErrorCode  = 10605;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- レコード削除 --//
	try
	{
		if( WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_NEW )
		{
			;
		}else if( WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_OLD ){
			tmpParent->DeleteRecord( getRecord() );
		}else{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"レコード削除はできません。" );
			tmpWDDataException->ErrorCode  = 10605;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10605;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//--　データクリア --//
	WordID = 0;
	MeanNo = 0;
	RelationType->Clear();
	RelationID->Clear();
	RelationNo->Clear();

}
//------------------------------------------------------------------------------
//　情報操作
//------------------------------------------------------------------------------
//***** データ部長取得
Int32 WDDatas::WDRelation::DataLength( void )
{
	Int32 tmpRelationSize;

	//-- 可変長部分のサイズを取得
	if( RelationType == nullptr )
	{
		tmpRelationSize = 0;
	}else{
		tmpRelationSize = ( WDRELATION_RELATIONTYPELEN +
							WDRELATION_RELATIONIDLEN + WDRELATION_RELATIONNOLEN )
							* RelationType->Count;
	}

	return	WDRELATION_WORDIDLEN +
			WDRELATION_MEANNOLEN +
			WDRELATION_RELATIONCNTLEN +
			tmpRelationSize;
}

//***** データレコード長取得
Int32 WDDatas::WDRelation::RecLength()
{
	return DataRecord::getHeaderLength() + DataLength();
}

//------------------------------------------------------------------------------
//　アイテム操作
//------------------------------------------------------------------------------
//***** 単語ID取得
Int32 WDDatas::WDRelation::getWordID( void )
{
	return WordID;
}

//***** 意味No取得
Int32 WDDatas::WDRelation::getMeanNo( void )
{
	return MeanNo;
}

//***** 関連語タイプ取得
Int32	WDDatas::WDRelation::getRelationType( Int32 inIdx )
{
	if( RelationType == nullptr ) return -1;

	if( inIdx < 0 || inIdx >= RelationType->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックス指定が範囲外です。" );
		tmpWDDataException->ErrorCode  = 10606;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	return RelationType[inIdx];
}

//***** 関連語ID取得
Int32	WDDatas::WDRelation::getRelationID( Int32 inIdx )
{
	if( RelationID == nullptr ) return -1;

	if( inIdx < 0 || inIdx >= RelationID->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックス指定が範囲外です。" );
		tmpWDDataException->ErrorCode  = 10607;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	return RelationID[inIdx];
}

//***** 関連語意味No取得
Int32	WDDatas::WDRelation::getRelationNo( Int32 inIdx )
{
	if( RelationNo == nullptr ) return -1;

	if( inIdx < 0 || inIdx >= RelationNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックス指定が範囲外です。" );
		tmpWDDataException->ErrorCode  = 10617;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	return RelationNo[inIdx];
}

//------------------------------------------------------------------------------
//***** 単語ID設定
void WDDatas::WDRelation::setWordID( Int32 inData )
{
	//-- 引数チェック --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"単語IDが不正です。" );
		tmpWDDataException->ErrorCode  = 10608;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	WordID = inData;
}

//***** 単語ID設定
void WDDatas::WDRelation::setMeanNo( Int32 inData )
{
	//-- 引数チェック --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味Noが不正です。" );
		tmpWDDataException->ErrorCode  = 10609;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	MeanNo = inData;
}


//***** 関連語タイプ設定
void WDDatas::WDRelation::setRelationType( Int32 inData, Int32 inIdx )
{	
	//-- 引数チェック --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"関連語タイプが不正です。" );
		tmpWDDataException->ErrorCode  = 10610;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	if( RelationType == nullptr || 
		inIdx < 0 || inIdx >= RelationType->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックス指定が範囲外です。" );
		tmpWDDataException->ErrorCode  = 10610;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	//-- データ設定 --//
	RelationType[inIdx] = inData;
}			

//***** 関連語ID設定
void WDDatas::WDRelation::setRelationID( Int32 inData, Int32 inIdx )
{	
	//-- 引数チェック --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"関連語IDが不正です。" );
		tmpWDDataException->ErrorCode  = 10611;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	if( RelationID == nullptr || 
		inIdx < 0 || inIdx >= RelationID->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックス指定が範囲外です。" );
		tmpWDDataException->ErrorCode  = 10611;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	//-- データ設定 --//
	RelationID[inIdx] = inData;
}

//***** 関連語意味No設定
void WDDatas::WDRelation::setRelationNo( Int32 inData, Int32 inIdx )
{	
	//-- 引数チェック --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"関連語意味Noが不正です。" );
		tmpWDDataException->ErrorCode  = 10618;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	if( RelationNo == nullptr || 
		inIdx < 0 || inIdx >= RelationNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックス指定が範囲外です。" );
		tmpWDDataException->ErrorCode  = 10618;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	//-- データ設定 --//
	RelationNo[inIdx] = inData;
}	
//***** 関連語追加
void WDDatas::WDRelation::AddRelation( Int32 inType, Int32 inID, Int32 inNo )
{
	//-- 引数チェック --//
	if( inType < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"関連語タイプが不正です。" );
		tmpWDDataException->ErrorCode  = 10612;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inID <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"関連語IDが不正です。" );
		tmpWDDataException->ErrorCode  = 10612;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	if( inNo <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"関連語意味Noが不正です。" );
		tmpWDDataException->ErrorCode  = 10612;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	if( RelationType == nullptr )
	{
		RelationType = gcnew List<Int32>();
		RelationID = gcnew List<Int32>();
		RelationNo = gcnew List<Int32>();
	}

	RelationType->Add( inType );
	RelationID->Add( inID );
	RelationNo->Add( inNo );

	if( RelationType->Count != RelationID->Count ||
		RelationType->Count != RelationNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"関連語情報に不整合が発生しました。" );
		tmpWDDataException->ErrorCode  = 10612;
		tmpWDDataException->ErrorCode2 = 4;
		throw tmpWDDataException;
	}
}

//***** 関連語削除
void WDDatas::WDRelation::RemoveRelation(int inIdx)
{
	//-- 引数チェック --//
	if( RelationType == nullptr || 
		inIdx < 0 || inIdx >= RelationType->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックス指定が範囲外です。" );
		tmpWDDataException->ErrorCode  = 10613;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	RelationType->RemoveAt( inIdx );
	RelationID->RemoveAt( inIdx );
	RelationNo->RemoveAt( inIdx );

	if( RelationType->Count != RelationID->Count ||
		RelationType->Count != RelationNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"関連語情報に不整合が発生しました。" );
		tmpWDDataException->ErrorCode  = 10613;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//***** 関連語数カウント
Int32 WDDatas::WDRelation::CountRelation( void )
{
	if( RelationType == nullptr )
	{
		return 0;
	}else{
		if( RelationType->Count != RelationID->Count )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"関連語情報のアイテム数が。" );
			tmpWDDataException->ErrorCode  = 10616;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;

		}
		return RelationType->Count;
	}
	
}
//------------------------------------------------------------------------------
//　データ操作
//------------------------------------------------------------------------------
//***** データ取得
array<Byte>^ WDDatas::WDRelation::getData( array<Byte>^ inData )
{
	array<Byte>^ rtData;
	Int32		 tmpPos;

	//-- 引数チェック --//
	if( inData != nullptr &&
		inData->Length < DataLength() )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー先データ長が短すぎます。" );
		tmpWDDataException->ErrorCode  = 10614;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( inData == nullptr )
		{
			rtData = gcnew array<Byte>( DataLength() );
		}else{
			rtData = inData;
		}

		tmpPos = 0;
	
		FJIFuncs::Int32ToArray( WordID, rtData, tmpPos );
		tmpPos += WDRELATION_WORDIDLEN;

		FJIFuncs::Int32ToArray( MeanNo, rtData, tmpPos );
		tmpPos += WDRELATION_MEANNOLEN;

		FJIFuncs::Int32ToArray( CountRelation() , rtData, tmpPos );
		tmpPos += WDRELATION_RELATIONCNTLEN;

		for( Int32 i = 0; i < CountRelation(); i++ )
		{
			FJIFuncs::Int32ToArray( RelationType[i] , rtData, tmpPos );
			tmpPos += WDRELATION_RELATIONTYPELEN;

			FJIFuncs::Int32ToArray( RelationID[i] , rtData, tmpPos );
			tmpPos += WDRELATION_RELATIONIDLEN;

			FJIFuncs::Int32ToArray( RelationNo[i] , rtData, tmpPos );
			tmpPos += WDRELATION_RELATIONNOLEN;
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データのコピーに失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10614;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- 正常終了 --//
	return rtData;
}

//***** データ設定
void WDDatas::WDRelation::setData( array<Byte>^ inData )
{
	Int32		tmpPos;
	Int32		tmpRelationCnt;

	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー元データが未設定です。" );
		tmpWDDataException->ErrorCode  = 10615;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length < sizeof( Int32 ) * 3 && 
		(inData->Length -  sizeof( Int32 ) * 3 ) % ( sizeof(Int32) *2 ) != 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー元データ長が正しくありません。" );
		tmpWDDataException->ErrorCode  = 10615;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		tmpPos = 0;

		WordID = FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDTRANS_WORDIDLEN;

		MeanNo = FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDTRANS_MEANNOLEN;

		tmpRelationCnt =  FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDTRANS_TRANSIDCNTLEN;

		//関連語リスト初期化
		if( RelationType == nullptr )
		{
			RelationType = gcnew List<Int32>();
		}else{
			RelationType->Clear();
		}
		if( RelationID == nullptr )
		{
			RelationID = gcnew List<Int32>();
		}else{
			RelationID->Clear();
		}
		if( RelationNo == nullptr )
		{
			RelationNo = gcnew List<Int32>();
		}else{
			RelationNo->Clear();
		}

		//可変長のデータ長チェック
		if( inData->Length != WDTRANS_WORDIDLEN + WDTRANS_MEANNOLEN + WDTRANS_TRANSIDCNTLEN +
							+ (WDRELATION_RELATIONTYPELEN + WDRELATION_RELATIONIDLEN + WDRELATION_RELATIONNOLEN )
												* tmpRelationCnt )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー元データ長が正しくありません。" );
			tmpWDDataException->ErrorCode  = 10615;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;

		}

		for( Int32 i = 0; i < tmpRelationCnt; i++ )
		{
			Int32 tmpRelationType;
			Int32 tmpRelationID;
			Int32 tmpRelationNo;

			tmpRelationType =  FJIFuncs::ArrayToInt32( inData, tmpPos );
			RelationType->Add( tmpRelationType );
			tmpPos += WDRELATION_RELATIONTYPELEN;

			tmpRelationID =  FJIFuncs::ArrayToInt32( inData, tmpPos );
			RelationID->Add( tmpRelationID );
			tmpPos += WDRELATION_RELATIONIDLEN;

			tmpRelationNo =  FJIFuncs::ArrayToInt32( inData, tmpPos );
			RelationNo->Add( tmpRelationNo );
			tmpPos += WDRELATION_RELATIONNOLEN;
		};

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データのコピーに失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10615;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}