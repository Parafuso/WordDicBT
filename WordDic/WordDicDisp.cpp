//------------------------------------------------------------------------------
//	���Ƃ΂̎��T�@���Ƃ΂̎��T�r���[�A�A�v���P�[�V�����@�\�[�X
//	Version 1.0.1.0		create date 2006/05/08
//	Version 1.0.1.1		change date 2010/10/22	WordGrpDispA�@WordGrpDispB ��{�P��\�������P�Ԗڂ̓ǂ݂���ɕύX
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	Windows Form�̃A�v���P�[�V����
//------------------------------------------------------------------------------
// WordDicWordDisp.cpp : �P��\��
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
using namespace System::Xml;

//***** �����P�ꃊ�X�g �_�u���N���b�N�i�P��\���j
System::Void WordDic::Form1::listBoxWordList_DoubleClick(System::Object^ sender, System::EventArgs^ e)
{
	WDWordGrp^ selWDWordGrp;

	try
	{
		//-- �I������Ă���P����擾
		if( listBoxWordList->SelectedItem == nullptr )
		{
			return;
		}else{
			selWDWordGrp = safe_cast<WDWordGrp^>(listBoxWordList->SelectedItem);
		}

		if( SchLanguage == 1 )
		{
			WordGrpLoadA( selWDWordGrp );
			WordGrpDispA( selWDWordGrp );
		}else{
			WordGrpLoadB( selWDWordGrp );
			WordGrpDispB( selWDWordGrp );
		}

	}catch( Exception^ exp ){
		ExceptionWrite( exp );
	}
}


//***** �P��O���[�v�Ǎ� ����A
void WordDic::Form1::WordGrpLoadA( WDWordGrp^ inWordGrp )
{
	DataRecord^	tmpRecord;
	WDWord^	tmpWord;
	WDMean^ tmpMean;
	WDTrans^ tmpTrans;
	WDRelation^ tmpRelation;
	array<Byte>^ tmpWordID;

	//-- �쐬�ς݂̃f�[�^�̗L�����`�F�b�N
	try
	{
		//����XML�쐬�ς݂Ȃ牽�����Ȃ�
		if( inWordGrp->getXMLFname() != nullptr )
		{
			return;
		}

		//����XML�f�[�^���쐬���Ă��闚�����Ȃ����`�F�b�N
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getWordID() == inWordGrp->getWordID() && 
				tmpWDWordGrp->getSchLang() == inWordGrp->getSchLang() )
			{
				//�Ǎ��ς݃f�[�^�������Ă��AXML�f�[�^���Ȃ���΍��Ȃ���
				if( tmpWDWordGrp->getXMLFname() == nullptr ||
					tmpWDWordGrp->getXMLFname()->Length == 0 )
				{
					ReadedWordList->Remove( tmpWDWordGrp );
					delete tmpWDWordGrp;
				}else{

					//�\�����X�g(����)�̍Ō�ɒǉ�����
					ReadedWordList->Remove( tmpWDWordGrp );
					ReadedWordList->Add( tmpWDWordGrp );
					inWordGrp->setXMLFname( tmpWDWordGrp->getXMLFname() );
					return;
				}
			}
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�����̒P��\���f�[�^�������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31303;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//���X�g�쐬
	try
	{
		//-- �f�[�^������ --//
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordGrp->getWordID(), nullptr, 0 );

		//-- �P��Ǎ� --//
		//1����
		tmpRecord = WordFileA->ReadRecord( tmpWordID, 2 );
		if( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"�P��ID:{0} �̒P�ꂪ������܂���B", inWordGrp->getWordID() ) );
			tmpWordDicException->ErrorCode = 31303;
			tmpWordDicException->ErrorCode2 = 2;
			throw tmpWordDicException;
		}
		tmpWord = gcnew WDWord( tmpRecord );
		inWordGrp->addWord( tmpWord, false );
		
		//2���ȍ~
		while( true )
		{
			if( tmpWord->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpWord->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
			{
				break;
			}

			tmpRecord = WordFileA->NextRecord( tmpRecord );
			if( tmpRecord == nullptr )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"�P��ID:{0} �̑S�Ă̒P�ꂪ�ǂݍ��߂܂���B", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31303;
				tmpWordDicException->ErrorCode2 = 3;
				throw tmpWordDicException;
			}
			tmpWord = gcnew WDWord( tmpRecord );
			inWordGrp->addWord( tmpWord, false );
		}

		//-- �Ӗ��Ǎ� --//
		//1����
		tmpRecord = MeanFileA->ReadRecord( tmpWordID, 1 );
		if( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"�P��ID:{0} �̈Ӗ���������܂���B", inWordGrp->getWordID() ) );
			tmpWordDicException->ErrorCode = 31303;
			tmpWordDicException->ErrorCode2 = 4;
			throw tmpWordDicException;
		}
		tmpMean = gcnew WDMean( tmpRecord );
		inWordGrp->addMean( tmpMean, false, 0 );
		
		//2���ȍ~
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
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"�P��ID:{0} �̑S�Ă̈Ӗ����ǂݍ��߂܂���B", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31303;
				tmpWordDicException->ErrorCode2 = 5;
				throw tmpWordDicException;
			}
			tmpMean = gcnew WDMean( tmpRecord );
			inWordGrp->addMean( tmpMean, false, 0 );
		}

		//-- �|��Ǎ� --//
		//1����
		tmpRecord = TransFileA->ReadRecord( tmpWordID, 1 );
		if( tmpRecord != nullptr )
		{
			tmpTrans = gcnew WDTrans( tmpRecord );
			inWordGrp->addTrans( tmpTrans );
		
			//2���ȍ~
			while( true )
			{
				if( tmpTrans->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
					tmpTrans->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )	
				{
					break;
				}

				tmpRecord = TransFileA->NextRecord( tmpRecord );
				if( tmpRecord == nullptr )
				{
					WordDicException^ tmpWordDicException = gcnew WordDicException( 
						String::Format( L"�P��ID:{0} �̑S�Ă̖|�󂪓ǂݍ��߂܂���B", inWordGrp->getWordID() ) );
					tmpWordDicException->ErrorCode = 31303;
					tmpWordDicException->ErrorCode2 = 6;
					throw tmpWordDicException;
				}
				tmpTrans = gcnew WDTrans( tmpRecord );
				inWordGrp->addTrans( tmpTrans );
			}
		}

		//-- �֘A��Ǎ� --//
		//1����
		tmpRecord = RelationFileA->ReadRecord( tmpWordID, 1 );
		if( tmpRecord != nullptr )
		{
			tmpRelation = gcnew WDRelation( tmpRecord );
			inWordGrp->addRelation( tmpRelation );

			//2���ȍ~
			while( true )
			{
				if( tmpRelation->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
					tmpRelation->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
				{
					break;
				}
	
				tmpRecord = RelationFileA->NextRecord( tmpRecord );
				if( tmpRecord == nullptr )
				{
					WordDicException^ tmpWordDicException = gcnew WordDicException( 
						String::Format( L"�P��ID:{0} �̑S�Ă̊֘A�ꂪ�ǂݍ��߂܂���B", inWordGrp->getWordID() ) );
					tmpWordDicException->ErrorCode = 31303;
					tmpWordDicException->ErrorCode2 = 7;
					throw tmpWordDicException;
				}
				tmpRelation = gcnew WDRelation( tmpRecord );
				inWordGrp->addRelation( tmpRelation );
			}
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��O���[�v�̌������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31303;
		tmpWordDicException->ErrorCode2 = 8;
		throw tmpWordDicException;

	//-- �I������ --//
	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
	}

}

//***** �P��O���[�v�Ǎ� ����B
void WordDic::Form1::WordGrpLoadB( WDWordGrp^ inWordGrp )
{
	DataRecord^	tmpRecord;
	WDWord^	tmpWord;
	WDMean^ tmpMean;
	WDTrans^ tmpTrans;
	WDRelation^ tmpRelation;
	array<Byte>^ tmpWordID;
	
	//-- �쐬�ς݂̃f�[�^�̗L�����`�F�b�N
	try
	{
		//����XML�쐬�ς݂Ȃ牽�����Ȃ�
		if( inWordGrp->getXMLFname() != nullptr )
		{
			return;
		}

		//����XML�f�[�^���쐬���Ă��闚�����Ȃ����`�F�b�N
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getWordID() == inWordGrp->getWordID() && 
				tmpWDWordGrp->getSchLang() == inWordGrp->getSchLang() )
			{
				//�Ǎ��ς݃f�[�^�������Ă��AXML�f�[�^���Ȃ���΍��Ȃ���
				if( tmpWDWordGrp->getXMLFname() == nullptr ||
					tmpWDWordGrp->getXMLFname()->Length == 0 )
				{
					ReadedWordList->Remove( tmpWDWordGrp );
					delete tmpWDWordGrp;
				}else{

					//�\�����X�g(����)�̍Ō�ɒǉ�����
					ReadedWordList->Remove( tmpWDWordGrp );
					ReadedWordList->Add( tmpWDWordGrp );
					inWordGrp->setXMLFname( tmpWDWordGrp->getXMLFname() );
					return;
				}
			}
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�����̒P��\���f�[�^�������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31304;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	try
	{
		//-- �f�[�^������ --//
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordGrp->getWordID(), nullptr, 0 );

		//-- �P��Ǎ� --//
		//1����
		tmpRecord = WordFileB->ReadRecord( tmpWordID, 2 );
		if( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"�P��ID:{0} �̒P�ꂪ������܂���B", inWordGrp->getWordID() ) );
			tmpWordDicException->ErrorCode = 31304;
			tmpWordDicException->ErrorCode2 = 2;
			throw tmpWordDicException;
		}
		tmpWord = gcnew WDWord( tmpRecord );
		inWordGrp->addWord( tmpWord, false );
		
		//2���ȍ~
		while( true )
		{
			if( tmpWord->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpWord->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
			{
				break;
			}

			tmpRecord = WordFileB->NextRecord( tmpRecord );
			if( tmpRecord == nullptr )
			{
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"�P��ID:{0} �̑S�Ă̒P�ꂪ�ǂݍ��߂܂���B", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31304;
				tmpWordDicException->ErrorCode2 = 3;
				throw tmpWordDicException;
			}
			tmpWord = gcnew WDWord( tmpRecord );
			inWordGrp->addWord( tmpWord, false );
		}

		//-- �Ӗ��Ǎ� --//
		//1����
		tmpRecord = MeanFileB->ReadRecord( tmpWordID, 1 );
		if( tmpRecord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( 
				String::Format( L"�P��ID:{0} �̈Ӗ���������܂���B", inWordGrp->getWordID() ) );
			tmpWordDicException->ErrorCode = 31304;
			tmpWordDicException->ErrorCode2 = 4;
			throw tmpWordDicException;
		}
		tmpMean = gcnew WDMean( tmpRecord );
		inWordGrp->addMean( tmpMean, false, 0 );
		
		//2���ȍ~
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
				WordDicException^ tmpWordDicException = gcnew WordDicException( 
					String::Format( L"�P��ID:{0} �̑S�Ă̈Ӗ����ǂݍ��߂܂���B", inWordGrp->getWordID() ) );
				tmpWordDicException->ErrorCode = 31304;
				tmpWordDicException->ErrorCode2 = 5;
				throw tmpWordDicException;
			}
			tmpMean = gcnew WDMean( tmpRecord );
			inWordGrp->addMean( tmpMean, false, 0 );
		}

		//-- �|��Ǎ� --//
		//1����
		tmpRecord = TransFileB->ReadRecord( tmpWordID, 1 );
		if( tmpRecord != nullptr )
		{
			tmpTrans = gcnew WDTrans( tmpRecord );
			inWordGrp->addTrans( tmpTrans );
			
			//2���ȍ~
			while( true )
			{
				if( tmpTrans->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
					tmpTrans->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
				{
					break;
				}

				tmpRecord = TransFileB->NextRecord( tmpRecord );
				if( tmpRecord == nullptr )
				{
					WordDicException^ tmpWordDicException = gcnew WordDicException( 
						String::Format( L"�P��ID:{0} �̑S�Ă̒P�ꂪ�ǂݍ��߂܂���B", inWordGrp->getWordID() ) );
					tmpWordDicException->ErrorCode = 31304;
					tmpWordDicException->ErrorCode2 = 6;
					throw tmpWordDicException;
				}
				tmpTrans = gcnew WDTrans( tmpRecord );
				inWordGrp->addTrans( tmpTrans );
	
			}
		}

		//-- �֘A��Ǎ� --//
		//1����
		tmpRecord = RelationFileB->ReadRecord( tmpWordID, 1 );
		if( tmpRecord != nullptr )
		{
			tmpRelation = gcnew WDRelation( tmpRecord );
			inWordGrp->addRelation( tmpRelation );
		
			//2���ȍ~
			while( true )
			{
				if( tmpRelation->getRecord()->getEachKeyFlg() == IS_NOEACHKEY ||
					tmpRelation->getRecord()->getEachKeyFlg() == IS_EACHKEYLST )
				{
					break;
				}

				tmpRecord = RelationFileB->NextRecord( tmpRecord );
				if( tmpRecord == nullptr )
				{
					WordDicException^ tmpWordDicException = gcnew WordDicException( 
						String::Format( L"�P��ID:{0} �̑S�Ă̒P�ꂪ�ǂݍ��߂܂���B", inWordGrp->getWordID() ) );
					tmpWordDicException->ErrorCode = 31304;
					tmpWordDicException->ErrorCode2 = 7;
					throw tmpWordDicException;
				}
				tmpRelation = gcnew WDRelation( tmpRecord );
				inWordGrp->addRelation( tmpRelation );
			}
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��O���[�v�̌������ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31304;
		tmpWordDicException->ErrorCode2 = 8;
		throw tmpWordDicException;

	//-- �I������ --//
	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
	}

}

//***** �P��O���[�v�\�� ����A
void WordDic::Form1::WordGrpDispA( WDWordGrp^ inWordGrp )
{
	String^	XmlFName;
	XmlTextWriter^ XmlFStream;
	WDWord^			tmpWDWord;
	WDWord^			tmpWDSubWord;
	WDMean^			tmpWDMean;
	WDTrans^		tmpWDTrans;
	WDRelation^		tmpWDRelation;
	array<Byte>^	tmpGroup;

	String^			tmpGroupName;				//���ޖ�
	array<Byte>^	tmpGroupID;					//����ID
	array<Byte>^	tmpGroupIDGt;				//����ID��
	array<Byte>^	tmpGroupIDLt;				//����ID��
	System::Text::Encoding^ tmpEnc;				//�G���R�[�_
	array<Char>^	tmpGroupIDStr;				//���ޖ�(�o�͗p)

	Int32			oldPractical = -1;			//���p�`
	Int32			oldPlurality = -1;			//�P������
	Int32			oldGramatical = -1;			//�l��
	Int32			oldSex = -1;				//��

	String^			tmpPrStr;
	String^			oldPrStr;
	String^			tmpRdStr;

	//-- �Ǎ��ς݃f�[�^������΂����\������
	try
	{
		if( inWordGrp->getXMLFname() != nullptr )
		{
				//XML�f�[�^������Ε\�����ďI��
				webBrowserBook->Url = gcnew Uri( inWordGrp->getXMLFname() );		

				return;
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��f�[�^�\���ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31305;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- �V����XML�t�@�C�����쐬����
	try
	{
		//-- �����ݒ� --//
		tmpGroup = gcnew array<Byte>( WDMEAN_GROUPGTLEN + WDMEAN_GROUPLTLEN );

		XmlFName = getXMLFname();														//�o��XML�t�@�C�����擾

		XmlFStream = gcnew XmlTextWriter( XmlFName, System::Text::Encoding::Unicode );	//�o��XML�t�@�C�����Z�b�g
		XmlFStream->Formatting = Formatting::Indented;									//�C���f���g����
		XmlFStream->QuoteChar = L'\"';													//�N�I�[�^�ݒ�@"
		XmlFStream->WriteStartDocument();												//�h�L�������g�X�^�[�g
		XmlFStream->WriteProcessingInstruction( L"xml-stylesheet",						//XSLT�w��
			String::Format( L"type=\"text/xsl\" href=\"{0}\"", WDConfigParm->XSLTFNameA ) );

		//���[�g�L�q
		XmlFStream->WriteStartElement( WORDS_NODE );									

		//-- ��{�P��L�q --//
		//�P�ڂ̓ǂݕ��̊�{�P���\������
		tmpWDWord = tmpWDSubWord = inWordGrp->getBaseWord( 0 );
		if( tmpWDWord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��f�[�^������܂���B" );
			tmpWordDicException->ErrorCode = 31305;
			tmpWordDicException->ErrorCode2 = 2;
			throw tmpWordDicException;
		}

		XmlFStream->WriteStartElement( BASE_NODE );															//�x�[�X
		XmlFStream->WriteElementString( BASE_WORD_ELE, tmpWDWord->getWord( nullptr ) );						//�P��
		XmlFStream->WriteElementString( BASE_READ1_ELE, tmpWDWord->getRead1( nullptr ) );					//�ǂݕ��P
		XmlFStream->WriteElementString( BASE_READ2_ELE, tmpWDWord->getRead2( nullptr ) );					//�ǂݕ��Q
		XmlFStream->WriteEndElement();

		//--��{�P��(���̓ǂݕ�) --//
		//�Q�ڈȍ~�̓ǂݕ��̊�{�P���\������
		XmlFStream->WriteStartElement( SUBBASEGRP_NODE );
		for( Int32 i = 1; i < inWordGrp->getReadPatternCnt(); i++ )
		{
			tmpWDSubWord = inWordGrp->getBaseWord( i );

			//��{�P�ꂪ�Ȃ��ǂݕ��͖�������B
			if( tmpWDSubWord == nullptr )
			{
				continue;
			}

			XmlFStream->WriteStartElement( SUBBASE_NODE );															//�x�[�X
			XmlFStream->WriteElementString( SUBBASE_WORD_ELE, tmpWDSubWord->getWord( nullptr ) );						//�P��
			XmlFStream->WriteElementString( SUBBASE_READ1_ELE, tmpWDSubWord->getRead1( nullptr ) );					//�ǂݕ��P
			XmlFStream->WriteElementString( SUBBASE_READ2_ELE, tmpWDSubWord->getRead2( nullptr ) );					//�ǂݕ��Q
			XmlFStream->WriteEndElement();
		}
		XmlFStream->WriteEndElement();
		
		//-- �Ӗ��u���b�N�L�q --//
		XmlFStream->WriteStartElement( MEANS_NODE );														//�Ӗ��u���b�N
	
		for( Int32 i = 0; i < inWordGrp->getMeanCnt(); i++ )
		{
			XmlFStream->WriteStartElement( MEAN_NODE );														//�Ӗ�
			//�Ӗ��擾
			tmpWDMean = inWordGrp->getMean( i );
			if( tmpWDMean == nullptr )
			{
				continue;
			}
			//�Ӗ��ԍ�
			XmlFStream->WriteAttributeString( MEANNO_ELE, tmpWDMean->getMeanNo().ToString() );

			//-- �|��L�q --//
			tmpWDTrans = inWordGrp->getTransNo( tmpWDMean->getMeanNo() );

			if( tmpWDTrans != nullptr )
			{
				//�|��O���[�v�m�[�h
				XmlFStream->WriteStartElement( TRANSES_NODE );									

				for( Int32 j = 0; j < tmpWDTrans->CountTransID(); j++ )
				{
					//�|��m�[�h
					XmlFStream->WriteStartElement( TRANS_NODE );								

					XmlFStream->WriteElementString( TRANSID_ELE,								//�|��ID
						String::Format( L"B.{0}", tmpWDTrans->getTransID( j ).ToString() ) );	
					XmlFStream->WriteElementString( TRANSWORD_ELE,								//�|��P��
						getTransWordA( tmpWDTrans->getTransID( j ) ) );	
				
					//�|��m�[�h�N���[�Y
					XmlFStream->WriteEndElement();												
				}

				//�|��O���[�v�m�[�h�N���[�Y
				XmlFStream->WriteEndElement();													
			}

			//-- �Ӗ��L�q --//
			tmpGroupID = gcnew array<Byte>(WDMEAN_GROUPGTLEN + WDMEAN_GROUPLTLEN);
			tmpGroupIDGt = gcnew array<Byte>(WDMEAN_GROUPGTLEN);
			tmpGroupIDLt = gcnew array<Byte>(WDMEAN_GROUPLTLEN);
			tmpEnc = System::Text::Encoding::ASCII;
			tmpGroupIDStr = gcnew array<Char>(WDMEAN_GROUPGTLEN + WDMEAN_GROUPLTLEN);;

			//���ރm�[�h
			XmlFStream->WriteStartElement( GROUP_NODE );

			for( Int32 i = 0; i < tmpWDMean->MeanGroupCount(); i++ )
			{
				tmpGroupIDGt = tmpWDMean->getGroupGt( i, tmpGroupIDGt );
				tmpGroupIDLt = tmpWDMean->getGroupLt( i, tmpGroupIDLt );
				Array::Copy( tmpGroupIDGt, tmpGroupID, 2 );
				Array::Copy( tmpGroupIDLt, 0, tmpGroupID, 2, 2 );
				tmpGroupIDStr = tmpEnc->GetChars( tmpGroupID );

				WDGroupTreeNode^ tmpWDGroupTreeNode = getGroup( tmpGroupIDGt, tmpGroupIDLt );			//���� 

				if( tmpWDGroupTreeNode != nullptr )
				{
					tmpGroupName = tmpWDGroupTreeNode->getName( nullptr );
				}else{
					tmpGroupName = L"(���ޖ����s���ł�)";
				}

				XmlFStream->WriteStartElement( GROUP_ELE );
				XmlFStream->WriteAttributeString( GROUPID_ELE,  
					String::Format( L"AG.{0} ", gcnew String(tmpGroupIDStr) ) );
				XmlFStream->WriteString( tmpGroupName );
				XmlFStream->WriteEndElement();

				delete tmpGroupIDStr;
				tmpGroupIDStr = nullptr;

			}
			XmlFStream->WriteEndElement();

			XmlFStream->WriteElementString( MSPEECH_ELE,										//�Ӗ��i��			
				getSegment( SegmentListA, SPEECH_ID, tmpWDMean->getSpeech() )->getName( nullptr ) );
			XmlFStream->WriteElementString( MRANK_ELE,											//�����N
				getSegment( SegmentListA, RANK_ID, tmpWDMean->getRank() )->getName( nullptr ) );
			XmlFStream->WriteElementString( MEAN_ELE, tmpWDMean->getMean( nullptr ) );			//�Ӗ�
			XmlFStream->WriteElementString( EXAMPLE_ELE, tmpWDMean->getExample( nullptr ) );	//�ᕶ

			//-- �֘A��L�q --//
			tmpWDRelation = inWordGrp->getRelationNo( tmpWDMean->getMeanNo() );

			if( tmpWDRelation != nullptr )
			{
				//�֘A��O���[�v�m�[�h
				XmlFStream->WriteStartElement( RELATIONS_NODE );								

				for( Int32 j = 0; j < tmpWDRelation->CountRelation(); j++ )
				{
					XmlFStream->WriteStartElement( RELATION_NODE );								//�֘A��m�[�h

					XmlFStream->WriteElementString( RELATIONTYPE_ELE,							//�֘A��^�C�v
						getSegment( SegmentListA, RELATION_ID, tmpWDRelation->getRelationType( j ) )->getName( nullptr ) );	
					XmlFStream->WriteElementString( RELATIONID_ELE,								//�֘A��ID
						String::Format( L"A.{0}", tmpWDRelation->getRelationID( j ).ToString() ) );	
					XmlFStream->WriteElementString( RELATION_ELE,								//�֘A��P��
						getRelationWordA( tmpWDRelation->getRelationID( j ) ) );	
				
					//�|��m�[�h�N���[�Y
					XmlFStream->WriteEndElement();												
				}

				//�|��O���[�v�m�[�h�N���[�Y
				XmlFStream->WriteEndElement();													
			}

			//�Ӗ��N���[�Y
			XmlFStream->WriteEndElement();												
		}

		//�Ӗ��u���b�N�N���[�Y
		XmlFStream->WriteEndElement();													

		//-- ���p�`�L�q --//
		//���p�O���[�v�Z�N�V�����m�[�h		
		XmlFStream->WriteStartElement( PRATICALGRPSEC_ELE );								

		//���p�O���[�v�m�[�h		
		XmlFStream->WriteStartElement( PRATICALGRP_ELE );								

		//�擪�P��擾
		tmpWDWord = inWordGrp->getWord( 0 );
		Int32 tmpReadPattern = tmpWDWord->getReadPattern();

		//���p�^�C�v
		XmlFStream->WriteElementString( PRATICALTYPE_ELE,										//���p�^�C�v
			getSegment( SegmentListA, TYPE_ID, tmpWDWord->getType() )->getName( nullptr ) );
		//���p�`�O���[�v�m�[�h
		XmlFStream->WriteStartElement( PRATICALS_NODE );								


		for( Int32 i = 0; i < inWordGrp->getWordCnt(); i++ )
		{
			
			tmpWDWord = inWordGrp->getWord( i );
			if( tmpWDWord == nullptr )
			{
				continue;
			}
			if( tmpReadPattern != tmpWDWord->getReadPattern() )
			{
				tmpReadPattern = tmpWDWord->getReadPattern();
				//���p�`�O���[�v�m�[�h�N���[�Y
				XmlFStream->WriteEndElement();
				//���p�O���[�v�m�[�h�N���[�Y		
				XmlFStream->WriteEndElement();
				//���p�O���[�v�m�[�h		
				XmlFStream->WriteStartElement( PRATICALGRP_ELE );								
				//���p�^�C�v
				XmlFStream->WriteElementString( PRATICALTYPE_ELE,										//���p�^�C�v
					getSegment( SegmentListA, TYPE_ID, tmpWDWord->getType() )->getName( nullptr ) );
				//���p�`�O���[�v�m�[�h
				XmlFStream->WriteStartElement( PRATICALS_NODE );								
			}

			//���p�`�m�[�h
			XmlFStream->WriteStartElement( PRATICALITEM_NODE );

			//���p�`
			if( oldPractical != tmpWDWord->getPractical() )
			{
				oldPractical = tmpWDWord->getPractical();
				oldGramatical = -1;
				oldSex = -1;	
				oldPlurality = -1;
				tmpPrStr = getSegment( SegmentListA, PRATICAL_ID, oldPractical )->getName( nullptr );
			}
			//�P������
			if( oldPlurality != tmpWDWord->getPlurality() )
			{
				oldPlurality = tmpWDWord->getPlurality();
				oldGramatical = -1;
				oldSex = -1;	
				if( tmpPrStr == nullptr ||
					tmpPrStr->Length == 0 )
				{
					if( tmpPrStr != nullptr ) delete tmpPrStr;
					tmpPrStr = getSegment( SegmentListA, PLURALITY_ID, oldPlurality )->getName( nullptr );
				}else{
					tmpRdStr = getSegment( SegmentListA, PLURALITY_ID, oldPlurality )->getName( nullptr );
					if( tmpRdStr->Length > 0 )
					{
						oldPrStr = tmpPrStr;
						tmpPrStr = String::Format( L"{0}�E{1}", oldPrStr, tmpRdStr ); 
						delete oldPrStr;
					}
					delete oldPrStr;
				}

			}
			//�l��
			if( oldGramatical != tmpWDWord->getGramatical() )
			{
				oldGramatical = tmpWDWord->getGramatical();
				oldSex = -1;	
				if( tmpPrStr == nullptr ||
					tmpPrStr->Length == 0 )
				{
					if( tmpPrStr != nullptr ) delete tmpPrStr;
					tmpPrStr = getSegment( SegmentListA, GRAMATICAL_ID, oldGramatical )->getName( nullptr );
				}else{
					tmpRdStr = getSegment( SegmentListA, GRAMATICAL_ID, oldGramatical )->getName( nullptr ); 
					if( tmpRdStr->Length > 0 )
					{
						oldPrStr = tmpPrStr;
						tmpPrStr = String::Format( L"{0}�E{1}", oldPrStr, tmpRdStr ); 
						delete oldPrStr;
					}
					delete tmpRdStr;
				}
			}
			//��
			if( oldSex != tmpWDWord->getSex() )
			{
				oldSex = tmpWDWord->getSex();
				if( tmpPrStr == nullptr ||
					tmpPrStr->Length == 0 )
				{
					if( tmpPrStr != nullptr ) delete tmpPrStr;
					tmpPrStr = getSegment( SegmentListA, SEX_ID, oldSex )->getName( nullptr );
				}else{
					tmpRdStr = getSegment( SegmentListA, SEX_ID, oldSex )->getName( nullptr );
					if( tmpRdStr->Length > 0 )
					{
						oldPrStr = tmpPrStr;
						tmpPrStr = String::Format( L"{0}�E{1}", oldPrStr, tmpRdStr ); 
						delete oldPrStr;
					}
					delete tmpRdStr;
				}
			}
			//���p�`
			XmlFStream->WriteStartElement( PRATICALTITLE_ELE );
			XmlFStream->WriteAttributeString( PRATICALTYPEID_ELE,									//���p�^�C�vID
										tmpWDWord->getType().ToString() );
			XmlFStream->WriteAttributeString( PRATICALID_ELE,											//���p�`ID
										tmpWDWord->getPractical().ToString() );
			XmlFStream->WriteString( tmpPrStr );
			XmlFStream->WriteEndElement();
			delete tmpPrStr;
			tmpPrStr = nullptr;

			XmlFStream->WriteElementString( PRATICALWORD_ELE, tmpWDWord->getWord( nullptr ) );		//�P��
			XmlFStream->WriteElementString( PRATICALREAD1_ELE, tmpWDWord->getRead1( nullptr ) );	//�ǂݕ��P
			XmlFStream->WriteElementString( PRATICALREAD2_ELE, tmpWDWord->getRead2( nullptr ) );	//�ǂݕ��Q

			//���p�`�N���[�Y
			XmlFStream->WriteEndElement();													
		}
		//���p�`�O���[�v�N���[�Y
		XmlFStream->WriteEndElement();													
		//���p�O���[�v�N���[�Y
		XmlFStream->WriteEndElement();
		//���p�O���[�v�Z�N�V�����N���[�Y
		XmlFStream->WriteEndElement();

		//-- �I������ --//
		//���[�g�N���[�Y
		XmlFStream->WriteEndElement();													
		XmlFStream->Flush();
		XmlFStream->Close();

		//�P��O���[�v��Ǎ��ς݃��X�g�ɒǉ�
		inWordGrp->setXMLFname( XmlFName );
		ReadedWordList->Add( inWordGrp );
		webBrowserBook->Url = gcnew Uri( inWordGrp->getXMLFname() );		

	}catch( Exception^ exp )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�\���f�[�^�쐬���ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31305;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		if( XmlFName != nullptr ) delete XmlFName;
		if( XmlFStream != nullptr ) delete XmlFStream;
		if( tmpGroupName != nullptr ) delete tmpGroupName;
		if( tmpGroupID != nullptr ) delete tmpGroupID;
		if( tmpGroupIDGt != nullptr ) delete tmpGroupIDGt;
		if( tmpGroupIDLt != nullptr ) delete tmpGroupIDLt;
		if( tmpEnc != nullptr ) delete tmpEnc;
		if( tmpGroupIDStr != nullptr ) delete tmpGroupIDStr;
	}

}

//***** �P��O���[�v�\�� ����B
void WordDic::Form1::WordGrpDispB( WDWordGrp^ inWordGrp )
{
	String^			XmlFName;					//XML�t�@�C����
	XmlTextWriter^	XmlFStream;					//XML�t�@�C�����C�^�[
	WDWord^			tmpWDWord;					//�P��f�[�^
	WDWord^			tmpWDSubWord;				//�T�u�P��f�[�^(�ǂ�)
	WDMean^			tmpWDMean;					//�Ӗ��f�[�^
	WDTrans^		tmpWDTrans;					//�|��f�[�^
	WDRelation^		tmpWDRelation;				//�֘A��f�[�^

	String^			tmpGroupName;				//���ޖ�
	array<Byte>^	tmpGroupID;					//����ID
	array<Byte>^	tmpGroupIDGt;				//����ID��
	array<Byte>^	tmpGroupIDLt;				//����ID��
	System::Text::Encoding^ tmpEnc;				//�G���R�[�_
	array<Char>^	tmpGroupIDStr;				//���ޖ�(�o�͗p)

	String^			tmpPrStr;					
	String^			oldPrStr;
	String^			tmpRdStr;

	Int32			oldPractical = -1;			//���p�`
	Int32			oldPlurality = -1;			//�P������
	Int32			oldGramatical = -1;			//�l��
	Int32			oldSex = -1;				//��

	//-- �Ǎ��ς݃f�[�^������΂����\������
	try
	{
		if( inWordGrp->getXMLFname() != nullptr )
		{
				//XML�f�[�^������Ε\�����ďI��
				webBrowserBook->Url = gcnew Uri( inWordGrp->getXMLFname() );		

				return;
		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��f�[�^�\���ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31306;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- �V����XML�t�@�C�����쐬����
	try
	{
		//-- �����ݒ� --//
		XmlFName = getXMLFname();														//�o��XML�t�@�C�����擾

		XmlFStream = gcnew XmlTextWriter( XmlFName, System::Text::Encoding::Unicode );	//�o��XML�t�@�C�����Z�b�g
		XmlFStream->Formatting = Formatting::Indented;									//�C���f���g����
		XmlFStream->QuoteChar = L'\"';													//�N�I�[�^�ݒ�@"
		XmlFStream->WriteStartDocument();												//�h�L�������g�X�^�[�g
		XmlFStream->WriteProcessingInstruction( L"xml-stylesheet",						//XSLT�w��
			String::Format( L"type=\"text/xsl\" href=\"{0}\"", WDConfigParm->XSLTFNameB ) );

		//���[�g�L�q
		XmlFStream->WriteStartElement( WORDS_NODE );									

		//-- ��{�P��L�q --//
		//�P�ڂ̓ǂݕ��̊�{�P���\������
		tmpWDWord = inWordGrp->getBaseWord( 0 );
		if( tmpWDWord == nullptr )
		{
			WordDicException^ tmpWordDicException = gcnew WordDicException( L"�P��f�[�^������܂���B" );
			tmpWordDicException->ErrorCode = 31306;
			tmpWordDicException->ErrorCode2 = 2;
			throw tmpWordDicException;
		}
		XmlFStream->WriteStartElement( BASE_NODE );															//�x�[�X
		XmlFStream->WriteElementString( BASE_WORD_ELE, tmpWDWord->getWord( nullptr ) );						//�P��
		XmlFStream->WriteElementString( BASE_READ1_ELE, tmpWDWord->getRead1( nullptr ) );					//�ǂݕ��P
		XmlFStream->WriteElementString( BASE_READ2_ELE, tmpWDWord->getRead2( nullptr ) );					//�ǂݕ��Q
		XmlFStream->WriteEndElement();

		//--��{�P��(���̓ǂݕ�) --//
		//�Q�ڈȍ~�̓ǂݕ��̊�{�P���\������
		XmlFStream->WriteStartElement( SUBBASEGRP_NODE );
		for( Int32 i = 1; i < inWordGrp->getReadPatternCnt(); i++ )
		{
			tmpWDSubWord = inWordGrp->getBaseWord( i );
			if( tmpWDSubWord == nullptr )
			{
				continue;
			}
			XmlFStream->WriteStartElement( SUBBASE_NODE );															//�x�[�X
			XmlFStream->WriteElementString( SUBBASE_WORD_ELE, tmpWDSubWord->getWord( nullptr ) );						//�P��
			XmlFStream->WriteElementString( SUBBASE_READ1_ELE, tmpWDSubWord->getRead1( nullptr ) );					//�ǂݕ��P
			XmlFStream->WriteElementString( SUBBASE_READ2_ELE, tmpWDSubWord->getRead2( nullptr ) );					//�ǂݕ��Q
			XmlFStream->WriteEndElement();
		}
		XmlFStream->WriteEndElement();

		//-- �Ӗ��u���b�N�L�q --//
		XmlFStream->WriteStartElement( MEANS_NODE );														//�Ӗ��u���b�N
	
		for( Int32 i = 0; i < inWordGrp->getMeanCnt(); i++ )
		{
			XmlFStream->WriteStartElement( MEAN_NODE );														//�Ӗ�
			//�Ӗ��擾
			tmpWDMean = inWordGrp->getMean( i );
			if( tmpWDMean == nullptr )
			{
				continue;
			}

			//�Ӗ��ԍ�
			XmlFStream->WriteAttributeString( MEANNO_ELE, tmpWDMean->getMeanNo().ToString() );

			//-- �|��L�q --//
			tmpWDTrans = inWordGrp->getTransNo( tmpWDMean->getMeanNo() );

			if( tmpWDTrans != nullptr )
			{
				//�|��O���[�v�m�[�h
				XmlFStream->WriteStartElement( TRANSES_NODE );									

				for( Int32 j = 0; j < tmpWDTrans->CountTransID(); j++ )
				{
					//�|��m�[�h
					XmlFStream->WriteStartElement( TRANS_NODE );								

					XmlFStream->WriteElementString( TRANSID_ELE,								//�|��ID
						String::Format( L"A.{0}", tmpWDTrans->getTransID( j ).ToString() ) );	
					XmlFStream->WriteElementString( TRANSWORD_ELE,								//�|��P��
						getTransWordB( tmpWDTrans->getTransID( j ) ) );	
				
					//�|��m�[�h�N���[�Y
					XmlFStream->WriteEndElement();												
				}

				//�|��O���[�v�m�[�h�N���[�Y
				XmlFStream->WriteEndElement();													
			}

			//-- �Ӗ��L�q --//
			tmpGroupID = gcnew array<Byte>(WDMEAN_GROUPGTLEN + WDMEAN_GROUPLTLEN);
			tmpGroupIDGt = gcnew array<Byte>(WDMEAN_GROUPGTLEN);
			tmpGroupIDLt = gcnew array<Byte>(WDMEAN_GROUPLTLEN);
			tmpEnc = System::Text::Encoding::ASCII;
			tmpGroupIDStr = gcnew array<Char>(WDMEAN_GROUPGTLEN + WDMEAN_GROUPLTLEN);;

			//���ރm�[�h
			XmlFStream->WriteStartElement( GROUP_NODE );

			for( Int32 i = 0; i < tmpWDMean->MeanGroupCount(); i++ )
			{
				tmpGroupIDGt = tmpWDMean->getGroupGt( i, tmpGroupIDGt );
				tmpGroupIDLt = tmpWDMean->getGroupLt( i, tmpGroupIDLt );
				Array::Copy( tmpGroupIDGt, tmpGroupID, 2 );
				Array::Copy( tmpGroupIDLt, 0, tmpGroupID, 2, 2 );
				Int32 dummy = tmpEnc->GetCharCount( tmpGroupID,0,4 );
				tmpGroupIDStr = tmpEnc->GetChars( tmpGroupID);

				WDGroupTreeNode^ tmpWDGroupTreeNode = getGroup( tmpGroupIDGt, tmpGroupIDLt );			//���� 

				if( tmpWDGroupTreeNode != nullptr )
				{
					tmpGroupName = tmpWDGroupTreeNode->getName( nullptr );
				}else{
					tmpGroupName = L"(���ޖ����s���ł�)";
				}

				XmlFStream->WriteStartElement( GROUP_ELE );
				XmlFStream->WriteAttributeString( GROUPID_ELE,  
					String::Format( L"BG.{0} ", gcnew String(tmpGroupIDStr) ) );
				XmlFStream->WriteString( tmpGroupName );
				XmlFStream->WriteEndElement();

				delete tmpGroupIDStr;
				tmpGroupIDStr = nullptr;
			}
			XmlFStream->WriteEndElement();

			XmlFStream->WriteElementString( MSPEECH_ELE,										//�Ӗ��i��			
				getSegment( SegmentListB, SPEECH_ID, tmpWDMean->getSpeech() )->getName( nullptr ) );
			XmlFStream->WriteElementString( MRANK_ELE,											//�����N
				getSegment( SegmentListB, RANK_ID, tmpWDMean->getRank() )->getName( nullptr ) );
			XmlFStream->WriteElementString( MEAN_ELE, tmpWDMean->getMean( nullptr ) );			//�Ӗ�
			XmlFStream->WriteElementString( EXAMPLE_ELE, tmpWDMean->getExample( nullptr ) );	//�ᕶ

			//-- �֘A��L�q --//
			tmpWDRelation = inWordGrp->getRelationNo( tmpWDMean->getMeanNo() );

			if( tmpWDRelation != nullptr )
			{
				//�֘A��O���[�v�m�[�h
				XmlFStream->WriteStartElement( RELATIONS_NODE );								

				for( Int32 j = 0; j < tmpWDRelation->CountRelation(); j++ )
				{
					XmlFStream->WriteStartElement( RELATION_NODE );								//�֘A��m�[�h

					XmlFStream->WriteElementString( RELATIONTYPE_ELE,							//�֘A��^�C�v
						getSegment( SegmentListB, RELATION_ID, tmpWDRelation->getRelationType( j ) )->getName( nullptr ) );	
					XmlFStream->WriteElementString( RELATIONID_ELE,								//�֘A��ID
						String::Format( L"B.{0}", tmpWDRelation->getRelationID( j ).ToString() ) );	
					XmlFStream->WriteElementString( RELATION_ELE,								//�֘A��P��
						getRelationWordB( tmpWDRelation->getRelationID( j ) ) );	
				
					//�|��m�[�h�N���[�Y
					XmlFStream->WriteEndElement();												
				}

				//�|��O���[�v�m�[�h�N���[�Y
				XmlFStream->WriteEndElement();													
			}

			//�Ӗ��N���[�Y
			XmlFStream->WriteEndElement();												
		}

		//�Ӗ��u���b�N�N���[�Y
		XmlFStream->WriteEndElement();												

		//-- ���p�`�L�q --//
		//���p�O���[�v�Z�N�V�����m�[�h		
		XmlFStream->WriteStartElement( PRATICALGRPSEC_ELE );								
		//���p�O���[�v�m�[�h		
		XmlFStream->WriteStartElement( PRATICALGRP_ELE );								

		//�擪�P��擾
		tmpWDWord = inWordGrp->getWord( 0 );
		Int32 tmpReadPattern = tmpWDWord->getReadPattern();

		//���p�^�C�v
		XmlFStream->WriteElementString( PRATICALTYPE_ELE,
			getSegment( SegmentListB, TYPE_ID, tmpWDWord->getType() )->getName( nullptr ) );
		//���p�`�O���[�v�m�[�h
		XmlFStream->WriteStartElement( PRATICALS_NODE );								


		for( Int32 i = 0; i < inWordGrp->getWordCnt(); i ++ )
		{
			tmpWDWord = inWordGrp->getWord( i );
			if( tmpWDWord == nullptr )
			{
				continue;
			}

			if( tmpReadPattern != tmpWDWord->getReadPattern() )
			{
				tmpReadPattern = tmpWDWord->getReadPattern();
				//���p�`�O���[�v�m�[�h�N���[�Y
				XmlFStream->WriteEndElement();
				//���p�O���[�v�m�[�h�N���[�Y		
				XmlFStream->WriteEndElement();
				//���p�O���[�v�m�[�h		
				XmlFStream->WriteStartElement( PRATICALGRP_ELE );								
				//���p�^�C�v
				XmlFStream->WriteElementString( PRATICALTYPE_ELE,										//���p�^�C�v
					getSegment( SegmentListA, TYPE_ID, tmpWDWord->getType() )->getName( nullptr ) );
				//���p�`�O���[�v�m�[�h
				XmlFStream->WriteStartElement( PRATICALS_NODE );								
			}


			//���p�`�m�[�h
			XmlFStream->WriteStartElement( PRATICALITEM_NODE );
			
			//���p�`
			if( oldPractical != tmpWDWord->getPractical() )
			{
				oldPractical = tmpWDWord->getPractical();
				oldPlurality = -1;
				oldGramatical = -1;
				oldSex = -1;	
				tmpPrStr = getSegment( SegmentListB, PRATICAL_ID, oldPractical )->getName( nullptr );
			}
			//�P������
			if( oldPlurality != tmpWDWord->getPlurality() )
			{
				oldPlurality = tmpWDWord->getPlurality();
				oldGramatical = -1;
				oldSex = -1;	
				if( tmpPrStr == nullptr || 
					tmpPrStr->Length == 0 )
				{
					if( tmpPrStr != nullptr ) delete tmpPrStr;
					tmpPrStr = getSegment( SegmentListB, PLURALITY_ID, oldPlurality )->getName( nullptr );
				}else{
					tmpRdStr = getSegment( SegmentListB, PLURALITY_ID, oldPlurality )->getName( nullptr );
					if( tmpRdStr->Length > 0 )
					{
						oldPrStr = tmpPrStr;
						tmpPrStr = String::Format( L"{0}�E{1}", oldPrStr, tmpRdStr );
						delete oldPrStr;
					}
					delete tmpRdStr;
				}

			}
			//�l��
			if( oldGramatical != tmpWDWord->getGramatical() )
			{
				oldGramatical = tmpWDWord->getGramatical();
				oldSex = -1;	
				if( tmpPrStr == nullptr || 
					tmpPrStr->Length == 0 )
				{
					if( tmpPrStr != nullptr ) delete tmpPrStr;
					tmpPrStr = getSegment( SegmentListB, GRAMATICAL_ID, oldGramatical )->getName( nullptr );
				}else{
					tmpRdStr = getSegment( SegmentListB, GRAMATICAL_ID, oldGramatical )->getName( nullptr );
					if( tmpRdStr->Length > 0 )
					{
						oldPrStr = tmpPrStr;
						tmpPrStr = String::Format( L"{0}�E{1}", oldPrStr, tmpRdStr );
						delete oldPrStr;
					}
					delete tmpRdStr;
				}

			}
			//��
			if( oldSex != tmpWDWord->getSex() )
			{
				oldSex = tmpWDWord->getSex();
				if( tmpPrStr == nullptr || 
					tmpPrStr->Length == 0 )
				{
					if( tmpPrStr != nullptr ) delete tmpPrStr;
					tmpPrStr = getSegment( SegmentListB, SEX_ID, oldSex )->getName( nullptr );
				}else{
					tmpRdStr = getSegment( SegmentListB, SEX_ID, oldSex )->getName( nullptr );
					if( tmpRdStr->Length > 0 )
					{
						oldPrStr = tmpPrStr;
						tmpPrStr = String::Format( L"{0}�E{1}", oldPrStr, tmpRdStr );
						delete oldPrStr;
					}
					delete tmpRdStr;
				}

			}
			//���p�`
			XmlFStream->WriteStartElement( PRATICALTITLE_ELE );
			XmlFStream->WriteAttributeString( PRATICALTYPEID_ELE,									//���p���@ID
									tmpWDWord->getType().ToString() );
			XmlFStream->WriteAttributeString( PRATICALID_ELE,										//���p�`ID					
									tmpWDWord->getPractical().ToString() );
			XmlFStream->WriteString( tmpPrStr );
			XmlFStream->WriteEndElement();
			delete tmpPrStr;
			tmpPrStr = nullptr;

			XmlFStream->WriteElementString( PRATICALWORD_ELE, tmpWDWord->getWord( nullptr ) );		//�P��
			XmlFStream->WriteElementString( PRATICALREAD1_ELE, tmpWDWord->getRead1( nullptr ) );	//�ǂݕ��P
			XmlFStream->WriteElementString( PRATICALREAD2_ELE, tmpWDWord->getRead2( nullptr ) );	//�ǂݕ��Q

			//���p�`�N���[�Y
			XmlFStream->WriteEndElement();													
		}

		//���p�`�O���[�v�N���[�Y
		XmlFStream->WriteEndElement();													
		//���p�O���[�v�N���[�Y
		XmlFStream->WriteEndElement();
		//���p�O���[�v�Z�N�V�����N���[�Y
		XmlFStream->WriteEndElement();
		
		//-- �I������ --//
		//���[�g�N���[�Y
		XmlFStream->WriteEndElement();													
		XmlFStream->Flush();
		XmlFStream->Close();

		//�P��O���[�v��Ǎ��ς݃��X�g�ɒǉ�
		inWordGrp->setXMLFname( XmlFName );
		ReadedWordList->Add( inWordGrp );
		webBrowserBook->Url = gcnew Uri( inWordGrp->getXMLFname() );		

	}catch( Exception^ exp )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�\���f�[�^�쐬���ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31306;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;

	}finally{
		if( XmlFName != nullptr ) delete XmlFName;
		if( XmlFStream != nullptr ) delete XmlFStream;
		if( tmpGroupName != nullptr ) delete tmpGroupName;
		if( tmpGroupID != nullptr ) delete tmpGroupID;
		if( tmpGroupIDGt != nullptr ) delete tmpGroupIDGt;
		if( tmpGroupIDLt != nullptr ) delete tmpGroupIDLt;
		if( tmpEnc != nullptr ) delete tmpEnc;
		if( tmpGroupIDStr != nullptr ) delete tmpGroupIDStr;
	}

}

//***** ����A������B�̖|��������
String^ WordDic::Form1::getTransWordA( Int32 inWordID )
{
	array<Byte>^	tmpWordID;
	DataRecord^		tmpRecord;
	DataRecord^		tmpOldRecord;
	WDWord^			tmpWord;
	String^ rtString;

	if( inWordID <= 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�|��ID���s���ł��B" );
		tmpWordDicException->ErrorCode = 31307;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- XML�\���ς݂̃��X�g����|����T�� --//
	try
	{
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getWordID() == inWordID && 
				tmpWDWordGrp->getSchLang() == 2 )
			{
				tmpWord = tmpWDWordGrp->getBaseWord();

				if( tmpWord == nullptr )
				{
					tmpWord = tmpWDWordGrp->getWord( 0 );
				}
				
				return tmpWord->getWord( nullptr );
			}

		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�|��ꌟ�����ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31307;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- �V���ɖ|����T�� --//
	try
	{

		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordID, nullptr, 0 );
		tmpRecord = WordFileB->ReadRecord( tmpWordID, 2);
		while( true )
		{
			if( tmpRecord == nullptr )
			{
				rtString =  L"(�|��ꂪ�s���ł��B)";
				break;
			}
		
			tmpWord = gcnew WDWord( tmpRecord );
			if( tmpWord->getBaseFlg() == true )
			{
				break;
			}
			if( tmpRecord->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpRecord->getEachKeyFlg() == IS_EACHKEYLST )
			{
				break;
			}
			tmpOldRecord = tmpRecord;
			tmpRecord = WordFileB->NextRecord( tmpOldRecord );
			delete tmpOldRecord;
			delete tmpWord;
		}

		rtString = tmpWord->getWord( nullptr );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�|��ꌟ�����ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31307;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
		if( tmpWord != nullptr ) delete tmpWord;
		if( tmpRecord != nullptr ) delete tmpRecord;
	}

	return rtString;

}
//***** ����B������A�̖|��������
String^ WordDic::Form1::getTransWordB( Int32 inWordID )
{
	array<Byte>^	tmpWordID;
	DataRecord^		tmpRecord;
	DataRecord^		tmpOldRecord;
	WDWord^			tmpWord;
	String^ rtString;

	if( inWordID <= 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�|��ID���s���ł��B" );
		tmpWordDicException->ErrorCode = 31308;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- XML�\���ς݂̃��X�g����|����T�� --//
	try
	{
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getWordID() == inWordID && 
				tmpWDWordGrp->getSchLang() == 1 )
			{
				tmpWord = tmpWDWordGrp->getBaseWord();

				if( tmpWord == nullptr )
				{
					tmpWord = tmpWDWordGrp->getWord( 0 );
				}
				
				return tmpWord->getWord( nullptr );
			}

		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�|��ꌟ�����ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31308;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- �V���ɖ|����T�� --//
	try
	{
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordID, nullptr, 0 );
		tmpRecord = WordFileA->ReadRecord( tmpWordID, 2);
		while( true )
		{
			if( tmpRecord == nullptr )
			{
				rtString =  L"(�|��ꂪ�s���ł��B)";
				break;
			}
		
			tmpWord = gcnew WDWord( tmpRecord );
			if( tmpWord->getBaseFlg() == true )
			{
				break;
			}
			if( tmpRecord->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpRecord->getEachKeyFlg() == IS_EACHKEYLST )
			{
				break;
			}
			tmpOldRecord = tmpRecord;
			tmpRecord = WordFileA->NextRecord( tmpOldRecord );
			delete tmpOldRecord;
			delete tmpWord;
		}

		rtString = tmpWord->getWord( nullptr );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�|��ꌟ�����ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31308;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;

	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
		if( tmpWord != nullptr ) delete tmpWord;
		if( tmpRecord != nullptr ) delete tmpRecord;
	}

	return rtString;

}

//***** ����A�̊֘A�ꌟ��
String^ WordDic::Form1::getRelationWordA( Int32 inWordID )
{
	array<Byte>^	tmpWordID;
	DataRecord^		tmpRecord;
	DataRecord^		tmpOldRecord;
	WDWord^			tmpWord;
	String^ rtString;

	if( inWordID <= 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�֘A��ID���s���ł��B" );
		tmpWordDicException->ErrorCode = 31309;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- XML�\���ς݂̃��X�g����֘A���T�� --//
	try
	{
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getWordID() == inWordID && 
				tmpWDWordGrp->getSchLang() == 1 )
			{
				tmpWord = tmpWDWordGrp->getBaseWord();

				if( tmpWord == nullptr )
				{
					tmpWord = tmpWDWordGrp->getWord( 0 );
				}
				
				return tmpWord->getWord( nullptr );
			}

		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�֘A�ꌟ�����ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31309;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- �����P�ꃊ�X�g����֘A���T�� --//
	try
	{
		for( Int32 i = 0; i < listBoxWordList->Items->Count; i++ )
		{
			WDWordGrp^ tmpWDWordGrp = safe_cast<WDWordGrp^>( listBoxWordList->Items[i]);
			if( tmpWDWordGrp->getWordID() == inWordID &&
				tmpWDWordGrp->getSchLang() == 1 )
			{
				tmpWord = tmpWDWordGrp->getBaseWord();

				if( tmpWord == nullptr )
				{
					tmpWord = tmpWDWordGrp->getWord( 0 );
				}
				
				return tmpWord->getWord( nullptr );
			}
		}
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�֘A�ꌟ�����ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31309;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}

	//-- �V���ɒP���Ǎ��� --//
	try
	{
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordID, nullptr, 0 );
		tmpRecord = WordFileA->ReadRecord( tmpWordID, 2);
		while( true )
		{
			if( tmpRecord == nullptr )
			{
				return L"(�֘A�ꂪ�s���ł��B)";
				break;
			}
		
			tmpWord = gcnew WDWord( tmpRecord );
			if( tmpWord->getBaseFlg() == true )
			{
				break;
			}
			if( tmpRecord->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpRecord->getEachKeyFlg() == IS_EACHKEYLST )
			{
				break;
			}
			tmpOldRecord = tmpRecord;
			tmpRecord = WordFileA->NextRecord( tmpOldRecord );
			delete tmpOldRecord;
			delete tmpWord;
		}

		rtString = tmpWord->getWord( nullptr );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L" �֘A�ꌟ�����ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31309;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;

	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
		if( tmpWord != nullptr ) delete tmpWord;
		if( tmpRecord != nullptr ) delete tmpRecord;
	}

	return rtString;

}
//***** ����B�̊֘A�ꌟ��
String^ WordDic::Form1::getRelationWordB( Int32 inWordID )
{
	array<Byte>^	tmpWordID;
	DataRecord^		tmpRecord;
	DataRecord^		tmpOldRecord;
	WDWord^			tmpWord;
	String^			rtString;

	if( inWordID <= 0 )
	{
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�֘A��ID���s���ł��B" );
		tmpWordDicException->ErrorCode = 31310;
		tmpWordDicException->ErrorCode2 = 1;
		throw tmpWordDicException;
	}

	//-- XML�\���ς݂̃��X�g����֘A���T�� --//
	try
	{
		for each( WDWordGrp^ tmpWDWordGrp in ReadedWordList )
		{
			if( tmpWDWordGrp->getWordID() == inWordID && 
				tmpWDWordGrp->getSchLang() == 2 )
			{
				tmpWord = tmpWDWordGrp->getBaseWord();

				if( tmpWord == nullptr )
				{
					tmpWord = tmpWDWordGrp->getWord( 0 );
				}
				
				return tmpWord->getWord( nullptr );
			}

		}

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�֘A�ꌟ�����ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31310;
		tmpWordDicException->ErrorCode2 = 2;
		throw tmpWordDicException;
	}

	//-- �����P�ꃊ�X�g����֘A���T�� --//
	try
	{
		for( Int32 i = 0; i < listBoxWordList->Items->Count; i++ )
		{
			WDWordGrp^ tmpWDWordGrp = safe_cast<WDWordGrp^>( listBoxWordList->Items[i]);
			if( tmpWDWordGrp->getWordID() == inWordID &&
				tmpWDWordGrp->getSchLang() == 2 )
			{
				tmpWord = tmpWDWordGrp->getBaseWord();

				if( tmpWord == nullptr )
				{
					tmpWord = tmpWDWordGrp->getWord( 0 );
				}
				
				return tmpWord->getWord( nullptr );
			}
		}
	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L"�֘A�ꌟ�����ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31310;
		tmpWordDicException->ErrorCode2 = 3;
		throw tmpWordDicException;
	}

	//-- �V���Ɋ֘A���T�� --//
	try
	{
		tmpWordID = FJIsam::FJIFuncs::Int32ToArray( inWordID, nullptr, 0 );
		tmpRecord = WordFileB->ReadRecord( tmpWordID, 2);
		while( true )
		{
			if( tmpRecord == nullptr )
			{
				rtString =  L"(�֘A�ꂪ�s���ł��B)";
				break;
			}
		
			tmpWord = gcnew WDWord( tmpRecord );
			if( tmpWord->getBaseFlg() == true )
			{
				break;
			}
			if( tmpRecord->getEachKeyFlg() == IS_NOEACHKEY ||
				tmpRecord->getEachKeyFlg() == IS_EACHKEYLST )
			{
				break;
			}
			tmpOldRecord = tmpRecord;
			tmpRecord = WordFileB->NextRecord( tmpOldRecord );
			delete tmpOldRecord;
			delete tmpWord;
		}

		rtString = tmpWord->getWord( nullptr );

	}catch( Exception^ exp ){
		WordDicException^ tmpWordDicException = gcnew WordDicException( L" �֘A�ꌟ�����ɃG���[���������܂����B", exp );
		tmpWordDicException->ErrorCode = 31310;
		tmpWordDicException->ErrorCode2 = 4;
		throw tmpWordDicException;

	}finally{
		if( tmpWordID != nullptr ) delete tmpWordID;
		if( tmpWord != nullptr ) delete tmpWord;
		if( tmpRecord != nullptr ) delete tmpRecord;
	}

	return rtString;
}
