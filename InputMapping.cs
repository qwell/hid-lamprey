using System;
using System.Collections.Generic;
using System.Text;

namespace Lamprey
{
    public class InputMapping
    {
        public Boolean Builtin { get; set; }
        public string Device { get; set; }
        public string Name { get; set; }
        public InputCode.InputCodeZ Code { get; set; }
        public int Value { get; set; }
    }
}
