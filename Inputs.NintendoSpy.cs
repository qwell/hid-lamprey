using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Text;
using System.Threading;

namespace Lamprey
{
    partial class Inputs
    {
        class NintendoSpy
        {
            public void Poll()
            {
                SerialPort serialPort = new SerialPort();
                serialPort.DataReceived += SerialPort_DataReceived;

                serialPort.Open();

                int res = 0;
                do
                {
                    Thread.Sleep(new TimeSpan(24, 0, 0));
                } while (res == 0);

                serialPort.Close();
            }

            private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
            {
            }
        }
    }
}
