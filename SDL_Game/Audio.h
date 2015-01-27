#pragma once
#include <SDL_mixer.h>
#include <iostream>
#include <stdint.h>

namespace aud
{
	// Audio callback works out of class only 
	void audioCallback(void *userdata, Uint8 *stream, int len);
	
	// Audio position and length
	static Uint8 *audio_pos; 
	static Uint32 audio_len; 

	class audio
	{
	public:
		// Constructor
		audio();
		// Select if is a sfx or not
		void sfxSelect(bool select);
		// Load the audio
		void loadAudio(std::string file);
		// Play
		void playAudio();
		// Pause
		void pauseAudio();
	private:
		// Storage for filename
		std::string filename;
		// Length and Buffer
		Uint32 wav_length;
		Uint8 *wav_buffer;
		// Specifies our music
		SDL_AudioSpec wav_spec;
		// Play Value
		int play = 0;
		// SFX Bool
		bool sfx;
		// Music storage
		Mix_Music *gMusic;
		Mix_Chunk *gChunk;
	};
}