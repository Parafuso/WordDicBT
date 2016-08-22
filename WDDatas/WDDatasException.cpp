//WDDatasException.h
//------------------------------------------------------------------------------
//	ISAMアクセスライブラリ　単語辞典データ用例外クラス クラス
//	Version 1.0		Create Date 2006/05/08 .net 2.0 で作成(新規)
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDDatasException		:例外クラス
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDDatasException.h"

//------------------------------------------------------------------------------
//	class	:WDDatasException	:例外クラス
//------------------------------------------------------------------------------
//***** コンストラクタ
WDDatas::WDDatasException::WDDatasException()
			: System::Exception(), ErrorCode(0), ErrorCode2(0)
{
};

//***** コンストラクタ
WDDatas::WDDatasException::WDDatasException(String^ msg)
			: System::Exception( msg ), ErrorCode(0), ErrorCode2(0)
{
};

//***** コンストラクタ
WDDatas::WDDatasException::WDDatasException(String^ msg, Exception^ inner )
			: System::Exception( msg, inner  ), ErrorCode(0), ErrorCode2(0)
{
};
