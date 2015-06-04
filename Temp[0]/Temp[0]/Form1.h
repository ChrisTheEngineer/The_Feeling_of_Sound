#pragma once

namespace VC {

	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Runtime::InteropServices;


	/// <summary>
	/// Summary for Form1
	/// </summary>
	#include "stdafx.h"


	public ref class Form1 : public System::Windows::Forms::Form {
	public:
		Tempo audioSender;
		
		//static BASS_DEVICEINFO* recordDevices;


	public: 
		static char* file = "";
		static String^ defaultPath = "defaults.temp0";
	private: System::Windows::Forms::Panel^ xSpectrum;
	private: System::Windows::Forms::MenuStrip^  xMenu;

	private: System::Windows::Forms::ToolStripMenuItem^  xRealTimeDevice;
	private: System::Windows::Forms::ToolStripMenuItem^  xDevicePort;
	private: System::Windows::Forms::PictureBox^  xMenuBarImage;

	public: 
		static int marker = 0;
		static int specLine = 0;
	private: System::Windows::Forms::Timer^  xBackgroundTimer;




	private: System::Windows::Forms::ToolStripMenuItem^  xSettings;
	private: System::Windows::Forms::ToolStripMenuItem^  xRestoreDefaults;
	private: System::Windows::Forms::TrackBar^  xSeek;
	private: System::Windows::Forms::Label^  xSongLen;
	private: System::Windows::Forms::Label^  xSongPos;
	private: System::Windows::Forms::Label^  xSongInfo;
	private: System::Windows::Forms::Button^  xRndQuote;



	public: 
		static BYTE* specbuf;
		Form1(void){
			playFlag = true;
			pauseFlag = false;
			specbuf = getSpecbuf();
			for(int k = 0; k < 4096; k++) specbuf[k] = (BYTE)128;//zero out spectrum
			InitializeComponent();
			xBackgroundTimer->Start();
			readQuotes();
			getRndQuote();
			if(audioSender.sp->IsOpen)
				xConnect->Enabled = false;

			if (File::Exists(defaultPath))
			{
				StreamReader^ sr = File::OpenText( defaultPath );
				xVolumeBar->Value = (int)Convert::ToInt32(sr->ReadLine());
				xVolumeLabel->Text = "Volume: " + xVolumeBar->Value.ToString() + "%";
				xIntensity->Value = (int)Convert::ToInt32(sr->ReadLine());
				xIntensityLabel->Text = "Intensity: " + xIntensity->Value.ToString();
				file = (char*)(void*)Marshal::StringToHGlobalAnsi(sr->ReadLine());
				xSeek->Maximum = (int)Convert::ToInt32(sr->ReadLine());
				xSeek->Value = (int)Convert::ToInt32(sr->ReadLine());
				xSongInfo->Text = sr->ReadLine();
				
				
				if(xSeek->Value/44100/4 % 60 < 10)
					xSongPos->Text = (xSeek->Value/44100/4/60).ToString() + ":0" + (xSeek->Value/44100/4 % 60).ToString();
				else
					xSongPos->Text = (xSeek->Value/44100/4/60).ToString() + ":" + (xSeek->Value/44100/4 % 60).ToString();
				if(xSeek->Maximum/44100/4 % 60 < 10)
					xSongLen->Text = (xSeek->Maximum/44100/4/60).ToString() + ":0" + (xSeek->Maximum/44100/4 % 60).ToString();
				else
					xSongLen->Text = (xSeek->Maximum/44100/4/60).ToString() + ":" + (xSeek->Maximum/44100/4 % 60).ToString();
				

				if (sr)
					delete (IDisposable^)(sr);
			}

			this->FormClosing += gcnew FormClosingEventHandler(this, &Form1::Form1_Close);

		}
		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1(){
			audioSender.exitFlag = true;
			audioSender.myTimer->Enabled = false;
			playFlag = true;
			realtimeFlag = false;
			audioSender.myTimer->Stop();
			delete audioSender.myTimer;
			if (components){
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  xPlause;
	private: System::Windows::Forms::Timer^  xSpectrumTimer;
	private: System::Windows::Forms::PictureBox^ xSpectrumPicture;
	protected: 


	private: System::Windows::Forms::TrackBar^  xIntensity;
	private: System::Windows::Forms::Label^  xIntensityLabel;

	private: bool playFlag;
	private: bool pauseFlag;
	private: bool realtimeFlag;
	private: System::Windows::Forms::Label^  xDebug;

	private: System::Windows::Forms::TrackBar^  xVolumeBar;
	private: System::Windows::Forms::Label^  xVolumeLabel;
	private: System::Windows::Forms::Button^  xRealTime;

	private: System::Windows::Forms::Button^  xConnect;
	private: System::Windows::Forms::Button^  xOpenFile;
	private: System::Drawing::Point^ xTopPt;
	private: System::Drawing::Point^ xBottomPt;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void){
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->xPlause = (gcnew System::Windows::Forms::Button());
			this->xSpectrumTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->xIntensity = (gcnew System::Windows::Forms::TrackBar());
			this->xIntensityLabel = (gcnew System::Windows::Forms::Label());
			this->xDebug = (gcnew System::Windows::Forms::Label());
			this->xVolumeBar = (gcnew System::Windows::Forms::TrackBar());
			this->xVolumeLabel = (gcnew System::Windows::Forms::Label());
			this->xRealTime = (gcnew System::Windows::Forms::Button());
			this->xConnect = (gcnew System::Windows::Forms::Button());
			this->xOpenFile = (gcnew System::Windows::Forms::Button());
			this->xSpectrum = (gcnew System::Windows::Forms::Panel());
			this->xSpectrumPicture = (gcnew System::Windows::Forms::PictureBox());
			this->xMenu = (gcnew System::Windows::Forms::MenuStrip());
			this->xRealTimeDevice = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->xDevicePort = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->xSettings = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->xRestoreDefaults = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->xMenuBarImage = (gcnew System::Windows::Forms::PictureBox());
			this->xBackgroundTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->xSeek = (gcnew System::Windows::Forms::TrackBar());
			this->xSongLen = (gcnew System::Windows::Forms::Label());
			this->xSongPos = (gcnew System::Windows::Forms::Label());
			this->xSongInfo = (gcnew System::Windows::Forms::Label());
			this->xRndQuote = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->xIntensity))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->xVolumeBar))->BeginInit();
			this->xSpectrum->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->xSpectrumPicture))->BeginInit();
			this->xMenu->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->xMenuBarImage))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->xSeek))->BeginInit();
			this->SuspendLayout();
			// 
			// xPlause
			// 
			this->xPlause->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->xPlause->Location = System::Drawing::Point(203, 228);
			this->xPlause->Name = L"xPlause";
			this->xPlause->Size = System::Drawing::Size(144, 45);
			this->xPlause->TabIndex = 0;
			this->xPlause->Text = L"Play";
			this->xPlause->UseVisualStyleBackColor = false;
			this->xPlause->Click += gcnew System::EventHandler(this, &Form1::xPlause_Click);
			// 
			// xSpectrumTimer
			// 
			this->xSpectrumTimer->Interval = 1;
			this->xSpectrumTimer->Tick += gcnew System::EventHandler(this, &Form1::xSpectrumTimer_Tick);
			// 
			// xIntensity
			// 
			this->xIntensity->Location = System::Drawing::Point(203, 128);
			this->xIntensity->Maximum = 100;
			this->xIntensity->Name = L"xIntensity";
			this->xIntensity->Size = System::Drawing::Size(336, 45);
			this->xIntensity->TabIndex = 1;
			this->xIntensity->TickFrequency = 10;
			this->xIntensity->Value = 18;
			this->xIntensity->Scroll += gcnew System::EventHandler(this, &Form1::xIntensity_Scroll);
			// 
			// xIntensityLabel
			// 
			this->xIntensityLabel->AutoSize = true;
			this->xIntensityLabel->Location = System::Drawing::Point(211, 112);
			this->xIntensityLabel->Name = L"xIntensityLabel";
			this->xIntensityLabel->Size = System::Drawing::Size(64, 13);
			this->xIntensityLabel->TabIndex = 3;
			this->xIntensityLabel->Text = L"Intensity: 18";
			// 
			// xDebug
			// 
			this->xDebug->AutoSize = true;
			this->xDebug->Location = System::Drawing::Point(258, 8);
			this->xDebug->Name = L"xDebug";
			this->xDebug->Size = System::Drawing::Size(0, 13);
			this->xDebug->TabIndex = 4;
			// 
			// xVolumeBar
			// 
			this->xVolumeBar->Location = System::Drawing::Point(203, 182);
			this->xVolumeBar->Maximum = 100;
			this->xVolumeBar->Name = L"xVolumeBar";
			this->xVolumeBar->Size = System::Drawing::Size(336, 45);
			this->xVolumeBar->TabIndex = 5;
			this->xVolumeBar->TickFrequency = 10;
			this->xVolumeBar->Value = 70;
			this->xVolumeBar->Scroll += gcnew System::EventHandler(this, &Form1::xVolumeBar_Scroll);
			// 
			// xVolumeLabel
			// 
			this->xVolumeLabel->AutoSize = true;
			this->xVolumeLabel->Location = System::Drawing::Point(211, 166);
			this->xVolumeLabel->Name = L"xVolumeLabel";
			this->xVolumeLabel->Size = System::Drawing::Size(68, 13);
			this->xVolumeLabel->TabIndex = 7;
			this->xVolumeLabel->Text = L"Volume: 70%";
			// 
			// xRealTime
			// 
			this->xRealTime->Location = System::Drawing::Point(392, 228);
			this->xRealTime->Name = L"xRealTime";
			this->xRealTime->Size = System::Drawing::Size(144, 45);
			this->xRealTime->TabIndex = 9;
			this->xRealTime->Text = L"Real Time";
			this->xRealTime->UseVisualStyleBackColor = false;
			this->xRealTime->Click += gcnew System::EventHandler(this, &Form1::xRealTime_Click);
			// 
			// xConnect
			// 
			this->xConnect->BackColor = System::Drawing::SystemColors::Control;
			this->xConnect->Location = System::Drawing::Point(600, 182);
			this->xConnect->Name = L"xConnect";
			this->xConnect->Size = System::Drawing::Size(76, 25);
			this->xConnect->TabIndex = 11;
			this->xConnect->Text = L"Connect";
			this->xConnect->UseVisualStyleBackColor = false;
			this->xConnect->Click += gcnew System::EventHandler(this, &Form1::xConnect_Click);
			// 
			// xOpenFile
			// 
			this->xOpenFile->Location = System::Drawing::Point(600, 128);
			this->xOpenFile->Name = L"xOpenFile";
			this->xOpenFile->Size = System::Drawing::Size(76, 25);
			this->xOpenFile->TabIndex = 12;
			this->xOpenFile->Text = L"Open File";
			this->xOpenFile->UseVisualStyleBackColor = false;
			this->xOpenFile->Click += gcnew System::EventHandler(this, &Form1::xOpenFile_Click);
			// 
			// xSpectrum
			// 
			this->xSpectrum->Controls->Add(this->xSpectrumPicture);
			this->xSpectrum->Location = System::Drawing::Point(62, 280);
			this->xSpectrum->Name = L"xSpectrum";
			this->xSpectrum->Size = System::Drawing::Size(614, 191);
			this->xSpectrum->TabIndex = 13;
			this->xSpectrum->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::xSpectrum_Paint);
			// 
			// xSpectrumPicture
			// 
			this->xSpectrumPicture->BackColor = System::Drawing::Color::Black;
			this->xSpectrumPicture->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->xSpectrumPicture->Dock = System::Windows::Forms::DockStyle::Fill;
			this->xSpectrumPicture->Location = System::Drawing::Point(0, 0);
			this->xSpectrumPicture->Name = L"xSpectrumPicture";
			this->xSpectrumPicture->Size = System::Drawing::Size(614, 191);
			this->xSpectrumPicture->TabIndex = 0;
			this->xSpectrumPicture->TabStop = false;
			this->xSpectrumPicture->Click += gcnew System::EventHandler(this, &Form1::xSpectrumPicture_Click);
			this->xSpectrumPicture->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::xSpectrumPicture_Paint);
			// 
			// xMenu
			// 
			this->xMenu->AllowDrop = true;
			this->xMenu->BackColor = System::Drawing::SystemColors::MenuBar;
			this->xMenu->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->xMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->xRealTimeDevice, this->xDevicePort, 
				this->xSettings});
			this->xMenu->Location = System::Drawing::Point(0, 0);
			this->xMenu->Name = L"xMenu";
			this->xMenu->Size = System::Drawing::Size(752, 24);
			this->xMenu->TabIndex = 14;
			this->xMenu->Text = L"Real Time Device";
			// 
			// xRealTimeDevice
			// 
			this->xRealTimeDevice->Name = L"xRealTimeDevice";
			this->xRealTimeDevice->Size = System::Drawing::Size(109, 20);
			this->xRealTimeDevice->Text = L"Real Time Device";
			this->xRealTimeDevice->DropDownOpening += gcnew System::EventHandler(this, &Form1::xRealTimeDevice_Click);
			// 
			// xDevicePort
			// 
			this->xDevicePort->Name = L"xDevicePort";
			this->xDevicePort->Size = System::Drawing::Size(79, 20);
			this->xDevicePort->Text = L"Device Port";
			this->xDevicePort->DropDownOpening += gcnew System::EventHandler(this, &Form1::xDevicePort_Click);
			// 
			// xSettings
			// 
			this->xSettings->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->xRestoreDefaults});
			this->xSettings->Name = L"xSettings";
			this->xSettings->Size = System::Drawing::Size(61, 20);
			this->xSettings->Text = L"Settings";
			// 
			// xRestoreDefaults
			// 
			this->xRestoreDefaults->Name = L"xRestoreDefaults";
			this->xRestoreDefaults->Size = System::Drawing::Size(159, 22);
			this->xRestoreDefaults->Text = L"Restore Defaults";
			this->xRestoreDefaults->Click += gcnew System::EventHandler(this, &Form1::xRestoreDefaults_Click);
			// 
			// xMenuBarImage
			// 
			this->xMenuBarImage->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->xMenuBarImage->Location = System::Drawing::Point(0, 24);
			this->xMenuBarImage->Name = L"xMenuBarImage";
			this->xMenuBarImage->Size = System::Drawing::Size(748, 1);
			this->xMenuBarImage->TabIndex = 15;
			this->xMenuBarImage->TabStop = false;
			// 
			// xBackgroundTimer
			// 
			this->xBackgroundTimer->Tick += gcnew System::EventHandler(this, &Form1::xBackgroundTimer_Tick);
			// 
			// xSeek
			// 
			this->xSeek->BackColor = System::Drawing::Color::WhiteSmoke;
			this->xSeek->Location = System::Drawing::Point(63, 64);
			this->xSeek->Maximum = 0;
			this->xSeek->Name = L"xSeek";
			this->xSeek->Size = System::Drawing::Size(613, 45);
			this->xSeek->TabIndex = 16;
			this->xSeek->TickStyle = System::Windows::Forms::TickStyle::None;
			this->xSeek->Scroll += gcnew System::EventHandler(this, &Form1::xSeek_Scroll);
			// 
			// xSongLen
			// 
			this->xSongLen->AutoSize = true;
			this->xSongLen->Location = System::Drawing::Point(682, 64);
			this->xSongLen->Name = L"xSongLen";
			this->xSongLen->Size = System::Drawing::Size(28, 13);
			this->xSongLen->TabIndex = 17;
			this->xSongLen->Text = L"0:00";
			// 
			// xSongPos
			// 
			this->xSongPos->AutoSize = true;
			this->xSongPos->Location = System::Drawing::Point(29, 64);
			this->xSongPos->Name = L"xSongPos";
			this->xSongPos->Size = System::Drawing::Size(28, 13);
			this->xSongPos->TabIndex = 18;
			this->xSongPos->Text = L"0:00";
			// 
			// xSongInfo
			// 
			this->xSongInfo->AutoSize = true;
			this->xSongInfo->Location = System::Drawing::Point(62, 45);
			this->xSongInfo->Name = L"xSongInfo";
			this->xSongInfo->Size = System::Drawing::Size(0, 13);
			this->xSongInfo->TabIndex = 19;
			// 
			// xRndQuote
			// 
			this->xRndQuote->Location = System::Drawing::Point(685, 0);
			this->xRndQuote->Name = L"xRndQuote";
			this->xRndQuote->Size = System::Drawing::Size(62, 23);
			this->xRndQuote->TabIndex = 20;
			this->xRndQuote->Text = L"Random";
			this->xRndQuote->UseVisualStyleBackColor = true;
			this->xRndQuote->Click += gcnew System::EventHandler(this, &Form1::xRndQuote_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(752, 486);
			this->Controls->Add(this->xRndQuote);
			this->Controls->Add(this->xSongInfo);
			this->Controls->Add(this->xSongPos);
			this->Controls->Add(this->xSongLen);
			this->Controls->Add(this->xSeek);
			this->Controls->Add(this->xMenuBarImage);
			this->Controls->Add(this->xSpectrum);
			this->Controls->Add(this->xOpenFile);
			this->Controls->Add(this->xConnect);
			this->Controls->Add(this->xRealTime);
			this->Controls->Add(this->xVolumeLabel);
			this->Controls->Add(this->xVolumeBar);
			this->Controls->Add(this->xDebug);
			this->Controls->Add(this->xIntensityLabel);
			this->Controls->Add(this->xIntensity);
			this->Controls->Add(this->xPlause);
			this->Controls->Add(this->xMenu);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->xMenu;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(758, 515);
			this->MinimumSize = System::Drawing::Size(758, 515);
			this->Name = L"Form1";
			this->Text = L"Temp[0]";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->xIntensity))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->xVolumeBar))->EndInit();
			this->xSpectrum->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->xSpectrumPicture))->EndInit();
			this->xMenu->ResumeLayout(false);
			this->xMenu->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->xMenuBarImage))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->xSeek))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void xPlause_Click(System::Object^  sender, System::EventArgs^  e) {

				 if (playFlag) {
					if (!pauseFlag){
						BASS_Init(-1,44100,0,NULL,NULL); // initialize BASS

						if (!PlayFile(file)){ // start a file playing						
							BASS_Free();
							xOpenFile_Click(this, gcnew EventArgs());
						}
					
						if(!xSpectrumTimer->Enabled)xSpectrumTimer->Start();
						xSongInfo->Text = gcnew String(songName());
						pauseFlag = true;
						setVolume(70);
						int songLen = getSongLength();
						xSeek->Maximum = songLen;
						setSongPos(xSeek->Value);
						if(getSongLength()/44100/4 % 60 < 10)
							xSongLen->Text = (getSongLength()/44100/4/60).ToString() + ":0" + (getSongLength()/44100/4 % 60).ToString();
						else
							xSongLen->Text = (getSongLength()/44100/4/60).ToString() + ":" + (getSongLength()/44100/4 % 60).ToString();

					}
					else{
						ResumeFile();
						xSpectrumTimer->Enabled = true;
					}
					playFlag = false;
					xPlause->Text = "Pause";
					
				 }
				 else
				 {
					 xPlause->Text = "Play";
					 playFlag = true;
					 xSpectrumTimer->Enabled = false;
					 PauseFile();
					 try{
						audioSender.sp->Write("\0");
					 }catch(System::InvalidOperationException^){}
					
					 
				 }
			 }
