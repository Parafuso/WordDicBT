//WordDicException.h
//------------------------------------------------------------------------------
//	ISAM�A�N�Z�X���C�u�����@�P�ꎫ�T�p��O�N���X �w�b�_
//	Version 1.0		Create Date 2006/05/08 .net 2.0 �ō쐬(�V�K)
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WordDicException		:��O�N���X
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
//	class	:WordDicException	:��O�N���X
//------------------------------------------------------------------------------
namespace WordDic
{
	public ref class WordDicException :public System::Exception
	{
	public :
		//�R���X�g���N�^
		WordDicException( );
		WordDicException(String^ msg);
		WordDicException(String^ msg, Exception^ inner );

		//�����o
		int	ErrorCode;
		int	ErrorCode2;
	};
}