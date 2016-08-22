//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�p�N���X�@�w�b�_
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDGroupTreeNode : ���ރf�[�^��TreeView�pTreeNode
//------------------------------------------------------------------------------
#pragma once

using namespace WDDatas;

namespace WordDic
{
	public ref class WDGroupTreeNode : public System::Windows::Forms::TreeNode
	{
	public :
		//--  �R���X�g���N�^ --//
		WDGroupTreeNode();
		WDGroupTreeNode( String^ Text );
		WDGroupTreeNode( WDGroup^ inGroup );

		//-- �A�C�e������ --//
		array<Byte>^ getGroupGt( array<Byte>^ inData );					//���ޑ�擾
		array<Byte>^ getGroupLt( array<Byte>^ inData );					//���ޏ��擾
		String^		 getName( String^ inData );							//���̎擾
		String^		 getShortName( String^ inData );					//���̎擾


		void setGroupGt( array<Byte>^ inData );							//���ޑ�ݒ�
		void setGroupLt( array<Byte>^ inData );							//���ޏ��ݒ�
		void setName( String^ inData );									//���̐ݒ�
		void setShortName( String^ inData );							//���̐ݒ�

	private :
		array<Byte>^ GroupGt;
		array<Byte>^ GroupLt;
		String^ Name;
		String^ ShortName;
	};
}