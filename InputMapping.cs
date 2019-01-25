using System;
using System.Collections.Generic;
using System.Text;

namespace lamprey
{
    public class InputMapping
    {
        public Boolean Builtin { get; set; }
        public string Device { get; set; }
        public string Name { get; set; }
        public InputCode.InputCategory Category { get; set; }
        public int Code { get; set; }
        public int Value { get; set; }
    }
}
