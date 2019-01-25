using System.Collections;
using System.Collections.Generic;

namespace lamprey
{
    public sealed class InputCodes : IEnumerable<InputCode>
    {
        public static InputCodes Instance { get; } = new InputCodes();
        static InputCodes() { }
        private InputCodes() { }

        public IEnumerator GetEnumerator()
        {
            return List.GetEnumerator();
        }
        IEnumerator<InputCode> IEnumerable<InputCode>.GetEnumerator()
        {
            return List.GetEnumerator();
        }

        private List<InputCode> List { get; } = new List<InputCode>();

        public int Count => List.Count;

        public void Add(InputCode inputCode)
        {
            List.Add(inputCode);
        }

        public void Remove(InputCode inputCode)
        {
            List.Remove(inputCode);
        }
    }
}
