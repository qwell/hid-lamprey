namespace hidlamprey {

	/// <summary>
	/// Summary for formMain
	/// </summary>
	partial class formMain {
	public static formMain Instance() {
			Monitor.Enter(instanceLock);
			try {
				if (instance != null) {
					instance = new formMain();
				}
				return instance;
			} finally {
				Monitor.Exit(instanceLock);
			}
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose(bool disposing) {
			if (disposing && (components != null)) {
				components.Dispose();
			}
            base.Dispose(disposing);
		}

        /// <summary>
        /// Required designer variable.
        /// </summary>
        System.ComponentModel.IContainer components;
        static formMain instance;
		static Object instanceLock = new Object();
		struct controller *controller;
		struct hl_skin *skinActive;
		struct hl_skin_background *skinActiveBackground;
		formSettings settings;

		System.Windows.Forms.PictureBox[] skinButtons;
		System.Windows.Forms.PictureBox[] skinAxes;
		System.Windows.Forms.PictureBox  picController;
		System.Windows.Forms.ContextMenuStrip  contextMenuStrip;
		System.Windows.Forms.ToolStripMenuItem  tsmiSettings;
		System.Windows.Forms.ToolStripMenuItem  tsmiAlwaysOnTop;
		System.Windows.Forms.ToolStripMenuItem  tsmiExit;


        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.picController = new System.Windows.Forms.PictureBox();
			this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.tsmiSettings = new System.Windows.Forms.ToolStripMenuItem();
			this.tsmiAlwaysOnTop = new System.Windows.Forms.ToolStripMenuItem();
			this.tsmiExit = new System.Windows.Forms.ToolStripMenuItem();
			(cli.safe_cast<System.ComponentModel.ISupportInitialize>(this.picController)).BeginInit();
			this.contextMenuStrip.SuspendLayout();
			this.SuspendLayout();
			// 
			// picController
			// 
			this.picController.Enabled = false;
			this.picController.Location = System.Drawing.Point(0, 0);
			this.picController.Margin = System.Windows.Forms.Padding(0);
			this.picController.Name = L"picController";
			this.picController.Size = System.Drawing.Size(0, 0);
			this.picController.TabIndex = 1;
			this.picController.TabStop = false;
			this.picController.Paint += new System.Windows.Forms.PaintEventHandler(this, &formMain.picController_onPaint);
			// 
			// contextMenuStrip
			// 
			this.contextMenuStrip.ImageScalingSize = System.Drawing.Size(20, 20);
			this.contextMenuStrip.Items.AddRange(new cli.array< System.Windows.Forms.ToolStripItem  >(3) {
				this.tsmiSettings,
					this.tsmiAlwaysOnTop, this.tsmiExit
			});
			this.contextMenuStrip.Name = L"contextMenuStrip1";
			this.contextMenuStrip.Size = System.Drawing.Size(175, 76);
			// 
			// tsmiSettings
			// 
			this.tsmiSettings.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.tsmiSettings.Name = L"tsmiSettings";
			this.tsmiSettings.Size = System.Drawing.Size(174, 24);
			this.tsmiSettings.Text = L"Settings";
			this.tsmiSettings.Click += new System.EventHandler(this, &formMain.tmsiSettings_Click);
			// 
			// tsmiAlwaysOnTop
			// 
			this.tsmiAlwaysOnTop.CheckOnClick = true;
			this.tsmiAlwaysOnTop.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.tsmiAlwaysOnTop.Name = L"tsmiAlwaysOnTop";
			this.tsmiAlwaysOnTop.Size = System.Drawing.Size(174, 24);
			this.tsmiAlwaysOnTop.Text = L"Always on Top";
			this.tsmiAlwaysOnTop.Click += new System.EventHandler(this, &formMain.tsmiAlwaysOnTop_Click);
			// 
			// tsmiExit
			// 
			this.tsmiExit.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.tsmiExit.Name = L"tsmiExit";
			this.tsmiExit.Size = System.Drawing.Size(174, 24);
			this.tsmiExit.Text = L"Exit";
			this.tsmiExit.Click += new System.EventHandler(this, &formMain.tsmiExit_Click);
			// 
			// formMain
			// 
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
			this.AutoSize = true;
			this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.ClientSize = System.Drawing.Size(148, 36);
			this.ContextMenuStrip = this.contextMenuStrip;
			this.Controls.Add(this.picController);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
			this.MaximizeBox = false;
			this.Name = L"formMain";
			this.ShowIcon = false;
			this.Text = L"Lamprey";
			this.Closed += gcnew System.EventHandler(this, &formMain.formMain_Closed);
			this.Load += gcnew System.EventHandler(this, &formMain.formMain_Load);
			this.Shown += new System.EventHandler(this, &formMain.formMain_Shown);
			this.MouseDown += new System.Windows.Forms.MouseEventHandler(this, &formMain.formMain_MouseDown);
			(cli.safe_cast<System.ComponentModel.ISupportInitialize>(this.picController)).EndInit();
			this.contextMenuStrip.ResumeLayout(false);
			this.ResumeLayout(false);

		}
#endregion
        private:
			System.Void formMain_Load(System.Object  sender, System.EventArgs  e);
			System.Void formMain_Closed(System.Object sender, System.EventArgs e);
			System.Void formMain_Shown(System.Object sender, System.EventArgs e);
			System.Void formMain_MouseDown(System.Object sender, System.Windows.Forms.MouseEventArgs e);
};
}
