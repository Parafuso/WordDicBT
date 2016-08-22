//------------------------------------------------------------------------------
//	���Ƃ΂̎��T�@���Ƃ΂̎��T�r���[�A�A�v���P�[�V�����@�w�b�_
//	Version 1.0.0.0			create date 2006/05/08
//	Version 1.0.1.0			Change date 2009/09/13
//	Version 1.0.1.1			Change date 2010/10/22	ToolStripMenuItemWebEncycro1 �폜 �E�N���b�N���j���[�G���J���^���폜�i�C�x���g�֐��c���Ă���j
//	Version 1.0.3.0			Change date 2010/11/16�@�^�X�N�o�[����N���b�v�{�[�h�̓��e�ŒP�ꌟ���\�ɂ���B
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	Windows Form�̃A�v���P�[�V����
//------------------------------------------------------------------------------
#pragma once
#include "WDConfig.h"			//�ݒ���
#include "WDVerDialog.h"		//�o�[�W�����_�C�A���O

#include "WordDicCfg.h"			//���t�̎��T �����ݒ�
#include "WDWordGrp.h"			//�P��O���[�v���
#include "WDGroupTreeNode.h"	//�O���[�v�c���[�m�[�h
#include "WDWordSchListSort.h"	//�P�ꌟ�����ʕ\���p���X�g�{�b�N�X�\�[�g


namespace WordDic {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Microsoft::WindowsAPICodePack::Taskbar; 

	using namespace FJIsam;

	/// <summary>
	/// Form1 �̊T�v
	///
	/// �x��: ���̃N���X�̖��O��ύX����ꍇ�A���̃N���X���ˑ����邷�ׂĂ� .resx �t�@�C���Ɋ֘A�t����ꂽ
	///          �}�l�[�W ���\�[�X �R���p�C�� �c�[���ɑ΂��� 'Resource File Name' �v���p�e�B��
	///          �ύX����K�v������܂��B���̕ύX���s��Ȃ��ƁA
	///          �f�U�C�i�ƁA���̃t�H�[���Ɋ֘A�t����ꂽ���[�J���C�Y�ς݃��\�[�X�Ƃ��A
	///          ���������݂ɗ��p�ł��Ȃ��Ȃ�܂��B
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		//-- �R���X�g���N�^ --//
		Form1(void);

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~Form1();

	private: System::Windows::Forms::ToolStrip^  toolStripMain;
	private: System::Windows::Forms::ToolStripButton^  QuittoolStripButton;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripButton^  CopyCToolStripButton;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonConfig;
	private: System::Windows::Forms::ToolStripButton^  HelpLToolStripButton;


	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::SplitContainer^  splitContainerSch;

	private: System::Windows::Forms::TabControl^  tabCtrlSearch;
	private: System::Windows::Forms::TabPage^  tabPageSchWord;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanelSchWordSel;
	private: System::Windows::Forms::Panel^  panelSchWord;



	private: System::Windows::Forms::TextBox^  textBoxSchWord;

	private: System::Windows::Forms::Button^  buttonSchWord;
	private: System::Windows::Forms::Label^  labelSchWord;
	private: System::Windows::Forms::TabPage^  tabPageSchGroup;
	private: System::Windows::Forms::RadioButton^  radioButtonWordA;
	private: System::Windows::Forms::RadioButton^  radioButtonWordB;

	private: System::Windows::Forms::ListBox^  listBoxWordList;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanelWordListBtns2;


	private: System::Windows::Forms::Button^  buttonWordListClear;


	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanelGroupLang;
	private: System::Windows::Forms::RadioButton^  radioButtonGroupA;
	private: System::Windows::Forms::RadioButton^  radioButtonGroupB;
	private: System::Windows::Forms::TreeView^  treeViewGroupTree;

	private: System::Windows::Forms::WebBrowser^  webBrowserBook;
	private: System::Windows::Forms::StatusStrip^  statusStripMain;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelSchWordCnt;

	private: System::Windows::Forms::ContextMenuStrip^  contextMenuHelp;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItemHelpMan;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItemHelpVer;

	//Book�̈�p�E�N���b�N���j���[
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripBook;					//Book�̈�E�N���b�N���j���[

	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemBookCopy;				//�E�N���b�N���j���[�R�s�[

	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemWebSearch;			//�E�N���b�N���j���[Web�T�[�`���[�g
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItemWebSchSite1;			//�E�N���b�N���j���[Web�T�[�`�P
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItemWebSchSite2;			//�E�N���b�N���j���[Web�T�[�`�Q

	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItemWebEncyclopedia;		//�E�N���b�N���j���[�S�Ȏ��T���[�g
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItemWebEncycro2;			//�E�N���b�N���j���[�S�Ȏ��T�Q


	private: WDConfig^		dlgWDConfig;											//�ݒ�_�C�A���O
	private: WDVerDialog^ dlgWDVerDialog;											//�o�[�W�����_�C�A���O


	private: System::ComponentModel::IContainer^  components;

	//�^�X�N�o�[�{�^���p�{�^��
	private: Microsoft::WindowsAPICodePack::Taskbar::ThumbnailToolBarManager^ ThumbnailToolBarManagerWD;	//�^�X�N�o�[�{�^���}�l�[�W���[
	private: Microsoft::WindowsAPICodePack::Taskbar::ThumbnailToolBarButton^ ThumbButtonSchLangA;	//�^�X�N�o�[�{�^���F����P�{�^��						
	private: Microsoft::WindowsAPICodePack::Taskbar::ThumbnailToolBarButton^ ThumbButtonSchLangB;	//�^�X�N�o�[�{�^���F����Q�{�^��




	protected: 

	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�ϐ��ł��B
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->toolStripMain = (gcnew System::Windows::Forms::ToolStrip());
			this->QuittoolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->CopyCToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripButtonConfig = (gcnew System::Windows::Forms::ToolStripButton());
			this->HelpLToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainerSch = (gcnew System::Windows::Forms::SplitContainer());
			this->tabCtrlSearch = (gcnew System::Windows::Forms::TabControl());
			this->tabPageSchWord = (gcnew System::Windows::Forms::TabPage());
			this->flowLayoutPanelSchWordSel = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->radioButtonWordA = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonWordB = (gcnew System::Windows::Forms::RadioButton());
			this->panelSchWord = (gcnew System::Windows::Forms::Panel());
			this->textBoxSchWord = (gcnew System::Windows::Forms::TextBox());
			this->buttonSchWord = (gcnew System::Windows::Forms::Button());
			this->labelSchWord = (gcnew System::Windows::Forms::Label());
			this->tabPageSchGroup = (gcnew System::Windows::Forms::TabPage());
			this->treeViewGroupTree = (gcnew System::Windows::Forms::TreeView());
			this->flowLayoutPanelGroupLang = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->radioButtonGroupA = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonGroupB = (gcnew System::Windows::Forms::RadioButton());
			this->listBoxWordList = (gcnew System::Windows::Forms::ListBox());
			this->flowLayoutPanelWordListBtns2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->buttonWordListClear = (gcnew System::Windows::Forms::Button());
			this->webBrowserBook = (gcnew System::Windows::Forms::WebBrowser());
			this->contextMenuStripBook = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->toolStripMenuItemBookCopy = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItemWebSearch = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItemWebSchSite1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItemWebSchSite2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItemWebEncyclopedia = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItemWebEncycro2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statusStripMain = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabelSchWordCnt = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->contextMenuHelp = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->ToolStripMenuItemHelpMan = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItemHelpVer = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMain->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainerSch))->BeginInit();
			this->splitContainerSch->Panel1->SuspendLayout();
			this->splitContainerSch->Panel2->SuspendLayout();
			this->splitContainerSch->SuspendLayout();
			this->tabCtrlSearch->SuspendLayout();
			this->tabPageSchWord->SuspendLayout();
			this->flowLayoutPanelSchWordSel->SuspendLayout();
			this->panelSchWord->SuspendLayout();
			this->tabPageSchGroup->SuspendLayout();
			this->flowLayoutPanelGroupLang->SuspendLayout();
			this->flowLayoutPanelWordListBtns2->SuspendLayout();
			this->contextMenuStripBook->SuspendLayout();
			this->statusStripMain->SuspendLayout();
			this->contextMenuHelp->SuspendLayout();
			this->SuspendLayout();
			// 
			// toolStripMain
			// 
			this->toolStripMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->QuittoolStripButton, 
				this->toolStripSeparator1, this->CopyCToolStripButton, this->toolStripSeparator2, this->toolStripButtonConfig, this->HelpLToolStripButton});
			resources->ApplyResources(this->toolStripMain, L"toolStripMain");
			this->toolStripMain->Name = L"toolStripMain";
			// 
			// QuittoolStripButton
			// 
			resources->ApplyResources(this->QuittoolStripButton, L"QuittoolStripButton");
			this->QuittoolStripButton->Name = L"QuittoolStripButton";
			this->QuittoolStripButton->Click += gcnew System::EventHandler(this, &Form1::�I��toolStripButton_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			resources->ApplyResources(this->toolStripSeparator1, L"toolStripSeparator1");
			// 
			// CopyCToolStripButton
			// 
			this->CopyCToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->CopyCToolStripButton, L"CopyCToolStripButton");
			this->CopyCToolStripButton->Name = L"CopyCToolStripButton";
			this->CopyCToolStripButton->Click += gcnew System::EventHandler(this, &Form1::�R�s�[CToolStripButton_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			resources->ApplyResources(this->toolStripSeparator2, L"toolStripSeparator2");
			// 
			// toolStripButtonConfig
			// 
			this->toolStripButtonConfig->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->toolStripButtonConfig, L"toolStripButtonConfig");
			this->toolStripButtonConfig->Name = L"toolStripButtonConfig";
			this->toolStripButtonConfig->Click += gcnew System::EventHandler(this, &Form1::toolStripButtonConfig_Click);
			// 
			// HelpLToolStripButton
			// 
			this->HelpLToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			resources->ApplyResources(this->HelpLToolStripButton, L"HelpLToolStripButton");
			this->HelpLToolStripButton->Name = L"HelpLToolStripButton";
			this->HelpLToolStripButton->Click += gcnew System::EventHandler(this, &Form1::�w���vLToolStripButton_Click);
			// 
			// splitContainer1
			// 
			resources->ApplyResources(this->splitContainer1, L"splitContainer1");
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->splitContainerSch);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->webBrowserBook);
			// 
			// splitContainerSch
			// 
			resources->ApplyResources(this->splitContainerSch, L"splitContainerSch");
			this->splitContainerSch->Name = L"splitContainerSch";
			// 
			// splitContainerSch.Panel1
			// 
			this->splitContainerSch->Panel1->Controls->Add(this->tabCtrlSearch);
			// 
			// splitContainerSch.Panel2
			// 
			this->splitContainerSch->Panel2->Controls->Add(this->listBoxWordList);
			this->splitContainerSch->Panel2->Controls->Add(this->flowLayoutPanelWordListBtns2);
			// 
			// tabCtrlSearch
			// 
			this->tabCtrlSearch->Controls->Add(this->tabPageSchWord);
			this->tabCtrlSearch->Controls->Add(this->tabPageSchGroup);
			resources->ApplyResources(this->tabCtrlSearch, L"tabCtrlSearch");
			this->tabCtrlSearch->Name = L"tabCtrlSearch";
			this->tabCtrlSearch->SelectedIndex = 0;
			// 
			// tabPageSchWord
			// 
			this->tabPageSchWord->Controls->Add(this->flowLayoutPanelSchWordSel);
			this->tabPageSchWord->Controls->Add(this->panelSchWord);
			this->tabPageSchWord->Controls->Add(this->labelSchWord);
			resources->ApplyResources(this->tabPageSchWord, L"tabPageSchWord");
			this->tabPageSchWord->Name = L"tabPageSchWord";
			this->tabPageSchWord->UseVisualStyleBackColor = true;
			// 
			// flowLayoutPanelSchWordSel
			// 
			this->flowLayoutPanelSchWordSel->Controls->Add(this->radioButtonWordA);
			this->flowLayoutPanelSchWordSel->Controls->Add(this->radioButtonWordB);
			resources->ApplyResources(this->flowLayoutPanelSchWordSel, L"flowLayoutPanelSchWordSel");
			this->flowLayoutPanelSchWordSel->Name = L"flowLayoutPanelSchWordSel";
			// 
			// radioButtonWordA
			// 
			resources->ApplyResources(this->radioButtonWordA, L"radioButtonWordA");
			this->radioButtonWordA->Checked = true;
			this->radioButtonWordA->Name = L"radioButtonWordA";
			this->radioButtonWordA->TabStop = true;
			this->radioButtonWordA->UseVisualStyleBackColor = true;
			// 
			// radioButtonWordB
			// 
			resources->ApplyResources(this->radioButtonWordB, L"radioButtonWordB");
			this->radioButtonWordB->Name = L"radioButtonWordB";
			this->radioButtonWordB->UseVisualStyleBackColor = true;
			// 
			// panelSchWord
			// 
			this->panelSchWord->Controls->Add(this->textBoxSchWord);
			this->panelSchWord->Controls->Add(this->buttonSchWord);
			resources->ApplyResources(this->panelSchWord, L"panelSchWord");
			this->panelSchWord->Name = L"panelSchWord";
			// 
			// textBoxSchWord
			// 
			resources->ApplyResources(this->textBoxSchWord, L"textBoxSchWord");
			this->textBoxSchWord->Name = L"textBoxSchWord";
			this->textBoxSchWord->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::textBoxSchWord_KeyPress);
			// 
			// buttonSchWord
			// 
			resources->ApplyResources(this->buttonSchWord, L"buttonSchWord");
			this->buttonSchWord->Name = L"buttonSchWord";
			this->buttonSchWord->UseVisualStyleBackColor = true;
			this->buttonSchWord->Click += gcnew System::EventHandler(this, &Form1::buttonSchWord_Click);
			// 
			// labelSchWord
			// 
			resources->ApplyResources(this->labelSchWord, L"labelSchWord");
			this->labelSchWord->Name = L"labelSchWord";
			// 
			// tabPageSchGroup
			// 
			this->tabPageSchGroup->Controls->Add(this->treeViewGroupTree);
			this->tabPageSchGroup->Controls->Add(this->flowLayoutPanelGroupLang);
			resources->ApplyResources(this->tabPageSchGroup, L"tabPageSchGroup");
			this->tabPageSchGroup->Name = L"tabPageSchGroup";
			this->tabPageSchGroup->UseVisualStyleBackColor = true;
			// 
			// treeViewGroupTree
			// 
			resources->ApplyResources(this->treeViewGroupTree, L"treeViewGroupTree");
			this->treeViewGroupTree->Name = L"treeViewGroupTree";
			this->treeViewGroupTree->DoubleClick += gcnew System::EventHandler(this, &Form1::treeViewGroupTree_DoubleClick);
			// 
			// flowLayoutPanelGroupLang
			// 
			this->flowLayoutPanelGroupLang->Controls->Add(this->radioButtonGroupA);
			this->flowLayoutPanelGroupLang->Controls->Add(this->radioButtonGroupB);
			resources->ApplyResources(this->flowLayoutPanelGroupLang, L"flowLayoutPanelGroupLang");
			this->flowLayoutPanelGroupLang->Name = L"flowLayoutPanelGroupLang";
			// 
			// radioButtonGroupA
			// 
			resources->ApplyResources(this->radioButtonGroupA, L"radioButtonGroupA");
			this->radioButtonGroupA->Checked = true;
			this->radioButtonGroupA->Name = L"radioButtonGroupA";
			this->radioButtonGroupA->TabStop = true;
			this->radioButtonGroupA->UseVisualStyleBackColor = true;
			// 
			// radioButtonGroupB
			// 
			resources->ApplyResources(this->radioButtonGroupB, L"radioButtonGroupB");
			this->radioButtonGroupB->Name = L"radioButtonGroupB";
			this->radioButtonGroupB->UseVisualStyleBackColor = true;
			// 
			// listBoxWordList
			// 
			this->listBoxWordList->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->listBoxWordList, L"listBoxWordList");
			this->listBoxWordList->FormattingEnabled = true;
			this->listBoxWordList->Name = L"listBoxWordList";
			this->listBoxWordList->DoubleClick += gcnew System::EventHandler(this, &Form1::listBoxWordList_DoubleClick);
			// 
			// flowLayoutPanelWordListBtns2
			// 
			this->flowLayoutPanelWordListBtns2->Controls->Add(this->buttonWordListClear);
			resources->ApplyResources(this->flowLayoutPanelWordListBtns2, L"flowLayoutPanelWordListBtns2");
			this->flowLayoutPanelWordListBtns2->Name = L"flowLayoutPanelWordListBtns2";
			// 
			// buttonWordListClear
			// 
			resources->ApplyResources(this->buttonWordListClear, L"buttonWordListClear");
			this->buttonWordListClear->Name = L"buttonWordListClear";
			this->buttonWordListClear->UseVisualStyleBackColor = true;
			this->buttonWordListClear->Click += gcnew System::EventHandler(this, &Form1::buttonWordListClear_Click);
			// 
			// webBrowserBook
			// 
			this->webBrowserBook->ContextMenuStrip = this->contextMenuStripBook;
			resources->ApplyResources(this->webBrowserBook, L"webBrowserBook");
			this->webBrowserBook->IsWebBrowserContextMenuEnabled = false;
			this->webBrowserBook->MinimumSize = System::Drawing::Size(20, 18);
			this->webBrowserBook->Name = L"webBrowserBook";
			this->webBrowserBook->Url = (gcnew System::Uri(L"", System::UriKind::Relative));
			this->webBrowserBook->Navigating += gcnew System::Windows::Forms::WebBrowserNavigatingEventHandler(this, &Form1::webBrowserBook_Navigating);
			// 
			// contextMenuStripBook
			// 
			this->contextMenuStripBook->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripMenuItemBookCopy, 
				this->toolStripMenuItemWebSearch, this->ToolStripMenuItemWebEncyclopedia});
			this->contextMenuStripBook->Name = L"contextMenuStripNote";
			resources->ApplyResources(this->contextMenuStripBook, L"contextMenuStripBook");
			// 
			// toolStripMenuItemBookCopy
			// 
			this->toolStripMenuItemBookCopy->Name = L"toolStripMenuItemBookCopy";
			resources->ApplyResources(this->toolStripMenuItemBookCopy, L"toolStripMenuItemBookCopy");
			this->toolStripMenuItemBookCopy->Click += gcnew System::EventHandler(this, &Form1::toolStripMenuItemBookCopy_Click);
			// 
			// toolStripMenuItemWebSearch
			// 
			this->toolStripMenuItemWebSearch->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->ToolStripMenuItemWebSchSite1, 
				this->ToolStripMenuItemWebSchSite2});
			this->toolStripMenuItemWebSearch->Name = L"toolStripMenuItemWebSearch";
			resources->ApplyResources(this->toolStripMenuItemWebSearch, L"toolStripMenuItemWebSearch");
			// 
			// ToolStripMenuItemWebSchSite1
			// 
			this->ToolStripMenuItemWebSchSite1->Name = L"ToolStripMenuItemWebSchSite1";
			resources->ApplyResources(this->ToolStripMenuItemWebSchSite1, L"ToolStripMenuItemWebSchSite1");
			this->ToolStripMenuItemWebSchSite1->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItemWebSchSite1_Click);
			// 
			// ToolStripMenuItemWebSchSite2
			// 
			this->ToolStripMenuItemWebSchSite2->Name = L"ToolStripMenuItemWebSchSite2";
			resources->ApplyResources(this->ToolStripMenuItemWebSchSite2, L"ToolStripMenuItemWebSchSite2");
			this->ToolStripMenuItemWebSchSite2->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItemWebSchSite2_Click);
			// 
			// ToolStripMenuItemWebEncyclopedia
			// 
			this->ToolStripMenuItemWebEncyclopedia->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->ToolStripMenuItemWebEncycro2});
			this->ToolStripMenuItemWebEncyclopedia->Name = L"ToolStripMenuItemWebEncyclopedia";
			resources->ApplyResources(this->ToolStripMenuItemWebEncyclopedia, L"ToolStripMenuItemWebEncyclopedia");
			// 
			// ToolStripMenuItemWebEncycro2
			// 
			this->ToolStripMenuItemWebEncycro2->Name = L"ToolStripMenuItemWebEncycro2";
			resources->ApplyResources(this->ToolStripMenuItemWebEncycro2, L"ToolStripMenuItemWebEncycro2");
			this->ToolStripMenuItemWebEncycro2->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItemWebEncycro2_Click);
			// 
			// statusStripMain
			// 
			this->statusStripMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toolStripStatusLabelSchWordCnt});
			resources->ApplyResources(this->statusStripMain, L"statusStripMain");
			this->statusStripMain->Name = L"statusStripMain";
			// 
			// toolStripStatusLabelSchWordCnt
			// 
			this->toolStripStatusLabelSchWordCnt->Name = L"toolStripStatusLabelSchWordCnt";
			resources->ApplyResources(this->toolStripStatusLabelSchWordCnt, L"toolStripStatusLabelSchWordCnt");
			// 
			// contextMenuHelp
			// 
			this->contextMenuHelp->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->ToolStripMenuItemHelpMan, 
				this->ToolStripMenuItemHelpVer});
			this->contextMenuHelp->Name = L"contextMenuHelp";
			resources->ApplyResources(this->contextMenuHelp, L"contextMenuHelp");
			// 
			// ToolStripMenuItemHelpMan
			// 
			this->ToolStripMenuItemHelpMan->Name = L"ToolStripMenuItemHelpMan";
			resources->ApplyResources(this->ToolStripMenuItemHelpMan, L"ToolStripMenuItemHelpMan");
			this->ToolStripMenuItemHelpMan->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItemHelpMan_Click);
			// 
			// ToolStripMenuItemHelpVer
			// 
			this->ToolStripMenuItemHelpVer->Name = L"ToolStripMenuItemHelpVer";
			resources->ApplyResources(this->ToolStripMenuItemHelpVer, L"ToolStripMenuItemHelpVer");
			this->ToolStripMenuItemHelpVer->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItemHelpVer_Click);
			// 
			// Form1
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->toolStripMain);
			this->Controls->Add(this->statusStripMain);
			this->Name = L"Form1";
			this->toolStripMain->ResumeLayout(false);
			this->toolStripMain->PerformLayout();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->splitContainerSch->Panel1->ResumeLayout(false);
			this->splitContainerSch->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainerSch))->EndInit();
			this->splitContainerSch->ResumeLayout(false);
			this->tabCtrlSearch->ResumeLayout(false);
			this->tabPageSchWord->ResumeLayout(false);
			this->tabPageSchWord->PerformLayout();
			this->flowLayoutPanelSchWordSel->ResumeLayout(false);
			this->flowLayoutPanelSchWordSel->PerformLayout();
			this->panelSchWord->ResumeLayout(false);
			this->panelSchWord->PerformLayout();
			this->tabPageSchGroup->ResumeLayout(false);
			this->flowLayoutPanelGroupLang->ResumeLayout(false);
			this->flowLayoutPanelGroupLang->PerformLayout();
			this->flowLayoutPanelWordListBtns2->ResumeLayout(false);
			this->contextMenuStripBook->ResumeLayout(false);
			this->statusStripMain->ResumeLayout(false);
			this->statusStripMain->PerformLayout();
			this->contextMenuHelp->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	//-- �C�x���g ���j���[�R�}���h --//
