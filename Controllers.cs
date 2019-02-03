using System;
using System.Collections;
using System.Collections.Generic;

namespace Lamprey
{
    public sealed class Controllers : IEnumerable<Controller>
    {
        public static Controllers Instance { get; } = new Controllers();
        static Controllers() { }
        private Controllers() { }

        public IEnumerator GetEnumerator()
        {
            return List.GetEnumerator();
        }
        IEnumerator<Controller> IEnumerable<Controller>.GetEnumerator()
        {
            return List.GetEnumerator();
        }

        private List<Controller> List { get; } = new List<Controller>();
        public event EventHandler ControllerChanged;

        public int Count => List.Count;

        public void Add(Controller controller)
        {
            List.Add(controller);
        }

        public bool Remove(Controller controller)
        {
            return List.Remove(controller);
        }

        public Controller FindByName(string name)
        {
            foreach (Controller controller in List)
            {
                if (name == controller.Name)
                {
                    return controller;
                }
            }
            return null;
        }

        public void Change()
        {
            ControllerChanged?.Invoke(this, null);
        }
    }
}
