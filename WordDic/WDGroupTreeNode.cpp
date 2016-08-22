//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアー用クラス　ソース
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDGroupTreeNode : 分類データのTreeView用TreeNode
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "WDGroupTreeNode.h"	//分類データ用TreeNode
#include "WDDatasDef.h"			//単語辞典データ定数定義

//------------------------------------------------------------------------------
//　コンストラクタ
//------------------------------------------------------------------------------
WordDic::WDGroupTreeNode::WDGroupTreeNode( void )
: TreeNode( )
{
	GroupGt = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
	GroupLt = gcnew array<Byte>(WDGROUP_GROUPLTLEN);
}

WordDic::WDGroupTreeNode::WDGroupTreeNode( String^ Text )
: TreeNode( Text )
{
	GroupGt = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
	GroupLt = gcnew array<Byte>(WDGROUP_GROUPLTLEN);
	if( Text != nullptr )
	{
		Name = String::Copy( Text );
	}
}

WordDic::WDGroupTreeNode::WDGroupTreeNode( WDGroup^ inGroup )
: TreeNode()
{
	if( inGroup == nullptr )
	{
		return;
	}else{
		GroupGt = inGroup->getGroupGt( nullptr );
		GroupLt = inGroup->getGroupLt( nullptr );
		String^ tmpStr;
		tmpStr = inGroup->getName( nullptr );
		if( tmpStr != nullptr )
		{
			Name = String::Copy( tmpStr );
			TreeNode::Text = Name;
		}
		tmpStr = inGroup->getShortName( nullptr );
		if( tmpStr != nullptr )
		{
			ShortName = String::Copy( tmpStr );
		}
	}
}
//------------------------------------------------------------------------------
//　アイテム操作
//------------------------------------------------------------------------------
//***** 分類大取得
array<Byte>^ WordDic::WDGroupTreeNode::getGroupGt( array<Byte>^ inData )
{
	if( inData != nullptr )
	{
		if( inData->Length < WDGROUP_GROUPGTLEN )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"コピー先データ長が短すぎます。" );
			tmpWDDataException->ErrorCode  = 20001;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}

		try
		{
			Buffer::BlockCopy( GroupGt, 0, inData, 0, WDGROUP_GROUPGTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データのコピーに失敗しました。", exp );
			tmpWDDataException->ErrorCode  = 20001;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
		return inData;

	}else{

		array<Byte>^ rtData = gcnew array<Byte>(WDGROUP_GROUPGTLEN);
		try
		{
			Buffer::BlockCopy( GroupGt, 0, rtData, 0, WDGROUP_GROUPGTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データのコピーに失敗しました。", exp );
			tmpWDDataException->ErrorCode  = 20001;
			tmpWDDataException->ErrorCode2 = 3;
			throw tmpWDDataException;
		}

		return rtData;
	}
}

//***** 分類小取得
array<Byte>^ WordDic::WDGroupTreeNode::getGroupLt( array<Byte>^ inData )
{
	if( inData != nullptr )
	{
		if( inData->Length < WDGROUP_GROUPLTLEN )
		{
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"コピー先データ長が短すぎます。" );
			tmpWDDataException->ErrorCode  = 20002;
			tmpWDDataException->ErrorCode2 = 1;
			throw tmpWDDataException;
		}

		try
		{
			Buffer::BlockCopy( GroupLt, 0, inData, 0, WDGROUP_GROUPLTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データのコピーに失敗しました。", exp );
			tmpWDDataException->ErrorCode  = 20002;
			tmpWDDataException->ErrorCode2 = 2;
			throw tmpWDDataException;
		}
		return inData;

	}else{

		array<Byte>^ rtData = gcnew array<Byte>(WDGROUP_GROUPLTLEN);
		try
		{
			Buffer::BlockCopy( GroupLt, 0, rtData, 0, WDGROUP_GROUPLTLEN );
		}catch( Exception^ exp ){
			WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
				L"データのコピーに失敗しました。", exp );
			tmpWDDataException->ErrorCode  = 20002;
			tmpWDDataException->ErrorCode2 = 3;
			throw tmpWDDataException;
		}

		return rtData;
	}
}

//***** 名称取得
String^ WordDic::WDGroupTreeNode::getName( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert(0, Name );
		return inData;
	}else{
		return String::Copy( Name );
	}
}

//***** 略称取得
String^ WordDic::WDGroupTreeNode::getShortName( String^ inData )
{
	if( inData != nullptr )
	{
		inData->Remove( 0 );
		inData->Insert(0, ShortName );
		return inData;
	}else{
		return String::Copy( ShortName );
	}
}

//------------------------------------------------------------------------------
//***** 分類大設定
void WordDic::WDGroupTreeNode::setGroupGt( array<Byte>^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類大が未設定です。" );
		tmpWDDataException->ErrorCode  = 20002;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length < WDGROUP_GROUPGTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類大が短すぎます。" );
		tmpWDDataException->ErrorCode  = 20002;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		Buffer::BlockCopy( inData, 0, GroupGt, 0, WDGROUP_GROUPGTLEN );
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類大の設定にしパイしました。", exp );
		tmpWDDataException->ErrorCode  = 20002;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}
}		

//***** 分類小設定
void WordDic::WDGroupTreeNode::setGroupLt( array<Byte>^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類小が未設定です。" );
		tmpWDDataException->ErrorCode  = 20005;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length < WDGROUP_GROUPLTLEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類小が短すぎます。" );
		tmpWDDataException->ErrorCode  = 20005;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		Buffer::BlockCopy( inData, 0, GroupLt, 0, WDGROUP_GROUPLTLEN );
	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"分類小の設定にしパイしました。", exp );
		tmpWDDataException->ErrorCode  = 20005;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}							

//***** 名称設定
void WordDic::WDGroupTreeNode::setName( String^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"名称が未設定です。" );
		tmpWDDataException->ErrorCode  = 20005;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDGROUP_NAMELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"名称が長すぎます。" );
		tmpWDDataException->ErrorCode  = 20005;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( Name != nullptr )
		{
			delete Name;
		}
		Name = String::Copy( inData );
		this->Text = inData;

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"名称の設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 20005;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}			

//***** 略称設定
void WordDic::WDGroupTreeNode::setShortName( String^ inData )
{
	//-- 引数チェック --//
	if( inData == nullptr )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"略称が未設定です。" );
		tmpWDDataException->ErrorCode  = 20006;
		tmpWDDataException->ErrorCode2 = 1;
		throw tmpWDDataException;
	}
	if( inData->Length *2 > WDGROUP_SHORTNAMELEN )
	{
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"略称が長すぎます。" );
		tmpWDDataException->ErrorCode  = 20006;
		tmpWDDataException->ErrorCode2 = 2;
		throw tmpWDDataException;
	}

	//-- データ設定 --//
	try
	{
		if( ShortName != nullptr )
		{
			delete ShortName;
		}
		ShortName = String::Copy( inData );

	}catch( Exception^ exp ){
		WDDatasException^ tmpWDDataException = gcnew WDDatasException( 
			L"略称の設定に失敗しました。", exp );
		tmpWDDataException->ErrorCode  = 20006;
		tmpWDDataException->ErrorCode2 = 3;
		throw tmpWDDataException;
	}

}
