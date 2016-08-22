//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアー用クラス　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDWordListBox : 単語検索結果表示用リストボックス
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDWordList.h"			//単語検索結果表示用リストボックス
#include "WDDatasDef.h"			//単語辞典データ定数定義
#include "WDWordGrp.h"			//単語辞典情報

//------------------------------------------------------------------------------
//　ソート方法設定、確認
//------------------------------------------------------------------------------
//----- ソート順設定
void WordDic::WDWordList::setSortOrder( Int32 inSrtType,										
							Int32 inSrtWord1, Int32 inSrtWord2 )
{
	//-- 引数チェック --//
	if( inSrtType != schWord && inSrtType != schGrp )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ソートタイプが不正です。" );
		tmpWDDataException->ErrorCode  = 22001;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	if( inSrtWord1 < 0 && inSrtWord1 > 3 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ソート単語１が不正です。" );
		tmpWDDataException->ErrorCode  = 22001;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	if( inSrtWord2 < 0 && inSrtWord1 > 3 )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ソート単語２が不正です。" );
		tmpWDDataException->ErrorCode  = 22001;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

	//-- 項目設定
	srtType = inSrtType;
	srtWord1 = inSrtWord1;
	srtWord2 = inSrtWord2;
}

//----- ソートタイプ
Int32 WordDic::WDWordList::getSortType( void )
{
	return srtType;
}

//----- ソート単語１
Int32 WordDic::WDWordList::getSortWord1( void )
{
	return srtWord1;
}

//----- ソート単語２
Int32 WordDic::WDWordList::getSortWord2( void )
{
	return srtWord2;
}

//------------------------------------------------------------------------------
//　ソート
//------------------------------------------------------------------------------
//-- ソート
void WordDic::WDWordList::Sort()
{
	//-- アイテムが1つ以下なら何もしない
	if( Items->Count > 1 )
	{
		return;
	}

	try
	{
	    Int32 tmpCnt = Items->Count - 1;
		while( tmpCnt  >= 1 )
		{
			WDWordGrp^ chkWDWordGrp1 = safe_cast<WDWordGrp^>( Items[ tmpCnt ] );
			WDWordGrp^ chkWDWordGrp2 = safe_cast<WDWordGrp^>( Items[ tmpCnt -1 ] );

			//-- グループ検索時
			if( srtType == schGrp )
			{
				WDMean^ tmpWDMean1 = chkWDWordGrp1->getSchMean();
				WDMean^ tmpWDMean2 = chkWDWordGrp2->getSchMean();

				//アイテム１：意味内並び替え指定無し、アイテム２：意味内並べ替え指定あり。
				//終了
				if( tmpWDMean1->getGroupRank() == 0 &&
					tmpWDMean2->getGroupRank() != 0 )
				{
					return;

				//アイテム１：意味内並び替え指定あり、アイテム２：意味内並べ替え指定なし。
				//順序を入れ替える
				}else if( tmpWDMean1->getGroupRank() != 0 &&
						tmpWDMean2->getGroupRank() == 0 )		{
					Items[ tmpCnt ] = chkWDWordGrp2;
					Items[ tmpCnt - 1 ] = chkWDWordGrp1;
					break;

				//アイテム１並び替え順序 > アイテム２並び替え順序
				//終了
				}else if( tmpWDMean1->getGroupRank() > tmpWDMean2->getGroupRank() ) {
					return;
		
				//アイテム１並び替え順序 < アイテム２並び替え順序
				//順序を入れ替える
				}else if( tmpWDMean1->getGroupRank() < tmpWDMean2->getGroupRank() ) {
					Items[ tmpCnt ] = chkWDWordGrp2;
					Items[ tmpCnt - 1 ] = chkWDWordGrp1;
					break;
				}
	
			}

			//言葉で並び替え
			for( Int32 i = 0; i < 2; i++ )
			{
				//言葉のソート項目を決定
				Int32 schWord;
				Int32 cmpVal;

				WDWord^ chkWord1 = chkWDWordGrp1->getBaseWord();
				WDWord^ chkWord2 = chkWDWordGrp2->getBaseWord();
		
				if( i == 0 )
				{
					schWord = srtWord1;
				}else{
					schWord = srtWord2;
				}
					
				//ソート単語が未指定なら終了
				if( schWord == 0 )
				{
					return;
				}

				//単語
				if( schWord == 1)
				{
					cmpVal = String::Compare( chkWord1->getWord( nullptr ), chkWord2->getWord( nullptr ) );
					if( cmpVal < 0 )
					{
						Items[ tmpCnt ] = chkWDWordGrp2;
						Items[ tmpCnt - 1 ] = chkWDWordGrp1;
						break;
					}else if( cmpVal > 0 ) {
						return;
					}
		
				//読み方１
				}else if( schWord == 2 ) {						break;
					cmpVal = String::Compare( chkWord1->getRead1( nullptr ), chkWord2->getRead1( nullptr ) );
					if( cmpVal < 0 )
					{
						Items[ tmpCnt ] = chkWDWordGrp2;
						Items[ tmpCnt - 1 ] = chkWDWordGrp1;
						break;
					}else if( cmpVal > 0 ) {
						return;
					}
		
				//読み方２
				}else if( schWord == 3 ) {
					cmpVal = String::Compare( chkWord1->getRead2( nullptr ), chkWord2->getRead2( nullptr ) );
					if( cmpVal < 0 )
					{
						Items[ tmpCnt ] = chkWDWordGrp2;
						Items[ tmpCnt - 1 ] = chkWDWordGrp1;
						break;
					}else if( cmpVal > 0 ) {
						return;
					}
				
				}
			}

			//カウンター減算
			tmpCnt--;
		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ソート時にエラーが発生しました。", exp );
		tmpWDDataException->ErrorCode  = 22002;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
}
