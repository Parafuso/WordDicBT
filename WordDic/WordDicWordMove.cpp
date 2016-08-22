//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�A�v���P�[�V�����@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	Windows Form�̃A�v���P�[�V����
//------------------------------------------------------------------------------
// WordDicWordMove.cpp : �P��\���ړ�
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Form1.h"				//�P�ꎫ�T���C���t�H�[��
#include "WordDicDef.h"			//�P�ꎫ�T�p��`�t�@�C��
#include "WDGroupTreeNode.h"	//���ރf�[�^�pTreeNode
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
#include "WordDicException.h"	//�P�ꎫ�T�p��O�N���X

using namespace FJIsam;
using namespace WDDatas;
using namespace System::Xml;

//***** �����P�ꃊ�X�g �_�u���N���b�N�i�P��\���j
System::Void WordDic::Form1::webBrowserBook_Navigating(System::Object^  sender, System::Windows::Forms::WebBrowserNavigatingEventArgs^  e)
{
	String^ tmpUrl;

	try
	{
		//-- �������� --//
		try
		{
			tmpUrl = Path::GetFileName( e->Url->ToString() );

		}catch( Exception^ exp ){
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"�ړ���URL�擾���ɃG���[���������܂����B", exp );
			tmpWordDicException->ErrorCode = 31501;
			tmpWordDicException->ErrorCode2 = 1;
			throw tmpWordDicException;
		}

		//-- �f�[�^�̈ړ��悪xml�t�@�C��(�P��f�[�^)�łȂ��ꍇ�A�����N���`�F�b�N --//
		if( String::Compare( Path::GetExtension( tmpUrl ), L".xml", true ) != 0 )
		{
			BrowserLinkChk( tmpUrl );
		}

	}catch( Exception^ exp ){
		ExceptionWrite( exp );
	}
}

//***** �����N�`�F�b�N
void WordDic::Form1::BrowserLinkChk(System::String^ inUrlStr)
{
	String^ tmpStr;
	String^ tmpCmdStr;
	String^ tmpIDStr;
	Int32	tmpWordID;

	//-- �����`�F�b�N --//
	if( inUrlStr == nullptr )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�\���P���񂪖��w��ł��B" );
		tmpWordDicException->ErrorCode = 31502;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;

	}

	//-- ����R�}���h���擾
	tmpCmdStr = Path::GetFileNameWithoutExtension( inUrlStr );
	if( tmpCmdStr->Length == 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�����N�̃R�}���h�����ݒ�ł��B" );
		tmpWordDicException->ErrorCode = 31502;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- �Ώ�ID���擾(�P��ID�܂��͕���ID)
	tmpStr = Path::GetExtension( inUrlStr );
	if( tmpStr->Length <= 1 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�����N��ID�����ݒ�ł��B" );
		tmpWordDicException->ErrorCode = 31502;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}
	tmpIDStr = tmpStr->TrimStart( L'.' );
	delete tmpStr;

	//--�R�}���h���s

	//�P��ړ�(����A)
	if( String::Compare( tmpCmdStr, "A" ) == 0 )
	{
		try
		{
			tmpWordID = Int32::Parse( tmpIDStr );

		}catch( Exception^ exp ){
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��ID�̎w�肪�s���ł��B", exp );
			tmpWordDicException->ErrorCode = 31502;
			tmpWordDicException->ErrorCode2 = 4;
			throw tmpWordDicException;
		}
		WordDispMove( 1, tmpWordID );

	//�P��ړ�(����B)
	}else if( String::Compare( tmpCmdStr, "B" ) == 0 ) {	
		try
		{
			tmpWordID = Int32::Parse( tmpIDStr );

		}catch( Exception^ exp ){
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��ID�̎w�肪�s���ł��B", exp );
			tmpWordDicException->ErrorCode = 31502;
			tmpWordDicException->ErrorCode2 = 5;
			throw tmpWordDicException;
		}
		WordDispMove( 2, tmpWordID );

	//���ތ���(����A)
	}else if( String::Compare( tmpCmdStr, "AG" ) == 0 ) {
		if( tmpIDStr->Length != 4 )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"����ID�̎w�肪�s���ł��B" );
			tmpWordDicException->ErrorCode = 31502;
			tmpWordDicException->ErrorCode2 = 6;
			throw tmpWordDicException;
		}
		WordGroupSch( 1, tmpIDStr );

	//���ތ���(����B)
	}else if( String::Compare( tmpCmdStr, "BG" ) == 0 ) {		
		if( tmpIDStr->Length != 4 )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"����ID�̎w�肪�s���ł��B" );
			tmpWordDicException->ErrorCode = 31502;
			tmpWordDicException->ErrorCode2 = 7;
			throw tmpWordDicException;
		}
		WordGroupSch( 2, tmpIDStr );

	//�R�}���h�s��
	}else {
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�R�}���h������������܂���B" );
		tmpWordDicException->ErrorCode = 31502;
		tmpWordDicException->ErrorCode2 = 8;
		throw tmpWordDicException;
	}

}

