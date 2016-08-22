//------------------------------------------------------------------------------
//	単語辞典　単語辞典データクラス　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDWord		: 単語クラス
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//単語辞典データ用例外クラス
#include "WDDatas.h"			//単語辞典データクラス
#include "WDDatasDef.h"			//単語辞典データ定数定義
//#include "FJIsamDef.h"			//ISAM用定義ファイル

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDWord	: 単語クラス
//------------------------------------------------------------------------------
//***** コンストラクタ１(新規データ)
WDDatas::WDWord::WDWord()
 //: WDRec()
{
	//-- 変数定義 --//
	ReadPattern = 0;
	BaseFlg = false;
	Practical = 0;
	Gramatical = 0;
	Plurality = 0;
	Sex = 0;
	Type = 0;

}

//***** コンストラクタ２(読込データ)
WDDatas::WDWord::WDWord( DataRecord^ inRec )
{

	if(inRec == nullptr )
	{
		//-- 変数定義 --//
		ReadPattern = 0;
		BaseFlg = false;
		Practical = 0;
		Gramatical = 0;
		Plurality = 0;
		Sex = 0;
		Type = 0;
		return;
	}

	//-- 引数チェック --//
	if( inRec->getDataLength() != WDWORD_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードが単語データではありません。" );
		tmpWDDataException->ErrorCode  = 10101;
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
		tmpWDDataException->ErrorCode  = 10101;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//***** デストラクタ
WDDatas::WDWord::~WDWord()
{
	if( Word != nullptr ) delete Word;
	if( Read1 != nullptr ) delete Read1;
	if( Read2 != nullptr ) delete Read2;
}

//------------------------------------------------------------------------------
//　データレコード操作
//------------------------------------------------------------------------------
//***** データレコード取得
DataRecord^ WDDatas::WDWord::getRecord( void )
{
	DataRecord^ tmpRec;
	array<Byte>^ tmpDat;

	if( WDRec::getRecord() == nullptr )
	{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = gcnew DataRecord();
			tmpRec->setData( tmpDat, WDWORD_LENGTH );
			WDRec::setRecord( tmpRec );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データレコード取得でエラーが発生しました。", exp );
			tmpWDDataException->ErrorCode  = 10102;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}
	}else{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = WDRec::getRecord();
			tmpRec->setData( tmpDat, WDWORD_LENGTH );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データレコード取得でエラーが発生しました。", exp );
			tmpWDDataException->ErrorCode  = 10102;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}

	delete tmpDat;

	//-- 正常終了 --//
	return tmpRec;
}

//***** データレコード設定
void WDDatas::WDWord::setRecord(  DataRecord^ inRec )
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
			tmpWDDataException->ErrorCode  = 10103;
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
			tmpWDDataException->ErrorCode  = 10103;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}
}

//***** データレコード書込
void WDDatas::WDWord::Write( void )
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
		tmpWDDataException->ErrorCode  = 10104;
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
			tmpWDDataException->ErrorCode  = 10104;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10104;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** データレコード書込
void WDDatas::WDWord::Delete( void )
{
	FIsam^ tmpParent;

	//-- データレコードチェック --//
	if( WDRec::getRecord() == nullptr )
	{
		//--　データクリア --//
		if( Word != nullptr )
		{
			delete Word;
			Word = nullptr;
		}
		if( Read1 != nullptr )
		{
			delete Read1;
			Read1 = nullptr;
		}
		if( Read2 != nullptr )
		{
			delete Read2;
			Read2 = nullptr;
		}

		ReadPattern = 0;
		BaseFlg = false;
		Practical = 0;
		Gramatical = 0;
		Plurality = 0;
		Sex = 0;
		Type = 0;

		return;
	}

	//-- ISAMファイルチェック --//
	try
	{
		tmpParent = safe_cast<FIsam^>( WDRec::getRecord()->getParentFile() );
		if( tmpParent == nullptr )
		{
			//--　データクリア --//
			if( Word != nullptr )
			{
				delete Word;
				Word = nullptr;
			}
			if( Read1 != nullptr )
			{
				delete Read1;
				Read1 = nullptr;
			}
			if( Read2 != nullptr )
			{
				delete Read2;
				Read2 = nullptr;
			}

			ReadPattern = 0;
			BaseFlg = false;
			Practical = 0;
			Gramatical = 0;
			Plurality = 0;
			Sex = 0;
			Type = 0;

			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAMファイルが不正です。", exp );
		tmpWDDataException->ErrorCode  = 10105;
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
			tmpWDDataException->ErrorCode  = 10105;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データレコードの書込に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10105;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//--　データクリア --//
	if( Word != nullptr )
	{
		delete Word;
		Word = nullptr;
	}
	if( Read1 != nullptr )
	{
		delete Read1;
		Read1 = nullptr;
	}
	if( Read2 != nullptr )
	{
		delete Read2;
		Read2 = nullptr;
	}

	ReadPattern = 0;
	BaseFlg = false;
	Practical = 0;
	Gramatical = 0;
	Plurality = 0;
	Sex = 0;
	Type = 0;

}
//------------------------------------------------------------------------------
//　情報操作
//------------------------------------------------------------------------------
//***** データ長取得
Int32 WDDatas::WDWord::Length()
{
	return WDWORD_LENGTH;
}

//***** データレコード長取得
Int32 WDDatas::WDWord::RecLength()
{
	return DataRecord::getHeaderLength() + WDWORD_LENGTH;
}

//------------------------------------------------------------------------------
//　アイテム操作
//------------------------------------------------------------------------------
//***** 単語取得
String^ WDDatas::WDWord::getWord( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert( 0, Word );
		return inData;
	}else{
		if( Word->Length > 0 )
		{
			return Word->Trim('\0');
		}else{
			return gcnew String( L"" );
		}
	}
}

//***** 読み1取得
String^ WDDatas::WDWord::getRead1( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert( 0, Read1 );
		return inData;
	}else{
		if( Read1->Length > 0 )
		{
			return Read1->Trim('\0');
		}else{
			return gcnew String( L"" );
		}
	}

}								
//***** 読み2取得
String^ WDDatas::WDWord::getRead2( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert( 0, Read2 );
		return inData;
	}else{
		if( Read2->Length > 0 )
		{
			return Read2->Trim('\0');
		}else{
			return gcnew String( L"" );
		}
	}

}	

