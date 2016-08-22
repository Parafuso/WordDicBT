//------------------------------------------------------------------------------
//	単語辞典　単語辞典データクラス　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDGroup		: 分類クラス
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//単語辞典データ用例外クラス
#include "WDDatas.h"			//単語辞典データクラス
#include "WDDatasDef.h"			//単語辞典データ定数定義
//#include "FJIsamDef.h"			//ISAM用定義ファイル

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDGroup	: 分類クラス
//------------------------------------------------------------------------------
//***** コンストラクタ１(新規データ)
WDDatas::WDGroup::WDGroup()
{
	//-- 変数定義 --//
	GroupGt = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
	GroupLt = gcnew array<Byte>(WDGROUP_GROUPLTLEN);

}

//***** コンストラクタ２(読込データ)
WDDatas::WDGroup::WDGroup( DataRecord^ inRec )
{

	if(inRec == nullptr )
	{
		//-- 変数定義 --//
		GroupGt = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
		GroupLt = gcnew array<Byte>(WDGROUP_GROUPLTLEN);
		return;
	}

	//-- 引数チェック --//
	if( inRec->getDataLength() != WDGROUP_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードが分類データではありません。" );
		tmpWDDataException->ErrorCode  = 10301;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	
	//-- 変数定義 --//
	GroupGt = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
	GroupLt = gcnew array<Byte>(WDGROUP_GROUPLTLEN);

	//-- データ設定 --//
	try
	{
		setRecord( inRec );
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データ設定でエラーが発生しました。", exp );
		tmpWDDataException->ErrorCode  = 10301;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//***** デストラクタ
WDDatas::WDGroup::~WDGroup()
{
	delete GroupGt;
	delete GroupLt;
	if( Name != nullptr ) delete Name;
	if( ShortName != nullptr ) delete ShortName;
}

//------------------------------------------------------------------------------
//　データレコード操作
//------------------------------------------------------------------------------
//***** データレコード取得
DataRecord^ WDDatas::WDGroup::getRecord( void )
{
	DataRecord^ tmpRec;
	array<Byte>^ tmpDat;

	if( WDRec::getRecord() == nullptr )
	{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = gcnew DataRecord();
			tmpRec->setData( tmpDat, WDGROUP_LENGTH );
			WDRec::setRecord( tmpRec );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データレコード取得でエラーが発生しました。", exp );
			tmpWDDataException->ErrorCode  = 10302;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}
	}else{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = WDRec::getRecord();
			tmpRec->setData( tmpDat, WDGROUP_LENGTH );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データレコード取得でエラーが発生しました。", exp );
			tmpWDDataException->ErrorCode  = 10302;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}

	delete tmpDat;

	//-- 正常終了 --//
	return tmpRec;
}

//***** データレコード設定
void WDDatas::WDGroup::setRecord( DataRecord^ inRec )
{
	if( inRec != nullptr )
	{
		try
		{
			array<Byte>^ tmpDat;
			tmpDat = inRec->getData( nullptr );
			setData( tmpDat );
			WDRec::setRecord( inRec );
			delete tmpDat;
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データレコード設定でエラーが発生しました。", exp );
			tmpWDDataException->ErrorCode  = 10303;
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
			tmpWDDataException->ErrorCode  = 10303;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}
}

//***** データレコード書込
void WDDatas::WDGroup::Write( void )
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
		tmpWDDataException->ErrorCode  = 10304;
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
			tmpWDDataException->ErrorCode  = 10304;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10304;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** データレコード書込
void WDDatas::WDGroup::Delete( void )
{
	FIsam^ tmpParent;

	//-- データレコードチェック --//
	if( WDRec::getRecord() == nullptr )
	{
		//--　データクリア --//
		GroupGt[0] = 0;
		GroupGt[1] = 0;
		GroupLt[0] = 0;
		GroupLt[1] = 0;
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
			GroupGt[0] = 0;
			GroupGt[1] = 0;
			GroupLt[0] = 0;
			GroupLt[1] = 0;
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
		tmpWDDataException->ErrorCode  = 10305;
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
			tmpWDDataException->ErrorCode  = 10305;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10305;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//--　データクリア --//
	GroupGt[0] = 0;
	GroupGt[1] = 0;
	GroupLt[0] = 0;
	GroupLt[1] = 0;
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
Int32 WDDatas::WDGroup::Length()
{
	return WDGROUP_LENGTH;
}

//***** データレコード長取得
Int32 WDDatas::WDGroup::RecLength()
{
	return DataRecord::getHeaderLength() + WDGROUP_LENGTH;
}
//------------------------------------------------------------------------------
//　アイテム操作
//------------------------------------------------------------------------------
//***** 分類大取得
array<Byte>^ WDDatas::WDGroup::getGroupGt( array<Byte>^ inData )
{
	if( inData != nullptr )
	{
		if( inData->Length < WDGROUP_GROUPGTLEN )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"コピー先データ長が短すぎます。" );
			tmpWDDataException->ErrorCode  = 10306;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}

		try
		{
			Buffer::BlockCopy( GroupGt, 0, inData, 0, WDGROUP_GROUPGTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データのコピーに失敗しました。", exp );
			tmpWDDataException->ErrorCode  = 10306;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
		return inData;

	}else{

		array<Byte>^ rtData = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
		try
		{
			Buffer::BlockCopy( GroupGt, 0, rtData, 0, WDGROUP_GROUPGTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データのコピーに失敗しました。", exp );
			tmpWDDataException->ErrorCode  = 10306;
			tmpWDDataException->ErrorCode2 = 3;
			throw tmpWDDataException;
		}

		return rtData;
	}
}

//***** 分類小取得
array<Byte>^ WDDatas::WDGroup::getGroupLt( array<Byte>^ inData )
{
	if( inData != nullptr )
	{
		if( inData->Length < WDGROUP_GROUPLTLEN )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"コピー先データ長が短すぎます。" );
			tmpWDDataException->ErrorCode  = 10307;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}

		try
		{
			Buffer::BlockCopy( GroupLt, 0, inData, 0, WDGROUP_GROUPLTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データのコピーに失敗しました。", exp );
			tmpWDDataException->ErrorCode  = 10307;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
		return inData;

	}else{

		array<Byte>^ rtData = gcnew array<Byte>(WDGROUP_GROUPLTLEN);
		try
		{
			Buffer::BlockCopy( GroupLt, 0, rtData, 0, WDGROUP_GROUPLTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データのコピーに失敗しました。", exp );
			tmpWDDataException->ErrorCode  = 10307;
			tmpWDDataException->ErrorCode2 = 3;
			throw tmpWDDataException;
		}

		return rtData;
	}
}

//***** 名称取得
String^ WDDatas::WDGroup::getName( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert(0, Name );
		return inData;
	}else{
		if( Name->Length > 0 )
		{
			return Name->Trim('\0');
		}else{
			return gcnew String(L"");
		}
	}
}

//***** 略称取得
String^ WDDatas::WDGroup::getShortName( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert(0, ShortName );
		return inData;
	}else{
		if( ShortName->Length > 0 )
		{
			return ShortName->Trim('\0');
		}else{
			return gcnew String( L"" );
		}
	}
}

//------------------------------------------------------------------------------
//***** 分類大設定
void WDDatas::WDGroup::setGroupGt( array<Byte>^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類大が未設定です。" );
		tmpWDDataException->ErrorCode  = 10308;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length < WDGROUP_GROUPGTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類大が短すぎます。" );
		tmpWDDataException->ErrorCode  = 10308;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		Buffer::BlockCopy( inData, 0, GroupGt, 0, WDGROUP_GROUPGTLEN );
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類大の設定にしパイしました。", exp );
		tmpWDDataException->ErrorCode  = 10308;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}		

//***** 分類小設定
void WDDatas::WDGroup::setGroupLt( array<Byte>^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類小が未設定です。" );
		tmpWDDataException->ErrorCode  = 10309;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length < WDGROUP_GROUPLTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類小が短すぎます。" );
		tmpWDDataException->ErrorCode  = 10309;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		Buffer::BlockCopy( inData, 0, GroupLt, 0, WDGROUP_GROUPLTLEN );
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類小の設定にしパイしました。", exp );
		tmpWDDataException->ErrorCode  = 10309;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}							

//***** 名称設定
void WDDatas::WDGroup::setName( String^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"名称が未設定です。" );
		tmpWDDataException->ErrorCode  = 10310;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDGROUP_NAMELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"名称が長すぎます。" );
		tmpWDDataException->ErrorCode  = 10310;
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
		Name = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"名称の設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10310;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** 略称設定
void WDDatas::WDGroup::setShortName( String^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"略称が未設定です。" );
		tmpWDDataException->ErrorCode  = 10311;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDGROUP_SHORTNAMELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"略称が長すぎます。" );
		tmpWDDataException->ErrorCode  = 10311;
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
		ShortName = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"略称の設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10311;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}

//------------------------------------------------------------------------------
//　データ操作
//------------------------------------------------------------------------------
//***** データ取得
array<Byte>^ WDDatas::WDGroup::getData( array<Byte>^ inData )
{
	array<Byte>^ rtData;
	Int32		 tmpPos;
	
	//-- 引数チェック --//
	if( inData != nullptr &&
		inData->Length < WDGROUP_LENGTH - WDGROUP_RESERVEDLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー先データ長が短すぎます。" );
		tmpWDDataException->ErrorCode  = 10312;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( inData == nullptr )
		{
			rtData = gcnew array<Byte>( WDGROUP_LENGTH );
		}else{
			rtData = inData;
		}

		tmpPos = 0;
	
		//分類大
		Buffer::BlockCopy( GroupGt, 0, rtData, tmpPos, WDGROUP_GROUPGTLEN );
		tmpPos += WDGROUP_GROUPGTLEN;

		//分類小
		Buffer::BlockCopy( GroupLt, 0, rtData, tmpPos, WDGROUP_GROUPLTLEN );
		tmpPos += WDGROUP_GROUPLTLEN;

		//名称
		FJIFuncs::StringToArray( Name, rtData, tmpPos, WDGROUP_NAMELEN );
		tmpPos += WDGROUP_NAMELEN;

		//略称
		FJIFuncs::StringToArray( ShortName, rtData, tmpPos, WDGROUP_SHORTNAMELEN );
		tmpPos += WDGROUP_SHORTNAMELEN;

		//Reserve
		for(Int32 i = 0; i < WDGROUP_RESERVEDLEN; i++ )
		{
			Buffer::SetByte( rtData,tmpPos, 0 );
			tmpPos++;
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データのコピーに失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10312;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- 正常終了 --//
	return rtData;
}

//***** データ設定
void WDDatas::WDGroup::setData( array<Byte>^ inData )
{
	Int32		 tmpPos;

	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー元データが未設定です。" );
		tmpWDDataException->ErrorCode  = 10313;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length != WDGROUP_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー元データ長が正しくありません。" );
		tmpWDDataException->ErrorCode  = 10313;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		tmpPos = 0;

		Buffer::BlockCopy( inData, tmpPos, GroupGt, 0, WDGROUP_GROUPGTLEN );
		tmpPos += WDGROUP_GROUPGTLEN;

		Buffer::BlockCopy(  inData, tmpPos, GroupLt, 0, WDGROUP_GROUPLTLEN );
		tmpPos += WDGROUP_GROUPLTLEN;

		if( Name != nullptr ) delete Name;
		Name =  FJIFuncs::ArrayToString(inData, tmpPos, WDGROUP_NAMELEN );
		tmpPos += WDGROUP_NAMELEN;

		if( ShortName != nullptr ) delete ShortName;
		ShortName = FJIFuncs::ArrayToString(inData, tmpPos, WDGROUP_SHORTNAMELEN );
		tmpPos += WDGROUP_SHORTNAMELEN;

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データの設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10313;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}