//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�p�N���X�@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDWordListBox : �P�ꌟ�����ʕ\���p���X�g�{�b�N�X
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDWordList.h"			//�P�ꌟ�����ʕ\���p���X�g�{�b�N�X
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
#include "WDWordGrp.h"			//�P�ꎫ�T���

//------------------------------------------------------------------------------
//�@�\�[�g���@�ݒ�A�m�F
//------------------------------------------------------------------------------
//----- �\�[�g���ݒ�
void WordDic::WDWordList::setSortOrder( Int32 inSrtType,										
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
Int32 WordDic::WDWordList::getSortType( void )
{
	return srtType;
}

//----- �\�[�g�P��P
Int32 WordDic::WDWordList::getSortWord1( void )
{
	return srtWord1;
}

//----- �\�[�g�P��Q
Int32 WordDic::WDWordList::getSortWord2( void )
{
	return srtWord2;
}

//------------------------------------------------------------------------------
//�@�\�[�g
//------------------------------------------------------------------------------
//-- �\�[�g
void WordDic::WDWordList::Sort()
{
	//-- �A�C�e����1�ȉ��Ȃ牽�����Ȃ�
	if( Items->Count > 1 )
	{
		return;
	}

	try
	{
	    Int32 tmpCnt = Items->Count - 1;
		while( tmpCnt  >= 1 )
		{
			WDWordGrp^ chkWDWordGrp1 = safe_cast<WDWordGrp^>( Items[ tmpCnt ] );
			WDWordGrp^ chkWDWordGrp2 = safe_cast<WDWordGrp^>( Items[ tmpCnt -1 ] );

			//-- �O���[�v������
			if( srtType == schGrp )
			{
				WDMean^ tmpWDMean1 = chkWDWordGrp1->getSchMean();
				WDMean^ tmpWDMean2 = chkWDWordGrp2->getSchMean();

				//�A�C�e���P�F�Ӗ������ёւ��w�薳���A�A�C�e���Q�F�Ӗ������בւ��w�肠��B
				//�I��
				if( tmpWDMean1->getGroupRank() == 0 &&
					tmpWDMean2->getGroupRank() != 0 )
				{
					return;

				//�A�C�e���P�F�Ӗ������ёւ��w�肠��A�A�C�e���Q�F�Ӗ������בւ��w��Ȃ��B
				//���������ւ���
				}else if( tmpWDMean1->getGroupRank() != 0 &&
						tmpWDMean2->getGroupRank() == 0 )		{
					Items[ tmpCnt ] = chkWDWordGrp2;
					Items[ tmpCnt - 1 ] = chkWDWordGrp1;
					break;

				//�A�C�e���P���ёւ����� > �A�C�e���Q���ёւ�����
				//�I��
				}else if( tmpWDMean1->getGroupRank() > tmpWDMean2->getGroupRank() ) {
					return;
		
				//�A�C�e���P���ёւ����� < �A�C�e���Q���ёւ�����
				//���������ւ���
				}else if( tmpWDMean1->getGroupRank() < tmpWDMean2->getGroupRank() ) {
					Items[ tmpCnt ] = chkWDWordGrp2;
					Items[ tmpCnt - 1 ] = chkWDWordGrp1;
					break;
				}
	
			}

			//���t�ŕ��ёւ�
			for( Int32 i = 0; i < 2; i++ )
			{
				//���t�̃\�[�g���ڂ�����
				Int32 schWord;
				Int32 cmpVal;

				WDWord^ chkWord1 = chkWDWordGrp1->getBaseWord();
				WDWord^ chkWord2 = chkWDWordGrp2->getBaseWord();
		
				if( i == 0 )
				{
					schWord = srtWord1;
				}else{
					schWord = srtWord2;
				}
					
				//�\�[�g�P�ꂪ���w��Ȃ�I��
				if( schWord == 0 )
				{
					return;
				}

				//�P��
				if( schWord == 1)
				{
					cmpVal = String::Compare( chkWord1->getWord( nullptr ), chkWord2->getWord( nullptr ) );
					if( cmpVal < 0 )
					{
						Items[ tmpCnt ] = chkWDWordGrp2;
						Items[ tmpCnt - 1 ] = chkWDWordGrp1;
						break;
					}else if( cmpVal > 0 ) {
						return;
					}
		
				//�ǂݕ��P
				}else if( schWord == 2 ) {						break;
					cmpVal = String::Compare( chkWord1->getRead1( nullptr ), chkWord2->getRead1( nullptr ) );
					if( cmpVal < 0 )
					{
						Items[ tmpCnt ] = chkWDWordGrp2;
						Items[ tmpCnt - 1 ] = chkWDWordGrp1;
						break;
					}else if( cmpVal > 0 ) {
						return;
					}
		
				//�ǂݕ��Q
				}else if( schWord == 3 ) {
					cmpVal = String::Compare( chkWord1->getRead2( nullptr ), chkWord2->getRead2( nullptr ) );
					if( cmpVal < 0 )
					{
						Items[ tmpCnt ] = chkWDWordGrp2;
						Items[ tmpCnt - 1 ] = chkWDWordGrp1;
						break;
					}else if( cmpVal > 0 ) {
						return;
					}
				
				}
			}

			//�J�E���^�[���Z
			tmpCnt--;
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�\�[�g���ɃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 22002;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
}
