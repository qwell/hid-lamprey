#include "include/lamprey.h"

#include "include/display-win32-main.h"

using namespace System;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;

using namespace hidlamprey;

void formMain::output_controller() {
	if (button1->InvokeRequired) {
		button1->Invoke(gcnew Action(this, &formMain::output_controller));
	} else {
		button1->Text = L"Cheese";
	}
}