//WDDatasException.h
//------------------------------------------------------------------------------
//	ISAM�A�N�Z�X���C�u�����@�P�ꎫ�T�f�[�^�p��O�N���X �w�b�_
//	Version 1.0		Create Date 2006/05/08 .net 2.0 �ō쐬(�V�K)
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDDatasException		:��O�N���X
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
//	class	:WDDatasException	:��O�N���X
//------------------------------------------------------------------------------
namespace WDDatas
{
	public ref class WDDatasException :public System::Exception
	{
	public :
		//�R���X�g���N�^
		WDDatasException( );
		WDDatasException(String^ msg);
		WDDatasException(String^ msg, Exception^ inner );

		//�����o
		int	ErrorCode;
		int	ErrorCode2;
	};
}