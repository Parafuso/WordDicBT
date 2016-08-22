//------------------------------------------------------------------------------
//	���Ƃ΂̎��T�@���Ƃ΂̎��T�r���[�A�A�v���P�[�V�����@�w�b�_
//	Version 1.0.0.0		create date 2006/05/08
//	Version 1.0.1.0		create date 2009/09/13
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	Windows Form�̃A�v���P�[�V����
//------------------------------------------------------------------------------
// WordDicMenu.cpp : ���j���[����
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Form1.h"				//�P�ꎫ�T���C���t�H�[��
#include "WordDicDef.h"			//�P�ꎫ�T�p��`�t�@�C��
#include "WDGroupTreeNode.h"	//���ރf�[�^�pTreeNode
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
#include "FJIsamDef.h"			//ISAM�p��`�t�@�C��
#include "WordDicException.h"	//�P�ꎫ�T�p��O�N���X

using namespace FJIsam;
using namespace WDDatas;

//------------------------------------------------------------------------------
//�@�{�^���N���b�N
//------------------------------------------------------------------------------
//***** �I���{�^���N���b�N
System::Void WordDic::Form1::�I��toolStripButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	//-- �A�v���P�[�V�������I������
	this->Close();
}

//***** �R�s�[�{�^���N���b�N
System::Void WordDic::Form1::�R�s�[CToolStripButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	BookWordCopy();
}

//***** �ݒ�{�^���N���b�N
System::Void WordDic::Form1::toolStripButtonConfig_Click(System::Object^  sender, System::EventArgs^  e)
{
	dlgWDConfig->ShowDialog();
}

//***** �w���v�{�^���N���b�N
System::Void WordDic::Form1::�w���vLToolStripButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	Drawing::Point ^dispPoint;
	//Point ^formPoint;
	Drawing::Size  ^clientSZ;
	Drawing::Size  ^formSZ;

	//���j���[�ʒu��ݒ�
	clientSZ = this->ClientSize;
	formSZ = this->Size;
	//formPoint = this->Location;
	dispPoint = Cursor->Position;

	dispPoint->X -= this->Left + (formSZ->Width - clientSZ->Width);
	dispPoint->Y -= this->Top + (formSZ->Height - clientSZ->Height);

	//-- �w���v���j���[��\��
	contextMenuHelp->Show( this, *dispPoint );
}

//------------------------------------------------------------------------------
//�@�w���v���j���[
//------------------------------------------------------------------------------
//***** �w���v���j���[�F�u�}�j���A���v
System::Void WordDic::Form1::ToolStripMenuItemHelpMan_Click(System::Object^  sender, System::EventArgs^  e)
{
	String ^strFileName;

	strFileName = String::Concat(
					Path::GetDirectoryName( Application::ExecutablePath ) ,
					L"\\���Ƃ΂̎��T �}�j���A��.pdf" );

	//-- �}�j���A���N���iPDF�j
	System::Diagnostics::Process::Start( strFileName );


}
//***** �w���v���j���[�F�u�o�[�W�������v
System::Void WordDic::Form1::ToolStripMenuItemHelpVer_Click(System::Object^  sender, System::EventArgs^  e)
{
	//-- �o�[�W�������_�C�A���O�\��
	dlgWDVerDialog->ShowDialog();
}

