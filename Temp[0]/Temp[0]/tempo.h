	#include <vector>

	using namespace System;	
	using namespace System::IO::Ports;
	using namespace System::Windows::Forms;
	//using namespace InTheHand::Net::Bluetooth;
	
	BOOL PlayFile(char* file);
	BOOL PauseFile();
	BOOL ResumeFile();
	BOOL filePlaying();
	BOOL setVolume(int value);
	const char* songName();
	BOOL PlayRealtime(bool isReal);
	BOOL EndRealTime();
	float getSysVolume();
	int getLuigiVal();
	void setMult(float t);
	BYTE* getSpecbuf();
	std::vector<BASS_DEVICEINFO>  getRecordDevices();
	int getNumRecDev();
	void setDeviceNum(int num);
	int getDeviceNum();
	int getSongLength();
	int getSongPos();
	void setSongPos(int pos);
	char* getName();
	void setQuotes(std::vector<char*> temp);
	std::vector<char*> getQuotes();

public ref class Tempo {
public:
	static System::Windows::Forms::Timer^ myTimer = gcnew System::Windows::Forms::Timer;
	static int alarmCounter = 1;
	static bool exitFlag = false;
	SerialPort^ sp;
	static int intens = 18;
	bool connect();
	bool setPort(String^);

	void UpdateSpectrum();

	Tempo(){
		myTimer->Interval = 25;

		array<String^>^ portNames = sp->GetPortNames();
		/*if(portNames->Length == 0)*/ sp = gcnew SerialPort();
		//else sp = gcnew SerialPort(portNames[0]);

		try {sp->Open();
		/*sp->WriteTimeout = 50;*/}
		catch(System::IO::IOException^) {}
	}
	~Tempo(){
		if(sp->IsOpen){
			sp->Write("\0");
			sp->Close();
		}
	}
	static void TimerEventProcessor( Object^ /*myObject*/, EventArgs^ /*myEventArgs*/ ){
		myTimer->Stop();
		alarmCounter += 1;
		myTimer->Enabled = true;

	}
};

class SongInfo {
public:
	char* name;
	char* artist;
	char* album;
	SongInfo(){
		name = artist = album = "";
	}
	~SongInfo(){}
};