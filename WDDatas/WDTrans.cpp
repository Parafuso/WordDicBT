//------------------------------------------------------------------------------
//	単語辞典　単語辞典データクラス　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDTrans		: 翻訳クラス
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//単語辞典データ用例外クラス
#include "WDDatas.h"			//単語辞典データクラス
#include "WDDatasDef.h"			//単語辞典データ定数定義
//#include "FJIsamDef.h"			//ISAM用定義ファイル

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDTrans		: 翻訳クラス
//------------------------------------------------------------------------------
//***** コンストラクタ１(新規データ)
WDDatas::WDTrans::WDTrans()
 //: WDRec()
{
	//-- 変数定義 --//
	WordID = 0;
	MeanNo = 0;

	TransID = gcnew List<Int32>();
	TransNo = gcnew List<Int32>();
}

//***** コンストラクタ２(読込データ)
WDDatas::WDTrans::WDTrans( DataRecord^ inRec )
{

	//-- 変数定義 --//
	WordID = 0;
	MeanNo = 0;
	TransID = gcnew List<Int32>();
	TransNo = gcnew List<Int32>();

	if(inRec == nullptr )
	{
		return;
	}

	//-- 引数チェック --//
	if( inRec->getDataLength() < WDTRANS_WORDIDLEN + WDTRANS_MEANNOLEN + 
					WDTRANS_TRANSIDCNTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードのデータが短すぎます。" );
		tmpWDDataException->ErrorCode  = 10501;
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
		tmpWDDataException->ErrorCode  = 10501;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//***** デストラクタ
WDDatas::WDTrans::~WDTrans()
{
	if( TransID != nullptr ) delete TransID;
	if( TransNo != nullptr ) delete TransNo;
}

//------------------------------------------------------------------------------
//　データレコード操作
//------------------------------------------------------------------------------
//***** データレコード取得
DataRecord^ WDDatas::WDTrans::getRecord( void )
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
			tmpWDDataException->ErrorCode  = 10502;
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
			tmpWDDataException->ErrorCode  = 10502;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}

	delete tmpDat;

	//-- 正常終了 --//
	return tmpRec;
}

//***** データレコード設定
void WDDatas::WDTrans::setRecord(  DataRecord^ inRec )
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
			tmpWDDataException->ErrorCode  = 10503;
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
			tmpWDDataException->ErrorCode  = 10503;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}
}

//***** データレコード書込
void WDDatas::WDTrans::Write( void )
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
		tmpWDDataException->ErrorCode  = 10504;
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
			tmpWDDataException->ErrorCode  = 10504;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10504;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** データレコード書込