private: System::Void �I��toolStripButton_Click(System::Object^  sender, System::EventArgs^  e);				//�I���{�^���N���b�N
private: System::Void �R�s�[CToolStripButton_Click(System::Object^  sender, System::EventArgs^  e);				//�R�s�[�{�^���N���b�N
private: System::Void toolStripButtonConfig_Click(System::Object^  sender, System::EventArgs^  e);				//�ݒ�{�^���N���b�N
private: System::Void �w���vLToolStripButton_Click(System::Object^  sender, System::EventArgs^  e);				//�w���v�{�^���N���b�N

	//-- �C�x���g �w���v���j���[�R�}���h --//
private: System::Void ToolStripMenuItemHelpMan_Click(System::Object^  sender, System::EventArgs^  e);			//�w���v���j���[�F�u�}�j���A���v
private: System::Void ToolStripMenuItemHelpVer_Click(System::Object^  sender, System::EventArgs^  e);			//�w���v���j���[�F�u�o�[�W�������v


	//-- �C�x���g �e�R���|�[�l���g --//
private: System::Void textBoxSchWord_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);	//�����P��TextBox����
private: System::Void buttonSchWord_Click(System::Object^  sender, System::EventArgs^  e);						//�����{�^���N���b�N
private: System::Void listBoxWordList_DoubleClick(System::Object^  sender, System::EventArgs^  e);				//�����P�ꃊ�X�g�_�u���N���b�N
private: System::Void buttonWordListClear_Click(System::Object^  sender, System::EventArgs^  e);				//�N���A�{�^���N���b�N
private: System::Void webBrowserBook_Navigating(System::Object^  sender,										//�P�ꃊ���N�ړ�
											System::Windows::Forms::WebBrowserNavigatingEventArgs^  e); 
