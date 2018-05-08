#include "include/lamprey.h"

#include "include/controller.h"
#include "include/skin.h"

#include "include/display-win32-main.h"
#include "include/display-win32-settings.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;

using namespace hidlamprey;

void formSettings::output_raw(const char *device, const char *rawname, int value) {
}

System::Void formSettings::formSettings_Load(System::Object^  sender, System::EventArgs^  e) {
	tvSkins->BeginUpdate();
	for (int i = 0; i < hl_skin_count; i++) {
		TreeNode ^node = gcnew TreeNode(gcnew String(hl_skins[i]->name));
		for (int j = 0; j < hl_skins[i]->background_count; j++) {
			node->Nodes->Add(gcnew String(hl_skins[i]->backgrounds[j]->name));
		}
		tvSkins->Nodes->Add(node);
	}
	tvSkins->EndUpdate();

	tvMappings->BeginUpdate();
	for (int i = 0; i < input_mapping_count; i++) {
		if (!input_mappings[i]->builtin) {
			String ^strDevice = gcnew String(input_mappings[i]->device);
			TreeNode ^nodeDevice;
			for (int j = 0; j < this->tvMappings->Nodes->Count; j++) {
				if (strDevice  == this->tvMappings->Nodes[j]->Text) {
					nodeDevice = tvMappings->Nodes[j];
					break;
				}
			}
			if (!nodeDevice) {
				nodeDevice = gcnew TreeNode(strDevice);
			}

			for (int j = 0; j < codelookup_count / sizeof(*codelookups); j++) {
				struct codelookup type = codelookups[j];
				if (type.type == input_mappings[i]->maptype) {
					for (int k = 0; k < sizeof(type.codes) / sizeof(*type.codes); k++) {
						struct codelookup_code code = type.codes[k];
						if (code.code == input_mappings[i]->mapcode) {
							struct button_code *button = (struct button_code *)calloc(1, sizeof(*button));

							char text[256];
							snprintf(text, sizeof(text), "%s  =  %s", input_mappings[i]->rawname, code.description ? code.description : code.codestr);

							TreeNode ^nodeButton = gcnew TreeNode(gcnew String(text));

							button->type = type.type;
							button->code = code.code;

							nodeButton->Name = gcnew String(input_mappings[i]->rawname);
							nodeButton->Tag = IntPtr((void *)button);

							nodeDevice->Nodes->Add(nodeButton);
						}
					}
				}
			}

			if (!nodeDevice->TreeView) {
				tvMappings->Nodes->Add(nodeDevice);
			}
		}
	}
	tvMappings->EndUpdate();

	tvMapButtons->BeginUpdate();
	for (int i = 0; i < codelookup_count / sizeof(*codelookups); i++) {
		struct codelookup type = codelookups[i];
		if (type.codes[i].codestr) {
			TreeNode ^nodeType = gcnew TreeNode(gcnew String(type.description ? type.description : type.typestr));
			nodeType->Name = gcnew String(type.description ? type.description : type.typestr);

			for (int j = 0; j < sizeof(type.codes) / sizeof(*type.codes); j++) {
				struct codelookup_code code = type.codes[j];

				if (code.codestr) {
					TreeNode ^nodeCode = gcnew TreeNode(gcnew String(code.description ? code.description : code.codestr));
					nodeCode->Name = gcnew String(code.description ? code.description : code.codestr);

					struct button_code *button = (struct button_code *)calloc(1, sizeof(*button));

					button->type = type.type;
					button->code = code.code;

					nodeCode->Tag = IntPtr((void *)button);
					/*
					IntPtr tag = (IntPtr)nodeCode->Tag;
					struct button_code *foo = (struct button_code *)tag.ToPointer();
					*/

					nodeType->Nodes->Add(nodeCode);
				}
			}
			tvMapButtons->Nodes->Add(nodeType);
		}
	}
	tvMapButtons->EndUpdate();
}
System::Void formSettings::treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
	if (e->Node->Level == 1) {
		char *name = (char *)(void *)Marshal::StringToHGlobalAnsi(e->Node->Parent->Text);
		char *background = (char *)(void *)Marshal::StringToHGlobalAnsi(e->Node->Text);

		if (hl_settings->skin->name) {
			free(hl_settings->skin->name);
		}
		hl_settings->skin->name = strdup(name);

		if (hl_settings->skin->background) {
			free(hl_settings->skin->background);
		}
		hl_settings->skin->background = strdup(background);

		this->formMain->loadSkinImages(name, background);
	}
}
System::Void formSettings::tvMapButtons_ItemDrag(System::Object^  sender, System::Windows::Forms::ItemDragEventArgs^  e) {
	DoDragDrop(e->Item, DragDropEffects::Link);
}
System::Void formSettings::tvMappings_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
	e->Effect = DragDropEffects::Link;
}
System::Void formSettings::tvMappings_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
	if (e->Data->GetDataPresent("System.Windows.Forms.TreeNode", false)) {
		Point pt = ((TreeView ^)sender)->PointToClient(Point(e->X, e->Y));
		TreeNode ^nodeDest = ((TreeView ^)sender)->GetNodeAt(pt);
		if (nodeDest && nodeDest->Level == 1) {
			TreeNode ^nodeLink = (TreeNode ^)e->Data->GetData("System.Windows.Forms.TreeNode");
			nodeDest->Tag = nodeLink->Tag;
			nodeDest->Text = nodeDest->Name + "  =  " + nodeLink->Text;
		}
	}
}
