//------------------------------------------------------------------------------
//	ことばの辞典　ことばの辞典ビューアアプリケーション　ヘッダ
//	Version 1.0.0.0	create date 2006/05/08
//	Version 1.0.1.1	create date 1010/10/22	getBaseWord( void ) 検索した読み方の基本単語を返すよう変更
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDWordGrp : 辞典単語情報
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasDef.h"			//単語辞典データ定数定義
#include "WDWordGrp.h"			//単語データ用辞書

using namespace WDDatas;

//------------------------------------------------------------------------------
//　コンストラクタ
//------------------------------------------------------------------------------
WordDic::WDWordGrp::WDWordGrp( Int32 inLang, Int32 inDispNum, Int32 inSubDispNum )
{
	//-- 初期化 --//
	WordLst = gcnew List<WDWord^>();
	MeanLst = gcnew List<WDMean^>();
	TransLst = gcnew List<WDTrans^>();
	RelationLst = gcnew List<WDRelation^>();
	BaseWordLst = gcnew List<WDWord^>();

	SchWord = nullptr;
	WordID = -1;
	SchGroupRank = 0;
	DispNum = 0;
	SubDispNum = 0;

	//-- リスト並び替えクラス定義 --//
	if( WDWordComp == nullptr ) WDWordComp = gcnew WDWordComparer();
	if( WDMeanComp == nullptr ) WDMeanComp = gcnew WDMeanComparer();
	if( WDTransComp == nullptr ) WDTransComp = gcnew WDTransComparer();
	if( WDRelationComp == nullptr ) WDRelationComp = gcnew WDRelationComparer();
	
	//-- 検索言語設定 --//
	if( inLang != 1 && inLang != 2 )
	{
		SchLang = 1;
	}else{
		SchLang = inLang;
	}

	//-- 単語リスト表示方法設定 --//
	setWordListDisp( inDispNum, inSubDispNum );
	
}

//------------------------------------------------------------------------------
//　デストラクタ
//------------------------------------------------------------------------------
WordDic::WDWordGrp::~WDWordGrp( void )
{	
	for each( WDWord^ tmpWord in WordLst )
	{
		if( tmpWord != nullptr ) delete tmpWord;
	}
	delete WordLst;

	for each( WDMean^ tmpMean in MeanLst )
	{
		if( tmpMean != nullptr ) delete tmpMean;
	}
	delete MeanLst;

	for each( WDTrans^ tmpTrans in TransLst )
	{
		if( tmpTrans != nullptr ) delete tmpTrans;
	}
	delete TransLst;

	for each( WDRelation^ tmpRelation in RelationLst )
	{
		if( tmpRelation != nullptr ) delete tmpRelation;
	}
	delete RelationLst;

}

//------------------------------------------------------------------------------
//　アイテム参照
//------------------------------------------------------------------------------
//***** 単語取得
WDWord^ WordDic::WDWordGrp::getWord( Int32 idx )
{
	//-- 引数チェック --//
	if( idx < 0 ||
		idx > WordLst->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックスの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 21001;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}

	//-- 値返却 --//
	return WordLst[idx];
}

//***** 基本単語取得
WDWord^ WordDic::WDWordGrp::getBaseWord( void )
{
	//-- 基本単語がセットされている場合 --//
	// 検索した読み方と同じ読み方の基本単語を返す。
	if( BaseWordLst->Count > 0 )
	{
		//検索した読み方と同じ読み方かチェック
		for each( WDWord^ tmpWord in BaseWordLst )
		{
			if( tmpWord->getReadPattern() == SchReadPattern )
			{
				return tmpWord;
			}
		}
		//同じ読み方がない場合、nullを返す。
		return nullptr;

	//-- 基本単語がない場合は、nullを返す。
	}else{
		return nullptr;
	}
}

//***** 基本単語取得( 読み方で検索 )
WDWord^ WordDic::WDWordGrp::getBaseWord( Int32 inReadPattern )
{
	//-- 値返却 --//
	for each( WDWord^ tmpWord in BaseWordLst )
	{
		if( tmpWord->getReadPattern() == inReadPattern )
		{
			return tmpWord;
		}
	}
	return nullptr;
}