//***** 単語ID取得
Int32	WDDatas::WDWord::getWordID( void )
{
	return WordID;
}

//***** 読み方取得
Byte	WDDatas::WDWord::getReadPattern( void )
{
	return ReadPattern;
}

//***** 基本フラグ取得
Boolean	WDDatas::WDWord::getBaseFlg( void )
{
	return BaseFlg;

}

//***** 活用形取得
Byte	WDDatas::WDWord::getPractical( void )
{
	return Practical;
}

//***** 人称取得
Byte	WDDatas::WDWord::getGramatical( void )
{
	return Gramatical;
}

//***** 単数複数取得
Byte	WDDatas::WDWord::getPlurality( void )
{
	return Plurality;
}

//***** 性取得
Byte	WDDatas::WDWord::getSex( void )
{
	return Sex;
}

//***** 活用タイプ取得
Int32	WDDatas::WDWord::getType( void )
{
	return Type;
}


//------------------------------------------------------------------------------
//***** 単語設定
void WDDatas::WDWord::setWord( String^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"単語が未設定です。" );
		tmpWDDataException->ErrorCode  = 10106;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDWORD_WORDLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"単語が長すぎます。" );
		tmpWDDataException->ErrorCode  = 10106;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( Word != nullptr ) delete Word;
		Word = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"単語の設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10106;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** 読み1設定
void WDDatas::WDWord::setRead1( String^ inData )
{	
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"読み1が未設定です。" );
		tmpWDDataException->ErrorCode  = 10107;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDWORD_READ1LEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"読み1が長すぎます。" );
		tmpWDDataException->ErrorCode  = 10107;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( Read1 != nullptr ) delete Read1;
		Read1 = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"読み1の設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10107;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** 読み2設定
void WDDatas::WDWord::setRead2( String^ inData )
{	
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"読み2が未設定です。" );
		tmpWDDataException->ErrorCode  = 10108;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDWORD_READ2LEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"読み2が長すぎます。" );
		tmpWDDataException->ErrorCode  = 10108;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( Read2 != nullptr ) delete Read2;
		Read2 = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"読み2の設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10108;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** 単語ID設定
void WDDatas::WDWord::setWordID( Int32 inData )
{
	//-- 引数チェック --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"単語IDが不正です。" );
		tmpWDDataException->ErrorCode  = 10109;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	WordID = inData;
}

//***** 読み方設定
void WDDatas::WDWord::setReadPattern( Byte inData )
{
	ReadPattern = inData;
}

//***** 基本フラグ設定
void WDDatas::WDWord::setBaseFlg( Boolean inData )
{
	BaseFlg = inData;
}					


//***** 活用形設定
void WDDatas::WDWord::setPractical( Byte inData )
{
	Practical = inData;
}					

//***** 人称設定
void WDDatas::WDWord::setGramatical( Byte inData )
{
	Gramatical = inData;
}

//***** 単数複数設定
void WDDatas::WDWord::setPlurality( Byte inData )
{
	Plurality = inData;
}

//***** 性設定
void WDDatas::WDWord::setSex( Byte inData )
{
	Sex = inData;
}

//***** 活用タイプ設定
void WDDatas::WDWord::setType( Int32 inData )
{
	//-- 引数チェック --//
	if( inData < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"活用タイプが不正です。" );
		tmpWDDataException->ErrorCode  = 10116;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	Type = inData;
}


