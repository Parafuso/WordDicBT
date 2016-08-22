///------------------------------------------------------------------------------
//	単語辞典　定義ファイル
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
#pragma once

namespace WDDatas
{
	//-- WDWord 単語クラス --//
	#define WDWORD_LENGTH				400
	#define WDWORD_WORDLEN				100
	#define WDWORD_READ1LEN				100
	#define WDWORD_READ2LEN				100
	#define WDWORD_WORDIDLEN			4
	#define WDWORD_READPATTERNLEN		1
	#define WDWORD_BASEFLGLEN			1
	#define WDWORD_PRACTICALLEN			1
	#define WDWORD_GRAMATICALLEN		1
	#define WDWORD_PLURALITYLEN			1
	#define WDWORD_SEXLEN				1
	#define WDWORD_TYPELEN				4
	#define WDWORD_RESERVEDLEN			86

	//-- WDMEAN 単語意味 --//
	#define WDMEAN_LENGTH				1000
	#define WDMEAN_SHORT_LENGTH			20
	#define WDMEAN_WORDIDLEN			4
	#define WDMEAN_MEANNOLEN			4
	#define WDMEAN_MEANFLGLEN			4
	#define WDMEAN_GROUPRANKLEN			4
	#define WDMEAN_GROUPGTLEN			2
	#define WDMEAN_GROUPLTLEN			2
	#define WDMEAN_SPEECHLEN			1
	#define WDMEAN_RANKLEN				4
	#define WDMEAN_MEANLEN				500
	#define WDMEAN_EXAMPLELEN			400
	#define WDMEAN_RESERVEDLEN			75

	//-- WDTRANS 単語翻訳 --//
	#define WDTRANS_WORDIDLEN			4
	#define WDTRANS_MEANNOLEN			4
	#define WDTRANS_TRANSIDCNTLEN		4
	#define WDTRANS_TRANSIDLEN			4
	#define WDTRANS_TRANSNOLEN			4

	//-- WDRELATION 単語関連 --//
	#define WDRELATION_WORDIDLEN		4
	#define WDRELATION_MEANNOLEN		4
	#define WDRELATION_RELATIONCNTLEN	4
	#define WDRELATION_RELATIONTYPELEN	4
	#define WDRELATION_RELATIONIDLEN	4
	#define WDRELATION_RELATIONNOLEN	4

	//-- WDGROUP 分類 --//
	#define WDGROUP_LENGTH				100
	#define WDGROUP_GROUPGTLEN			2
	#define WDGROUP_GROUPLTLEN			2
	#define WDGROUP_NAMELEN				60
	#define WDGROUP_SHORTNAMELEN		10
	#define WDGROUP_RESERVEDLEN			26

	//-- WDSEGMENT 区分 --//
	#define WDSEGMENT_LENGTH			100
	#define WDSEGMENT_SEGMENTIDLEN		4
	#define WDSEGMENT_SEGMENTNOLEN		4
	#define WDSEGMENT_NAMELEN			60
	#define WDSEGMENT_SHORTNAMELEN		10
	#define WDSEGMENT_RESERVEDLEN		22
	
}