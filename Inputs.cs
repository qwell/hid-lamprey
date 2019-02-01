using System;
using System.Collections;
using System.Collections.Generic;

namespace Lamprey
{
    public sealed class Inputs : IEnumerable<Input>
    {
        public static Inputs Instance { get; } = new Inputs();
        static Inputs() { }
        private Inputs()
        {
            Load();
        }

        public IEnumerator GetEnumerator()
        {
            return List.GetEnumerator();
        }
        IEnumerator<Input> IEnumerable<Input>.GetEnumerator()
        {
            return List.GetEnumerator();
        }

        private List<Input> List { get; } = new List<Input>();

        public int Count => List.Count;

        public void Add(Input input)
        {
            List.Add(input);
        }

        public void Remove(Input input)
        {
            List.Remove(input);
        }

        public Input FindByCode(Input.InputCode code)
        {
            foreach (Input input in List)
            {
                if (code == input.Code)
                {
                    return input;
                }
            }
            return null;
        }

        public Input FindByCode(string code)
        {
            try
            {
                Input input = (Input)Enum.Parse(typeof(Input.InputCode), code);

                return this.FindByCode(input.Code);
            }
            catch (ArgumentException) {
                return null;
            }
        }

        private void Load()
        {
            List.AddRange(new Input[] {
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonEast, "A (East)"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonSouth, "B (South)"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonC, "C"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonNorth, "X (North)"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonWest, "Y (West)"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonZ, "Z"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonTriggerL, "L1"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonTriggerR, "R1"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonTriggerL2, "L2 (Digital)"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonTriggerR2, "R2 (Digital)"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonSelect, "Select"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonStart, "Start"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonMode, "Menu"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonThumbL, "Thumb Left"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonThumbR, "Thumb Right"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonDPadUp, "DPad Up"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonDPadDown, "DPad Down"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonDPadLeft, "DPad Left"),
                new Input(Input.InputType.GamepadButton, Input.InputCode.ButtonDPadRight, "DPad Right"),

                new Input(Input.InputType.MouseButton, Input.InputCode.MouseButtonLeft, "Button Left"),
                new Input(Input.InputType.MouseButton, Input.InputCode.MouseButtonRight, "Button Right"),
                new Input(Input.InputType.MouseButton, Input.InputCode.MouseButtonMiddle, "Button Middle"),
                new Input(Input.InputType.MouseButton, Input.InputCode.MouseButton4, "Button 4"),
                new Input(Input.InputType.MouseButton, Input.InputCode.MouseButton5, "Button 5"),
                new Input(Input.InputType.MouseButton, Input.InputCode.MouseButton6, "Button 6"),
                new Input(Input.InputType.MouseButton, Input.InputCode.MouseButton7, "Button 7"),
                new Input(Input.InputType.MouseButton, Input.InputCode.MouseButton8, "Button 8"),

            });
        }
    }
}
