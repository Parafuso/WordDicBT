//------------------------------------------------------------------------------
//	単語辞典　単語辞典データクラス　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDSegment	: 区分クラス
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//単語辞典データ用例外クラス
#include "WDDatas.h"			//単語辞典データクラス
#include "WDDatasDef.h"			//単語辞典データ定数定義
//#include "FJIsamDef.h"			//ISAM用定義ファイル

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDSegment	: 区分クラス
//------------------------------------------------------------------------------
//***** コンストラクタ１(新規データ)
WDDatas::WDSegment::WDSegment()
{
	//-- 変数定義 --//
	SegmentID = 0;
	SegmentNo = 0;
}

//***** コンストラクタ２(読込データ)
WDDatas::WDSegment::WDSegment( DataRecord^ inRec )
{

	if(inRec == nullptr )
	{
		//-- 変数定義 --//
		SegmentID = 0;
		SegmentNo = 0;
		return;
	}

	//-- 引数チェック --//
	if( inRec->getDataLength() != WDSEGMENT_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードが区分データではありません。" );
		tmpWDDataException->ErrorCode  = 10401;
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
		tmpWDDataException->ErrorCode  = 10401;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//***** デストラクタ
WDDatas::WDSegment::~WDSegment()
{
	if( Name != nullptr ) delete Name;
	if( ShortName != nullptr ) delete ShortName;
}

//------------------------------------------------------------------------------
//　データレコード操作
//------------------------------------------------------------------------------
//***** データレコード取得
DataRecord^ WDDatas::WDSegment::getRecord( void )
{
	DataRecord^ tmpRec;
	array<Byte>^ tmpDat;

	if( WDRec::getRecord() == nullptr )
	{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = gcnew DataRecord();
			tmpRec->setData( tmpDat, WDSEGMENT_LENGTH );
			WDRec::setRecord( tmpRec );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データレコード取得でエラーが発生しました。", exp );
			tmpWDDataException->ErrorCode  = 10402;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}
	}else{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = WDRec::getRecord();
			tmpRec->setData( tmpDat, WDSEGMENT_LENGTH );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データレコード取得でエラーが発生しました。", exp );
			tmpWDDataException->ErrorCode  = 10402;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}

	delete tmpDat;

	//-- 正常終了 --//
	return tmpRec;
}

//***** データレコード設定
void WDDatas::WDSegment::setRecord( DataRecord^ inRec )
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
			tmpWDDataException->ErrorCode  = 10403;
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
			tmpWDDataException->ErrorCode  = 10403;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}
}

//***** データレコード書込
void WDDatas::WDSegment::Write( void )
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
		tmpWDDataException->ErrorCode  = 10404;
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
			tmpWDDataException->ErrorCode  = 10404;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10404;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** データレコード書込
void WDDatas::WDSegment::Delete( void )
{
	FIsam^ tmpParent;

	//-- データレコードチェック --//
	if( WDRec::getRecord() == nullptr )
	{
		//--　データクリア --//
		SegmentID = 0;
		SegmentNo = 0;
		if( Name != nullptr )
		{
			delete Name;
			Name = nullptr;
		}
		if( ShortName != nullptr )
		{
			delete Name;
			ShortName = nullptr;
		}

		return;
	}

	//-- ISAMファイルチェック --//
	try
	{
		tmpParent = safe_cast<FIsam^>( WDRec::getRecord()->getParentFile() );
		if( tmpParent == nullptr )
		{
			//--　データクリア --//
			SegmentID = 0;
			SegmentNo = 0;
			if( Name != nullptr )
			{
				delete Name;
				Name = nullptr;
			}
			if( ShortName != nullptr )
			{
				delete Name;
				ShortName = nullptr;
			}

			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAMファイルが不正です。", exp );
		tmpWDDataException->ErrorCode  = 10405;
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
			tmpWDDataException->ErrorCode  = 10405;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10405;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//--　データクリア --//
	SegmentID = 0;
	SegmentNo = 0;
	if( Name != nullptr )
	{
		delete Name;
		Name = nullptr;
	}
	if( ShortName != nullptr )
	{
		delete Name;
		ShortName = nullptr;
	}

}
//------------------------------------------------------------------------------
//　情報操作
//------------------------------------------------------------------------------
//***** データ長取得
Int32 WDDatas::WDSegment::Length()
{
	return WDSEGMENT_LENGTH;
}

//***** データレコード長取得
Int32 WDDatas::WDSegment::RecLength()
{
	return DataRecord::getHeaderLength() + WDSEGMENT_LENGTH;
}
//------------------------------------------------------------------------------
//　アイテム操作
//------------------------------------------------------------------------------
//***** 区分ID取得
Int32	WDDatas::WDSegment::getSegmentID( void )
{
	return SegmentID;
}

//***** 区分No取得
Int32	WDDatas::WDSegment::getSegmentNo( void )
{
	return SegmentNo;
}

//***** 名称取得
String^ WDDatas::WDSegment::getName( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert( 0, Name );
		return inData;
	}else{
		if( Name->Length > 0 )
		{
			return Name->Trim('\0');
		}else{
			return gcnew String( L"" );
		}
	}
}

//***** 略称取得
String^ WDDatas::WDSegment::getShortName( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert( 0, ShortName );
		return inData;
	}else{
		if( ShortName->Length > 0 )
		{
			return String::Copy( ShortName )->Trim('\0');
		}else{
			return gcnew String(L"");
		}
	}
}

