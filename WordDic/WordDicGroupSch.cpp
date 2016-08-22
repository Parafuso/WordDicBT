//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�A�v���P�[�V�����@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	Windows Form�̃A�v���P�[�V����
//------------------------------------------------------------------------------
// WordDicGroupSch.cpp : ���ތ���
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
//***** ���ރc���[�r���[ �_�u���N���b�N
System::Void WordDic::Form1::treeViewGroupTree_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	WDGroupTreeNode^ tmpTreeNode;
	
	//-- �A�C�e�������I���Ȃ牽�����Ȃ� --//
	if( treeViewGroupTree->SelectedNode == nullptr )
	{
		return;
	}

	//-- ������ --//
	tmpTreeNode = safe_cast<WDGroupTreeNode^>(treeViewGroupTree->SelectedNode);
	if( SchGroup != nullptr )
	{
		delete SchGroup;
		SchGroup = nullptr;
	}
	SchGroup = gcnew array<Byte>( WDMEAN_GROUPGTLEN + WDMEAN_GROUPLTLEN );

	tmpTreeNode->getGroupGt( SchGroup );
	Buffer::BlockCopy( tmpTreeNode->getGroupLt( nullptr ), 0, SchGroup, WDMEAN_GROUPGTLEN, WDMEAN_GROUPLTLEN );

	SchMethod = 2;								//�������@(����)
	if( radioButtonGroupA->Checked == true )	//��������(A or B)
	{
		SchLanguage = 1;
	}else{
		SchLanguage = 2;
	}
	SchState = 0;								//�������(���ނ̂��� 0);

	//-- ���ތ��� --//
	try
	{
		//�P�ꃊ�X�g�N���A
		try
		{
			listBoxWordList->Sorted = false;
			schWordLstClear();
		}catch( Exception^ exp ){
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ތ����̑O�����ŃG���[���������܂����B", exp );
			tmpWordDicException->ErrorCode = 31601;
			tmpWordDicException->ErrorCode2 = 1;
			throw tmpWordDicException;
		}

		listBoxWordList->BeginUpdate();

		if( SchLanguage == 1 )
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

//------------------------------------------------------------------------------
// ��������
//------------------------------------------------------------------------------
//***** ���ތ��� ����A
void WordDic::Form1::GroupSchA( void )
{
	DataRecord^ tmpRecord;
	WDMean^		tmpMean;
	WDWordGrp^	tmpWordGrp;

	//-- �Ӗ� --//
	try
	{
		
		//1���ڂ̃f�[�^
		tmpRecord = MeanFileA->ReadRecord( SchGroup, 2 );
		if( tmpRecord != nullptr )
		{
			tmpMean = gcnew WDMean( tmpRecord );
			tmpWordGrp = gcnew WDWordGrp( SchLanguage,
				WDConfigParm->WordListDispA, WDConfigParm->WordListSubDispA );
			tmpWordGrp->addMean( tmpMean, true, tmpMean->getMeanFlg(0) );
			ReadBaseWordA( tmpWordGrp );

			listBoxWordList->Items->Add( tmpWordGrp );

			while( true )
			{
				if( tmpMean->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
					tmpMean->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
				{
					break;
				}

				tmpRecord = MeanFileA->NextRecord( tmpRecord );
				if( tmpRecord == nullptr )
				{
					break;
				}
				tmpMean = gcnew WDMean( tmpRecord );
				//���Ɍ����ς݂̒P��ID�Ɠ���Ȃ牽�����Ȃ�
				if( chkWordList( tmpMean->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispA, WDConfigParm->WordListSubDispA );
					tmpWordGrp->addMean( tmpMean, true, tmpMean->getMeanFlg(0) );
					ReadBaseWordA( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}
			}
		}
	}catch( Exception^ exp )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ތ������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31602;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

}

//***** ���ތ��� ����B
void WordDic::Form1::GroupSchB( void )
{
	DataRecord^ tmpRecord;
	WDMean^		tmpMean;
	WDWordGrp^	tmpWordGrp;

	//-- �Ӗ� --//
	try
	{
		//1���ڂ̃f�[�^
		tmpRecord = MeanFileB->ReadRecord( SchGroup, 2 );
		if( tmpRecord != nullptr )
		{
			tmpMean = gcnew WDMean( tmpRecord );
			tmpWordGrp = gcnew WDWordGrp( SchLanguage,
				WDConfigParm->WordListDispB, WDConfigParm->WordListSubDispB );
			tmpWordGrp->addMean( tmpMean, true, tmpMean->getMeanFlg(0) );
			ReadBaseWordB( tmpWordGrp );

			listBoxWordList->Items->Add( tmpWordGrp );

			while( true )
			{
				if( tmpMean->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
					tmpMean->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
				{
					break;
				}

				tmpRecord = MeanFileB->NextRecord( tmpRecord );
				if( tmpRecord == nullptr )
				{
					break;
				}
				tmpMean = gcnew WDMean( tmpRecord );
				//���Ɍ����ς݂̒P��ID�Ɠ���Ȃ牽�����Ȃ�
				if( chkWordList( tmpMean->getWordID() ) != 0 )
				{
					tmpWordGrp = gcnew WDWordGrp( SchLanguage,
						WDConfigParm->WordListDispB, WDConfigParm->WordListSubDispB );
					tmpWordGrp->addMean( tmpMean, true, tmpMean->getMeanFlg(0) );
					ReadBaseWordB( tmpWordGrp );
					listBoxWordList->Items->Add( tmpWordGrp );
				}
			}
		}
	}catch( Exception^ exp )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"���ތ������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31603;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

}