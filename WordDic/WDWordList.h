//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�A�v���P�[�V�����@�w�b�_
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDWordList : �P�ꌟ�����ʕ\���p���X�g�{�b�N�X
//------------------------------------------------------------------------------
#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace WordDic {

	/// <summary>
	/// WDWordList �̊T�v
	/// </summary>
	public ref class WDWordList : public System::Windows::Forms::ListBox
	{
	public:
		//-- �萔 --//
		static Int32 schWord = 0;										//�P�ꌟ��
		static Int32 schGrp = 1;										//���ތ���

		//-- �R���X�g���N�^ --//
		WDWordList(void)
			: ListBox(), srtType(schWord), srtWord1(0), srtWord2(0)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^ �R�[�h��ǉ����܂�
			//
		}
		//-- �\�[�g���@�ݒ�A�m�F --//
		void setSortOrder( Int32 inSrtType,								//�\�[�g���ݒ�
							Int32 inSrtWord1, Int32 inSrtWord2 );

		Int32 getSortType( void );										//�\�[�g�^�C�v
		Int32 getSortWord1( void );										//�\�[�g�P��P
		Int32 getSortWord2( void );										//�\�[�g�P��Q

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~WDWordList()
		{
			if (components)
			{
				delete components;
			}
		}

		//-- �\�[�g --//
		virtual void Sort() override;			

	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container ^components;

		//-- �\�[�g���[���p --//
		Int32	srtType;												//�\�[�g�^�C�v
		Int32	srtWord1;												//�\�[�g�P��P
		Int32	srtWord2;												//�\�[�g�P��Q

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			//this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion
	};
}