private: System::Void treeViewGroupTree_DoubleClick(System::Object^  sender, System::EventArgs^  e);			//���ރ��X�g�_�u���N���b�N	

	//-- �C�x���g Book�E�N���b�N���j���[�R�}���h --//
private: System::Void toolStripMenuItemBookCopy_Click(System::Object^  sender, System::EventArgs^  e);		//Book���j���[�F�u�R�s�[�v
//private: System::Void toolStripMenuItemWebSearch_Click(System::Object^  sender, System::EventArgs^  e);	//Book���j���[�F�uWeb�����v
private: System::Void ToolStripMenuItemWebSchSite1_Click(System::Object^  sender, System::EventArgs^  e);	//Book���j���[�F�uBing�����v
private: System::Void ToolStripMenuItemWebSchSite2_Click(System::Object^  sender, System::EventArgs^  e);	//Book���j���[�F�uGoogle�����v
private: System::Void ToolStripMenuItemWebEncycro1_Click(System::Object^  sender, System::EventArgs^  e);	//Book���j���[�F�u�G���J���^�\���v
private: System::Void ToolStripMenuItemWebEncycro2_Click(System::Object^  sender, System::EventArgs^  e);	//Book���j���[�F�uWiki�\���v

	//-- �C�x���g �^�X�N�o�[���j���[�R�}���h --//