void WDDatas::WDTrans::Delete( void )
{
	FIsam^ tmpParent;

	//-- データレコードチェック --//
	if( WDRec::getRecord() == nullptr )
	{
		//--　データクリア --//
		WordID = 0;
		MeanNo = 0;
		TransID->Clear();

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
			TransID->Clear();

			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAMファイルが不正です。", exp );
		tmpWDDataException->ErrorCode  = 10505;
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
			tmpWDDataException->ErrorCode  = 10505;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10505;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//--　データクリア --//
	WordID = 0;
	MeanNo = 0;
	TransID->Clear();

}
//------------------------------------------------------------------------------
//　情報操作
//------------------------------------------------------------------------------
//***** データ部長取得
Int32 WDDatas::WDTrans::DataLength( void )
{
	Int32 tmpTransIDSize;

	//-- 可変長部分のサイズを取得
	if( TransID == nullptr )
	{
		tmpTransIDSize = 0;
	}else{
		tmpTransIDSize = ( WDTRANS_TRANSIDLEN + WDTRANS_TRANSNOLEN ) * TransID->Count;
	}

	return	WDTRANS_WORDIDLEN +
			WDTRANS_MEANNOLEN +
			WDTRANS_TRANSIDCNTLEN +
			tmpTransIDSize;
}

//***** データレコード長取得
Int32 WDDatas::WDTrans::RecLength( void )
{
	return DataRecord::getHeaderLength() + DataLength();
}

//------------------------------------------------------------------------------
//　アイテム操作
//------------------------------------------------------------------------------
//***** 単語ID取得
Int32 WDDatas::WDTrans::getWordID( void )
{
	return WordID;
}

//***** 意味No取得
Int32 WDDatas::WDTrans::getMeanNo( void )
{
	return MeanNo;
}



//***** 翻訳ID取得
Int32 WDDatas::WDTrans::getTransID( Int32 inIdx )
{
	if( TransID == nullptr ) return -1;

	if( inIdx < 0 || inIdx >= TransID->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックス指定が範囲外です。" );
		tmpWDDataException->ErrorCode  = 10506;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	return TransID[inIdx];
}

//***** 翻訳意味No取得
Int32 WDDatas::WDTrans::getTransNo( Int32 inIdx )
{
	if( TransNo == nullptr ) return -1;

	if( inIdx < 0 || inIdx >= TransNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックス指定が範囲外です。" );
		tmpWDDataException->ErrorCode  = 10514;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	return TransNo[inIdx];
}

//------------------------------------------------------------------------------
//***** 単語ID設定
void WDDatas::WDTrans::setWordID( Int32 inData )
{
	//-- 引数チェック --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"単語IDが不正です。" );
		tmpWDDataException->ErrorCode  = 10507;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	WordID = inData;
}

//***** 単語ID設定
void WDDatas::WDTrans::setMeanNo( Int32 inData )
{
	//-- 引数チェック --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味Noが不正です。" );
		tmpWDDataException->ErrorCode  = 10508;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	MeanNo = inData;
}


//***** 翻訳ID設定
void WDDatas::WDTrans::setTransID( Int32 inData, Int32 inIdx )
{	
	//-- 引数チェック --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"翻訳IDが不正です。" );
		tmpWDDataException->ErrorCode  = 10509;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	if( TransID == nullptr || 
		inIdx < 0 || inIdx >= TransID->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックス指定が範囲外です。" );
		tmpWDDataException->ErrorCode  = 10509;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	//-- データ設定 --//
	TransID[inIdx] = inData;
}			

//***** 翻訳No設定
void WDDatas::WDTrans::setTransNo( Int32 inData, Int32 inIdx )
{	
	//-- 引数チェック --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"翻訳意味Noが不正です。" );
		tmpWDDataException->ErrorCode  = 10515;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	if( TransID == nullptr || 
		inIdx < 0 || inIdx >= TransID->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックス指定が範囲外です。" );
		tmpWDDataException->ErrorCode  = 10515;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	//-- データ設定 --//
	TransNo[inIdx] = inData;
}			

//***** 翻訳ID追加
void WDDatas::WDTrans::AddTransID( Int32 inID, Int32 inNo )
{
	//-- 引数チェック --//
	if( inID <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"翻訳IDが不正です。" );
		tmpWDDataException->ErrorCode  = 10510;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	if( inNo <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"翻訳意味Noが不正です。" );
		tmpWDDataException->ErrorCode  = 10510;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ追加 --//
	if( TransID == nullptr )
	{
		TransID = gcnew List<Int32>();
	}
	TransID->Add( inID );

	if( TransNo == nullptr )
	{
		TransNo = gcnew List<Int32>();
	}
	TransNo->Add( inNo );

	//-- 整合チェック --//
	if( TransID->Count != TransNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"翻訳情報が不整合です。" );
		tmpWDDataException->ErrorCode  = 10510;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}


}

//***** 翻訳ID削除
void WDDatas::WDTrans::RemoveTransID( Int32 inIdx)
{
	//-- 引数チェック --//
	if( TransID == nullptr || 
		inIdx < 0 || inIdx >= TransID->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックス指定が範囲外です。" );
		tmpWDDataException->ErrorCode  = 10511;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- 整合チェック --//
	if( TransID->Count != TransNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"翻訳情報が不整合です。" );
		tmpWDDataException->ErrorCode  = 10511;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	TransID->RemoveAt( inIdx );
	TransNo->RemoveAt( inIdx );

}

//***** 翻訳ID数カウント
Int32 WDDatas::WDTrans::CountTransID( void )
{
	if( TransID == nullptr )
	{
		return 0;
	}else{
		return TransID->Count;
	}
	
}
//------------------------------------------------------------------------------
//　データ操作
//------------------------------------------------------------------------------
//***** データ取得
array<Byte>^ WDDatas::WDTrans::getData( array<Byte>^ inData )
{
	array<Byte>^ rtData;
	Int32		 tmpPos;

	//-- 引数チェック --//
	if( inData != nullptr &&
		inData->Length < DataLength() )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー先データ長が短すぎます。" );
		tmpWDDataException->ErrorCode  = 10512;
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
		tmpPos += WDTRANS_WORDIDLEN;

		FJIFuncs::Int32ToArray( MeanNo, rtData, tmpPos );
		tmpPos += WDTRANS_MEANNOLEN;

		FJIFuncs::Int32ToArray( CountTransID() , rtData, tmpPos );
		tmpPos += WDTRANS_TRANSIDCNTLEN;

		for( Int32 i = 0; i < TransID->Count; i++ )
		{
			FJIFuncs::Int32ToArray( TransID[i] ,rtData, tmpPos );
			tmpPos += WDTRANS_TRANSIDLEN;

			FJIFuncs::Int32ToArray( TransNo[i] ,rtData, tmpPos );
			tmpPos += WDTRANS_TRANSNOLEN;
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データのコピーに失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10512;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- 正常終了 --//
	return rtData;
}

//***** データ設定
void WDDatas::WDTrans::setData( array<Byte>^ inData )
{
	Int32		tmpPos;
	Int32		tmpTransIDCnt;

	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー元データが未設定です。" );
		tmpWDDataException->ErrorCode  = 10513;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length < sizeof( Int32 ) * 3 && 
		(inData->Length -  sizeof( Int32 ) * 3 ) % sizeof(Int32) != 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー元データ長が正しくありません。" );
		tmpWDDataException->ErrorCode  = 10513;
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

		tmpTransIDCnt =  FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDTRANS_TRANSIDCNTLEN;

		if( TransID == nullptr )
		{
			TransID = gcnew List<Int32>();
		}else{
			TransID->Clear();
		}

		if( TransNo == nullptr )
		{
			TransNo = gcnew List<Int32>();
		}else{
			TransNo->Clear();
		}

		//可変長のデータ長チェック
		if( inData->Length != sizeof( Int32) *3 + 
			( WDTRANS_TRANSIDLEN + WDTRANS_TRANSNOLEN ) * tmpTransIDCnt )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー元データ長が正しくありません。" );
			tmpWDDataException->ErrorCode  = 10513;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;

		}

		for( Int32 i = 0; i < tmpTransIDCnt; i++ )
		{
			Int32 tmpTransID;
			Int32 tmpTransNo;

			tmpTransID =  FJIFuncs::ArrayToInt32( inData, tmpPos );
			TransID->Add( tmpTransID );
			tmpPos += WDTRANS_TRANSIDLEN;

			tmpTransNo =  FJIFuncs::ArrayToInt32( inData, tmpPos );
			TransNo->Add( tmpTransNo );
			tmpPos += WDTRANS_TRANSNOLEN;

		};

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データのコピーに失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10513;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}