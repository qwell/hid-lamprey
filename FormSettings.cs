using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lamprey
{
    public partial class FormSettings : Form
    {
        public event EventHandler SkinChanged;

        public FormSettings()
        {
            InitializeComponent();
        }

        private void update_mapping(string device, string rawname, Object tag)
        {
            Input input = (Input)tag;

            foreach (InputMapping inputMapping in InputMappings.Instance)
            {
                if (device == inputMapping.Device && rawname == inputMapping.Name)
                {
                    if (input == null)
                    {
                        InputMappings.Instance.Remove(inputMapping);
                    }
                    else
                    {
                        inputMapping.Value = 0;
                        inputMapping.Builtin = false;
                        inputMapping.Code = input.Code;
                    }

                    Settings.Instance.Save();
                    return;
                }
            }

            InputMappings.Instance.Add(new InputMapping
            {
                Value = 0,
                Builtin = false,
                Device = device,
                Name = rawname,
                Code = input != null ? input.Code : Input.InputCode.UnknownCode,
            });

            Settings.Instance.Save();
        }

        void FormSettings_ControllerChanged(object sender, EventArgs e)
        {
            if (this.tvMappings.InvokeRequired)
            {
                this.tvMappings.Invoke(new Action<object, EventArgs>(this.FormSettings_ControllerChanged), sender, e);
            }
            else
            {
                tvMappings.BeginUpdate();

                foreach (Controller controller in Controllers.Instance)
                {
                    TreeNode nodeDevice = null;

                    foreach (TreeNode node in tvMappings.Nodes)
                    {
                        if (controller.Name == node.Text)
                        {
                            nodeDevice = node;
                            break;
                        }
                    }

                    if (nodeDevice == null)
                    {
                        nodeDevice = new TreeNode(controller.Name)
                        {
                            Name = controller.Name,
                        };
                        nodeDevice.Expand();
                        tvMappings.Nodes.Add(nodeDevice);
                    }

                    foreach (Controller.Button button in controller.Buttons)
                    {
                        TreeNode nodeButton = null;

                        foreach (TreeNode node in nodeDevice.Nodes)
                        {
                            if (node.Name == button.Code.ToString())
                            {
                                nodeButton = node;
                                break;
                            }
                        }

                        if (nodeButton == null)
                        {
                            nodeButton = new TreeNode(button.Code.ToString())
                            {
                                Name = button.Code.ToString(),
                                ForeColor = Color.Red
                            };
                            nodeDevice.Nodes.Add(nodeButton);
                            nodeDevice.Expand();
                        }

                        if (button.Value != 0)
                        {
                            nodeButton.ForeColor = Color.Gold;
                        }
                        else if (nodeButton.Name == nodeButton.Text)
                        {
                            nodeButton.ForeColor = Color.Red;
                        }
                        else
                        {
                            nodeButton.ForeColor = Color.Green;
                        }
                    }

                    tvMappings.EndUpdate();
                }
            }
        }

        private void FormSettings_Load(object sender, EventArgs e)
        {
            toolTip1.SetToolTip(this.tvMappings, "Double-click to remove current mapping.  Press any button to add a new mapping target.");
            toolTip1.SetToolTip(this.tvMapButtons, "Drag a button to a mapping target (left) to assign a button mapping.");

            tvSkins.BeginUpdate();
            tvSkins.Nodes.Clear();

            Skins skins = Skins.Instance;
            foreach (Skin skin in skins)
            {
                TreeNode node = new TreeNode(skin.Name);
                foreach (Skin.Background background in skin.Backgrounds)
                {
                    node.Nodes.Add(background.Name);
                }
                tvSkins.Nodes.Add(node);
            }
            tvSkins.EndUpdate();

            tvMappings.BeginUpdate();
            tvMappings.Nodes.Clear();
            Inputs inputs = Inputs.Instance;
            InputMappings inputMappings = InputMappings.Instance;
            foreach (InputMapping inputMapping in inputMappings)
            {
                if (!inputMapping.Builtin)
                {
                    string strDevice = inputMapping.Device;
                    TreeNode nodeDevice = null;
                    for (int j = 0; j < this.tvMappings.Nodes.Count; j++)
                    {
                        if (strDevice == this.tvMappings.Nodes[j].Text)
                        {
                            nodeDevice = tvMappings.Nodes[j];
                            break;
                        }
                    }
                    if (nodeDevice == null)
                    {
                        nodeDevice = new TreeNode(strDevice)
                        {
                            Name = strDevice
                        };
                    }

                    foreach (Input input in inputs)
                    {
                        if (input.Code == inputMapping.Code)
                        {
                            TreeNode nodeButton = new TreeNode(inputMapping.Name + "  |  " + input.Description ?? input.Code.ToString())
                            {
                                Name = inputMapping.Name,
                                Tag = input,
                                ForeColor = Color.Green
                            };

                            nodeDevice.Nodes.Add(nodeButton);
                        }
                    }

                    if (nodeDevice.TreeView == null)
                    {
                        tvMappings.Nodes.Add(nodeDevice);
                    }
                }
            }
            tvMappings.ExpandAll();
            tvMappings.EndUpdate();

            tvMapButtons.BeginUpdate();
            tvMapButtons.Nodes.Clear();

            foreach (Input input in inputs)
            {
                TreeNode nodeCategory = null;
                if (input.Type != Input.InputType.UnknownType)
                {
                    if (input.Code >= 0)
                    {
                        string codeType;

                        switch (input.Type)
                        {
                            case Input.InputType.GamepadButton:
                                codeType = "Gamepad Buttons";
                                break;
                            case Input.InputType.MouseButton:
                                codeType = "Mouse Buttons";
                                break;
                            case Input.InputType.KeyboardKey:
                                codeType = "Keyboard Keys";
                                break;
                            case Input.InputType.NumpadKey:
                                codeType = "Numpad Keys";
                                break;
                            case Input.InputType.MiscKey:
                                codeType = "Misc Keys";
                                break;
                            case Input.InputType.AbsoluteAxis:
                                codeType = "Absolute Axis";
                                break;
                            case Input.InputType.RelativeAxis:
                                codeType = "Relative Axis";
                                break;
                            default:
                                codeType = "Other";
                                break;
                        }

                        foreach (TreeNode node in this.tvMapButtons.Nodes)
                        {
                            if (codeType == node.Text)
                            {
                                nodeCategory = node;
                                break;
                            }
                        }

                        if (nodeCategory == null)
                        {
                            nodeCategory = new TreeNode(codeType)
                            {
                                Name = codeType
                            };
                        }

                        TreeNode nodeCode = new TreeNode(input.Description ?? input.Code.ToString())
                        {
                            Name = input.Description ?? input.Code.ToString(),
                            Tag = input
                        };

                        nodeCategory.Nodes.Add(nodeCode);
                        if (nodeCategory.TreeView == null)
                        {
                            tvMapButtons.Nodes.Add(nodeCategory);
                        }
                    }
                }
            }
            tvMapButtons.EndUpdate();

            tvShortcuts.BeginUpdate();
            tvShortcuts.Nodes.Clear();
            foreach (Shortcut shortcut in Shortcuts.Instance)
            {
                TreeNode nodeShortcut = new TreeNode(shortcut.Name);

                foreach (Shortcut.Button button in shortcut.Buttons)
                {
                    foreach (Input input in inputs)
                    {
                        if (input.Code == button.Code)
                        {
                            TreeNode nodeButton = new TreeNode(input.Description ?? input.Code.ToString());
                            nodeShortcut.Nodes.Add(nodeButton);
                        }
                    }
                }

                tvShortcuts.Nodes.Add(nodeShortcut);
            }
            tvShortcuts.ExpandAll();
            tvShortcuts.EndUpdate();

            Controllers.Instance.ControllerChanged += FormSettings_ControllerChanged;
        }

        void FormSettings_Closed(object sender, EventArgs e)
        {
            Controllers.Instance.ControllerChanged -= FormSettings_ControllerChanged;
        }

        private void tvSkins_AfterSelect(object sender, TreeViewEventArgs e)
        {
            Settings settings = Settings.Instance;
            if (e.Node.Level == 1)
            {
                foreach (Skin Skin in Skins.Instance)
                {
                    if (Skin.Name == e.Node.Parent.Text)
                    {
                        settings.Skin = Skin;
                        foreach (Skin.Background Background in Skin.Backgrounds)
                        {
                            if (Background.Name == e.Node.Text)
                            {
                                settings.SkinBackground = Background;
                                break;
                            }
                        }
                        break;
                    }
                }

                if (this.SkinChanged != null)
                {
                    SkinChanged(this, null);
                }
            }
        }

        private void tvMapButtons_ItemDrag(object sender, System.Windows.Forms.ItemDragEventArgs e)
        {
            TreeNode node = (TreeNode)e.Item;
            if (node != null && node.Level == 1)
            {
                DoDragDrop(e.Item, DragDropEffects.Link);
            }
        }

        private void tvMappings_DragEnter(object sender, System.Windows.Forms.DragEventArgs e)
        {
            e.Effect = DragDropEffects.Link;
        }

        private void tvMappings_DragDrop(object sender, System.Windows.Forms.DragEventArgs e)
        {
            if (e.Data.GetDataPresent("System.Windows.Forms.TreeNode", false))
            {
                Point pt = ((TreeView)sender).PointToClient(new Point(e.X, e.Y));
                TreeNode nodeDest = ((TreeView)sender).GetNodeAt(pt);
                if (nodeDest != null && nodeDest.Level == 1)
                {
                    TreeNode nodeLink = (TreeNode)e.Data.GetData("System.Windows.Forms.TreeNode");
                    nodeDest.Tag = nodeLink.Tag;
                    nodeDest.Text = nodeDest.Name + "  |  " + nodeLink.Text;
                    nodeDest.ForeColor = Color.Green;

                    this.update_mapping(nodeDest.Parent.Name, nodeDest.Name, nodeDest.Tag);
                }
            }
        }

        private void tvMappings_NodeMouseDoubleClick(object sender, System.Windows.Forms.TreeNodeMouseClickEventArgs e)
        {
            if (e.Node.Level == 1)
            {
                this.update_mapping(e.Node.Parent.Name, e.Node.Name, null);

                e.Node.Tag = null;
                e.Node.Text = e.Node.Name;
                e.Node.Remove();
            }
        }

        private void eat_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = true;
            return;
        }
    }
}