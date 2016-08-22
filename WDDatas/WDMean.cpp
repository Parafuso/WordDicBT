//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�f�[�^�N���X�@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDMean		: �Ӗ��N���X
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//�P�ꎫ�T�f�[�^�p��O�N���X
#include "WDDatas.h"			//�P�ꎫ�T�f�[�^�N���X
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
//#include "FJIsamDef.h"			//ISAM�p��`�t�@�C��

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDMean	: �Ӗ��N���X
//------------------------------------------------------------------------------
//***** �R���X�g���N�^�P(�V�K�f�[�^)
WDDatas::WDMean::WDMean()
 //: WDRec()
{
	//-- ��r���� --//
	if( WDMeanGrpComp == nullptr ) WDMeanGrpComp = gcnew WDMeanGrpComparer();

	//-- �ϐ���` --//
	WordID = 0;
	MeanNo = 0;
	MeanGroup = gcnew List<WDMeanGroup^>();
	Speech = 0;
	Rank = 0;

	WDRec::setRecord( nullptr );

}

//***** �R���X�g���N�^�Q(�Ǎ��f�[�^)
WDDatas::WDMean::WDMean( DataRecord^ inRec )
{

	//-- ��r���� --//
	if( WDMeanGrpComp == nullptr ) WDMeanGrpComp = gcnew WDMeanGrpComparer();

	//-- �ϐ���` --//
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

	//-- �����`�F�b�N --//
	if( inRec->getDataLength() != WDMEAN_LENGTH &&
		inRec->getDataLength() != WDMEAN_SHORT_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h���Ӗ��f�[�^�ł͂���܂���B" );
		tmpWDDataException->ErrorCode  = 10201;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	
	//-- �f�[�^�ݒ� --//
	try
	{
		setRecord( inRec );
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�ݒ�ŃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 10201;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//***** �f�X�g���N�^
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
//�@�f�[�^���R�[�h����
//------------------------------------------------------------------------------
//***** �f�[�^���R�[�h�擾
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

	//-- ���ޏ��`�F�b�N --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ��f�[�^�����݂��܂���B" );
		tmpWDDataException->ErrorCode  = 10202;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	//-- �����`�F�b�N --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 10202;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	try
	{
		//-- ���ޑI�� --//
		tmpWDMeanGroup = MeanGroup[inIdx];
		tmpRec = tmpWDMeanGroup->DataRec;
		if( tmpRec == nullptr )
		{
			tmpRec = gcnew DataRecord();
		}

		//-- �f�[�^�ݒ� --//
		if( tmpWDMeanGroup->MeanFlg == 0  )
		{
			rtData = gcnew array<Byte>( WDMEAN_LENGTH );
		}else{
			rtData = gcnew array<Byte>( WDMEAN_SHORT_LENGTH );
		}

		tmpPos = 0;

		//�P��ID
		FJIFuncs::Int32ToArray( WordID, rtData, tmpPos );
		tmpPos += WDMEAN_WORDIDLEN;
		//�Ӗ�No
		FJIFuncs::Int32ToArray( MeanNo, rtData, tmpPos );
		tmpPos += WDMEAN_MEANNOLEN;

		//�Ӗ�Flg
		FJIFuncs::Int32ToArray( tmpWDMeanGroup->MeanFlg, rtData, tmpPos );
		tmpPos += WDMEAN_MEANFLGLEN;
		//���ޑ�
		Buffer::BlockCopy( tmpWDMeanGroup->GroupGt, 0, rtData, tmpPos, WDMEAN_GROUPGTLEN );
		tmpPos += WDMEAN_GROUPGTLEN;
		//���ޏ�
		Buffer::BlockCopy( tmpWDMeanGroup->GroupLt, 0, rtData, tmpPos, WDMEAN_GROUPLTLEN );
		tmpPos += WDMEAN_GROUPLTLEN;
		//���ޏ���
		FJIFuncs::Int32ToArray( tmpWDMeanGroup->GroupRank, rtData, tmpPos );
		tmpPos += WDMEAN_GROUPRANKLEN;


		if( tmpWDMeanGroup->MeanFlg == 0 )
		{

			//�i��
			rtData[tmpPos] = Speech;
			tmpPos += WDMEAN_SPEECHLEN;
			//�����N
			FJIFuncs::Int32ToArray( Rank, rtData, tmpPos );
			tmpPos += WDMEAN_RANKLEN;
			//�Ӗ�
			FJIFuncs::StringToArray( Mean, rtData, tmpPos, WDMEAN_MEANLEN );
			tmpPos += WDMEAN_MEANLEN;
			//�ᕶ
			FJIFuncs::StringToArray( Example, rtData, tmpPos, WDMEAN_EXAMPLELEN );
			tmpPos += WDMEAN_EXAMPLELEN;

			//�\��
			for(Int32 i = 0; i < WDMEAN_RESERVEDLEN; i++ )
			{
				Buffer::SetByte( rtData,tmpPos, 0 );
				tmpPos++;
			}

			//-- ���R�[�h�Ƀf�[�^�Z�b�g( MeanFlg 0 ) --//
			tmpRec->setData( rtData, WDMEAN_LENGTH );
		}else{
			//-- ���R�[�h�Ƀf�[�^�Z�b�g( MeanFlg 1�ȏ� ) --//
			tmpRec->setData( rtData, WDMEAN_SHORT_LENGTH );
		}

		
	}catch( Exception^ exp ){
		if( rtData != nullptr ) delete rtData;

		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�擾�ŃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 10202;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
	//-- ����I�� --//
	return tmpRec;
}

//***** �f�[�^���R�[�h�ݒ�
void WDDatas::WDMean::setRecord( DataRecord^ inRec )
{
	Int32			tmpWordID;
	Int32			tmpMeanNo;
	WDMeanGroup^	tmpWDMeanGroup;
	array<Byte>^	tmpDat;
	Int32			tmpPos;

	//-- �����`�F�b�N --//
	if( inRec == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̓f�[�^���R�[�h���ݒ肳��Ă��܂���B" );
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
				L"�R�s�[���f�[�^��������������܂���B" );
			tmpWDDataException->ErrorCode  = 10203;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}

		tmpPos = 0;

		//�P��ID
		tmpWordID = FJIFuncs::ArrayToInt32( tmpDat, tmpPos );
		tmpPos += WDMEAN_WORDIDLEN;
		//�Ӗ�No
		tmpMeanNo = FJIFuncs::ArrayToInt32( tmpDat, tmpPos );
		tmpPos += WDMEAN_MEANNOLEN;

		if( MeanGroup->Count != 0 && 
			( tmpWordID != WordID || tmpMeanNo != MeanNo ) )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�Y������Ӗ��f�[�^�ł͂���܂���B" );
			tmpWDDataException->ErrorCode  = 10203;
			tmpWDDataException->ErrorCode2 = 3;
			throw tmpWDDataException;
	
		}
		WordID = tmpWordID;
		MeanNo = tmpMeanNo;

		//�Ӗ��O���[�v
		tmpWDMeanGroup = gcnew WDMeanGroup();

		//�Ӗ��t���O
		tmpWDMeanGroup->MeanFlg = FJIFuncs::ArrayToInt32( tmpDat, tmpPos );
		tmpPos += WDMEAN_MEANFLGLEN;
	
		//���ޑ�
		tmpWDMeanGroup->GroupGt = gcnew array<Byte>(WDMEAN_GROUPGTLEN); 
		Buffer::BlockCopy( tmpDat, tmpPos, tmpWDMeanGroup->GroupGt, 0, WDMEAN_GROUPGTLEN );
		tmpPos += WDMEAN_GROUPGTLEN;
		//���ޏ�
		tmpWDMeanGroup->GroupLt = gcnew array<Byte>(WDMEAN_GROUPLTLEN); 
		Buffer::BlockCopy( tmpDat, tmpPos, tmpWDMeanGroup->GroupLt, 0, WDMEAN_GROUPLTLEN );
		tmpPos += WDMEAN_GROUPLTLEN;
		//���ޏ���
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
						L"�f�[�^��������������܂���B" );
					tmpWDDataException->ErrorCode  = 10203;
					tmpWDDataException->ErrorCode2 = 4;
					throw tmpWDDataException;
				}
			}else{
				if( inRec->getDataLength() != WDMEAN_LENGTH )
				{
					WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
						L"�f�[�^��������������܂���B" );
					tmpWDDataException->ErrorCode  = 10203;
					tmpWDDataException->ErrorCode2 = 5;
					throw tmpWDDataException;
				}

				//�i��
				Speech = tmpDat[tmpPos];
				tmpPos += WDMEAN_SPEECHLEN;
				//�����N
				Rank = FJIFuncs::ArrayToInt32( tmpDat, tmpPos );
				tmpPos += WDMEAN_RANKLEN;
				//�Ӗ�
				if( Mean != nullptr ) delete Mean;
				Mean = FJIFuncs::ArrayToString( tmpDat, tmpPos, WDMEAN_MEANLEN );
				tmpPos += WDMEAN_MEANLEN;
				//�ᕶ
				if( Example != nullptr ) delete Example;
				Example = FJIFuncs::ArrayToString( tmpDat, tmpPos, WDMEAN_EXAMPLELEN );
				tmpPos += WDMEAN_EXAMPLELEN;
	
			}
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�ݒ莞�ɃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 10203;
		tmpWDDataException->ErrorCode2 = 6;
		throw tmpWDDataException;

	}finally{
		if( tmpDat != nullptr ) delete tmpDat;
	}

}