private: System::Void xSpectrumTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
				//xDebug->Text = (1.0/ getSysVolume()).ToString();
				/*if (realtimeFlag)
					setMult(72.0 / getSysVolume());
				else
					setMult(1.0);*/
				marker++;
				xSpectrumPicture->Invalidate(System::Drawing::Rectangle(marker-1, 0, 2, xSpectrumPicture->Height));
							
				audioSender.UpdateSpectrum();	
				if(!realtimeFlag && getSongPos() <= xSeek->Maximum){ 
					xSeek->Value = getSongPos();			
					if(xSeek->Value/44100/4 % 60 < 10)
						xSongPos->Text = (xSeek->Value/44100/4/60).ToString() + ":0" + (xSeek->Value/44100/4 % 60).ToString();
					else
						xSongPos->Text = (xSeek->Value/44100/4/60).ToString() + ":" + (xSeek->Value/44100/4 % 60).ToString();
				}
		 }

private: System::Void xBackgroundTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
			    if(!audioSender.sp->IsOpen && !xConnect->Enabled){//enable connect button if connection is lost
					xConnect->ForeColor = Color::DarkRed;
					xConnect->Enabled = true;
				}
				if(!filePlaying() && !playFlag) {
					xPlause->Text = "Play";
					playFlag = true;
					marker = 0;
					xSpectrumPicture->Refresh();
					xSpectrumTimer->Enabled = false;
					xSeek->Value = 0;
					xSongPos->Text = "0:00";
					
				}
				//xDebug->Text = gcnew String(_ultoa(getRecordDevices()[getDeviceNum()].flags, new char, 32));
				if(getRecordDevices()[getDeviceNum()].flags == 0 || getRecordDevices()[getDeviceNum()].flags == 4){
					//disable realtime, change color to red, only enable when a new record device is selected or old one is re-enabled
					//((ToolStripMenuItem^)xRealTimeDevice->DropDownItems[getDeviceNum()])->Checked = false; //removes the check mark
							
					if(xRealTime->Enabled){ 
						xSpectrumTimer->Enabled = false;
						xSpectrumPicture->Refresh();
						xRealTime_Click(this, gcnew EventArgs());			
					}
					xRealTime->Enabled = false;
					xRealTimeDevice->ForeColor = Color::DarkRed;
				}
				else if(xRealTimeDevice->ForeColor == Color::DarkRed){//reverts back to a normal state if everything is fine
					xRealTime->Enabled = true;
					xRealTimeDevice->ForeColor = Color::Black;
				}
		 }

