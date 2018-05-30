#include "include/lamprey.h"

#include "include/controller.h"
#include "include/skin.h"

#include "include/display-win32-main.h"
#include "include/display-win32-settings.h"

using namespace System;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;

using namespace hidlamprey;

hl_mutex_t controller_mutex;

System::Void formMain::picController_onPaint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	if (!controller) {
		return;
	}

	hl_mutex_lock(&controller_mutex);

	for (int i = 0; i < controller->button_count; i++) {
		struct button_state *button = controller->buttons[i];
		for (int j = 0; j < skinActive->button_count; j++) {
			struct hl_skin_button *skin_button = skinActive->buttons[j];
			if (button->type == skin_button->type && button->code == skin_button->code) {
				if (button->value) {
					e->Graphics->DrawImage(this->skinButtons[j]->Image, RectangleF(this->skinButtons[j]->Location, this->skinButtons[j]->Size));
				}
			}
		}

		for (int j = 0; j < skinActive->axis_count; j++) {
			struct hl_skin_axis *skin_axis = skinActive->axes[j];
			if ((button->type == skin_axis->type_x && button->code == skin_axis->code_x) ||
				(button->type == skin_axis->type_y && button->code == skin_axis->code_y)) {
				int offset_x = this->skinAxes[j]->Location.X - skin_axis->x;
				int offset_y = this->skinAxes[j]->Location.Y - skin_axis->y;
				int visible = false;

				if (button->type == skin_axis->type_x && button->code == skin_axis->code_x && (skin_axis->trigger_x == 0 || (skin_axis->trigger_x > 0 && button->value > skin_axis->trigger_x) || (skin_axis->trigger_x < 0 && button->value < skin_axis->trigger_x))) {
					if (button->value) {
						if (skin_axis->offset_x) {
							offset_x = (button->type == EV_REL ? button->decay : button->value) / (256 / skin_axis->offset_x);
						} else {
							offset_x = 0;
						}
						visible = true;
					} else {
						offset_x = 0;
					}
				}

				if (button->type == skin_axis->type_y && button->code == skin_axis->code_y && (skin_axis->trigger_y == 0 || (skin_axis->trigger_y > 0 && button->value > skin_axis->trigger_y) || (skin_axis->trigger_y < 0 && button->value < skin_axis->trigger_y))) {
					if (button->value) {
						if (skin_axis->offset_y) {
							offset_y = (button->type == EV_REL ? button->decay : button->value) / (256 / skin_axis->offset_y);
						} else {
							offset_y = 0;
						}
						visible = true;
					} else {
						offset_y = 0;
					}
				}

				this->skinAxes[j]->Location = Drawing::Point(skin_axis->x + offset_x, skin_axis->y + offset_y);
				if (visible) {
					e->Graphics->DrawImage(this->skinAxes[j]->Image, RectangleF(this->skinAxes[j]->Location, this->skinAxes[j]->Size));
				}
			}
		}
	}

	hl_mutex_unlock(&controller_mutex);
}
System::Void formMain::tsmiAlwaysOnTop_Click(System::Object^ sender, System::EventArgs^ e) {
	this->TopMost = tsmiAlwaysOnTop->Checked;
}
System::Void formMain::tsmiExit_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();
}
System::Void formMain::tmsiSettings_Click(System::Object^  sender, System::EventArgs^  e) {
	settings->ShowDialog();
}
System::Void formMain::formMain_Load(System::Object^  sender, System::EventArgs^  e) {
	this->DoubleBuffered = true;

	settings = gcnew formSettings(this);
}

System::Void formMain::formMain_Closed(System::Object^ sender, System::EventArgs^ e) {
}

System::Void formMain::formMain_Shown(System::Object^ sender, System::EventArgs^ e) {
	this->loadSkinImages(hl_settings->skin->name, hl_settings->skin->background);
}

System::Void formMain::formMain_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		const int HT_CAPTION = 2;
		ReleaseCapture();
		SendMessage(static_cast<HWND>(this->Handle.ToPointer()), WM_NCLBUTTONDOWN, HT_CAPTION, 0);
	}
}

System::Void formMain::timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	if (!this->controller) {
		return;
	}

	hl_mutex_lock(&controller_mutex);
	for (int i = 0; i < this->controller->button_count; i++) {
		if (this->controller->buttons[i]->type == EV_REL && this->controller->buttons[i]->value != 0) {
			int16_t decay_amount;
			if (abs(this->controller->buttons[i]->value) < 10) {
				decay_amount = this->controller->buttons[i]->value;
			} else {
				decay_amount = this->controller->buttons[i]->value * .1;
			}
			this->controller->buttons[i]->decay -= decay_amount;
			if (abs(this->controller->buttons[i]->decay) < abs(decay_amount)) {
				this->controller->buttons[i]->decay = 0;
				this->controller->buttons[i]->value = 0;
			}
			this->needRefresh = true;
		}
	}
	hl_mutex_unlock(&controller_mutex);

	if (this->needRefresh) {
		if (this->picController->InvokeRequired) {
			this->picController->Invoke(gcnew Action(this, &formMain::refreshImage));
		} else {
			this->refreshImage();
		}
	}
}

