//------------------------------------------------------------------------------
//	単語辞典定義ファイル
//	Version 1.0.0.0		create date 2006/05/08
//	Version 1.0.1.0		create date 2009/09/13
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
#pragma once

namespace WordDic
{

	//辞典ファイル　ファイルID
	#define WDWORDPTBR_FID		L"WDWORD_PTBR"			//単語ファイルポルトガル語
	#define WDMEANPTBRJP_FID	L"WDMEAN_PTBRJP"		//意味ファイルポルトガル語（日本語で解説)
	#define WDTRANSPTBRJP_FID	L"WDTRANS_PTBRJP"		//翻訳ファイルポルトガル語→日本語
	#define WDRELATIONPTBR_FID	L"WDREL_PTBR"			//関連語ファイルポルトガル語
	#define WDSEGMENTPTBRJP_FID	L"WDSEG_PTBR_JP"		//区分ファイルポルトガル語(日本語名表記)

	#define WDWORDJP_FID		L"WDWORD_JP"			//単語ファイル日本語
	#define WDMEANJPJP_FID		L"WDMEAN_JPJP"			//意味ファイル日本語(日本語で解説)
	#define WDTRANSJPPTBR_FID	L"WDTRANS_JPPTBR"		//翻訳ファイル日本語→ポルトガル語
	#define WDRELATIONJP_FID	L"WDREL_JP"				//関連語ファイル日本語
	#define WDSEGMENTJPJP_FID	L"WDSEG_JP_JP"			//区分ファイル日本語(日本語名表記)

	#define WDGROUPJP_FID		L"WDGROUP_JP"			//分類ファイル(日本語名表記)

	//区分ID
	static const Int32 SPEECH_ID =		1;						//品詞区分ID
	static const Int32 PRATICAL_ID =	2;						//活用形区分ID
	static const Int32 GRAMATICAL_ID =	3;						//人称区分ID
	static const Int32 PLURALITY_ID	=	4;						//単数複数区分ID
	static const Int32 SEX_ID =			5;						//性区分ID
	static const Int32 TYPE_ID =		6;						//活用タイプ区分ID
	static const Int32 RELATION_ID =	7;						//関連語タイプ区分ID
	static const Int32 RANK_ID =		8;						//ランク区分ID

	//XMLエレメント名
	#define	WORDS_NODE				L"WORDS"				//ベースノード
	#define BASE_NODE				L"BASE"					//基本単語ノード
	#define BASE_WORD_ELE			L"WORD"					//基本単語 単語
	#define BASE_READ1_ELE			L"READ1"				//基本単語 読み１
	#define BASE_READ2_ELE			L"READ2"				//基本単語 読み２
	#define SUBBASEGRP_NODE			L"SUBBASEGRP"			//基本単語読み方グループノード
	#define SUBBASE_NODE			L"SUBBASE"				//基本単語読み方ノード
	#define SUBBASE_WORD_ELE		L"SUBWORD"				//基本単語 単語
	#define SUBBASE_READ1_ELE		L"SUBREAD1"				//基本単語 読み１
	#define SUBBASE_READ2_ELE		L"SUBREAD2"				//基本単語 読み２
	#define MEANS_NODE				L"MEANS"				//意味グループノード
	#define MEAN_NODE				L"MEAN"					//意味ノード
	#define MEANNO_ELE				L"MEANNO"				//意味番号
	#define TRANSES_NODE			L"TRANSES"				//翻訳グループノード
	#define TRANS_NODE				L"TITEM"				//翻訳ノード
	#define TRANSID_ELE				L"TRANSID"				//翻訳ID 
	#define TRANSWORD_ELE			L"TRANS"				//翻訳単語
	#define GROUP_NODE				L"GITEM"				//分類グループノード
	#define GROUPID_ELE				L"GROUPID"				//分類
	#define GROUP_ELE				L"GROUP"				//分類
	#define MSPEECH_ELE				L"MSPEECH"				//意味品詞
	#define MRANK_ELE				L"MRANK"				//意味ランク
	#define MEAN_ELE				L"MITEM"				//意味
	#define EXAMPLE_ELE				L"EXAMPLE"				//例文
	#define RELATIONS_NODE			L"RELS"					//関連語グループノード
	#define RELATION_NODE			L"RITEM"				//関連語グループノード
	#define RELATIONTYPE_ELE		L"RELTYPE"				//関連語タイプ
	#define RELATIONID_ELE			L"RELID"				//関連語ID
	#define RELATION_ELE			L"REL"					//関連語
	#define PRATICALGRPSEC_ELE		L"PRGROUPSEC"			//活用グループセクション
	#define PRATICALGRP_ELE			L"PRGROUP"				//活用グループ
	#define PRATICALTYPE_ELE		L"PRTYPE"				//活用タイプ
	#define PRATICALS_NODE			L"PRATICALS"			//活用形グループノード
	#define PRATICALITEM_NODE		L"PRITEM"				//活用形ノード
	#define PRATICALTITLE_ELE		L"PRTITLE"				//活用形(活用形、人称、単数複数、性など）
	#define PRATICALTYPEID_ELE		L"PRTYPEID"				//活用方法ID
	#define PRATICALID_ELE			L"PRTICALID"			//活用形ID
	#define PRATICALWORD_ELE		L"PRWORD"				//活用形単語
	#define PRATICALREAD1_ELE		L"PRREAD1"				//活用形読み方１
	#define PRATICALREAD2_ELE		L"PRREAD2"				//活用形読み方２

	//単語表示データ格納フォルダ（一部）
	#define XMLFOLDERNAME			L"WDSch\\"				//パス名(相対)

	//Web検索
	#define WEB_BING			L"http://www.bing.com/search?q="							//Bing
	#define WEB_GOOGLE			L"http://www.google.co.jp/search?hl=ja&q="					//Google
	//Web百科事典
	#define WEB_ENCALTA			L"http://jp.encarta.msn.com/encnet/refpages/search.aspx?q="	//エンカルタ
	#define WEB_WIKI			L"http://ja.wikipedia.org/wiki/"							//Wiki

				


};
