//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�p�N���X�@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDWordGrp : ���T�P����
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDWordGrp.h"			//�P��f�[�^�p����
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`

using namespace WDDatas;
//------------------------------------------------------------------------------
//�@�P�ꎫ�T�p�f�[�^��r
//------------------------------------------------------------------------------
//***** �P���r
Int32 WordDic::WDWordComparer::Compare(WDWord^ x, WDWord^ y)
{
	Int32 Result;

	//X��nullptr�̏ꍇ
	if (x == nullptr)
	{
		if (y == nullptr)
		{
			return 0;
        }else{
			//X = nullptr , Y != nullptr ->Y��������(��ɗ���)
			return 1;
		}
	}

	//X != nullptr , Y = nullptr ->X��������(��ɗ���)
	if( y == nullptr )
	{
		return -1;
	}

	//WordID��r
	if( x->getWordID() < y->getWordID() )
	{
		return -1;
	}else if( x->getWordID() > y->getWordID() ){
		return 1;
	}

	//�ǂݕ���r
	Result = x->getReadPattern().CompareTo( y->getReadPattern() );
	if( Result != 0 ) return Result;

	//���p�`��r
	Result = x->getPractical().CompareTo( y->getPractical() );
	if( Result != 0 ) return Result;

	//�P��������r
	Result = x->getPlurality().CompareTo( y->getPlurality() );
	if( Result != 0 ) return Result;

	//�l�̔�r
	Result = x->getGramatical().CompareTo( y->getGramatical() );
	if( Result != 0 ) return Result;

	//���ʔ�r
	Result = x->getSex().CompareTo( y->getSex() );
	if( Result != 0 ) return Result;

	//���S��v
	return 0;

}

//***** �Ӗ���r
Int32 WordDic::WDMeanComparer::Compare(WDMean^ x, WDMean^ y)
{
	Int32 Result;
	Int32 i;

	//X��nullptr�̏ꍇ
	if (x == nullptr)
	{
		if (y == nullptr)
		{
			return 0;
        }else{
			//X = nullptr , Y != nullptr ->Y��������(��ɗ���)
			return 1;
		}
	}

	//X != nullptr , Y = nullptr ->X��������(��ɗ���)
	if( y == nullptr )
	{
		return -1;
	}

	//WordID��r
	if( x->getWordID() < y->getWordID() )
	{
		return -1;
	}else if( x->getWordID() > y->getWordID() ){
		return 1;
	}
	//�Ӗ��ԍ���r
	Result = x->getMeanNo().CompareTo( y->getMeanNo() );
	if( Result != 0 ) return Result;

	//���ޏ��ʔ�r
	for( i = 0; i < x->MeanGroupCount(); i++ )
	{
		//��v����ΏI��
		Result = x->getGroupRank(i).CompareTo( y->getGroupRank(0) );
		if( Result == 0 ) return 0;
	}
	//��v���Ȃ�
	return Result;

}

//***** �|���r
Int32 WordDic::WDTransComparer::Compare(WDTrans^ x, WDTrans^ y)
{
	Int32 Result;

	//X��nullptr�̏ꍇ
	if (x == nullptr)
	{
		if (y == nullptr)
		{
			return 0;
        }else{
			//X = nullptr , Y != nullptr ->Y��������(��ɗ���)
			return 1;
		}
	}

	//X != nullptr , Y = nullptr ->X��������(��ɗ���)
	if( y == nullptr )
	{
		return -1;
	}

	//WordID��r
	if( x->getWordID() < y->getWordID() )
	{
		return -1;
	}else if( x->getWordID() > y->getWordID() ){
		return 1;
	}
	//�Ӗ��ԍ���r
	Result = x->getMeanNo().CompareTo( y->getMeanNo() );
	return Result;

	//���S��v
	return 0;

}

//***** �֘A���r
Int32 WordDic::WDRelationComparer::Compare(WDRelation^ x, WDRelation^ y)
{
	Int32 Result;

	//X��nullptr�̏ꍇ
	if (x == nullptr)
	{
		if (y == nullptr)
		{
			return 0;
        }else{
			//X = nullptr , Y != nullptr ->Y��������(��ɗ���)
			return 1;
		}
	}

	//X != nullptr , Y = nullptr ->X��������(��ɗ���)
	if( y == nullptr )
	{
		return -1;
	}

	//WordID��r
	if( x->getWordID() < y->getWordID() )
	{
		return -1;
	}else if( x->getWordID() > y->getWordID() ){
		return 1;
	}
	//�Ӗ��ԍ���r
	Result = x->getMeanNo().CompareTo( y->getMeanNo() );
	if( Result != 0 ) return Result;

	//���S��v
	return 0;

}