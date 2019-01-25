using System.Collections;
using System.Collections.Generic;

namespace lamprey
{
    public sealed class InputMappings : IEnumerable<InputMapping>
    {
        public static InputMappings Instance { get; } = new InputMappings();
        static InputMappings() { }
        private InputMappings() { }

        public IEnumerator GetEnumerator()
        {
            return List.GetEnumerator();
        }
        IEnumerator<InputMapping> IEnumerable<InputMapping>.GetEnumerator()
        {
            return List.GetEnumerator();
        }

        private List<InputMapping> List { get; } = new List<InputMapping>();

        public int Count => List.Count;

        public void Add(InputMapping inputMapping)
        {
            List.Add(inputMapping);
        }

        public void Remove(InputMapping inputMapping)
        {
            List.Remove(inputMapping);
        }
    }
}
