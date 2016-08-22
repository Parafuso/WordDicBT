//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�f�[�^�N���X�@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDGroup		: ���ރN���X
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//�P�ꎫ�T�f�[�^�p��O�N���X
#include "WDDatas.h"			//�P�ꎫ�T�f�[�^�N���X
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
//#include "FJIsamDef.h"			//ISAM�p��`�t�@�C��

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDGroup	: ���ރN���X
//------------------------------------------------------------------------------
//***** �R���X�g���N�^�P(�V�K�f�[�^)
WDDatas::WDGroup::WDGroup()
{
	//-- �ϐ���` --//
	GroupGt = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
	GroupLt = gcnew array<Byte>(WDGROUP_GROUPLTLEN);

}

//***** �R���X�g���N�^�Q(�Ǎ��f�[�^)
WDDatas::WDGroup::WDGroup( DataRecord^ inRec )
{

	if(inRec == nullptr )
	{
		//-- �ϐ���` --//
		GroupGt = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
		GroupLt = gcnew array<Byte>(WDGROUP_GROUPLTLEN);
		return;
	}

	//-- �����`�F�b�N --//
	if( inRec->getDataLength() != WDGROUP_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�����ރf�[�^�ł͂���܂���B" );
		tmpWDDataException->ErrorCode  = 10301;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	
	//-- �ϐ���` --//
	GroupGt = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
	GroupLt = gcnew array<Byte>(WDGROUP_GROUPLTLEN);

	//-- �f�[�^�ݒ� --//
	try
	{
		setRecord( inRec );
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�ݒ�ŃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 10301;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//***** �f�X�g���N�^
WDDatas::WDGroup::~WDGroup()
{
	delete GroupGt;
	delete GroupLt;
	if( Name != nullptr ) delete Name;
	if( ShortName != nullptr ) delete ShortName;
}

//------------------------------------------------------------------------------
//�@�f�[�^���R�[�h����
//------------------------------------------------------------------------------
//***** �f�[�^���R�[�h�擾
DataRecord^ WDDatas::WDGroup::getRecord( void )
{
	DataRecord^ tmpRec;
	array<Byte>^ tmpDat;

	if( WDRec::getRecord() == nullptr )
	{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = gcnew DataRecord();
			tmpRec->setData( tmpDat, WDGROUP_LENGTH );
			WDRec::setRecord( tmpRec );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^���R�[�h�擾�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10302;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}
	}else{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = WDRec::getRecord();
			tmpRec->setData( tmpDat, WDGROUP_LENGTH );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^���R�[�h�擾�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10302;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}

	delete tmpDat;

	//-- ����I�� --//
	return tmpRec;
}

//***** �f�[�^���R�[�h�ݒ�
void WDDatas::WDGroup::setRecord( DataRecord^ inRec )
{
	if( inRec != nullptr )
	{
		try
		{
			array<Byte>^ tmpDat;
			tmpDat = inRec->getData( nullptr );
			setData( tmpDat );
			WDRec::setRecord( inRec );
			delete tmpDat;
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^���R�[�h�ݒ�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10303;
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
			tmpWDDataException->ErrorCode  = 10303;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}
}

//***** �f�[�^���R�[�h����
void WDDatas::WDGroup::Write( void )
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
		tmpWDDataException->ErrorCode  = 10304;
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
			tmpWDDataException->ErrorCode  = 10304;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10304;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** �f�[�^���R�[�h����
void WDDatas::WDGroup::Delete( void )
{
	FIsam^ tmpParent;

	//-- �f�[�^���R�[�h�`�F�b�N --//
	if( WDRec::getRecord() == nullptr )
	{
		//--�@�f�[�^�N���A --//
		GroupGt[0] = 0;
		GroupGt[1] = 0;
		GroupLt[0] = 0;
		GroupLt[1] = 0;
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
			GroupGt[0] = 0;
			GroupGt[1] = 0;
			GroupLt[0] = 0;
			GroupLt[1] = 0;
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
		tmpWDDataException->ErrorCode  = 10305;
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
			tmpWDDataException->ErrorCode  = 10305;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10305;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//--�@�f�[�^�N���A --//
	GroupGt[0] = 0;
	GroupGt[1] = 0;
	GroupLt[0] = 0;
	GroupLt[1] = 0;
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
Int32 WDDatas::WDGroup::Length()
{
	return WDGROUP_LENGTH;
}

//***** �f�[�^���R�[�h���擾
Int32 WDDatas::WDGroup::RecLength()
{
	return DataRecord::getHeaderLength() + WDGROUP_LENGTH;
}
//------------------------------------------------------------------------------
//�@�A�C�e������
//------------------------------------------------------------------------------
//***** ���ޑ�擾
array<Byte>^ WDDatas::WDGroup::getGroupGt( array<Byte>^ inData )
{
	if( inData != nullptr )
	{
		if( inData->Length < WDGROUP_GROUPGTLEN )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�R�s�[��f�[�^�����Z�����܂��B" );
			tmpWDDataException->ErrorCode  = 10306;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}

		try
		{
			Buffer::BlockCopy( GroupGt, 0, inData, 0, WDGROUP_GROUPGTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
			tmpWDDataException->ErrorCode  = 10306;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
		return inData;

	}else{

		array<Byte>^ rtData = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
		try
		{
			Buffer::BlockCopy( GroupGt, 0, rtData, 0, WDGROUP_GROUPGTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
			tmpWDDataException->ErrorCode  = 10306;
			tmpWDDataException->ErrorCode2 = 3;
			throw tmpWDDataException;
		}

		return rtData;
	}
}

//***** ���ޏ��擾
array<Byte>^ WDDatas::WDGroup::getGroupLt( array<Byte>^ inData )
{
	if( inData != nullptr )
	{
		if( inData->Length < WDGROUP_GROUPLTLEN )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�R�s�[��f�[�^�����Z�����܂��B" );
			tmpWDDataException->ErrorCode  = 10307;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}

		try
		{
			Buffer::BlockCopy( GroupLt, 0, inData, 0, WDGROUP_GROUPLTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
			tmpWDDataException->ErrorCode  = 10307;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
		return inData;

	}else{

		array<Byte>^ rtData = gcnew array<Byte>(WDGROUP_GROUPLTLEN);
		try
		{
			Buffer::BlockCopy( GroupLt, 0, rtData, 0, WDGROUP_GROUPLTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
			tmpWDDataException->ErrorCode  = 10307;
			tmpWDDataException->ErrorCode2 = 3;
			throw tmpWDDataException;
		}

		return rtData;
	}
}

//***** ���̎擾
String^ WDDatas::WDGroup::getName( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert(0, Name );
		return inData;
	}else{
		if( Name->Length > 0 )
		{
			return Name->Trim('\0');
		}else{
			return gcnew String(L"");
		}
	}
}

//***** ���̎擾
String^ WDDatas::WDGroup::getShortName( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert(0, ShortName );
		return inData;
	}else{
		if( ShortName->Length > 0 )
		{
			return ShortName->Trim('\0');
		}else{
			return gcnew String( L"" );
		}
	}
}

//------------------------------------------------------------------------------
//***** ���ޑ�ݒ�
void WDDatas::WDGroup::setGroupGt( array<Byte>^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޑ傪���ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10308;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length < WDGROUP_GROUPGTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޑ傪�Z�����܂��B" );
		tmpWDDataException->ErrorCode  = 10308;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		Buffer::BlockCopy( inData, 0, GroupGt, 0, WDGROUP_GROUPGTLEN );
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޑ�̐ݒ�ɂ��p�C���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10308;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}		

//***** ���ޏ��ݒ�
void WDDatas::WDGroup::setGroupLt( array<Byte>^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޏ������ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10309;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length < WDGROUP_GROUPLTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޏ����Z�����܂��B" );
		tmpWDDataException->ErrorCode  = 10309;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		Buffer::BlockCopy( inData, 0, GroupLt, 0, WDGROUP_GROUPLTLEN );
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޏ��̐ݒ�ɂ��p�C���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10309;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}							

//***** ���̐ݒ�
void WDDatas::WDGroup::setName( String^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10310;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDGROUP_NAMELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂��������܂��B" );
		tmpWDDataException->ErrorCode  = 10310;
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
		Name = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10310;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** ���̐ݒ�
void WDDatas::WDGroup::setShortName( String^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10311;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDGROUP_SHORTNAMELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂��������܂��B" );
		tmpWDDataException->ErrorCode  = 10311;
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
		ShortName = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10311;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}

//------------------------------------------------------------------------------
//�@�f�[�^����
//------------------------------------------------------------------------------
//***** �f�[�^�擾
array<Byte>^ WDDatas::WDGroup::getData( array<Byte>^ inData )
{
	array<Byte>^ rtData;
	Int32		 tmpPos;
	
	//-- �����`�F�b�N --//
	if( inData != nullptr &&
		inData->Length < WDGROUP_LENGTH - WDGROUP_RESERVEDLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[��f�[�^�����Z�����܂��B" );
		tmpWDDataException->ErrorCode  = 10312;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		if( inData == nullptr )
		{
			rtData = gcnew array<Byte>( WDGROUP_LENGTH );
		}else{
			rtData = inData;
		}

		tmpPos = 0;
	
		//���ޑ�
		Buffer::BlockCopy( GroupGt, 0, rtData, tmpPos, WDGROUP_GROUPGTLEN );
		tmpPos += WDGROUP_GROUPGTLEN;

		//���ޏ�
		Buffer::BlockCopy( GroupLt, 0, rtData, tmpPos, WDGROUP_GROUPLTLEN );
		tmpPos += WDGROUP_GROUPLTLEN;

		//����
		FJIFuncs::StringToArray( Name, rtData, tmpPos, WDGROUP_NAMELEN );
		tmpPos += WDGROUP_NAMELEN;

		//����
		FJIFuncs::StringToArray( ShortName, rtData, tmpPos, WDGROUP_SHORTNAMELEN );
		tmpPos += WDGROUP_SHORTNAMELEN;

		//Reserve
		for(Int32 i = 0; i < WDGROUP_RESERVEDLEN; i++ )
		{
			Buffer::SetByte( rtData,tmpPos, 0 );
			tmpPos++;
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10312;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- ����I�� --//
	return rtData;
}

//***** �f�[�^�ݒ�
void WDDatas::WDGroup::setData( array<Byte>^ inData )
{
	Int32		 tmpPos;

	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[���f�[�^�����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10313;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length != WDGROUP_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[���f�[�^��������������܂���B" );
		tmpWDDataException->ErrorCode  = 10313;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		tmpPos = 0;

		Buffer::BlockCopy( inData, tmpPos, GroupGt, 0, WDGROUP_GROUPGTLEN );
		tmpPos += WDGROUP_GROUPGTLEN;

		Buffer::BlockCopy(  inData, tmpPos, GroupLt, 0, WDGROUP_GROUPLTLEN );
		tmpPos += WDGROUP_GROUPLTLEN;

		if( Name != nullptr ) delete Name;
		Name =  FJIFuncs::ArrayToString(inData, tmpPos, WDGROUP_NAMELEN );
		tmpPos += WDGROUP_NAMELEN;

		if( ShortName != nullptr ) delete ShortName;
		ShortName = FJIFuncs::ArrayToString(inData, tmpPos, WDGROUP_SHORTNAMELEN );
		tmpPos += WDGROUP_SHORTNAMELEN;

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10313;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}