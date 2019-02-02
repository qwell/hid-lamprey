using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Lamprey
{
    public class Controller
    {
        public class Button : Input
        {
            public Button(Input input) : base(input) { }
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

            public void Add(Button button)
            {
                List.Add(button);
            }

            public bool Remove(Button button)
            {
                return List.Remove(button);
            }

            public Button FindByCode(Input.InputCode code)
            {
                foreach (Button button in List)
                {
                    if (code == button.Code)
                    {
                        return button;
                    }
                }
                return null;
            }
        }

        public string Name { get; set; }
        public ControllerButtons Buttons { get; set; } = new ControllerButtons();
    }
}
