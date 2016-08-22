//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�A�v���P�[�V�����@�\�[�X
//	Version 1.0.0.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	Windows Form�̃A�v���P�[�V����
//------------------------------------------------------------------------------
// WordDicCmd.cpp : �ėp�R�}���h���L�q���܂��B
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
using namespace WordDic;

//***** �敪�擾
WDSegment^	WordDic::Form1::getSegment( List<WDSegment^>^ inSegmentLst,
								Int32 inID, Int32 inNum )
{

	//-- �����`�F�b�N --//
	if( inSegmentLst == nullptr )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�Z�O�����g���X�g�����w��ł��B" );
		tmpWordDicException->ErrorCode = 31201;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}
	if( inID < 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�敪ID�̎w�肪�ԈႦ�Ă��܂��B" );
		tmpWordDicException->ErrorCode = 31201;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	if( inNum < 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�敪�ԍ��̎w�肪�ԈႦ�Ă��܂��B" );
		tmpWordDicException->ErrorCode = 31201;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}

	for each( WDSegment^ tmpSeg in inSegmentLst )
	{
		if( tmpSeg == nullptr )
		{
			continue;
		}

		if( tmpSeg->getSegmentID() == inID &&
			tmpSeg->getSegmentNo() == inNum )
		{
			return tmpSeg;
		}
	}

	//�Y������
	return nullptr;
}

//***** ���ގ擾
WDGroupTreeNode^ WordDic::Form1::getGroup( array<Byte>^ inGroupGt, array<Byte>^ inGroupLt )
{
	array<Byte>^ tmpGroupGt;
	array<Byte>^ tmpGroupLt;
	TreeNodeCollection^ tmpNodes;
    System::Collections::IEnumerator^ schNodes;

	//-- �����`�F�b�N --//
	if( inGroupGt == nullptr ||
		inGroupGt->Length < WDMEAN_GROUPGTLEN )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ޑ�ID�����w��ł��B" );
		tmpWordDicException->ErrorCode = 31202;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}
	if( inGroupLt == nullptr ||
		inGroupLt->Length < WDMEAN_GROUPLTLEN )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ޏ�ID�����w��ł��B" );
		tmpWordDicException->ErrorCode = 31202;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	try
	{

		tmpNodes = treeViewGroupTree->Nodes;
		schNodes = (safe_cast<System::Collections::IEnumerable^>(tmpNodes))->GetEnumerator();
		while( schNodes->MoveNext() )
		{
			//���݂̃m�[�h�̔�r
			WDGroupTreeNode^ tmpWDGroupTreeNode = safe_cast<WDGroupTreeNode^>(schNodes->Current);
			tmpGroupGt = tmpWDGroupTreeNode->getGroupGt( nullptr );
			tmpGroupLt = tmpWDGroupTreeNode->getGroupLt( nullptr );
			if( inGroupGt[0] == tmpGroupGt[0] && inGroupGt[1] == tmpGroupGt[1] &&
				inGroupLt[0] == tmpGroupLt[0] && inGroupLt[1] == tmpGroupLt[1] )
			{
				return tmpWDGroupTreeNode;
			}
			//���m�[�h�̌���
			WDGroupTreeNode^ chldWDGroupTreeNode = getGroupChld( 
						tmpWDGroupTreeNode, inGroupGt, inGroupLt );
			if( chldWDGroupTreeNode != nullptr )
			{
				return chldWDGroupTreeNode;
			}

		}	 
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ތ������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31202;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		IDisposable^ tmpDisposable = dynamic_cast<System::IDisposable^>(schNodes);
		if ( tmpDisposable != nullptr )
		{
			delete tmpDisposable;
		}
	}

	return nullptr;
}