//***** �f�[�^���R�[�h����
void WDDatas::WDMean::Write( void )
{
	Write( 0 );
}

void WDDatas::WDMean::Write( Int32 inIdx )
{
	DataRecord^ tmpRec;
	FIsam^ tmpParent;

	//-- ���ޏ��`�F�b�N --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ��f�[�^�����݂��܂���B" );
		tmpWDDataException->ErrorCode  = 10204;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	//-- �����`�F�b�N --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 10204;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^���R�[�h�`�F�b�N --//
	if( MeanGroup[inIdx]->DataRec == nullptr )
	{
		return;
	}

	//-- ISAM�t�@�C���`�F�b�N --//
	try
	{
		tmpParent = safe_cast<FIsam^>( MeanGroup[inIdx]->DataRec->getParentFile() );
		if( tmpParent == nullptr )
		{
			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAM�t�@�C�����s���ł��B", exp );
		tmpWDDataException->ErrorCode  = 10204;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//-- ���R�[�h����(�����Œǉ��A�X�V���f) --//
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
				L"���R�[�h�����͂ł��܂���B" );
			tmpWDDataException->ErrorCode  = 10204;
			tmpWDDataException->ErrorCode2 = 4;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10204;
		tmpWDDataException->ErrorCode2 = 5;
		throw tmpWDDataException;
	}
}

