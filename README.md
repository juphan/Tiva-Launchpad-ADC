# Tiva-Launchpad-ADC
A Keil uVision project that uses C code to program a TM4C123GH6PM microcontroller to collect data from a single MyoWare muscle sensor and then send the results to a PC through the UART. The code is mainly used to display the basics of using the ADC on the Tiva Launchpad.

- Place project folder in your "my_project" folder

  (Ex: C:\ti\TivaWare_C_Series-2.1.4.178\examples\boards\my_projects\Myoware)

- Data from one channel is sampled at 200KHz (Max is 1MHz, but needs optimization to reach that level)

- Oversampling is performed to achieve stable ADC readings (Every 200 data points are averaged to get a stable reading)

- The actual number of data points being outputted from this ADC channel is 1000 samples/sec (1000 Hz)
  - Format of data being sampled from 1 channel and then sent through UART: '50\n'
  - Format of data being sampled from 4 channels and then sent through UART (Receiver needs to parse data): '59,58,90,11\n'

- The max baud rate of the Tiva Launchpad is 115200
  - This limits the number of data points that can be sent out to be 1000 samples/sec (1000 Hz) 
