//------------------------------------------------------------------------------
//	���Ƃ΂̎��T�@���Ƃ΂̎��T�r���[�A�A�v���P�[�V�����@�w�b�_
//	Version 1.0.0.0	create date 2006/05/08
//	Version 1.0.1.1	create date 1010/10/22	getBaseWord( void ) ���������ǂݕ��̊�{�P���Ԃ��悤�ύX
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDWordGrp : ���T�P����
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
#include "WDWordGrp.h"			//�P��f�[�^�p����

using namespace WDDatas;

//------------------------------------------------------------------------------
//�@�R���X�g���N�^
//------------------------------------------------------------------------------
WordDic::WDWordGrp::WDWordGrp( Int32 inLang, Int32 inDispNum, Int32 inSubDispNum )
{
	//-- ������ --//
	WordLst = gcnew List<WDWord^>();
	MeanLst = gcnew List<WDMean^>();
	TransLst = gcnew List<WDTrans^>();
	RelationLst = gcnew List<WDRelation^>();
	BaseWordLst = gcnew List<WDWord^>();

	SchWord = nullptr;
	WordID = -1;
	SchGroupRank = 0;
	DispNum = 0;
	SubDispNum = 0;

	//-- ���X�g���ёւ��N���X��` --//
	if( WDWordComp == nullptr ) WDWordComp = gcnew WDWordComparer();
	if( WDMeanComp == nullptr ) WDMeanComp = gcnew WDMeanComparer();
	if( WDTransComp == nullptr ) WDTransComp = gcnew WDTransComparer();
	if( WDRelationComp == nullptr ) WDRelationComp = gcnew WDRelationComparer();
	
	//-- ��������ݒ� --//
	if( inLang != 1 && inLang != 2 )
	{
		SchLang = 1;
	}else{
		SchLang = inLang;
	}

	//-- �P�ꃊ�X�g�\�����@�ݒ� --//
	setWordListDisp( inDispNum, inSubDispNum );
	
}

//------------------------------------------------------------------------------
//�@�f�X�g���N�^
//------------------------------------------------------------------------------
WordDic::WDWordGrp::~WDWordGrp( void )
{	
	for each( WDWord^ tmpWord in WordLst )
	{
		if( tmpWord != nullptr ) delete tmpWord;
	}
	delete WordLst;

	for each( WDMean^ tmpMean in MeanLst )
	{
		if( tmpMean != nullptr ) delete tmpMean;
	}
	delete MeanLst;

	for each( WDTrans^ tmpTrans in TransLst )
	{
		if( tmpTrans != nullptr ) delete tmpTrans;
	}
	delete TransLst;

	for each( WDRelation^ tmpRelation in RelationLst )
	{
		if( tmpRelation != nullptr ) delete tmpRelation;
	}
	delete RelationLst;

}

//------------------------------------------------------------------------------
//�@�A�C�e���Q��
//------------------------------------------------------------------------------
//***** �P��擾
WDWord^ WordDic::WDWordGrp::getWord( Int32 idx )
{
	//-- �����`�F�b�N --//
	if( idx < 0 ||
		idx > WordLst->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 21001;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}

	//-- �l�ԋp --//
	return WordLst[idx];
}

//***** ��{�P��擾
WDWord^ WordDic::WDWordGrp::getBaseWord( void )
{
	//-- ��{�P�ꂪ�Z�b�g����Ă���ꍇ --//
	// ���������ǂݕ��Ɠ����ǂݕ��̊�{�P���Ԃ��B
	if( BaseWordLst->Count > 0 )
	{
		//���������ǂݕ��Ɠ����ǂݕ����`�F�b�N
		for each( WDWord^ tmpWord in BaseWordLst )
		{
			if( tmpWord->getReadPattern() == SchReadPattern )
			{
				return tmpWord;
			}
		}
		//�����ǂݕ����Ȃ��ꍇ�Anull��Ԃ��B
		return nullptr;

	//-- ��{�P�ꂪ�Ȃ��ꍇ�́Anull��Ԃ��B
	}else{
		return nullptr;
	}
}

//***** ��{�P��擾( �ǂݕ��Ō��� )
WDWord^ WordDic::WDWordGrp::getBaseWord( Int32 inReadPattern )
{
	//-- �l�ԋp --//
	for each( WDWord^ tmpWord in BaseWordLst )
	{
		if( tmpWord->getReadPattern() == inReadPattern )
		{
			return tmpWord;
		}
	}
	return nullptr;
}

