//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�p�N���X�@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDWordSchListComparer : �P�ꌟ�����ʕ\���p���X�g�{�b�N�X�\�[�g
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
#include "WDWordSchListSort.h"	//�P�ꌟ�����ʕ\���p���X�g�{�b�N�X�\�[�g

//------------------------------------------------------------------------------
//�@�\�[�g���@�ݒ�A�m�F
//------------------------------------------------------------------------------
//----- �\�[�g���ݒ�
void WordDic::WDWordSchListComparer::setSortOrder( Int32 inSrtType,										
							Int32 inSrtWord1, Int32 inSrtWord2 )
{
	//-- �����`�F�b�N --//
	if( inSrtType != schWord && inSrtType != schGrp )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�\�[�g�^�C�v���s���ł��B" );
		tmpWDDataException->ErrorCode  = 22001;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	if( inSrtWord1 < 0 && inSrtWord1 > 3 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�\�[�g�P��P���s���ł��B" );
		tmpWDDataException->ErrorCode  = 22001;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	if( inSrtWord2 < 0 && inSrtWord1 > 3 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�\�[�g�P��Q���s���ł��B" );
		tmpWDDataException->ErrorCode  = 22001;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//-- ���ڐݒ�
	srtType = inSrtType;
	srtWord1 = inSrtWord1;
	srtWord2 = inSrtWord2;
}

//----- �\�[�g�^�C�v
Int32 WordDic::WDWordSchListComparer::getSortType( void )
{
	return srtType;
}

//----- �\�[�g�P��P
Int32 WordDic::WDWordSchListComparer::getSortWord1( void )
{
	return srtWord1;
}

//----- �\�[�g�P��Q
Int32 WordDic::WDWordSchListComparer::getSortWord2( void )
{
	return srtWord2;
}

//------------------------------------------------------------------------------
//�@�\�[�g
//------------------------------------------------------------------------------
//-- �\�[�g
Int32 WordDic::WDWordSchListComparer::Compare(Object^ x, Object^ y)
{
	Int32 Result;

	WDWordGrp^ tmpWDWordGrp1 = safe_cast<WDWordGrp^>(x);
	WDWordGrp^ tmpWDWordGrp2 = safe_cast<WDWordGrp^>(y);


	//-- X��nullptr�̏ꍇ
	if (tmpWDWordGrp1 == nullptr)
	{
		if (tmpWDWordGrp2 == nullptr)
		{
			return 0;
        }else{
			//X = nullptr , Y != nullptr ->Y��������(��ɗ���)
			return 1;
		}
	}

	//-- X != nullptr , Y = nullptr ->X��������(��ɗ���)
	if( tmpWDWordGrp2 == nullptr )
	{
		return -1;
	}


	try
	{

		//-- �O���[�v������
		if( srtType == schGrp )
		{
			//�A�C�e���P�F�Ӗ������ёւ��w�薳���A�A�C�e���Q�F�Ӗ������בւ��w�肠��B
			//�I��
			if( tmpWDWordGrp1->getSchGroupRank() == 0 &&
				tmpWDWordGrp2->getSchGroupRank() != 0 )
			{
				return 1;

			//�A�C�e���P�F�Ӗ������ёւ��w�肠��A�A�C�e���Q�F�Ӗ������בւ��w��Ȃ��B
			//���������ւ���
			}else if( tmpWDWordGrp1->getSchGroupRank() != 0 &&
					  tmpWDWordGrp2->getSchGroupRank() == 0 )		{
				return -1;

			//�A�C�e���P���ёւ����� > �A�C�e���Q���ёւ�����
			//�I��
			}else if( tmpWDWordGrp1->getSchGroupRank() > tmpWDWordGrp2->getSchGroupRank() ) {
				return 1;
		
			//�A�C�e���P���ёւ����� < �A�C�e���Q���ёւ�����
			//���������ւ���
			}else if( tmpWDWordGrp1->getSchGroupRank() < tmpWDWordGrp2->getSchGroupRank() ) {
				return -1;
			}
	
		}

		//���t�ŕ��ёւ�
		for( Int32 i = 0; i < 2; i++ )
		{
			//���t�̃\�[�g���ڂ�����
			Int32 schWord;

			WDWord^ chkWord1 = tmpWDWordGrp1->getBaseWord();
			WDWord^ chkWord2 = tmpWDWordGrp2->getBaseWord();
		
			if( i == 0 )
			{
				schWord = srtWord1;
			}else{
				schWord = srtWord2;
			}
					
			//�\�[�g�P�ꂪ���w��Ȃ�I��
			if( schWord == 0 )
			{
				return 0;
			}

			//�P��
			if( schWord == 1)
			{
				Result = String::Compare( chkWord1->getWord( nullptr ), chkWord2->getWord( nullptr ) );
					if( Result < 0 )
					{
						return -1;

					}else if( Result > 0 ) {
						return 1;

					}
		
			//�ǂݕ��P
			}else if( schWord == 2 ) {
				Result = String::Compare( chkWord1->getRead1( nullptr ), chkWord2->getRead1( nullptr ) );
				if( Result < 0 ) 
				{
						return -1;

				}else if( Result > 0 ) {
						return 1;

				}
		
			//�ǂݕ��Q
			}else if( schWord == 3 ) {
				Result = String::Compare( chkWord1->getRead2( nullptr ), chkWord2->getRead2( nullptr ) );
				if( Result < 0 )
				{
						return -1;

				}else if( Result > 0 ) {
						return 1;

				}
				
			}

		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�\�[�g���ɃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 22002;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- ���S��v --//
	return 0;
}
