using System;
using System.Collections;
using System.Collections.Generic;

namespace Lamprey
{
    public sealed class Controller
    {
        public static Controller Instance { get; } = new Controller();
        static Controller() { }
        private Controller() { }

        public class Button : Input
        {
            public Button(InputType Type, InputCode Code, string Description) : base(Type, Code, Description) { }
            public int Value { get; set; }
            public int Decay { get; set; }
        }

        public class ControllerButtons : IEnumerable<Controller.Button>
        {
            public IEnumerator<Controller.Button> GetEnumerator()
            {
                return List.GetEnumerator();
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return List.GetEnumerator();
            }

            private List<Controller.Button> List { get; } = new List<Controller.Button>();

            public int Count => List.Count;
        }

        public string Name { get; }
        public ControllerButtons Buttons { get; set; } = new ControllerButtons();
    }
}
