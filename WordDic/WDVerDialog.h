//------------------------------------------------------------------------------
//	���Ƃ΂̎��T�@���Ƃ΂̎��T�r���[�A�A�v���P�[�V�����@�w�b�_
//	Version 1.0.0.0			Create date 2007/10/07
//	Version 1.0.3.0			Change date 2010/11/16�@�^�X�N�o�[����N���b�v�{�[�h�̓��e�ŒP�ꌟ���\�ɂ���B
//	Copyright		���䌳�Y
//------------------------------------------------------------------------------
//	classes
//		WDVerDialog : �o�[�W�����_�C�A���O
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
	/// WDVerDialog �̊T�v
	///
	/// �o�[�W�����_�C�A���O
	///
	/// </summary>
	public ref class WDVerDialog : public System::Windows::Forms::Form
	{
	public:
		WDVerDialog(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^ �R�[�h��ǉ����܂�
			//
		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~WDVerDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::PictureBox^  pictureBoxIcon;
	private: System::Windows::Forms::Label^  labelWordDic;
	private: System::Windows::Forms::Label^  labelVersion;
	private: System::Windows::Forms::Label^  labelCopyRight;



	private: System::ComponentModel::IContainer^  components;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(WDVerDialog::typeid));
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->pictureBoxIcon = (gcnew System::Windows::Forms::PictureBox());
			this->labelWordDic = (gcnew System::Windows::Forms::Label());
			this->labelVersion = (gcnew System::Windows::Forms::Label());
			this->labelCopyRight = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxIcon))->BeginInit();
			this->SuspendLayout();
			// 
			// buttonOK
			// 
			this->buttonOK->Location = System::Drawing::Point(117, 121);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(75, 23);
			this->buttonOK->TabIndex = 0;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &WDVerDialog::buttonOK_Click);
			// 
			// pictureBoxIcon
			// 
			this->pictureBoxIcon->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBoxIcon.BackgroundImage")));
			this->pictureBoxIcon->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBoxIcon->InitialImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBoxIcon.InitialImage")));
			this->pictureBoxIcon->Location = System::Drawing::Point(12, 25);
			this->pictureBoxIcon->Name = L"pictureBoxIcon";
			this->pictureBoxIcon->Size = System::Drawing::Size(64, 59);
			this->pictureBoxIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBoxIcon->TabIndex = 1;
			this->pictureBoxIcon->TabStop = false;
			// 
			// labelWordDic
			// 
			this->labelWordDic->AutoSize = true;
			this->labelWordDic->Location = System::Drawing::Point(82, 25);
			this->labelWordDic->Name = L"labelWordDic";
			this->labelWordDic->Size = System::Drawing::Size(65, 12);
			this->labelWordDic->TabIndex = 2;
			this->labelWordDic->Text = L"���Ƃ΂̎��T";
			// 
			// labelVersion
			// 
			this->labelVersion->AutoSize = true;
			this->labelVersion->Location = System::Drawing::Point(82, 47);
			this->labelVersion->Name = L"labelVersion";
			this->labelVersion->Size = System::Drawing::Size(59, 12);
			this->labelVersion->TabIndex = 3;
			this->labelVersion->Text = L"Ver. 1.0.3.0";
			// 
			// labelCopyRight
			// 
			this->labelCopyRight->AutoSize = true;
			this->labelCopyRight->Location = System::Drawing::Point(82, 63);
			this->labelCopyRight->Name = L"labelCopyRight";
			this->labelCopyRight->Size = System::Drawing::Size(206, 12);
			this->labelCopyRight->TabIndex = 4;
			this->labelCopyRight->Text = L"CopyRight(c)�@2007-2010�@����@���Y�@";
			// 
			// WDVerDialog
			// 
			this->AcceptButton = this->buttonOK;
			this->AccessibleRole = System::Windows::Forms::AccessibleRole::Dialog;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(304, 156);
			this->Controls->Add(this->labelCopyRight);
			this->Controls->Add(this->labelVersion);
			this->Controls->Add(this->labelWordDic);
			this->Controls->Add(this->pictureBoxIcon);
			this->Controls->Add(this->buttonOK);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"WDVerDialog";
			this->RightToLeftLayout = true;
			this->ShowInTaskbar = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"���Ƃ΂̎��T�@�o�[�W�������";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxIcon))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e);		//OK�{�^���N���b�N

};
}