void formMain::refreshImage() {
	this->needRefresh = false;

	this->picController->Refresh();
}

void formMain::output_controller(struct controller *c) {
	if (!skinActive) {
		return;
	}

	hl_mutex_lock(&controller_mutex);
	this->controller = c;
	this->needRefresh = true;
	hl_mutex_unlock(&controller_mutex);
}

void formMain::output_raw(const char *device, const char *rawname, int value) {
	if (settings && settings->Visible) {
		((formSettings ^)settings)->output_raw(gcnew String(device), gcnew String(rawname), Int16(value));
	}
}

void formMain::loadSkinImages(char *skin_name, char *skin_background) {
	hl_mutex_create(&controller_mutex);

	if (this->skinButtons) {
		delete(this->skinButtons);
	}
	if (this->skinAxes) {
		delete(this->skinAxes);
	}

	for (int i = 0; i < hl_skin_count; i++) {
		if (!strcmp(skin_name, hl_skins[i]->name)) {
			skinActive = hl_skins[i];

			for (int j = 0; j < skinActive->background_count; j++) {
				if (!strcmp(skin_background, skinActive->backgrounds[j]->name)) {
					skinActiveBackground = skinActive->backgrounds[j];
					break;
				}
			}
			break;
		}
	}

	if (!skinActive) {
		return;
	}

	Drawing::Bitmap ^backgroundImage = gcnew Bitmap(String::Concat(gcnew String(skinActive->path), gcnew String(skinActiveBackground->filename)));
	backgroundImage->MakeTransparent(Color::White);

	picController->Image = backgroundImage;
	picController->Size = backgroundImage->Size;
	picController->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;

	this->skinButtons = gcnew array<System::Windows::Forms::PictureBox^>(skinActive->button_count);
	for (int i = 0; i < skinActive->button_count; i++) {
		System::Windows::Forms::PictureBox^ picButton = (gcnew System::Windows::Forms::PictureBox());

		Drawing::Bitmap ^buttonImage = gcnew Bitmap(String::Concat(gcnew String(skinActive->path), gcnew String(skinActive->buttons[i]->filename)));
		buttonImage->MakeTransparent(Color::White);

		picButton->Anchor = AnchorStyles::Left | AnchorStyles::Top;
		picButton->BackColor = Color::Transparent;
		picButton->Enabled = false;
		picButton->Image = buttonImage;
		picButton->Location = System::Drawing::Point(skinActive->buttons[i]->x, skinActive->buttons[i]->y);
		picButton->Name = L"picButton";
		picButton->Name += i;
		picButton->Padding = System::Windows::Forms::Padding(0, 0, 0, 0);
		picButton->Size = buttonImage->Size;
		picButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
		picButton->Visible = false;

		this->skinButtons[i] = picButton;

		this->Controls->Add(picButton);

		picButton->Parent = this->picController;
	}

	this->skinAxes = gcnew array<System::Windows::Forms::PictureBox^>(skinActive->axis_count);
	for (int i = 0; i < skinActive->axis_count; i++) {
		System::Windows::Forms::PictureBox^ picAxis = (gcnew System::Windows::Forms::PictureBox());

		Drawing::Bitmap ^axisImage = gcnew Bitmap(String::Concat(gcnew String(skinActive->path), gcnew String(skinActive->axes[i]->filename)));
		axisImage->MakeTransparent(Color::White);

		picAxis->Anchor = AnchorStyles::Left | AnchorStyles::Top;
		picAxis->BackColor = Color::Transparent;
		picAxis->Enabled = false;
		picAxis->Image = axisImage;
		picAxis->Location = System::Drawing::Point(skinActive->axes[i]->x, skinActive->axes[i]->y);
		picAxis->Name = L"picAxis";
		picAxis->Name += i;
		picAxis->Padding = System::Windows::Forms::Padding(0, 0, 0, 0);
		picAxis->Size = axisImage->Size;
		picAxis->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
		picAxis->Visible = false;

		this->skinAxes[i] = picAxis;

		this->Controls->Add(picAxis);

		picAxis->Parent = this->picController;
	}

	if (backgroundImage->Width > 640 || backgroundImage->Height > 640) {
		/* Scale down to a maximum of 640px */
		float scale;
		if (backgroundImage->Width > backgroundImage->Height) {
			scale = 640 * ((float)1 / backgroundImage->Width);
		} else {
			scale = 640 * ((float)1 / backgroundImage->Height);
		}
		picController->Scale(SizeF(scale, scale));
	}
	picController->Visible = true;
}
