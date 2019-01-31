using System.Collections;
using System.Collections.Generic;

namespace Lamprey
{
    public sealed class InputCodes : IEnumerable<InputCode>
    {
        public static InputCodes Instance { get; } = new InputCodes();
        static InputCodes() { }
        private InputCodes()
        {
            Load();
        }

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

        private void Load()
        {
            List.AddRange(new InputCode[] {
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonEast, "A (East)"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonSouth, "B (South)"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonC, "C"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonNorth, "X (North)"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonWest, "Y (West)"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonZ, "Z"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonTriggerL, "L1"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonTriggerR, "R1"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonTriggerL2, "L2 (Digital)"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonTriggerR2, "R2 (Digital)"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonSelect, "Select"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonStart, "Start"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonMode, "Menu"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonThumbL, "Thumb Left"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonThumbR, "Thumb Right"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonDPadUp, "DPad Up"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonDPadDown, "DPad Down"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonDPadLeft, "DPad Left"),
                new InputCode(InputCode.InputType.GamepadButton, InputCode.InputCodeZ.ButtonDPadRight, "DPad Right"),

                new InputCode(InputCode.InputType.MouseButton, InputCode.InputCodeZ.MouseButtonLeft, "Button Left"),
                new InputCode(InputCode.InputType.MouseButton, InputCode.InputCodeZ.MouseButtonRight, "Button Right"),
                new InputCode(InputCode.InputType.MouseButton, InputCode.InputCodeZ.MouseButtonMiddle, "Button Middle"),
                new InputCode(InputCode.InputType.MouseButton, InputCode.InputCodeZ.MouseButton4, "Button 4"),
                new InputCode(InputCode.InputType.MouseButton, InputCode.InputCodeZ.MouseButton5, "Button 5"),
                new InputCode(InputCode.InputType.MouseButton, InputCode.InputCodeZ.MouseButton6, "Button 6"),
                new InputCode(InputCode.InputType.MouseButton, InputCode.InputCodeZ.MouseButton7, "Button 7"),
                new InputCode(InputCode.InputType.MouseButton, InputCode.InputCodeZ.MouseButton8, "Button 8"),

            });
        }
    }
}
