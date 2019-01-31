using System;

namespace Lamprey
{
    public class InputCode
    {
        public enum InputType
        {
            UnknownType,
            GamepadButton,
            MouseButton,
            KeyboardKey,
            NumpadKey,
            MiscKey,
            AbsoluteAxis,
            RelativeAxis,
        }

        public InputCode(InputType Type, InputCodeZ Code, string Description)
        {
            this.Type = Type;
            this.Code = Code;
            this.Description = Description ?? Code.ToString();
        }

        public InputType Type { get; } = InputType.UnknownType;
        public InputCodeZ Code { get; } = InputCodeZ.UnknownCode;
        public string Description { get; } = InputCodeZ.UnknownCode.ToString();

        public enum InputCodeZ
        {
            UnknownCode,

            ButtonSouth,
            ButtonB = ButtonSouth,
            ButtonEast,
            ButtonA = ButtonEast,
            ButtonC,
            ButtonNorth,
            ButtonX = ButtonNorth,
            ButtonWest,
            ButtonY = ButtonWest,
            ButtonZ,
            ButtonTriggerL,
            ButtonTriggerR,
            ButtonTriggerL2,
            ButtonTriggerR2,
            ButtonSelect,
            ButtonStart,
            ButtonMode,
            ButtonThumbL,
            ButtonThumbR,
            ButtonDPadUp,
            ButtonDPadDown,
            ButtonDPadLeft,
            ButtonDPadRight,

            MouseButton1,
            MouseButtonLeft = MouseButton1,
            MouseButton2,
            MouseButtonRight = MouseButton2,
            MouseButton3,
            MouseButtonMiddle = MouseButton3,
            MouseButton4,
            MouseButton5,
            MouseButton6,
            MouseButton7,
            MouseButton8,

            Key0,
            Key1,
            Key2,
            Key3,
            Key4,
            Key5,
            Key6,
            Key7,
            Key8,
            Key9,
            KeyA,
            KeyB,
            KeyC,
            KeyD,
            KeyE,
            KeyF,
            KeyG,
            KeyH,
            KeyI,
            KeyJ,
            KeyK,
            KeyL,
            KeyM,
            KeyN,
            KeyO,
            KeyP,
            KeyQ,
            KeyR,
            KeyS,
            KeyT,
            KeyU,
            KeyV,
            KeyW,
            KeyX,
            KeyY,
            KeyZ,
            KeyF1,
            KeyF2,
            KeyF3,
            KeyF4,
            KeyF5,
            KeyF6,
            KeyF7,
            KeyF8,
            KeyF9,
            KeyF10,
            KeyF11,
            KeyF12,
            KeyF13,
            KeyF14,
            KeyF15,
            KeyF16,
            KeyF17,
            KeyF18,
            KeyF19,
            KeyF20,
            KeyF21,
            KeyF22,
            KeyF23,
            KeyF24,

            Numpad0,
            Numpad1,
            Numpad2,
            Numpad3,
            Numpad4,
            Numpad5,
            Numpad6,
            Numpad7,
            Numpad8,
            Numpad9,
        }
    }
}
