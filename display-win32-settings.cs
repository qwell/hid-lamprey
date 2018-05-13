using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace hidlamprey {
    public partial class formSettings : Form {

        public formSettings(formMain formMain)
        {
            this.formMain = formMain;
            InitializeComponent();
            //
            //TODO: Add the constructor code here
            //
        }

        private void update_mapping(String strDevice, String strButtonName, IntPtr tag) {
#if false
	        struct button_code *button_code = (struct button_code *)tag.ToPointer();

	        struct input_mapping *dinput_mapping;

	        const char *device = (char *)(void *)Marshal.StringToHGlobalAnsi(strDevice);
	        const char *rawname = (char *)(void *)Marshal.StringToHGlobalAnsi(strButtonName);

	        for (int i = 0; i < input_mapping_count; i++) {
		        dinput_mapping = input_mappings[i];

		        if (!strcmp(device, dinput_mapping->device) && !strcmp(rawname, dinput_mapping->rawname)) {
			        if (!button_code) {
				        struct input_mapping **test = input_mappings;
				        free(input_mappings[i]);

				        for (int j = i; j < input_mapping_count - 1; j++) {
					        input_mappings[j] = input_mappings[j + 1];
				        }

				        input_mapping_count--;
			        } else {
				        dinput_mapping->mapvalue = 0;
				        dinput_mapping->builtin = false;
				        dinput_mapping->maptype = button_code->type;
				        dinput_mapping->mapcode = button_code->code;
			        }

			        return;
		        }
	        }

	        dinput_mapping = (struct input_mapping *)malloc(sizeof(struct input_mapping));
	        dinput_mapping->mapvalue = 0;
	        dinput_mapping->builtin = false;
	        dinput_mapping->device = strdup((char *)device);
	        dinput_mapping->rawname = strdup((char *)rawname);
	        if (button_code) {
		        /* We shouldn't have gotten here, but compensate anyways. */
		        dinput_mapping->maptype = button_code->type;
		        dinput_mapping->mapcode = button_code->code;
	        }

	        input_mappings = (struct input_mapping **)realloc(input_mappings, (input_mapping_count + 1) * sizeof(*input_mappings));
	        input_mappings[input_mapping_count++] = dinput_mapping;
#endif
        }
        void output_raw(String device, String rawname, Int16 value) {
#if false
            if (this->tvMappings->InvokeRequired) {
		        this->tvMappings->Invoke(gcnew Action<String , String , Int16>(this, &formSettings.output_raw), device, rawname, value);
	        } else {
		        TreeNode nodeDevice;
		        TreeNode nodeButton;

		        for (int i = 0; i < this->tvMappings->Nodes->Count; i++) {
			        if (device == this->tvMappings->Nodes[i]->Text) {
				        nodeDevice = tvMappings->Nodes[i];

				        for (int j = 0; j < nodeDevice->Nodes->Count; j++) {
					        if (nodeDevice->Nodes[j]->Name == rawname) {
						        if (value != 0) {
							        nodeDevice->Nodes[j]->ForeColor = Color.Gold;
						        } else if (nodeDevice->Nodes[j]->Name == nodeDevice->Nodes[j]->Text) {
							        nodeDevice->Nodes[j]->ForeColor = Color.Red;
						        } else {
							        nodeDevice->Nodes[j]->ForeColor = Color.Green;
						        }
						        return;
					        }
				        }
				        break;
			        }
		        }
		        if (!nodeDevice) {
			        nodeDevice = gcnew TreeNode(device);
			        nodeDevice->Name = device;
		        }

		        tvMappings->BeginUpdate();

		        nodeButton = gcnew TreeNode(rawname);
		        nodeButton->Name = rawname;
		        nodeButton->ForeColor = Color.Red;

		        nodeDevice->Nodes->Add(nodeButton);
		        nodeDevice->Expand();

		        if (!nodeDevice->TreeView) {
			        tvMappings->Nodes->Add(nodeDevice);
		        }

		        tvMappings->EndUpdate();
	        }
#endif
        }

        void formSettings_Load(System.Object  sender, System.EventArgs  e) {
#if false
            toolTip1->SetToolTip(this->tvMappings, "Double-click to remove current mapping.  Press any button to add a new mapping target.");
	        toolTip1->SetToolTip(this->tvMapButtons, "Drag a button to a mapping target (left) to assign a button mapping.");

	        tvSkins->BeginUpdate();
	        for (int i = 0; i < hl_skin_count; i++) {
		        TreeNode node = gcnew TreeNode(gcnew String(hl_skins[i]->name));
		        for (int j = 0; j < hl_skins[i]->background_count; j++) {
			        node->Nodes->Add(gcnew String(hl_skins[i]->backgrounds[j]->name));
		        }
		        tvSkins->Nodes->Add(node);
	        }
	        tvSkins->EndUpdate();

	        tvMappings->BeginUpdate();
	        for (int i = 0; i < input_mapping_count; i++) {
		        if (!input_mappings[i]->builtin) {
			        String strDevice = gcnew String(input_mappings[i]->device);
			        TreeNode nodeDevice;
			        for (int j = 0; j < this->tvMappings->Nodes->Count; j++) {
				        if (strDevice  == this->tvMappings->Nodes[j]->Text) {
					        nodeDevice = tvMappings->Nodes[j];
					        break;
				        }
			        }
			        if (!nodeDevice) {
				        nodeDevice = gcnew TreeNode(strDevice);
				        nodeDevice->Name = gcnew String(strDevice);
			        }

			        for (int j = 0; j < codelookup_count / sizeof(*codelookups); j++) {
				        struct codelookup type = codelookups[j];
				        if (type.type == input_mappings[i]->maptype) {
					        for (int k = 0; k < sizeof(type.codes) / sizeof(*type.codes); k++) {
						        struct codelookup_code code = type.codes[k];
						        if (code.code == input_mappings[i]->mapcode) {
							        struct button_code *button = (struct button_code *)calloc(1, sizeof(*button));

							        char text[256];
							        snprintf(text, sizeof(text), "%s  |  %s", input_mappings[i]->rawname, code.description ? code.description : code.codestr);

							        TreeNode nodeButton = gcnew TreeNode(gcnew String(text));

							        button->type = type.type;
							        button->code = code.code;

							        nodeButton->Name = gcnew String(input_mappings[i]->rawname);
							        nodeButton->Tag = IntPtr((void *)button);
							        nodeButton->ForeColor = Color.Green;

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
	        tvMappings->ExpandAll();
	        tvMappings->EndUpdate();

	        tvMapButtons->BeginUpdate();
	        for (int i = 0; i < codelookup_count / sizeof(*codelookups); i++) {
		        TreeNode nodeCategory;

		        struct codelookup type = codelookups[i];
		        if (type.codes[i].codestr) {
			        for (int j = 0; j < sizeof(type.codes) / sizeof(*type.codes); j++) {
				        struct codelookup_code code = type.codes[j];

				        if (code.codestr) {
					        String strCategory;

					        switch (code.category) {
					        case GamepadButton:
						        strCategory = gcnew String("Gamepad Buttons");
						        break;
					        case MouseButton:
						        strCategory = gcnew String("Mouse Buttons");
						        break;
					        case KeyboardKey:
						        strCategory = gcnew String("Keyboard Keys");
						        break;
					        case KeyboardNumpadKey:
						        strCategory = gcnew String("Keyboard Numpad Keys");
						        break;
					        case KeyboardMiscKey:
						        strCategory = gcnew String("Keyboard Misc Keys");
						        break;
					        case AbsoluteAxis:
						        strCategory = gcnew String("Absolute Axis");
						        break;
					        case RelativeAxis:
						        strCategory = gcnew String("Relative Axis");
						        break;
					        default:
						        strCategory = gcnew String("Other");
						        break;
					        }

					        if (!nodeCategory || nodeCategory->Text != strCategory) {
						        nodeCategory = nullptr;
						        for (int k = 0; k < this->tvMapButtons->Nodes->Count; k++) {
							        if (strCategory == this->tvMapButtons->Nodes[k]->Text) {
								        nodeCategory = tvMapButtons->Nodes[k];
								        break;
							        }
						        }
					        }
					        if (!nodeCategory) {
						        nodeCategory = gcnew TreeNode(strCategory);
						        nodeCategory->Name = gcnew String(strCategory);
					        }

					        TreeNode nodeCode = gcnew TreeNode(gcnew String(code.description ? code.description : code.codestr));
					        nodeCode->Name = gcnew String(code.description ? code.description : code.codestr);

					        struct button_code *button = (struct button_code *)calloc(1, sizeof(*button));

					        button->type = type.type;
					        button->code = code.code;

					        nodeCode->Tag = IntPtr((void *)button);

					        nodeCategory->Nodes->Add(nodeCode);
					        if (!nodeCategory->TreeView) {
						        tvMapButtons->Nodes->Add(nodeCategory);
					        }
				        }
			        }
		        }
	        }
	        tvMapButtons->EndUpdate();
#endif
        }
        void tvSkins_AfterSelect(System.Object  sender, System.Windows.Forms.TreeViewEventArgs  e) {
#if false
            if (e->Node->Level == 1) {
		        char *name = (char *)(void *)Marshal.StringToHGlobalAnsi(e->Node->Parent->Text);
		        char *background = (char *)(void *)Marshal.StringToHGlobalAnsi(e->Node->Text);

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
#endif
        }
        void tvMapButtons_ItemDrag(System.Object  sender, System.Windows.Forms.ItemDragEventArgs  e) {
#if false
            TreeNode node = (TreeNode )e->Item;
	        if (node && node->Level == 1) {
		        DoDragDrop(e->Item, DragDropEffects.Link);
	        }
#endif
        }
        void tvMappings_DragEnter(System.Object  sender, System.Windows.Forms.DragEventArgs  e) {
#if false
            e->Effect = DragDropEffects.Link;
#endif
        }
        void tvMappings_DragDrop(System.Object  sender, System.Windows.Forms.DragEventArgs  e) {
#if false
            if (e->Data->GetDataPresent("System.Windows.Forms.TreeNode", false)) {
		        Point pt = ((TreeView )sender)->PointToClient(Point(e->X, e->Y));
		        TreeNode nodeDest = ((TreeView )sender)->GetNodeAt(pt);
		        if (nodeDest && nodeDest->Level == 1) {
			        TreeNode nodeLink = (TreeNode )e->Data->GetData("System.Windows.Forms.TreeNode");
			        nodeDest->Tag = nodeLink->Tag;
			        nodeDest->Text = nodeDest->Name + "  |  " + nodeLink->Text;
			        nodeDest->ForeColor = Color.Green;

			        this->update_mapping(nodeDest->Parent->Name, nodeDest->Name, (IntPtr)nodeDest->Tag);
		        }
	        }
#endif
        }
        void tvMappings_NodeMouseDoubleClick(System.Object  sender, System.Windows.Forms.TreeNodeMouseClickEventArgs  e) {
#if false
            if (e->Node->Level == 1) {
		        this->update_mapping(e->Node->Parent->Name, e->Node->Name, IntPtr(nullptr));

		        e->Node->Tag = nullptr;
		        e->Node->Text = e->Node->Name;
		        e->Node->Remove();
	        }
#endif
        }
    }
}