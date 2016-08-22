//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�p�N���X�@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDGroupTreeNode : ���ރf�[�^��TreeView�pTreeNode
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDGroupTreeNode.h"	//���ރf�[�^�pTreeNode
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`

//------------------------------------------------------------------------------
//�@�R���X�g���N�^
//------------------------------------------------------------------------------
WordDic::WDGroupTreeNode::WDGroupTreeNode( void )
: TreeNode( )
{
	GroupGt = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
	GroupLt = gcnew array<Byte>(WDGROUP_GROUPLTLEN);
}

WordDic::WDGroupTreeNode::WDGroupTreeNode( String^ Text )
: TreeNode( Text )
{
	GroupGt = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
	GroupLt = gcnew array<Byte>(WDGROUP_GROUPLTLEN);
	if( Text != nullptr )
	{
		Name = String::Copy( Text );
	}
}

WordDic::WDGroupTreeNode::WDGroupTreeNode( WDGroup^ inGroup )
: TreeNode()
{
	if( inGroup == nullptr )
	{
		return;
	}else{
		GroupGt = inGroup->getGroupGt( nullptr );
		GroupLt = inGroup->getGroupLt( nullptr );
		String^ tmpStr;
		tmpStr = inGroup->getName( nullptr );
		if( tmpStr != nullptr )
		{
			Name = String::Copy( tmpStr );
			TreeNode::Text = Name;
		}
		tmpStr = inGroup->getShortName( nullptr );
		if( tmpStr != nullptr )
		{
			ShortName = String::Copy( tmpStr );
		}
	}
}
//------------------------------------------------------------------------------
//�@�A�C�e������
//------------------------------------------------------------------------------
//***** ���ޑ�擾
array<Byte>^ WordDic::WDGroupTreeNode::getGroupGt( array<Byte>^ inData )
{
	if( inData != nullptr )
	{
		if( inData->Length < WDGROUP_GROUPGTLEN )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�R�s�[��f�[�^�����Z�����܂��B" );
			tmpWDDataException->ErrorCode  = 20001;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}

		try
		{
			Buffer::BlockCopy( GroupGt, 0, inData, 0, WDGROUP_GROUPGTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
			tmpWDDataException->ErrorCode  = 20001;
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
			tmpWDDataException->ErrorCode  = 20001;
			tmpWDDataException->ErrorCode2 = 3;
			throw tmpWDDataException;
		}

		return rtData;
	}
}

//***** ���ޏ��擾
array<Byte>^ WordDic::WDGroupTreeNode::getGroupLt( array<Byte>^ inData )
{
	if( inData != nullptr )
	{
		if( inData->Length < WDGROUP_GROUPLTLEN )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�R�s�[��f�[�^�����Z�����܂��B" );
			tmpWDDataException->ErrorCode  = 20002;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}

		try
		{
			Buffer::BlockCopy( GroupLt, 0, inData, 0, WDGROUP_GROUPLTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
			tmpWDDataException->ErrorCode  = 20002;
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
			tmpWDDataException->ErrorCode  = 20002;
			tmpWDDataException->ErrorCode2 = 3;
			throw tmpWDDataException;
		}

		return rtData;
	}
}

//***** ���̎擾
String^ WordDic::WDGroupTreeNode::getName( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert(0, Name );
		return inData;
	}else{
		return String::Copy( Name );
	}
}

//***** ���̎擾
String^ WordDic::WDGroupTreeNode::getShortName( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert(0, ShortName );
		return inData;
	}else{
		return String::Copy( ShortName );
	}
}

//------------------------------------------------------------------------------
//***** ���ޑ�ݒ�
void WordDic::WDGroupTreeNode::setGroupGt( array<Byte>^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޑ傪���ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 20002;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length < WDGROUP_GROUPGTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޑ傪�Z�����܂��B" );
		tmpWDDataException->ErrorCode  = 20002;
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
		tmpWDDataException->ErrorCode  = 20002;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}		

//***** ���ޏ��ݒ�
void WordDic::WDGroupTreeNode::setGroupLt( array<Byte>^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޏ������ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 20005;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length < WDGROUP_GROUPLTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���ޏ����Z�����܂��B" );
		tmpWDDataException->ErrorCode  = 20005;
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
		tmpWDDataException->ErrorCode  = 20005;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}							

//***** ���̐ݒ�
void WordDic::WDGroupTreeNode::setName( String^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 20005;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDGROUP_NAMELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂��������܂��B" );
		tmpWDDataException->ErrorCode  = 20005;
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
		this->Text = inData;

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 20005;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** ���̐ݒ�
void WordDic::WDGroupTreeNode::setShortName( String^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 20006;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDGROUP_SHORTNAMELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���̂��������܂��B" );
		tmpWDDataException->ErrorCode  = 20006;
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
		tmpWDDataException->ErrorCode  = 20006;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}
