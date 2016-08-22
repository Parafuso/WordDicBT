//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�f�[�^�N���X�@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDRelation		: �֘A��N���X
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//�P�ꎫ�T�f�[�^�p��O�N���X
#include "WDDatas.h"			//�P�ꎫ�T�f�[�^�N���X
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
//#include "FJIsamDef.h"			//ISAM�p��`�t�@�C��

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDRelation		: �֘A��N���X
//------------------------------------------------------------------------------
//***** �R���X�g���N�^�P(�V�K�f�[�^)
WDDatas::WDRelation::WDRelation()
 //: WDRec()
{
	//-- �ϐ���` --//
	WordID = 0;
	MeanNo = 0;
	RelationType = gcnew List<Int32>();
	RelationID = gcnew List<Int32>();
	RelationNo = gcnew List<Int32>();
}

//***** �R���X�g���N�^�Q(�Ǎ��f�[�^)
WDDatas::WDRelation::WDRelation( DataRecord^ inRec )
{

	//-- �ϐ���` --//
	WordID = 0;
	MeanNo = 0;
	RelationType = gcnew List<Int32>();
	RelationID = gcnew List<Int32>();
	RelationNo = gcnew List<Int32>();

	if(inRec == nullptr )
	{
		return;
	}

	//-- �����`�F�b�N --//
	if( inRec->getDataLength() < WDRELATION_WORDIDLEN +
			WDRELATION_MEANNOLEN + WDRELATION_RELATIONCNTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h���Ӗ��f�[�^�ł͂���܂���B" );
		tmpWDDataException->ErrorCode  = 10601;
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
		tmpWDDataException->ErrorCode  = 10601;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//***** �f�X�g���N�^
WDDatas::WDRelation::~WDRelation()
{
	if( RelationType != nullptr ) delete RelationType;
	if( RelationID != nullptr ) delete RelationID;
	if( RelationNo != nullptr ) delete RelationNo;
}

//------------------------------------------------------------------------------
//�@�f�[�^���R�[�h����
//------------------------------------------------------------------------------
//***** �f�[�^���R�[�h�擾
DataRecord^ WDDatas::WDRelation::getRecord( void )
{
	DataRecord^ tmpRec;
	array<Byte>^ tmpDat;

	if( WDRec::getRecord() == nullptr )
	{
		try
		{
			tmpDat = getData( nullptr );
			tmpRec = gcnew DataRecord();
			tmpRec->setData( tmpDat, DataLength() );
			WDRec::setRecord( tmpRec );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^���R�[�h�擾�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10602;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}
	}else{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = WDRec::getRecord();
			tmpRec->setData( tmpDat, DataLength()  );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^���R�[�h�擾�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10602;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}

	delete tmpDat;

	//-- ����I�� --//
	return tmpRec;
}

//***** �f�[�^���R�[�h�ݒ�
void WDDatas::WDRelation::setRecord(  DataRecord^ inRec )
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
				L"�f�[�^���R�[�h�ݒ�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10603;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}
	}else{
		try
		{
			WDRec::setRecord( nullptr );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^���R�[�h�ݒ�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10603;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}
}

//***** �f�[�^���R�[�h����
void WDDatas::WDRelation::Write( void )
{
	FIsam^ tmpParent;

	//-- �f�[�^���R�[�h�`�F�b�N --//
	if( WDRec::getRecord() == nullptr )
	{
		return;
	}

	//-- ISAM�t�@�C���`�F�b�N --//
	try
	{
		tmpParent = safe_cast<FIsam^>( WDRec::getRecord()->getParentFile() );
		if( tmpParent == nullptr )
		{
			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAM�t�@�C�����s���ł��B", exp );
		tmpWDDataException->ErrorCode  = 10604;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- ���R�[�h����(�����Œǉ��A�X�V���f) --//
	try
	{
		if( WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_NEW )
		{
			tmpParent->AddRecord( getRecord() );
		}else if( WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_OLD ){
			tmpParent->UpdateRecord( getRecord() );
		}else{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"���R�[�h�폜�͂ł��܂���B" );
			tmpWDDataException->ErrorCode  = 10604;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10604;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** �f�[�^���R�[�h����
void WDDatas::WDRelation::Delete( void )
{
	FIsam^ tmpParent;

	//-- �f�[�^���R�[�h�`�F�b�N --//
	if( WDRec::getRecord() == nullptr )
	{
		//--�@�f�[�^�N���A --//
		WordID = 0;
		MeanNo = 0;
		RelationType->Clear();
		RelationID->Clear();
		RelationNo->Clear();
		
		return;
	}

	//-- ISAM�t�@�C���`�F�b�N --//
	try
	{
		tmpParent = safe_cast<FIsam^>( WDRec::getRecord()->getParentFile() );
		if( tmpParent == nullptr )
		{
			//--�@�f�[�^�N���A --//
			WordID = 0;
			MeanNo = 0;
			RelationType->Clear();
			RelationID->Clear();
			RelationNo->Clear();

			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAM�t�@�C�����s���ł��B", exp );
		tmpWDDataException->ErrorCode  = 10605;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- ���R�[�h�폜 --//
	try
	{
		if( WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_NEW )
		{
			;
		}else if( WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_OLD ){
			tmpParent->DeleteRecord( getRecord() );
		}else{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"���R�[�h�폜�͂ł��܂���B" );
			tmpWDDataException->ErrorCode  = 10605;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10605;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//--�@�f�[�^�N���A --//
	WordID = 0;
	MeanNo = 0;
	RelationType->Clear();
	RelationID->Clear();
	RelationNo->Clear();

}
//------------------------------------------------------------------------------
//�@��񑀍�
//------------------------------------------------------------------------------
//***** �f�[�^�����擾
Int32 WDDatas::WDRelation::DataLength( void )
{
	Int32 tmpRelationSize;

	//-- �ϒ������̃T�C�Y���擾
	if( RelationType == nullptr )
	{
		tmpRelationSize = 0;
	}else{
		tmpRelationSize = ( WDRELATION_RELATIONTYPELEN +
							WDRELATION_RELATIONIDLEN + WDRELATION_RELATIONNOLEN )
							* RelationType->Count;
	}

	return	WDRELATION_WORDIDLEN +
			WDRELATION_MEANNOLEN +
			WDRELATION_RELATIONCNTLEN +
			tmpRelationSize;
}

//***** �f�[�^���R�[�h���擾
Int32 WDDatas::WDRelation::RecLength()
{
	return DataRecord::getHeaderLength() + DataLength();
}

//------------------------------------------------------------------------------
//�@�A�C�e������
//------------------------------------------------------------------------------
//***** �P��ID�擾
Int32 WDDatas::WDRelation::getWordID( void )
{
	return WordID;
}

//***** �Ӗ�No�擾
Int32 WDDatas::WDRelation::getMeanNo( void )
{
	return MeanNo;
}

//***** �֘A��^�C�v�擾
Int32	WDDatas::WDRelation::getRelationType( Int32 inIdx )
{
	if( RelationType == nullptr ) return -1;

	if( inIdx < 0 || inIdx >= RelationType->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�w�肪�͈͊O�ł��B" );
		tmpWDDataException->ErrorCode  = 10606;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	return RelationType[inIdx];
}

//***** �֘A��ID�擾
Int32	WDDatas::WDRelation::getRelationID( Int32 inIdx )
{
	if( RelationID == nullptr ) return -1;

	if( inIdx < 0 || inIdx >= RelationID->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�w�肪�͈͊O�ł��B" );
		tmpWDDataException->ErrorCode  = 10607;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	return RelationID[inIdx];
}

//***** �֘A��Ӗ�No�擾
Int32	WDDatas::WDRelation::getRelationNo( Int32 inIdx )
{
	if( RelationNo == nullptr ) return -1;

	if( inIdx < 0 || inIdx >= RelationNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�w�肪�͈͊O�ł��B" );
		tmpWDDataException->ErrorCode  = 10617;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	return RelationNo[inIdx];
}

//------------------------------------------------------------------------------
//***** �P��ID�ݒ�
void WDDatas::WDRelation::setWordID( Int32 inData )
{
	//-- �����`�F�b�N --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�P��ID���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10608;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	WordID = inData;
}

//***** �P��ID�ݒ�
void WDDatas::WDRelation::setMeanNo( Int32 inData )
{
	//-- �����`�F�b�N --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ�No���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10609;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	MeanNo = inData;
}


//***** �֘A��^�C�v�ݒ�
void WDDatas::WDRelation::setRelationType( Int32 inData, Int32 inIdx )
{	
	//-- �����`�F�b�N --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�֘A��^�C�v���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10610;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	if( RelationType == nullptr || 
		inIdx < 0 || inIdx >= RelationType->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�w�肪�͈͊O�ł��B" );
		tmpWDDataException->ErrorCode  = 10610;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	//-- �f�[�^�ݒ� --//
	RelationType[inIdx] = inData;
}			

//***** �֘A��ID�ݒ�
void WDDatas::WDRelation::setRelationID( Int32 inData, Int32 inIdx )
{	
	//-- �����`�F�b�N --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�֘A��ID���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10611;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	if( RelationID == nullptr || 
		inIdx < 0 || inIdx >= RelationID->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�w�肪�͈͊O�ł��B" );
		tmpWDDataException->ErrorCode  = 10611;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	//-- �f�[�^�ݒ� --//
	RelationID[inIdx] = inData;
}

//***** �֘A��Ӗ�No�ݒ�
void WDDatas::WDRelation::setRelationNo( Int32 inData, Int32 inIdx )
{	
	//-- �����`�F�b�N --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�֘A��Ӗ�No���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10618;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	if( RelationNo == nullptr || 
		inIdx < 0 || inIdx >= RelationNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�w�肪�͈͊O�ł��B" );
		tmpWDDataException->ErrorCode  = 10618;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	//-- �f�[�^�ݒ� --//
	RelationNo[inIdx] = inData;
}	
//***** �֘A��ǉ�
void WDDatas::WDRelation::AddRelation( Int32 inType, Int32 inID, Int32 inNo )
{
	//-- �����`�F�b�N --//
	if( inType < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�֘A��^�C�v���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10612;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inID <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�֘A��ID���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10612;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	if( inNo <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�֘A��Ӗ�No���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10612;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	if( RelationType == nullptr )
	{
		RelationType = gcnew List<Int32>();
		RelationID = gcnew List<Int32>();
		RelationNo = gcnew List<Int32>();
	}

	RelationType->Add( inType );
	RelationID->Add( inID );
	RelationNo->Add( inNo );

	if( RelationType->Count != RelationID->Count ||
		RelationType->Count != RelationNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�֘A����ɕs�������������܂����B" );
		tmpWDDataException->ErrorCode  = 10612;
		tmpWDDataException->ErrorCode2 = 4;
		throw tmpWDDataException;
	}
}

//***** �֘A��폜
void WDDatas::WDRelation::RemoveRelation(int inIdx)
{
	//-- �����`�F�b�N --//
	if( RelationType == nullptr || 
		inIdx < 0 || inIdx >= RelationType->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�w�肪�͈͊O�ł��B" );
		tmpWDDataException->ErrorCode  = 10613;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	RelationType->RemoveAt( inIdx );
	RelationID->RemoveAt( inIdx );
	RelationNo->RemoveAt( inIdx );

	if( RelationType->Count != RelationID->Count ||
		RelationType->Count != RelationNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�֘A����ɕs�������������܂����B" );
		tmpWDDataException->ErrorCode  = 10613;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//***** �֘A�ꐔ�J�E���g
Int32 WDDatas::WDRelation::CountRelation( void )
{
	if( RelationType == nullptr )
	{
		return 0;
	}else{
		if( RelationType->Count != RelationID->Count )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�֘A����̃A�C�e�������B" );
			tmpWDDataException->ErrorCode  = 10616;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;

		}
		return RelationType->Count;
	}
	
}
//------------------------------------------------------------------------------
//�@�f�[�^����
//------------------------------------------------------------------------------
//***** �f�[�^�擾
array<Byte>^ WDDatas::WDRelation::getData( array<Byte>^ inData )
{
	array<Byte>^ rtData;
	Int32		 tmpPos;

	//-- �����`�F�b�N --//
	if( inData != nullptr &&
		inData->Length < DataLength() )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[��f�[�^�����Z�����܂��B" );
		tmpWDDataException->ErrorCode  = 10614;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		if( inData == nullptr )
		{
			rtData = gcnew array<Byte>( DataLength() );
		}else{
			rtData = inData;
		}

		tmpPos = 0;
	
		FJIFuncs::Int32ToArray( WordID, rtData, tmpPos );
		tmpPos += WDRELATION_WORDIDLEN;

		FJIFuncs::Int32ToArray( MeanNo, rtData, tmpPos );
		tmpPos += WDRELATION_MEANNOLEN;

		FJIFuncs::Int32ToArray( CountRelation() , rtData, tmpPos );
		tmpPos += WDRELATION_RELATIONCNTLEN;

		for( Int32 i = 0; i < CountRelation(); i++ )
		{
			FJIFuncs::Int32ToArray( RelationType[i] , rtData, tmpPos );
			tmpPos += WDRELATION_RELATIONTYPELEN;

			FJIFuncs::Int32ToArray( RelationID[i] , rtData, tmpPos );
			tmpPos += WDRELATION_RELATIONIDLEN;

			FJIFuncs::Int32ToArray( RelationNo[i] , rtData, tmpPos );
			tmpPos += WDRELATION_RELATIONNOLEN;
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10614;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- ����I�� --//
	return rtData;
}

//***** �f�[�^�ݒ�
void WDDatas::WDRelation::setData( array<Byte>^ inData )
{
	Int32		tmpPos;
	Int32		tmpRelationCnt;

	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[���f�[�^�����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10615;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length < sizeof( Int32 ) * 3 && 
		(inData->Length -  sizeof( Int32 ) * 3 ) % ( sizeof(Int32) *2 ) != 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[���f�[�^��������������܂���B" );
		tmpWDDataException->ErrorCode  = 10615;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		tmpPos = 0;

		WordID = FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDTRANS_WORDIDLEN;

		MeanNo = FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDTRANS_MEANNOLEN;

		tmpRelationCnt =  FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDTRANS_TRANSIDCNTLEN;

		//�֘A�ꃊ�X�g������
		if( RelationType == nullptr )
		{
			RelationType = gcnew List<Int32>();
		}else{
			RelationType->Clear();
		}
		if( RelationID == nullptr )
		{
			RelationID = gcnew List<Int32>();
		}else{
			RelationID->Clear();
		}
		if( RelationNo == nullptr )
		{
			RelationNo = gcnew List<Int32>();
		}else{
			RelationNo->Clear();
		}

		//�ϒ��̃f�[�^���`�F�b�N
		if( inData->Length != WDTRANS_WORDIDLEN + WDTRANS_MEANNOLEN + WDTRANS_TRANSIDCNTLEN +
							+ (WDRELATION_RELATIONTYPELEN + WDRELATION_RELATIONIDLEN + WDRELATION_RELATIONNOLEN )
												* tmpRelationCnt )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[���f�[�^��������������܂���B" );
			tmpWDDataException->ErrorCode  = 10615;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;

		}

		for( Int32 i = 0; i < tmpRelationCnt; i++ )
		{
			Int32 tmpRelationType;
			Int32 tmpRelationID;
			Int32 tmpRelationNo;

			tmpRelationType =  FJIFuncs::ArrayToInt32( inData, tmpPos );
			RelationType->Add( tmpRelationType );
			tmpPos += WDRELATION_RELATIONTYPELEN;

			tmpRelationID =  FJIFuncs::ArrayToInt32( inData, tmpPos );
			RelationID->Add( tmpRelationID );
			tmpPos += WDRELATION_RELATIONIDLEN;

			tmpRelationNo =  FJIFuncs::ArrayToInt32( inData, tmpPos );
			RelationNo->Add( tmpRelationNo );
			tmpPos += WDRELATION_RELATIONNOLEN;
		};

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10615;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}