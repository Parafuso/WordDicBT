//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�f�[�^�N���X�@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDTrans		: �|��N���X
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//�P�ꎫ�T�f�[�^�p��O�N���X
#include "WDDatas.h"			//�P�ꎫ�T�f�[�^�N���X
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
//#include "FJIsamDef.h"			//ISAM�p��`�t�@�C��

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDTrans		: �|��N���X
//------------------------------------------------------------------------------
//***** �R���X�g���N�^�P(�V�K�f�[�^)
WDDatas::WDTrans::WDTrans()
 //: WDRec()
{
	//-- �ϐ���` --//
	WordID = 0;
	MeanNo = 0;

	TransID = gcnew List<Int32>();
	TransNo = gcnew List<Int32>();
}

//***** �R���X�g���N�^�Q(�Ǎ��f�[�^)
WDDatas::WDTrans::WDTrans( DataRecord^ inRec )
{

	//-- �ϐ���` --//
	WordID = 0;
	MeanNo = 0;
	TransID = gcnew List<Int32>();
	TransNo = gcnew List<Int32>();

	if(inRec == nullptr )
	{
		return;
	}

	//-- �����`�F�b�N --//
	if( inRec->getDataLength() < WDTRANS_WORDIDLEN + WDTRANS_MEANNOLEN + 
					WDTRANS_TRANSIDCNTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̃f�[�^���Z�����܂��B" );
		tmpWDDataException->ErrorCode  = 10501;
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
		tmpWDDataException->ErrorCode  = 10501;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//***** �f�X�g���N�^
WDDatas::WDTrans::~WDTrans()
{
	if( TransID != nullptr ) delete TransID;
	if( TransNo != nullptr ) delete TransNo;
}

//------------------------------------------------------------------------------
//�@�f�[�^���R�[�h����
//------------------------------------------------------------------------------
//***** �f�[�^���R�[�h�擾
DataRecord^ WDDatas::WDTrans::getRecord( void )
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
			tmpWDDataException->ErrorCode  = 10502;
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
			tmpWDDataException->ErrorCode  = 10502;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}

	delete tmpDat;

	//-- ����I�� --//
	return tmpRec;
}

//***** �f�[�^���R�[�h�ݒ�
void WDDatas::WDTrans::setRecord(  DataRecord^ inRec )
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
			tmpWDDataException->ErrorCode  = 10503;
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
			tmpWDDataException->ErrorCode  = 10503;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}
}

