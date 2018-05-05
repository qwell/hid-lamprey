#include "include/lamprey.h"

#include "include/skin.h"

#include "include/display-win32-settings.h"

using namespace System;
using namespace System::Windows::Forms;

using namespace hidlamprey;

System::Void formSettings::formSettings_Load(System::Object^  sender, System::EventArgs^  e) {
	treeView1->BeginUpdate();
	for (int i = 0; i < hl_skin_count; i++) {
		TreeNode ^node = gcnew TreeNode(gcnew String(hl_skins[i]->name));
		for (int j = 0; j < hl_skins[i]->background_count; j++) {
			node->Nodes->Add(gcnew String(hl_skins[i]->backgrounds[j]->name));
		}
		treeView1->Nodes->Add(node);
	}
	treeView1->EndUpdate();
}