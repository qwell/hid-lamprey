using System.Collections.Generic;

namespace Lamprey
{
    partial class FormDisplay
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.picController = new System.Windows.Forms.PictureBox();
            this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.tsmiSettings = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiAlwaysOnTop = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiExit = new System.Windows.Forms.ToolStripMenuItem();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.picController)).BeginInit();
            this.contextMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // picController
            // 
            this.picController.Enabled = false;
            this.picController.Location = new System.Drawing.Point(0, 0);
            this.picController.Margin = new System.Windows.Forms.Padding(0);
            this.picController.Name = "picController";
            this.picController.Size = new System.Drawing.Size(0, 0);
            this.picController.TabIndex = 1;
            this.picController.TabStop = false;
            this.picController.Paint += new System.Windows.Forms.PaintEventHandler(this.picController_onPaint);
            // 
            // contextMenuStrip
            // 
            this.contextMenuStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.contextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmiSettings,
            this.tsmiAlwaysOnTop,
            this.tsmiExit});
            this.contextMenuStrip.Name = "contextMenuStrip1";
            this.contextMenuStrip.Size = new System.Drawing.Size(175, 76);
            // 
            // tsmiSettings
            // 
            this.tsmiSettings.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tsmiSettings.Name = "tsmiSettings";
            this.tsmiSettings.Size = new System.Drawing.Size(174, 24);
            this.tsmiSettings.Text = "Settings";
            this.tsmiSettings.Click += new System.EventHandler(this.tmsiSettings_Click);
            // 
            // tsmiAlwaysOnTop
            // 
            this.tsmiAlwaysOnTop.CheckOnClick = true;
            this.tsmiAlwaysOnTop.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tsmiAlwaysOnTop.Name = "tsmiAlwaysOnTop";
            this.tsmiAlwaysOnTop.Size = new System.Drawing.Size(174, 24);
            this.tsmiAlwaysOnTop.Text = "Always on Top";
            this.tsmiAlwaysOnTop.Click += new System.EventHandler(this.tsmiAlwaysOnTop_Click);
            // 
            // tsmiExit
            // 
            this.tsmiExit.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tsmiExit.Name = "tsmiExit";
            this.tsmiExit.Size = new System.Drawing.Size(174, 24);
            this.tsmiExit.Text = "Exit";
            this.tsmiExit.Click += new System.EventHandler(this.tsmiExit_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 10;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // FormDisplay
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.ContextMenuStrip = this.contextMenuStrip;
            this.Controls.Add(this.picController);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.MaximizeBox = false;
            this.Name = "FormDisplay";
            this.ShowIcon = false;
            this.Text = "Lamprey";
            this.Closed += new System.EventHandler(this.FormDisplay_Closed);
            this.Load += new System.EventHandler(this.FormDisplay_Load);
            this.Shown += new System.EventHandler(this.FormDisplay_Shown);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.FormDisplay_MouseDown);
            ((System.ComponentModel.ISupportInitialize)(this.picController)).EndInit();
            this.contextMenuStrip.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private List<SkinButtonPictureBox> skinButtons;
        private List<SkinAxisPictureBox> skinAxes;
        private System.Windows.Forms.PictureBox picController;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem tsmiSettings;
        private System.Windows.Forms.ToolStripMenuItem tsmiAlwaysOnTop;
        private System.Windows.Forms.ToolStripMenuItem tsmiExit;
        private System.Windows.Forms.Timer timer1;
    }
}