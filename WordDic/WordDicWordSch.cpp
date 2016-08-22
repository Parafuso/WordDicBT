//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�A�v���P�[�V�����@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	Windows Form�̃A�v���P�[�V����
//------------------------------------------------------------------------------
// WordDicWordSch.cpp : �P�ꌟ��
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
// �C�x���g����
//------------------------------------------------------------------------------
//***** �����{�^���N���b�N�i�P�ꌟ���j
System::Void WordDic::Form1::buttonSchWord_Click(System::Object^  sender, System::EventArgs^  e)
{
	//�P�ꌟ��
	WordSearch();
}

//***** �����P��TextBox����
System::Void WordDic::Form1::textBoxSchWord_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
	//Enter�����͂����ƁA�P�ꌟ���ƍs��
	if( e->KeyChar == (Char)Keys::Enter )
	{
		WordSearch();
		e->Handled = true;
	}
}

//------------------------------------------------------------------------------
// ��������
//------------------------------------------------------------------------------
//***** �P�ꌟ��
void WordDic::Form1::WordSearch( void )
{

	//-- ��������Ȃ�Ȃɂ����Ȃ� --//
	if( textBoxSchWord->Text->Length == 0 )
	{
		return;
	}

	//-- ������ --//
	if(SchWord != nullptr )
	{	
		delete SchWord;
		SchWord = nullptr;
	}
	SchWord = textBoxSchWord->Text;				//�����P��
	SchMethod = 1;								//�������@(�P��)
	if( radioButtonWordA->Checked == true )		//��������(A or B)
	{
		SchLanguage = 1;
	}else{
		SchLanguage = 2;
	}
	SchState = 1;								//�������(�P��̂��� 1);


	//-- �P�ꌟ�� --//
	try
	{
		//�P�ꃊ�X�g�N���A
		try
		{
			schWordLstClear();
		}catch( Exception^ exp ){
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P�ꌟ���̑O�����ŃG���[���������܂����B", exp );
			tmpWordDicException->ErrorCode = 31101;
			tmpWordDicException->ErrorCode2 = 1;
			throw tmpWordDicException;
		}

		//
		listBoxWordList->BeginUpdate();

		if( SchLanguage == 1 )
		{
			WordSchA();					//����A ����
			//�\�[�g
			WordSchListComparer->setSortOrder( WDWordSchListComparer::schWord, 
						WDConfigParm->WordListSortA1, WDConfigParm->WordListSortA2 );
			ArrayList::Adapter( listBoxWordList->Items )->Sort( WordSchListComparer );

		}else{	
			WordSchB();					//����B ����
			//�\�[�g
			WordSchListComparer->setSortOrder( WDWordSchListComparer::schWord, 
						WDConfigParm->WordListSortB1, WDConfigParm->WordListSortB2 );
			ArrayList::Adapter( listBoxWordList->Items )->Sort( WordSchListComparer );

		}

		//�P��̌��������X�e�[�^�X�o�[�ɕ\��
		if( listBoxWordList->Items->Count == 0 )
		{
			toolStripStatusLabelSchWordCnt->Text = WDConfigParm->WordSchZero;
		}else{
			toolStripStatusLabelSchWordCnt->Text = String::Format( WDConfigParm->WordSchAny, listBoxWordList->Items->Count );
		}

	}catch( Exception^ exp ){
		ExceptionWrite( exp );

	}finally{
		listBoxWordList->EndUpdate();
	}


}

//***** �P�� ����A����
void WordDic::Form1::WordSchA( void )
{
	List<DataRecord^>^	tmpList;
	WDWord^				tmpWord;
	WDWordGrp^			tmpWordGrp;

	//-- �P�� --//
	try
	{
		SchState = 1;								//�������(�P��);

		//���R�[�h����
		tmpList = WordFileA->ReadRecordWords( SchWord, 1 );
		if( tmpList != nullptr )
		{
			for( Int32 i = 0; i < tmpList->Count; i++ )
			{
				tmpWord = gcnew WDWord( tmpList[i] );
				//�d�����Ȃ��P��ID�̏ꍇ�͏���
				if( chkWordList( tmpWord->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage, 
							WDConfigParm->WordListDispA, WDConfigParm->WordListSubDispA );
					tmpWordGrp->addWord( tmpWord, true );
					ReadBaseWordA( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}
			}
		}
	}catch( Exception^ exp ) {
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P�ꌟ�����ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31102;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;

	}finally{
		if( tmpList != nullptr )	delete tmpList;
	}

	//-- �ǂݕ��P --//
	try
	{
		SchState = 2;								//�������(�ǂݕ��P);
		
		//1���ڂ̃f�[�^
		if( WDConfigParm->Read1IdxA != 0 )
		{
			tmpList = WordFileA->ReadRecordWords( SchWord, WDConfigParm->Read1IdxA );
		}else{
			tmpList = nullptr;
		}
		
		if( tmpList != nullptr )
		{
			for( Int32 i = 0; i < tmpList->Count; i++ )
			{
				tmpWord = gcnew WDWord( tmpList[i] );
				//�d�����Ȃ��P��ID�̏ꍇ�͏���
				if( chkWordList( tmpWord->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispA, WDConfigParm->WordListSubDispA );
					tmpWordGrp->addWord( tmpWord, true );
					ReadBaseWordA( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}else{
					delete tmpList[i];
					tmpList[i] = nullptr;
				}
			}
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�ǂݕ��P�������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31102;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;

	}finally{
		if( tmpList != nullptr )	delete tmpList;
	}

	//-- �ǂݕ��Q --//
	try
	{
		SchState = 3;								//�������(�ǂݕ��Q);
		
		//1���ڂ̃f�[�^
		if( WDConfigParm->Read2IdxA != 0 )
		{
			tmpList = WordFileA->ReadRecordWords( SchWord, WDConfigParm->Read2IdxA );
		}else{
			tmpList = nullptr;
		}

		if( tmpList != nullptr )
		{
			for( Int32 i = 0; i < tmpList->Count; i++ )
			{
				tmpWord = gcnew WDWord( tmpList[i] );
				//�d�����Ȃ��P��ID�̏ꍇ�͏���
				if( chkWordList( tmpWord->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispA, WDConfigParm->WordListSubDispA );
					tmpWordGrp->addWord( tmpWord, true );
					ReadBaseWordA( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}else{
					delete tmpList[i];
					tmpList[i] = nullptr;
				}
			}
		}

	}catch( Exception^ exp ) {
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�ǂݕ��Q�������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31102;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		if( tmpList != nullptr )	delete tmpList;
	}

}

//***** �P�� ����B����
void WordDic::Form1::WordSchB( void )
{
	List<DataRecord^>^	tmpList;
	WDWord^				tmpWord;
	WDWordGrp^			tmpWordGrp;

	//-- �P�� --//
	try
	{
		SchState = 1;								//�������(�P��);

		//���R�[�h����
		tmpList = WordFileB->ReadRecordWords( SchWord, 1 );
		if( tmpList != nullptr )
		{
			for( Int32 i = 0; i < tmpList->Count; i++ )
			{
				tmpWord = gcnew WDWord( tmpList[i] );
				//�d�����Ȃ��P��ID�̏ꍇ�͏���
				if( chkWordList( tmpWord->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispB, WDConfigParm->WordListSubDispB );
					tmpWordGrp->addWord( tmpWord, true );
					ReadBaseWordB( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}
			}
		}

	}catch( Exception^ exp ) {
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P�ꌟ�����ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31103;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;

	}finally{
		if( tmpList != nullptr )	delete tmpList;
	}

	//-- �ǂݕ��P --//
	try
	{
		SchState = 2;								//�������(�ǂݕ��P);
		
		//���R�[�h����
		if( WDConfigParm->Read1IdxB != 0 )
		{
			tmpList = WordFileB->ReadRecordWords( SchWord, WDConfigParm->Read1IdxB );
		}else{
			tmpList = nullptr;
		}

		if( tmpList != nullptr )
		{
			for( Int32 i = 0; i < tmpList->Count; i++ )
			{
				tmpWord = gcnew WDWord( tmpList[i] );
				//�d�����Ȃ��P��ID�̏ꍇ�͏���
				if( chkWordList( tmpWord->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispB, WDConfigParm->WordListSubDispB );
					tmpWordGrp->addWord( tmpWord, true );
					ReadBaseWordB( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}
			}
		}

	}catch( Exception^ exp ) {
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�ǂݕ��P�������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31103;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;

	}finally{
		if( tmpList != nullptr )	delete tmpList;
	}

	//-- �ǂݕ��Q --//
	try
	{
		SchState = 3;								//�������(�ǂݕ��Q);
		
		//1���ڂ̃f�[�^
		if( WDConfigParm->Read2IdxB != 0 )
		{
			tmpList = WordFileB->ReadRecordWords( SchWord, WDConfigParm->Read2IdxB );
		}else{
			tmpList = nullptr;
		}

		if( tmpList != nullptr )
		{
			for( Int32 i = 0; i < tmpList->Count; i++ )
			{
				tmpWord = gcnew WDWord( tmpList[i] );
				//�d�����Ȃ��P��ID�̏ꍇ�͏���
				if( chkWordList( tmpWord->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispB, WDConfigParm->WordListSubDispB );
					tmpWordGrp->addWord( tmpWord, true );
					ReadBaseWordB( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}
			}
		}

	}catch( Exception^ exp ) {
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�ǂݕ��Q�������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31103;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		if( tmpList != nullptr )	delete tmpList;
	}
}

//***** �P���{�`���� ����A
void WordDic::Form1::ReadBaseWordA( WDWordGrp^ inWordGrp )
{
	DataRecord^	tmpRecord;
	WDWord^	tmpWord;
	array<Byte>^ tmpWordID;


	//-- ���Ɋ�{�P���Ǎ��ς݂Ȃ�Ȃɂ����Ȃ� --//
	if( inWordGrp->getBaseWord() != nullptr )
	{
		return;
	}

	
	try
	{
		//-- �f�[�^������ --//
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordGrp->getWordID(), nullptr, 0 );

		//-- 1���� --//
		tmpRecord = WordFileA->ReadRecord( tmpWordID, 2 );
		if( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"�P��ID:{0} �̃f�[�^��������܂���B", inWordGrp->getWordID() ) );
			tmpWordDicException->ErrorCode = 31104;
			tmpWordDicException->ErrorCode2 = 1;
			throw tmpWordDicException;
		}
		tmpWord = gcnew WDWord( tmpRecord );
		inWordGrp->addWord( tmpWord, false );
		
		//-- 2���ȍ~ --//
		while( true )
		{
			if( inWordGrp->getBaseWord() != nullptr )
			{
				break;
			}
			if( tmpWord->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpWord->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"�P��ID:{0} �̒P���{�`��������܂���B", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31104;
				tmpWordDicException->ErrorCode2 = 2;
				throw tmpWordDicException;
			}

			tmpRecord = WordFileA->NextRecord( tmpRecord );
			if( tmpRecord == nullptr )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"�P��ID:{0} �̒P���{�`��������܂���B", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31103;
				tmpWordDicException->ErrorCode2 = 3;
				throw tmpWordDicException;
			}
			tmpWord = gcnew WDWord( tmpRecord );
			inWordGrp->addWord( tmpWord, false );
		}
	}catch( Exception^ exp )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P���{�`�̌������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31104;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;

	//-- �I������ --//
	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
	}

}

//***** �P���{�`���� ����B
void WordDic::Form1::ReadBaseWordB( WDWordGrp^ inWordGrp )
{
	DataRecord^	tmpRecord;
	WDWord^	tmpWord;
	array<Byte>^ tmpWordID;


	//-- ���Ɋ�{�P���Ǎ��ς݂Ȃ�Ȃɂ����Ȃ� --//
	if( inWordGrp->getBaseWord() != nullptr )
	{
		return;
	}

	
	try
	{
		//-- �f�[�^������ --//
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordGrp->getWordID(), nullptr, 0 );

		//-- 1���� --//
		tmpRecord = WordFileB->ReadRecord( tmpWordID, 2 );
		if( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"�P��ID:{0} �̃f�[�^��������܂���B", inWordGrp->getWordID() ) );
			tmpWordDicException->ErrorCode = 31105;
			tmpWordDicException->ErrorCode2 = 1;
			throw tmpWordDicException;
		}
		tmpWord = gcnew WDWord( tmpRecord );
		inWordGrp->addWord( tmpWord, false );
		
		//-- 2���ȍ~ --//
		while( true )
		{
			if( inWordGrp->getBaseWord() != nullptr )
			{
				break;
			}
			if( tmpWord->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpWord->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"�P��ID:{0} �̒P���{�`��������܂���B", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31105;
				tmpWordDicException->ErrorCode2 = 2;
				throw tmpWordDicException;
			}

			tmpRecord = WordFileB->NextRecord( tmpRecord );
			if( tmpRecord == nullptr )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"�P��ID:{0} �̒P���{�`��������܂���B", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31105;
				tmpWordDicException->ErrorCode2 = 3;
				throw tmpWordDicException;
			}
			tmpWord = gcnew WDWord( tmpRecord );
			inWordGrp->addWord( tmpWord, false );
		}
	}catch( Exception^ exp )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P���{�`�̌������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31105;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;

	//-- �I������ --//
	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
	}

}

//***** ��{�P��ID�d������
Int32 WordDic::Form1::chkWordList( Int32 inWordID )
{
	//-- ��v����� 0 --//
	for( Int32 i = 0; i < listBoxWordList->Items->Count; i++ )
	{
		WDWordGrp^ tmpWordGrp = safe_cast<WDWordGrp^>(listBoxWordList->Items[i]);

		if( tmpWordGrp->getWordID() == inWordID )
		{
			return 0;
		}
	}
	//-- ��v���� --//
	return -1;
}

