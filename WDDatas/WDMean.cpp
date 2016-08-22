//------------------------------------------------------------------------------
//	単語辞典　単語辞典データクラス　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDMean		: 意味クラス
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//単語辞典データ用例外クラス
#include "WDDatas.h"			//単語辞典データクラス
#include "WDDatasDef.h"			//単語辞典データ定数定義
//#include "FJIsamDef.h"			//ISAM用定義ファイル

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDMean	: 意味クラス
//------------------------------------------------------------------------------
//***** コンストラクタ１(新規データ)
WDDatas::WDMean::WDMean()
 //: WDRec()
{
	//-- 比較処理 --//
	if( WDMeanGrpComp == nullptr ) WDMeanGrpComp = gcnew WDMeanGrpComparer();

	//-- 変数定義 --//
	WordID = 0;
	MeanNo = 0;
	MeanGroup = gcnew List<WDMeanGroup^>();
	Speech = 0;
	Rank = 0;

	WDRec::setRecord( nullptr );

}

//***** コンストラクタ２(読込データ)
WDDatas::WDMean::WDMean( DataRecord^ inRec )
{

	//-- 比較処理 --//
	if( WDMeanGrpComp == nullptr ) WDMeanGrpComp = gcnew WDMeanGrpComparer();

	//-- 変数定義 --//
	WordID = 0;
	MeanNo = 0;
	MeanGroup = gcnew List<WDMeanGroup^>();
	Speech = 0;
	Rank = 0;
	WDRec::setRecord( nullptr );

	if(inRec == nullptr )
	{
		return;
	}

	//-- 引数チェック --//
	if( inRec->getDataLength() != WDMEAN_LENGTH &&
		inRec->getDataLength() != WDMEAN_SHORT_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードが意味データではありません。" );
		tmpWDDataException->ErrorCode  = 10201;
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
		tmpWDDataException->ErrorCode  = 10201;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//***** デストラクタ
WDDatas::WDMean::~WDMean()
{
	WDMeanGroup^ tmpMeanGroup;

	for( Int32 i = 0; i < MeanGroup->Count; i++ )
	{
		tmpMeanGroup = MeanGroup[i];
		if( tmpMeanGroup != nullptr )
		{
			if( tmpMeanGroup->GroupGt != nullptr ) delete tmpMeanGroup->GroupGt;
			if( tmpMeanGroup->GroupLt != nullptr ) delete tmpMeanGroup->GroupLt;
			delete tmpMeanGroup;
		}
	}
	delete MeanGroup;
	if( Mean != nullptr ) delete Mean;
	if( Example != nullptr ) delete Example;
}

//------------------------------------------------------------------------------
//　データレコード操作
//------------------------------------------------------------------------------
//***** データレコード取得
DataRecord^ WDDatas::WDMean::getRecord( void )
{
	return getRecord( 0 );
}

DataRecord^ WDDatas::WDMean::getRecord( Int32 inIdx )
{
	DataRecord^		tmpRec;
	WDMeanGroup^	tmpWDMeanGroup;
	array<Byte>^	rtData;
	Int32			tmpPos;

	//-- 分類情報チェック --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味データが存在しません。" );
		tmpWDDataException->ErrorCode  = 10202;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	//-- 引数チェック --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックスの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 10202;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	try
	{
		//-- 分類選択 --//
		tmpWDMeanGroup = MeanGroup[inIdx];
		tmpRec = tmpWDMeanGroup->DataRec;
		if( tmpRec == nullptr )
		{
			tmpRec = gcnew DataRecord();
		}

		//-- データ設定 --//
		if( tmpWDMeanGroup->MeanFlg == 0  )
		{
			rtData = gcnew array<Byte>( WDMEAN_LENGTH );
		}else{
			rtData = gcnew array<Byte>( WDMEAN_SHORT_LENGTH );
		}

		tmpPos = 0;

		//単語ID
		FJIFuncs::Int32ToArray( WordID, rtData, tmpPos );
		tmpPos += WDMEAN_WORDIDLEN;
		//意味No
		FJIFuncs::Int32ToArray( MeanNo, rtData, tmpPos );
		tmpPos += WDMEAN_MEANNOLEN;

		//意味Flg
		FJIFuncs::Int32ToArray( tmpWDMeanGroup->MeanFlg, rtData, tmpPos );
		tmpPos += WDMEAN_MEANFLGLEN;
		//分類大
		Buffer::BlockCopy( tmpWDMeanGroup->GroupGt, 0, rtData, tmpPos, WDMEAN_GROUPGTLEN );
		tmpPos += WDMEAN_GROUPGTLEN;
		//分類小
		Buffer::BlockCopy( tmpWDMeanGroup->GroupLt, 0, rtData, tmpPos, WDMEAN_GROUPLTLEN );
		tmpPos += WDMEAN_GROUPLTLEN;
		//分類順位
		FJIFuncs::Int32ToArray( tmpWDMeanGroup->GroupRank, rtData, tmpPos );
		tmpPos += WDMEAN_GROUPRANKLEN;


		if( tmpWDMeanGroup->MeanFlg == 0 )
		{

			//品詞
			rtData[tmpPos] = Speech;
			tmpPos += WDMEAN_SPEECHLEN;
			//ランク
			FJIFuncs::Int32ToArray( Rank, rtData, tmpPos );
			tmpPos += WDMEAN_RANKLEN;
			//意味
			FJIFuncs::StringToArray( Mean, rtData, tmpPos, WDMEAN_MEANLEN );
			tmpPos += WDMEAN_MEANLEN;
			//例文
			FJIFuncs::StringToArray( Example, rtData, tmpPos, WDMEAN_EXAMPLELEN );
			tmpPos += WDMEAN_EXAMPLELEN;

			//予約
			for(Int32 i = 0; i < WDMEAN_RESERVEDLEN; i++ )
			{
				Buffer::SetByte( rtData,tmpPos, 0 );
				tmpPos++;
			}

			//-- レコードにデータセット( MeanFlg 0 ) --//
			tmpRec->setData( rtData, WDMEAN_LENGTH );
		}else{
			//-- レコードにデータセット( MeanFlg 1以上 ) --//
			tmpRec->setData( rtData, WDMEAN_SHORT_LENGTH );
		}

		
	}catch( Exception^ exp ){
		if( rtData != nullptr ) delete rtData;

		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコード取得でエラーが発生しました。", exp );
		tmpWDDataException->ErrorCode  = 10202;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
	//-- 正常終了 --//
	return tmpRec;
}

//***** データレコード設定
void WDDatas::WDMean::setRecord( DataRecord^ inRec )
{
	Int32			tmpWordID;
	Int32			tmpMeanNo;
	WDMeanGroup^	tmpWDMeanGroup;
	array<Byte>^	tmpDat;
	Int32			tmpPos;

	//-- 引数チェック --//
	if( inRec == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"入力データレコードが設定されていません。" );
		tmpWDDataException->ErrorCode  = 10203;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	try
	{
		tmpDat = inRec->getData( nullptr );

		if( tmpDat->Length != WDMEAN_LENGTH &&
			tmpDat->Length != WDMEAN_SHORT_LENGTH )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"コピー元データ長が正しくありません。" );
			tmpWDDataException->ErrorCode  = 10203;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}

		tmpPos = 0;

		//単語ID
		tmpWordID = FJIFuncs::ArrayToInt32( tmpDat, tmpPos );
		tmpPos += WDMEAN_WORDIDLEN;
		//意味No
		tmpMeanNo = FJIFuncs::ArrayToInt32( tmpDat, tmpPos );
		tmpPos += WDMEAN_MEANNOLEN;

		if( MeanGroup->Count != 0 && 
			( tmpWordID != WordID || tmpMeanNo != MeanNo ) )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"該当する意味データではありません。" );
			tmpWDDataException->ErrorCode  = 10203;
			tmpWDDataException->ErrorCode2 = 3;
			throw tmpWDDataException;
	
		}
		WordID = tmpWordID;
		MeanNo = tmpMeanNo;

		//意味グループ
		tmpWDMeanGroup = gcnew WDMeanGroup();

		//意味フラグ
		tmpWDMeanGroup->MeanFlg = FJIFuncs::ArrayToInt32( tmpDat, tmpPos );
		tmpPos += WDMEAN_MEANFLGLEN;
	
		//分類大
		tmpWDMeanGroup->GroupGt = gcnew array<Byte>(WDMEAN_GROUPGTLEN); 
		Buffer::BlockCopy( tmpDat, tmpPos, tmpWDMeanGroup->GroupGt, 0, WDMEAN_GROUPGTLEN );
		tmpPos += WDMEAN_GROUPGTLEN;
		//分類小
		tmpWDMeanGroup->GroupLt = gcnew array<Byte>(WDMEAN_GROUPLTLEN); 
		Buffer::BlockCopy( tmpDat, tmpPos, tmpWDMeanGroup->GroupLt, 0, WDMEAN_GROUPLTLEN );
		tmpPos += WDMEAN_GROUPLTLEN;
		//分類順位
		tmpWDMeanGroup->GroupRank = FJIFuncs::ArrayToInt32( tmpDat, tmpPos );
		tmpPos += WDMEAN_GROUPRANKLEN;

		if( addMeanGrp( tmpWDMeanGroup ) == 0 )
		{
			tmpWDMeanGroup->DataRec = inRec;
			if( tmpWDMeanGroup->MeanFlg > 0 )
			{
				if( inRec->getDataLength() != WDMEAN_SHORT_LENGTH )
				{
					WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
						L"データ長が正しくありません。" );
					tmpWDDataException->ErrorCode  = 10203;
					tmpWDDataException->ErrorCode2 = 4;
					throw tmpWDDataException;
				}
			}else{
				if( inRec->getDataLength() != WDMEAN_LENGTH )
				{
					WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
						L"データ長が正しくありません。" );
					tmpWDDataException->ErrorCode  = 10203;
					tmpWDDataException->ErrorCode2 = 5;
					throw tmpWDDataException;
				}

				//品詞
				Speech = tmpDat[tmpPos];
				tmpPos += WDMEAN_SPEECHLEN;
				//ランク
				Rank = FJIFuncs::ArrayToInt32( tmpDat, tmpPos );
				tmpPos += WDMEAN_RANKLEN;
				//意味
				if( Mean != nullptr ) delete Mean;
				Mean = FJIFuncs::ArrayToString( tmpDat, tmpPos, WDMEAN_MEANLEN );
				tmpPos += WDMEAN_MEANLEN;
				//例文
				if( Example != nullptr ) delete Example;
				Example = FJIFuncs::ArrayToString( tmpDat, tmpPos, WDMEAN_EXAMPLELEN );
				tmpPos += WDMEAN_EXAMPLELEN;
	
			}
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコード設定時にエラーが発生しました。", exp );
		tmpWDDataException->ErrorCode  = 10203;
		tmpWDDataException->ErrorCode2 = 6;
		throw tmpWDDataException;

	}finally{
		if( tmpDat != nullptr ) delete tmpDat;
	}

}

