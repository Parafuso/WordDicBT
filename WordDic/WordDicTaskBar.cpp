//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�A�v���P�[�V�����@�\�[�X
//	Version 1.0			Create date 2006/05/08
//	Version 1.0.3.0		Change date 2010/11/16

//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	Windows Form�̃A�v���P�[�V����
//------------------------------------------------------------------------------
// WordDicTaskBar.cpp : �^�X�N�o�[�ɒǉ������{�^���̏������L�q�����t�@�C���ł��B
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Form1.h"				//�P�ꎫ�T���C���t�H�[��
#include "WordDicDef.h"			//�P�ꎫ�T�p��`�t�@�C��
#include "WordDicCfg.h"			//�P�ꎫ�T�R���t�B�O
#include "WDGroupTreeNode.h"	//���ރf�[�^�pTreeNode
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
#include "FJIsamDef.h"			//ISAM�p��`�t�@�C��
#include "WordDicException.h"	//�P�ꎫ�T�p��O�N���X

using namespace FJIsam;
using namespace WDDatas;

//------------------------------------------------------------------------------
// �^�X�N�o�[�F����{�^���P����̌���
//------------------------------------------------------------------------------
System::Void WordDic::Form1::ThumbButtonSchLangA_Click(System::Object^  sender, 
							Microsoft::WindowsAPICodePack::Taskbar::ThumbnailButtonClickedEventArgs^  e)
{
	String^	ClipWord;												//�N���b�v�{�[�h�̒P��
	array<String^>^	SchWord;										//��������P��i���s�R�[�h���𐮌`�j
	
	array<String^>^ SplitChar = gcnew array<String^>{ L"\n" };		//���o���镶���̋�؂�

	//-- �N���b�v�{�[�h�̕������擾 --//
	ClipWord = System::Windows::Forms::Clipboard::GetText();

	//�N���b�v�{�[�h�̕�������Ȃ牽�����Ȃ��B
	if( String::IsNullOrEmpty( ClipWord ) == true )
	{
		return;
	}
	
	//-- �N���b�v�{�[�h�̕����𐮌`���� --//
	// ���s������ꍇ��1�s�ڂ݂̂𒊏o //
	SchWord = ClipWord->Split( SplitChar, System::StringSplitOptions::RemoveEmptyEntries );
	


	//-- �N���b�v�{�[�h�̒P��Ō���P�̌������s�� --//
	textBoxSchWord->Text = SchWord[0]->Trim();						//�����P��ݒ�i�O��̋󔒂������j
	radioButtonWordA->Checked = true;								//�����Ώۂ�����`�ɐݒ�
	buttonSchWord->PerformClick();									//�������s�i�����{�^���N���b�N�j

	//-- ��ʂ�\������ --//
	tabCtrlSearch->SelectTab(0);									//�P�ꌟ���̃^�u��\������B
	this->Activate();												//���Ƃ΂̎��T���A�N�e�B�u�ɂ���B


}

//------------------------------------------------------------------------------
// �^�X�N�o�[�F����{�^���Q����̌���
//------------------------------------------------------------------------------
System::Void WordDic::Form1::ThumbButtonSchLangB_Click(System::Object^  sender, 
							Microsoft::WindowsAPICodePack::Taskbar::ThumbnailButtonClickedEventArgs^  e)
{
	String^	ClipWord;												//�N���b�v�{�[�h�̒P��
	array<String^>^	SchWord;										//��������P��i���s�R�[�h���𐮌`�j
	
	array<String^>^ SplitChar = gcnew array<String^>{ L"\n" };		//���o���镶���̋�؂�

	//-- �N���b�v�{�[�h�̕������擾 --//
	ClipWord = System::Windows::Forms::Clipboard::GetText();

	//�N���b�v�{�[�h�̕�������Ȃ牽�����Ȃ��B
	if( String::IsNullOrEmpty( ClipWord ) == true )
	{
		return;
	}
	
	//-- �N���b�v�{�[�h�̕����𐮌`���� --//
	// ���s������ꍇ��1�s�ڂ݂̂𒊏o //
	SchWord = ClipWord->Split( SplitChar, System::StringSplitOptions::RemoveEmptyEntries );
	


	//-- �N���b�v�{�[�h�̒P��Ō���P�̌������s�� --//
	textBoxSchWord->Text = SchWord[0]->Trim();						//�����P��ݒ�i�O��̋󔒂������j
	radioButtonWordB->Checked = true;								//�����Ώۂ�����a�ɐݒ�
	buttonSchWord->PerformClick();									//�������s�i�����{�^���N���b�N�j

	//-- ��ʂ�\������ --//
	tabCtrlSearch->SelectTab(0);									//�P�ꌟ���̃^�u��\������B
	this->Activate();												//���Ƃ΂̎��T���A�N�e�B�u�ɂ���B

}
