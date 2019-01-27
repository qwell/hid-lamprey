using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Lamprey
{
    public class Skin
    {
        public Skin() { }

        public class Background
        {
            public string Name { get; set; }
            public string Filename { get; set; }
        }

        public class Button : InputCode
        {
            public string Filename { get; }
            public int X { get; }
            public int Y { get; }
        }

        public class Axis
        {
            public class AxisX : InputCode
            {
                public int X { get; }
                public int Offset { get; }
                public int Trigger { get; }
            }

            public class AxisY : InputCode
            {
                public int Y { get; }
                public int Offset { get; }
                public int Trigger { get; }
            }

            public string Filename { get; }
            public AxisX X { get; }
            public AxisY Y { get; }
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

            public void Add(Skin.Background background)
            {
                List.Add(background);
            }

            public void Remove(Skin.Background background)
            {
                List.Remove(background);
            }

            public Skin.Background FindByName(string name)
            {
                foreach (Skin.Background background in List)
                {
                    if (name == background.Name)
                    {
                        return background;
                    }
                }
                return null;
            }
        }

        public class SkinButtons : IEnumerable<Skin.Button>
        {
            public IEnumerator<Skin.Button> GetEnumerator()
            {
                return List.GetEnumerator();
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return List.GetEnumerator();
            }

            private List<Skin.Button> List { get; } = new List<Skin.Button>();

            public int Count => List.Count;
        }

        public class SkinAxes : IEnumerable<Skin.Axis>
        {
            public IEnumerator<Skin.Axis> GetEnumerator()
            {
                return List.GetEnumerator();
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return List.GetEnumerator();
            }

            private List<Skin.Axis> List { get; } = new List<Skin.Axis>();

            public int Count => List.Count;
        }

        public string Name { get; set; }
        public string Path { get; set; }
        public SkinBackgrounds Backgrounds { get; set; } = new SkinBackgrounds();
        public SkinButtons Buttons { get; set; } = new SkinButtons();
        public SkinAxes Axes { get; set; } = new SkinAxes();
    }
}