//***** ���ގ擾(���m�[�h����)
WDGroupTreeNode^ WordDic::Form1::getGroupChld( WDGroupTreeNode^ inTreeNode, 
							array<Byte>^ inGroupGt, array<Byte>^ inGroupLt )
{
	array<Byte>^ tmpGroupGt;
	array<Byte>^ tmpGroupLt;
    System::Collections::IEnumerator^ schNodes;

	//-- �����`�F�b�N --//
	if( inGroupGt == nullptr ||
		inGroupGt->Length < WDMEAN_GROUPGTLEN )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ޑ�ID�����w��ł��B" );
		tmpWordDicException->ErrorCode = 31203;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}
	if( inGroupLt == nullptr ||
		inGroupLt->Length < WDMEAN_GROUPLTLEN )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ޏ�ID�����w��ł��B" );
		tmpWordDicException->ErrorCode = 31203;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}
	if( inTreeNode == nullptr )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�����m�[�h�����w��ł��B" );
		tmpWordDicException->ErrorCode = 31203;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}

	try
	{

		schNodes = (safe_cast<System::Collections::IEnumerable^>(inTreeNode->Nodes))->GetEnumerator();
		while( schNodes->MoveNext() )
		{
			//���݂̃m�[�h�̔�r
			WDGroupTreeNode^ tmpWDGroupTreeNode = safe_cast<WDGroupTreeNode^>(schNodes->Current);
			tmpGroupGt = tmpWDGroupTreeNode->getGroupGt( nullptr );
			tmpGroupLt = tmpWDGroupTreeNode->getGroupLt( nullptr );
			if( inGroupGt[0] == tmpGroupGt[0] && inGroupGt[1] == tmpGroupGt[1] &&
				inGroupLt[0] == tmpGroupLt[0] && inGroupLt[1] == tmpGroupLt[1] )
			{
				return tmpWDGroupTreeNode;
			}
			//���m�[�h�̌���
			WDGroupTreeNode^ chldWDGroupTreeNode = getGroupChld( 
						tmpWDGroupTreeNode, inGroupGt, inGroupLt );
			if( chldWDGroupTreeNode != nullptr )
			{
				return chldWDGroupTreeNode;
			}

		}	 
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ތ������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31203;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;

	}finally{
		IDisposable^ tmpDisposable = dynamic_cast<System::IDisposable^>(schNodes);
		if ( tmpDisposable != nullptr )
		{
			delete tmpDisposable;
		}
	}

	return nullptr;
}

