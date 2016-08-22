//------------------------------------------------------------------------------
//	単語辞典　単語辞典ビュアー用クラス　ヘッダ
//	Version 1.0		create date 2006/05/08
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDGroupTreeNode : 分類データのTreeView用TreeNode
//------------------------------------------------------------------------------
#pragma once

using namespace WDDatas;

namespace WordDic
{
	public ref class WDGroupTreeNode : public System::Windows::Forms::TreeNode
	{
	public :
		//--  コンストラクタ --//
		WDGroupTreeNode();
		WDGroupTreeNode( String^ Text );
		WDGroupTreeNode( WDGroup^ inGroup );

		//-- アイテム操作 --//
		array<Byte>^ getGroupGt( array<Byte>^ inData );					//分類大取得
		array<Byte>^ getGroupLt( array<Byte>^ inData );					//分類小取得
		String^		 getName( String^ inData );							//名称取得
		String^		 getShortName( String^ inData );					//略称取得


		void setGroupGt( array<Byte>^ inData );							//分類大設定
		void setGroupLt( array<Byte>^ inData );							//分類小設定
		void setName( String^ inData );									//名称設定
		void setShortName( String^ inData );							//略称設定

	private :
		array<Byte>^ GroupGt;
		array<Byte>^ GroupLt;
		String^ Name;
		String^ ShortName;
	};
}