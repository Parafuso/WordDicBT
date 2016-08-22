//------------------------------------------------------------------------------
//	ことばの辞典　ことばの辞典ビューアアプリケーション　ヘッダ
//	Version 1.0		create date 2008/03/15
//	Copyright		藤井元雄
//------------------------------------------------------------------------------
//	classes
//		WDConfig : ことばの辞典　設定画面
//------------------------------------------------------------------------------
#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace WordDic {

	/// <summary>
	/// WDConfig の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class WDConfig : public System::Windows::Forms::Form
	{
	public:
		WDConfig(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~WDConfig()
		{
			if (components)
			{
				delete components;
			}
		}






	protected: 












	private: System::Windows::Forms::Panel^  panelBottuns;
	private: System::Windows::Forms::Button^  buttonApply;
	private: System::Windows::Forms::Button^  buttonCancel;
	private: System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::TabControl^  tabControlBase;
	private: System::Windows::Forms::TabPage^  tabPageBase;
	private: System::Windows::Forms::GroupBox^  groupScreenLang;
	private: System::Windows::Forms::Label^  labelScreenLang;
	public: System::Windows::Forms::ComboBox^  comboBoxScreenLang;
	private: 

	private: System::Windows::Forms::TabPage^  tabPageSearch;

	private: System::Windows::Forms::TabPage^  tabPageDic;
	public: System::Windows::Forms::ComboBox^  comboBoxWebSearch;
	private: 



	private: System::Windows::Forms::Label^  labelWebSearch;


	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(WDConfig::typeid));
			this->panelBottuns = (gcnew System::Windows::Forms::Panel());
			this->buttonApply = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->tabControlBase = (gcnew System::Windows::Forms::TabControl());
			this->tabPageBase = (gcnew System::Windows::Forms::TabPage());
			this->groupScreenLang = (gcnew System::Windows::Forms::GroupBox());
			this->labelScreenLang = (gcnew System::Windows::Forms::Label());
			this->comboBoxScreenLang = (gcnew System::Windows::Forms::ComboBox());
			this->tabPageSearch = (gcnew System::Windows::Forms::TabPage());
			this->labelWebSearch = (gcnew System::Windows::Forms::Label());
			this->comboBoxWebSearch = (gcnew System::Windows::Forms::ComboBox());
			this->tabPageDic = (gcnew System::Windows::Forms::TabPage());
			this->panelBottuns->SuspendLayout();
			this->tabControlBase->SuspendLayout();
			this->tabPageBase->SuspendLayout();
			this->groupScreenLang->SuspendLayout();
			this->tabPageSearch->SuspendLayout();
			this->SuspendLayout();
			// 
			// panelBottuns
			// 
			this->panelBottuns->Controls->Add(this->buttonApply);
			this->panelBottuns->Controls->Add(this->buttonCancel);
			this->panelBottuns->Controls->Add(this->buttonOK);
			this->panelBottuns->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panelBottuns->Location = System::Drawing::Point(0, 243);
			this->panelBottuns->Name = L"panelBottuns";
			this->panelBottuns->Size = System::Drawing::Size(480, 29);
			this->panelBottuns->TabIndex = 2;
			// 
			// buttonApply
			// 
			this->buttonApply->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->buttonApply->Location = System::Drawing::Point(393, 4);
			this->buttonApply->Name = L"buttonApply";
			this->buttonApply->Size = System::Drawing::Size(75, 23);
			this->buttonApply->TabIndex = 2;
			this->buttonApply->Text = L"適用";
			this->buttonApply->UseVisualStyleBackColor = true;
			// 
			// buttonCancel
			// 
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->buttonCancel->Location = System::Drawing::Point(312, 4);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 1;
			this->buttonCancel->Text = L"キャンセル";
			this->buttonCancel->UseVisualStyleBackColor = true;
			// 
			// buttonOK
			// 
			this->buttonOK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->buttonOK->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->buttonOK->Location = System::Drawing::Point(231, 4);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(75, 23);
			this->buttonOK->TabIndex = 0;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			// 
			// tabControlBase
			// 
			this->tabControlBase->Controls->Add(this->tabPageBase);
			this->tabControlBase->Controls->Add(this->tabPageSearch);
			this->tabControlBase->Controls->Add(this->tabPageDic);
			this->tabControlBase->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControlBase->HotTrack = true;
			this->tabControlBase->Location = System::Drawing::Point(0, 0);
			this->tabControlBase->Name = L"tabControlBase";
			this->tabControlBase->SelectedIndex = 0;
			this->tabControlBase->Size = System::Drawing::Size(480, 243);
			this->tabControlBase->TabIndex = 3;
			// 
			// tabPageBase
			// 
			this->tabPageBase->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tabPageBase->Controls->Add(this->groupScreenLang);
			this->tabPageBase->Location = System::Drawing::Point(4, 22);
			this->tabPageBase->Name = L"tabPageBase";
			this->tabPageBase->Padding = System::Windows::Forms::Padding(3);
			this->tabPageBase->Size = System::Drawing::Size(472, 217);
			this->tabPageBase->TabIndex = 0;
			this->tabPageBase->Text = L"基本";
			this->tabPageBase->UseVisualStyleBackColor = true;
			// 
			// groupScreenLang
			// 
			this->groupScreenLang->Controls->Add(this->labelScreenLang);
			this->groupScreenLang->Controls->Add(this->comboBoxScreenLang);
			this->groupScreenLang->Location = System::Drawing::Point(7, 14);
			this->groupScreenLang->Name = L"groupScreenLang";
			this->groupScreenLang->Size = System::Drawing::Size(450, 78);
			this->groupScreenLang->TabIndex = 0;
			this->groupScreenLang->TabStop = false;
			this->groupScreenLang->Text = L"画面の表示言語";
			// 
			// labelScreenLang
			// 
			this->labelScreenLang->AutoSize = true;
			this->labelScreenLang->Location = System::Drawing::Point(15, 51);
			this->labelScreenLang->Name = L"labelScreenLang";
			this->labelScreenLang->Size = System::Drawing::Size(256, 12);
			this->labelScreenLang->TabIndex = 1;
			this->labelScreenLang->Text = L"画面のメニューやボタンに表示する言語を指定します。";
			// 
			// comboBoxScreenLang
			// 
			this->comboBoxScreenLang->BackColor = System::Drawing::SystemColors::Window;
			this->comboBoxScreenLang->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxScreenLang->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->comboBoxScreenLang->FormattingEnabled = true;
			this->comboBoxScreenLang->IntegralHeight = false;
			this->comboBoxScreenLang->Items->AddRange(gcnew cli::array< System::Object^  >(1) {L"日本語"});
			this->comboBoxScreenLang->Location = System::Drawing::Point(14, 19);
			this->comboBoxScreenLang->Name = L"comboBoxScreenLang";
			this->comboBoxScreenLang->Size = System::Drawing::Size(425, 20);
			this->comboBoxScreenLang->TabIndex = 0;
			// 
			// tabPageSearch
			// 
			this->tabPageSearch->Controls->Add(this->labelWebSearch);
			this->tabPageSearch->Controls->Add(this->comboBoxWebSearch);
			this->tabPageSearch->Location = System::Drawing::Point(4, 22);
			this->tabPageSearch->Name = L"tabPageSearch";
			this->tabPageSearch->Padding = System::Windows::Forms::Padding(3);
			this->tabPageSearch->Size = System::Drawing::Size(472, 217);
			this->tabPageSearch->TabIndex = 2;
			this->tabPageSearch->Text = L"Web検索";
			this->tabPageSearch->UseVisualStyleBackColor = true;
			// 
			// labelWebSearch
			// 
			this->labelWebSearch->AutoSize = true;
			this->labelWebSearch->Location = System::Drawing::Point(38, 79);
			this->labelWebSearch->Name = L"labelWebSearch";
			this->labelWebSearch->Size = System::Drawing::Size(350, 12);
			this->labelWebSearch->TabIndex = 1;
			this->labelWebSearch->Text = L"表示中の単語、または選択中の言葉を検索するWebサイトを選択します。";
			// 
			// comboBoxWebSearch
			// 
			this->comboBoxWebSearch->BackColor = System::Drawing::SystemColors::Window;
			this->comboBoxWebSearch->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxWebSearch->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->comboBoxWebSearch->FormattingEnabled = true;
			this->comboBoxWebSearch->IntegralHeight = false;
			this->comboBoxWebSearch->Items->AddRange(gcnew cli::array< System::Object^  >(1) {L"エンカルタ"});
			this->comboBoxWebSearch->Location = System::Drawing::Point(26, 46);
			this->comboBoxWebSearch->Name = L"comboBoxWebSearch";
			this->comboBoxWebSearch->Size = System::Drawing::Size(417, 20);
			this->comboBoxWebSearch->TabIndex = 0;
			// 
			// tabPageDic
			// 
			this->tabPageDic->Location = System::Drawing::Point(4, 22);
			this->tabPageDic->Name = L"tabPageDic";
			this->tabPageDic->Padding = System::Windows::Forms::Padding(3);
			this->tabPageDic->Size = System::Drawing::Size(472, 217);
			this->tabPageDic->TabIndex = 1;
			this->tabPageDic->Text = L"辞書";
			// 
			// WDConfig
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(480, 272);
			this->Controls->Add(this->tabControlBase);
			this->Controls->Add(this->panelBottuns);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"WDConfig";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"設定画面";
			this->Shown += gcnew System::EventHandler(this, &WDConfig::WDConfig_Shown);
			this->panelBottuns->ResumeLayout(false);
			this->tabControlBase->ResumeLayout(false);
			this->tabPageBase->ResumeLayout(false);
			this->groupScreenLang->ResumeLayout(false);
			this->groupScreenLang->PerformLayout();
			this->tabPageSearch->ResumeLayout(false);
			this->tabPageSearch->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private: System::Void WDConfig_Shown(System::Object^  sender, System::EventArgs^  e);	//ダイアログ表示時のイベント
	private: System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e);	//OKボタンクリック
};
}
