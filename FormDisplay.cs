using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Lamprey
{
    public partial class FormDisplay : Form
    {
        const int WM_NCLBUTTONDOWN = 0xA1;
        const int HT_CAPTION = 0x2;
        [DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();
        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int wMsg, int wParam, int lParam);

        public FormDisplay()
        {
            InitializeComponent();
        }

        bool needRefresh = true;

        private class SkinButtonPictureBox : PictureBox
        {
            public Skin.Button SkinButton { get; set; }
        }

        private class SkinAxisPictureBox : PictureBox
        {
            public Skin.Axis SkinAxis { get; set; }
        }

        void picController_onPaint(object sender, PaintEventArgs e)
        {
            foreach (Controller Controller in Controllers.Instance)
            {
                foreach (Controller.Button ControllerButton in Controller.Buttons)
                {
                    foreach (SkinButtonPictureBox SkinButtonPictureBox in this.skinButtons)
                    {
                        Skin.Button SkinButton = SkinButtonPictureBox.SkinButton;
                        if (ControllerButton.Code == SkinButtonPictureBox.SkinButton.Code)
                        {
                            if (ControllerButton.Value != 0)
                            {
                                e.Graphics.DrawImage(SkinButtonPictureBox.Image, new RectangleF(SkinButtonPictureBox.Location, SkinButtonPictureBox.Size));
                            }
                        }
                    }

                    foreach (SkinAxisPictureBox SkinAxisPictureBox in this.skinAxes)
                    {
                        Skin.Axis SkinAxis = SkinAxisPictureBox.SkinAxis;
                        if ((SkinAxis.X != null && ControllerButton.Code == SkinAxis.X.Code) || (SkinAxis.Y != null && ControllerButton.Code == SkinAxis.Y.Code))
                        {
                            int offset_x = SkinAxisPictureBox.Location.X - SkinAxis.PosX;
                            int offset_y = SkinAxisPictureBox.Location.Y - SkinAxis.PosY;
                            bool visible = false;

                            if (ControllerButton.Code == SkinAxis.X.Code && (SkinAxis.X.Trigger == 0 || (SkinAxis.X.Trigger > 0 && ControllerButton.Value > SkinAxis.X.Trigger) || (SkinAxis.X.Trigger < 0 && ControllerButton.Value < SkinAxis.X.Trigger)))
                            {
                                if (ControllerButton.Value != 0)
                                {
                                    if (SkinAxis.X.Offset != 0)
                                    {
                                        offset_x = (ControllerButton.Type == Input.InputType.RelativeAxis ? ControllerButton.Decay : ControllerButton.Value) / (256 / SkinAxis.X.Offset);
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

                            if (ControllerButton.Code == SkinAxis.Y.Code && (SkinAxis.Y.Trigger == 0 || (SkinAxis.Y.Trigger > 0 && ControllerButton.Value > SkinAxis.Y.Trigger) || (SkinAxis.Y.Trigger < 0 && ControllerButton.Value < SkinAxis.Y.Trigger)))
                            {
                                if (ControllerButton.Value != 0)
                                {
                                    if (SkinAxis.Y.Offset != 0)
                                    {
                                        offset_y = (ControllerButton.Type == Input.InputType.RelativeAxis ? ControllerButton.Decay : ControllerButton.Value) / (256 / SkinAxis.Y.Offset);
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

                            SkinAxisPictureBox.Location = new Point(SkinAxis.PosX + offset_x, SkinAxis.PosY + offset_y);
                            if (visible)
                            {
                                e.Graphics.DrawImage(SkinAxisPictureBox.Image, new RectangleF(SkinAxisPictureBox.Location, SkinAxisPictureBox.Size));
                            }
                        }
                    }
                }
            }
        }

        void tsmiAlwaysOnTop_Click(object sender, EventArgs e)
        {
            this.TopMost = tsmiAlwaysOnTop.Checked;
        }

        void tsmiExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        void tmsiSettings_Click(object sender, EventArgs e)
        {
            FormSettings settings = new FormSettings();
            settings.SkinChanged += new EventHandler(FormDisplay_SkinChanged);
            settings.ShowDialog(this);
            settings.Dispose();
        }

        void FormDisplay_Load(object sender, EventArgs e)
        {
            this.DoubleBuffered = true;
        }

        void FormDisplay_Closed(object sender, EventArgs e)
        {
        }

        void FormDisplay_Shown(object sender, EventArgs e)
        {
            this.loadSkinImages();
        }

        void FormDisplay_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            }
        }

        void timer1_Tick(object sender, EventArgs e)
        {
            foreach (Controller Controller in Controllers.Instance)
            {
                foreach (Controller.Button Button in Controller.Buttons)
                {
                    if (Button.Type == Input.InputType.RelativeAxis && Button.Value != 0)
                    {
                        int decay_amount;
                        if (Math.Abs(Button.Value) < 10)
                        {
                            decay_amount = Button.Value;
                        }
                        else
                        {
                            decay_amount = (int)(Button.Value * .1);
                        }
                        Button.Decay -= decay_amount;
                        if (Math.Abs(Button.Decay) < Math.Abs(decay_amount))
                        {
                            Button.Decay = 0;
                            Button.Value = 0;
                        }
                        this.needRefresh = true;
                    }
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

        void output_controller()
        {
            this.needRefresh = true;
        }

        void FormDisplay_SkinChanged(object sender, EventArgs e)
        {
            this.loadSkinImages();
        }

        void loadSkinImages()
        {
            Settings settings = Settings.Instance;
            Bitmap backgroundImage = new Bitmap(settings.Skin.Path + settings.SkinBackground.Filename);
            backgroundImage.MakeTransparent(Color.White);

            picController.Image = backgroundImage;
            picController.Size = backgroundImage.Size;
            picController.SizeMode = PictureBoxSizeMode.Zoom;

            this.skinButtons = new List<SkinButtonPictureBox>();

            foreach (Skin.Button Button in settings.Skin.Buttons)
            {
                SkinButtonPictureBox picButton = new SkinButtonPictureBox();

                Bitmap buttonImage = new Bitmap(settings.Skin.Path + Button.Filename);
                buttonImage.MakeTransparent(Color.White);

                picButton.Anchor = AnchorStyles.Left | AnchorStyles.Top;
                picButton.BackColor = Color.Transparent;
                picButton.Enabled = false;
                picButton.Image = buttonImage;
                picButton.Location = new Point(Button.PosX, Button.PosY);
                picButton.Name = "picButton" + Button.GetHashCode();
                picButton.Padding = new Padding(0, 0, 0, 0);
                picButton.Size = buttonImage.Size;
                picButton.SizeMode = PictureBoxSizeMode.Zoom;
                picButton.Visible = false;

                picButton.SkinButton = Button;

                this.skinButtons.Add(picButton);
                this.Controls.Add(picButton);

                picButton.Parent = this.picController;
            }

            this.skinAxes = new List<SkinAxisPictureBox>();

            foreach (Skin.Axis Axis in settings.Skin.Axes)
            {
                SkinAxisPictureBox picAxis = new SkinAxisPictureBox();

                Bitmap axisImage = new Bitmap(settings.Skin.Path + Axis.Filename);
                axisImage.MakeTransparent(Color.White);

                picAxis.Anchor = AnchorStyles.Left | AnchorStyles.Top;
                picAxis.BackColor = Color.Transparent;
                picAxis.Enabled = false;
                picAxis.Image = axisImage;
                picAxis.Location = new Point(Axis.PosX, Axis.PosY);
                picAxis.Name = "picAxis" + Axis.GetHashCode();
                picAxis.Padding = new Padding(0, 0, 0, 0);
                picAxis.Size = axisImage.Size;
                picAxis.SizeMode = PictureBoxSizeMode.Zoom;
                picAxis.Visible = false;

                picAxis.SkinAxis = Axis;

                this.skinAxes.Add(picAxis);
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
                picController.Scale(new SizeF(scale, scale));
            }
            picController.Visible = true;
        }
    }
}
