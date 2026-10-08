//2022182034 임성진
#include "GlobalState.h"

#include <iostream>
#include <string>
#include "Day.h"
#include "Time.h"
#include "StateMachine.h"

#include "Yuki_Makoto/Yuki_Makoto.h"
#include "Yuki_Makoto/Yuki_Makoto_States.h"
#include "Aegis/Aegis.h"
#include "Aegis/Aegis_States.h"
#include "Yamagishi_Fuka/Yamagishi_Fuka.h"
#include "Yamagishi_Fuka/Yamagishi_Fuka_States.h"

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
	Yuki_Makoto_GlobalState* yukiGlobalState = static_cast<Yuki_Makoto_GlobalState*>(yuki->GetFSM()->GetGlobalState());
	Aegis_GlobalState* aegisGlobalState = static_cast<Aegis_GlobalState*>(aegis->GetFSM()->GetGlobalState());
	Yamagishi_Fuka_GlobalState* yamagishiGlobalState = static_cast<Yamagishi_Fuka_GlobalState*>(yamagishi->GetFSM()->GetGlobalState());

	yukiGlobalState->Execute(yuki);
	aegisGlobalState->Execute(aegis);
	yamagishiGlobalState->Execute(yamagishi);


	if(yukiGlobalState->GetCurrentTime() != currentTime &&
		aegisGlobalState->GetCurrentTime() != currentTime &&
		yamagishiGlobalState->GetCurrentTime() != currentTime) {
		currentTime = static_cast<DayTime>((static_cast<int>(currentTime) + 1) % 4);
		printTimeSignal = true;
	}
	if (yukiGlobalState->GetCurrentDay() != currentDay &&
		aegisGlobalState->GetCurrentDay() != currentDay &&
		yamagishiGlobalState->GetCurrentDay() != currentDay) {
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

//============================유키 마코토 전역 상태==============================

Yuki_Makoto_GlobalState* Yuki_Makoto_GlobalState::Instance() {
	static Yuki_Makoto_GlobalState instance;
	return &instance;
}

void Yuki_Makoto_GlobalState::Execute(Yuki_Makoto* entity) {
	//시간 진행
	if (timeChangeSignal) {
		//심야가 되면 요일을 진행
		if (currentTime == DayTime::Night) CallDaySignal();

		currentTime = static_cast<DayTime>((static_cast<int>(currentTime) + 1) % 4);
		timeChangeSignal = false;
	}
	
	//요일 진행
	if (dayChangeSignal) {
		currentDay = static_cast<Day>((static_cast<int>(currentDay) + 1) % 7);
		dayChangeSignal = false;
	}
}

void Yuki_Makoto_GlobalState::OnMessage(Yuki_Makoto* entity, const string message) {
	if (message == "Aegis_Interactable") {
		aegisInteractionSignal = true;
	}
	else if (message == "Yamagishi_Fuka_Interactable") {
		yamagishiInteractionSignal = true;
	}
}

//==============================아이기스 전역 상태==============================

Aegis_GlobalState* Aegis_GlobalState::Instance() {
	static Aegis_GlobalState instance;
	return &instance;
}

void Aegis_GlobalState::Execute(Aegis* entity) {
	//시간 진행
	if (timeChangeSignal) {
		//심야가 되면 요일을 진행
		if (currentTime == DayTime::Night) CallDaySignal();

		currentTime = static_cast<DayTime>((static_cast<int>(currentTime) + 1) % 4);
		timeChangeSignal = false;
	}

	//요일 진행
	if (dayChangeSignal) {
		currentDay = static_cast<Day>((static_cast<int>(currentDay) + 1) % 7);
		dayChangeSignal = false;
	}
}

void Aegis_GlobalState::OnMessage(Aegis* entity, const string message) {
	if (message == "Selected") {
		yukiInteractionSignal = true;
	}
	else if (message == "Unselected") {
		yukiInteractionSignal = false;
	}
}

//========================야마기시 후카 전역 상태==============================

Yamagishi_Fuka_GlobalState* Yamagishi_Fuka_GlobalState::Instance() {
	static Yamagishi_Fuka_GlobalState instance;
	return &instance;
}

void Yamagishi_Fuka_GlobalState::Execute(Yamagishi_Fuka* entity) {
	//시간 진행
	if (timeChangeSignal) {
		//심야가 되면 요일을 진행
		if (currentTime == DayTime::Night) CallDaySignal();

		currentTime = static_cast<DayTime>((static_cast<int>(currentTime) + 1) % 4);
		timeChangeSignal = false;
	}

	//요일 진행
	if (dayChangeSignal) {
		currentDay = static_cast<Day>((static_cast<int>(currentDay) + 1) % 7);
		dayChangeSignal = false;
	}
}

void Yamagishi_Fuka_GlobalState::OnMessage(Yamagishi_Fuka* entity, const string message) {
	if (message == "Selected") {
		yukiInteractionSignal = true;
	}
	else if (message == "Unselected") {
		yukiInteractionSignal = false;
	}
}