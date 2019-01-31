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
                                    } else
                                    {
                                        SkinBackground = null;
                                    }
                                }
                                break;
                            case "option":
                                if (xml.HasAttributes && xml.HasValue)
                                {
                                    switch (xml.GetAttribute("name"))
                                    {
                                        case "deadzone_axis":
                                            DeadzoneAxis = xml.ReadElementContentAsFloat();
                                            break;
                                        case "deadzone_hat":
                                            DeadzoneHat = xml.ReadElementContentAsFloat();
                                            break;
                                    }
                                }
                                break;
                            case "device":
                                if (xml.HasAttributes && xml.HasValue)
                                {
                                    if (xml.GetAttribute("name").Length > 0)
                                    {
                                        Device device = new Device {
                                            Name = xml.GetAttribute("name"),
                                            Location = xml.ReadElementContentAsString()
                                        };
                                        Devices.Add(device);
                                    }
                                }

                                break;
                        }
                        break;
                }
            }
        }
        public void Save() { }
        public Skin Skin { get; set; }
        public Skin.Background SkinBackground { get; set; }
        public float DeadzoneAxis { get; set; } = 0.2F;
        public float DeadzoneHat { get; set; } = 0F;

        // TODO: Properly implement this.
        public class Device
        {
            public string Name { get; set; }
            public string Location { get; set; }
        }
        public List<Device> Devices { get; set; }
    }
}
