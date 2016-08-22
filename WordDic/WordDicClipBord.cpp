//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�A�v���P�[�V�����@�\�[�X
//	Version 1.0.0.0		create date 2006/05/08
//	Version 1.0.1.0		create date 2009/09/13
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	Windows Form�̃A�v���P�[�V����
//------------------------------------------------------------------------------
// WordDicClipBorad.cpp : �N���b�v�{�[�h����B
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
// Book�̉E�N���b�N���j���[
//------------------------------------------------------------------------------
//***** �R�s�[�i�I�����ꂽ�������R�s�[����j
System::Void WordDic::Form1::toolStripMenuItemBookCopy_Click(System::Object^  sender, System::EventArgs^  e)
{
	//�u�b�N�̈�ɉ����\������Ă��Ȃ���Ή������Ȃ��B
	if( webBrowserBook->Document->Title == L"" )	return;

	BookWordCopy();
}

//***** Book�̑I���e�L�X�g�R�s�[
void WordDic::Form1::BookWordCopy( void )
{
	String ^strCopyWord;

	//�u�b�N�̈�ɉ����\������Ă��Ȃ���Ή������Ȃ��B
	if( webBrowserBook->Document->Title == L"" )	return;

	strCopyWord = GetProcWord();
	System::Windows::Forms::Clipboard::SetText( strCopyWord );

}

//***** Book���j���[�F�uBing�����v
System::Void WordDic::Form1::ToolStripMenuItemWebSchSite1_Click(System::Object^  sender, System::EventArgs^  e)
{
	String ^strCopyWord;
	String ^strSearchWord;

	//�u�b�N�̈�ɉ����\������Ă��Ȃ���Ή������Ȃ��B
	if( webBrowserBook->Document->Title == L"" )	return;

	//�Ώە�����I��
	strCopyWord = GetProcWord();
	strSearchWord = createSearchStrBytes( strCopyWord );

	//�u���E�U��Web���������{����
	System::Diagnostics::Process::Start( String::Concat( WEB_BING, strSearchWord ) );

}

//***** Book���j���[�F�uGoogle�����v
System::Void WordDic::Form1::ToolStripMenuItemWebSchSite2_Click(System::Object^  sender, System::EventArgs^  e)
{
	String ^strCopyWord;
	String ^strSearchWord;

	//�u�b�N�̈�ɉ����\������Ă��Ȃ���Ή������Ȃ��B
	if( webBrowserBook->Document->Title == L"" )	return;

	//�Ώە�����I��
	strCopyWord = GetProcWord();
	strSearchWord = createSearchStrBytes( strCopyWord );

	//�u���E�U��Web���������{����
	System::Diagnostics::Process::Start( String::Concat( WEB_GOOGLE, strSearchWord ) );
}

//***** Book���j���[�F�u�G���J���^�\���v
System::Void WordDic::Form1::ToolStripMenuItemWebEncycro1_Click(System::Object^  sender, System::EventArgs^  e)
{
	String ^strCopyWord;
	String ^strSearchWord;

	//�u�b�N�̈�ɉ����\������Ă��Ȃ���Ή������Ȃ��B
	if( webBrowserBook->Document->Title == L"" )	return;

	//�Ώە�����I��
	strCopyWord = GetProcWord();
	strSearchWord = createSearchStrBytes( strCopyWord );

	//�u���E�U��Web���������{����
	System::Diagnostics::Process::Start( String::Concat( WEB_ENCALTA, strSearchWord ) );

}

//***** Book���j���[�F�uWiki�\���v
System::Void WordDic::Form1::ToolStripMenuItemWebEncycro2_Click(System::Object^  sender, System::EventArgs^  e)
{
	String ^strCopyWord;
	String ^strSearchWord;

	//�u�b�N�̈�ɉ����\������Ă��Ȃ���Ή������Ȃ��B
	if( webBrowserBook->Document->Title == L"" )	return;

	//�Ώە�����I��
	strCopyWord = GetProcWord();
	strSearchWord = createSearchStrBytes( strCopyWord );

	//�u���E�U��Web���������{����
	System::Diagnostics::Process::Start( String::Concat( WEB_WIKI, strSearchWord ) );
}

//------------------------------------------------------------------------------
// �֘A�R�}���h
//------------------------------------------------------------------------------
//*****Web�������[�h�쐬
String^ WordDic::Form1::GetProcWord( void )
{
	String ^rtWord;
	mshtml::IHTMLDocument2 ^IHtmlDoc;
	mshtml::IHTMLSelectionObject ^ IHtmlSelDoc;
	mshtml::IHTMLTxtRange ^IHtmlTxt;

	IHtmlDoc = static_cast<mshtml::IHTMLDocument2^>(webBrowserBook->Document->DomDocument);
	IHtmlSelDoc = IHtmlDoc->selection;
	IHtmlTxt = static_cast<mshtml::IHTMLTxtRange^>(IHtmlSelDoc->createRange());

	//�u�b�N�ɕ������I������Ă���ΑI�����ꂽ������Ԃ��B
	if (IHtmlTxt->text != nullptr )
	{
		rtWord = IHtmlTxt->text;

		//�����I������Ă��Ȃ���΁A�^�C�g����I������B
	}else{
		rtWord = webBrowserBook->Document->Title;
	}

	return rtWord;

}

//*****Web�������[�h�쐬
String^ WordDic::Form1::createSearchStrBytes( String^ strSchWord )
{
	System::Text::Encoding^ tmpEnc = System::Text::Encoding::UTF8;
	String^ strTrimWord;										//�g���~���O��̌������[�h		
	array<Byte>^ tmpBytes;
	array<Char>^ tmpStrArray;

	String^ strRetWord;

	//�g���~���O���s���B
	strTrimWord = strSchWord->Trim();
	
	//UTF8�փR�[�h�ϊ����s���B
	tmpBytes = tmpEnc->GetBytes( strTrimWord );

	//�ϊ��̈���쐬����
	tmpStrArray = gcnew array<Char>(tmpBytes->Length * 3 +1);

	for( Int32 i = 0; i < tmpBytes->Length; i++ )
	{
		String^ tmpCodeStr = String::Format("%{0:X2}", tmpBytes[i] );
		tmpStrArray[i * 3]		= tmpCodeStr[0];
		tmpStrArray[i * 3 + 1 ]	= tmpCodeStr[1];
		tmpStrArray[i * 3 + 2 ] = tmpCodeStr[2];

	}
	tmpStrArray[tmpBytes->Length * 3] = 0;

	//�ԋp���[�h���쐬����
	strRetWord = gcnew String(tmpStrArray);

	return strRetWord;
}