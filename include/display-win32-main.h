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
		
		void output_controller(struct controller_display *controller);
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
		}

		System::Void formMain::formMain_onPaint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);

		static formMain^ instance;
		static Object^ instanceLock = gcnew Object();
		struct controller_display *controller;
		array<System::Windows::Forms::PictureBox^>^ skinButtons;
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
			this->picController = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picController))->BeginInit();
			this->SuspendLayout();
			// 
			// picController
			// 
			this->picController->Location = System::Drawing::Point(0, 0);
			this->picController->Name = L"picController";
			this->picController->Size = System::Drawing::Size(0, 0);
			this->picController->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picController->TabIndex = 1;
			this->picController->TabStop = false;
			// 
			// formMain
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(148, 36);
			this->Controls->Add(this->picController);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"formMain";
			this->ShowIcon = false;
			this->Text = L"Lamprey";
			this->Closed += gcnew System::EventHandler(this, &formMain::formMain_Closed);
			this->Load += gcnew System::EventHandler(this, &formMain::formMain_Load);
			this->Shown += gcnew System::EventHandler(this, &formMain::formMain_Shown);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &formMain::formMain_onPaint);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picController))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void formMain_Load(System::Object^  sender, System::EventArgs^  e) {
		this->DoubleBuffered = true;
	}

	private: System::Void formMain_Closed(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void formMain_Shown(System::Object^  sender, System::EventArgs^  e) {
		this->loadSkinImages();
	}
	};
}
