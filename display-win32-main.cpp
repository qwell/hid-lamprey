#include "include/lamprey.h"

#include "include/controller.h"
#include "include/skin.h"

#include "include/display-win32-main.h"

using namespace System;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;

using namespace hidlamprey;

void formMain::output_controller(IntPtr controller) {
	if (!hl_active_skin) {
		return;
	}

	if (picController->InvokeRequired) {
		picController->Invoke(gcnew Action<IntPtr>(this, &formMain::output_controller), controller);
	} else {
		struct controller_display *c = (struct controller_display *)controller.ToPointer();

		for (int j = 0; j < sizeof(c->mapping) / sizeof(*c->mapping); j++) {
			struct controller_display_mapping *mapping = &c->mapping[j];

			for (int k = 0; k < sizeof(mapping->buttons) / sizeof(*mapping->buttons); k++) {
				const struct button_trigger *trigger = &mapping->buttons[k];

				for (int l = 0; l < hl_active_skin->button_count; l++) {
					if (trigger->type == hl_active_skin->buttons[l]->type && trigger->code == hl_active_skin->buttons[l]->code) {
						if (mapping->value) {
							this->skinButtons[l]->Visible = true;
						} else {
							this->skinButtons[l]->Visible = false;
						}
					}
				}
			}
		}
	}
}

void formMain::loadSkinImages() {
	if (this->skinButtons) {
		delete(this->skinButtons);
	}

	if (!hl_active_skin) {
		return;
	}

	Drawing::Bitmap ^backgroundImage = gcnew Bitmap(String::Concat(gcnew String(hl_active_skin->path), gcnew String(hl_active_skin->background.filename)));
	//backgroundImage->MakeTransparent(Color::White);

	//this->Size = backgroundImage->Size + Drawing::Size(48, 48);

	picController->Image = backgroundImage;
	picController->Size = backgroundImage->Size;
	picController->Visible = true;

	this->skinButtons = gcnew array<System::Windows::Forms::PictureBox^>(hl_active_skin->button_count);

	for (int i = 0; i < hl_active_skin->button_count; i++) {
		System::Windows::Forms::PictureBox^  picButton = (gcnew System::Windows::Forms::PictureBox());

		Drawing::Bitmap ^buttonImage = gcnew Bitmap(String::Concat(gcnew String(hl_active_skin->path), gcnew String(hl_active_skin->buttons[i]->filename)));
		buttonImage->MakeTransparent(Color::White);

		picButton->BackColor = Color::Transparent;
		picButton->BackgroundImage = buttonImage;
		picButton->Location = this->picController->Location;
		picButton->Name = L"picButton";
		picButton->Name += i;
		picButton->Size = buttonImage->Size;
		picButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Normal;
		picButton->Visible = false;

		picButton->Location = System::Drawing::Point(hl_active_skin->buttons[i]->x, hl_active_skin->buttons[i]->y);

		this->skinButtons[i] = picButton;

		this->Controls->Add(picButton);

		picButton->Parent = this->picController;
	}
}