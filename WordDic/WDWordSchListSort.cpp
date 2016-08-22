//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアー用クラス　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDWordSchListComparer : 単語検索結果表示用リストボックスソート
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasDef.h"			//単語辞典データ定数定義
#include "WDWordSchListSort.h"	//単語検索結果表示用リストボックスソート

//------------------------------------------------------------------------------
//　ソート方法設定、確認
//------------------------------------------------------------------------------
//----- ソート順設定
void WordDic::WDWordSchListComparer::setSortOrder( Int32 inSrtType,										
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
Int32 WordDic::WDWordSchListComparer::getSortType( void )
{
	return srtType;
}

//----- ソート単語１
Int32 WordDic::WDWordSchListComparer::getSortWord1( void )
{
	return srtWord1;
}

//----- ソート単語２
Int32 WordDic::WDWordSchListComparer::getSortWord2( void )
{
	return srtWord2;
}

//------------------------------------------------------------------------------
//　ソート
//------------------------------------------------------------------------------
//-- ソート
Int32 WordDic::WDWordSchListComparer::Compare(Object^ x, Object^ y)
{
	Int32 Result;

	WDWordGrp^ tmpWDWordGrp1 = safe_cast<WDWordGrp^>(x);
	WDWordGrp^ tmpWDWordGrp2 = safe_cast<WDWordGrp^>(y);


	//-- Xがnullptrの場合
	if (tmpWDWordGrp1 == nullptr)
	{
		if (tmpWDWordGrp2 == nullptr)
		{
			return 0;
        }else{
			//X = nullptr , Y != nullptr ->Yが小さい(先に来る)
			return 1;
		}
	}

	//-- X != nullptr , Y = nullptr ->Xが小さい(先に来る)
	if( tmpWDWordGrp2 == nullptr )
	{
		return -1;
	}


	try
	{

		//-- グループ検索時
		if( srtType == schGrp )
		{
			//アイテム１：意味内並び替え指定無し、アイテム２：意味内並べ替え指定あり。
			//終了
			if( tmpWDWordGrp1->getSchGroupRank() == 0 &&
				tmpWDWordGrp2->getSchGroupRank() != 0 )
			{
				return 1;

			//アイテム１：意味内並び替え指定あり、アイテム２：意味内並べ替え指定なし。
			//順序を入れ替える
			}else if( tmpWDWordGrp1->getSchGroupRank() != 0 &&
					  tmpWDWordGrp2->getSchGroupRank() == 0 )		{
				return -1;

			//アイテム１並び替え順序 > アイテム２並び替え順序
			//終了
			}else if( tmpWDWordGrp1->getSchGroupRank() > tmpWDWordGrp2->getSchGroupRank() ) {
				return 1;
		
			//アイテム１並び替え順序 < アイテム２並び替え順序
			//順序を入れ替える
			}else if( tmpWDWordGrp1->getSchGroupRank() < tmpWDWordGrp2->getSchGroupRank() ) {
				return -1;
			}
	
		}

		//言葉で並び替え
		for( Int32 i = 0; i < 2; i++ )
		{
			//言葉のソート項目を決定
			Int32 schWord;

			WDWord^ chkWord1 = tmpWDWordGrp1->getBaseWord();
			WDWord^ chkWord2 = tmpWDWordGrp2->getBaseWord();
		
			if( i == 0 )
			{
				schWord = srtWord1;
			}else{
				schWord = srtWord2;
			}
					
			//ソート単語が未指定なら終了
			if( schWord == 0 )
			{
				return 0;
			}

			//単語
			if( schWord == 1)
			{
				Result = String::Compare( chkWord1->getWord( nullptr ), chkWord2->getWord( nullptr ) );
					if( Result < 0 )
					{
						return -1;

					}else if( Result > 0 ) {
						return 1;

					}
		
			//読み方１
			}else if( schWord == 2 ) {
				Result = String::Compare( chkWord1->getRead1( nullptr ), chkWord2->getRead1( nullptr ) );
				if( Result < 0 ) 
				{
						return -1;

				}else if( Result > 0 ) {
						return 1;

				}
		
			//読み方２
			}else if( schWord == 3 ) {
				Result = String::Compare( chkWord1->getRead2( nullptr ), chkWord2->getRead2( nullptr ) );
				if( Result < 0 )
				{
						return -1;

				}else if( Result > 0 ) {
						return 1;

				}
				
			}

		}

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"ソート時にエラーが発生しました。", exp );
		tmpWDDataException->ErrorCode  = 22002;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}

	//-- 完全一致 --//
	return 0;
}
