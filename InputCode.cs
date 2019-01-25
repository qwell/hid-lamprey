using System;

namespace lamprey
{
    public class InputCode
    {
        public enum InputCategory
        {
            Button,
            AxisAbsolute,
            AxisRelative,
        }
        public enum InputCodeType
        {
            UnknownType,
            GamepadButton,
            MouseButton,
            KeyboardKey,
            KeyboardNumpadKey,
            KeyboardMiscKey,
            AbsoluteAxis,
            RelativeAxis,
        }

        public InputCategory Category { get; }
        public InputCodeType Type { get; }
        public int Code { get; }
        public String Description { get; }
    }
}
