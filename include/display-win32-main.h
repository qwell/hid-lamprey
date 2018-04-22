#pragma once

namespace hidlamprey {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for formMain
	/// </summary>
	public ref class formMain : public System::Windows::Forms::Form {
	public:
		static formMain^ Instance() {
			Monitor::Enter(instanceLock);
			try {
				if (!instance) {
					instance = gcnew formMain();
				}
				return instance;
			} finally {
				Monitor::Exit(instanceLock);
			}
		}
		
		void output_controller(IntPtr controller);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~formMain() {
			if (components) {
				delete components;
			}
		}

	private:
		formMain(void) {
			InitializeComponent();
		}

		static formMain^ instance;
		static Object^ instanceLock = gcnew Object();
		Boolean imageControllerLoaded = false;
		System::Windows::Forms::Button^  button1;
		System::Windows::Forms::PictureBox^  picController;

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->picController = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picController))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 308);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(96, 36);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &formMain::button1_Click);
			// 
			// picController
			// 
			this->picController->ImageLocation = L"resources/SNES_Simplified_small.png";
			this->picController->Location = System::Drawing::Point(12, 12);
			this->picController->Name = L"picController";
			this->picController->Size = System::Drawing::Size(640, 284);
			this->picController->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picController->TabIndex = 1;
			this->picController->TabStop = false;
			this->picController->LoadCompleted += gcnew System::ComponentModel::AsyncCompletedEventHandler(this, &formMain::picController_LoadCompleted);
			// 
			// formMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(120, 120);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->ClientSize = System::Drawing::Size(664, 356);
			this->Controls->Add(this->picController);
			this->Controls->Add(this->button1);
			this->MaximizeBox = false;
			this->Name = L"formMain";
			this->ShowIcon = false;
			this->Text = L"Lamprey";
			this->Closed += gcnew System::EventHandler(this, &formMain::formMain_Closed);
			this->Load += gcnew System::EventHandler(this, &formMain::formMain_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picController))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void formMain_Load(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void formMain_Closed(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void picController_LoadCompleted(System::Object^  sender, System::ComponentModel::AsyncCompletedEventArgs^  e) {
		this->imageControllerLoaded = true;
	}
};
}
