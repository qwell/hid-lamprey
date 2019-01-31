using System;
using System.Collections;
using System.Collections.Generic;

namespace Lamprey
{
    public class Shortcut
    {
        public class Button : InputCode
        {
            public Button(InputType Type, InputCodeZ Code, string Description) : base(Type, Code, Description) { }
            public int TriggerLow { get; }
            public int TriggerHigh { get; }
        }

        public class ShortcutButtons : IEnumerable<Shortcut.Button>
        {
            public IEnumerator<Shortcut.Button> GetEnumerator()
            {
                return List.GetEnumerator();
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return List.GetEnumerator();
            }

            private List<Shortcut.Button> List { get; } = new List<Shortcut.Button>();

            public int Count => List.Count;
        }

        public string Name { get; }
        public ShortcutButtons Buttons { get; set; } = new ShortcutButtons();
    }
}