//***** �f�[�^���R�[�h����
void WDDatas::WDMean::Delete( void )
{
	Delete( 0 );
}

void WDDatas::WDMean::Delete( Int32 inIdx )
{
	DataRecord^ tmpRec;
	FIsam^ tmpParent;

	//-- ���ޏ��`�F�b�N --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ��f�[�^�����݂��܂���B" );
		tmpWDDataException->ErrorCode  = 10205;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	//-- �����`�F�b�N --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 10205;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//--Isam���R�[�h�폜 --//
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
			L"ISAM�f�[�^�폜�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10205;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//--�@�f�[�^�N���A --//
	try
	{
		//-- ���ލ폜 --//
		if( MeanGroup[inIdx]->GroupGt != nullptr ) delete MeanGroup[inIdx]->GroupGt;
		if( MeanGroup[inIdx]->GroupLt != nullptr ) delete MeanGroup[inIdx]->GroupLt;
		delete MeanGroup[inIdx];
		MeanGroup->RemoveAt( inIdx );

		//-- �A�C�e�������S�ɂȂ� --//
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
			L"�f�[�^�폜�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10205;
		tmpWDDataException->ErrorCode2 = 4;
		throw tmpWDDataException;
	}


}
//------------------------------------------------------------------------------
//�@��񑀍�
//------------------------------------------------------------------------------
//***** �f�[�^�����擾
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

