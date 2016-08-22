//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�f�[�^�N���X�@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDDatas		: �f�[�^���R�[�h��{�N���X
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//�P�ꎫ�T�f�[�^�p��O�N���X
#include "WDDatas.h"			//�P�ꎫ�T�f�[�^�N���X
//#include "FJIsamDef.h"			//ISAM�p��`�t�@�C��

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDData	:DataRecord �g�p���C���N���X
//------------------------------------------------------------------------------
//***** �R���X�g���N�^�P(�V�K�f�[�^)
/*WDDatas::WDRec::WDRec()
{
	DataRec = nullptr;
}

//***** �R���X�g���N�^�Q(�Ǎ��f�[�^)
WDDatas::WDRec::WDRec( DataRecord^ inRec )
{
	DataRec = inRec;
}
*/
//------------------------------------------------------------------------------
//***** �f�X�g���N�^
WDDatas::WDRec::~WDRec()
{
	if( DataRec != nullptr )	delete DataRec;
}

//------------------------------------------------------------------------------
//�@�f�[�^���R�[�h����
//------------------------------------------------------------------------------
//***** �f�[�^���R�[�h�擾
DataRecord^ WDDatas::WDRec::getRecord( void )
{
	return DataRec;
}

//***** �f�[�^���R�[�h�ݒ�
void WDDatas::WDRec::setRecord(  DataRecord^ inRec )
{
	if( inRec != nullptr )
	{
		DataRec = inRec;
	}
}

//***** �f�[�^���R�[�h����
void WDDatas::WDRec::Write( void )
{
	FIsam^ tmpParent;

	//-- �f�[�^���R�[�h�`�F�b�N --//
	if( DataRec == nullptr )
	{
		return;
	}

	//-- ISAM�t�@�C���`�F�b�N --//
	try
	{
		tmpParent = safe_cast<FIsam^>( DataRec->getParentFile() );
		if( tmpParent == nullptr )
		{
			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAM�t�@�C�����s���ł��B", exp );
		tmpWDDataException->ErrorCode  = 10001;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- ���R�[�h����(�����Œǉ��A�X�V���f) --//
	try
	{
		if( DataRec->getRecStat() == DataRecStat_EN::REC_NEW )
		{
			tmpParent->AddRecord( DataRec );
		}else if( DataRec->getRecStat() == DataRecStat_EN::REC_OLD ){
			tmpParent->UpdateRecord( DataRec );
		}else{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"���R�[�h�폜�͂ł��܂���B" );
			tmpWDDataException->ErrorCode  = 10001;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10001;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** �f�[�^���R�[�h�폜
void WDDatas::WDRec::Delete( void )
{
	FIsam^ tmpParent;

	//-- �f�[�^���R�[�h�`�F�b�N --//
	if( DataRec == nullptr )
	{
		return;
	}

	//-- ISAM�t�@�C���`�F�b�N --//
	try
	{
		tmpParent = safe_cast<FIsam^>( DataRec->getParentFile() );
		if( tmpParent == nullptr )
		{
			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAM�t�@�C�����s���ł��B", exp );
		tmpWDDataException->ErrorCode  = 10002;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- ���R�[�h�폜 --//
	try
	{
		if( DataRec->getRecStat() == DataRecStat_EN::REC_NEW )
		{
			;
		}if( DataRec->getRecStat() == DataRecStat_EN::REC_OLD )
		{
			tmpParent->DeleteRecord( DataRec );
			delete DataRec;
			DataRec = nullptr;
		}else{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"���̃f�[�^���R�[�h�͍폜�ł��܂���B" );
			tmpWDDataException->ErrorCode  = 10002;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10002;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//�@��񑀍�
//------------------------------------------------------------------------------
//***** �f�[�^�����擾
Int32 WDDatas::WDRec::Length()
{
	return 0;
}

//***** �f�[�^���R�[�h���擾
Int32 WDDatas::WDRec::RecLength()
{
	if( DataRec == nullptr )
	{
		return 0;
	}else{
		return DataRec->getRecLength();
	}
}