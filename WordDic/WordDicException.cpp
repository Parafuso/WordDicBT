//WordDicException.h
//------------------------------------------------------------------------------
//	ISAM�A�N�Z�X���C�u�����@�P�ꎫ�T�p��O�N���X �N���X
//	Version 1.0		Create Date 2006/05/08 .net 2.0 �ō쐬(�V�K)
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WordDicException		:��O�N���X
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WordDicException.h"

//------------------------------------------------------------------------------
//	class	:WordDicException	:��O�N���X
//------------------------------------------------------------------------------
//***** �R���X�g���N�^
WordDic::WordDicException::WordDicException()
			: System::Exception(), ErrorCode(0), ErrorCode2(0)
{
};

//***** �R���X�g���N�^
WordDic::WordDicException::WordDicException(String^ msg)
			: System::Exception( msg ), ErrorCode(0), ErrorCode2(0)
{
};

//***** �R���X�g���N�^
WordDic::WordDicException::WordDicException(String^ msg, Exception^ inner )
			: System::Exception( msg, inner  ), ErrorCode(0), ErrorCode2(0)
{
};
