# The Feeling of Sound
Development of a device that amplifies the experience of listening to music using haptic technologies.

Un4seen BASS audio library - used for audio information

#Project Description
Project originally created using Visual Studio 2015 RC on Windows 8.1

The overall objective was to create a wristband containing small vibrating motors that would vibrate along with audio, thereby enhancing the listening experience.  Specific goals included to use a Bluetooth communication with the wristband, to write a computer program to control it, and to determine the most effective way to translate sound into a tactile experience.

FFT data from a song is used to determine the when the bass frequencies are highest. The intensity of the bass is sent serially to an arduino board to vibrate motors. This helps provide a more interactive and better experience.

To interface with the Arduino board, install the [Arduino USB Driver](http://www.arduino.cc/en/Main/Software). The code for the Arduino microcontroller is located in the [Arduino](https://github.com/ChrisTheEngineer/The_Feeling_of_Sound/tree/master/Arduino/ASCIIToArduino) section.

The program has a random set of quotes it iterates through. These do not correspond to the functionality of the program, they are simply just for fun. To add, edit, or remove quotes: go to the [Quotes](/Temp[0]/Temp[0]/Quotes.temp0) file and simply edit it in a text editor such as notepad. Each line corresponds to a seperate quote.

**Program:**

<img src="/Documents/Program.png?raw=true" alt="Program">

**Wristband:**

<img src="/Documents/Wristband.jpg?raw=true" alt="Wristband" width = 634 height=432>

Files containing a more in-depth description and details of the project are located in the [Documents](https://github.com/ChrisTheEngineer/The_Feeling_of_Sound/tree/master/Documents) section.
