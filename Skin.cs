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
            public string Filename { get; set; }
            public int PosX { get; set; }
            public int PosY { get; set; }
        }

        public class Axis
        {
            public class AxisX : InputCode
            {
                public int Offset { get; set; }
                public int Trigger { get; set; }
            }

            public class AxisY : InputCode
            {
                public int Offset { get; set; }
                public int Trigger { get; set; }
            }

            public string Filename { get; set; }
            public int PosX { get; set; }
            public int PosY { get; set; }
            public AxisX X { get; set; }
            public AxisY Y { get; set; }
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

            public void Add(Skin.Button button)
            {
                List.Add(button);
            }

            public void Remove(Skin.Button button)
            {
                List.Remove(button);
            }
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

            public void Add(Skin.Axis axis)
            {
                List.Add(axis);
            }

            public void Remove(Skin.Axis axis)
            {
                List.Remove(axis);
            }
        }

        public string Name { get; set; }
        public string Path { get; set; }
        public SkinBackgrounds Backgrounds { get; set; } = new SkinBackgrounds();
        public SkinButtons Buttons { get; set; } = new SkinButtons();
        public SkinAxes Axes { get; set; } = new SkinAxes();
    }
}
