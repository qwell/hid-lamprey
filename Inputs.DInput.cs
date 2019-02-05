using SharpDX.DirectInput;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Threading;

namespace Lamprey
{
    partial class Inputs
    {
        class DInput
        {
            private DirectInput DirectInput { get; } = new DirectInput();
            private List<WaitDevice> WaitDevices { get; } = new List<WaitDevice>();

            private class CompatInput
            {
                public Key DInputKey { get; }
                public Input.InputCode InputCode { get; }

                public CompatInput(Key DInputKey, Input.InputCode InputCode)
                {
                    this.DInputKey = DInputKey;
                    this.InputCode = InputCode;
                }
            }

            class WaitDevice
            {
                public WaitHandle Handle { get; }
                public Device Device { get; }

                public WaitDevice(WaitHandle Handle, Device Device)
                {
                    this.Handle = Handle;
                    this.Device = Device;
                }
            }

            private void RefreshDevices()
            {
                foreach (DeviceInstance deviceInstance in DirectInput.GetDevices())
                {
                    if (deviceInstance.Type == DeviceType.Device)
                    {
                        continue;
                    }

                    string deviceName = "DirectInput " + deviceInstance.InstanceName;
                    bool changed = false;

                    if (Controllers.Instance.FindByName(deviceName) == null)
                    {
                        Controller controller = new Controller()
                        {
                            Name = deviceName,
                        };

                        Controllers.Instance.Add(controller);

                        WaitHandle waitHandle = new AutoResetEvent(false);
                        Device device = null;

                        switch (deviceInstance.Type)
                        {
                            case DeviceType.Gamepad:
                            case DeviceType.Joystick:
                                Joystick joystick = new Joystick(DirectInput, deviceInstance.InstanceGuid);
                                device = joystick;

                                joystick.Properties.Range = new InputRange(-256, 256);

                                for (int i = 0; i < joystick.Capabilities.ButtonCount; i++)
                                {
                                    Controller.Button button = controller.Buttons.FindByName("button:" + i);
                                    if (button == null)
                                    {
                                        Input input = Inputs.Instance.FindByCode(Input.InputCode.UnknownCode);
                                        if (input == null)
                                        {
                                            continue;
                                        }
                                        button = new Controller.Button(input)
                                        {
                                            Name = "button:" + i,
                                        };
                                        controller.Buttons.Add(button);
                                    }
                                }

                                for (int i = 0; i < joystick.Capabilities.PovCount; i++)
                                {
                                    string[] directions = { "up", "down", "left", "right" };
                                    foreach (string direction in directions)
                                    {
                                        Controller.Button button = controller.Buttons.FindByName("dpad_" + direction + ":" + i);
                                        if (button == null)
                                        {
                                            Input input = Inputs.Instance.FindByCode(Input.InputCode.UnknownCode);
                                            if (input == null)
                                            {
                                                continue;
                                            }
                                            button = new Controller.Button(input)
                                            {
                                                Name = "dpad_" + direction + ":" + i,
                                            };
                                            controller.Buttons.Add(button);
                                        }
                                    }
                                }

                                break;
                            case DeviceType.Mouse:
                            case DeviceType.ScreenPointer:
                                Mouse mouse = new Mouse(DirectInput);
                                device = mouse;

                                for (int i = 0; i < mouse.Capabilities.ButtonCount; i++)
                                {
                                    Controller.Button button = controller.Buttons.FindByName("button:" + i);
                                    if (button == null)
                                    {
                                        Input input = Inputs.Instance.FindByCode(Input.InputCode.UnknownCode);
                                        if (input == null)
                                        {
                                            continue;
                                        }
                                        button = new Controller.Button(input)
                                        {
                                            Name = "button:" + i,
                                        };
                                        controller.Buttons.Add(button);
                                    }

                                }

                                break;
                            case DeviceType.Keyboard:
                                Keyboard keyboard = new Keyboard(DirectInput);
                                device = keyboard;

                                foreach (CompatInput compatInput in CompatInputs)
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
                                    }
                                }
                                break;
                        }

                        if (device != null)
                        {
                            device.SetCooperativeLevel(Process.GetCurrentProcess().MainWindowHandle, CooperativeLevel.Background | CooperativeLevel.NonExclusive);
                            device.SetNotification(waitHandle);
                            device.Acquire();

                            WaitDevices.Add(new WaitDevice(waitHandle, device));
                        }

                        changed = true;
                    }

                    if (changed)
                    {
                        Controllers.Instance.Change();
                    }
                }
            }

