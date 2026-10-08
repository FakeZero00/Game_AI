#include "GlobalState.h"

#include <iostream>
#include <string>
#include "Day.h"
#include "Time.h"

#include "Yuki_Makoto/Yuki_Makoto.h"
#include "Aegis/Aegis.h"
#include "Yamagishi_Fuka/Yamagishi_Fuka.h"

using namespace std;
//============================게임 월드 전역 상태==============================

void GameWorld::PrintCurrentTime() {
	if (printTimeSignal) {
		string dayNames[] = { "월요일", "화요일", "수요일", "목요일", "금요일", "토요일", "일요일" };
		string timeNames[] = { "아침", "방과 후", "밤", "심야" };

		cout << "======[" << dayNames[static_cast<int>(currentDay)] << "]: " << timeNames[static_cast<int>(currentTime)] << "======" << endl;
		printTimeSignal = false;
	}
}

void GameWorld::Update() {

	if(yuki->currentTime != currentTime &&
		aegis->currentTime != currentTime &&
		yamagishi->currentTime != currentTime) {
		currentTime = static_cast<DayTime>((static_cast<int>(currentTime) + 1) % 4);
		printTimeSignal = true;
	}
	if (yuki->currentDay != currentDay &&
		aegis->currentDay != currentDay &&
		yamagishi->currentDay != currentDay) {
		currentDay = static_cast<Day>((static_cast<int>(currentDay) + 1) % 7);
		printTimeSignal = true;
	}

	if (currentDay == Day::Monday && currentTime == DayTime::Morning) {
		loop++;
	}
}

void GameWorld::Message2Makoto(const string message) {
	yuki->OnMessage(message);
}

void GameWorld::Message2Aegis(const string message) {
	aegis->OnMessage(message);
}

void GameWorld::Message2Yamagishi(const string message) {
	yamagishi->OnMessage(message);
}