//***** 検索単語取得
WDWord^	WordDic::WDWordGrp::getSchWord( void )
{
	//-- 単語で検索していなければnullptrを返す --//
	if( SchMethod != 1 )
	{
		return nullptr;
	}

	//-- 値返却 --//
	return SchWord;
}

//***** 意味取得
WDMean^ WordDic::WDWordGrp::getMean( Int32 idx )
{
	//-- 引数チェック --//
	if( idx < 0 ||
		idx > MeanLst->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックスの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 21002;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}

	//-- 値返却 --//
	return MeanLst[idx];
}

WDMean^	WordDic::WDWordGrp::getSchMean( void )
{
	//-- 意味(分類)で検索していなければnullptrを返す --//
	if( SchMethod != 2 )
	{
		return nullptr;
	}

	//-- 値返却 --//
	return SchMean;
}
//***** 翻訳取得
WDTrans^ WordDic::WDWordGrp::getTrans( Int32 idx )
{
	//-- 引数チェック --//
	if( idx < 0 ||
		idx > TransLst->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックスの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 21003;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}

	//-- 値返却 --//
	return TransLst[idx];
}

//***** 翻訳語取得(意味Noによる)
WDTrans^ WordDic::WDWordGrp::getTransNo( Int32 inNo )
{
	//-- 引数チェック --//
	if( inNo <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味Noの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 21010;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	
	//-- データ検索 --//
	for( Int32 i = 0; i < TransLst->Count; i++ )
	{
		if( TransLst[i]->getMeanNo() == inNo )
		{
			return TransLst[i];
		}
	}

	//-- 値返却 --//
	return nullptr;
}

//***** 関連語取得
WDRelation^ WordDic::WDWordGrp::getRelation( Int32 idx )
{
	//-- 引数チェック --//
	if( idx < 0 ||
		idx > RelationLst->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"インデックスの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 21004;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}

	//-- 値返却 --//
	return RelationLst[idx];
}

//***** 関連語取得(意味Noによる)
WDRelation^ WordDic::WDWordGrp::getRelationNo( Int32 inNo )
{
	//-- 引数チェック --//
	if( inNo <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味Noの指定が不正です。" );
		tmpWDDataException->ErrorCode  = 21011;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	
	//-- データ検索 --//
	for( Int32 i = 0; i < RelationLst->Count; i++ )
	{
		if( RelationLst[i]->getMeanNo() == inNo )
		{
			return RelationLst[i];
		}
	}

	//-- 値返却 --//
	return nullptr;
}

//***** XMLファイル名取得
String^ WordDic::WDWordGrp::getXMLFname( void )
{
	if( XMLFname == nullptr )
	{
		return nullptr;
	}
	return String::Copy( XMLFname );
}
						
//***** 単語ID取得
Int32 WordDic::WDWordGrp::getWordID( void )
{
	//-- 値返却 --//
	return WordID;
}

//***** 単語数取得
Int32 WordDic::WDWordGrp::getWordCnt( void )
{
	//-- 値返却 --//
	return WordLst->Count;
}

//***** 意味数取得
Int32 WordDic::WDWordGrp::getMeanCnt( void )
{
	//-- 値返却 --//
	return MeanLst->Count;
}

//***** 翻訳数取得
Int32 WordDic::WDWordGrp::getTransCnt( void )
{
	//-- 値返却 --//
	return TransLst->Count;
}
		
//***** 関連語数取得
Int32 WordDic::WDWordGrp::getRelationCnt( void )
{
	//-- 値返却 --//
	return RelationLst->Count;
}

//***** 検索方法取得
Int32 WordDic::WDWordGrp::getSchMethod( void )
{
	//-- 値返却 --//
	return SchMethod;
}

//***** 検索言語取得
Int32 WordDic::WDWordGrp::getSchLang( void )
{
	//-- 値返却 --//
	return SchLang;
}

//***** ToStringでの表示方法設定
Int32 WordDic::WDWordGrp::getWordListDisp( void )
{
	return	DispNum;
}

//***** 検索意味分類順位
Int32 WordDic::WDWordGrp::getSchGroupRank( void )
{
	return SchGroupRank;
}

//***** 読み方数取得
Int32 WordDic::WDWordGrp::getReadPatternCnt( void )
{
	return BaseWordLst->Count;
}

//------------------------------------------------------------------------------
//　アイテム追加
//------------------------------------------------------------------------------
//***** 単語追加
void WordDic::WDWordGrp::addWord( WDWord^ inWord, Boolean inSch )
{
	//-- 引数チェック --//
	if( inWord == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"単語データが未設定です。" );
		tmpWDDataException->ErrorCode  = 21005;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	if( WordID != -1 &&
		WordID != inWord->getWordID() )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"異なる単語は追加できません。" );
		tmpWDDataException->ErrorCode  = 21005;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	if( inSch == true && SchMethod != 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"既に検索方法が設定されています。" );
		tmpWDDataException->ErrorCode  = 21005;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//-- 単語セット --//
	//同一データなら追加せずに終了
	for each( WDWord^ tmpWord in WordLst )
	{
		if( WDWordComp->Compare( tmpWord, inWord ) == 0 )
		{
			return;
		}
	}

	//検索単語に設定
	if( inSch == true )
	{
		SchMethod = 1;
		SchWord = inWord;
		SchReadPattern = inWord->getReadPattern();
	}

	//単語基本形に設定
	if( inWord->getBaseFlg() == true )
	{
		BaseWordLst->Add( inWord );

		//基本単語リストソート
		if( BaseWordLst->Count > 1 )
		{
			BaseWordLst->Sort( WDWordComp );
		}
	}

	//単語ID設定
	if( WordID == -1 )
	{
		WordID = inWord->getWordID();
	}

	//単語リストに設定
	WordLst->Add( inWord );

	//単語リストソート
	if( WordLst->Count >1 )
	{
		WordLst->Sort( WDWordComp );
	}
}

//***** 意味追加
void WordDic::WDWordGrp::addMean( WDMean^ inMean, Boolean inSch, Int32 inMeanFlg )
{
	Boolean addFlg;

	//-- 引数チェック --//
	if( inMean== nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味データが未設定です。" );
		tmpWDDataException->ErrorCode  = 21006;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	if( WordID != -1 &&
		WordID != inMean->getWordID() )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"異なる単語の意味は追加できません。" );
		tmpWDDataException->ErrorCode  = 21006;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	if( inSch == true && SchMethod != 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"既に検索方法が設定されています。" );
		tmpWDDataException->ErrorCode  = 21006;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//検索意味に設定
	if( inSch == true )
	{
		SchMethod = 2;
		SchMean = inMean;

		for( Int32 i = 0; i < inMean->MeanGroupCount(); i++ )
		{
			WDMeanGroup^ tmpWDMeanGroup = inMean->getGroup( i );
			if( tmpWDMeanGroup == nullptr )
			{
				WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
					L"分類情報が存在しません。" );
				tmpWDDataException->ErrorCode  = 21006;
				tmpWDDataException->ErrorCode2 = 4;
				throw tmpWDDataException;
			}
			if( tmpWDMeanGroup->MeanFlg == inMeanFlg )
			{
				SchGroupRank = tmpWDMeanGroup->GroupRank;
			}
		}
	}

	//単語ID設定
	if( WordID == -1 )
	{
		WordID = inMean->getWordID();
	}
		
	//意味リストに設定
	try
	{
		addFlg = false;
		for each( WDMean^ tmpWDMean in MeanLst )
		{
			if( tmpWDMean->getWordID() == inMean->getWordID() &&
				tmpWDMean->getMeanNo() == inMean->getMeanNo() )
			{
				addFlg = true;
				tmpWDMean->MergeMean( inMean );
			}
		}
		if( addFlg == false )
		{
			MeanLst->Add( inMean );
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"意味追加時にエラーが発生しました。", exp );
		tmpWDDataException->ErrorCode  = 21006;
		tmpWDDataException->ErrorCode2 = 5;
		throw tmpWDDataException;
	}

	//意味リストソート
	if( addFlg == false &&
		MeanLst->Count >1 )
	{
		MeanLst->Sort( WDMeanComp );
	}
}

//***** 翻訳追加
void WordDic::WDWordGrp::addTrans( WDTrans^ inTrans )
{
	//-- 引数チェック --//
	if( inTrans== nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"翻訳データが未設定です。" );
		tmpWDDataException->ErrorCode  = 21007;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	if( WordID != inTrans->getWordID() )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"異なる単語の翻訳は追加できません。" );
		tmpWDDataException->ErrorCode  = 21007;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- 翻訳セット --//
	//同一データなら追加せずに終了
	for each( WDTrans^ tmpTrans in TransLst )
	{
		if( WDTransComp->Compare( tmpTrans, inTrans ) == 0 )
		{
			return;
		}
	}

	//翻訳リストに設定
	TransLst->Add( inTrans );

	//翻訳リストソート
	if( TransLst->Count >1 )
	{
		TransLst->Sort( WDTransComp );
	}
}

