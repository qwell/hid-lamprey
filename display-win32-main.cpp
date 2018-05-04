#include "include/lamprey.h"

#include "include/controller.h"
#include "include/skin.h"

#include "include/display-win32-main.h"

using namespace System;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;

using namespace hidlamprey;

hl_mutex_t controller_mutex;

System::Void formMain::formMain_onPaint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	if (!controller) {
		return;
	}

	hl_mutex_lock(&controller_mutex);

	for (int i = 0; i < controller->button_count; i++) {
		struct button_state *button = controller->buttons[i];
		for (int j = 0; j < hl_active_skin->button_count; j++) {
			struct hl_skin_button *skin_button = hl_active_skin->buttons[j];
			if (button->type == skin_button->type && button->code == skin_button->code) {
				if (button->value) {
					this->skinButtons[j]->Visible = true;
				} else {
					this->skinButtons[j]->Visible = false;
				}
			}
		}

		for (int j = 0; j < hl_active_skin->axis_count; j++) {
			struct hl_skin_axis *skin_axis = hl_active_skin->axes[j];
			if ((button->type == skin_axis->type_x && button->code == skin_axis->code_x) ||
				(button->type == skin_axis->type_y && button->code == skin_axis->code_y)) {
				int offset_x = this->skinAxes[j]->Location.X - skin_axis->x;
				int offset_y = this->skinAxes[j]->Location.Y - skin_axis->y;

				if (button->type == skin_axis->type_x && button->code == skin_axis->code_x) {
					if (button->value) {
						offset_x = button->value / (256 / skin_axis->offset_x);
					} else {
						offset_x = 0;
					}
				}

				if (button->type == skin_axis->type_y && button->code == skin_axis->code_y) {
					if (button->value) {
						offset_y = button->value / (256 / skin_axis->offset_y);
					} else {
						offset_y = 0;
					}
				}

				this->skinAxes[j]->Location = Drawing::Point(skin_axis->x + offset_x, skin_axis->y + offset_y);
				if (offset_x || offset_y) {
					this->skinAxes[j]->Visible = true;
				} else {
					this->skinAxes[j]->Visible = false;
				}
			}
		}
	}

	hl_mutex_unlock(&controller_mutex);
}

void formMain::output_controller(struct controller *c) {
	if (!hl_active_skin) {
		return;
	}

	hl_mutex_lock(&controller_mutex);
	this->controller = c;
	hl_mutex_unlock(&controller_mutex);

	this->Invalidate();
}

void formMain::loadSkinImages() {
	hl_mutex_create(&controller_mutex);

	if (this->skinButtons) {
		delete(this->skinButtons);
	}
	if (this->skinAxes) {
		delete(this->skinAxes);
	}

	if (!hl_active_skin) {
		return;
	}

	Drawing::Bitmap ^backgroundImage = gcnew Bitmap(String::Concat(gcnew String(hl_active_skin->path), gcnew String(hl_active_skin->background.filename)));
	//backgroundImage->MakeTransparent(Color::White);

	picController->Image = backgroundImage;
	picController->Size = backgroundImage->Size;
	picController->Visible = true;

	this->skinButtons = gcnew array<System::Windows::Forms::PictureBox^>(hl_active_skin->button_count);
	for (int i = 0; i < hl_active_skin->button_count; i++) {
		System::Windows::Forms::PictureBox^ picButton = (gcnew System::Windows::Forms::PictureBox());

		Drawing::Bitmap ^buttonImage = gcnew Bitmap(String::Concat(gcnew String(hl_active_skin->path), gcnew String(hl_active_skin->buttons[i]->filename)));
		buttonImage->MakeTransparent(Color::White);

		picButton->BackColor = Color::Transparent;
		picButton->Enabled = false;
		picButton->Image = buttonImage;
		picButton->Location = System::Drawing::Point(hl_active_skin->buttons[i]->x, hl_active_skin->buttons[i]->y);
		picButton->Name = L"picButton";
		picButton->Name += i;
		picButton->Padding = System::Windows::Forms::Padding(0, 0, 0, 0);
		picButton->Size = buttonImage->Size;
		picButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
		picButton->Visible = false;

		this->skinButtons[i] = picButton;

		this->Controls->Add(picButton);

		picButton->Parent = this->picController;
	}

	this->skinAxes = gcnew array<System::Windows::Forms::PictureBox^>(hl_active_skin->axis_count);
	for (int i = 0; i < hl_active_skin->axis_count; i++) {
		System::Windows::Forms::PictureBox^ picAxis = (gcnew System::Windows::Forms::PictureBox());

		Drawing::Bitmap ^axisImage = gcnew Bitmap(String::Concat(gcnew String(hl_active_skin->path), gcnew String(hl_active_skin->axes[i]->filename)));
		axisImage->MakeTransparent(Color::White);

		picAxis->BackColor = Color::Transparent;
		picAxis->Enabled = false;
		picAxis->Image = axisImage;
		picAxis->Location = System::Drawing::Point(hl_active_skin->axes[i]->x, hl_active_skin->axes[i]->y);
		picAxis->Name = L"picAxis";
		picAxis->Name += i;
		picAxis->Padding = System::Windows::Forms::Padding(0, 0, 0, 0);
		picAxis->Size = axisImage->Size;
		picAxis->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
		picAxis->Visible = false;

		this->skinAxes[i] = picAxis;

		this->Controls->Add(picAxis);

		picAxis->Parent = this->picController;
	}
}