//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�A�v���P�[�V�����@�\�[�X
//	Version 1.0			Create date 2006/05/08
//	Version 1.0.3.0		Change date 2010/11/16

//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	Windows Form�̃A�v���P�[�V����
//------------------------------------------------------------------------------
// WordDicStart.cpp : �����������L�q�����t�@�C���ł��B
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
// �R���X�g���N�^
//------------------------------------------------------------------------------
WordDic::Form1::Form1(void)
{
	InitializeComponent();
	try
	{
		CreateDatas();										//�f�[�^�쐬
		InitializeForms();									//�t�H�[���̏�����
		ReadConfig();										//�R���t�B�O�Z�b�g�A�b�v
		LoadGroupFile();									//����TreeView�쐬
		LoadSegmentFile();									//�敪�t�@�C���Ǎ�
		OpenDicFile();										//�����t�@�C���I�[�v��

	}catch( Exception^ exp ){
		ExceptionWrite( exp );
	}
}
//------------------------------------------------------------------------------
// ��������
//------------------------------------------------------------------------------
//***** �f�[�^�쐬
void WordDic::Form1::CreateDatas( void )
{
	//-- ���X�g�쐬 --//
	//�����\���ς݂̒P�ꃊ�X�g
	ReadedWordList = gcnew List<WDWordGrp^>();

	//�����P�ꃊ�X�g�\�[�g�p�֐�
	WordSchListComparer = gcnew WDWordSchListComparer();


	//-- �P��\���f�[�^�i�[�t�H���_�쐬 --//
	DispXMLForder = String::Format( L"{0}\\{1}", 
		System::Environment::GetEnvironmentVariable("TEMP"), XMLFOLDERNAME );
//	DispXMLForder = String::Format( L"{0}\\{1}", 
//				Path::GetDirectoryName( Application::UserAppDataPath  ), XMLFOLDERNAME );
	
	//-- �P��\���f�[�^�i�[�t�H���_�����݂��Ă��Ȃ���΁A�쐬���� --//
    if (  !Directory::Exists( DispXMLForder ) )
	{
		Directory::CreateDirectory( DispXMLForder );
	//-- �P��\���f�[�^�i�[�t�H���_�����݂��Ă���Β��g����ɂ��� --//
	}else{
		DeleteXmlFiles();
	}

}


//***** �t�H�[���̏�����
void WordDic::Form1::InitializeForms( void )
{
	System::OperatingSystem^	tmpOSInf;				//OS���
	System::Version^		tmpOSVer;				//OS�o�[�W����

	System::Drawing::Icon^	IconSchLangA;			//����`�p�A�C�R��
	System::Drawing::Icon^	IconSchLangB;			//����a�p�A�C�R��
	String^					IconFName;				//�A�C�R���t�@�C����

	//-- OS�̃`�F�b�N(Windows 7�ȑO�Ȃ牽�����Ȃ�)--//

	tmpOSInf = System::Environment::OSVersion;
	tmpOSVer = tmpOSInf->Version;

	if( (tmpOSVer->Major == 6 && tmpOSVer->Minor == 0) ||
		 tmpOSVer->Major < 6 )
	{
		return;
	}

	//-- ����`�{�^���̒�` --//
	IconFName = getFilePathName( L"img\\ja_jp.ico" );
	IconSchLangA = gcnew System::Drawing::Icon( IconFName, System::Drawing::Size(16,16 ) );
	ThumbButtonSchLangA = gcnew ThumbnailToolBarButton( IconSchLangA, L"�N���b�v�{�[�h�̒P��œ��{�ꌟ��" );
	//����`�{�^���̃C�x���g��`
	ThumbButtonSchLangA->Click += gcnew  System::EventHandler<ThumbnailButtonClickedEventArgs^>( this, &Form1::ThumbButtonSchLangA_Click );


	//-- ����a�{�^���̒�` --//
	IconFName = getFilePathName( L"img\\pt_br.ico" );
	IconSchLangB = gcnew System::Drawing::Icon( IconFName, System::Drawing::Size(16,16 ) );
	ThumbButtonSchLangB = gcnew ThumbnailToolBarButton( IconSchLangB, L"�N���b�v�{�[�h�̒P��Ń|���g�K���ꌟ��" );
	//����a�{�^���̃C�x���g��`
	ThumbButtonSchLangB->Click += gcnew System::EventHandler<ThumbnailButtonClickedEventArgs^>( this, &Form1::ThumbButtonSchLangB_Click );


	//�{�^�����^�X�N�o�[�ɃZ�b�g
	ThumbnailToolBarManagerWD = Microsoft::WindowsAPICodePack::Taskbar::TaskbarManager::Instance->ThumbnailToolBars;
		ThumbnailToolBarManagerWD->AddButtons(this->Handle ,ThumbButtonSchLangA,ThumbButtonSchLangB);

}

