#include "sound_manager.h"
#include <Windows.h>
#include "glut.h"
#include <stdio.h>

const char* file_name = "train_sound.wav";
const int TRAIN_SOUND_LENGTH = 22000; //is ms
bool train_sound_playing = false;

void PlayTrainSound(int i)
{
	train_sound_playing = PlaySound(file_name, NULL, SND_ASYNC);
	glutTimerFunc(TRAIN_SOUND_LENGTH, StopSound, 0); //repeat sound when its finish 

}

void StopSound(int i)
{
	train_sound_playing = !PlaySound(NULL, NULL, SND_ASYNC);
	train_sound_playing = false;
}
