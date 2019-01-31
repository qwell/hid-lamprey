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

        public InputCategory Category { get; set; } = InputCategory.UnknownCategory;
        public InputCodeType Type { get; set; } = InputCodeType.UnknownType;
        public int Code { get; set; }
        public String Description { get; set; }
    }
}
