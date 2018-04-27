#include "include/lamprey.h"

#include "include/controller.h"
#include "include/skin.h"

#include "include/display-win32-main.h"

using namespace System;
using namespace System::Drawing::Drawing2D;
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

	if (picControllerDisplay->InvokeRequired) {
		picControllerDisplay->Invoke(gcnew Action<IntPtr>(this, &formMain::output_controller), controller);
	} else {
		struct controller_display *c = (struct controller_display *)controller.ToPointer();

		/*
		Bitmap^ bitmap = gcnew Bitmap(picControllerDisplay->Width, picControllerDisplay->Height);
		Graphics^ g = Graphics::FromImage(bitmap);

		GraphicsPath^ path = gcnew GraphicsPath();

		bitmap->MakeTransparent();
		*/

		//g->DrawString(gcnew String(c->name), gcnew System::Drawing::Font(FontFamily::GenericMonospace, 16), gcnew SolidBrush(Color::Black), Point(50, 50));

		for (int j = 0; j < sizeof(c->mapping) / sizeof(*c->mapping); j++) {
			struct controller_display_mapping *mapping = &c->mapping[j];

			/*
			if (mapping->value == 0) {
				continue;
			}
			*/

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

				/*
				if (trigger->code == BTN_SOUTH) {
					path->AddEllipse(Drawing::Rectangle(Point(478, 167), Drawing::Size(48, 48)));
				} else if (trigger->code == BTN_EAST) {
					path->AddEllipse(Drawing::Rectangle(Point(539, 121), Drawing::Size(48, 48)));
				} else if (trigger->code == BTN_NORTH) {
					path->AddEllipse(Drawing::Rectangle(Point(478, 72), Drawing::Size(48, 48)));
				} else if (trigger->code == BTN_WEST) {
					path->AddEllipse(Drawing::Rectangle(Point(419, 119), Drawing::Size(48, 48)));
				} else if (trigger->code == BTN_TL) {
					array<Point>^ points = {
						Point(68,25),
						Point(68,18),Point(68,18),Point(71,17),
						Point(82,11),Point(92,6),Point(93,6),
						Point(98,5),Point(103,3),Point(112,0),
						Point(161,0),
						Point(216,0),
						Point(213,0),Point(213,8),Point(214,13),
						Point(170,13),
						Point(123,13),
						Point(114,14),Point(97,19),Point(92,21),
						Point(83,24),Point(78,27),Point(68,32),
					};
					array<Byte>^ types = {
						(Byte)PathPointType::Start,
						(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,
						(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,
						(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,
						(Byte)PathPointType::Line,
						(Byte)PathPointType::Line,
						(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,
						(Byte)PathPointType::Line,
						(Byte)PathPointType::Line,
						(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,
						(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,
					};

					path->AddPath(gcnew GraphicsPath(points, types), false);
				}
				else if (trigger->code == BTN_TR) {
					array<Point>^ points = {
						Point(561,26),
						Point(556,24),Point(548,21),Point(542,19),
						Point(526,14),Point(516,13),Point(468,13),
						Point(425,13),
						Point(425,9),
						Point(426,0),Point(423,0),Point(478,0),
						Point(527,0),
						Point(538,4),
						Point(544,6),Point(554,10),Point(560,13),
						Point(571,18),
						Point(571,25),
						Point(571,28),Point(571,31),Point(570,31),
						Point(570,31),Point(566,29),Point(561,26),
					};
					array<Byte>^ types = {
						(Byte)PathPointType::Start,
						(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,
						(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,
						(Byte)PathPointType::Line,
						(Byte)PathPointType::Line,
						(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,
						(Byte)PathPointType::Line,
						(Byte)PathPointType::Line,
						(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,
						(Byte)PathPointType::Line,
						(Byte)PathPointType::Line,
						(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,
						(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,(Byte)PathPointType::Bezier,
					};

					path->AddPath(gcnew GraphicsPath(points, types), false);
				} else if (trigger->code == BTN_SELECT) {
					path->StartFigure();
					path->AddArc(236, 162, 26, 26, -130, -180);
					path->AddArc(266, 139, 26, 26, 50, -180);
					path->CloseFigure();
				} else if (trigger->code == BTN_START) {
					path->StartFigure();
					path->AddArc(304, 162, 26, 26, -130, -180);
					path->AddArc(334, 139, 26, 26, 50, -180);
					path->CloseFigure();
				} else if (trigger->code == BTN_DPAD_UP) {
					array<Point>^ points = {
						Point(139, 98),
						Point(150, 120),
						Point(128, 120)
					};
					path->AddPolygon(points);
				} else if (trigger->code == BTN_DPAD_RIGHT) {
					array<Point>^ points = {
						Point(164, 134),
						Point(186, 145),
						Point(164, 156)
					};
					path->AddPolygon(points);
				} else if (trigger->code == BTN_DPAD_DOWN) {
					array<Point>^ points = {
						Point(139, 194),
						Point(150, 172),
						Point(128, 172)
					};
					path->AddPolygon(points);
				} else if (trigger->code == BTN_DPAD_LEFT) {
					array<Point>^ points = {
						Point(112, 134),
						Point(92, 145),
						Point(112, 156)
					};
					path->AddPolygon(points);
				} else {
					continue;
				}
				*/
			}
		}

		/*
		g->FillRegion(gcnew SolidBrush(Color::Cyan), gcnew Drawing::Region(path));

		picControllerDisplay->BackgroundImage = bitmap;
		*/
	}
}

void formMain::loadSkinImages() {
	int count = sizeof(testbuttons) / sizeof(*testbuttons);

	delete(this->skinButtons);
	this->skinButtons = gcnew array<System::Windows::Forms::PictureBox^>(count);

	for (int i = 0; i < count; i++) {
		System::Windows::Forms::PictureBox^  picTestButton = (gcnew System::Windows::Forms::PictureBox());

		Drawing::Bitmap ^testimage = gcnew Bitmap(String::Concat(gcnew String(L"skins/lamprey-SNES/"), gcnew String(testbuttons[i].name)));
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