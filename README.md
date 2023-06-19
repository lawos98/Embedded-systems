## Description

AGH The WIET course expands the scope of competence, in the design and construction of embedded devices with an emphasis on practical skills.

## List

* [Concept](documentation/concept)
* [Overview](documentation/overview)
* [How to use](documentation/how-to-use)
* [Microphone](documentation/microphone)
* [Visualizer](documentation/visualizer)
* [LightControler](documentation/light)
* [WebConfig](documentation/web)
* [Conclusion](documentation/conclusion)

# Tech Stack

<p align="center">
<img height="50" src="https://cdn.platformio.org/images/platformio-logo.17fdc3bc.png" />
<img height="50" src="https://upload.wikimedia.org/wikipedia/commons/5/5b/Arduino_Logo_Registered.svg" />
<img height="50" src="https://www.raspberrypi.com/app/uploads/2022/02/COLOUR-Raspberry-Pi-Symbol-Registered.png" />
<img height="50" src="https://upload.wikimedia.org/wikipedia/commons/1/18/ISO_C%2B%2B_Logo.svg" />
</p>

# Hardware platform

[Arduino Nano RP2040 Connect](https://store.arduino.cc/products/arduino-nano-rp2040-connect#looxReviews)

<br/><br/>
<div align=center padding=100>
<img src=/documentation/concept/Arduino-Nano-RP2040-Connect-with.jpg width=75% padding=100>
<br/><br/>
<br/><br/>

<table border="0" cellspacing="0"><colgroup width="148"></colgroup> <colgroup width="222"></colgroup> <colgroup width="305"></colgroup>
<tbody>
<tr>
<td rowspan="2" align="center" valign="middle" height="34"><span style="font-family: DejaVu Serif;">Board</span></td>
<td colspan="2" align="left" valign="middle"><span style="font-family: DejaVu Serif;">Nano RP2040 Connect</span></td>
</tr>
<tr>
<td colspan="2" align="left" valign="middle"><span style="font-family: DejaVu Serif;">SKU: ABX00052</span></td>
</tr>
<tr>
<td align="center" valign="middle" height="17"><span style="font-family: DejaVu Serif;">Microcontroller</span></td>
<td colspan="2" align="left" valign="middle"><span style="font-family: DejaVu Serif;">Raspberry Pi&reg; RP2040</span></td>
</tr>
<tr>
<td align="center" valign="middle" height="17"><span style="font-family: DejaVu Serif;">USB connector</span></td>
<td colspan="2" align="left" valign="middle"><span style="font-family: DejaVu Serif;">Micro USB</span></td>
</tr>
<tr>
<td rowspan="5" align="center" valign="middle" height="85"><span style="font-family: DejaVu Serif;">Pins</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Built-in LED pin</span></td>
<td align="left" valign="middle">13</td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Analog Input Pins</span></td>
<td align="left" valign="middle">20</td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Analog Input Pins</span></td>
<td align="left" valign="middle">8</td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">PWM pins</span></td>
<td align="left" valign="middle">20 (Except A6, A7)</td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">External interrupts</span></td>
<td align="left" valign="middle">20 (Except A6, A7)</td>
</tr>
<tr>
<td rowspan="3" align="center" valign="middle" height="51"><span style="font-family: DejaVu Serif;">Connectivity</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Wi-Fi</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Nina W102 uBlox module</span></td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Bluetooth&reg;</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Nina W102 uBlox module</span></td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Secure element</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">ATECC608A-MAHDA-T Crypto IC</span></td>
</tr>
<tr>
<td rowspan="2" align="center" valign="middle" height="34"><span style="font-family: DejaVu Serif;">Sensors</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">IMU</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">LSM6DSOXTR (6-axis)</span></td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Microphone</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">MP34DT05</span></td>
</tr>
<tr>
<td rowspan="3" align="center" valign="middle" height="51"><span style="font-family: DejaVu Serif;">Communication</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">UART</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Yes</span></td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">I2C</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Yes</span></td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">SPI</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Yes</span></td>
</tr>
<tr>
<td rowspan="3" align="center" valign="middle" height="51"><span style="font-family: DejaVu Serif;">Power</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Circuit operating voltage</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">3.3V</span></td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Input Voltage (VIN)</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">5-21V</span></td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">DC Current per I/O pin</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">4 mA</span></td>
</tr>
<tr>
<td align="center" valign="middle" height="17"><span style="font-family: DejaVu Serif;">Clock speed</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Processor</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">133 MHz</span></td>
</tr>
<tr>
<td rowspan="2" align="center" valign="middle" height="34"><span style="font-family: DejaVu Serif;">Memory</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">AT25SF128A-MHB-T&nbsp;</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">16MB Flash IC</span></td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Nina W102 uBlox module</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">448 KB ROM, 520KB SRAM, 16MB Flash</span></td>
</tr>
<tr>
<td rowspan="3" align="center" valign="middle" height="51"><span style="font-family: DejaVu Serif;">Dimensions</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Weight</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">6 g</span></td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Width</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">18 mm</span></td>
</tr>
<tr>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">Length</span></td>
<td align="left" valign="middle"><span style="font-family: DejaVu Serif;">45 mm</span></td>
</tr>
</tbody>
</table>
</div>

## Authors

- [Jakub Spólnik](https://github.com/lawos98)
