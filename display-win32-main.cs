using System;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace hidlamprey {
    public partial class formMain : Form
    {
        private formMain()
        {
            InitializeComponent();
        }

        private hl_mutex_t controller_mutex;

        private System.Void picController_onPaint(System.Object sender, System.Windows.Forms.PaintEventArgs e) {
	        if (!controller) {
		        return;
	        }

	        hl_mutex_lock(&controller_mutex);

	        for (int i = 0; i < controller.button_count; i++) {
		        struct button_state *button = controller.buttons[i];
		        for (int j = 0; j < skinActive.button_count; j++) {
			        struct hl_skin_button *skin_button = skinActive.buttons[j];
			        if (button.type == skin_button.type && button.code == skin_button.code) {
				        if (button.value) {
					        this.skinButtons[j].Visible = true;
				        }
				        else {
					        this.skinButtons[j].Visible = false;
				        }
			        }
		        }

		        for (int j = 0; j < skinActive.axis_count; j++) {
			        struct hl_skin_axis *skin_axis = skinActive.axes[j];
			        if ((button.type == skin_axis.type_x && button.code == skin_axis.code_x) ||
				        (button.type == skin_axis.type_y && button.code == skin_axis.code_y)) {
				        int offset_x = this.skinAxes[j].Location.X - skin_axis.x;
				        int offset_y = this.skinAxes[j].Location.Y - skin_axis.y;

				        if (button.type == skin_axis.type_x && button.code == skin_axis.code_x) {
					        if (button.value) {
						        offset_x = button.value / (256 / skin_axis.offset_x);
					        }
					        else {
						        offset_x = 0;
					        }
				        }

				        if (button.type == skin_axis.type_y && button.code == skin_axis.code_y) {
					        if (button.value) {
						        offset_y = button.value / (256 / skin_axis.offset_y);
					        }
					        else {
						        offset_y = 0;
					        }
				        }

				        this.skinAxes[j].Location = Drawing.Point(skin_axis.x + offset_x, skin_axis.y + offset_y);
				        if (offset_x || offset_y) {
					        this.skinAxes[j].Visible = true;
				        }
				        else {
					        this.skinAxes[j].Visible = false;
				        }
			        }
		        }
	        }

	        hl_mutex_unlock(&controller_mutex);
        }

        private System.Void tsmiAlwaysOnTop_Click(System.Object sender, System.EventArgs e) {
	        this.TopMost = tsmiAlwaysOnTop.Checked;
        }

        System.Void tsmiExit_Click(System.Object sender, System.EventArgs e) {
	        this.Close();
        }

        System.Void tmsiSettings_Click(System.Object  sender, System.EventArgs  e) {
	        settings.ShowDialog();
        }

        System.Void formMain_Load(System.Object  sender, System.EventArgs  e) {
	        this.DoubleBuffered = true;

	        settings = new formSettings(this);
        }

        private System.Void formMain_Closed(System.Object sender, System.EventArgs e) {
        }

        private System.Void formMain_Shown(System.Object sender, System.EventArgs e) {
	        this.loadSkinImages(hl_settings.skin.name, hl_settings.skin.background);
        }

        private System.Void formMain_MouseDown(System.Object sender, System.Windows.Forms.MouseEventArgs e) {
	        if (e.Button == System.Windows.Forms.MouseButtons.Left) {
		        const int HT_CAPTION = 2;
		        ReleaseCapture();
		        SendMessage(static_cast<HWND>(this.Handle.ToPointer()), WM_NCLBUTTONDOWN, HT_CAPTION, 0);
	        }
        }

        private void refreshImage() {
	        this.picController.Refresh();
        }

        public void output_controller(struct controller *c) {
	        if (!skinActive) {
		        return;
	        }

	        hl_mutex_lock(&controller_mutex);
	        this.controller = c;
	        hl_mutex_unlock(&controller_mutex);

	        if (this.picController.InvokeRequired) {
		        this.picController.Invoke(new Action(this, &formMain.refreshImage));
	        }
	        else {
		        this.refreshImage();
	        }
        }

        private void output_raw(const char *device, const char *rawname, int value) {
	        if (settings.Visible) {
		        settings.output_raw(new String(device), new String(rawname), Int16(value));
	        }
        }

        private void loadSkinImages(char *skin_name, char *skin_background) {
	        hl_mutex_create(&controller_mutex);

	        if (this.skinButtons) {
		        delete(this.skinButtons);
	        }
	        if (this.skinAxes) {
		        delete(this.skinAxes);
	        }

	        for (int i = 0; i < hl_skin_count; i++) {
		        if (!strcmp(skin_name, hl_skins[i].name)) {
			        skinActive = hl_skins[i];

			        for (int j = 0; j < skinActive.background_count; j++) {
				        if (!strcmp(skin_background, skinActive.backgrounds[j].name)) {
					        skinActiveBackground = skinActive.backgrounds[j];
					        break;
				        }
			        }
			        break;
		        }
	        }

	        if (!skinActive) {
		        return;
	        }

	        Drawing.Bitmap backgroundImage = new Bitmap(String.Concat(new String(skinActive.path), new String(skinActiveBackground.filename)));
	        //backgroundImage.MakeTransparent(Color.White);

	        picController.Image = backgroundImage;
	        picController.Size = backgroundImage.Size;
	        picController.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;

	        this.skinButtons = new array<System.Windows.Forms.PictureBox>(skinActive.button_count);
	        for (int i = 0; i < skinActive.button_count; i++) {
		        System.Windows.Forms.PictureBox picButton = (new System.Windows.Forms.PictureBox());

		        Drawing.Bitmap buttonImage = new Bitmap(String.Concat(new String(skinActive.path), new String(skinActive.buttons[i].filename)));
		        buttonImage.MakeTransparent(Color.White);

		        picButton.Anchor = AnchorStyles.Left | AnchorStyles.Top;
		        picButton.BackColor = Color.Transparent;
		        picButton.Enabled = false;
		        picButton.Image = buttonImage;
		        picButton.Location = System.Drawing.Point(skinActive.buttons[i].x, skinActive.buttons[i].y);
		        picButton.Name = L"picButton";
		        picButton.Name += i;
		        picButton.Padding = System.Windows.Forms.Padding(0, 0, 0, 0);
		        picButton.Size = buttonImage.Size;
		        picButton.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
		        picButton.Visible = false;

		        this.skinButtons[i] = picButton;

		        this.Controls.Add(picButton);

		        picButton.Parent = this.picController;
	        }

	        this.skinAxes = new System.Windows.Forms.PictureBox[skinActive.axis_count];
	        for (int i = 0; i < skinActive.axis_count; i++) {
		        System.Windows.Forms.PictureBox picAxis = (new System.Windows.Forms.PictureBox());

		        Drawing.Bitmap axisImage = new System.Drawing.Bitmap(String.Concat(new String(skinActive.path), new String(skinActive.axes[i].filename)));
		        axisImage.MakeTransparent(System.Drawing.Color.White);

		        picAxis.Anchor = AnchorStyles.Left | AnchorStyles.Top;
		        picAxis.BackColor = System.Drawing.Color.Transparent;
		        picAxis.Enabled = false;
		        picAxis.Image = axisImage;
		        picAxis.Location = new System.Drawing.Point(skinActive.axes[i].x, skinActive.axes[i].y);
		        picAxis.Name = "picAxis";
		        picAxis.Name += i;
		        picAxis.Padding = new System.Windows.Forms.Padding(0, 0, 0, 0);
		        picAxis.Size = axisImage.Size;
		        picAxis.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
		        picAxis.Visible = false;

		        this.skinAxes[i] = picAxis;

		        this.Controls.Add(picAxis);

		        picAxis.Parent = this.picController;
	        }

	        float scale = 640 * ((float)1 / backgroundImage.Width);
	        picController.Scale(new System.Drawing.SizeF(scale, scale));
	        picController.Visible = true;
        }
    }
}