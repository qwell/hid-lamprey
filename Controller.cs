using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Lamprey
{
    public sealed class Controller
    {
        public static Controller Instance { get; } = new Controller();
        static Controller() { }
        private Controller() { }

        public class Button : InputCode
        {
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

        public String Name { get; }
        public ControllerButtons Buttons { get; set; }
    }
}
