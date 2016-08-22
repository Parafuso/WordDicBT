//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�f�[�^�p��O�N���X�@�w�b�_
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDDatas		: �f�[�^���R�[�h��{�N���X
//		WDWord		: �P��N���X
//		WDMean		: �Ӗ��N���X
//		WDGroup		: ���ރN���X
//		WDSegment	: �敪�N���X
//------------------------------------------------------------------------------
#pragma once

using namespace System;
using namespace FJIsam;

namespace WDDatas {

	//***** �x�[�X�N���X
	public ref class WDRec
	{
		//-- �f�X�g���N�^ --//	
		virtual ~WDRec();
	public :
		//-- �f�[�^���R�[�h���� --//
		virtual DataRecord^ getRecord( void );							//�f�[�^���R�[�h�擾
		virtual void setRecord( DataRecord^ inRec );					//�f�[�^���R�[�h�ݒ�
		virtual void Write( void );										//�f�[�^���R�[�h����
		virtual void Delete( void );									//�f�[�^���R�[�h�폜

		//-- ��񑀍� --//
		static Int32 Length();											//�f�[�^�����擾
		virtual Int32 RecLength();										//�f�[�^���R�[�h���擾

	private :

		DataRecord^	DataRec;
	};

	//***** �P��N���X
	public ref class WDWord : public WDRec
	{
	public :
		//-- �R���X�g���N�^ --//	
		WDWord();
		WDWord( DataRecord^ inRec );

		//-- �f�X�g���N�^ --//	
		~WDWord();

		//-- �f�[�^���R�[�h���� --//
		virtual DataRecord^ getRecord( void ) override;					//�f�[�^���R�[�h�擾
		virtual void setRecord( DataRecord^ inRec ) override;			//�f�[�^���R�[�h�ݒ�
		virtual void Write( void ) override;							//�f�[�^���R�[�h����
		virtual void Delete( void ) override;							//�f�[�^���R�[�h�폜

		//-- ��񑀍� --//
		static Int32 Length();											//�f�[�^�����擾
		virtual Int32 RecLength() override;								//�f�[�^���R�[�h���擾

		//-- �A�C�e������ --//
		String^ getWord( String^ inData );								//�P��擾
		String^ getRead1( String^ inData );								//�ǂ�1�擾
		String^ getRead2( String^ inData );								//�ǂ�2�擾
		Int32	getWordID( void );										//�P��ID�擾
		Byte	getReadPattern( void );									//�ǂݕ��擾
		Boolean	getBaseFlg( void );										//��{�t���O�擾
		Byte	getPractical( void );									//���p�`�擾
		Byte	getPlurality( void );									//�P�������擾
		Byte	getGramatical( void );									//�l�̎擾
		Byte	getSex( void );											//���擾
		Int32	getType( void );										//���p�^�C�v�擾
	
		void setWord( String^ inData );									//�P��ݒ�
		void setRead1( String^ inData );								//�ǂ�1�ݒ�
		void setRead2( String^ inData );								//�ǂ�2�ݒ�
		void setWordID( Int32 inData );									//�P��ID�ݒ�
		void setReadPattern( Byte inData );								//�ǂݕ��ݒ�
		void setBaseFlg( Boolean inData );								//��{�t���O�ݒ�
		void setPractical( Byte inData );								//���p�`�ݒ�
		void setPlurality( Byte inData );								//�P�������ݒ�
		void setGramatical( Byte inData );								//�l�̐ݒ�
		void setSex( Byte inData );										//���ݒ�
		void setType( Int32 inData );									//���p�^�C�v�ݒ�

	private :
		//-- �f�[�^���� --//
		array<Byte>^ getData( array<Byte>^ inRec );						//�f�[�^�擾
		void		 setData( array<Byte>^ inRec );						//�f�[�^�ݒ�

		String^			Word;						//�P��
		String^			Read1;						//�ǂ�1
		String^			Read2;						//�ǂ�2
		Int32			WordID;						//�P��ID
		Byte			ReadPattern;				//�ǂݕ�
		Boolean			BaseFlg;					//��{�t���O
		Byte			Practical;					//���p�`
		Byte			Plurality;					//�P������
		Byte			Gramatical;					//�l��
		Byte			Sex;						//��
		Int32			Type;						//���p�^�C�v

	};


	//***** �Ӗ��N���X�p���ލ\����
	public ref struct WDMeanGroup
	{
		Int32			MeanFlg;					//�Ӗ��t���O
		array<Byte>^	GroupGt;					//���ޑ�
		array<Byte>^	GroupLt;					//���ޏ�
		Int32			GroupRank;					//���ރ����N
		DataRecord^		DataRec;					//�f�[�^���R�[�h
	};

	//�Ӗ����ޔ�r
	public ref class WDMeanGrpComparer: System::Collections::Generic::IComparer<WDMeanGroup^>					//�Ӗ����X�g��r
	{
	public:
		virtual Int32 Compare(WDMeanGroup^ x, WDMeanGroup^ y);		//�Ӗ��O���[�v
	};

	//***** �Ӗ��N���X
	public ref class WDMean : public  WDRec
	{
	public :

		//-- �R���X�g���N�^ --//	
		WDMean( void );
		WDMean( DataRecord^ inRec );

		//-- �f�X�g���N�^ --//	
		~WDMean();

		//-- �f�[�^���R�[�h���� --//
		virtual DataRecord^ getRecord( void ) override;					//�f�[�^���R�[�h�擾
		virtual void setRecord( DataRecord^ inRec ) override;			//�f�[�^���R�[�h�ݒ�
		virtual void Write( void ) override;							//�f�[�^���R�[�h����
		virtual void Delete( void ) override;							//�f�[�^���R�[�h�폜

		DataRecord^ getRecord( Int32 inIdx );							//�f�[�^���R�[�h�擾(idx�w��)
		void Write( Int32 inIdx );										//�f�[�^���R�[�h����(idx�w��)
		void Delete( Int32 inIdx );										//�f�[�^���R�[�h�폜(idx�w��)

		//-- ��񑀍� --//
		Int32 DataLength( Int32 inIdx );								//�f�[�^�����擾
		virtual Int32 RecLength() override;								//�f�[�^���R�[�h���擾
		Int32	RecLength( Int32 inIdx );								//�f�[�^���R�[�h���擾(idx�w��)

		Int32	getWordID( void );										//�P��ID�擾
		Int32	getMeanNo( void );										//�Ӗ�No�擾
		WDMeanGroup^	getGroup( Int32 inIdx );						//���ގ擾
		Int32			getMeanFlg( Int32 inIdx );						//���ރt���O�擾
		array<Byte>^	getGroupGt( Int32 inIdx,						//���ޑ�擾 
								array<Byte>^ inData );
		array<Byte>^	getGroupLt( Int32 inIdx		,					//���ޏ��擾
								array<Byte>^ inData );					
		Int32	getGroupRank( Int32 inIdx );							//���ޏ��ʎ擾
		Byte	getSpeech( void );										//�i���擾
		Int32	getRank( void );										//�����N�擾
		String^ getMean( String^ inData );								//�P��擾
		String^ getExample( String^ inData );							//�ᕶ�擾
		Int32	MeanGroupCount( void );									//���ސ�
		
		void setWordID( Int32 inData );									//�P��ID�ݒ�
		void setMeanNo( Int32 inData );									//�Ӗ�No�ݒ�
		void setGroup( Int32 inMeanFlg, array<Byte>^ inGroupGt, 		//���ސݒ�
						array<Byte>^ inGroupLt, Int32 inGroupRank );
		void setSpeech( Byte inData );									//�i���ݒ�
		void setRank(Byte inData );										//�����N�ݒ�
		void setMean( String^ inData );									//�Ӗ��ݒ�
		void setExample( String^ inData );								//�ᕶ�ݒ�

		void MergeMean( WDMean^ inData );								//�Ӗ��}�[�W

	private :
		Int32 addMeanGrp( WDMeanGroup^ inMeanGrp );						//�Ӗ��O���[�v�ǉ�

		Int32				WordID;										//�P��ID
		Int32				MeanNo;										//�Ӗ�No
		List<WDMeanGroup^>^	MeanGroup;									//�Ӗ��O���[�v
		Byte				Speech;										//�i��
		Int32				Rank;										//�����N
		String^				Mean;										//�Ӗ�
		String^				Example;									//�ᕶ

		//-- �Ӗ��O���[�v��r
		static WDMeanGrpComparer^ WDMeanGrpComp = nullptr;				//�Ӗ����ޕ��ёւ�

	};

	
	//***** �|��N���X
	public ref class WDTrans : public  WDRec
	{
	public :
		//-- �R���X�g���N�^ --//	
		WDTrans( void );
		WDTrans( DataRecord^ inRec );

		//-- �f�X�g���N�^ --//	
		~WDTrans();

		//-- �f�[�^���R�[�h���� --//
		virtual DataRecord^ getRecord( void ) override;					//�f�[�^���R�[�h�擾
		virtual void setRecord( DataRecord^ inRec ) override;			//�f�[�^���R�[�h�ݒ�
		virtual void Write( void ) override;							//�f�[�^���R�[�h����
		virtual void Delete( void ) override;							//�f�[�^���R�[�h�폜

		//-- ��񑀍� --//
		Int32 DataLength( void );										//�f�[�^�����擾
		virtual Int32 RecLength() override;								//�f�[�^���R�[�h���擾

		Int32	getWordID( void );										//�P��ID�擾
		Int32	getMeanNo( void );										//�Ӗ�No�擾
		Int32	getTransID( Int32 inIdx );								//�|��ID�擾
		Int32	getTransNo( Int32 inIdx );								//�|��Ӗ�No�擾

		void setWordID( Int32 inData );									//�P��ID�ݒ�
		void setMeanNo( Int32 inData );									//�Ӗ�No�ݒ�
		void setTransID( Int32 inData, Int32 inIdx );					//�|��ID�ݒ�
		void setTransNo( Int32 inData, Int32 inIdx );					//�|��Ӗ�No�ݒ�
		void AddTransID( Int32 inID, Int32 inNo );						//�|��ID�ǉ�
		void RemoveTransID( Int32 inIdx );								//�|��ID�폜
		Int32 CountTransID( void );										//�|��ID���J�E���g

	private :
		//-- �f�[�^���� --//
		array<Byte>^ getData( array<Byte>^ inRec );						//�f�[�^�擾
		void		 setData( array<Byte>^ inRec );						//�f�[�^�ݒ�

		Int32			WordID;					//�P��ID
		Int32			MeanNo;					//�Ӗ�No
		List<Int32>^	TransID;				//�|��ID
		List<Int32>^	TransNo;				//�|��Ӗ�No

	};

	//***** �֘A��N���X
	public ref class WDRelation : public  WDRec
	{
	public :
		//-- �R���X�g���N�^ --//	
		WDRelation( void );
		WDRelation( DataRecord^ inRec );

		//-- �f�X�g���N�^ --//	
		~WDRelation();

		//-- �f�[�^���R�[�h���� --//
		virtual DataRecord^ getRecord( void ) override;					//�f�[�^���R�[�h�擾
		virtual void setRecord( DataRecord^ inRec ) override;			//�f�[�^���R�[�h�ݒ�
		virtual void Write( void ) override;							//�f�[�^���R�[�h����
		virtual void Delete( void ) override;							//�f�[�^���R�[�h�폜

		//-- ��񑀍� --//
		Int32 DataLength();												//�f�[�^�����擾
		virtual Int32 RecLength() override;								//�f�[�^���R�[�h���擾

		Int32	getWordID( void );										//�P��ID�擾
		Int32	getMeanNo( void );										//�Ӗ�No�擾
		Int32	getRelationType( Int32 inIdx );							//�֘A��^�C�v�擾
		Int32	getRelationID( Int32 inIdx );							//�֘A��ID�擾
		Int32	getRelationNo( Int32 inIdx );							//�֘A��Ӗ�No�擾
	
		void setWordID( Int32 inData );									//�P��ID�ݒ�
		void setMeanNo( Int32 inData );									//�Ӗ�No�ݒ�
		void setRelationType( Int32 inData, Int32 inIdx );				//�֘A�^�C�v�ݒ�
		void setRelationID( Int32 inData, Int32 inIdx );				//�֘A��ID�ݒ�
		void setRelationNo( Int32 inData, Int32 inIdx );				//�֘A��Ӗ�No�ݒ�
		void AddRelation( Int32 inType, Int32 inID, Int32 inNo );		//�֘A��ǉ�
		void RemoveRelation( Int32 inIdx );								//�֘A��폜
		Int32 CountRelation( void );									//�֘A�ꐔ�J�E���g

	private :
		//-- �f�[�^���� --//
		array<Byte>^ getData( array<Byte>^ inRec );						//�f�[�^�擾
		void		 setData( array<Byte>^ inRec );						//�f�[�^�ݒ�

		Int32			WordID;					//�P��ID
		Int32			MeanNo;					//�Ӗ�No
		List<Int32>^	RelationType;			//�֘A����
		List<Int32>^	RelationID;				//�֘A��ID
		List<Int32>^	RelationNo;				//�֘A��Ӗ�No


	};

	//***** ���ރN���X
	public ref class WDGroup : public WDRec
	{
	public :
		//-- �R���X�g���N�^ --//	
		WDGroup();
		WDGroup( DataRecord^ inRec );

		//-- �f�X�g���N�^ --//	
		~WDGroup();

		//-- �f�[�^���R�[�h���� --//
		virtual DataRecord^ getRecord( void ) override;					//�f�[�^���R�[�h�擾
		virtual void setRecord( DataRecord^ inRec ) override;			//�f�[�^���R�[�h�ݒ�
		virtual void Write( void ) override;							//�f�[�^���R�[�h����
		virtual void Delete( void ) override;							//�f�[�^���R�[�h�폜

		//-- ��񑀍� --//
		static Int32 Length();											//�f�[�^�����擾
		virtual Int32 RecLength() override;								//�f�[�^���R�[�h���擾

		//-- �A�C�e������ --//
		array<Byte>^ getGroupGt( array<Byte>^ inData );					//���ޑ�擾
		array<Byte>^ getGroupLt( array<Byte>^ inData );					//���ޏ��擾
		String^		 getName( String^ inData );							//���̎擾
		String^		 getShortName( String^ inData );					//���̎擾


		void setGroupGt( array<Byte>^ inData );							//���ޑ�ݒ�
		void setGroupLt( array<Byte>^ inData );							//���ޏ��ݒ�
		void setName( String^ inData );									//���̐ݒ�
		void setShortName( String^ inData );							//���̐ݒ�

	private :
		//-- �f�[�^���� --//
		array<Byte>^ getData( array<Byte>^ inRec );						//�f�[�^�擾
		void		 setData( array<Byte>^ inRec );						//�f�[�^�ݒ�

		array<Byte>^	GroupGt;				//���ޑ�
		array<Byte>^	GroupLt;				//���ޏ�
		String^			Name;					//����
		String^			ShortName;				//����
	};

	//***** ���ރN���X
	public ref class WDSegment : public WDRec
	{
	public :
		//-- �R���X�g���N�^ --//	
		WDSegment();
		WDSegment( DataRecord^ inRec );

		//-- �f�X�g���N�^ --//	
		~WDSegment();

		//-- �f�[�^���R�[�h���� --//
		virtual DataRecord^ getRecord( void ) override;					//�f�[�^���R�[�h�擾
		virtual void setRecord( DataRecord^ inRec ) override;			//�f�[�^���R�[�h�ݒ�
		virtual void Write( void ) override;							//�f�[�^���R�[�h����
		virtual void Delete( void ) override;							//�f�[�^���R�[�h�폜

		//-- ��񑀍� --//
		static Int32 Length();											//�f�[�^�����擾
		virtual Int32 RecLength() override;								//�f�[�^���R�[�h���擾

		//-- �A�C�e������ --//
		Int32	getSegmentID( void );									//�敪ID�擾
		Int32	getSegmentNo( void );									//�敪No�擾
		String^	 getName( String^ inData );								//���̎擾
		String^	 getShortName( String^ inData );						//���̎擾

		void setSegmentID( Int32 inData );								//�敪ID�ݒ�
		void setSegmentNo( Int32 inData );								//�敪No�ݒ�
		void setName( String^ inData );									//���̐ݒ�
		void setShortName( String^ inData );							//���̐ݒ�

	private :
		//-- �f�[�^���� --//
		array<Byte>^ getData( array<Byte>^ inRec );						//�f�[�^�擾
		void		 setData( array<Byte>^ inRec );						//�f�[�^�ݒ�

		Int32			SegmentID;				//�敪ID
		Int32			SegmentNo;				//�敪No
		String^			Name;					//����
		String^			ShortName;				//����
	};



}
