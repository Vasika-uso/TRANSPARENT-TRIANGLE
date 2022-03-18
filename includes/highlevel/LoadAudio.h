#pragma once
// using soloud library
/*
Welcome
https://sol.gfxile.net/soloud/index.html
FAQ
https://sol.gfxile.net/soloud/faq.html
Github
https://github.com/jarikomppa/soloud
*/

//this project is using a modified version of Soloud Directory Structure
#include "SoLoud/soloud.h"
#include "SoLoud/soloud_wav.h"
#include "SoLoud/soloud_speech.h"
#include "SoLoud/soloud_openmpt.h"
#include "SoLoud/soloud_thread.h"
//------------------------------------------------------------------------------------------

// thread for multithreading
#include <thread>
#include <iostream>
#include <ctime>

// For Slider class recognition....////////////////////////
#include "highlevel/Slider.h"
class Slider;
//////////////////////////////////////////////////////////////

///for function thread overflow managing...///////////////////////////////////////////////////////
using namespace std;
inline double __ctime() {
	return time(NULL);
}

class LoadAudio {
	bool UPDATE_SOUND = false;
	bool QUIT_THREAD = false;
	float vol = 0.0f;
	
	//double crtvolume = 0.0;
	double last = __ctime();
	SoLoud::Soloud* soloud = new SoLoud::Soloud(); // Engine core
	SoLoud::Wav* wav = new SoLoud::Wav();       // One sample source

	bool mmplaysound = false; // bool for playing
	int sound_handle = -1; // Soloud Needs a handle to play/pause
	double current_time = 0; // trying to sync this with slider
	int button___ins = 0; // temp variable
	bool seek_change = false; // if it should change the current time.
	string previous; // so it doesnt load the same audio sample twice

public:
	void setVolume(float vol);
	LoadAudio(); // constructor , no args
	void Play(string path); // main playing method
	void ___play_sound(string path, SoLoud::Soloud* soloud, SoLoud::Wav* wav, bool loop); // plays sound with class variables
	void skip(double time); // skips <time> - time
	void back(double time); // goes back <time> - time
	void pause(); // pauses
	void setLooping(bool instance);
	void sync_Slider(Slider* slider); // Sync with <slider> - slider
	double time(); // returns time
	double song_time(); // returns sample time
};