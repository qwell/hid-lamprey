using System;
using System.Collections;
using System.Collections.Generic;
using System.Xml;

namespace Lamprey
{
    public sealed class InputMappings : IEnumerable<InputMapping>
    {
        public static InputMappings Instance { get; } = new InputMappings();
        static InputMappings() { }
        private InputMappings()
        {
            Load();
        }

        public IEnumerator GetEnumerator()
        {
            return List.GetEnumerator();
        }
        IEnumerator<InputMapping> IEnumerable<InputMapping>.GetEnumerator()
        {
            return List.GetEnumerator();
        }

        private List<InputMapping> List { get; } = new List<InputMapping>();

        public int Count => List.Count;

        public void Add(InputMapping inputMapping)
        {
            List.Add(inputMapping);
        }

        public bool Remove(InputMapping inputMapping)
        {
            return List.Remove(inputMapping);
        }

        public InputMapping FindByDeviceName(string device, string name)
        {
            foreach (InputMapping inputMapping in List)
            {
                if (device == inputMapping.Device && name == inputMapping.Name)
                {
                    return inputMapping;
                }
            }
            return null;
        }

        private void Load()
        {
            //TODO: Add builtin mappings?

            XmlReader xml = XmlReader.Create(@"settings\mappings.xml");
            xml.MoveToContent();
            while (xml.Read())
            {
                switch (xml.NodeType)
                {
                    case XmlNodeType.Element:
                        switch (xml.Name)
                        {
                            case "mapping":
                                if (xml.HasAttributes)
                                {
                                    string device = xml.GetAttribute("device");
                                    string name = xml.GetAttribute("name");

                                    Input.InputCode inputCode;
                                    if (!Enum.TryParse(xml.GetAttribute("code"), true, out inputCode))
                                    {
                                        inputCode = Input.InputCode.UnknownCode;
                                    }

                                    InputMapping inputMapping = this.FindByDeviceName(device, name);
                                    if (inputMapping == null)
                                    {
                                        this.Add(new InputMapping()
                                        {
                                            Device = device,
                                            Name = name,
                                            Code = inputCode,
                                        });
                                    }
                                    else
                                    {
                                        inputMapping.Code = inputCode;
                                    }
                                }

                                break;
                        }

                        break;
                }
            }
        }
    }
}
