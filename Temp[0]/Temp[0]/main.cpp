#include <iostream>
//#include "stdio.h"
#include "bass.h"
#include "SerialClass.h"
using namespace std;

DWORD chan, timer = 0;
Serial* s = new Serial("COM3");
char *file = "C:/Users/Christian/Music/Hans Zimmer/Inception/Mombassa.mp3";

BOOL PlayFile(){
	if (!(chan=BASS_StreamCreateFile(FALSE,file,0,0,BASS_SAMPLE_LOOP))
		&& !(chan=BASS_MusicLoad(FALSE,file,0,0,BASS_MUSIC_RAMP|BASS_SAMPLE_LOOP,1))) {
		cout << "Can't play file" << endl;
		Sleep(1000);
		return FALSE; // Can't load the file
	}

	BASS_ChannelPlay(chan,FALSE);
    
	return TRUE;
}
void  UpdateSpectrum(){
	int x,y;
		
		float fft[1024];
		const int numBins = 3;
		int bass[numBins];
		BASS_ChannelGetData(chan,fft,BASS_DATA_FFT2048); // get the FFT data
			for (x=0;x<1024;x++) {
				y = (fft[x+1])*3*127;
				if (y>127) y=127; // cap it
				if (x < numBins)
					bass[x] = y;
			}
			
			char temp[2];
			temp[0]=((bass[0]+bass[1]+bass[2])/3);

			temp[1]='\0';
			s->WriteData(temp, 1);
}

int main(){
	// initialize BASS
	if (!BASS_Init(-1,44100,0,NULL,NULL)) {
		cout << "cannot init device";
		return -1;
	}
	if (!PlayFile()) { // start a file playing
		BASS_Free();
		return -1;
	}
	while(1){
		UpdateSpectrum();
		Sleep(25);
	}

	int a;
	cin >> a;
	return 0;
}
