//------------------------------------------------------------------------------
//	�P�ꎫ�T�@�P�ꎫ�T�r���A�[�p�N���X�@�w�b�_
//	Version 1.0		create date 2006/05/08
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WordDicCfg : �P�ꎫ�T�R���t�B�O
//------------------------------------------------------------------------------
#pragma once
using namespace WDDatas;

namespace WordDic
{
	public ref class WordDicCfg
	{
	public:
		//***** �敪�t�@�C�����
		String^ GroupFName;										//���ރt�@�C����

		//***** ����A���
		//�t�@�C�����
		String^ WordFNameA;										//�P��t�@�C���� ����A
		String^ MeanFNameA;										//�Ӗ��t�@�C���� ����A
		String^ TransFNameA;									//�|��t�@�C���� ����A
		String^ RelationFNameA;									//�֘A��t�@�C���� ����A
		String^ SegmentFNameA;									//�敪�t�@�C���� ����A

		//�P�ꌟ���C���f�b�N�X���
		Int32 Read1IdxA;										//�ǂݕ�1�C���f�b�N�X ����A
		Int32 Read2IdxA;										//�ǂݕ�2�C���f�b�N�X ����A

		//�P�ꌟ�����X�g���
		Int32 WordListSortA1;									//�P�ꃊ�X�g�̃\�[�g���P ����A( 1:Word�A2:Read1,3:Read2 )
		Int32 WordListSortA2;									//�P�ꃊ�X�g�̃\�[�g���Q ����A( 1:Word�A2:Read1,3:Read2 )

		//�P�ꃊ�X�g�\��
		Int32 WordListDispA;									//�P�ꃊ�X�g�\�� ����A
		Int32 WordListSubDispA;									//�P�ꃊ�X�g�T�u�\�� ����A

		//�P��\���e���v���[�g���
		String^ XSLTFNameA;										//XSL�t�@�C���� ����A

		//***** ����B���
		//�t�@�C�����
		String^ WordFNameB;										//�P��t�@�C���� ����B
		String^ MeanFNameB;										//�Ӗ��t�@�C���� ����B
		String^ TransFNameB;									//�|��t�@�C���� ����B
		String^ RelationFNameB;									//�֘A��t�@�C���� ����B
		String^ SegmentFNameB;									//�敪�t�@�C���� ����B

		//�P�ꌟ���C���f�b�N�X���
		Int32 Read1IdxB;										//�ǂݕ�1�C���f�b�N�X ����B
		Int32 Read2IdxB;										//�ǂݕ�1�C���f�b�N�X ����B

		//�P��\���e���v���[�g���
		String^ XSLTFNameB;										//XSL�t�@�C���� ����B

		//�P�ꌟ�����X�g�\�[�g���
		Int32 WordListSortB1;									//�P�ꃊ�X�g�̃\�[�g���P ����B( 1:Word�A2:Read1,3:Read2 )
		Int32 WordListSortB2;									//�P�ꃊ�X�g�̃\�[�g���Q ����B( 1:Word�A2:Read1,3:Read2 )

		//�P�ꃊ�X�g�\��
		Int32 WordListDispB;									//�P�ꃊ�X�g�\�� ����B
		Int32 WordListSubDispB;									//�P�ꃊ�X�g�T�u�\�� ����B1

		//�P�ꌟ�����b�Z�[�W
		String^ WordSchZero;									//�P�ꂪ������Ȃ���
		String^ WordSchAny;										//�P�ꂪ����������

	};
}
