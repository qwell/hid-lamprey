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
		void loadSkinImages();

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

			//this->picControllerDisplay->Parent = this->picController;
			//this->picControllerDisplay->Location = System::Drawing::Point(0, 0);
		}

		static formMain^ instance;
		static Object^ instanceLock = gcnew Object();
		Boolean imageControllerLoaded = false;
		array<System::Windows::Forms::PictureBox^>^ skinButtons;
		System::Windows::Forms::PictureBox^  picController;
		System::Windows::Forms::PictureBox^  picControllerDisplay;


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
			this->picController = (gcnew System::Windows::Forms::PictureBox());
			this->picControllerDisplay = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picController))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picControllerDisplay))->BeginInit();
			this->SuspendLayout();
			// 
			// picController
			// 
			this->picController->ImageLocation = L"skins/lamprey-SNES/controller_alpha.png";
			this->picController->Location = System::Drawing::Point(12, 12);
			this->picController->Name = L"picController";
			this->picController->Size = System::Drawing::Size(640, 284);
			this->picController->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picController->TabIndex = 1;
			this->picController->TabStop = false;
			this->picController->LoadCompleted += gcnew System::ComponentModel::AsyncCompletedEventHandler(this, &formMain::picController_LoadCompleted);
			// 
			// picControllerDisplay
			// 
			this->picControllerDisplay->BackColor = System::Drawing::Color::Transparent;
			this->picControllerDisplay->ImageLocation = L"";
			this->picControllerDisplay->Location = System::Drawing::Point(1012, 1012);
			this->picControllerDisplay->Name = L"picControllerDisplay";
			this->picControllerDisplay->Size = System::Drawing::Size(640, 284);
			this->picControllerDisplay->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picControllerDisplay->TabIndex = 2;
			this->picControllerDisplay->TabStop = false;
			this->picControllerDisplay->Visible = false;
			// 
			// formMain
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(664, 307);
			this->Controls->Add(this->picControllerDisplay);
			this->Controls->Add(this->picController);
			this->MaximizeBox = false;
			this->Name = L"formMain";
			this->ShowIcon = false;
			this->Text = L"Lamprey";
			this->Closed += gcnew System::EventHandler(this, &formMain::formMain_Closed);
			this->Load += gcnew System::EventHandler(this, &formMain::formMain_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picController))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picControllerDisplay))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void formMain_Load(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void formMain_Closed(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void picController_LoadCompleted(System::Object^  sender, System::ComponentModel::AsyncCompletedEventArgs^  e) {
		this->loadSkinImages();

		this->imageControllerLoaded = true;
	}
};
}