private: System::Void xIntensity_Scroll(System::Object^  sender, System::EventArgs^  e) {
				 audioSender.intens = xIntensity->Value;
				 xIntensityLabel->Text = "Intensity: " + audioSender.intens.ToString();
		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
		 
private: System::Void xVolumeBar_Scroll(System::Object^  sender, System::EventArgs^  e) {
				setVolume(xVolumeBar->Value);
				xVolumeLabel->Text = "Volume: " + xVolumeBar->Value.ToString() + "%";
		 }
private: System::Void xRealTime_Click(System::Object^  sender, System::EventArgs^  e) {
			 marker = 0;
			 xSpectrumPicture->Refresh();
			 xSeek->Enabled = !xSeek->Enabled;
			 xSongLen->Enabled = !xSongLen->Enabled;
			 xSongPos->Enabled = !xSongPos->Enabled;
			 xSongInfo->Enabled = !xSongInfo->Enabled;
			 xVolumeBar->Enabled = !xVolumeBar->Enabled;
			 xVolumeLabel->Enabled = !xVolumeLabel->Enabled;
			 xPlause->Enabled = !xPlause->Enabled;
			 xOpenFile->Enabled = !xOpenFile->Enabled;
			 if(realtimeFlag){
				 xSpectrumTimer->Enabled = false;
				 EndRealTime();
			 }
			 else {
				 if(pauseFlag &&!playFlag)xPlause_Click(this, gcnew EventArgs());
				 PauseFile();
				 PlayRealtime(false);
				 xSpectrumTimer->Enabled = true;
			 }
			 realtimeFlag = !realtimeFlag;
		 }

private: System::Void xConnect_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(audioSender.connect())
				 xConnect->Enabled = false;
			 else 
				 xConnect->ForeColor = Color::DarkRed;
		 }	 
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		 }
private: System::Void xOpenFile_Click(System::Object^  sender, System::EventArgs^  e) {
			  Stream^ myStream;
			  OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

			  //openFileDialog1->InitialDirectory = "c:\\";
			  openFileDialog1->Filter = "All files|*.*|Audio Files|*.mo3;*.xm;*.mod;*.s3m;*.it;*.mtm;*.umx;*.mp3;*.mp2;*.m4a;*.mp1;*.ogg;*.wav;*.aif";
			  openFileDialog1->FilterIndex = 2;
			  openFileDialog1->RestoreDirectory = true;

			  if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK ){
				 if ( (myStream = openFileDialog1->OpenFile()) != nullptr ){

					file = (char*)(void*)Marshal::StringToHGlobalAnsi(openFileDialog1->FileName->Replace('\\','/'));//replaces '\' with '/' to be read correctly
					//xDebug->Text = gcnew String(file); //prints file location into debug
					marker = 0;
					xSpectrumPicture->Refresh();
					xSeek->Value = 0;

					if(pauseFlag && !playFlag){//when the music is currently playing and not trying to 'resume' when the music is paused
						xPlause_Click(this, gcnew EventArgs());//pause music
						BASS_Free();
						pauseFlag = false;
					}
					else{//when the music was pasued, will open up the new file to play instantly
						BASS_Free();
						pauseFlag = false;
					}
					xPlause_Click(this, gcnew EventArgs());//play music
					myStream->Close();
				 }
			  }
		 }