//***** XML�t�@�C�����쐬
String^ WordDic::Form1::getXMLFname( void )
{
	DateTime tmpDate;
	Int32	tmpDateNum;
	String^ rtString;

	//-- �������� --//

	//�P��\���f�[�^�i�[�t�H���_�����w��Ȃ��O�G���[
	if( DispXMLForder == nullptr || 
		DispXMLForder->Length == 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��\���f�[�^�i�[�t�H���_����`����Ă��܂���B", nullptr );
		tmpWordDicException->ErrorCode = 31204;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	try
	{

		//-- �t�@�C�������擾 --//
		while( true )
		{
			tmpDate = DateTime::Now;
			tmpDateNum = (tmpDate.Year + tmpDate.Month + tmpDate.Day ) * 1000 +
					tmpDate.Hour + tmpDate.Minute + tmpDate.Second + tmpDate.Millisecond;
			rtString = String::Format( L"{0}WD{1:d08}.xml", DispXMLForder, tmpDateNum.ToString() );
			if( !File::Exists( rtString ) )
			{
				return rtString;
			}
		}
	
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��\���t�@�C�����������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31204;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;

	}
}


//***** ��O���o��
void WordDic::Form1::ExceptionWrite( Exception^ exp )
{
	String^ tmpExpName;
	StreamWriter^ standardOutput;

	if( File::Exists( getFilePathName( L"debug.txt" ) ) )
	{
		standardOutput = File::AppendText( getFilePathName( L"debug.txt" ) );
	}else{
		standardOutput = File::CreateText( getFilePathName( L"debug.txt" ) );
	}
	standardOutput->AutoFlush = true;
	Console::SetOut( standardOutput );
	

	tmpExpName = exp->GetType()->Name;
	if( String::Compare( tmpExpName, gcnew String( L"FJIsamException" ) ) == 0 )
	{
		FJIsamException^ tmpExp = (FJIsamException^)exp;
		Console::WriteLine( 
				String::Format( L"{0} : {1}-{2} : {3} \n",  tmpExp->GetType()->Name, 
				tmpExp->ErrorCode, tmpExp->ErrorCode2, tmpExp->Message ) );
	}else if( String::Compare( tmpExpName, gcnew String( L"WDDatasException" ) ) == 0){
		WDDatasException^ tmpExp = (WDDatasException^)exp;
		Console::WriteLine( 
				String::Format( L"{0} : {1}-{2} : {3} \n",  tmpExp->GetType()->Name, 
				tmpExp->ErrorCode, tmpExp->ErrorCode2, tmpExp->Message ) );
	}else if( String::Compare( tmpExpName, gcnew String( L"WordDicException" ) ) == 0){
		WordDicException^ tmpExp = (WordDicException^)exp;
		Console::WriteLine( 
				String::Format( L"{0} : {1}-{2} : {3} \n",  tmpExp->GetType()->Name, 
				tmpExp->ErrorCode, tmpExp->ErrorCode2, tmpExp->Message ) );
	}else{
		Console::WriteLine( 
			String::Format( L"{0} : {1} \n", exp->Message, exp->GetType()->Name ) );
	}
	Console::WriteLine( exp->StackTrace );

	//�ȉ��A�ŏ��̗�O�����n�_�܂Ń��[�v
	while( exp->InnerException != nullptr )
	{
		exp = exp->InnerException;
		tmpExpName = exp->GetType()->Name;
		if( String::Compare( exp->GetType()->Name, gcnew String( L"FJIsamException" ) ) == 0)
		{
			FJIsamException^ tmpExp = (FJIsamException^)exp;
			Console::WriteLine( 
				String::Format( L" + {0} : {1}-{2} : {3} \n",  tmpExp->GetType()->Name,
				tmpExp->ErrorCode, tmpExp->ErrorCode2, tmpExp->Message ) );
		}else if( String::Compare( tmpExpName, gcnew String( L"WDDatasException" ) ) == 0 ){
			WDDatasException^ tmpExp = (WDDatasException^)exp;
			Console::WriteLine( 
				String::Format( L" + {0} : {1}-{2} : {3} \n",  tmpExp->GetType()->Name,
				tmpExp->ErrorCode, tmpExp->ErrorCode2, tmpExp->Message ) );
		}else if( String::Compare( tmpExpName, gcnew String( L"WordDicException" ) ) == 0){
			WordDicException^ tmpExp = (WordDicException^)exp;
			Console::WriteLine( 
				String::Format( L" + {0} : {1}-{2} : {3} \n",  tmpExp->GetType()->Name,
				tmpExp->ErrorCode, tmpExp->ErrorCode2, tmpExp->Message ) );
		}else{
			Console::WriteLine( 
				String::Format( L" + {0} : {1} \n", exp->GetType()->Name, exp->Message ) );
		}
		Console::WriteLine( exp->StackTrace );
	}
	standardOutput->Close();

}

//***** IE7�ȉ��̕����C������
String^ WordDic::Form1::IE7UnderString( String^ inStr )
{	
	array<Char>^ schChr;
	Int32		i;

	//-- IE�R���|�[�l���g�̃o�[�W�����`�F�b�N
	if( webBrowserBook->Version->Major >= 7 )
	{
		return inStr;
	}

	//-- �����`�F�b�N
	if( inStr == nullptr )
	{
		return nullptr;
	}

	//--�f�[�^�`�F�b�N
	schChr = inStr->ToCharArray();
	i = 0;
	for each( Char c in schChr )
	{
		switch( c )
		{
		case L'\u0303' :
			schChr[i] = L'~';
			break;

		}

		i++;
	}

	//-- �f�[�^�ԋp
	return gcnew String( schChr );
}

//***** �t�@�C���p�X���擾
String^ WordDic::Form1::getFilePathName( String^ inStr )
{
	//-- �����Ȃ��Ȃ�A�v���O�������s�p�X��Ԃ��B
	if( inStr == nullptr )
	{
		return Path::GetDirectoryName( Application::ExecutablePath );
	}

	//-- ��΃p�X�Ȃ牽�����Ȃ��B
	if( Path::IsPathRooted( inStr ) == true )
	{
		return inStr;
	//-- ���΃p�X�Ȃ�WordDic�̎��sPath��t������B
	}else{
		return String::Format( L"{0}\\{1}", 
			Path::GetDirectoryName( Application::ExecutablePath ), inStr );
	}

}
