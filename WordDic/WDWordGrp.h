//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�p�N���X�@�w�b�_
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDWordGrp : ���T�P����
//------------------------------------------------------------------------------
#pragma once
using namespace WDDatas;

namespace WordDic
{
	public ref class WDWordComparer: System::Collections::Generic::IComparer<WDWord^>					//�P�ꃊ�X�g��r
	{
	public:
		virtual Int32 Compare(WDWord^ x, WDWord^ y);
	};

	public ref class WDMeanComparer: System::Collections::Generic::IComparer<WDMean^>					//�Ӗ����X�g��r
	{
	public:
		virtual Int32 Compare(WDMean^ x, WDMean^ y);
	};

	public ref class WDTransComparer: System::Collections::Generic::IComparer<WDTrans^>				//�|�󃊃X�g��r
	{
	public:
		virtual Int32 Compare(WDTrans^ x, WDTrans^ y);
	};

	public ref class WDRelationComparer: System::Collections::Generic::IComparer<WDRelation^>			//�֘A�ꃊ�X�g��r
	{
	public:
		virtual Int32 Compare(WDRelation^ x, WDRelation^ y);
	};

	//***** �P��O���[�v
	public ref class WDWordGrp 
	{
	public :
		//--  �R���X�g���N�^ --//
		WDWordGrp( Int32 inLang, Int32 inDispNum, Int32 inSubDispNum );
		//--  �f�X�g���N�^ --//
		~WDWordGrp();

		//-- �A�C�e���Q�� --//
		WDWord^ getWord( Int32 idx );									//�P��擾
		WDWord^ getBaseWord( void );									//��{�P��擾
		WDWord^ getBaseWord( Int32 inReadPattern );						//��{�P��擾(�ǂݕ��ɂ��)
		WDWord^	getSchWord( void );										//�����P��擾
		WDMean^ getMean( Int32 idx );									//�Ӗ��擾
		WDMean^ getSchMean( void );										//�����Ӗ��擾
		WDTrans^ getTrans( Int32 idx );									//�|��擾
		WDTrans^ getTransNo( Int32 inNo );								//�|��擾(�Ӗ�NO�ɂ��)
		WDRelation^ getRelation( Int32 idx );							//�֘A��擾
		WDRelation^ getRelationNo( Int32 inNo );						//�֘A��擾(�Ӗ�NO�ɂ��)
		String^		getXMLFname( void );								//XML�t�@�C�����擾

		Int32 getWordID( void );										//�P��ID�擾
		Int32 getWordCnt( void );										//�P�ꐔ�擾
		Int32 getMeanCnt( void );										//�Ӗ����擾
		Int32 getTransCnt( void );										//�|�󐔎擾
		Int32 getRelationCnt( void );									//�֘A�ꐔ�擾

		Int32 getSchMethod( void );										//�������@�擾
		Int32 getSchLang( void );										//��������擾
		Int32 getWordListDisp( void );									//ToString�ł̕\�����@�擾
		Int32 getSchGroupRank( void );									//�����Ӗ����ޏ���
		Int32 getReadPatternCnt( void );								//�ǂݕ����擾

		//-- �A�C�e���ݒ� --//
		void addWord( WDWord^ inWord, Boolean inSch );					//�P��ǉ�
		void addMean( WDMean^ inMean, Boolean inSch, Int32 inMeanFlg );	//�Ӗ��ǉ�
		void addTrans( WDTrans^ inTrans );								//�|��ǉ�
		void addRelation( WDRelation^ inRelation );						//�֘A��ǉ�
		void setXMLFname( String^ inXMLFname );							//XML�t�@�C�����ݒ�
		void setWordListDisp( Int32 inDispNum, Int32 inSubDispNum );	//ToString�ł̕\�����@�ݒ�

		//-- ���X�gBox�p --//
		virtual String^ ToString( void ) override;						//������擾

	private :
		List<WDWord^>^		WordLst;									//�P�ꃊ�X�g
		List<WDMean^>^		MeanLst;									//�Ӗ����X�g
		List<WDTrans^>^		TransLst;									//�|�󃊃X�g
		List<WDRelation^>^	RelationLst;								//�֘A�ꃊ�X�g
		List<WDWord^>^		BaseWordLst;								//��{�P�ꃊ�X�g
		WDWord^				SchWord;									//�����P��
		WDMean^				SchMean;									//�����P��
		Int32				WordID;										//�P��ID
		String^				XMLFname;									//�P����XML�t�@�C����
		Int32				SchMethod;									//�������@( 1:�P�� 2:�Ӗ�(����) )
		Int32				SchLang;									//��������( 1:����A 2:����B )
		Int32				SchGroupRank;								//���ޏ���
		Int32				SchReadPattern;								//�����ǂݕ�

		Int32				DispNum;									//ToString�ł̕\���P��( 1:Word 2:Read1 3:Read2 )
		Int32				SubDispNum;									//ToString�ł̃T�u�\���P��( �V )

		static WDWordComparer^		WDWordComp = nullptr;				//�P�ꃊ�X�g��r
		static WDMeanComparer^		WDMeanComp = nullptr;				//�Ӗ����X�g��r
		static WDTransComparer^		WDTransComp = nullptr;				//�|�󃊃X�g��r
		static WDRelationComparer^	WDRelationComp = nullptr;			//�֘A�ꃊ�X�g��r
	};

}