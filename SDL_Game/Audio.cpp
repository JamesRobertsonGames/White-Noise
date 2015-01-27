/*!
*  \brief     Audio Class.
*  \details   This class is to handle the Ausio in the game. Pausing, playing and stopping.
*  \author    James Robertson
*  \version   1.0a
*  \date      2014-2015
*  \copyright GNU Public License.
*/

#include "Audio.h"

aud::audio::audio()
{
	gMusic = NULL;
	gChunk = NULL;
	audio_pos = 0; // global pointer to the audio buffer to be played
	audio_len = 0; // remaining length of the sample we have to play
	wav_length = 0; // length of our sample
	wav_buffer = 0; // buffer containing our audio file
	play = 0;
	sfx = false;
}

void aud::audio::sfxSelect(bool select)
{
	sfx = select;
}

void aud::audioCallback(void *userdata, Uint8 *stream, int len)
{
	if (audio_len == 0)
		return;

	len = ((Uint8)len > audio_len ? audio_len : len);
	SDL_memcpy(stream, audio_pos, len); 					// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, 33);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}

void aud::audio::loadAudio(std::string file)
{
	if (sfx)
	{
		gChunk = Mix_LoadWAV(file.c_str());
	}
	else
	{
		gMusic = Mix_LoadMUS(file.c_str());
	}
}

void aud::audio::playAudio()
{
	if (sfx)
	{
		wav_spec.callback = audioCallback;
		wav_spec.userdata = NULL;

		audio_pos = wav_buffer; // copy sound buffer
		audio_len = wav_length; // copy file length
		SDL_OpenAudio(&wav_spec, NULL);
		SDL_PauseAudio(play);
	}
	else
	{
		Mix_PlayMusic(gMusic, -1);
	}

}

void aud::audio::pauseAudio()
{
	if (sfx)
	{

	}
	else
	{
		SDL_CloseAudio();
	}
}