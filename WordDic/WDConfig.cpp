//------------------------------------------------------------------------------
//	���Ƃ΂̎��T�@���Ƃ΂̎��T�r���[�A�A�v���P�[�V�����@�w�b�_
//	Version 1.0		create date 2008/03/15
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDConfig : �ݒ���
//------------------------------------------------------------------------------
#include "StdAfx.h"
#include "WDConfig.h"			//�ݒ���
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
#include "WDWordGrp.h"			//�P��f�[�^�p����

using namespace WDDatas;

//------------------------------------------------------------------------------
//�@�_�C�A���O�����\��
//------------------------------------------------------------------------------
//***** �_�C�A���O�����\��
System::Void WordDic::WDConfig::WDConfig_Shown(System::Object^  sender, System::EventArgs^  e)
{
	comboBoxScreenLang->Text = comboBoxScreenLang->Items[0]->ToString();	//����̑I��
	comboBoxWebSearch->Text = comboBoxWebSearch->Items[0]->ToString();		//Web�T�[�`�̑I��
}


//------------------------------------------------------------------------------
//�@�{�^���N���b�N
//------------------------------------------------------------------------------
//***** OK�{�^���N���b�N
System::Void WordDic::WDConfig::buttonOK_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Close();
}
