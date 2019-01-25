using System;
using System.Collections.Generic;
using System.Text;

namespace Lamprey
{
    public sealed class Settings
    {
        public static Settings Instance { get; } = new Settings();
        static Settings() { }
        private Settings() { }

        public void Save() { }
        public Skin Skin { get; set; }
        public Skin.Background SkinBackground { get; set; }
    }
}
