#pragma once

namespace hidlamprey {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for formSettings
	/// </summary>
	public ref class formSettings : public System::Windows::Forms::Form
	{
	public:
		formSettings(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~formSettings()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		System::Void formSettings_Load(System::Object^  sender, System::EventArgs^  e);

	private: System::Windows::Forms::TreeView^  treeView1;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->SuspendLayout();
			// 
			// treeView1
			// 
			this->treeView1->Location = System::Drawing::Point(12, 12);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(258, 229);
			this->treeView1->TabIndex = 1;
			// 
			// formSettings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Controls->Add(this->treeView1);
			this->Name = L"formSettings";
			this->Text = L"formSettings";
			this->Load += gcnew System::EventHandler(this, &formSettings::formSettings_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