            public void Poll()
            {
                if (WaitDevices.Count == 0)
                {
                    RefreshDevices();
                }

                int res = 0;
                do
                {
                    int triggerHandle = WaitHandle.WaitAny(WaitDevices.ConvertAll(new Converter<WaitDevice, WaitHandle>(i => i.Handle)).ToArray(), 500);
                    if (triggerHandle >= 256)
                    {
                        RefreshDevices();
                        continue;
                    }

                    bool changed = false;

                    Device device = WaitDevices.ConvertAll(new Converter<WaitDevice, Device>(i => i.Device)).ToArray()[triggerHandle];

                    string deviceName = "DirectInput " + device.Information.InstanceName;
                    Controller controller = Controllers.Instance.FindByName(deviceName);

                    switch (device.Information.Type)
                    {
                        case DeviceType.Gamepad:
                        case DeviceType.Joystick:
                            Joystick joystick = (Joystick)device;
                            JoystickState joystickState = joystick.GetCurrentState();

                            break;
                        case DeviceType.Mouse:
                        case DeviceType.ScreenPointer:
                            Mouse mouse = (Mouse)device;

                            break;
                        case DeviceType.Keyboard:
                            Keyboard keyboard = (Keyboard)device;
                            KeyboardState keyboardState = keyboard.GetCurrentState();

                            foreach (CompatInput compatInput in CompatInputs)
                            {
                                Controller.Button button = controller.Buttons.FindByCode(compatInput.InputCode);

                                int value = keyboardState.IsPressed(compatInput.DInputKey) ? 1 : 0;
                                if (button.Value != value)
                                {
                                    button.Value = value;
                                    changed = true;
                                }
                            }

                            break;
                    }

                    if (changed)
                    {
                        Controllers.Instance.Change();
                    }
                } while (res == 0);
            }

            private readonly CompatInput[] CompatInputs = new CompatInput[] {
            new CompatInput(Key.D0, Input.InputCode.Key0),
            new CompatInput(Key.D1, Input.InputCode.Key1),
            new CompatInput(Key.D2, Input.InputCode.Key2),
            new CompatInput(Key.D3, Input.InputCode.Key3),
            new CompatInput(Key.D4, Input.InputCode.Key4),
            new CompatInput(Key.D5, Input.InputCode.Key5),
            new CompatInput(Key.D6, Input.InputCode.Key6),
            new CompatInput(Key.D7, Input.InputCode.Key7),
            new CompatInput(Key.D8, Input.InputCode.Key8),
            new CompatInput(Key.D9, Input.InputCode.Key9),
            new CompatInput(Key.A, Input.InputCode.KeyA),
            new CompatInput(Key.B, Input.InputCode.KeyB),
            new CompatInput(Key.C, Input.InputCode.KeyC),
            new CompatInput(Key.D, Input.InputCode.KeyD),
            new CompatInput(Key.E, Input.InputCode.KeyE),
            new CompatInput(Key.F, Input.InputCode.KeyF),
            new CompatInput(Key.G, Input.InputCode.KeyG),
            new CompatInput(Key.H, Input.InputCode.KeyH),
            new CompatInput(Key.I, Input.InputCode.KeyI),
            new CompatInput(Key.J, Input.InputCode.KeyJ),
            new CompatInput(Key.K, Input.InputCode.KeyK),
            new CompatInput(Key.L, Input.InputCode.KeyL),
            new CompatInput(Key.M, Input.InputCode.KeyM),
            new CompatInput(Key.N, Input.InputCode.KeyN),
            new CompatInput(Key.O, Input.InputCode.KeyO),
            new CompatInput(Key.P, Input.InputCode.KeyP),
            new CompatInput(Key.Q, Input.InputCode.KeyQ),
            new CompatInput(Key.R, Input.InputCode.KeyR),
            new CompatInput(Key.S, Input.InputCode.KeyS),
            new CompatInput(Key.T, Input.InputCode.KeyT),
            new CompatInput(Key.U, Input.InputCode.KeyU),
            new CompatInput(Key.V, Input.InputCode.KeyV),
            new CompatInput(Key.W, Input.InputCode.KeyW),
            new CompatInput(Key.X, Input.InputCode.KeyX),
            new CompatInput(Key.Y, Input.InputCode.KeyY),
            new CompatInput(Key.Z, Input.InputCode.KeyZ),
            new CompatInput(Key.F1, Input.InputCode.KeyF1),
            new CompatInput(Key.F2, Input.InputCode.KeyF2),
            new CompatInput(Key.F3, Input.InputCode.KeyF3),
            new CompatInput(Key.F4, Input.InputCode.KeyF4),
            new CompatInput(Key.F5, Input.InputCode.KeyF5),
            new CompatInput(Key.F6, Input.InputCode.KeyF6),
            new CompatInput(Key.F7, Input.InputCode.KeyF7),
            new CompatInput(Key.F8, Input.InputCode.KeyF8),
            new CompatInput(Key.F9, Input.InputCode.KeyF9),
            new CompatInput(Key.F10, Input.InputCode.KeyF10),
            new CompatInput(Key.F11, Input.InputCode.KeyF11),
            new CompatInput(Key.F12, Input.InputCode.KeyF12),
            new CompatInput(Key.F13, Input.InputCode.KeyF13),
            new CompatInput(Key.F14, Input.InputCode.KeyF14),
            new CompatInput(Key.F15, Input.InputCode.KeyF15),

            new CompatInput(Key.NumberPad0, Input.InputCode.Numpad0),
            new CompatInput(Key.NumberPad1, Input.InputCode.Numpad1),
            new CompatInput(Key.NumberPad2, Input.InputCode.Numpad2),
            new CompatInput(Key.NumberPad3, Input.InputCode.Numpad3),
            new CompatInput(Key.NumberPad4, Input.InputCode.Numpad4),
            new CompatInput(Key.NumberPad5, Input.InputCode.Numpad5),
            new CompatInput(Key.NumberPad6, Input.InputCode.Numpad6),
            new CompatInput(Key.NumberPad7, Input.InputCode.Numpad7),
            new CompatInput(Key.NumberPad8, Input.InputCode.Numpad8),
            new CompatInput(Key.NumberPad9, Input.InputCode.Numpad9),
        };
        }
    }
}