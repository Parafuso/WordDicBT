//------------------------------------------------------------------------------
//	ことばの辞典　ことばの辞典ビューアアプリケーション　ヘッダ
//	Version 1.0.0.0			create date 2006/05/08
//	Version 1.0.1.0			Change date 2009/09/13
//	Version 1.0.1.1			Change date 2010/10/22	ToolStripMenuItemWebEncycro1 削除 右クリックメニューエンカルタを削除（イベント関数残している）
//	Version 1.0.3.0			Change date 2010/11/16　タスクバーからクリップボードの内容で単語検索可能にする。
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	Windows Formのアプリケーション
//------------------------------------------------------------------------------
#pragma once
#include "WDConfig.h"			//設定画面
#include "WDVerDialog.h"		//バージョンダイアログ

#include "WordDicCfg.h"			//言葉の辞典 初期設定
#include "WDWordGrp.h"			//単語グループ情報
#include "WDGroupTreeNode.h"	//グループツリーノード
#include "WDWordSchListSort.h"	//単語検索結果表示用リストボックスソート


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
	/// Form1 の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		//-- コンストラクタ --//
		Form1(void);

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
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

	//Book領域用右クリックメニュー
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripBook;					//Book領域右クリックメニュー

	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemBookCopy;				//右クリックメニューコピー

	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemWebSearch;			//右クリックメニューWebサーチルート
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItemWebSchSite1;			//右クリックメニューWebサーチ１
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItemWebSchSite2;			//右クリックメニューWebサーチ２

	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItemWebEncyclopedia;		//右クリックメニュー百科事典ルート
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItemWebEncycro2;			//右クリックメニュー百科事典２


	private: WDConfig^		dlgWDConfig;											//設定ダイアログ
	private: WDVerDialog^ dlgWDVerDialog;											//バージョンダイアログ


	private: System::ComponentModel::IContainer^  components;

	//タスクバーボタン用ボタン
	private: Microsoft::WindowsAPICodePack::Taskbar::ThumbnailToolBarManager^ ThumbnailToolBarManagerWD;	//タスクバーボタンマネージャー
	private: Microsoft::WindowsAPICodePack::Taskbar::ThumbnailToolBarButton^ ThumbButtonSchLangA;	//タスクバーボタン：言語１ボタン						
	private: Microsoft::WindowsAPICodePack::Taskbar::ThumbnailToolBarButton^ ThumbButtonSchLangB;	//タスクバーボタン：言語２ボタン




	protected: 

	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
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
			this->QuittoolStripButton->Click += gcnew System::EventHandler(this, &Form1::終了toolStripButton_Click);
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
			this->CopyCToolStripButton->Click += gcnew System::EventHandler(this, &Form1::コピーCToolStripButton_Click);
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
			this->HelpLToolStripButton->Click += gcnew System::EventHandler(this, &Form1::ヘルプLToolStripButton_Click);
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
	//-- イベント メニューコマンド --//
private: System::Void 終了toolStripButton_Click(System::Object^  sender, System::EventArgs^  e);				//終了ボタンクリック
private: System::Void コピーCToolStripButton_Click(System::Object^  sender, System::EventArgs^  e);				//コピーボタンクリック
private: System::Void toolStripButtonConfig_Click(System::Object^  sender, System::EventArgs^  e);				//設定ボタンクリック
private: System::Void ヘルプLToolStripButton_Click(System::Object^  sender, System::EventArgs^  e);				//ヘルプボタンクリック

	//-- イベント ヘルプメニューコマンド --//
private: System::Void ToolStripMenuItemHelpMan_Click(System::Object^  sender, System::EventArgs^  e);			//ヘルプメニュー：「マニュアル」
private: System::Void ToolStripMenuItemHelpVer_Click(System::Object^  sender, System::EventArgs^  e);			//ヘルプメニュー：「バージョン情報」


	//-- イベント 各コンポーネント --//
private: System::Void textBoxSchWord_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);	//検索単語TextBox入力
private: System::Void buttonSchWord_Click(System::Object^  sender, System::EventArgs^  e);						//検索ボタンクリック
private: System::Void listBoxWordList_DoubleClick(System::Object^  sender, System::EventArgs^  e);				//検索単語リストダブルクリック
private: System::Void buttonWordListClear_Click(System::Object^  sender, System::EventArgs^  e);				//クリアボタンクリック
private: System::Void webBrowserBook_Navigating(System::Object^  sender,										//単語リンク移動
											System::Windows::Forms::WebBrowserNavigatingEventArgs^  e); 
private: System::Void treeViewGroupTree_DoubleClick(System::Object^  sender, System::EventArgs^  e);			//分類リストダブルクリック	

	//-- イベント Book右クリックメニューコマンド --//
private: System::Void toolStripMenuItemBookCopy_Click(System::Object^  sender, System::EventArgs^  e);		//Bookメニュー：「コピー」
//private: System::Void toolStripMenuItemWebSearch_Click(System::Object^  sender, System::EventArgs^  e);	//Bookメニュー：「Web検索」
private: System::Void ToolStripMenuItemWebSchSite1_Click(System::Object^  sender, System::EventArgs^  e);	//Bookメニュー：「Bing検索」
private: System::Void ToolStripMenuItemWebSchSite2_Click(System::Object^  sender, System::EventArgs^  e);	//Bookメニュー：「Google検索」
private: System::Void ToolStripMenuItemWebEncycro1_Click(System::Object^  sender, System::EventArgs^  e);	//Bookメニュー：「エンカルタ表示」
private: System::Void ToolStripMenuItemWebEncycro2_Click(System::Object^  sender, System::EventArgs^  e);	//Bookメニュー：「Wiki表示」

	//-- イベント タスクバーメニューコマンド --//