//------------------------------------------------------------------------------
//　データ操作
//------------------------------------------------------------------------------
//***** データ取得
array<Byte>^ WDDatas::WDWord::getData( array<Byte>^ inData )
{
	array<Byte>^ rtData;
	Int32		 tmpPos;

	//-- 引数チェック --//
	if( inData != nullptr &&
		inData->Length < WDWORD_LENGTH - WDWORD_RESERVEDLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー先データ長が短すぎます。" );
		tmpWDDataException->ErrorCode  = 10117;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( inData == nullptr )
		{
			rtData = gcnew array<Byte>( WDWORD_LENGTH );
		}else{
			rtData = inData;
		}

		tmpPos = 0;
		//単語	
		FJIFuncs::StringToArray( Word, rtData, tmpPos, WDWORD_WORDLEN );
		tmpPos += WDWORD_WORDLEN;
		//読み方１
		FJIFuncs::StringToArray( Read1, rtData, tmpPos, WDWORD_READ1LEN );
		tmpPos += WDWORD_READ1LEN;
		//読み方２
		FJIFuncs::StringToArray( Read2, rtData, tmpPos, WDWORD_READ2LEN );
		tmpPos += WDWORD_READ2LEN;
		//単語ID
		FJIFuncs::Int32ToArray( WordID, rtData, tmpPos );
		tmpPos += WDWORD_WORDIDLEN;

		//読み方
		rtData[tmpPos] = ReadPattern;
		tmpPos += WDWORD_READPATTERNLEN;

		//基本フラグ
		if( BaseFlg == true )		//trueなら　0 :　falseなら 0以外
		{
			rtData[tmpPos] = 0;
		}else{
			rtData[tmpPos] = 1;
		}
		tmpPos += WDWORD_BASEFLGLEN;

		//活用形
		rtData[tmpPos] = Practical;
		tmpPos += WDWORD_PRACTICALLEN;
		//単数複数
		rtData[tmpPos] = Plurality;
		tmpPos += WDWORD_PLURALITYLEN;
		//人称
		rtData[tmpPos] = Gramatical;
		tmpPos += WDWORD_GRAMATICALLEN;
		//性
		rtData[tmpPos] = Sex;
		tmpPos += WDWORD_SEXLEN;
		//活用type
		FJIFuncs::Int32ToArray( Type, rtData, tmpPos );
		tmpPos += WDWORD_TYPELEN;

		//余白
		for(Int32 i = 0; i < WDWORD_RESERVEDLEN; i++ )
		{
			Buffer::SetByte( rtData,tmpPos, 0 );
			tmpPos++;
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データのコピーに失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10117;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- 正常終了 --//
	return rtData;
}

//***** データ設定
void WDDatas::WDWord::setData( array<Byte>^ inData )
{
	Int32		 tmpPos;

	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー元データが未設定です。" );
		tmpWDDataException->ErrorCode  = 10118;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length != WDWORD_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"コピー元データ長が正しくありません。" );
		tmpWDDataException->ErrorCode  = 10118;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		tmpPos = 0;
		//単語
		if( Word != nullptr ) delete Word;
		Word = FJIFuncs::ArrayToString(inData, tmpPos, WDWORD_WORDLEN );
		tmpPos += WDWORD_WORDLEN;
		//読み方１
		if( Read1 != nullptr ) delete Read1;
		Read1 = FJIFuncs::ArrayToString(inData, tmpPos, WDWORD_WORDLEN );
		tmpPos += WDWORD_READ1LEN;
		//読み方２
		if( Read2 != nullptr ) delete Read2;
		Read2 = FJIFuncs::ArrayToString(inData, tmpPos, WDWORD_WORDLEN );
		tmpPos += WDWORD_READ2LEN;
		//単語ID
		WordID = FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDWORD_WORDIDLEN;

		//品詞
		ReadPattern = inData[tmpPos];
		tmpPos += WDWORD_READPATTERNLEN;

		//基本フラグ
		if( inData[tmpPos] == 0 )	//0なら　true , 0以外なら false
		{
			BaseFlg = true;
		}else{
			BaseFlg = false;
		}
		tmpPos += WDWORD_BASEFLGLEN;
		//活用形
		Practical = inData[tmpPos];
		tmpPos += WDWORD_PRACTICALLEN;
		//単数複数
		Plurality = inData[tmpPos];
		tmpPos += WDWORD_PLURALITYLEN;
		//人称
		Gramatical = inData[tmpPos];
		tmpPos += WDWORD_GRAMATICALLEN;
		//性
		Sex = inData[tmpPos];
		tmpPos += WDWORD_SEXLEN;
		//活用type
		Type = FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDWORD_TYPELEN;

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"データの設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 10118;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}