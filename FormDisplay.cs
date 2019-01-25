using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Lamprey
{
    public partial class FormDisplay : Form
    {
        public FormDisplay()
        {
            InitializeComponent();
        }

        void picController_onPaint(object sender, System.Windows.Forms.PaintEventArgs e)
        {
            foreach (Controller.Button ControllerButton in Controller.Instance.Buttons)
            {
                foreach (Skin.Button SkinButton in Settings.Instance.Skin.Buttons)
                {
                    if (ControllerButton.Type == SkinButton.Type && ControllerButton.Code == SkinButton.Code)
                    {
                        if (ControllerButton.Value != 0)
                        {
                            e.Graphics.DrawImage(this.skinButtons[j].Image, new RectangleF(this.skinButtons[j].Location, this.skinButtons[j].Size));
                        }
                    }
                }

                foreach (Skin.Axis SkinAxis in Settings.Instance.Skin.Axes)
                {
                    if ((ControllerButton.Type == SkinAxis.X.Type && ControllerButton.Code == SkinAxis.X.Code) ||
                        (ControllerButton.Type == SkinAxis.Y.Type && ControllerButton.Code == SkinAxis.Y.Code))
                    {
                        int offset_x = this.skinAxes[j].Location.X - SkinAxis.X.X;
                        int offset_y = this.skinAxes[j].Location.Y - SkinAxis.Y.Y;
                        bool visible = false;

                        if (ControllerButton.Type == SkinAxis.X.Type && ControllerButton.Code == SkinAxis.X.Code && (SkinAxis.X.Trigger == 0 || (SkinAxis.X.Trigger > 0 && ControllerButton.Value > SkinAxis.X.Trigger) || (SkinAxis.X.Trigger < 0 && ControllerButton.Value < SkinAxis.X.Trigger)))
                        {
                            if (ControllerButton.Value != 0)
                            {
                                if (SkinAxis.X.Offset != 0)
                                {
                                    offset_x = (ControllerButton.Type == EV_REL ? ControllerButton.Decay : ControllerButton.Value) / (256 / SkinAxis.X.Offset);
                                }
                                else
                                {
                                    offset_x = 0;
                                }
                                visible = true;
                            }
                            else
                            {
                                offset_x = 0;
                            }
                        }

                        if (ControllerButton.Type == SkinAxis.Y.Type && ControllerButton.Code == SkinAxis.Y.Code && (SkinAxis.Y.Trigger == 0 || (SkinAxis.Y.Trigger > 0 && ControllerButton.Value > SkinAxis.Y.Trigger) || (SkinAxis.Y.Trigger < 0 && ControllerButton.Value < SkinAxis.Y.Trigger)))
                        {
                            if (ControllerButton.Value != 0)
                            {
                                if (SkinAxis.Y.Offset != 0)
                                {
                                    offset_y = (ControllerButton.Type == EV_REL ? ControllerButton.Decay : ControllerButton.Value) / (256 / SkinAxis.Y.Offset);
                                }
                                else
                                {
                                    offset_y = 0;
                                }
                                visible = true;
                            }
                            else
                            {
                                offset_y = 0;
                            }
                        }

                        this.skinAxes[j].Location = new Point(SkinAxis.X.X + offset_x, SkinAxis.Y.Y + offset_y);
                        if (visible)
                        {
                            e.Graphics.DrawImage(this.skinAxes[j].Image, new RectangleF(this.skinAxes[j].Location, this.skinAxes[j].Size));
                        }
                    }
                }
            }
        }

        void tsmiAlwaysOnTop_Click(object sender, System.EventArgs e)
        {
            this.TopMost = tsmiAlwaysOnTop.Checked;
        }

        void tsmiExit_Click(object sender, System.EventArgs e)
        {
            this.Close();
        }

        void tmsiSettings_Click(object sender, System.EventArgs e)
        {
            settings.ShowDialog();
        }

        void formMain_Load(object sender, System.EventArgs e)
        {
            this.DoubleBuffered = true;

            settings = new formSettings(this);
        }

        void formMain_Closed(object sender, System.EventArgs e)
        {
        }

        void formMain_Shown(object sender, System.EventArgs e)
        {
            this.loadSkinImages();
        }

        void formMain_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                const int HT_CAPTION = 2;
                ReleaseCapture();
                SendMessage(static_cast<HWND>(this.Handle.ToPointer()), WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            }
        }

        void timer1_Tick(object sender, System.EventArgs e)
        {
            for (int i = 0; i < this.controller.button_count; i++)
            {
                if (this.controller.buttons[i].type == EV_REL && this.controller.buttons[i].value != 0)
                {
                    int16_t decay_amount;
                    if (abs(this.controller.buttons[i].value) < 10)
                    {
                        decay_amount = this.controller.buttons[i].value;
                    }
                    else
                    {
                        decay_amount = this.controller.buttons[i].value * .1;
                    }
                    this.controller.buttons[i].decay -= decay_amount;
                    if (abs(this.controller.buttons[i].decay) < abs(decay_amount))
                    {
                        this.controller.buttons[i].decay = 0;
                        this.controller.buttons[i].value = 0;
                    }
                    this.needRefresh = true;
                }
            }

            if (this.needRefresh)
            {
                if (this.picController.InvokeRequired)
                {
                    this.picController.Invoke(new Action(this.refreshImage));
                }
                else
                {
                    this.refreshImage();
                }
            }
        }

        void refreshImage()
        {
            this.needRefresh = false;

            this.picController.Refresh();
        }

        void output_controller(struct controller * c) {
	        if (!skinActive) {
		        return;
	        }

            this.controller = c;

            this.needRefresh = true;
        }

    void output_raw(const char* device, const char* rawname, int value)
    {
        if (settings && settings.Visible)
        {
            ((formSettings)settings).output_raw(new String(device), new String(rawname), Int16(value));
        }
    }

    void loadSkinImages()
    {
        if (Settings.Instance.Skin == null)
        {
            return;
        }

        Drawing.Bitmap backgroundImage = new Bitmap(String.Concat(new String(skinActive.path), new String(skinActiveBackground.filename)));
        backgroundImage.MakeTransparent(Color.White);

        picController.Image = backgroundImage;
        picController.Size = backgroundImage.Size;
        picController.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;

        this.skinButtons = new array<System.Windows.Forms.PictureBox>(skinActive.button_count);
        for (int i = 0; i < skinActive.button_count; i++)
        {
            System.Windows.Forms.PictureBox picButton = (new System.Windows.Forms.PictureBox());

            Drawing.Bitmap buttonImage = new Bitmap(String.Concat(new String(skinActive.path), new String(skinActive.buttons[i].filename)));
            buttonImage.MakeTransparent(Color.White);

            picButton.Anchor = AnchorStyles.Left | AnchorStyles.Top;
            picButton.BackColor = Color.Transparent;
            picButton.Enabled = false;
            picButton.Image = buttonImage;
            picButton.Location = new Point(skinActive.buttons[i].x, skinActive.buttons[i].y);
            picButton.Name = "picButton";
            picButton.Name += i;
            picButton.Padding = new System.Windows.Forms.Padding(0, 0, 0, 0);
            picButton.Size = buttonImage.Size;
            picButton.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            picButton.Visible = false;

            this.skinButtons[i] = picButton;

            this.Controls.Add(picButton);

            picButton.Parent = this.picController;
        }


        this.skinAxes = new System.Windows.Forms.PictureBox[skinActive.axis_count];
        for (int i = 0; i < skinActive.axis_count; i++)
        {
            System.Windows.Forms.PictureBox picAxis = (new System.Windows.Forms.PictureBox());

            Drawing.Bitmap axisImage = new Bitmap(String.Concat(new String(skinActive.path), new String(skinActive.axes[i].filename)));
            axisImage.MakeTransparent(Color.White);

            picAxis.Anchor = AnchorStyles.Left | AnchorStyles.Top;
            picAxis.BackColor = Color.Transparent;
            picAxis.Enabled = false;
            picAxis.Image = axisImage;
            picAxis.Location = System.Drawing.Point(skinActive.axes[i].x, skinActive.axes[i].y);
            picAxis.Name = "picAxis";
            picAxis.Name += i;
            picAxis.Padding = System.Windows.Forms.Padding(0, 0, 0, 0);
            picAxis.Size = axisImage.Size;
            picAxis.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            picAxis.Visible = false;

            this.skinAxes[i] = picAxis;

            this.Controls.Add(picAxis);

            picAxis.Parent = this.picController;
        }

        if (backgroundImage.Width > 640 || backgroundImage.Height > 640)
        {
            /* Scale down to a maximum of 640px */
            float scale;
            if (backgroundImage.Width > backgroundImage.Height)
            {
                scale = 640 * ((float)1 / backgroundImage.Width);
            }
            else
            {
                scale = 640 * ((float)1 / backgroundImage.Height);
            }
            picController.Scale(SizeF(scale, scale));
        }
        picController.Visible = true;
    }
}
}
