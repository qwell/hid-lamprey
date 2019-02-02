using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;

namespace Lamprey
{
    public sealed class Inputs : IEnumerable<Input>
    {
        public static Inputs Instance { get; } = new Inputs();
        static Inputs() { }
        private Inputs()
        {
            Load();

            Thread t = new Thread(new ThreadStart(XInput.Poll))
            {
                IsBackground = true
            };
            t.Start();
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

        public bool Remove(Input input)
        {
            return List.Remove(input);
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
            if (string.IsNullOrEmpty(code))
            {
                return null;
            }

            Input.InputCode inputCode;
            if (!Enum.TryParse(code, true, out inputCode))
            {
                return null;
            }

            return this.FindByCode(inputCode);
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

                new Input(Input.InputType.KeyboardKey, Input.InputCode.Key0, "0"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.Key1, "1"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.Key2, "2"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.Key3, "3"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.Key4, "4"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.Key5, "5"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.Key6, "6"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.Key7, "7"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.Key8, "8"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.Key9, "9"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyA, "A"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyB, "B"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyC, "C"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyD, "D"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyE, "E"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF, "F"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyG, "G"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyH, "H"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyI, "I"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyJ, "J"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyK, "K"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyL, "L"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyM, "M"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyN, "N"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyO, "O"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyP, "P"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyQ, "Q"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyR, "R"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyS, "S"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyT, "T"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyU, "U"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyV, "V"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyW, "W"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyX, "X"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyY, "Y"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyZ, "Z"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF1, "F1"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF2, "F2"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF3, "F3"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF4, "F4"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF5, "F5"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF6, "F6"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF7, "F7"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF8, "F8"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF9, "F9"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF10, "F10"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF11, "F11"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF12, "F12"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF13, "F13"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF14, "F14"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF15, "F15"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF16, "F16"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF17, "F17"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF18, "F18"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF19, "F19"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF20, "F20"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF21, "F21"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF22, "F22"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF23, "F23"),
                new Input(Input.InputType.KeyboardKey, Input.InputCode.KeyF24, "F24"),

                new Input(Input.InputType.NumpadKey, Input.InputCode.Numpad0, "Numpad 0"),
                new Input(Input.InputType.NumpadKey, Input.InputCode.Numpad1, "Numpad 1"),
                new Input(Input.InputType.NumpadKey, Input.InputCode.Numpad2, "Numpad 2"),
                new Input(Input.InputType.NumpadKey, Input.InputCode.Numpad3, "Numpad 3"),
                new Input(Input.InputType.NumpadKey, Input.InputCode.Numpad4, "Numpad 4"),
                new Input(Input.InputType.NumpadKey, Input.InputCode.Numpad5, "Numpad 5"),
                new Input(Input.InputType.NumpadKey, Input.InputCode.Numpad6, "Numpad 6"),
                new Input(Input.InputType.NumpadKey, Input.InputCode.Numpad7, "Numpad 7"),
                new Input(Input.InputType.NumpadKey, Input.InputCode.Numpad8, "Numpad 8"),
                new Input(Input.InputType.NumpadKey, Input.InputCode.Numpad9, "Numpad 9"),
            });
        }
    }
}
