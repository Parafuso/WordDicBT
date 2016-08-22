//------------------------------------------------------------------------------
//	���Ƃ΂̎��T�@���Ƃ΂̎��T�r���[�A�A�v���P�[�V�����@�w�b�_
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDWordSchListComparer : �P�ꌟ�����ʕ\���p���X�g�{�b�N�X�\�[�g
//------------------------------------------------------------------------------
#pragma once

using namespace WDDatas;

namespace WordDic
{
	public ref class WDWordSchListComparer: public System::Collections::IComparer					//�P�ꃊ�X�g��r
	{
	public:
		virtual Int32 Compare(Object^ x, Object^ y);

		//-- �萔 --//
		static Int32 schWord = 0;										//�P�ꌟ��
		static Int32 schGrp = 1;										//���ތ���

		//-- �\�[�g���@�ݒ�A�m�F --//
		void setSortOrder( Int32 inSrtType,								//�\�[�g���ݒ�
							Int32 inSrtWord1, Int32 inSrtWord2 );

		Int32 getSortType( void );										//�\�[�g�^�C�v
		Int32 getSortWord1( void );										//�\�[�g�P��P
		Int32 getSortWord2( void );										//�\�[�g�P��Q

	private:
		//-- �\�[�g���[���p --//
		Int32	srtType;												//�\�[�g�^�C�v
		Int32	srtWord1;												//�\�[�g�P��P
		Int32	srtWord2;												//�\�[�g�P��Q

	};
}