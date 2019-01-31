using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Xml;

namespace Lamprey
{
    public sealed class Skins : IEnumerable<Skin>
    {
        public static Skins Instance { get; } = new Skins();
        static Skins() { }
        private Skins()
        {
            Load();
        }

        public IEnumerator GetEnumerator()
        {
            return List.GetEnumerator();
        }
        IEnumerator<Skin> IEnumerable<Skin>.GetEnumerator()
        {
            return List.GetEnumerator();
        }

        private List<Skin> List { get; } = new List<Skin>();

        public int Count => List.Count;

        private void Load()
        {
            EnumerationOptions x = new EnumerationOptions();
            foreach (string file in Directory.EnumerateFiles("skins", "skin.xml", SearchOption.AllDirectories))
            {
                Skin skin = null;

                XmlReader xml = XmlReader.Create(file);
                xml.MoveToContent();
                if (xml.HasAttributes)
                {
                    skin = new Skin {
                        Name = xml.GetAttribute("name"),
                        Path = file.Substring(0, file.Length - "skin.xml".Length)
                    };
                    // TODO: Add backwards compat for NintendoSpy type= attribute.
                }

                if (skin == null || skin.Name.Length == 0)
                {
                    continue;
                }

                this.Add(skin);

                while (xml.Read())
                {
                    switch (xml.NodeType)
                    {
                        case XmlNodeType.Element:
                            switch (xml.Name)
                            {
                                case "background":
                                    if (xml.HasAttributes)
                                    {
                                        Skin.Background background = new Skin.Background {
                                            Name = xml.GetAttribute("name"),
                                            Filename = xml.GetAttribute("image")
                                        };

                                        if (background.Name.Length == 0 || background.Filename.Length == 0)
                                        {
                                            continue;
                                        }
                                        skin.Backgrounds.Add(background);
                                    }
                                    break;
                                    /*
                                case "button":
                                    if (xml.HasAttributes)
                                    {
                                        Skin.Button button = new Skin.Button {
                                            Filename = xml.GetAttribute("image"),
                                            Category = (InputCode.InputCategory)int.Parse(xml.GetAttribute("type")),
                                            Code = int.Parse(xml.GetAttribute("code")),
                                            PosX = int.Parse(xml.GetAttribute("x") ?? xml.GetAttribute("X")),
                                            PosY = int.Parse(xml.GetAttribute("y") ?? xml.GetAttribute("Y")),
                                        };

                                        skin.Buttons.Add(button);
                                    }
                                    break;
                                case "axis":
                                    if (xml.HasAttributes)
                                    {
                                        Skin.Axis axis = new Skin.Axis {
                                            Filename = xml.GetAttribute("image"),
                                            PosX = int.Parse(xml.GetAttribute("x") ?? xml.GetAttribute("X")),
                                            PosY = int.Parse(xml.GetAttribute("y") ?? xml.GetAttribute("Y")),
                                            X = xml.GetAttribute("code_x").Length == 0 ? null : new Skin.Axis.AxisX {
                                                Category = (InputCode.InputCategory)int.Parse(xml.GetAttribute("type_x")),
                                                Code = int.Parse(xml.GetAttribute("code_x")),
                                            },
                                            Y = xml.GetAttribute("code_y").Length > 0 ? null : new Skin.Axis.AxisY {
                                                Category = (InputCode.InputCategory)int.Parse(xml.GetAttribute("type_y")),
                                                Code = int.Parse(xml.GetAttribute("code_y")),
                                            },
                                        };

                                        skin.Axes.Add(axis);
                                    }
                                    break;
                                    */
                            }
                            break;
                    }
                }
            }
        }

        public void Add(Skin skin)
        {
            List.Add(skin);
        }

        public void Remove(Skin skin)
        {
            List.Remove(skin);
        }

        public Skin FindByName(string name)
        {
            foreach (Skin skin in List)
            {
                if (name == skin.Name)
                {
                    return skin;
                }
            }
            return null;
        }
    }
}