private: System::Void xSpectrum_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
private: System::Void xSpectrumPicture_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			Graphics^ g = e->Graphics;
			if(marker == xSpectrumPicture->Width)marker = 0;
			specLine = marker - 1;
			if(specLine == -1) specLine = xSpectrumPicture->Width - 1;
			for(int y = 0; y < xSpectrumPicture->Height; y++)
			{
				if ((int)specbuf[xSpectrumPicture->Height-y-1] < 153)
					g->DrawRectangle(gcnew Pen(System::Drawing::Color::FromArgb(0, 0, (((int)specbuf[xSpectrumPicture->Height-y-1]-127)*10))),specLine, y, 1, 1);
				else if ((int)specbuf[xSpectrumPicture->Height-y-1] < 179)
					g->DrawRectangle(gcnew Pen(System::Drawing::Color::FromArgb(((int)specbuf[xSpectrumPicture->Height-y-1]-153)*5, 0, 255)),specLine, y, 1, 1);
				else if ((int)specbuf[xSpectrumPicture->Height-y-1] < 205)
					g->DrawRectangle(gcnew Pen(System::Drawing::Color::FromArgb(((int)specbuf[xSpectrumPicture->Height-y-1]-179)*5+128, 0, (204-(int)specbuf[xSpectrumPicture->Height-y-1])*10)),specLine, y, 1, 1);
				else if ((int)specbuf[xSpectrumPicture->Height-y-1] < 230)
					g->DrawRectangle(gcnew Pen(System::Drawing::Color::FromArgb(255, 0, ((int)specbuf[xSpectrumPicture->Height-y-1]-204)*5)),specLine, y, 1, 1);
				else
					g->DrawRectangle(gcnew Pen(System::Drawing::Color::FromArgb(255, (((int)specbuf[xSpectrumPicture->Height-y-1]-230)*5)+128, 0)), specLine, y, 1, 1);
			}
			g->DrawLine(System::Drawing::Pens::WhiteSmoke, marker, xSpectrumPicture->Top, marker, xSpectrumPicture->Bottom);
}
private: System::Void xSpectrumPicture_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: void setRTDevice(System::Object^  sender, System::EventArgs^  e){
			 ToolStripMenuItem^ temp = (System::Windows::Forms::ToolStripMenuItem^)sender;
			 setDeviceNum(int::Parse(temp->Name));
			 if(realtimeFlag){
				 BASS_RecordFree();
				 marker = 0;
				 xSpectrumPicture->Refresh();
				 PlayRealtime(true);
			 }
		 }
