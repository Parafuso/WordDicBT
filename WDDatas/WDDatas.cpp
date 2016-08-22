//------------------------------------------------------------------------------
//	単語辞典　単語辞典データクラス　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDDatas		: データレコード基本クラス
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//単語辞典データ用例外クラス
#include "WDDatas.h"			//単語辞典データクラス
//#include "FJIsamDef.h"			//ISAM用定義ファイル

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDData	:DataRecord 使用メインクラス
//------------------------------------------------------------------------------
//***** コンストラクタ１(新規データ)
/*WDDatas::WDRec::WDRec()
{
	DataRec = nullptr;
}

//***** コンストラクタ２(読込データ)
WDDatas::WDRec::WDRec( DataRecord^ inRec )
{
	DataRec = inRec;
}
*/
//------------------------------------------------------------------------------
//***** デストラクタ
WDDatas::WDRec::~WDRec()
{
	if( DataRec != nullptr )	delete DataRec;
}

//------------------------------------------------------------------------------
//　データレコード操作
//------------------------------------------------------------------------------
//***** データレコード取得
DataRecord^ WDDatas::WDRec::getRecord( void )
{
	return DataRec;
}

//***** データレコード設定
void WDDatas::WDRec::setRecord(  DataRecord^ inRec )
{
	if( inRec != nullptr )
	{
		DataRec = inRec;
	}
}

//***** データレコード書込
void WDDatas::WDRec::Write( void )
{
	FIsam^ tmpParent;

	//-- データレコードチェック --//
	if( DataRec == nullptr )
	{
		return;
	}

	//-- ISAMファイルチェック --//
	try
	{
		tmpParent = safe_cast<FIsam^>( DataRec->getParentFile() );
		if( tmpParent == nullptr )
		{
			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAMファイルが不正です。", exp );
		tmpWDDataException->ErrorCode  = 10001;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- レコード書込(自動で追加、更新判断) --//
	try
	{
		if( DataRec->getRecStat() == DataRecStat_EN::REC_NEW )
		{
			tmpParent->AddRecord( DataRec );
		}else if( DataRec->getRecStat() == DataRecStat_EN::REC_OLD ){
			tmpParent->UpdateRecord( DataRec );
		}else{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"レコード削除はできません。" );
			tmpWDDataException->ErrorCode  = 10001;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10001;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** データレコード削除
void WDDatas::WDRec::Delete( void )
{
	FIsam^ tmpParent;

	//-- データレコードチェック --//
	if( DataRec == nullptr )
	{
		return;
	}

	//-- ISAMファイルチェック --//
	try
	{
		tmpParent = safe_cast<FIsam^>( DataRec->getParentFile() );
		if( tmpParent == nullptr )
		{
			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAMファイルが不正です。", exp );
		tmpWDDataException->ErrorCode  = 10002;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- レコード削除 --//
	try
	{
		if( DataRec->getRecStat() == DataRecStat_EN::REC_NEW )
		{
			;
		}if( DataRec->getRecStat() == DataRecStat_EN::REC_OLD )
		{
			tmpParent->DeleteRecord( DataRec );
			delete DataRec;
			DataRec = nullptr;
		}else{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"このデータレコードは削除できません。" );
			tmpWDDataException->ErrorCode  = 10002;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10002;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//　情報操作
//------------------------------------------------------------------------------
//***** データ部長取得
Int32 WDDatas::WDRec::Length()
{
	return 0;
}

//***** データレコード長取得
Int32 WDDatas::WDRec::RecLength()
{
	if( DataRec == nullptr )
	{
		return 0;
	}else{
		return DataRec->getRecLength();
	}
}