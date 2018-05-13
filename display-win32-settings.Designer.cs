namespace hidlamprey {

	/// <summary>
	/// Summary for formSettings
	/// </summary>
	partial class formSettings
	{
	    protected override void Dispose(bool disposing)
	    {
		    if (disposing && (components != null))
		    {
			    components.Dispose();
		    }
            base.Dispose(disposing);
	    }

        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        private formMain formMain;
        private System.Windows.Forms.TreeView tvSkins;
        private System.Windows.Forms.TreeView tvMapButtons;
        private System.Windows.Forms.TreeView tvMappings;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabSkins;
        private System.Windows.Forms.TabPage tabMappings;
        private System.Windows.Forms.ToolTip toolTip1;
        
        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.tvSkins = new System.Windows.Forms.TreeView();
			this.tvMappings = new System.Windows.Forms.TreeView();
			this.tvMapButtons = new System.Windows.Forms.TreeView();
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.tabSkins = new System.Windows.Forms.TabPage();
			this.tabMappings = new System.Windows.Forms.TabPage();
			this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
			this.tabControl1.SuspendLayout();
			this.tabSkins.SuspendLayout();
			this.tabMappings.SuspendLayout();
			this.SuspendLayout();
			// 
			// tvSkins
			// 
			this.tvSkins.Location = new System.Drawing.Point(6, 8);
			this.tvSkins.Name = "tvSkins";
			this.tvSkins.Size = new System.Drawing.Size(265, 457);
			this.tvSkins.TabIndex = 1;
			this.tvSkins.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.tvSkins_AfterSelect);
			// 
			// tvMappings
			// 
			this.tvMappings.AllowDrop = true;
			this.tvMappings.Location = new System.Drawing.Point(6, 6);
			this.tvMappings.Name = "tvMappings";
			this.tvMappings.Size = new System.Drawing.Size(360, 464);
			this.tvMappings.TabIndex = 6;
			this.tvMappings.NodeMouseDoubleClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.tvMappings_NodeMouseDoubleClick);
			this.tvMappings.DragDrop += new System.Windows.Forms.DragEventHandler(this.tvMappings_DragDrop);
			this.tvMappings.DragEnter += new System.Windows.Forms.DragEventHandler(this.tvMappings_DragEnter);
			// 
			// tvMapButtons
			// 
			this.tvMapButtons.Location = new System.Drawing.Point(372, 6);
			this.tvMapButtons.Name = "tvMapButtons";
			this.tvMapButtons.Size = new System.Drawing.Size(360, 464);
			this.tvMapButtons.TabIndex = 5;
			this.tvMapButtons.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.tvMapButtons_ItemDrag);
			// 
			// tabControl1
			// 
			this.tabControl1.Controls.Add(this.tabSkins);
			this.tabControl1.Controls.Add(this.tabMappings);
			this.tabControl1.Location = new System.Drawing.Point(12, 12);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(747, 505);
			this.tabControl1.TabIndex = 6;
			// 
			// tabSkins
			// 
			this.tabSkins.Controls.Add(this.tvSkins);
			this.tabSkins.Location = new System.Drawing.Point(4, 25);
			this.tabSkins.Name = "tabSkins";
			this.tabSkins.Padding = new System.Windows.Forms.Padding(3);
			this.tabSkins.Size = new System.Drawing.Size(739, 476);
			this.tabSkins.TabIndex = 0;
			this.tabSkins.Text = "Skins";
			this.tabSkins.UseVisualStyleBackColor = true;
			// 
			// tabMappings
			// 
			this.tabMappings.Controls.Add(this.tvMappings);
			this.tabMappings.Controls.Add(this.tvMapButtons);
			this.tabMappings.Location = new System.Drawing.Point(4, 25);
			this.tabMappings.Name = "tabMappings";
			this.tabMappings.Padding = new System.Windows.Forms.Padding(3);
			this.tabMappings.Size = new System.Drawing.Size(739, 476);
			this.tabMappings.TabIndex = 1;
			this.tabMappings.Text = "Input Mappings";
			this.tabMappings.UseVisualStyleBackColor = true;
			// 
			// toolTip1
			// 
			this.toolTip1.AutoPopDelay = 3000;
			this.toolTip1.InitialDelay = 500;
			this.toolTip1.ReshowDelay = 100;
			// 
			// formSettings
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8, 16);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(763, 529);
			this.Controls.Add(this.tabControl1);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "formSettings";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.Text = "Settings";
			this.Load += new System.EventHandler(this.formSettings_Load);
			this.tabControl1.ResumeLayout(false);
			this.tabSkins.ResumeLayout(false);
			this.tabMappings.ResumeLayout(false);
			this.ResumeLayout(false);

		}
#endregion
};
}
