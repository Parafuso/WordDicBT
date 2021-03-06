//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアー用クラス　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDWordGrp : 辞典単語情報
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDWordGrp.h"			//単語データ用辞書
#include "WDDatasDef.h"			//単語辞典データ定数定義

using namespace WDDatas;
//------------------------------------------------------------------------------
//　単語辞典用データ比較
//------------------------------------------------------------------------------
//***** 単語比較
Int32 WordDic::WDWordComparer::Compare(WDWord^ x, WDWord^ y)
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

	//WordID比較
	if( x->getWordID() < y->getWordID() )
	{
		return -1;
	}else if( x->getWordID() > y->getWordID() ){
		return 1;
	}

	//読み方比較
	Result = x->getReadPattern().CompareTo( y->getReadPattern() );
	if( Result != 0 ) return Result;

	//活用形比較
	Result = x->getPractical().CompareTo( y->getPractical() );
	if( Result != 0 ) return Result;

	//単数複数比較
	Result = x->getPlurality().CompareTo( y->getPlurality() );
	if( Result != 0 ) return Result;

	//人称比較
	Result = x->getGramatical().CompareTo( y->getGramatical() );
	if( Result != 0 ) return Result;

	//性別比較
	Result = x->getSex().CompareTo( y->getSex() );
	if( Result != 0 ) return Result;

	//完全一致
	return 0;

}

//***** 意味比較
Int32 WordDic::WDMeanComparer::Compare(WDMean^ x, WDMean^ y)
{
	Int32 Result;
	Int32 i;

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

	//WordID比較
	if( x->getWordID() < y->getWordID() )
	{
		return -1;
	}else if( x->getWordID() > y->getWordID() ){
		return 1;
	}
	//意味番号比較
	Result = x->getMeanNo().CompareTo( y->getMeanNo() );
	if( Result != 0 ) return Result;

	//分類順位比較
	for( i = 0; i < x->MeanGroupCount(); i++ )
	{
		//一致すれば終了
		Result = x->getGroupRank(i).CompareTo( y->getGroupRank(0) );
		if( Result == 0 ) return 0;
	}
	//一致しない
	return Result;

}

//***** 翻訳比較
Int32 WordDic::WDTransComparer::Compare(WDTrans^ x, WDTrans^ y)
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

	//WordID比較
	if( x->getWordID() < y->getWordID() )
	{
		return -1;
	}else if( x->getWordID() > y->getWordID() ){
		return 1;
	}
	//意味番号比較
	Result = x->getMeanNo().CompareTo( y->getMeanNo() );
	return Result;

	//完全一致
	return 0;

}

//***** 関連語比較
Int32 WordDic::WDRelationComparer::Compare(WDRelation^ x, WDRelation^ y)
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

	//WordID比較
	if( x->getWordID() < y->getWordID() )
	{
		return -1;
	}else if( x->getWordID() > y->getWordID() ){
		return 1;
	}
	//意味番号比較
	Result = x->getMeanNo().CompareTo( y->getMeanNo() );
	if( Result != 0 ) return Result;

	//完全一致
	return 0;

}