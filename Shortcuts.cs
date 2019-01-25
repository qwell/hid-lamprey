using System.Collections;
using System.Collections.Generic;

namespace Lamprey
{
    public sealed class Shortcuts : IEnumerable<Shortcut>
    {
        public static Shortcuts Instance { get; } = new Shortcuts();
        static Shortcuts() { }
        private Shortcuts() { }

        public IEnumerator GetEnumerator()
        {
            return List.GetEnumerator();
        }
        IEnumerator<Shortcut> IEnumerable<Shortcut>.GetEnumerator()
        {
            return List.GetEnumerator();
        }

        private List<Shortcut> List { get; } = new List<Shortcut>();

        public int Count => List.Count;

        public void Add(Shortcut shortcut)
        {
            List.Add(shortcut);
        }

        public void Remove(Shortcut shortcut)
        {
            List.Remove(shortcut);
        }
    }
}
