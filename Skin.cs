using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace lamprey
{
    public class Skin
    {
        public class Background
        {
            public string Name { get; }
        }

        public class SkinBackgrounds : IEnumerable<Skin.Background>
        {
            public IEnumerator<Skin.Background> GetEnumerator()
            {
                return List.GetEnumerator();
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return List.GetEnumerator();
            }

            private List<Skin.Background> List { get; } = new List<Skin.Background>();

            public int Count => List.Count;
        }

        public string Name { get; set; }
        public SkinBackgrounds Backgrounds { get; set; }
    }
}
