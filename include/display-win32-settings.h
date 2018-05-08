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
		formSettings(formMain ^formMain)
		{
			this->formMain = formMain;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		void formSettings::output_raw(const char *device, const char *rawname, int value);

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

	protected:
	private: System::Windows::Forms::Button^  btnAddMapping;
	private: System::Windows::Forms::Button^  btnDeleteMapping;
	private: System::Windows::Forms::TreeView^  tvSkins;



	private: System::Windows::Forms::TreeView^  tvMapButtons;
	private: System::Windows::Forms::TreeView^  tvMappings;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabSkins;
	private: System::Windows::Forms::TabPage^  tabMappings;




	private:
		formMain ^ formMain;
		System::Void formSettings_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);



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
			this->btnAddMapping = (gcnew System::Windows::Forms::Button());
			this->btnDeleteMapping = (gcnew System::Windows::Forms::Button());
			this->tvSkins = (gcnew System::Windows::Forms::TreeView());
			this->tvMappings = (gcnew System::Windows::Forms::TreeView());
			this->tvMapButtons = (gcnew System::Windows::Forms::TreeView());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabSkins = (gcnew System::Windows::Forms::TabPage());
			this->tabMappings = (gcnew System::Windows::Forms::TabPage());
			this->tabControl1->SuspendLayout();
			this->tabSkins->SuspendLayout();
			this->tabMappings->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnAddMapping
			// 
			this->btnAddMapping->Location = System::Drawing::Point(294, 434);
			this->btnAddMapping->Name = L"btnAddMapping";
			this->btnAddMapping->Size = System::Drawing::Size(72, 36);
			this->btnAddMapping->TabIndex = 3;
			this->btnAddMapping->Text = L"Add";
			this->btnAddMapping->UseVisualStyleBackColor = true;
			// 
			// btnDeleteMapping
			// 
			this->btnDeleteMapping->ForeColor = System::Drawing::Color::Red;
			this->btnDeleteMapping->Location = System::Drawing::Point(216, 434);
			this->btnDeleteMapping->Name = L"btnDeleteMapping";
			this->btnDeleteMapping->Size = System::Drawing::Size(72, 36);
			this->btnDeleteMapping->TabIndex = 4;
			this->btnDeleteMapping->Text = L"Delete";
			this->btnDeleteMapping->UseVisualStyleBackColor = true;
			// 
			// tvSkins
			// 
			this->tvSkins->Location = System::Drawing::Point(6, 8);
			this->tvSkins->Name = L"tvSkins";
			this->tvSkins->Size = System::Drawing::Size(265, 457);
			this->tvSkins->TabIndex = 1;
			this->tvSkins->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &formSettings::treeView1_AfterSelect);
			// 
			// tvMappings
			// 
			this->tvMappings->AllowDrop = true;
			this->tvMappings->Location = System::Drawing::Point(6, 6);
			this->tvMappings->Name = L"tvMappings";
			this->tvMappings->Size = System::Drawing::Size(360, 422);
			this->tvMappings->TabIndex = 6;
			this->tvMappings->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &formSettings::tvMappings_DragDrop);
			this->tvMappings->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &formSettings::tvMappings_DragEnter);
			// 
			// tvMapButtons
			// 
			this->tvMapButtons->Location = System::Drawing::Point(372, 6);
			this->tvMapButtons->Name = L"tvMapButtons";
			this->tvMapButtons->Size = System::Drawing::Size(360, 464);
			this->tvMapButtons->TabIndex = 5;
			this->tvMapButtons->ItemDrag += gcnew System::Windows::Forms::ItemDragEventHandler(this, &formSettings::tvMapButtons_ItemDrag);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabSkins);
			this->tabControl1->Controls->Add(this->tabMappings);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(747, 505);
			this->tabControl1->TabIndex = 6;
			// 
			// tabSkins
			// 
			this->tabSkins->Controls->Add(this->tvSkins);
			this->tabSkins->Location = System::Drawing::Point(4, 25);
			this->tabSkins->Name = L"tabSkins";
			this->tabSkins->Padding = System::Windows::Forms::Padding(3);
			this->tabSkins->Size = System::Drawing::Size(739, 476);
			this->tabSkins->TabIndex = 0;
			this->tabSkins->Text = L"Skins";
			this->tabSkins->UseVisualStyleBackColor = true;
			// 
			// tabMappings
			// 
			this->tabMappings->Controls->Add(this->tvMappings);
			this->tabMappings->Controls->Add(this->tvMapButtons);
			this->tabMappings->Controls->Add(this->btnAddMapping);
			this->tabMappings->Controls->Add(this->btnDeleteMapping);
			this->tabMappings->Location = System::Drawing::Point(4, 25);
			this->tabMappings->Name = L"tabMappings";
			this->tabMappings->Padding = System::Windows::Forms::Padding(3);
			this->tabMappings->Size = System::Drawing::Size(739, 476);
			this->tabMappings->TabIndex = 1;
			this->tabMappings->Text = L"Input Mappings (Not Fully Implemented)";
			this->tabMappings->UseVisualStyleBackColor = true;
			// 
			// formSettings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(763, 529);
			this->Controls->Add(this->tabControl1);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"formSettings";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"Settings";
			this->Load += gcnew System::EventHandler(this, &formSettings::formSettings_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabSkins->ResumeLayout(false);
			this->tabMappings->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void tvMapButtons_ItemDrag(System::Object^  sender, System::Windows::Forms::ItemDragEventArgs^  e);
private: System::Void tvMappings_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
private: System::Void tvMappings_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
};
}