//***** �����P��擾
WDWord^	WordDic::WDWordGrp::getSchWord( void )
{
	//-- �P��Ō������Ă��Ȃ����nullptr��Ԃ� --//
	if( SchMethod != 1 )
	{
		return nullptr;
	}

	//-- �l�ԋp --//
	return SchWord;
}

//***** �Ӗ��擾
WDMean^ WordDic::WDWordGrp::getMean( Int32 idx )
{
	//-- �����`�F�b�N --//
	if( idx < 0 ||
		idx > MeanLst->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 21002;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}

	//-- �l�ԋp --//
	return MeanLst[idx];
}

WDMean^	WordDic::WDWordGrp::getSchMean( void )
{
	//-- �Ӗ�(����)�Ō������Ă��Ȃ����nullptr��Ԃ� --//
	if( SchMethod != 2 )
	{
		return nullptr;
	}

	//-- �l�ԋp --//
	return SchMean;
}
//***** �|��擾
WDTrans^ WordDic::WDWordGrp::getTrans( Int32 idx )
{
	//-- �����`�F�b�N --//
	if( idx < 0 ||
		idx > TransLst->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 21003;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}

	//-- �l�ԋp --//
	return TransLst[idx];
}

//***** �|���擾(�Ӗ�No�ɂ��)
WDTrans^ WordDic::WDWordGrp::getTransNo( Int32 inNo )
{
	//-- �����`�F�b�N --//
	if( inNo <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ�No�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 21010;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	
	//-- �f�[�^���� --//
	for( Int32 i = 0; i < TransLst->Count; i++ )
	{
		if( TransLst[i]->getMeanNo() == inNo )
		{
			return TransLst[i];
		}
	}

	//-- �l�ԋp --//
	return nullptr;
}

//***** �֘A��擾
WDRelation^ WordDic::WDWordGrp::getRelation( Int32 idx )
{
	//-- �����`�F�b�N --//
	if( idx < 0 ||
		idx > RelationLst->Count )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�C���f�b�N�X�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 21004;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}

	//-- �l�ԋp --//
	return RelationLst[idx];
}

//***** �֘A��擾(�Ӗ�No�ɂ��)
WDRelation^ WordDic::WDWordGrp::getRelationNo( Int32 inNo )
{
	//-- �����`�F�b�N --//
	if( inNo <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ�No�̎w�肪�s���ł��B" );
		tmpWDDataException->ErrorCode  = 21011;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;

	}
	
	//-- �f�[�^���� --//
	for( Int32 i = 0; i < RelationLst->Count; i++ )
	{
		if( RelationLst[i]->getMeanNo() == inNo )
		{
			return RelationLst[i];
		}
	}

	//-- �l�ԋp --//
	return nullptr;
}

//***** XML�t�@�C�����擾
String^ WordDic::WDWordGrp::getXMLFname( void )
{
	if( XMLFname == nullptr )
	{
		return nullptr;
	}
	return String::Copy( XMLFname );
}
						
//***** �P��ID�擾
Int32 WordDic::WDWordGrp::getWordID( void )
{
	//-- �l�ԋp --//
	return WordID;
}

//***** �P�ꐔ�擾
Int32 WordDic::WDWordGrp::getWordCnt( void )
{
	//-- �l�ԋp --//
	return WordLst->Count;
}

//***** �Ӗ����擾
Int32 WordDic::WDWordGrp::getMeanCnt( void )
{
	//-- �l�ԋp --//
	return MeanLst->Count;
}

//***** �|�󐔎擾
Int32 WordDic::WDWordGrp::getTransCnt( void )
{
	//-- �l�ԋp --//
	return TransLst->Count;
}
		
//***** �֘A�ꐔ�擾
Int32 WordDic::WDWordGrp::getRelationCnt( void )
{
	//-- �l�ԋp --//
	return RelationLst->Count;
}

//***** �������@�擾
Int32 WordDic::WDWordGrp::getSchMethod( void )
{
	//-- �l�ԋp --//
	return SchMethod;
}

//***** ��������擾
Int32 WordDic::WDWordGrp::getSchLang( void )
{
	//-- �l�ԋp --//
	return SchLang;
}

//***** ToString�ł̕\�����@�ݒ�
Int32 WordDic::WDWordGrp::getWordListDisp( void )
{
	return	DispNum;
}

//***** �����Ӗ����ޏ���
Int32 WordDic::WDWordGrp::getSchGroupRank( void )
{
	return SchGroupRank;
}

//***** �ǂݕ����擾
Int32 WordDic::WDWordGrp::getReadPatternCnt( void )
{
	return BaseWordLst->Count;
}

