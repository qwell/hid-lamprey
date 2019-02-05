using System;
using System.Collections.Generic;
using System.Text;

namespace Lamprey
{
    public class InputMapping
    {
        public bool Builtin { get; set; }
        public string Device { get; set; }
        public string Name { get; set; }
        public Input.InputCode Code { get; set; }
    }
}
