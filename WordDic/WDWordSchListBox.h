//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�A�v���P�[�V�����@�w�b�_
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDWordListBox : �P�ꌟ�����ʕ\���p���X�g�{�b�N�X
//------------------------------------------------------------------------------
#pragma once
#include "WDWordGrp.h"			//�P��f�[�^�p����

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace WDDatas;



namespace WordDic {

	/// <summary>
	/// WDWordSchListBox �̊T�v
	/// </summary>
	public ref class WDWordSchListBox : public System::Windows::Forms::ListBox
	{
	public:
		WDWordSchListBox(void)
			: ListBox(), srtType(0), srtWord1(0), srtWord2(0)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^ �R�[�h��ǉ����܂�
			//
		}


	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~WDWordSchListBox()
		{
			if (components)
			{
				delete components;
			}
		}

		//�\�[�g
		{

		}


	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container ^components;


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
