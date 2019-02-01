using System.Collections;
using System.Collections.Generic;

namespace Lamprey
{
    public sealed class InputMappings : IEnumerable<InputMapping>
    {
        public static InputMappings Instance { get; } = new InputMappings();
        static InputMappings() { }
        private InputMappings() {
            Load();
        }

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

        public bool Remove(InputMapping inputMapping)
        {
            return List.Remove(inputMapping);
        }

        private void Load()
        {

        }
    }
}
