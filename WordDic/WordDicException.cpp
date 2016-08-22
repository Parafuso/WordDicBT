//WordDicException.h
//------------------------------------------------------------------------------
//	ISAMアクセスライブラリ　単語辞典用例外クラス クラス
//	Version 1.0		Create Date 2006/05/08 .net 2.0 で作成(新規)
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WordDicException		:例外クラス
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WordDicException.h"

//------------------------------------------------------------------------------
//	class	:WordDicException	:例外クラス
//------------------------------------------------------------------------------
//***** コンストラクタ
WordDic::WordDicException::WordDicException()
			: System::Exception(), ErrorCode(0), ErrorCode2(0)
{
};

//***** コンストラクタ
WordDic::WordDicException::WordDicException(String^ msg)
			: System::Exception( msg ), ErrorCode(0), ErrorCode2(0)
{
};

//***** コンストラクタ
WordDic::WordDicException::WordDicException(String^ msg, Exception^ inner )
			: System::Exception( msg, inner  ), ErrorCode(0), ErrorCode2(0)
{
};
