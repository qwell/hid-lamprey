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

	for (int j = 0; j < sizeof(controller->mapping) / sizeof(*controller->mapping); j++) {
		struct controller_display_mapping *mapping = &controller->mapping[j];

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
			for (int l = 0; l < hl_active_skin->axis_count; l++) {
				if ((trigger->type == hl_active_skin->axes[l]->type_x && trigger->code == hl_active_skin->axes[l]->code_x) ||
					(trigger->type == hl_active_skin->axes[l]->type_y && trigger->code == hl_active_skin->axes[l]->code_y)) {
					int offset_x = this->skinAxes[l]->Location.X - hl_active_skin->axes[l]->x;
					int offset_y = this->skinAxes[l]->Location.Y - hl_active_skin->axes[l]->y;

					if (trigger->type == hl_active_skin->axes[l]->type_x && trigger->code == hl_active_skin->axes[l]->code_x) {
						if (mapping->value && mapping->realvalue < 0 && trigger->trigger_low < 0) {
							offset_x = mapping->realvalue / (256 / hl_active_skin->axes[l]->offset_x);
						} else if (mapping->value && mapping->realvalue > 0 && trigger->trigger_high > 0) {
							offset_x = mapping->realvalue / (256 / hl_active_skin->axes[l]->offset_x);
						} else {
							offset_x = 0;
						}

						this->skinAxes[l]->Location = Drawing::Point(hl_active_skin->axes[l]->x + offset_x, this->skinAxes[l]->Location.Y);
						if (offset_x) {
							this->skinAxes[l]->Visible = true;
						}
					}

					if (trigger->type == hl_active_skin->axes[l]->type_y && trigger->code == hl_active_skin->axes[l]->code_y) {
						if (mapping->value && mapping->realvalue < 0 && trigger->trigger_low < 0) {
							offset_y = mapping->realvalue / (256 / hl_active_skin->axes[l]->offset_y);
						} else if (mapping->value && mapping->realvalue > 0 && trigger->trigger_high > 0) {
							offset_y = mapping->realvalue / (256 / hl_active_skin->axes[l]->offset_y);
						} else {
							offset_y = 0;
						}

						this->skinAxes[l]->Location = Drawing::Point(this->skinAxes[l]->Location.X, hl_active_skin->axes[l]->y + offset_y);
						if (offset_y) {
							this->skinAxes[l]->Visible = true;
						}
					}

					if (offset_x == 0 && offset_y == 0) {
						this->skinAxes[l]->Visible = false;
					}
				}
			}
		}
	}

	hl_mutex_unlock(&controller_mutex);
}

void formMain::output_controller(struct controller_display *c) {
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