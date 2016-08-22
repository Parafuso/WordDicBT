//WordDicException.h
//------------------------------------------------------------------------------
//	ISAMアクセスライブラリ　単語辞典用例外クラス ヘッダ
//	Version 1.0		Create Date 2006/05/08 .net 2.0 で作成(新規)
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WordDicException		:例外クラス
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
//	class	:WordDicException	:例外クラス
//------------------------------------------------------------------------------
namespace WordDic
{
	public ref class WordDicException :public System::Exception
	{
	public :
		//コンストラクタ
		WordDicException( );
		WordDicException(String^ msg);
		WordDicException(String^ msg, Exception^ inner );

		//メンバ
		int	ErrorCode;
		int	ErrorCode2;
	};
}