//------------------------------------------------------------------------------
//	�P�ꎫ�T��`�t�@�C��
//	Version 1.0.0.0		create date 2006/05/08
//	Version 1.0.1.0		create date 2009/09/13
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
#pragma once

namespace WordDic
{

	//���T�t�@�C���@�t�@�C��ID
	#define WDWORDPTBR_FID		L"WDWORD_PTBR"			//�P��t�@�C���|���g�K����
	#define WDMEANPTBRJP_FID	L"WDMEAN_PTBRJP"		//�Ӗ��t�@�C���|���g�K����i���{��ŉ��)
	#define WDTRANSPTBRJP_FID	L"WDTRANS_PTBRJP"		//�|��t�@�C���|���g�K���ꁨ���{��
	#define WDRELATIONPTBR_FID	L"WDREL_PTBR"			//�֘A��t�@�C���|���g�K����
	#define WDSEGMENTPTBRJP_FID	L"WDSEG_PTBR_JP"		//�敪�t�@�C���|���g�K����(���{�ꖼ�\�L)

	#define WDWORDJP_FID		L"WDWORD_JP"			//�P��t�@�C�����{��
	#define WDMEANJPJP_FID		L"WDMEAN_JPJP"			//�Ӗ��t�@�C�����{��(���{��ŉ��)
	#define WDTRANSJPPTBR_FID	L"WDTRANS_JPPTBR"		//�|��t�@�C�����{�ꁨ�|���g�K����
	#define WDRELATIONJP_FID	L"WDREL_JP"				//�֘A��t�@�C�����{��
	#define WDSEGMENTJPJP_FID	L"WDSEG_JP_JP"			//�敪�t�@�C�����{��(���{�ꖼ�\�L)

	#define WDGROUPJP_FID		L"WDGROUP_JP"			//���ރt�@�C��(���{�ꖼ�\�L)

	//�敪ID
	static const Int32 SPEECH_ID =		1;						//�i���敪ID
	static const Int32 PRATICAL_ID =	2;						//���p�`�敪ID
	static const Int32 GRAMATICAL_ID =	3;						//�l�̋敪ID
	static const Int32 PLURALITY_ID	=	4;						//�P�������敪ID
	static const Int32 SEX_ID =			5;						//���敪ID
	static const Int32 TYPE_ID =		6;						//���p�^�C�v�敪ID
	static const Int32 RELATION_ID =	7;						//�֘A��^�C�v�敪ID
	static const Int32 RANK_ID =		8;						//�����N�敪ID

	//XML�G�������g��
	#define	WORDS_NODE				L"WORDS"				//�x�[�X�m�[�h
	#define BASE_NODE				L"BASE"					//��{�P��m�[�h
	#define BASE_WORD_ELE			L"WORD"					//��{�P�� �P��
	#define BASE_READ1_ELE			L"READ1"				//��{�P�� �ǂ݂P
	#define BASE_READ2_ELE			L"READ2"				//��{�P�� �ǂ݂Q
	#define SUBBASEGRP_NODE			L"SUBBASEGRP"			//��{�P��ǂݕ��O���[�v�m�[�h
	#define SUBBASE_NODE			L"SUBBASE"				//��{�P��ǂݕ��m�[�h
	#define SUBBASE_WORD_ELE		L"SUBWORD"				//��{�P�� �P��
	#define SUBBASE_READ1_ELE		L"SUBREAD1"				//��{�P�� �ǂ݂P
	#define SUBBASE_READ2_ELE		L"SUBREAD2"				//��{�P�� �ǂ݂Q
	#define MEANS_NODE				L"MEANS"				//�Ӗ��O���[�v�m�[�h
	#define MEAN_NODE				L"MEAN"					//�Ӗ��m�[�h
	#define MEANNO_ELE				L"MEANNO"				//�Ӗ��ԍ�
	#define TRANSES_NODE			L"TRANSES"				//�|��O���[�v�m�[�h
	#define TRANS_NODE				L"TITEM"				//�|��m�[�h
	#define TRANSID_ELE				L"TRANSID"				//�|��ID 
	#define TRANSWORD_ELE			L"TRANS"				//�|��P��
	#define GROUP_NODE				L"GITEM"				//���ރO���[�v�m�[�h
	#define GROUPID_ELE				L"GROUPID"				//����
	#define GROUP_ELE				L"GROUP"				//����
	#define MSPEECH_ELE				L"MSPEECH"				//�Ӗ��i��
	#define MRANK_ELE				L"MRANK"				//�Ӗ������N
	#define MEAN_ELE				L"MITEM"				//�Ӗ�
	#define EXAMPLE_ELE				L"EXAMPLE"				//�ᕶ
	#define RELATIONS_NODE			L"RELS"					//�֘A��O���[�v�m�[�h
	#define RELATION_NODE			L"RITEM"				//�֘A��O���[�v�m�[�h
	#define RELATIONTYPE_ELE		L"RELTYPE"				//�֘A��^�C�v
	#define RELATIONID_ELE			L"RELID"				//�֘A��ID
	#define RELATION_ELE			L"REL"					//�֘A��
	#define PRATICALGRPSEC_ELE		L"PRGROUPSEC"			//���p�O���[�v�Z�N�V����
	#define PRATICALGRP_ELE			L"PRGROUP"				//���p�O���[�v
	#define PRATICALTYPE_ELE		L"PRTYPE"				//���p�^�C�v
	#define PRATICALS_NODE			L"PRATICALS"			//���p�`�O���[�v�m�[�h
	#define PRATICALITEM_NODE		L"PRITEM"				//���p�`�m�[�h
	#define PRATICALTITLE_ELE		L"PRTITLE"				//���p�`(���p�`�A�l�́A�P�������A���Ȃǁj
	#define PRATICALTYPEID_ELE		L"PRTYPEID"				//���p���@ID
	#define PRATICALID_ELE			L"PRTICALID"			//���p�`ID
	#define PRATICALWORD_ELE		L"PRWORD"				//���p�`�P��
	#define PRATICALREAD1_ELE		L"PRREAD1"				//���p�`�ǂݕ��P
	#define PRATICALREAD2_ELE		L"PRREAD2"				//���p�`�ǂݕ��Q

	//�P��\���f�[�^�i�[�t�H���_�i�ꕔ�j
	#define XMLFOLDERNAME			L"WDSch\\"				//�p�X��(����)

	//Web����
	#define WEB_BING			L"http://www.bing.com/search?q="							//Bing
	#define WEB_GOOGLE			L"http://www.google.co.jp/search?hl=ja&q="					//Google
	//Web�S�Ȏ��T
	#define WEB_ENCALTA			L"http://jp.encarta.msn.com/encnet/refpages/search.aspx?q="	//�G���J���^
	#define WEB_WIKI			L"http://ja.wikipedia.org/wiki/"							//Wiki

				


};
