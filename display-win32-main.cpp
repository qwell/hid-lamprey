#include "include/lamprey.h"

#include "include/controller.h"

#include "include/display-win32-main.h"

using namespace System;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;

using namespace hidlamprey;

void formMain::output_controller(IntPtr controller) {
	if (!this->imageControllerLoaded) {
		return;
	}

	if (picController->InvokeRequired) {
		picController->Invoke(gcnew Action<IntPtr>(this, &formMain::output_controller), controller);
	} else {
		struct controller_display *c = (struct controller_display *)controller.ToPointer();

		Graphics^ g = picController->CreateGraphics();
		Pen^ pen = gcnew Pen(Color::FromArgb(255, 0, 0, 255));
		Random^ r = gcnew Random;

		g->DrawString(gcnew String(c->name), gcnew System::Drawing::Font(FontFamily::GenericMonospace, 16), gcnew SolidBrush(Color::Black), Point(50, 50));
		g->DrawEllipse(pen, System::Drawing::Rectangle(r->Next(0, 400), r->Next(0, 200), 50, 50));
	}
}