private: System::Void xRealTimeDevice_Click(System::Object^  sender, System::EventArgs^  e) {
				std::vector<BASS_DEVICEINFO> recordDevices = getRecordDevices();
				xRealTimeDevice->DropDownItems->Clear();

				for(int k = 0; k < getNumRecDev(); k++){
					ToolStripMenuItem^ device = gcnew ToolStripMenuItem();
					device->Name =  k.ToString();
					device->Tag = k;
					device->Text = gcnew String(recordDevices[k].name);//"Visible Menu Text Here";    
					device->Click += gcnew EventHandler(this,&Form1::setRTDevice);
					if(k == getDeviceNum())device->Checked = true;
					if(recordDevices[k].flags != BASS_DEVICE_ENABLED && recordDevices[k].flags != 3) device->Enabled = false;											 
					xRealTimeDevice->DropDownItems->Add(device);
				}
				if(getNumRecDev() == 0){
				 ToolStripMenuItem^ device = gcnew ToolStripMenuItem();
				 device->Text = "No Avaliable Devices";
				 device->Enabled = false;
				 xDevicePort->DropDownItems->Add(device);
			 }
		 }
private: void setPort(System::Object^  sender, System::EventArgs^  e){
			 ToolStripMenuItem^ temp = (System::Windows::Forms::ToolStripMenuItem^)sender;
			 if(audioSender.setPort(temp->Text))
				 xConnect->Enabled = false;
		 }
