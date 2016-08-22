//------------------------------------------------------------------------------
//	’PŒê«“T@’PŒê«“Tƒrƒ…ƒA[—pƒNƒ‰ƒX@ƒ\[ƒX
//	Version 1.0		create date 2006/05/08
//	Copyright		“¡ˆäŒ³—Y
//------------------------------------------------------------------------------
//	classes
//		WDWordGrp : «“T’PŒêî•ñ
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDWordGrp.h"			//’PŒêƒf[ƒ^—p«‘
#include "WDDatasDef.h"			//’PŒê«“Tƒf[ƒ^’è”’è‹`

using namespace WDDatas;
//------------------------------------------------------------------------------
//@’PŒê«“T—pƒf[ƒ^”äŠr
//------------------------------------------------------------------------------
//***** ’PŒê”äŠr
Int32 WordDic::WDWordComparer::Compare(WDWord^ x, WDWord^ y)
{
	Int32 Result;

	//X‚ªnullptr‚Ìê‡
	if (x == nullptr)
	{
		if (y == nullptr)
		{
			return 0;
        }else{
			//X = nullptr , Y != nullptr ->Y‚ª¬‚³‚¢(æ‚É—ˆ‚é)
			return 1;
		}
	}

	//X != nullptr , Y = nullptr ->X‚ª¬‚³‚¢(æ‚É—ˆ‚é)
	if( y == nullptr )
	{
		return -1;
	}

	//WordID”äŠr
	if( x->getWordID() < y->getWordID() )
	{
		return -1;
	}else if( x->getWordID() > y->getWordID() ){
		return 1;
	}

	//“Ç‚İ•û”äŠr
	Result = x->getReadPattern().CompareTo( y->getReadPattern() );
	if( Result != 0 ) return Result;

	//Šˆ—pŒ`”äŠr
	Result = x->getPractical().CompareTo( y->getPractical() );
	if( Result != 0 ) return Result;

	//’P”•¡””äŠr
	Result = x->getPlurality().CompareTo( y->getPlurality() );
	if( Result != 0 ) return Result;

	//lÌ”äŠr
	Result = x->getGramatical().CompareTo( y->getGramatical() );
	if( Result != 0 ) return Result;

	//«•Ê”äŠr
	Result = x->getSex().CompareTo( y->getSex() );
	if( Result != 0 ) return Result;

	//Š®‘Sˆê’v
	return 0;

}

//***** ˆÓ–¡”äŠr
Int32 WordDic::WDMeanComparer::Compare(WDMean^ x, WDMean^ y)
{
	Int32 Result;
	Int32 i;

	//X‚ªnullptr‚Ìê‡
	if (x == nullptr)
	{
		if (y == nullptr)
		{
			return 0;
        }else{
			//X = nullptr , Y != nullptr ->Y‚ª¬‚³‚¢(æ‚É—ˆ‚é)
			return 1;
		}
	}

	//X != nullptr , Y = nullptr ->X‚ª¬‚³‚¢(æ‚É—ˆ‚é)
	if( y == nullptr )
	{
		return -1;
	}

	//WordID”äŠr
	if( x->getWordID() < y->getWordID() )
	{
		return -1;
	}else if( x->getWordID() > y->getWordID() ){
		return 1;
	}
	//ˆÓ–¡”Ô†”äŠr
	Result = x->getMeanNo().CompareTo( y->getMeanNo() );
	if( Result != 0 ) return Result;

	//•ª—Ş‡ˆÊ”äŠr
	for( i = 0; i < x->MeanGroupCount(); i++ )
	{
		//ˆê’v‚·‚ê‚ÎI—¹
		Result = x->getGroupRank(i).CompareTo( y->getGroupRank(0) );
		if( Result == 0 ) return 0;
	}
	//ˆê’v‚µ‚È‚¢
	return Result;

}

//***** –|–ó”äŠr
Int32 WordDic::WDTransComparer::Compare(WDTrans^ x, WDTrans^ y)
{
	Int32 Result;

	//X‚ªnullptr‚Ìê‡
	if (x == nullptr)
	{
		if (y == nullptr)
		{
			return 0;
        }else{
			//X = nullptr , Y != nullptr ->Y‚ª¬‚³‚¢(æ‚É—ˆ‚é)
			return 1;
		}
	}

	//X != nullptr , Y = nullptr ->X‚ª¬‚³‚¢(æ‚É—ˆ‚é)
	if( y == nullptr )
	{
		return -1;
	}

	//WordID”äŠr
	if( x->getWordID() < y->getWordID() )
	{
		return -1;
	}else if( x->getWordID() > y->getWordID() ){
		return 1;
	}
	//ˆÓ–¡”Ô†”äŠr
	Result = x->getMeanNo().CompareTo( y->getMeanNo() );
	return Result;

	//Š®‘Sˆê’v
	return 0;

}

//***** ŠÖ˜AŒê”äŠr
Int32 WordDic::WDRelationComparer::Compare(WDRelation^ x, WDRelation^ y)
{
	Int32 Result;

	//X‚ªnullptr‚Ìê‡
	if (x == nullptr)
	{
		if (y == nullptr)
		{
			return 0;
        }else{
			//X = nullptr , Y != nullptr ->Y‚ª¬‚³‚¢(æ‚É—ˆ‚é)
			return 1;
		}
	}

	//X != nullptr , Y = nullptr ->X‚ª¬‚³‚¢(æ‚É—ˆ‚é)
	if( y == nullptr )
	{
		return -1;
	}

	//WordID”äŠr
	if( x->getWordID() < y->getWordID() )
	{
		return -1;
	}else if( x->getWordID() > y->getWordID() ){
		return 1;
	}
	//ˆÓ–¡”Ô†”äŠr
	Result = x->getMeanNo().CompareTo( y->getMeanNo() );
	if( Result != 0 ) return Result;

	//Š®‘Sˆê’v
	return 0;

}