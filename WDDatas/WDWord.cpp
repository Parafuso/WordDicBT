//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�f�[�^�N���X�@�\�[�X
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDWord		: �P��N���X
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"	//�P�ꎫ�T�f�[�^�p��O�N���X
#include "WDDatas.h"			//�P�ꎫ�T�f�[�^�N���X
#include "WDDatasDef.h"			//�P�ꎫ�T�f�[�^�萔��`
//#include "FJIsamDef.h"			//ISAM�p��`�t�@�C��

using namespace WDDatas;
using namespace FJIsam;

//------------------------------------------------------------------------------
//  class	:WDWord	: �P��N���X
//------------------------------------------------------------------------------
//***** �R���X�g���N�^�P(�V�K�f�[�^)
WDDatas::WDWord::WDWord()
 //: WDRec()
{
	//-- �ϐ���` --//
	ReadPattern = 0;
	BaseFlg = false;
	Practical = 0;
	Gramatical = 0;
	Plurality = 0;
	Sex = 0;
	Type = 0;

}

//***** �R���X�g���N�^�Q(�Ǎ��f�[�^)
WDDatas::WDWord::WDWord( DataRecord^ inRec )
{

	if(inRec == nullptr )
	{
		//-- �ϐ���` --//
		ReadPattern = 0;
		BaseFlg = false;
		Practical = 0;
		Gramatical = 0;
		Plurality = 0;
		Sex = 0;
		Type = 0;
		return;
	}

	//-- �����`�F�b�N --//
	if( inRec->getDataLength() != WDWORD_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h���P��f�[�^�ł͂���܂���B" );
		tmpWDDataException->ErrorCode  = 10101;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	
	//-- �f�[�^�ݒ� --//
	try
	{
		setRecord( inRec );
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�ݒ�ŃG���[���������܂����B", exp );
		tmpWDDataException->ErrorCode  = 10101;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}
}

//------------------------------------------------------------------------------
//***** �f�X�g���N�^
WDDatas::WDWord::~WDWord()
{
	if( Word != nullptr ) delete Word;
	if( Read1 != nullptr ) delete Read1;
	if( Read2 != nullptr ) delete Read2;
}

//------------------------------------------------------------------------------
//�@�f�[�^���R�[�h����
//------------------------------------------------------------------------------
//***** �f�[�^���R�[�h�擾
DataRecord^ WDDatas::WDWord::getRecord( void )
{
	DataRecord^ tmpRec;
	array<Byte>^ tmpDat;

	if( WDRec::getRecord() == nullptr )
	{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = gcnew DataRecord();
			tmpRec->setData( tmpDat, WDWORD_LENGTH );
			WDRec::setRecord( tmpRec );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^���R�[�h�擾�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10102;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}
	}else{
		try
		{
			tmpDat = getData( nullptr);
			tmpRec = WDRec::getRecord();
			tmpRec->setData( tmpDat, WDWORD_LENGTH );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^���R�[�h�擾�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10102;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}

	delete tmpDat;

	//-- ����I�� --//
	return tmpRec;
}

//***** �f�[�^���R�[�h�ݒ�
void WDDatas::WDWord::setRecord(  DataRecord^ inRec )
{
	if( inRec != nullptr )
	{
		try
		{
			array<Byte>^ tmpDat;
			tmpDat = inRec->getData( nullptr );
			setData( tmpDat );
			delete tmpDat;
			WDRec::setRecord( inRec );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^���R�[�h�ݒ�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10103;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}
	}else{
		try
		{
			WDRec::setRecord( nullptr );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"�f�[�^���R�[�h�ݒ�ŃG���[���������܂����B", exp );
			tmpWDDataException->ErrorCode  = 10103;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}
}

//***** �f�[�^���R�[�h����
void WDDatas::WDWord::Write( void )
{
	FIsam^ tmpParent;

	//-- �f�[�^���R�[�h�`�F�b�N --//
	if( WDRec::getRecord() == nullptr )
	{
		return;
	}

	//-- ISAM�t�@�C���`�F�b�N --//
	try
	{
		tmpParent = safe_cast<FIsam^>( WDRec::getRecord()->getParentFile() );
		if( tmpParent == nullptr )
		{
			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAM�t�@�C�����s���ł��B", exp );
		tmpWDDataException->ErrorCode  = 10104;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- ���R�[�h����(�����Œǉ��A�X�V���f) --//
	try
	{
		if( WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_NEW )
		{
			tmpParent->AddRecord( getRecord() );
		}else if( WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_OLD ){
			tmpParent->UpdateRecord( getRecord() );
		}else{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"���R�[�h�폜�͂ł��܂���B" );
			tmpWDDataException->ErrorCode  = 10104;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10104;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}

//***** �f�[�^���R�[�h����
void WDDatas::WDWord::Delete( void )
{
	FIsam^ tmpParent;

	//-- �f�[�^���R�[�h�`�F�b�N --//
	if( WDRec::getRecord() == nullptr )
	{
		//--�@�f�[�^�N���A --//
		if( Word != nullptr )
		{
			delete Word;
			Word = nullptr;
		}
		if( Read1 != nullptr )
		{
			delete Read1;
			Read1 = nullptr;
		}
		if( Read2 != nullptr )
		{
			delete Read2;
			Read2 = nullptr;
		}

		ReadPattern = 0;
		BaseFlg = false;
		Practical = 0;
		Gramatical = 0;
		Plurality = 0;
		Sex = 0;
		Type = 0;

		return;
	}

	//-- ISAM�t�@�C���`�F�b�N --//
	try
	{
		tmpParent = safe_cast<FIsam^>( WDRec::getRecord()->getParentFile() );
		if( tmpParent == nullptr )
		{
			//--�@�f�[�^�N���A --//
			if( Word != nullptr )
			{
				delete Word;
				Word = nullptr;
			}
			if( Read1 != nullptr )
			{
				delete Read1;
				Read1 = nullptr;
			}
			if( Read2 != nullptr )
			{
				delete Read2;
				Read2 = nullptr;
			}

			ReadPattern = 0;
			BaseFlg = false;
			Practical = 0;
			Gramatical = 0;
			Plurality = 0;
			Sex = 0;
			Type = 0;

			return;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ISAM�t�@�C�����s���ł��B", exp );
		tmpWDDataException->ErrorCode  = 10105;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- ���R�[�h�폜 --//
	try
	{
		if( WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_NEW )
		{
			;
		}else if( WDRec::getRecord()->getRecStat() == DataRecStat_EN::REC_OLD ){
			tmpParent->DeleteRecord( getRecord() );
		}else{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"���R�[�h�폜�͂ł��܂���B" );
			tmpWDDataException->ErrorCode  = 10105;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^���R�[�h�̏����Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10105;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//--�@�f�[�^�N���A --//
	if( Word != nullptr )
	{
		delete Word;
		Word = nullptr;
	}
	if( Read1 != nullptr )
	{
		delete Read1;
		Read1 = nullptr;
	}
	if( Read2 != nullptr )
	{
		delete Read2;
		Read2 = nullptr;
	}

	ReadPattern = 0;
	BaseFlg = false;
	Practical = 0;
	Gramatical = 0;
	Plurality = 0;
	Sex = 0;
	Type = 0;

}
//------------------------------------------------------------------------------
//�@��񑀍�
//------------------------------------------------------------------------------
//***** �f�[�^���擾
Int32 WDDatas::WDWord::Length()
{
	return WDWORD_LENGTH;
}

//***** �f�[�^���R�[�h���擾
Int32 WDDatas::WDWord::RecLength()
{
	return DataRecord::getHeaderLength() + WDWORD_LENGTH;
}

//------------------------------------------------------------------------------
//�@�A�C�e������
//------------------------------------------------------------------------------
//***** �P��擾
String^ WDDatas::WDWord::getWord( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert( 0, Word );
		return inData;
	}else{
		if( Word->Length > 0 )
		{
			return Word->Trim('\0');
		}else{
			return gcnew String( L"" );
		}
	}
}

//***** �ǂ�1�擾
String^ WDDatas::WDWord::getRead1( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert( 0, Read1 );
		return inData;
	}else{
		if( Read1->Length > 0 )
		{
			return Read1->Trim('\0');
		}else{
			return gcnew String( L"" );
		}
	}

}								
//***** �ǂ�2�擾
String^ WDDatas::WDWord::getRead2( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert( 0, Read2 );
		return inData;
	}else{
		if( Read2->Length > 0 )
		{
			return Read2->Trim('\0');
		}else{
			return gcnew String( L"" );
		}
	}

}	

//***** �P��ID�擾
Int32	WDDatas::WDWord::getWordID( void )
{
	return WordID;
}

//***** �ǂݕ��擾
Byte	WDDatas::WDWord::getReadPattern( void )
{
	return ReadPattern;
}

//***** ��{�t���O�擾
Boolean	WDDatas::WDWord::getBaseFlg( void )
{
	return BaseFlg;

}

//***** ���p�`�擾
Byte	WDDatas::WDWord::getPractical( void )
{
	return Practical;
}

//***** �l�̎擾
Byte	WDDatas::WDWord::getGramatical( void )
{
	return Gramatical;
}

//***** �P�������擾
Byte	WDDatas::WDWord::getPlurality( void )
{
	return Plurality;
}

//***** ���擾
Byte	WDDatas::WDWord::getSex( void )
{
	return Sex;
}

//***** ���p�^�C�v�擾
Int32	WDDatas::WDWord::getType( void )
{
	return Type;
}


//------------------------------------------------------------------------------
//***** �P��ݒ�
void WDDatas::WDWord::setWord( String^ inData )
{
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�P�ꂪ���ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10106;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDWORD_WORDLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�P�ꂪ�������܂��B" );
		tmpWDDataException->ErrorCode  = 10106;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		if( Word != nullptr ) delete Word;
		Word = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�P��̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10106;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** �ǂ�1�ݒ�
void WDDatas::WDWord::setRead1( String^ inData )
{	
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�ǂ�1�����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10107;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDWORD_READ1LEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�ǂ�1���������܂��B" );
		tmpWDDataException->ErrorCode  = 10107;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		if( Read1 != nullptr ) delete Read1;
		Read1 = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�ǂ�1�̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10107;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** �ǂ�2�ݒ�
void WDDatas::WDWord::setRead2( String^ inData )
{	
	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�ǂ�2�����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10108;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDWORD_READ2LEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�ǂ�2���������܂��B" );
		tmpWDDataException->ErrorCode  = 10108;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		if( Read2 != nullptr ) delete Read2;
		Read2 = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�ǂ�2�̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10108;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** �P��ID�ݒ�
void WDDatas::WDWord::setWordID( Int32 inData )
{
	//-- �����`�F�b�N --//
	if( inData <= 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�P��ID���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10109;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	WordID = inData;
}

//***** �ǂݕ��ݒ�
void WDDatas::WDWord::setReadPattern( Byte inData )
{
	ReadPattern = inData;
}

//***** ��{�t���O�ݒ�
void WDDatas::WDWord::setBaseFlg( Boolean inData )
{
	BaseFlg = inData;
}					


//***** ���p�`�ݒ�
void WDDatas::WDWord::setPractical( Byte inData )
{
	Practical = inData;
}					

//***** �l�̐ݒ�
void WDDatas::WDWord::setGramatical( Byte inData )
{
	Gramatical = inData;
}

//***** �P�������ݒ�
void WDDatas::WDWord::setPlurality( Byte inData )
{
	Plurality = inData;
}

//***** ���ݒ�
void WDDatas::WDWord::setSex( Byte inData )
{
	Sex = inData;
}

//***** ���p�^�C�v�ݒ�
void WDDatas::WDWord::setType( Int32 inData )
{
	//-- �����`�F�b�N --//
	if( inData < 0 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"���p�^�C�v���s���ł��B" );
		tmpWDDataException->ErrorCode  = 10116;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	Type = inData;
}


//------------------------------------------------------------------------------
//�@�f�[�^����
//------------------------------------------------------------------------------
//***** �f�[�^�擾
array<Byte>^ WDDatas::WDWord::getData( array<Byte>^ inData )
{
	array<Byte>^ rtData;
	Int32		 tmpPos;

	//-- �����`�F�b�N --//
	if( inData != nullptr &&
		inData->Length < WDWORD_LENGTH - WDWORD_RESERVEDLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[��f�[�^�����Z�����܂��B" );
		tmpWDDataException->ErrorCode  = 10117;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		if( inData == nullptr )
		{
			rtData = gcnew array<Byte>( WDWORD_LENGTH );
		}else{
			rtData = inData;
		}

		tmpPos = 0;
		//�P��	
		FJIFuncs::StringToArray( Word, rtData, tmpPos, WDWORD_WORDLEN );
		tmpPos += WDWORD_WORDLEN;
		//�ǂݕ��P
		FJIFuncs::StringToArray( Read1, rtData, tmpPos, WDWORD_READ1LEN );
		tmpPos += WDWORD_READ1LEN;
		//�ǂݕ��Q
		FJIFuncs::StringToArray( Read2, rtData, tmpPos, WDWORD_READ2LEN );
		tmpPos += WDWORD_READ2LEN;
		//�P��ID
		FJIFuncs::Int32ToArray( WordID, rtData, tmpPos );
		tmpPos += WDWORD_WORDIDLEN;

		//�ǂݕ�
		rtData[tmpPos] = ReadPattern;
		tmpPos += WDWORD_READPATTERNLEN;

		//��{�t���O
		if( BaseFlg == true )		//true�Ȃ�@0 :�@false�Ȃ� 0�ȊO
		{
			rtData[tmpPos] = 0;
		}else{
			rtData[tmpPos] = 1;
		}
		tmpPos += WDWORD_BASEFLGLEN;

		//���p�`
		rtData[tmpPos] = Practical;
		tmpPos += WDWORD_PRACTICALLEN;
		//�P������
		rtData[tmpPos] = Plurality;
		tmpPos += WDWORD_PLURALITYLEN;
		//�l��
		rtData[tmpPos] = Gramatical;
		tmpPos += WDWORD_GRAMATICALLEN;
		//��
		rtData[tmpPos] = Sex;
		tmpPos += WDWORD_SEXLEN;
		//���ptype
		FJIFuncs::Int32ToArray( Type, rtData, tmpPos );
		tmpPos += WDWORD_TYPELEN;

		//�]��
		for(Int32 i = 0; i < WDWORD_RESERVEDLEN; i++ )
		{
			Buffer::SetByte( rtData,tmpPos, 0 );
			tmpPos++;
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�̃R�s�[�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10117;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- ����I�� --//
	return rtData;
}

//***** �f�[�^�ݒ�
void WDDatas::WDWord::setData( array<Byte>^ inData )
{
	Int32		 tmpPos;

	//-- �����`�F�b�N --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[���f�[�^�����ݒ�ł��B" );
		tmpWDDataException->ErrorCode  = 10118;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length != WDWORD_LENGTH )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�R�s�[���f�[�^��������������܂���B" );
		tmpWDDataException->ErrorCode  = 10118;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- �f�[�^�ݒ� --//
	try
	{
		tmpPos = 0;
		//�P��
		if( Word != nullptr ) delete Word;
		Word = FJIFuncs::ArrayToString(inData, tmpPos, WDWORD_WORDLEN );
		tmpPos += WDWORD_WORDLEN;
		//�ǂݕ��P
		if( Read1 != nullptr ) delete Read1;
		Read1 = FJIFuncs::ArrayToString(inData, tmpPos, WDWORD_WORDLEN );
		tmpPos += WDWORD_READ1LEN;
		//�ǂݕ��Q
		if( Read2 != nullptr ) delete Read2;
		Read2 = FJIFuncs::ArrayToString(inData, tmpPos, WDWORD_WORDLEN );
		tmpPos += WDWORD_READ2LEN;
		//�P��ID
		WordID = FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDWORD_WORDIDLEN;

		//�i��
		ReadPattern = inData[tmpPos];
		tmpPos += WDWORD_READPATTERNLEN;

		//��{�t���O
		if( inData[tmpPos] == 0 )	//0�Ȃ�@true , 0�ȊO�Ȃ� false
		{
			BaseFlg = true;
		}else{
			BaseFlg = false;
		}
		tmpPos += WDWORD_BASEFLGLEN;
		//���p�`
		Practical = inData[tmpPos];
		tmpPos += WDWORD_PRACTICALLEN;
		//�P������
		Plurality = inData[tmpPos];
		tmpPos += WDWORD_PLURALITYLEN;
		//�l��
		Gramatical = inData[tmpPos];
		tmpPos += WDWORD_GRAMATICALLEN;
		//��
		Sex = inData[tmpPos];
		tmpPos += WDWORD_SEXLEN;
		//���ptype
		Type = FJIFuncs::ArrayToInt32( inData, tmpPos );
		tmpPos += WDWORD_TYPELEN;

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"�f�[�^�̐ݒ�Ɏ��s���܂����B", exp );
		tmpWDDataException->ErrorCode  = 10118;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}