private: System::Void xDevicePort_Click(System::Object^  sender, System::EventArgs^  e) {
			 xDevicePort->DropDownItems->Clear();
			 array<String^>^ portNames = audioSender.sp->GetPortNames();
			 
			 for(int k = 0; k < portNames->Length; k++){
				 ToolStripMenuItem^ port = gcnew ToolStripMenuItem();
				 port->Name = k.ToString();
				 port->Tag = k;
				 port->Text = portNames[k];
				 port->Click += gcnew EventHandler(this,&Form1::setPort);
				 if(portNames[k] == audioSender.sp->PortName) port->Checked = true;
				 xDevicePort->DropDownItems->Add(port);
			 }
			 if(portNames->Length == 0){
				 ToolStripMenuItem^ port = gcnew ToolStripMenuItem();
				 port->Text = "No Avaliable Ports";
				 port->Enabled = false;
				 xDevicePort->DropDownItems->Add(port);
			 }
		 }

private: System::Void Form1_Close(System::Object^ form, System::Windows::Forms::FormClosingEventArgs^ e) {
			 File::Delete( defaultPath );
			 StreamWriter^ sw = File::CreateText( defaultPath );
			 sw->WriteLine(xVolumeBar->Value.ToString());//Volume Level
			 sw->WriteLine(xIntensity->Value.ToString());//Intensity Level
			 sw->WriteLine(gcnew String(file));//Current File
			 sw->WriteLine(xSeek->Maximum.ToString());//Current Song Length
			 sw->WriteLine(xSeek->Value.ToString());//Current Song Position
			 sw->WriteLine(xSongInfo->Text);//Current Song Name

			 if (sw)
                  delete (IDisposable^)(sw);
		 }