//***** 関連語追加
void WordDic::WDWordGrp::addRelation( WDRelation^ inRelation )
{
	//-- 引数チェック --//
	if( inRelation== nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"関連語データが未設定です。" );
		tmpWDDataException->ErrorCode  = 21008;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	if( WordID != inRelation->getWordID() )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"異なる単語の関連語は追加できません。" );
		tmpWDDataException->ErrorCode  = 21008;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- 関連語セット --//
	//同一データなら追加せずに終了
	for each( WDRelation^ tmpRelation in RelationLst )
	{
		if( WDRelationComp->Compare( tmpRelation, inRelation ) == 0 )
		{
			return;
		}
	}

	//関連語リストに設定
	RelationLst->Add( inRelation );

	//関連語リストソート
	if( RelationLst->Count >1 )
	{
		RelationLst->Sort( WDRelationComp );
	}
}

//***** 単語情報XMLファイル名
void WordDic::WDWordGrp::setXMLFname( String^ inXMLFname )
{
	//-- 引数チェック --//
	if( inXMLFname == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"XMLファイル名が未設定です。" );
		tmpWDDataException->ErrorCode  = 21009;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- XMLファイル名設定 --//
	XMLFname = String::Copy( inXMLFname );
}

//***** ToStringでの表示方法設定
void WordDic::WDWordGrp::setWordListDisp( Int32 inDispNum, Int32 inSubDispNum )
{
	//表示
	if( inDispNum > 0 )
	{

		if( inDispNum < 1 && inDispNum > 3 )
		{
			DispNum = 1;
		}else{
			DispNum = inDispNum;
		}
	}

	//サブ表示
	if( inSubDispNum > -1 )
	{
		if( inSubDispNum < 0 && inSubDispNum > 3 )
		{
			SubDispNum = 0;
		}else{
			SubDispNum = inSubDispNum;
		}
	}

}

