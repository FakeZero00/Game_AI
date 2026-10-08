//2022182034 임성진
#pragma once
#include <string>
#include "Day.h"
#include "DayTime.h"
using namespace std;

class Yuki_Makoto;
class Aegis;
class Yamagishi_Fuka;

//============================게임 월드 전역 상태==============================
class GameWorld {
private:
	Yuki_Makoto* yuki; // 유키 마코토 객체에 대한 포인터
	Aegis* aegis; // 아이기스 객체에 대한 포인터
	Yamagishi_Fuka* yamagishi; // 야마기시 후카 객체에 대한 포인터

	Day currentDay = Day::Sunday; // 현재 요일을 나타내는 멤버 변수
	DayTime currentTime = DayTime::Night; // 현재 시간을 나타내는 멤버 변수
	bool dayChangeSignal = false;
	bool timeChangeSignal = false;
	bool printTimeSignal = true;

public:
	int loop = 0;

	GameWorld(Yuki_Makoto* yuki, Aegis* aegis, Yamagishi_Fuka* yamagishi) : yuki(yuki), aegis(aegis), yamagishi(yamagishi) {}

	Day GetCurrentDay() const { return currentDay; }
	DayTime GetCurrentTime() const { return currentTime; }

	void PrintCurrentTime();
	void Update();

	void Message2Makoto(const string message);
	void Message2Aegis(const string message);
	void Message2Yamagishi(const string message);
};