//***** �f�[�^���R�[�h����
void WDDatas::WDTrans::Write( void )
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
		tmpWDDataException->ErrorCode  = 10504;
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
			tmpWDDataException->ErrorCode  = 10504;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10504;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** �f�[�^���R�[�h����
void WDDatas::WDTrans::Delete( void )
{
	FIsam^ tmpParent;

	//-- �f�[�^���R�[�h�`�F�b�N --//
	if( WDRec::getRecord() == nullptr )
	{
		//--�@�f�[�^�N���A --//
		WordID = 0;
		MeanNo = 0;
		TransID->Clear();

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
			TransID->Clear();

			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAM�t�@�C�����s���ł��B", exp );
		tmpWDDataException->ErrorCode  = 10505;
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
			tmpWDDataException->ErrorCode  = 10505;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10505;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//--�@�f�[�^�N���A --//
	WordID = 0;
	MeanNo = 0;
	TransID->Clear();

}
//------------------------------------------------------------------------------
//�@��񑀍�
//------------------------------------------------------------------------------
//***** �f�[�^�����擾
Int32 WDDatas::WDTrans::DataLength( void )
{
	Int32 tmpTransIDSize;

	//-- �ϒ������̃T�C�Y���擾
	if( TransID == nullptr )
	{
		tmpTransIDSize = 0;
	}else{
		tmpTransIDSize = ( WDTRANS_TRANSIDLEN + WDTRANS_TRANSNOLEN ) * TransID->Count;
	}

	return	WDTRANS_WORDIDLEN +
			WDTRANS_MEANNOLEN +
			WDTRANS_TRANSIDCNTLEN +
			tmpTransIDSize;
}

//***** �f�[�^���R�[�h���擾
Int32 WDDatas::WDTrans::RecLength( void )
{
	return DataRecord::getHeaderLength() + DataLength();
}

//------------------------------------------------------------------------------
//�@�A�C�e������
//------------------------------------------------------------------------------
//***** �P��ID�擾
Int32 WDDatas::WDTrans::getWordID( void )
{
	return WordID;
}

//***** �Ӗ�No�擾
Int32 WDDatas::WDTrans::getMeanNo( void )
{
	return MeanNo;
}



//***** �|��ID�擾
Int32 WDDatas::WDTrans::getTransID( Int32 inIdx )
{
	if( TransID == nullptr ) return -1;

	if( inIdx < 0 || inIdx >= TransID->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�w�肪�͈͊O�ł��B" );
		tmpWDDataException->ErrorCode  = 10506;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	return TransID[inIdx];
}

//***** �|��Ӗ�No�擾
Int32 WDDatas::WDTrans::getTransNo( Int32 inIdx )
{
	if( TransNo == nullptr ) return -1;

	if( inIdx < 0 || inIdx >= TransNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�w�肪�͈͊O�ł��B" );
		tmpWDDataException->ErrorCode  = 10514;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	return TransNo[inIdx];
}

//------------------------------------------------------------------------------
//***** �P��ID�ݒ�
void WDDatas::WDTrans::setWordID( Int32 inData )
{
	//-- �����`�F�b�N --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�P��ID���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10507;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	WordID = inData;
}

//***** �P��ID�ݒ�
void WDDatas::WDTrans::setMeanNo( Int32 inData )
{
	//-- �����`�F�b�N --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ�No���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10508;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	MeanNo = inData;
}


//***** �|��ID�ݒ�
void WDDatas::WDTrans::setTransID( Int32 inData, Int32 inIdx )
{	
	//-- �����`�F�b�N --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�|��ID���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10509;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	if( TransID == nullptr || 
		inIdx < 0 || inIdx >= TransID->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�w�肪�͈͊O�ł��B" );
		tmpWDDataException->ErrorCode  = 10509;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	//-- �f�[�^�ݒ� --//
	TransID[inIdx] = inData;
}			

//***** �|��No�ݒ�
void WDDatas::WDTrans::setTransNo( Int32 inData, Int32 inIdx )
{	
	//-- �����`�F�b�N --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�|��Ӗ�No���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10515;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	if( TransID == nullptr || 
		inIdx < 0 || inIdx >= TransID->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�w�肪�͈͊O�ł��B" );
		tmpWDDataException->ErrorCode  = 10515;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
	
	//-- �f�[�^�ݒ� --//
	TransNo[inIdx] = inData;
}			

//***** �|��ID�ǉ�
void WDDatas::WDTrans::AddTransID( Int32 inID, Int32 inNo )
{
	//-- �����`�F�b�N --//
	if( inID <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�|��ID���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10510;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	if( inNo <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�|��Ӗ�No���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10510;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ǉ� --//
	if( TransID == nullptr )
	{
		TransID = gcnew List<Int32>();
	}
	TransID->Add( inID );

	if( TransNo == nullptr )
	{
		TransNo = gcnew List<Int32>();
	}
	TransNo->Add( inNo );

	//-- �����`�F�b�N --//
	if( TransID->Count != TransNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�|���񂪕s�����ł��B" );
		tmpWDDataException->ErrorCode  = 10510;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}


}

//***** �|��ID�폜
void WDDatas::WDTrans::RemoveTransID( Int32 inIdx)
{
	//-- �����`�F�b�N --//
	if( TransID == nullptr || 
		inIdx < 0 || inIdx >= TransID->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�w�肪�͈͊O�ł��B" );
		tmpWDDataException->ErrorCode  = 10511;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- �����`�F�b�N --//
	if( TransID->Count != TransNo->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�|���񂪕s�����ł��B" );
		tmpWDDataException->ErrorCode  = 10511;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	TransID->RemoveAt( inIdx );
	TransNo->RemoveAt( inIdx );

}

//***** �|��ID���J�E���g
Int32 WDDatas::WDTrans::CountTransID( void )
{
	if( TransID == nullptr )
	{
		return 0;
	}else{
		return TransID->Count;
	}
	
}
//------------------------------------------------------------------------------
//�@�f�[�^����
//------------------------------------------------------------------------------
//***** �f�[�^�擾
array<Byte>^ WDDatas::WDTrans::getData( array<Byte>^ inData )
{
	array<Byte>^ rtData;
	Int32		 tmpPos;

	//-- �����`�F�b�N --//
	if( inData != nullptr &&
		inData->Length < DataLength() )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[��f�[�^�����Z�����܂��B" );
		tmpWDDataException->ErrorCode  = 10512;
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
		tmpPos += WDTRANS_WORDIDLEN;

		FJIFuncs::Int32ToArray( MeanNo, rtData, tmpPos );
		tmpPos += WDTRANS_MEANNOLEN;

		FJIFuncs::Int32ToArray( CountTransID() , rtData, tmpPos );
		tmpPos += WDTRANS_TRANSIDCNTLEN;

		for( Int32 i = 0; i < TransID->Count; i++ )
		{
			FJIFuncs::Int32ToArray( TransID[i] ,rtData, tmpPos );
			tmpPos += WDTRANS_TRANSIDLEN;

			FJIFuncs::Int32ToArray( TransNo[i] ,rtData, tmpPos );
			tmpPos += WDTRANS_TRANSNOLEN;
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10512;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- ����I�� --//
	return rtData;
}

//***** �f�[�^�ݒ�
void WDDatas::WDTrans::setData( array<Byte>^ inData )
{
	Int32		tmpPos;
	Int32		tmpTransIDCnt;

	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[���f�[�^�����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10513;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length < sizeof( Int32 ) * 3 && 
		(inData->Length -  sizeof( Int32 ) * 3 ) % sizeof(Int32) != 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[���f�[�^��������������܂���B" );
		tmpWDDataException->ErrorCode  = 10513;
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

		tmpTransIDCnt =  FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDTRANS_TRANSIDCNTLEN;

		if( TransID == nullptr )
		{
			TransID = gcnew List<Int32>();
		}else{
			TransID->Clear();
		}

		if( TransNo == nullptr )
		{
			TransNo = gcnew List<Int32>();
		}else{
			TransNo->Clear();
		}

		//�ϒ��̃f�[�^���`�F�b�N
		if( inData->Length != sizeof( Int32) *3 + 
			( WDTRANS_TRANSIDLEN + WDTRANS_TRANSNOLEN ) * tmpTransIDCnt )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[���f�[�^��������������܂���B" );
			tmpWDDataException->ErrorCode  = 10513;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;

		}

		for( Int32 i = 0; i < tmpTransIDCnt; i++ )
		{
			Int32 tmpTransID;
			Int32 tmpTransNo;

			tmpTransID =  FJIFuncs::ArrayToInt32( inData, tmpPos );
			TransID->Add( tmpTransID );
			tmpPos += WDTRANS_TRANSIDLEN;

			tmpTransNo =  FJIFuncs::ArrayToInt32( inData, tmpPos );
			TransNo->Add( tmpTransNo );
			tmpPos += WDTRANS_TRANSNOLEN;

		};

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10513;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}