#include "include/lamprey.h"

#include "include/controller.h"
#include "include/skin.h"

#include "include/display-win32-main.h"

using namespace System;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;

using namespace hidlamprey;

struct hl_skin_button testbuttons[] = {
	{ "up.png", "EV_KEY", "BTN_DPAD_UP", 117, 92 },
	{ "right.png", "EV_KEY", "BTN_DPAD_RIGHT", 155, 126 },
	{ "down.png", "EV_KEY", "BTN_DPAD_DOWN", 117, 166 },
	{ "left.png", "EV_KEY", "BTN_DPAD_LEFT", 82, 126 },
	{ "ABXY.png", "EV_KEY", "BTN_NORTH", 482, 74 },
	{ "ABXY.png", "EV_KEY", "BTN_EAST", 542, 124 },
	{ "ABXY.png", "EV_KEY", "BTN_SOUTH", 484, 171 },
	{ "ABXY.png", "EV_KEY", "BTN_WEST", 423, 123 },
	{ "L.png", "EV_KEY", "BTN_TL", 72, 4 },
	{ "R.png", "EV_KEY", "BTN_TR", 430, 4 },
	{ "select.png", "EV_KEY", "BTN_SELECT", 239, 146 },
	{ "start.png", "EV_KEY", "BTN_START", 308, 146 },
};

void formMain::output_controller(IntPtr controller) {
	if (!this->imageControllerLoaded) {
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

				int count = sizeof(testbuttons) / sizeof(*testbuttons);

				for (int l = 0; l < count; l++) {
					struct button_code *code = hl_controller_get_code_by_name(testbuttons[l].type, testbuttons[l].code);
					if (trigger->type == code->type && trigger->code == code->code) {
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
	int count = sizeof(testbuttons) / sizeof(*testbuttons);

	delete(this->skinButtons);
	this->skinButtons = gcnew array<System::Windows::Forms::PictureBox^>(count);

	for (int i = 0; i < count; i++) {
		System::Windows::Forms::PictureBox^  picTestButton = (gcnew System::Windows::Forms::PictureBox());

		Drawing::Bitmap ^testimage = gcnew Bitmap(String::Concat(gcnew String(L"skins/snes-lamprey/"), gcnew String(testbuttons[i].name)));
		testimage->MakeTransparent(Color::White);

		picTestButton->BackColor = Color::Transparent;
		picTestButton->BackgroundImage = testimage;
		picTestButton->Location = this->picController->Location;
		picTestButton->Name = L"picTestButton";
		picTestButton->Name += i;
		picTestButton->Size = testimage->Size;
		picTestButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Normal;
		picTestButton->Visible = false;

		picTestButton->Location = System::Drawing::Point(testbuttons[i].x, testbuttons[i].y);

		this->skinButtons[i] = picTestButton;

		this->Controls->Add(picTestButton);

		picTestButton->Parent = this->picController;
	}
}