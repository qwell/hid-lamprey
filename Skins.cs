using System.Collections;
using System.Collections.Generic;

namespace lamprey
{
    public sealed class Skins : IEnumerable<Skin>
    {
        public static Skins Instance { get; } = new Skins();
        static Skins() { }
        private Skins() { }

        public IEnumerator GetEnumerator()
        {
            return List.GetEnumerator();
        }
        IEnumerator<Skin> IEnumerable<Skin>.GetEnumerator()
        {
            return List.GetEnumerator();
        }

        private List<Skin> List { get; } = new List<Skin>();

        public int Count => List.Count;

        public void Add(Skin skin)
        {
            List.Add(skin);
        }

        public void Remove(Skin skin)
        {
            List.Remove(skin);
        }
    }
}

