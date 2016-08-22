//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�A�v���P�[�V�����@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	Windows Form�̃A�v���P�[�V����
//------------------------------------------------------------------------------
// WordDicSchListAct.cpp : �������X�g�̃A�N�V�����B
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Form1.h"				//�P�ꎫ�T���C���t�H�[��
#include "WDGroupTreeNode.h"	//���ރf�[�^�pTreeNode
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
#include "WordDicException.h"	//�P�ꎫ�T�p��O�N���X

using namespace FJIsam;
using namespace WDDatas;

//------------------------------------------------------------------------------
// �����P�ꃊ�X�g�{�b�N�X����
//------------------------------------------------------------------------------
//***** �N���A�{�^�� �N���b�N
System::Void WordDic::Form1::buttonWordListClear_Click(System::Object^  sender, System::EventArgs^  e)
{
	try
	{
		schWordLstClear();

	}catch( Exception^ exp ){
		ExceptionWrite( exp );
	}

}

//***** �����P�ꃊ�X�g�N���A
void WordDic::Form1::schWordLstClear( void )
{
	try{
		//-- �������� --//
		listBoxWordList->BeginUpdate();			//���X�g�{�b�N�X�`���~

		//-- XML�f�[�^�Ǎ��ς݃f�[�^�ȊO���폜���� --//
		for( Int32 i = 0; i < listBoxWordList->Items->Count; i++ )
		{
			WDWordGrp^ tmpWordGrp = safe_cast<WDWordGrp^>(listBoxWordList->Items[i] );
			
			for each( WDWordGrp^ schWordGrp in ReadedWordList )
			{
				if( schWordGrp != tmpWordGrp )
				{
					delete tmpWordGrp;
					break;
				}
			}

		}
		//-- �������X�g�̃N���A --//
		listBoxWordList->Items->Clear();

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�����P�ꃊ�X�g�N���A���ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31402;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;

	}finally{
		listBoxWordList->EndUpdate();			//���X�g�{�b�N�X�`��J�n
	}
}
