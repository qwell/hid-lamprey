using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace Lamprey
{
    public sealed class Settings
    {
        public static Settings Instance { get; } = new Settings();
        static Settings() { }
        private Settings()
        {
            Load();
        }

        private void Load()
        {
            XmlReader xml = XmlReader.Create(@"settings\settings.xml");
            xml.MoveToContent();
            while (xml.Read())
            {
                switch (xml.NodeType)
                {
                    case XmlNodeType.Element:
                        switch (xml.Name)
                        {
                            case "skin":
                                if (xml.HasAttributes)
                                {
                                    Skin = Skins.Instance.FindByName(xml.GetAttribute("name"));
                                    if (Skin != null)
                                    {
                                        SkinBackground = Skin.Backgrounds.FindByName(xml.GetAttribute("background"));
                                    }
                                    else
                                    {
                                        SkinBackground = null;
                                    }
                                }
                                break;
                            case "device":
                                break;
                            case "option":
                                break;
                        }
                        break;
                }
            }
        }
        public void Save() { }
        public Skin Skin { get; set; }
        public Skin.Background SkinBackground { get; set; }
    }
}