//***** �f�[�^���R�[�h���擾
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
//�@�A�C�e������
//------------------------------------------------------------------------------
//***** �P��ID�擾
Int32 WDDatas::WDMean::getWordID( void )
{
	return WordID;
}

//***** �Ӗ�No�擾
Int32 WDDatas::WDMean::getMeanNo( void )
{
	return MeanNo;
}

//***** ���ގ擾
WDMeanGroup^ WDDatas::WDMean::getGroup( Int32 inIdx )
{
	WDMeanGroup^ tmpGroup;
	WDMeanGroup^ rtGroup;

	//-- ���ޏ��`�F�b�N --//
	if( MeanGroup->Count == 0 )
	{
		return nullptr;
	}

	//-- �����`�F�b�N --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�̎w�肪�s���ł��B" );
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
			L"���ގ擾���ɃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 10211;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
		return rtGroup;
}

Int32 WDDatas::WDMean::getMeanFlg( Int32 inIdx )
{
	//-- ���ޏ��`�F�b�N --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޏ�񂪂���܂���B" );
		tmpWDDataException->ErrorCode  = 10212;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- �����`�F�b�N --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 10212;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	try
	{
		return MeanGroup[inIdx]->MeanFlg;

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ��t���O�擾���ɃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 10212;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** ���ޑ�擾
array<Byte>^ WDDatas::WDMean::getGroupGt( Int32 inIdx, array<Byte>^ inData )
{
	array<Byte>^ rtData;

	//-- ���ޏ��`�F�b�N --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޏ�񂪂���܂���B" );
		tmpWDDataException->ErrorCode  = 10206;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- �����`�F�b�N --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 10206;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	try
	{
		//-- �f�[�^�̈�ݒ� --//
		if( inData != nullptr )
		{
			if( inData->Length < WDMEAN_GROUPGTLEN )
			{
				WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
					L"�R�s�[��f�[�^�����Z�����܂��B" );
				tmpWDDataException->ErrorCode  = 10206;
				tmpWDDataException->ErrorCode2 = 3;
				throw tmpWDDataException;
			}
			rtData = inData;
		}else{

			rtData = gcnew array<Byte>(WDMEAN_GROUPGTLEN);
		}

		//-- �f�[�^�R�s�[ --//
		Buffer::BlockCopy( MeanGroup[inIdx]->GroupGt, 0, rtData, 0, WDMEAN_GROUPGTLEN );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10206;
		tmpWDDataException->ErrorCode2 = 4;
		throw tmpWDDataException;
	}

	//-- ����I�� --//
	return rtData;

}

//***** ���ޏ��擾
array<Byte>^ WDDatas::WDMean::getGroupLt( Int32 inIdx, array<Byte>^ inData )
{
	array<Byte>^ rtData;

	//-- ���ޏ��`�F�b�N --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޏ�񂪂���܂���B" );
		tmpWDDataException->ErrorCode  = 10207;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- �����`�F�b�N --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 10207;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	try
	{
		//-- �f�[�^�̈�ݒ� --//
		if( inData != nullptr )
		{
			if( inData->Length < WDMEAN_GROUPLTLEN )
			{
				WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
					L"�R�s�[��f�[�^�����Z�����܂��B" );
				tmpWDDataException->ErrorCode  = 10207;
				tmpWDDataException->ErrorCode2 = 3;
				throw tmpWDDataException;
			}
			rtData = inData;
		}else{
			rtData = gcnew array<Byte>(WDMEAN_GROUPLTLEN);
		}

		//-- �f�[�^�R�s�[ --//
		Buffer::BlockCopy( MeanGroup[inIdx]->GroupLt, 0, rtData, 0, WDMEAN_GROUPLTLEN );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10207;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//-- ����I�� --//
	return rtData;
}

//***** ���ޏ��ʎ擾
Int32 WDDatas::WDMean::getGroupRank( Int32 inIdx )
{
	//-- ���ޏ��`�F�b�N --//
	if( MeanGroup->Count == 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޏ�񂪂���܂���B" );
		tmpWDDataException->ErrorCode  = 10214;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- �����`�F�b�N --//
	if( inIdx < 0 || inIdx >= MeanGroup->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 10214;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	try
	{
		return MeanGroup[inIdx]->GroupRank;

	}catch(Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ރ����N�̎擾���ɃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 10214;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** �i���擾
Byte WDDatas::WDMean::getSpeech( void )
{
	return Speech;
}

//***** �����N�擾
Int32 WDDatas::WDMean::getRank( void )
{
	return Rank;
}

//***** �Ӗ��擾
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

//***** �ᕶ�擾
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

//***** ���ސ��擾
Int32 WDDatas::WDMean::MeanGroupCount( void )
{
	return MeanGroup->Count;
}									

//------------------------------------------------------------------------------
//***** �P��ID�ݒ�
void WDDatas::WDMean::setWordID( Int32 inData )
{
	//-- �����`�F�b�N --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�P��ID���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10208;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	WordID = inData;
}

//***** �P��ID�ݒ�
void WDDatas::WDMean::setMeanNo( Int32 inData )
{
	//-- �����`�F�b�N --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ�No���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10209;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	MeanNo = inData;
}

//***** ���ސݒ�
void WDDatas::WDMean::setGroup( Int32 inMeanFlg, array<Byte>^ inGroupGt, 		
					array<Byte>^ inGroupLt, Int32 inGroupRank )
{
	WDMeanGroup^ tmpWDMeanGroup;

	//-- �����`�F�b�N --//
	if( inMeanFlg < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ��t���O���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inGroupGt == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޑ傪���ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	if( inGroupGt->Length < WDMEAN_GROUPGTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޑ傪�Z�����܂��B" );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
	if( inGroupLt == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޏ������ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 4;
		throw tmpWDDataException;
	}
	if( inGroupLt->Length < WDMEAN_GROUPLTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޏ����Z�����܂��B" );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 5;
		throw tmpWDDataException;
	}
	//-- �����`�F�b�N --//
	if( inGroupRank < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޏ��ʂ��s���ł��B" );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 6;
		throw tmpWDDataException;
	}

	try
	{
		//�Ӗ��t���O
		tmpWDMeanGroup = gcnew WDMeanGroup;
		tmpWDMeanGroup->MeanFlg = inMeanFlg;

		//-- ���ރR�s�[ --//
		//���ޑ�
		tmpWDMeanGroup->GroupGt = gcnew array<Byte>(WDMEAN_GROUPGTLEN);
		Buffer::BlockCopy( inGroupGt, 0, tmpWDMeanGroup->GroupGt, 0, WDMEAN_GROUPGTLEN );
		//���ޏ�
		tmpWDMeanGroup->GroupLt = gcnew array<Byte>(WDMEAN_GROUPLTLEN);
		Buffer::BlockCopy( inGroupLt, 0, tmpWDMeanGroup->GroupLt, 0, WDMEAN_GROUPLTLEN );
		//���ރ����N
		tmpWDMeanGroup->GroupRank = inGroupRank;
		//�f�[�^���R�[�h
		tmpWDMeanGroup->DataRec = nullptr;

		//�Ӗ��O���[�v�ǉ�
		addMeanGrp( tmpWDMeanGroup );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ސݒ蒆�ɃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 10215;
		tmpWDDataException->ErrorCode2 = 6;
		throw tmpWDDataException;
	}
}

//***** �i���ݒ�
void WDDatas::WDMean::setSpeech( Byte inData )
{
	Speech = inData;
}

//***** �����N�ݒ�
void WDDatas::WDMean::setRank( Byte inData )
{
	if( inData < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�����N���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10219;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	Rank = inData;
}

//***** �Ӗ��ݒ�
void WDDatas::WDMean::setMean( String^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ������ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10213;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDMEAN_MEANLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ����������܂��B" );
		tmpWDDataException->ErrorCode  = 10213;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		if( Mean != nullptr )
		{
			delete Mean;
		}
		Mean = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ��̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10213;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** �Ӗ��ݒ�
void WDDatas::WDMean::setExample( String^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ������ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10217;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDMEAN_EXAMPLELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ����������܂��B" );
		tmpWDDataException->ErrorCode  = 10217;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		if( Example != nullptr )
		{
			delete Example;
		}
		Example = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ��̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10217;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}

//***** �Ӗ��}�[�W
void WDDatas::WDMean::MergeMean( WDMean^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		return;
	}

	if( WordID != inData->WordID ||
		MeanNo != inData->MeanNo )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̈Ӗ��͌����ł��܂���B" );
		tmpWDDataException->ErrorCode  = 10218;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}

	try
	{
		for each( WDMeanGroup^ tmpWDMeanGroup in inData->MeanGroup )
		{
			addMeanGrp( tmpWDMeanGroup );

			//�i��
			if( tmpWDMeanGroup->MeanFlg == 0 &&
				Speech == 0 )
			{
				Speech = inData->Speech;
			}
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ��̌������ɃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 10218;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;

	}

		
	//�Ӗ�
	if( Mean == nullptr )
	{
		Mean = String::Copy( inData->Mean );
	}

	//�ᕶ
	if( Example == nullptr )
	{
		Example = String::Copy( inData->Example );
	}

}								

//***** �Ӗ��O���[�v�ǉ�
Int32 WDDatas::WDMean::addMeanGrp( WDMeanGroup^ inMeanGrp )
{

	//-- �����`�F�b�N --//
	if( inMeanGrp == nullptr )
	{
		return -1;
	}

	//-- �����ǉ� --//
	for each( WDMeanGroup^ tmpMeanGrp in MeanGroup )
	{
		if( WDMeanGrpComp->Compare( tmpMeanGrp, inMeanGrp ) == 0 )
		{
			return -1;
		}
	
	}
	//-- ���ޒǉ� --//
	MeanGroup->Add( inMeanGrp );
	//-- ���ރ\�[�g --//
	MeanGroup->Sort( WDMeanGrpComp );

	//-- ����I�� --//
	return 0;
}

//***** �Ӗ��O���[�v��r
Int32 WDDatas::WDMeanGrpComparer::Compare( WDMeanGroup^ x, WDMeanGroup^ y)
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

	//�Ӗ��t���O��r
	if( x->MeanFlg < y->MeanFlg )
	{
		return -1;
	}else if( x->MeanFlg > y->MeanFlg ){
		return 1;
	}
	
	//���ޑ��r
	Result = x->GroupGt[0].CompareTo( y->GroupGt[0] );
	if( Result == 0 ) return Result;
	Result = x->GroupGt[1].CompareTo( y->GroupGt[1] );
	if( Result == 0 ) return Result;

	//���ޏ���r
	Result = x->GroupLt[0].CompareTo( y->GroupLt[0] );
	if( Result == 0 ) return Result;
	Result = x->GroupLt[1].CompareTo( y->GroupLt[1] );
	
	//��r����
	return Result;

}