private: System::Void ThumbButtonSchLangA_Click(System::Object^  sender, 
							Microsoft::WindowsAPICodePack::Taskbar::ThumbnailButtonClickedEventArgs^  e);	//タスクバー：言語１ボタン
private: System::Void ThumbButtonSchLangB_Click(System::Object^  sender, 
							Microsoft::WindowsAPICodePack::Taskbar::ThumbnailButtonClickedEventArgs^  e);	//タスクバー：言語２ボタン

		//-- 追加データ--//		
		WordDicCfg^			WDConfigParm;										//単語辞典コンフィグ

		String^				DispXMLForder;										//単語表示データ格納フォルダ

		List<WDSegment^>^	SegmentListA;										//分類リストA
		List<WDSegment^>^	SegmentListB;										//分類リストB
		FIsam^	WordFileA;														//単語ファイルA
		FIsam^	MeanFileA;														//意味ファイルA
		FIsam^	TransFileA;														//翻訳ファイルA
		FIsam^	RelationFileA;													//関連語ファイルA

		FIsam^	WordFileB;														//単語ファイルB
		FIsam^	MeanFileB;														//意味ファイルB
		FIsam^	TransFileB;														//翻訳ファイルB
		FIsam^	RelationFileB;													//関連語ファイルB

		List<WDWordGrp^>^	ReadedWordList;										//辞書表示済みの単語
		Int32				SchMethod;											//検索方法 0:未 1:単語 2:分類
		Int32				SchLanguage;										//検索言語 0:未 1:A 2:B
		Int32				SchState;											//検索状態 0:未 1:単語 2:読み方1 3:読み方2
		String^				SchWord;											//検索単語
		array<Byte>^		SchGroup;											//検索グループ

		WDWordSchListComparer^ WordSchListComparer;								


 		//-- 追加ファンクション --//
		//初期処理
		void CreateDatas( void );												//データ作成
		void InitializeForms( void );											//フォームの初期化
		void ReadConfig( void );												//コンフィグセットアップ
		void LoadGroupFile( void );												//分類TreeView作成
		void LoadSegmentFile( void );											//区分ファイル読込
		void OpenDicFile( void );												//辞書ファイルオープン

		//単語検索処理
		void WordSearch( void );												//単語検索
		void WordSchA( void );													//単語検索 言語A
		void WordSchB( void );													//単語検索 言語B
		void ReadBaseWordA( WDWordGrp^ inWordGrp );								//単語基本形検索 言語A
		void ReadBaseWordB( WDWordGrp^ inWordGrp );								//単語基本形検索 言語B
		Int32 chkWordList( Int32 inWordID );									//単語リストの重複チェック

		//分類検索処理
		void GroupSchA( void );													//分類検索 言語A
		void GroupSchB( void );													//分類検索 言語B

		//単語データ表示処理
		void WordGrpLoadA( WDWordGrp^ inWordGrp );								//単語グループ読込 言語A
		void WordGrpLoadB( WDWordGrp^ inWordGrp );								//単語グループ読込 言語B
		void WordGrpDispA( WDWordGrp^ inWordGrp );								//単語グループ表示 言語A
		void WordGrpDispB( WDWordGrp^ inWordGrp );								//単語グループ表示 言語B
		String^ getTransWordA( Int32 inWordID );								//言語A→言語Bの翻訳語検索
		String^ getTransWordB( Int32 inWordID );								//言語B→言語Aの翻訳語検索
		String^ getRelationWordA( Int32 inWordID );								//言語Aの関連語検索
		String^ getRelationWordB( Int32 inWordID );								//言語Bの関連語検索

		//検索単語クリア
		void schWordLstClear( void );											//検索単語リストクリア

		//表示データ移動
		void BrowserLinkChk( String^ inUrlStr );								//リンクチェック
		void WordDispMove( Int32 inLang, Int32 inWordID );						//単語表示移動
		void WordGroupSch( Int32 inLang, String^ inGroupID );					//単語グループ検索

		//クリップボード操作
		void BookWordCopy( void );												//Bookの選択テキストコピー
		String^ GetProcWord( void );											//右クリック処理対象文字
		String^ createSearchStrBytes( String^ strSchWord );						//Web検索ワード作成
	
		//その他コマンド
		WDSegment^	getSegment( List<WDSegment^>^ inSegmentLst,					//区分取得
								Int32 inID, Int32 inNum );
		WDGroupTreeNode^ getGroup( array<Byte>^ inGroupGt,						//分類取得
								array<Byte>^ inGroupLt );
		WDGroupTreeNode^ getGroupChld( WDGroupTreeNode^ inTreeNode,				//分類取得(小ノード)
			array<Byte>^ inGroupGt,	array<Byte>^ inGroupLt );
		String^ getXMLFname();													//XMLファイル名取得
		void ExceptionWrite( Exception^ exp );									//例外情報出力
		String^ IE7UnderString( String^ inStr );								//IE7以下の文字修正処理
		String^ getFilePathName( String^ inStr );								//ファイルパス名取得


		//終了処理
		void DeleteXmlFiles( void );											//XMLファイル削除
		void DeleteDatas( void );												//データ削除
			

};
}