private: System::Void ThumbButtonSchLangA_Click(System::Object^  sender, 
							Microsoft::WindowsAPICodePack::Taskbar::ThumbnailButtonClickedEventArgs^  e);	//�^�X�N�o�[�F����P�{�^��
private: System::Void ThumbButtonSchLangB_Click(System::Object^  sender, 
							Microsoft::WindowsAPICodePack::Taskbar::ThumbnailButtonClickedEventArgs^  e);	//�^�X�N�o�[�F����Q�{�^��

		//-- �ǉ��f�[�^--//		
		WordDicCfg^			WDConfigParm;										//�P�ꎫ�T�R���t�B�O

		String^				DispXMLForder;										//�P��\���f�[�^�i�[�t�H���_

		List<WDSegment^>^	SegmentListA;										//���ރ��X�gA
		List<WDSegment^>^	SegmentListB;										//���ރ��X�gB
		FIsam^	WordFileA;														//�P��t�@�C��A
		FIsam^	MeanFileA;														//�Ӗ��t�@�C��A
		FIsam^	TransFileA;														//�|��t�@�C��A
		FIsam^	RelationFileA;													//�֘A��t�@�C��A

		FIsam^	WordFileB;														//�P��t�@�C��B
		FIsam^	MeanFileB;														//�Ӗ��t�@�C��B
		FIsam^	TransFileB;														//�|��t�@�C��B
		FIsam^	RelationFileB;													//�֘A��t�@�C��B

		List<WDWordGrp^>^	ReadedWordList;										//�����\���ς݂̒P��
		Int32				SchMethod;											//�������@ 0:�� 1:�P�� 2:����
		Int32				SchLanguage;										//�������� 0:�� 1:A 2:B
		Int32				SchState;											//������� 0:�� 1:�P�� 2:�ǂݕ�1 3:�ǂݕ�2
		String^				SchWord;											//�����P��
		array<Byte>^		SchGroup;											//�����O���[�v

		WDWordSchListComparer^ WordSchListComparer;								


 		//-- �ǉ��t�@���N�V���� --//
		//��������
		void CreateDatas( void );												//�f�[�^�쐬
		void InitializeForms( void );											//�t�H�[���̏�����
		void ReadConfig( void );												//�R���t�B�O�Z�b�g�A�b�v
		void LoadGroupFile( void );												//����TreeView�쐬
		void LoadSegmentFile( void );											//�敪�t�@�C���Ǎ�
		void OpenDicFile( void );												//�����t�@�C���I�[�v��

		//�P�ꌟ������
		void WordSearch( void );												//�P�ꌟ��
		void WordSchA( void );													//�P�ꌟ�� ����A
		void WordSchB( void );													//�P�ꌟ�� ����B
		void ReadBaseWordA( WDWordGrp^ inWordGrp );								//�P���{�`���� ����A
		void ReadBaseWordB( WDWordGrp^ inWordGrp );								//�P���{�`���� ����B
		Int32 chkWordList( Int32 inWordID );									//�P�ꃊ�X�g�̏d���`�F�b�N

		//���ތ�������
		void GroupSchA( void );													//���ތ��� ����A
		void GroupSchB( void );													//���ތ��� ����B

		//�P��f�[�^�\������
		void WordGrpLoadA( WDWordGrp^ inWordGrp );								//�P��O���[�v�Ǎ� ����A
		void WordGrpLoadB( WDWordGrp^ inWordGrp );								//�P��O���[�v�Ǎ� ����B
		void WordGrpDispA( WDWordGrp^ inWordGrp );								//�P��O���[�v�\�� ����A
		void WordGrpDispB( WDWordGrp^ inWordGrp );								//�P��O���[�v�\�� ����B
		String^ getTransWordA( Int32 inWordID );								//����A������B�̖|��ꌟ��
		String^ getTransWordB( Int32 inWordID );								//����B������A�̖|��ꌟ��
		String^ getRelationWordA( Int32 inWordID );								//����A�̊֘A�ꌟ��
		String^ getRelationWordB( Int32 inWordID );								//����B�̊֘A�ꌟ��

		//�����P��N���A
		void schWordLstClear( void );											//�����P�ꃊ�X�g�N���A

		//�\���f�[�^�ړ�
		void BrowserLinkChk( String^ inUrlStr );								//�����N�`�F�b�N
		void WordDispMove( Int32 inLang, Int32 inWordID );						//�P��\���ړ�
		void WordGroupSch( Int32 inLang, String^ inGroupID );					//�P��O���[�v����

		//�N���b�v�{�[�h����
		void BookWordCopy( void );												//Book�̑I���e�L�X�g�R�s�[
		String^ GetProcWord( void );											//�E�N���b�N�����Ώە���
		String^ createSearchStrBytes( String^ strSchWord );						//Web�������[�h�쐬
	
		//���̑��R�}���h
		WDSegment^	getSegment( List<WDSegment^>^ inSegmentLst,					//�敪�擾
								Int32 inID, Int32 inNum );
		WDGroupTreeNode^ getGroup( array<Byte>^ inGroupGt,						//���ގ擾
								array<Byte>^ inGroupLt );
		WDGroupTreeNode^ getGroupChld( WDGroupTreeNode^ inTreeNode,				//���ގ擾(���m�[�h)
			array<Byte>^ inGroupGt,	array<Byte>^ inGroupLt );
		String^ getXMLFname();													//XML�t�@�C�����擾
		void ExceptionWrite( Exception^ exp );									//��O���o��
		String^ IE7UnderString( String^ inStr );								//IE7�ȉ��̕����C������
		String^ getFilePathName( String^ inStr );								//�t�@�C���p�X���擾


		//�I������
		void DeleteXmlFiles( void );											//XML�t�@�C���폜
		void DeleteDatas( void );												//�f�[�^�폜
			

};
}