//------------------------------------------------------------------------------
//�@�A�C�e���ǉ�
//------------------------------------------------------------------------------
//***** �P��ǉ�
void WordDic::WDWordGrp::addWord( WDWord^ inWord, Boolean inSch )
{
	//-- �����`�F�b�N --//
	if( inWord == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�P��f�[�^�����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 21005;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	if( WordID != -1 &&
		WordID != inWord->getWordID() )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�قȂ�P��͒ǉ��ł��܂���B" );
		tmpWDDataException->ErrorCode  = 21005;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	if( inSch == true && SchMethod != 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���Ɍ������@���ݒ肳��Ă��܂��B" );
		tmpWDDataException->ErrorCode  = 21005;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//-- �P��Z�b�g --//
	//����f�[�^�Ȃ�ǉ������ɏI��
	for each( WDWord^ tmpWord in WordLst )
	{
		if( WDWordComp->Compare( tmpWord, inWord ) == 0 )
		{
			return;
		}
	}

	//�����P��ɐݒ�
	if( inSch == true )
	{
		SchMethod = 1;
		SchWord = inWord;
		SchReadPattern = inWord->getReadPattern();
	}

	//�P���{�`�ɐݒ�
	if( inWord->getBaseFlg() == true )
	{
		BaseWordLst->Add( inWord );

		//��{�P�ꃊ�X�g�\�[�g
		if( BaseWordLst->Count > 1 )
		{
			BaseWordLst->Sort( WDWordComp );
		}
	}

	//�P��ID�ݒ�
	if( WordID == -1 )
	{
		WordID = inWord->getWordID();
	}

	//�P�ꃊ�X�g�ɐݒ�
	WordLst->Add( inWord );

	//�P�ꃊ�X�g�\�[�g
	if( WordLst->Count >1 )
	{
		WordLst->Sort( WDWordComp );
	}
}

//***** �Ӗ��ǉ�
void WordDic::WDWordGrp::addMean( WDMean^ inMean, Boolean inSch, Int32 inMeanFlg )
{
	Boolean addFlg;

	//-- �����`�F�b�N --//
	if( inMean== nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ��f�[�^�����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 21006;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	if( WordID != -1 &&
		WordID != inMean->getWordID() )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�قȂ�P��̈Ӗ��͒ǉ��ł��܂���B" );
		tmpWDDataException->ErrorCode  = 21006;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	if( inSch == true && SchMethod != 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���Ɍ������@���ݒ肳��Ă��܂��B" );
		tmpWDDataException->ErrorCode  = 21006;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//�����Ӗ��ɐݒ�
	if( inSch == true )
	{
		SchMethod = 2;
		SchMean = inMean;

		for( Int32 i = 0; i < inMean->MeanGroupCount(); i++ )
		{
			WDMeanGroup^ tmpWDMeanGroup = inMean->getGroup( i );
			if( tmpWDMeanGroup == nullptr )
			{
				WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
					L"���ޏ�񂪑��݂��܂���B" );
				tmpWDDataException->ErrorCode  = 21006;
				tmpWDDataException->ErrorCode2 = 4;
				throw tmpWDDataException;
			}
			if( tmpWDMeanGroup->MeanFlg == inMeanFlg )
			{
				SchGroupRank = tmpWDMeanGroup->GroupRank;
			}
		}
	}

	//�P��ID�ݒ�
	if( WordID == -1 )
	{
		WordID = inMean->getWordID();
	}
		
	//�Ӗ����X�g�ɐݒ�
	try
	{
		addFlg = false;
		for each( WDMean^ tmpWDMean in MeanLst )
		{
			if( tmpWDMean->getWordID() == inMean->getWordID() &&
				tmpWDMean->getMeanNo() == inMean->getMeanNo() )
			{
				addFlg = true;
				tmpWDMean->MergeMean( inMean );
			}
		}
		if( addFlg == false )
		{
			MeanLst->Add( inMean );
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�Ӗ��ǉ����ɃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 21006;
		tmpWDDataException->ErrorCode2 = 5;
		throw tmpWDDataException;
	}

	//�Ӗ����X�g�\�[�g
	if( addFlg == false &&
		MeanLst->Count >1 )
	{
		MeanLst->Sort( WDMeanComp );
	}
}

//***** �|��ǉ�
void WordDic::WDWordGrp::addTrans( WDTrans^ inTrans )
{
	//-- �����`�F�b�N --//
	if( inTrans== nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�|��f�[�^�����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 21007;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	if( WordID != inTrans->getWordID() )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�قȂ�P��̖|��͒ǉ��ł��܂���B" );
		tmpWDDataException->ErrorCode  = 21007;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �|��Z�b�g --//
	//����f�[�^�Ȃ�ǉ������ɏI��
	for each( WDTrans^ tmpTrans in TransLst )
	{
		if( WDTransComp->Compare( tmpTrans, inTrans ) == 0 )
		{
			return;
		}
	}

	//�|�󃊃X�g�ɐݒ�
	TransLst->Add( inTrans );

	//�|�󃊃X�g�\�[�g
	if( TransLst->Count >1 )
	{
		TransLst->Sort( WDTransComp );
	}
}

//***** �֘A��ǉ�
void WordDic::WDWordGrp::addRelation( WDRelation^ inRelation )
{
	//-- �����`�F�b�N --//
	if( inRelation== nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�֘A��f�[�^�����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 21008;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	if( WordID != inRelation->getWordID() )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�قȂ�P��̊֘A��͒ǉ��ł��܂���B" );
		tmpWDDataException->ErrorCode  = 21008;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �֘A��Z�b�g --//
	//����f�[�^�Ȃ�ǉ������ɏI��
	for each( WDRelation^ tmpRelation in RelationLst )
	{
		if( WDRelationComp->Compare( tmpRelation, inRelation ) == 0 )
		{
			return;
		}
	}

	//�֘A�ꃊ�X�g�ɐݒ�
	RelationLst->Add( inRelation );

	//�֘A�ꃊ�X�g�\�[�g
	if( RelationLst->Count >1 )
	{
		RelationLst->Sort( WDRelationComp );
	}
}

//***** �P����XML�t�@�C����
void WordDic::WDWordGrp::setXMLFname( String^ inXMLFname )
{
	//-- �����`�F�b�N --//
	if( inXMLFname == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"XML�t�@�C���������ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 21009;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- XML�t�@�C�����ݒ� --//
	XMLFname = String::Copy( inXMLFname );
}

//***** ToString�ł̕\�����@�ݒ�
void WordDic::WDWordGrp::setWordListDisp( Int32 inDispNum, Int32 inSubDispNum )
{
	//�\��
	if( inDispNum > 0 )
	{

		if( inDispNum < 1 && inDispNum > 3 )
		{
			DispNum = 1;
		}else{
			DispNum = inDispNum;
		}
	}

	//�T�u�\��
	if( inSubDispNum > -1 )
	{
		if( inSubDispNum < 0 && inSubDispNum > 3 )
		{
			SubDispNum = 0;
		}else{
			SubDispNum = inSubDispNum;
		}
	}

}

//------------------------------------------------------------------------------
//�@���X�g�{�b�N�X�p
//------------------------------------------------------------------------------
//***** ������擾
String^ WordDic::WDWordGrp::ToString( void  )
{
	WDWord^ dispWord;
	String^ tmpString;
	String^ tmpSubString;
	String^ rtString;

	//-- �\������P���I�� --//
	if( BaseWordLst->Count > 0 )
	{
		for each( WDWord^ tmpWord in BaseWordLst )
		{
			if( tmpWord->getReadPattern() == SchReadPattern )
			{
				dispWord = tmpWord;
				break;
			}
		}
		if( dispWord == nullptr )
		{
			return L"(�P�ꂪ����܂���)";
		}

	}else{
		return L"(�P�ꂪ����܂���)";
	}
	
	//-- �\���f�[�^�ݒ�
	switch( DispNum )
	{
	//�P��
	case 1:
		tmpString = dispWord->getWord( nullptr );
		break;
	//�ǂݕ��P
	case 2:
		tmpString = dispWord->getRead1( nullptr );
		break;
	//�ǂݕ��Q
	case 3:
		tmpString = dispWord->getRead2( nullptr );
		break;
	//����ȊO�i�P��j
	default :
		tmpString = dispWord->getWord( nullptr );
	}
	//--�T�u�\�����Ȃ��ꍇ
	if( SubDispNum == 0 )
	{
		return tmpString;
	}

	//--�T�u�\��������ꍇ
	switch( SubDispNum )
	{
	//�P��
	case 1:
		tmpSubString = dispWord->getWord( nullptr );
		break;
	//�ǂݕ��P
	case 2:
		tmpSubString = dispWord->getRead1( nullptr );
		break;
	//�ǂݕ��Q
	case 3:
		tmpSubString = dispWord->getRead2( nullptr );
		break;
	//����ȊO�i�P��j
	default :
		tmpSubString = dispWord->getWord( nullptr );
	}

	rtString = String::Format( L"{0} �y{1}�z", tmpString, tmpSubString );
	delete tmpString;
	delete tmpSubString;

	//--�����Ԃ�--//
	return rtString;
}
