//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�A�v���P�[�V�����@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	Windows Form�̃A�v���P�[�V����
//------------------------------------------------------------------------------
// WordDicEnd.cpp : �I���������L�q�����t�@�C���ł��B
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
// �f�X�g���N�^
//------------------------------------------------------------------------------
WordDic::Form1::~Form1()
{
	try
	{
		DeleteXmlFiles();
		DeleteDatas();

	}catch( Exception^ exp ){
		ExceptionWrite( exp );
	}

	if (components)
	{
		delete components;
	}
}

//------------------------------------------------------------------------------
// �I������
//------------------------------------------------------------------------------
//***** XML�f�[�^�폜����
void WordDic::Form1::DeleteXmlFiles( void )
{
	DirectoryInfo^				schDir;
	Collections::IEnumerator^	schEnum;

	//-- �P��\���f�[�^�i�[�t�H���_���Ȃ���Ή������Ȃ� --//
	if( DispXMLForder == nullptr ||
		DispXMLForder->Length == 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��\���f�[�^�i�[�t�H���_����`����Ă��܂���B", nullptr );
		tmpWordDicException->ErrorCode = 31701;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- �t�@�C�����폜 --//
	try
	{
		schDir = gcnew DirectoryInfo( DispXMLForder );

		schEnum =  schDir->GetFiles()->GetEnumerator();

		//-- �S�f�[�^���폜����܂ŌJ��Ԃ�
		while( schEnum->MoveNext() )
		{
			FileInfo^ tmpFile = safe_cast<FileInfo^>(schEnum->Current);
			
			tmpFile->Delete();
		}
		schDir->Delete(true);
	
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��\���t�@�C���폜���ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31701;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;

	}finally{
		if( schDir != nullptr ) delete schDir;
	}
}

//***** �f�[�^�폜
void WordDic::Form1::DeleteDatas( void )
{
	if( ReadedWordList != nullptr ) delete ReadedWordList;
}
