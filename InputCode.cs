using System;

namespace Lamprey
{
    public class InputCode
    {
        public enum InputCategory
        {
            UnknownCategory,
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

        public InputCategory Category { get; } = InputCategory.UnknownCategory;
        public InputCodeType Type { get; } = InputCodeType.UnknownType;
        public int Code { get; }
        public String Description { get; }
    }
}
