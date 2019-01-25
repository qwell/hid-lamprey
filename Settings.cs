using System;
using System.Collections.Generic;
using System.Text;

namespace lamprey
{
    public sealed class Settings
    {
        public static Settings Instance { get; } = new Settings();
        static Settings() { }
        private Settings() { }

        public void Save() { }
        public String SkinName { get; set; }
        public String SkinBackground { get; set; }
    }
}