//***** �R���t�B�O�Z�b�g�A�b�v
void WordDic::Form1::ReadConfig( void )
{
	WDConfigParm = gcnew WordDicCfg();

	WDConfigParm->Read1IdxA = 3;
	WDConfigParm->Read2IdxA = 4;

	WDConfigParm->Read1IdxB = 0;
	WDConfigParm->Read2IdxB = 3;

	//�\�[�g��
	WDConfigParm->WordListSortA1 = 2;				//�Ђ炪��
	WDConfigParm->WordListSortA2 = 1;				//�P��

	//�\��
	WDConfigParm->WordListDispA =  1;				//�P��
	WDConfigParm->WordListSubDispA =  2;			//�Ђ炪��

	//�\�[�g��
	WDConfigParm->WordListSortB1 = 1;				//�A���t�@�x�b�g
	WDConfigParm->WordListSortB2 = 3;				//�J�^�J�i

	//�\��
	WDConfigParm->WordListDispB =  1;				//�A���t�@�x�b�g
	WDConfigParm->WordListSubDispB =  0;				//�Ȃ�

	WDConfigParm->GroupFName = getFilePathName( L"Dic\\GroupJa-jp.fis" );
	WDConfigParm->SegmentFNameA = getFilePathName( L"Dic\\SegmentJa-jp_Ja-jp.fis" );
	WDConfigParm->SegmentFNameB = getFilePathName( L"Dic\\SegmentPt-br_Ja-jp.fis" );

	//�P��t�@�C���� ����A
	WDConfigParm->WordFNameA = getFilePathName( L"Dic\\WordJa-jp.fis" );
	//�Ӗ��t�@�C���� ����A
	WDConfigParm->MeanFNameA = getFilePathName( L"Dic\\MeanJa-jp_Ja-jp.fis" );										
	//�|��t�@�C���� ����A
	WDConfigParm->TransFNameA = getFilePathName( L"Dic\\TransJa-jp_Pt-br.fis" );										
	//�֘A��t�@�C���� ����A
	WDConfigParm->RelationFNameA = getFilePathName( L"Dic\\RelationJa-jp.fis" );;									

	//�P��t�@�C���� ����B
	WDConfigParm->WordFNameB = getFilePathName( L"Dic\\WordPt-br.fis" );										
	//�Ӗ��t�@�C���� ����B
	WDConfigParm->MeanFNameB = getFilePathName( L"Dic\\MeanPt-br_Ja-jp.fis" );										
	//�|��t�@�C���� ����B
	WDConfigParm->TransFNameB = getFilePathName( L"Dic\\TransPt-br_Ja-jp.fis" );
	//�֘A��t�@�C���� ����B
	WDConfigParm->RelationFNameB = getFilePathName( L"Dic\\RelationPt-br.fis" );			

	//XSLT�t�@�C���� ����A
	WDConfigParm->XSLTFNameA =  getFilePathName( L"Japonese1.xslt" );
	//XSLT�t�@�C���� ����B
	WDConfigParm->XSLTFNameB =  getFilePathName( L"Portugues1.xslt" );

	//�P�ꂪ������Ȃ���
	WDConfigParm->WordSchZero = L"�P�ꂪ������܂���";
	//WDConfigParm����������
	WDConfigParm->WordSchAny = L"{0} ������܂���";


}


