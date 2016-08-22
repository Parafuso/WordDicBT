//WDDatasException.h
//------------------------------------------------------------------------------
//	ISAMアクセスライブラリ　単語辞典データ用例外クラス ヘッダ
//	Version 1.0		Create Date 2006/05/08 .net 2.0 で作成(新規)
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDDatasException		:例外クラス
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
//	class	:WDDatasException	:例外クラス
//------------------------------------------------------------------------------
namespace WDDatas
{
	public ref class WDDatasException :public System::Exception
	{
	public :
		//コンストラクタ
		WDDatasException( );
		WDDatasException(String^ msg);
		WDDatasException(String^ msg, Exception^ inner );

		//メンバ
		int	ErrorCode;
		int	ErrorCode2;
	};
}