//***** �P��\���ړ�
void WordDic::Form1::WordDispMove( Int32 inLang, Int32 inWordID )
{
	array<Byte>^ schWordIDKey;
	WDWordGrp^ schWDWordGrp;
	DataRecord^ tmpDataRecord;
	WDWord^ tmpWord;

	//-- �����`�F�b�N --//
	if( inLang != 1 && inLang != 2 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"����w�肪�s���ł��B" );
		tmpWordDicException->ErrorCode = 31503;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}
	if( inWordID <= 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��ID���s���ł��B" );
		tmpWordDicException->ErrorCode = 31503;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- �����̕\���f�[�^���������� --//
	try
	{
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getSchLang() == inLang &&
				tmpWDWordGrp->getWordID() == inWordID )
			{
				//�\���f�[�^���ŐV�Ɉړ�����
				ReadedWordList->Remove( tmpWDWordGrp );
				ReadedWordList->Add( tmpWDWordGrp );

				//URL���w�肷��
				webBrowserBook->Url = gcnew Uri( tmpWDWordGrp->getXMLFname() );

				return;
			}
		}
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�����̒P��f�[�^�������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31503;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}

	//-- �P����������A�\������ --//
	try
	{

		//�����L�[���擾����
		schWordIDKey = FJIsam::FJIFuncs::Int32ToArray( inWordID, nullptr, 0 );

		switch( inLang )
		{
		//����A����������
		case 1:
			tmpDataRecord = WordFileA->ReadRecord( schWordIDKey, 2 );
			if( tmpDataRecord == nullptr )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( L"�Y������P�ꂪ������܂���B" );
				tmpWordDicException->ErrorCode = 31503;
				tmpWordDicException->ErrorCode2 = 4;
				throw tmpWordDicException;
			}
			schWDWordGrp = gcnew WDWordGrp( inLang,
				WDConfigParm->WordListDispA, WDConfigParm->WordListSubDispA );
			tmpWord = gcnew WDWord( tmpDataRecord );
			schWDWordGrp->addWord( tmpWord, false );

			WordGrpLoadA( schWDWordGrp );
			WordGrpDispA( schWDWordGrp );
			break;

		//����B����������
		case 2:
			tmpDataRecord = WordFileB->ReadRecord( schWordIDKey, 2 );
			if( tmpDataRecord == nullptr )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( L"�Y������P�ꂪ������܂���B" );
				tmpWordDicException->ErrorCode = 31503;
				tmpWordDicException->ErrorCode2 = 5;
				throw tmpWordDicException;
			}
			schWDWordGrp = gcnew WDWordGrp( inLang,
				WDConfigParm->WordListDispB, WDConfigParm->WordListSubDispB );
			tmpWord = gcnew WDWord( tmpDataRecord );
			schWDWordGrp->addWord( tmpWord, false );

			WordGrpLoadB( schWDWordGrp );
			WordGrpDispB( schWDWordGrp );
			break;

		}
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�ړ���̒P��f�[�^�쐬���ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31503;
		tmpWordDicException->ErrorCode2 = 6;
		throw tmpWordDicException;

	}finally{
		if( schWordIDKey != nullptr ) delete schWordIDKey;
	}
}

//***** �P��O���[�v����
void WordDic::Form1::WordGroupSch( Int32 inLang, String^ inGroupID )
{
	array<Byte>^ tmpGroupID;
	System::Text::Encoding^ tmpEnc;				//�G���R�[�_
	
	//-- �����`�F�b�N --//
	if( inLang != 1 && inLang != 2 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"����w�肪�s���ł��B" );
		tmpWordDicException->ErrorCode = 31504;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}
	if( inGroupID == nullptr || 
		inGroupID->Length != 4 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"����ID���s���ł��B" );
		tmpWordDicException->ErrorCode = 31503;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- �O���[�v���� --//
	tmpEnc = System::Text::Encoding::ASCII;
	tmpGroupID = tmpEnc->GetBytes( inGroupID );

	if( SchGroup != nullptr ) delete SchGroup;
	SchGroup = tmpGroupID;

	SchMethod = 2;
	if( inLang == 1 )
	{

		SchLanguage = 1;
		radioButtonGroupA->Checked = true;
	}else{
		SchLanguage = 2;
		radioButtonGroupB->Checked = true;
	}

	try
	{
		listBoxWordList->BeginUpdate();
		//�P�ꃊ�X�g�N���A
		try
		{

			listBoxWordList->Sorted = false;
			schWordLstClear();
		}catch( Exception^ exp ){
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ތ����̑O�����ŃG���[���������܂����B", exp );
			tmpWordDicException->ErrorCode = 31503;
			tmpWordDicException->ErrorCode2 = 3;
			throw tmpWordDicException;
		}

		if( inLang == 1 )
		{
			GroupSchA();					//����A ����
			//�\�[�g
			WordSchListComparer->setSortOrder(  WDWordSchListComparer::schGrp, 
						WDConfigParm->WordListSortA1, WDConfigParm->WordListSortA2 );
			ArrayList::Adapter( listBoxWordList->Items )->Sort( WordSchListComparer );
		}else{	
			GroupSchB();					//����B ����
			//�\�[�g
			WordSchListComparer->setSortOrder( WDWordSchListComparer::schGrp, 
						WDConfigParm->WordListSortB1, WDConfigParm->WordListSortB2 );
			ArrayList::Adapter( listBoxWordList->Items )->Sort( WordSchListComparer );

		}
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ތ����ŃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31504;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		listBoxWordList->EndUpdate();
		webBrowserBook->Url = webBrowserBook->Url;
	}
}