//***** ����TreeView�쐬
void WordDic::Form1::LoadGroupFile( void )
{
	FIsam^ GroupFile;

	DataRecord^ tmpRecord;
	WDGroup^ tmpGroup;
	WDGroupTreeNode^ tmpTreeNode;
	array<Byte>^ tmpGroupLt;

	Int32 tmpItemCnt;

	TreeNode^ BaseNode;

	//-- �t�@�C���I�[�v�� --//
	try
	{
		GroupFile = gcnew FIsam( WDConfigParm->GroupFName, 4096, IsamOpenMode::READ_ONLY );
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ރt�@�C���̃I�[�v���Ɏ��s���܂����B", exp );
		tmpWordDicException->ErrorCode = 31001;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- ���ރt�@�C���Ǎ� --//
	try
	{
		//-- �x�[�X�m�[�h�쐬 --//
		tmpRecord = GroupFile->FirstRecord(1);
		if ( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ރf�[�^������܂���B");
			tmpWordDicException->ErrorCode = 31001;
			tmpWordDicException->ErrorCode2 = 2;
		}
		tmpGroup = gcnew WDGroup( tmpRecord );
		BaseNode = gcnew WDGroupTreeNode( tmpGroup );
		treeViewGroupTree->Nodes->Add( BaseNode );

		//-- 1�ڂ̕��ރm�[�h�쐬 --//
		tmpRecord = GroupFile->NextRecord( tmpRecord );
		if ( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ރf�[�^��1�ڂ̏�񂪂���܂���B" );
			tmpWordDicException->ErrorCode = 31001;
			tmpWordDicException->ErrorCode2 = 3;
		}
		tmpGroup = gcnew WDGroup( tmpRecord );
		tmpTreeNode = gcnew WDGroupTreeNode( tmpGroup );
		BaseNode->Nodes->Add( tmpTreeNode );
		
		WDGroupTreeNode^ tmpParentNode = tmpTreeNode;		
		
		while( true )
		{
			tmpItemCnt++;
			tmpRecord = GroupFile->NextRecord( tmpRecord );
			delete tmpGroup;
			if( tmpRecord == nullptr )
			{
				break;
			}
			tmpGroup = gcnew WDGroup( tmpRecord );
			tmpTreeNode  = gcnew WDGroupTreeNode( tmpGroup );
			tmpGroupLt = tmpTreeNode->getGroupLt( nullptr );
			// ���ޏ��� '00'�Ȃ�@���x���P�i���ނ̌��O���[�v)�ɂ���
			if( tmpGroupLt[0] == '0' && tmpGroupLt[1] == '0' )
			{
				BaseNode->Nodes->Add( tmpTreeNode );
				tmpParentNode = tmpTreeNode;
			}else{
				tmpParentNode->Nodes->Add( tmpTreeNode );
			}
		}
		
		//-- �������� --//
		BaseNode->Expand();					//BaseNode��W�J����

		GroupFile->Close();					//Isam�N���[�Y
		delete GroupFile;

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"����TreeView�쐬�Ɏ��s���܂����B", exp );
		tmpWordDicException->ErrorCode = 31001;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;
	}
}

//***** �敪�t�@�C�����[�h
void WordDic::Form1::LoadSegmentFile( void )
{
	FIsam^		SegmentFile;			//�敪�t�@�C��
	DataRecord^	tmpRecord;				//��ƃ��R�[�h
	WDSegment^	tmpSegment;				//�敪�f�[�^


	//-- ���X�g�쐬 --//
	SegmentListA = gcnew List<WDSegment^>();
	SegmentListB = gcnew List<WDSegment^>();

	//--�敪�t�@�C��A�Ǎ�--//
	//�t�@�C���I�[�v��
	try
	{
		SegmentFile = gcnew FIsam( WDConfigParm->SegmentFNameA, 4096, IsamOpenMode::READ_ONLY );
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"�敪�t�@�C��A({0})�̃I�[�v���Ɏ��s���܂����B", WDConfigParm->SegmentFNameA ), exp );
		tmpWordDicException->ErrorCode = 31002;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	try
	{
		//1���ړǍ�
		tmpRecord = SegmentFile->FirstRecord(1);
		if ( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"�敪�f�[�^A({0})������܂���B",WDConfigParm->SegmentFNameA ) );
			tmpWordDicException->ErrorCode = 31002;
			tmpWordDicException->ErrorCode2 = 2;
		}
		tmpSegment = gcnew WDSegment( tmpRecord );
		SegmentListA->Add( tmpSegment );

		//2���ڈȍ~
		while( true )
		{
			tmpRecord = SegmentFile->NextRecord( tmpRecord );
			if( tmpRecord == nullptr )
			{
				break;
			}

			tmpSegment = gcnew WDSegment( tmpRecord );
			SegmentListA->Add( tmpSegment );
		}
		SegmentFile->Close();
		delete SegmentFile;

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�敪���X�gA�̍쐬�Ɏ��s���܂����B", exp );
		tmpWordDicException->ErrorCode = 31002;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}

	//--�敪�t�@�C��A�Ǎ�--//
	//�t�@�C���I�[�v��
	try
	{
		SegmentFile = gcnew FIsam( WDConfigParm->SegmentFNameB, 4096, IsamOpenMode::READ_ONLY );
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"�敪�t�@�C��B({0})�̃I�[�v���Ɏ��s���܂����B", WDConfigParm->SegmentFNameB ), exp );
		tmpWordDicException->ErrorCode = 31002;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;
	}

	try
	{
		//1���ړǍ�
		tmpRecord = SegmentFile->FirstRecord(1);
		if ( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"�敪�f�[�^B({0})������܂���B",WDConfigParm->SegmentFNameB ) );
			tmpWordDicException->ErrorCode = 31002;
			tmpWordDicException->ErrorCode2 = 2;
		}
		tmpSegment = gcnew WDSegment( tmpRecord );
		SegmentListB->Add( tmpSegment );

		//2���ڈȍ~
		while( true )
		{
			tmpRecord = SegmentFile->NextRecord( tmpRecord );
			if( tmpRecord == nullptr )
			{
				break;
			}

			tmpSegment = gcnew WDSegment( tmpRecord );
			SegmentListB->Add( tmpSegment );
		}
		SegmentFile->Close();
		delete SegmentFile;

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�敪���X�gB�̍쐬�Ɏ��s���܂����B", exp );
		tmpWordDicException->ErrorCode = 31002;
		tmpWordDicException->ErrorCode2 = 6;
		throw tmpWordDicException;
	}

}