//***** データレコード書込
void WDDatas::WDMean::Write( void )
{
	Write( 0 );
}

void WDDatas::WDMean::Write( Int32 inIdx )
{
	DataRecord^ tmpRec;
	FIsam^ tmpParent;

	//-- 分類情報チェック --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味データが存在しません。" );
		tmpWDDataException->ErrorCode  = 10204;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	//-- 引数チェック --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックスの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 10204;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データレコードチェック --//
	if( MeanGroup[inIdx]->DataRec == nullptr )
	{
		return;
	}

	//-- ISAMファイルチェック --//
	try
	{
		tmpParent = safe_cast<FIsam^>( MeanGroup[inIdx]->DataRec->getParentFile() );
		if( tmpParent == nullptr )
		{
			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAMファイルが不正です。", exp );
		tmpWDDataException->ErrorCode  = 10204;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//-- レコード書込(自動で追加、更新判断) --//
	try
	{
		tmpRec = getRecord( inIdx );
		if( tmpRec->getRecStat() == DataRecStat_EN::REC_NEW )
		{
			tmpParent->AddRecord( tmpRec );
		}else if( tmpRec->getRecStat() == DataRecStat_EN::REC_OLD ){
			tmpParent->UpdateRecord( tmpRec );
		}else{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"レコード書込はできません。" );
			tmpWDDataException->ErrorCode  = 10204;
			tmpWDDataException->ErrorCode2 = 4;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10204;
		tmpWDDataException->ErrorCode2 = 5;
		throw tmpWDDataException;
	}
}

//***** データレコード書込
void WDDatas::WDMean::Delete( void )
{
	Delete( 0 );
}

void WDDatas::WDMean::Delete( Int32 inIdx )
{
	DataRecord^ tmpRec;
	FIsam^ tmpParent;

	//-- 分類情報チェック --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味データが存在しません。" );
		tmpWDDataException->ErrorCode  = 10205;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	//-- 引数チェック --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックスの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 10205;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//--Isamレコード削除 --//
	try
	{
		tmpRec = MeanGroup[inIdx]->DataRec;
		if( tmpRec != nullptr )
		{
			tmpParent = safe_cast<FIsam^>( WDRec::getRecord()->getParentFile() );
			if( tmpParent != nullptr &&
				WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_OLD )
			{
				tmpParent->DeleteRecord( getRecord() );
			}
			delete tmpRec;
		}
		
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAMデータ削除に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10205;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//--　データクリア --//
	try
	{
		//-- 分類削除 --//
		if( MeanGroup[inIdx]->GroupGt != nullptr ) delete MeanGroup[inIdx]->GroupGt;
		if( MeanGroup[inIdx]->GroupLt != nullptr ) delete MeanGroup[inIdx]->GroupLt;
		delete MeanGroup[inIdx];
		MeanGroup->RemoveAt( inIdx );

		//-- アイテムが完全にない --//
		if( MeanGroup->Count == 0 )
		{
			WordID = 0;
			MeanNo = 0;
			if( Mean != nullptr )
			{
				delete Mean;
				Mean = nullptr;
			}
			if( Example != nullptr )
			{
				delete Example;
				Example = nullptr;
			}
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データ削除に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10205;
		tmpWDDataException->ErrorCode2 = 4;
		throw tmpWDDataException;
	}


}
//------------------------------------------------------------------------------
//　情報操作
//------------------------------------------------------------------------------
//***** データ部長取得
Int32 WDDatas::WDMean::DataLength( Int32 inIdx )
{
	if( MeanGroup->Count == 0 )
	{
		return 0;
	}
	if( inIdx < 0 || MeanGroup->Count < inIdx )
	{
		return 0;
	}

	if( MeanGroup[inIdx]->MeanFlg == 0 )
	{
		return WDMEAN_LENGTH;
	}else{
		return WDMEAN_SHORT_LENGTH;
	}
}

//***** データレコード長取得
Int32 WDDatas::WDMean::RecLength()
{
	return RecLength( 0 );
}

Int32 WDDatas::WDMean::RecLength( Int32 inIdx )
{
	if( MeanGroup->Count == 0 )
	{
		return 0;
	}
	if( inIdx < 0 || MeanGroup->Count < inIdx )
	{
		return 0;
	}

	if( MeanGroup[inIdx]->MeanFlg == 0 )
	{
		return DataRecord::getHeaderLength() + WDMEAN_LENGTH;
	}else{
		return DataRecord::getHeaderLength() + WDMEAN_SHORT_LENGTH;
	}
}

//------------------------------------------------------------------------------
//　アイテム操作
//------------------------------------------------------------------------------
//***** 単語ID取得
Int32 WDDatas::WDMean::getWordID( void )
{
	return WordID;
}

//***** 意味No取得
Int32 WDDatas::WDMean::getMeanNo( void )
{
	return MeanNo;
}

//***** 分類取得
WDMeanGroup^ WDDatas::WDMean::getGroup( Int32 inIdx )
{
	WDMeanGroup^ tmpGroup;
	WDMeanGroup^ rtGroup;

	//-- 分類情報チェック --//
	if( MeanGroup->Count == 0 )
	{
		return nullptr;
	}

	//-- 引数チェック --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックスの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 10211;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	try
	{
		tmpGroup = MeanGroup[inIdx];

		rtGroup = gcnew WDMeanGroup;
		rtGroup->MeanFlg = tmpGroup->MeanFlg;
		rtGroup->GroupGt = gcnew array<Byte>(WDMEAN_GROUPGTLEN);
		Buffer::BlockCopy( tmpGroup->GroupGt, 0, rtGroup->GroupGt, 0, WDMEAN_GROUPGTLEN );
		rtGroup->GroupLt = gcnew array<Byte>(WDMEAN_GROUPLTLEN);
		Buffer::BlockCopy( tmpGroup->GroupLt, 0, rtGroup->GroupLt, 0, WDMEAN_GROUPGTLEN );
		rtGroup->GroupRank = tmpGroup->GroupRank;
		rtGroup->DataRec = nullptr;

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類取得時にエラーが発生しました。", exp );
		tmpWDDataException->ErrorCode  = 10211;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
		return rtGroup;
}

Int32 WDDatas::WDMean::getMeanFlg( Int32 inIdx )
{
	//-- 分類情報チェック --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類情報がありません。" );
		tmpWDDataException->ErrorCode  = 10212;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- 引数チェック --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックスの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 10212;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	try
	{
		return MeanGroup[inIdx]->MeanFlg;

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味フラグ取得時にエラーが発生しました。", exp );
		tmpWDDataException->ErrorCode  = 10212;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** 分類大取得
array<Byte>^ WDDatas::WDMean::getGroupGt( Int32 inIdx, array<Byte>^ inData )
{
	array<Byte>^ rtData;

	//-- 分類情報チェック --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類情報がありません。" );
		tmpWDDataException->ErrorCode  = 10206;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- 引数チェック --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックスの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 10206;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	try
	{
		//-- データ領域設定 --//
		if( inData != nullptr )
		{
			if( inData->Length < WDMEAN_GROUPGTLEN )
			{
				WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
					L"コピー先データ長が短すぎます。" );
				tmpWDDataException->ErrorCode  = 10206;
				tmpWDDataException->ErrorCode2 = 3;
				throw tmpWDDataException;
			}
			rtData = inData;
		}else{

			rtData = gcnew array<Byte>(WDMEAN_GROUPGTLEN);
		}

		//-- データコピー --//
		Buffer::BlockCopy( MeanGroup[inIdx]->GroupGt, 0, rtData, 0, WDMEAN_GROUPGTLEN );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データのコピーに失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10206;
		tmpWDDataException->ErrorCode2 = 4;
		throw tmpWDDataException;
	}

	//-- 正常終了 --//
	return rtData;

}

//***** 分類小取得
array<Byte>^ WDDatas::WDMean::getGroupLt( Int32 inIdx, array<Byte>^ inData )
{
	array<Byte>^ rtData;

	//-- 分類情報チェック --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類情報がありません。" );
		tmpWDDataException->ErrorCode  = 10207;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- 引数チェック --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックスの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 10207;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	try
	{
		//-- データ領域設定 --//
		if( inData != nullptr )
		{
			if( inData->Length < WDMEAN_GROUPLTLEN )
			{
				WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
					L"コピー先データ長が短すぎます。" );
				tmpWDDataException->ErrorCode  = 10207;
				tmpWDDataException->ErrorCode2 = 3;
				throw tmpWDDataException;
			}
			rtData = inData;
		}else{
			rtData = gcnew array<Byte>(WDMEAN_GROUPLTLEN);
		}

		//-- データコピー --//
		Buffer::BlockCopy( MeanGroup[inIdx]->GroupLt, 0, rtData, 0, WDMEAN_GROUPLTLEN );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データのコピーに失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10207;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//-- 正常終了 --//
	return rtData;
}

//***** 分類順位取得
Int32 WDDatas::WDMean::getGroupRank( Int32 inIdx )
{
	//-- 分類情報チェック --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類情報がありません。" );
		tmpWDDataException->ErrorCode  = 10214;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- 引数チェック --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックスの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 10214;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	try
	{
		return MeanGroup[inIdx]->GroupRank;

	}catch(Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類ランクの取得時にエラーが発生しました。", exp );
		tmpWDDataException->ErrorCode  = 10214;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** 品詞取得
Byte WDDatas::WDMean::getSpeech( void )
{
	return Speech;
}

//***** ランク取得
Int32 WDDatas::WDMean::getRank( void )
{
	return Rank;
}

//***** 意味取得
String^ WDDatas::WDMean::getMean( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert( 0, Mean );
		return inData;
	}else{
		if( Mean->Length > 0 )
		{
			return Mean->Trim('\0');
		}else{
			return gcnew String( L"") ;
		}
	}

}								

//***** 例文取得
String^ WDDatas::WDMean::getExample( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert( 0, Example );
		return inData;
	}else{
		if( Example->Length > 0 )
		{
			return Example->Trim('\0');
		}else{
			return gcnew String( L"") ;
		}
	}

}								

//***** 分類数取得
Int32 WDDatas::WDMean::MeanGroupCount( void )
{
	return MeanGroup->Count;
}									

//------------------------------------------------------------------------------
//***** 単語ID設定
void WDDatas::WDMean::setWordID( Int32 inData )
{
	//-- 引数チェック --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"単語IDが不正です。" );
		tmpWDDataException->ErrorCode  = 10208;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	WordID = inData;
}

//***** 単語ID設定
void WDDatas::WDMean::setMeanNo( Int32 inData )
{
	//-- 引数チェック --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味Noが不正です。" );
		tmpWDDataException->ErrorCode  = 10209;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	MeanNo = inData;
}

//***** 分類設定
void WDDatas::WDMean::setGroup( Int32 inMeanFlg, array<Byte>^ inGroupGt, 		
					array<Byte>^ inGroupLt, Int32 inGroupRank )
{
	WDMeanGroup^ tmpWDMeanGroup;

	//-- 引数チェック --//
	if( inMeanFlg < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味フラグが不正です。" );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inGroupGt == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類大が未設定です。" );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	if( inGroupGt->Length < WDMEAN_GROUPGTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類大が短すぎます。" );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
	if( inGroupLt == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類小が未設定です。" );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 4;
		throw tmpWDDataException;
	}
	if( inGroupLt->Length < WDMEAN_GROUPLTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類小が短すぎます。" );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 5;
		throw tmpWDDataException;
	}
	//-- 引数チェック --//
	if( inGroupRank < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類順位が不正です。" );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 6;
		throw tmpWDDataException;
	}

	try
	{
		//意味フラグ
		tmpWDMeanGroup = gcnew WDMeanGroup;
		tmpWDMeanGroup->MeanFlg = inMeanFlg;

		//-- 分類コピー --//
		//分類大
		tmpWDMeanGroup->GroupGt = gcnew array<Byte>(WDMEAN_GROUPGTLEN);
		Buffer::BlockCopy( inGroupGt, 0, tmpWDMeanGroup->GroupGt, 0, WDMEAN_GROUPGTLEN );
		//分類小
		tmpWDMeanGroup->GroupLt = gcnew array<Byte>(WDMEAN_GROUPLTLEN);
		Buffer::BlockCopy( inGroupLt, 0, tmpWDMeanGroup->GroupLt, 0, WDMEAN_GROUPLTLEN );
		//分類ランク
		tmpWDMeanGroup->GroupRank = inGroupRank;
		//データレコード
		tmpWDMeanGroup->DataRec = nullptr;

		//意味グループ追加
		addMeanGrp( tmpWDMeanGroup );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類設定中にエラーが発生しました。", exp );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 6;
		throw tmpWDDataException;
	}
}

//***** 品詞設定
void WDDatas::WDMean::setSpeech( Byte inData )
{
	Speech = inData;
}

//***** ランク設定
void WDDatas::WDMean::setRank( Byte inData )
{
	if( inData < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ランクが不正です。" );
		tmpWDDataException->ErrorCode  = 10219;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	Rank = inData;
}

//***** 意味設定
void WDDatas::WDMean::setMean( String^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味が未設定です。" );
		tmpWDDataException->ErrorCode  = 10213;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDMEAN_MEANLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味が長すぎます。" );
		tmpWDDataException->ErrorCode  = 10213;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( Mean != nullptr )
		{
			delete Mean;
		}
		Mean = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味の設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10213;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** 意味設定
void WDDatas::WDMean::setExample( String^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味が未設定です。" );
		tmpWDDataException->ErrorCode  = 10217;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDMEAN_EXAMPLELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味が長すぎます。" );
		tmpWDDataException->ErrorCode  = 10217;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( Example != nullptr )
		{
			delete Example;
		}
		Example = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味の設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10217;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}

//***** 意味マージ
void WDDatas::WDMean::MergeMean( WDMean^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		return;
	}

	if( WordID != inData->WordID ||
		MeanNo != inData->MeanNo )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"この意味は結合できません。" );
		tmpWDDataException->ErrorCode  = 10218;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}

	try
	{
		for each( WDMeanGroup^ tmpWDMeanGroup in inData->MeanGroup )
		{
			addMeanGrp( tmpWDMeanGroup );

			//品詞
			if( tmpWDMeanGroup->MeanFlg == 0 &&
				Speech == 0 )
			{
				Speech = inData->Speech;
			}
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味の結合時にエラーが発生しました。", exp );
		tmpWDDataException->ErrorCode  = 10218;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;

	}

		
	//意味
	if( Mean == nullptr )
	{
		Mean = String::Copy( inData->Mean );
	}

	//例文
	if( Example == nullptr )
	{
		Example = String::Copy( inData->Example );
	}

}								

//***** 意味グループ追加
Int32 WDDatas::WDMean::addMeanGrp( WDMeanGroup^ inMeanGrp )
{

	//-- 引数チェック --//
	if( inMeanGrp == nullptr )
	{
		return -1;
	}

	//-- 引数追加 --//
	for each( WDMeanGroup^ tmpMeanGrp in MeanGroup )
	{
		if( WDMeanGrpComp->Compare( tmpMeanGrp, inMeanGrp ) == 0 )
		{
			return -1;
		}
	
	}
	//-- 分類追加 --//
	MeanGroup->Add( inMeanGrp );
	//-- 分類ソート --//
	MeanGroup->Sort( WDMeanGrpComp );

	//-- 正常終了 --//
	return 0;
}

//***** 意味グループ比較
Int32 WDDatas::WDMeanGrpComparer::Compare( WDMeanGroup^ x, WDMeanGroup^ y)
{
	Int32 Result;

	//Xがnullptrの場合
	if (x == nullptr)
	{
		if (y == nullptr)
		{
			return 0;
        }else{
			//X = nullptr , Y != nullptr ->Yが小さい(先に来る)
			return 1;
		}
	}

	//X != nullptr , Y = nullptr ->Xが小さい(先に来る)
	if( y == nullptr )
	{
		return -1;
	}

	//意味フラグ比較
	if( x->MeanFlg < y->MeanFlg )
	{
		return -1;
	}else if( x->MeanFlg > y->MeanFlg ){
		return 1;
	}
	
	//分類大比較
	Result = x->GroupGt[0].CompareTo( y->GroupGt[0] );
	if( Result == 0 ) return Result;
	Result = x->GroupGt[1].CompareTo( y->GroupGt[1] );
	if( Result == 0 ) return Result;

	//分類小比較
	Result = x->GroupLt[0].CompareTo( y->GroupLt[0] );
	if( Result == 0 ) return Result;
	Result = x->GroupLt[1].CompareTo( y->GroupLt[1] );
	
	//比較完了
	return Result;

}