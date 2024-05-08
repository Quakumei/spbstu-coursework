// Mol-8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h> 
#include <windows.h>
#include "inc\fmod.hpp"
#include "inc\fmod_errors.h"
#include <iostream>
#pragma comment(lib, "fmodex_vc.lib")
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	// FMOD 4	
	// Инициализируем FMOD
	FMOD_RESULT result;
	FMOD::System * system; 
	result = FMOD::System_Create(&system);
	result = system->init(16, FMOD_INIT_NORMAL, 0);

	// Зададим наш звук и запустим его
	FMOD::Sound* sound;
	FMOD::Channel* channel;
	system->createSound("ns.mp3", FMOD_3D, 0, &sound);
	system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);

	// Зададим эффект Distortion
	FMOD::DSP* distortion;
	float distortionLevel = 0.7f; // 0.0 = Отсутствие эффекта, 1.0 = Максимальный
	system->createDSPByType(FMOD_DSP_TYPE_DISTORTION, &distortion);
	distortion->setParameter(FMOD_DSP_DISTORTION_LEVEL, distortionLevel);

	// Добавим звуковой эффект к нашему каналу
	FMOD::DSPConnection* connection;
	channel->addDSP(distortion, &connection);

	// Ждем, пока композиция не будет исполнена полностью и наслаждаемся прекрасной музыкой
	bool isPlaying = true;
	while (isPlaying) {
		channel->isPlaying(&isPlaying);
		system->update();
	}

	return 0;
}
