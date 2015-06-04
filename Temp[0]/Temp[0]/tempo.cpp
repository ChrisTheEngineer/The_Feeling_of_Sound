#include "stdafx.h"

	int realTimeMult = 1;
	int luigiVal = 0;
	HSTREAM chan = 0; //channel from file
	DWORD temp_chan = 0; //channel from real time
	BYTE* specbuf = new BYTE[4096];
	std::vector<BASS_DEVICEINFO> recordDevices;
	std::vector<char*> quotes;
	int deviceNum = 0;
	bool isOpenBluetooth = true;

	std::vector<char*> getQuotes(){
		return quotes;
	}
	void setQuotes(std::vector<char*> temp){
		quotes = temp;
	}
	void setSongPos(int pos){
		BASS_ChannelSetPosition(chan, (QWORD)pos, BASS_POS_BYTE);
	}
	int getSongLength(){
		return std::ceil((double)BASS_ChannelGetLength(chan, BASS_POS_BYTE));///44100.0/4.0);
	}
	int getSongPos(){
		return std::ceil((double)BASS_ChannelGetPosition(chan,BASS_POS_BYTE));///44100.0/4.0);
	}
	void setDeviceNum(int num){
		deviceNum = num;
	}
	int getDeviceNum(){
		return deviceNum;
	}
	std::vector<BASS_DEVICEINFO> getRecordDevices(){
		BASS_DEVICEINFO t;
		DWORD dev = 0;
		recordDevices.clear();
		while (BASS_RecordGetDeviceInfo(dev, &t)){
			recordDevices.push_back(t);
			dev++;
		}

		return recordDevices;
	}

	int getNumRecDev(){
		return recordDevices.size();
	}

	int getLuigiVal(){
		return luigiVal;
	}

	BYTE* getSpecbuf(){
		return specbuf;
	}

	void setMult(float t){
		realTimeMult = t;
	}

	BOOL EndRealTime(){
		BASS_RecordFree();
		chan = temp_chan;
		return true;
	}

	BOOL PlayRealtime(bool deviceChanged){
		if(!deviceChanged)
			temp_chan = chan;
		BASS_RecordInit(deviceNum);
		chan = BASS_RecordStart(44100, 2, BASS_SAMPLE_FLOAT, NULL, NULL);
		return true;
	}

	const char* songName(){
		if (BASS_ChannelGetTags(chan, BASS_TAG_ICY)){
			return BASS_ChannelGetTags(chan, BASS_TAG_ICY);
		}
		else if (BASS_ChannelGetTags(chan, BASS_TAG_META)){
			return BASS_ChannelGetTags(chan, BASS_TAG_META);
		}
		else if (BASS_ChannelGetTags(chan, BASS_TAG_MUSIC_NAME)){
			return BASS_ChannelGetTags(chan, BASS_TAG_MUSIC_NAME);
		}
		else if (BASS_ChannelGetTags(chan, BASS_TAG_OGG)){
			return BASS_ChannelGetTags(chan, BASS_TAG_OGG);
		}
		else if (BASS_ChannelGetTags(chan, BASS_TAG_ID3)){
			return BASS_ChannelGetTags(chan, BASS_TAG_ID3) + 3;	// Skip "TAG"
		}
		else if (BASS_ChannelGetTags(chan, BASS_TAG_ID3V2)){
			return BASS_ChannelGetTags(chan, BASS_TAG_ID3V2);
		}
		else if(BASS_ChannelGetTags(chan, BASS_TAG_MP4)){
			return BASS_ChannelGetTags(chan, BASS_TAG_MP4) + 6; // Skip "Title="
		}
		else
			return "Nothing";
	}

	float getSysVolume(){
		return BASS_GetVolume();
	}

	BOOL setVolume(int value){
		return BASS_ChannelSetAttribute(chan, BASS_ATTRIB_VOL, (float)value/100.0);
	}

	BOOL filePlaying(){
		return BASS_ChannelIsActive(chan) == BASS_ACTIVE_PLAYING;//want it to be stopped?
	}

	BOOL ResumeFile(){
		return BASS_ChannelPlay(chan,false);
	}

	BOOL PlayFile(char* file){
		if (!(chan=BASS_StreamCreateFile(FALSE,file,0,0,NULL))
		&& !(chan=BASS_MusicLoad(FALSE,file,0,0,BASS_MUSIC_RAMP,1))) {
			return FALSE; // Can't load the file
		}

		BASS_ChannelPlay(chan, false);		
		return TRUE;
	}

	BOOL PauseFile(){
		
		return BASS_ChannelPause(chan);
	}

	bool Tempo::connect(){
		try {
			sp->Open();
		}
		catch(System::IO::IOException^) {
			return false;
		}
		return true;
	}
	bool Tempo::setPort(String^ portName){
		sp = gcnew SerialPort(portName);
		try {
			sp->Open();
		}
		catch(System::IO::IOException^) {
			return false;
		}
		return true;

	}
	void Tempo::UpdateSpectrum(){
	int x,y;
		
		float fft[2048];
		const int numBins = 12;
		int bass[numBins];
		//realTimeMult = 1/getSysVolume();
		BASS_ChannelGetData(chan,fft,BASS_DATA_FFT4096); // get the FFT data
			for (x=0;x<2048;x++) {
				y = (fft[x+1])*intens*127*realTimeMult;
				if (y>127) y=127; // cap it
				specbuf[x]=(BYTE)(128+y); // plot it
				if (x < numBins)
					bass[x] = y;
			}
			
			char temp[2];
			int bassAvg = 0;
			for(int k = 0; k < numBins; k++) bassAvg+= bass[k];
			bassAvg /= numBins;
			luigiVal = bassAvg;
			temp[0]= bassAvg;
			temp[1]='\0';
			String^ tempStr = gcnew String(temp);
			if(sp->IsOpen && isOpenBluetooth){
				try{
					if(bassAvg == 0 || BASS_ChannelIsActive(chan) != BASS_ACTIVE_PLAYING)
						sp->Write("\0");
					else
						sp->Write(tempStr);
					}
				catch(System::IO::IOException^ e){isOpenBluetooth = false;}
			}			
}