private: System::Void xSeek_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 setSongPos(xSeek->Value);
			 if(xSeek->Value/44100/4 % 60 < 10)
				xSongPos->Text = (xSeek->Value/44100/4/60).ToString() + ":0" + (xSeek->Value/44100/4 % 60).ToString();
			 else
				xSongPos->Text = (xSeek->Value/44100/4/60).ToString() + ":" + (xSeek->Value/44100/4 % 60).ToString();
		 }
private: System::Void xRestoreDefaults_Click(System::Object^  sender, System::EventArgs^  e) {
			 xIntensity->Value = 18;
			 audioSender.intens = xIntensity->Value;
			 xIntensityLabel->Text = "Intensity: " + xIntensity->Value.ToString();
			 xVolumeBar->Value = 70;
			 setVolume(xVolumeBar->Value);
			 xVolumeLabel->Text = "Volume: " + xVolumeBar->Value.ToString() + "%";
		 }
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: void readQuotes(){
			StreamReader^ sr = File::OpenText("Quotes.temp0");
			std::vector<char*> quotes;

			while(!sr->EndOfStream){
				try{
					quotes.push_back((char*)(void*)Marshal::StringToHGlobalAnsi(sr->ReadLine()));
				}
				catch(System::IO::IOException^ e){
					break;
				}
			}
			setQuotes(quotes);	
		 }
private: void getRndQuote(){
			std::vector<char*> quotes =  getQuotes();
			System::Random^ rnd = gcnew Random();

			if(quotes.size() == 0) this->Text = "Temp[0]";
			else this->Text = "Temp[0] - " + gcnew String(quotes[rnd->Next(0, quotes.size())]);

		 }

private: System::Void xRndQuote_Click(System::Object^  sender, System::EventArgs^  e) {
			 getRndQuote();
		 }
};
}