//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�f�[�^�N���X�@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDSegment	: �敪�N���X
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//�P�ꎫ�T�f�[�^�p��O�N���X
#include "WDDatas.h"			//�P�ꎫ�T�f�[�^�N���X
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
//#include "FJIsamDef.h"			//ISAM�p��`�t�@�C��

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDSegment	: �敪�N���X
//------------------------------------------------------------------------------
//***** �R���X�g���N�^�P(�V�K�f�[�^)
WDDatas::WDSegment::WDSegment()
{
	//-- �ϐ���` --//
	SegmentID = 0;
	SegmentNo = 0;
}

//***** �R���X�g���N�^�Q(�Ǎ��f�[�^)
WDDatas::WDSegment::WDSegment( DataRecord^ inRec )
{

	if(inRec == nullptr )
	{
		//-- �ϐ���` --//
		SegmentID = 0;
		SegmentNo = 0;
		return;
	}

	//-- �����`�F�b�N --//
	if( inRec->getDataLength() != WDSEGMENT_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h���敪�f�[�^�ł͂���܂���B" );
		tmpWDDataException->ErrorCode  = 10401;
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
		tmpWDDataException->ErrorCode  = 10401;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//***** �f�X�g���N�^
WDDatas::WDSegment::~WDSegment()
{
	if( Name != nullptr ) delete Name;
	if( ShortName != nullptr ) delete ShortName;
}

//------------------------------------------------------------------------------
//�@�f�[�^���R�[�h����
//------------------------------------------------------------------------------
//***** �f�[�^���R�[�h�擾
DataRecord^ WDDatas::WDSegment::getRecord( void )
{
	DataRecord^ tmpRec;
	array<Byte>^ tmpDat;

	if( WDRec::getRecord() == nullptr )
	{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = gcnew DataRecord();
			tmpRec->setData( tmpDat, WDSEGMENT_LENGTH );
			WDRec::setRecord( tmpRec );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^���R�[�h�擾�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10402;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}
	}else{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = WDRec::getRecord();
			tmpRec->setData( tmpDat, WDSEGMENT_LENGTH );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^���R�[�h�擾�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10402;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}

	delete tmpDat;

	//-- ����I�� --//
	return tmpRec;
}

//***** �f�[�^���R�[�h�ݒ�
void WDDatas::WDSegment::setRecord( DataRecord^ inRec )
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
			tmpWDDataException->ErrorCode  = 10403;
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
			tmpWDDataException->ErrorCode  = 10403;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}
}

//***** �f�[�^���R�[�h����
void WDDatas::WDSegment::Write( void )
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
		tmpWDDataException->ErrorCode  = 10404;
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
			tmpWDDataException->ErrorCode  = 10404;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10404;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** �f�[�^���R�[�h����
void WDDatas::WDSegment::Delete( void )
{
	FIsam^ tmpParent;

	//-- �f�[�^���R�[�h�`�F�b�N --//
	if( WDRec::getRecord() == nullptr )
	{
		//--�@�f�[�^�N���A --//
		SegmentID = 0;
		SegmentNo = 0;
		if( Name != nullptr )
		{
			delete Name;
			Name = nullptr;
		}
		if( ShortName != nullptr )
		{
			delete Name;
			ShortName = nullptr;
		}

		return;
	}

	//-- ISAM�t�@�C���`�F�b�N --//
	try
	{
		tmpParent = safe_cast<FIsam^>( WDRec::getRecord()->getParentFile() );
		if( tmpParent == nullptr )
		{
			//--�@�f�[�^�N���A --//
			SegmentID = 0;
			SegmentNo = 0;
			if( Name != nullptr )
			{
				delete Name;
				Name = nullptr;
			}
			if( ShortName != nullptr )
			{
				delete Name;
				ShortName = nullptr;
			}

			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAM�t�@�C�����s���ł��B", exp );
		tmpWDDataException->ErrorCode  = 10405;
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
			tmpWDDataException->ErrorCode  = 10405;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10405;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//--�@�f�[�^�N���A --//
	SegmentID = 0;
	SegmentNo = 0;
	if( Name != nullptr )
	{
		delete Name;
		Name = nullptr;
	}
	if( ShortName != nullptr )
	{
		delete Name;
		ShortName = nullptr;
	}

}
//------------------------------------------------------------------------------
//�@��񑀍�
//------------------------------------------------------------------------------
//***** �f�[�^���擾
Int32 WDDatas::WDSegment::Length()
{
	return WDSEGMENT_LENGTH;
}

//***** �f�[�^���R�[�h���擾
Int32 WDDatas::WDSegment::RecLength()
{
	return DataRecord::getHeaderLength() + WDSEGMENT_LENGTH;
}
//------------------------------------------------------------------------------
//�@�A�C�e������
//------------------------------------------------------------------------------
//***** �敪ID�擾
Int32	WDDatas::WDSegment::getSegmentID( void )
{
	return SegmentID;
}

//***** �敪No�擾
Int32	WDDatas::WDSegment::getSegmentNo( void )
{
	return SegmentNo;
}

//***** ���̎擾
String^ WDDatas::WDSegment::getName( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert( 0, Name );
		return inData;
	}else{
		if( Name->Length > 0 )
		{
			return Name->Trim('\0');
		}else{
			return gcnew String( L"" );
		}
	}
}

//***** ���̎擾
String^ WDDatas::WDSegment::getShortName( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert( 0, ShortName );
		return inData;
	}else{
		if( ShortName->Length > 0 )
		{
			return String::Copy( ShortName )->Trim('\0');
		}else{
			return gcnew String(L"");
		}
	}
}

//------------------------------------------------------------------------------
//***** �敪ID�ݒ�
void WDDatas::WDSegment::setSegmentID( Int32 inData )
{
	//-- �����`�F�b�N --//
	if( inData < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�敪ID���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10406;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	SegmentID = inData;
}

//***** �敪No�ݒ�
void WDDatas::WDSegment::setSegmentNo( Int32 inData )
{
	//-- �����`�F�b�N --//
	if( inData < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�敪No���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10407;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	SegmentNo = inData;
}

//***** ���̐ݒ�
void WDDatas::WDSegment::setName( String^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10408;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDSEGMENT_NAMELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂��������܂��B" );
		tmpWDDataException->ErrorCode  = 10408;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		if( Name != nullptr )
		{
			delete Name;
		}
		Name = gcnew String( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10408;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** ���̐ݒ�
void WDDatas::WDSegment::setShortName( String^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10409;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDSEGMENT_SHORTNAMELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂��������܂��B" );
		tmpWDDataException->ErrorCode  = 10409;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		if( ShortName != nullptr )
		{
			delete ShortName;
		}
		
		ShortName = gcnew String( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10409;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}

//------------------------------------------------------------------------------
//�@�f�[�^����
//------------------------------------------------------------------------------
//***** �f�[�^�擾
array<Byte>^ WDDatas::WDSegment::getData( array<Byte>^ inData )
{
	array<Byte>^ rtData;
	Int32		 tmpPos;

	//-- �����`�F�b�N --//
	if( inData != nullptr &&
		inData->Length < WDSEGMENT_LENGTH - WDSEGMENT_RESERVEDLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[��f�[�^�����Z�����܂��B" );
		tmpWDDataException->ErrorCode  = 10410;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		if( inData == nullptr )
		{
			rtData = gcnew array<Byte>( WDSEGMENT_LENGTH );
		}else{
			rtData = inData;
		}

		tmpPos = 0;
	
		FJIFuncs::Int32ToArray( SegmentID, rtData, tmpPos );
		tmpPos += WDSEGMENT_SEGMENTIDLEN;

		FJIFuncs::Int32ToArray( SegmentNo, rtData, tmpPos );
		tmpPos += WDSEGMENT_SEGMENTNOLEN;

		FJIFuncs::StringToArray( Name, rtData, tmpPos, WDSEGMENT_NAMELEN );
		tmpPos += WDSEGMENT_NAMELEN;

		FJIFuncs::StringToArray( ShortName, rtData, tmpPos, WDSEGMENT_SHORTNAMELEN );
		tmpPos += WDSEGMENT_SHORTNAMELEN;

		for(Int32 i = 0; i < WDSEGMENT_RESERVEDLEN; i++ )
		{
			Buffer::SetByte( rtData,tmpPos, 0 );
			tmpPos++;
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10410;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- ����I�� --//
	return rtData;
}

//***** �f�[�^�ݒ�
void WDDatas::WDSegment::setData( array<Byte>^ inData )
{
	Int32		 tmpPos;

	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[���f�[�^�����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10411;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length != WDSEGMENT_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[���f�[�^��������������܂���B" );
		tmpWDDataException->ErrorCode  = 10411;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		tmpPos = 0;

		SegmentID = FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDSEGMENT_SEGMENTIDLEN;

		SegmentNo = FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDSEGMENT_SEGMENTNOLEN;

		if( Name != nullptr ) delete Name;
		Name = FJIFuncs::ArrayToString(inData, tmpPos, WDSEGMENT_NAMELEN );
		tmpPos += WDSEGMENT_NAMELEN;

		if( ShortName != nullptr ) delete ShortName;
		ShortName = FJIFuncs::ArrayToString(inData, tmpPos, WDSEGMENT_SHORTNAMELEN );
		tmpPos += WDSEGMENT_SHORTNAMELEN;

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10411;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}