//------------------------------------------------------------------------------
//***** 区分ID設定
void WDDatas::WDSegment::setSegmentID( Int32 inData )
{
	//-- 引数チェック --//
	if( inData < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"区分IDが不正です。" );
		tmpWDDataException->ErrorCode  = 10406;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	SegmentID = inData;
}

//***** 区分No設定
void WDDatas::WDSegment::setSegmentNo( Int32 inData )
{
	//-- 引数チェック --//
	if( inData < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"区分Noが不正です。" );
		tmpWDDataException->ErrorCode  = 10407;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	SegmentNo = inData;
}

//***** 名称設定
void WDDatas::WDSegment::setName( String^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"名称が未設定です。" );
		tmpWDDataException->ErrorCode  = 10408;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDSEGMENT_NAMELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"名称が長すぎます。" );
		tmpWDDataException->ErrorCode  = 10408;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( Name != nullptr )
		{
			delete Name;
		}
		Name = gcnew String( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"名称の設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10408;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** 略称設定
void WDDatas::WDSegment::setShortName( String^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"略称が未設定です。" );
		tmpWDDataException->ErrorCode  = 10409;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDSEGMENT_SHORTNAMELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"略称が長すぎます。" );
		tmpWDDataException->ErrorCode  = 10409;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( ShortName != nullptr )
		{
			delete ShortName;
		}
		
		ShortName = gcnew String( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"略称の設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10409;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}

//------------------------------------------------------------------------------
//　データ操作
//------------------------------------------------------------------------------
//***** データ取得
array<Byte>^ WDDatas::WDSegment::getData( array<Byte>^ inData )
{
	array<Byte>^ rtData;
	Int32		 tmpPos;

	//-- 引数チェック --//
	if( inData != nullptr &&
		inData->Length < WDSEGMENT_LENGTH - WDSEGMENT_RESERVEDLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー先データ長が短すぎます。" );
		tmpWDDataException->ErrorCode  = 10410;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( inData == nullptr )
		{
			rtData = gcnew array<Byte>( WDSEGMENT_LENGTH );
		}else{
			rtData = inData;
		}

		tmpPos = 0;
	
		FJIFuncs::Int32ToArray( SegmentID, rtData, tmpPos );
		tmpPos += WDSEGMENT_SEGMENTIDLEN;

		FJIFuncs::Int32ToArray( SegmentNo, rtData, tmpPos );
		tmpPos += WDSEGMENT_SEGMENTNOLEN;

		FJIFuncs::StringToArray( Name, rtData, tmpPos, WDSEGMENT_NAMELEN );
		tmpPos += WDSEGMENT_NAMELEN;

		FJIFuncs::StringToArray( ShortName, rtData, tmpPos, WDSEGMENT_SHORTNAMELEN );
		tmpPos += WDSEGMENT_SHORTNAMELEN;

		for(Int32 i = 0; i < WDSEGMENT_RESERVEDLEN; i++ )
		{
			Buffer::SetByte( rtData,tmpPos, 0 );
			tmpPos++;
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データのコピーに失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10410;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- 正常終了 --//
	return rtData;
}

//***** データ設定
void WDDatas::WDSegment::setData( array<Byte>^ inData )
{
	Int32		 tmpPos;

	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー元データが未設定です。" );
		tmpWDDataException->ErrorCode  = 10411;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length != WDSEGMENT_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー元データ長が正しくありません。" );
		tmpWDDataException->ErrorCode  = 10411;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		tmpPos = 0;

		SegmentID = FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDSEGMENT_SEGMENTIDLEN;

		SegmentNo = FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDSEGMENT_SEGMENTNOLEN;

		if( Name != nullptr ) delete Name;
		Name = FJIFuncs::ArrayToString(inData, tmpPos, WDSEGMENT_NAMELEN );
		tmpPos += WDSEGMENT_NAMELEN;

		if( ShortName != nullptr ) delete ShortName;
		ShortName = FJIFuncs::ArrayToString(inData, tmpPos, WDSEGMENT_SHORTNAMELEN );
		tmpPos += WDSEGMENT_SHORTNAMELEN;

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データの設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10411;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}