//***** �����t�@�C���I�[�v��
void WordDic::Form1::OpenDicFile( void )
{

	//-- ����A�֘A�t�@�C���I�[�v�� --//
	//�P��A�t�@�C��
	try
	{
		WordFileA = gcnew FIsam( WDConfigParm->WordFNameA, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"�P��t�@�C��A({0})�̃I�[�v���Ɏ��s���܂����B", WDConfigParm->WordFNameA ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}
	//�Ӗ�A�t�@�C��
	try
	{
		MeanFileA = gcnew FIsam( WDConfigParm->MeanFNameA, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"�Ӗ��t�@�C��A({0})�̃I�[�v���Ɏ��s���܂����B", WDConfigParm->MeanFNameA ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}
	//�|��A�t�@�C��
	try
	{
		TransFileA = gcnew FIsam( WDConfigParm->TransFNameA, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"�|��t�@�C��A({0})�̃I�[�v���Ɏ��s���܂����B", WDConfigParm->TransFNameA ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}
	//�֘A��A�t�@�C��
	try
	{
		RelationFileA = gcnew FIsam( WDConfigParm->RelationFNameA, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"�֘A��t�@�C��A({0})�̃I�[�v���Ɏ��s���܂����B", WDConfigParm->RelationFNameA ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;
	}

	//-- ����B�֘A�t�@�C���I�[�v��
	//�P��B�t�@�C��
	try
	{
		WordFileB = gcnew FIsam( WDConfigParm->WordFNameB, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"�P��t�@�C��B({0})�̃I�[�v���Ɏ��s���܂����B", WDConfigParm->WordFNameB ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 5;
		throw tmpWordDicException;
	}
	//�Ӗ�B�t�@�C��
	try
	{
		MeanFileB = gcnew FIsam( WDConfigParm->MeanFNameB, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"�Ӗ��t�@�C��B({0})�̃I�[�v���Ɏ��s���܂����B", WDConfigParm->MeanFNameB ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 6;
		throw tmpWordDicException;
	}
	//�|��B�t�@�C��
	try
	{
		TransFileB = gcnew FIsam( WDConfigParm->TransFNameB, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"�|��t�@�C��B({0})�̃I�[�v���Ɏ��s���܂����B", WDConfigParm->TransFNameB ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 7;
		throw tmpWordDicException;
	}
	//�֘A��A�t�@�C��
	try
	{
		RelationFileB = gcnew FIsam( WDConfigParm->RelationFNameB, 4096, IsamOpenMode::READ_ONLY );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( 
			String::Format( L"�֘A��t�@�C��B({0})�̃I�[�v���Ɏ��s���܂����B", WDConfigParm->RelationFNameB ), exp );
		tmpWordDicException->ErrorCode = 31003;
		tmpWordDicException->ErrorCode2 = 8;
		throw tmpWordDicException;
	}
	

	//-- �ݒ�_�C�A���O
	dlgWDConfig = gcnew WDConfig();

	//-- �o�[�W�����_�C�A���O
	dlgWDVerDialog = gcnew WDVerDialog();

}