//------------------------------------------------------------------------------
//　リストボックス用
//------------------------------------------------------------------------------
//***** 文字列取得
String^ WordDic::WDWordGrp::ToString( void  )
{
	WDWord^ dispWord;
	String^ tmpString;
	String^ tmpSubString;
	String^ rtString;

	//-- 表示する単語を選択 --//
	if( BaseWordLst->Count > 0 )
	{
		for each( WDWord^ tmpWord in BaseWordLst )
		{
			if( tmpWord->getReadPattern() == SchReadPattern )
			{
				dispWord = tmpWord;
				break;
			}
		}
		if( dispWord == nullptr )
		{
			return L"(単語がありません)";
		}

	}else{
		return L"(単語がありません)";
	}
	
	//-- 表示データ設定
	switch( DispNum )
	{
	//単語
	case 1:
		tmpString = dispWord->getWord( nullptr );
		break;
	//読み方１
	case 2:
		tmpString = dispWord->getRead1( nullptr );
		break;
	//読み方２
	case 3:
		tmpString = dispWord->getRead2( nullptr );
		break;
	//それ以外（単語）
	default :
		tmpString = dispWord->getWord( nullptr );
	}
	//--サブ表示がない場合
	if( SubDispNum == 0 )
	{
		return tmpString;
	}

	//--サブ表示がある場合
	switch( SubDispNum )
	{
	//単語
	case 1:
		tmpSubString = dispWord->getWord( nullptr );
		break;
	//読み方１
	case 2:
		tmpSubString = dispWord->getRead1( nullptr );
		break;
	//読み方２
	case 3:
		tmpSubString = dispWord->getRead2( nullptr );
		break;
	//それ以外（単語）
	default :
		tmpSubString = dispWord->getWord( nullptr );
	}

	rtString = String::Format( L"{0} 【{1}】", tmpString, tmpSubString );
	delete tmpString;
	delete tmpSubString;

	//--言語を返す--//
	return rtString;
}
