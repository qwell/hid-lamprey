﻿using System;
using System.Runtime.InteropServices;
using System.Threading;

namespace Lamprey
{
    partial class Inputs
    {
        class XInput
        {
            private static readonly int MaxDevices = 4;

            private class CompatInput
            {
                public int XInputCode { get; }
                public Input.InputCode InputCode { get; }

                public CompatInput(int XInputCode, Input.InputCode InputCode)
                {
                    this.XInputCode = XInputCode;
                    this.InputCode = InputCode;
                }
            }

            public void Poll()
            {
                uint[] PacketNumber = new uint[MaxDevices];

                int res = 0;
                do
                {
                    for (int i = 0; i < MaxDevices; i++)
                    {
                        bool changed = false;

                        XInputState newState = new XInputState();
                        if (XInputGetState(i, ref newState) != 0)
                        {
                            continue;
                        }

                        if (newState.PacketNumber <= PacketNumber[i])
                        {
                            continue;
                        }
                        PacketNumber[i] = newState.PacketNumber;

                        Controller controller = Controllers.Instance.FindByName("XInput" + i);
                        if (controller == null)
                        {
                            controller = new Controller()
                            {
                                Name = "XInput" + i,
                            };

                            Controllers.Instance.Add(controller);

                            changed = true;
                        }

                        foreach (CompatInput compatInput in compatInputs)
                        {
                            Controller.Button button = controller.Buttons.FindByCode(compatInput.InputCode);
                            if (button == null)
                            {
                                Input input = Inputs.Instance.FindByCode(compatInput.InputCode);
                                if (input == null)
                                {
                                    continue;
                                }
                                button = new Controller.Button(input)
                                {
                                    Name = input.Description,
                                };
                                controller.Buttons.Add(button);

                                changed = true;
                            }

                            int value = (newState.Gamepad.Buttons & compatInput.XInputCode) != 0 ? 1 : 0;
                            if (button.Value != value)
                            {
                                button.Value = value;
                                changed = true;
                            }
                        }

                        if (changed)
                        {
                            Controllers.Instance.Change();
                        }
                    }
                    Thread.Yield();
                } while (res == 0);
            }

            private static readonly int XINPUT_GAMEPAD_DPAD_UP = 0x0001;
            private static readonly int XINPUT_GAMEPAD_DPAD_DOWN = 0x0002;
            private static readonly int XINPUT_GAMEPAD_DPAD_LEFT = 0x0004;
            private static readonly int XINPUT_GAMEPAD_DPAD_RIGHT = 0x0008;
            private static readonly int XINPUT_GAMEPAD_START = 0x0010;
            private static readonly int XINPUT_GAMEPAD_BACK = 0x0020;
            private static readonly int XINPUT_GAMEPAD_LEFT_THUMB = 0x0040;
            private static readonly int XINPUT_GAMEPAD_RIGHT_THUMB = 0x0080;
            private static readonly int XINPUT_GAMEPAD_LEFT_SHOULDER = 0x0100;
            private static readonly int XINPUT_GAMEPAD_RIGHT_SHOULDER = 0x0200;
            private static readonly int XINPUT_GAMEPAD_A = 0x1000;
            private static readonly int XINPUT_GAMEPAD_B = 0x2000;
            private static readonly int XINPUT_GAMEPAD_X = 0x4000;
            private static readonly int XINPUT_GAMEPAD_Y = 0x8000;

            private static CompatInput[] compatInputs = new CompatInput[] {
            new CompatInput(XINPUT_GAMEPAD_DPAD_UP, Input.InputCode.ButtonDPadUp),
            new CompatInput(XINPUT_GAMEPAD_DPAD_DOWN, Input.InputCode.ButtonDPadDown),
            new CompatInput(XINPUT_GAMEPAD_DPAD_LEFT, Input.InputCode.ButtonDPadLeft),
            new CompatInput(XINPUT_GAMEPAD_DPAD_RIGHT, Input.InputCode.ButtonDPadRight),
            new CompatInput(XINPUT_GAMEPAD_START, Input.InputCode.ButtonStart),
            new CompatInput(XINPUT_GAMEPAD_BACK, Input.InputCode.ButtonSelect),
            new CompatInput(XINPUT_GAMEPAD_LEFT_THUMB, Input.InputCode.ButtonThumbL),
            new CompatInput(XINPUT_GAMEPAD_RIGHT_THUMB, Input.InputCode.ButtonThumbR),
            new CompatInput(XINPUT_GAMEPAD_LEFT_SHOULDER, Input.InputCode.ButtonTriggerL),
            new CompatInput(XINPUT_GAMEPAD_RIGHT_SHOULDER, Input.InputCode.ButtonTriggerR),
            new CompatInput(XINPUT_GAMEPAD_A, Input.InputCode.ButtonSouth),
            new CompatInput(XINPUT_GAMEPAD_B, Input.InputCode.ButtonEast),
            new CompatInput(XINPUT_GAMEPAD_X, Input.InputCode.ButtonWest),
            new CompatInput(XINPUT_GAMEPAD_Y, Input.InputCode.ButtonNorth),
        };

            [DllImport("xinput1_4.dll")]
            public static extern int XInputGetState(int UserIndex, ref XInputState State);

            [StructLayout(LayoutKind.Explicit)]
            public struct XInputState
            {
                [FieldOffset(0)]
                public uint PacketNumber;

                [FieldOffset(4)]
                public XInputGamepad Gamepad;
            }

            [StructLayout(LayoutKind.Explicit)]
            public struct XInputGamepad
            {
                [MarshalAs(UnmanagedType.I2)]
                [FieldOffset(0)]
                public ushort Buttons;

                [MarshalAs(UnmanagedType.I1)]
                [FieldOffset(2)]
                public byte LeftTrigger;

                [MarshalAs(UnmanagedType.I1)]
                [FieldOffset(3)]
                public byte RightTrigger;

                [MarshalAs(UnmanagedType.I2)]
                [FieldOffset(4)]
                public short ThumbLX;

                [MarshalAs(UnmanagedType.I2)]
                [FieldOffset(6)]
                public short ThumbLY;

                [MarshalAs(UnmanagedType.I2)]
                [FieldOffset(8)]
                public short ThumbRX;

                [MarshalAs(UnmanagedType.I2)]
                [FieldOffset(10)]
                public short ThumbRY;
            }
        }
    }
}