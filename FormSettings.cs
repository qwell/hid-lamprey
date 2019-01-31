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
        public FormSettings()
        {
            InitializeComponent();
        }

        private void update_mapping(string device, string rawname, Object tag)
        {
            InputCode inputCode = (InputCode)tag;

            foreach (InputMapping inputMapping in InputMappings.Instance)
            {
                if (device == inputMapping.Device && rawname == inputMapping.Name)
                {
                    if (inputCode == null)
                    {
                        InputMappings.Instance.Remove(inputMapping);
                    }
                    else
                    {
                        inputMapping.Value = 0;
                        inputMapping.Builtin = false;
                        inputMapping.Code = inputCode.Code;
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
                Code = inputCode != null ? inputCode.Code : InputCode.InputCodeZ.UnknownCode,
            });

            Settings.Instance.Save();
        }

        void output_raw(string device, string rawname, int value)
        {
            if (this.tvMappings.InvokeRequired)
            {
                this.tvMappings.Invoke(new Action<string, string, int>(this.output_raw), device, rawname, value);
            }
            else
            {
                TreeNode nodeDevice = null;
                TreeNode nodeButton;

                foreach (TreeNode node in tvMappings.Nodes)
                {
                    if (device == node.Text)
                    {
                        nodeDevice = node;

                        foreach (TreeNode node2 in nodeDevice.Nodes)
                        {
                            if (node2.Name == rawname)
                            {
                                if (value != 0)
                                {
                                    node2.ForeColor = Color.Gold;
                                }
                                else if (node2.Name == node2.Text)
                                {
                                    node2.ForeColor = Color.Red;
                                }
                                else
                                {
                                    node2.ForeColor = Color.Green;
                                }
                                return;
                            }
                        }
                        break;
                    }
                }
                if (nodeDevice == null)
                {
                    nodeDevice = new TreeNode(device)
                    {
                        Name = device
                    };
                }

                tvMappings.BeginUpdate();

                nodeButton = new TreeNode(rawname)
                {
                    Name = rawname,
                    ForeColor = Color.Red
                };

                nodeDevice.Nodes.Add(nodeButton);
                nodeDevice.Expand();

                if (nodeDevice.TreeView == null)
                {
                    tvMappings.Nodes.Add(nodeDevice);
                }

                tvMappings.EndUpdate();
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
            InputCodes inputCodes = InputCodes.Instance;
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

                    foreach (InputCode inputCode in inputCodes)
                    {
                        if (inputCode.Code == inputMapping.Code)
                        {
                            TreeNode nodeButton = new TreeNode(inputMapping.Name + "  |  " + inputCode.Description ?? inputCode.Code.ToString())
                            {
                                Name = inputMapping.Name,
                                Tag = inputCode,
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

            foreach (InputCode inputCode in inputCodes)
            {
                TreeNode nodeCategory = null;
                if (inputCode.Type != InputCode.InputType.UnknownType)
                {
                    if (inputCode.Code >= 0)
                    {
                        string codeType;

                        switch (inputCode.Type)
                        {
                            case InputCode.InputType.GamepadButton:
                                codeType = "Gamepad Buttons";
                                break;
                            case InputCode.InputType.MouseButton:
                                codeType = "Mouse Buttons";
                                break;
                            case InputCode.InputType.KeyboardKey:
                                codeType = "Keyboard Keys";
                                break;
                            case InputCode.InputType.NumpadKey:
                                codeType = "Keyboard Numpad Keys";
                                break;
                            case InputCode.InputType.MiscKey:
                                codeType = "Keyboard Misc Keys";
                                break;
                            case InputCode.InputType.AbsoluteAxis:
                                codeType = "Absolute Axis";
                                break;
                            case InputCode.InputType.RelativeAxis:
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

                        TreeNode nodeCode = new TreeNode(inputCode.Description ?? inputCode.Code.ToString())
                        {
                            Name = inputCode.Description ?? inputCode.Code.ToString(),
                            Tag = inputCode
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
                    foreach (InputCode inputCode in inputCodes)
                    {
                        if (inputCode.Code == button.Code)
                        {
                            TreeNode nodeButton = new TreeNode(inputCode.Description ?? inputCode.Code.ToString());
                            nodeShortcut.Nodes.Add(nodeButton);
                        }
                    }
                }

                tvShortcuts.Nodes.Add(nodeShortcut);
            }
            tvShortcuts.ExpandAll();
            tvShortcuts.EndUpdate();
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

                //formMain.loadSkinImages();
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