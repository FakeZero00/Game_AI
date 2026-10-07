#pragma once
#include "State.h"

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

	GameWorld(Yuki_Makoto* yuki, Aegis* aegis) : yuki(yuki), aegis(aegis) {}

	Day GetCurrentDay() const { return currentDay; }
	DayTime GetCurrentTime() const { return currentTime; }

	void PrintCurrentTime();
	void Update();

	void Message2Makoto(const string message);
	void Message2Aegis(const string message);
	void Message2Yamagishi(const string message);
};

//============================유키 마코토 전역 상태==============================

class Yuki_Makoto_GlobalState : public State<Yuki_Makoto> {
private:
	Day currentDay = Day::Sunday; // 현재 요일을 나타내는 멤버 변수
	DayTime currentTime = DayTime::Night; // 현재 시간을 나타내는 멤버 변수
	bool dayChangeSignal = false;
	bool timeChangeSignal = false;

	bool aegisInteractionSignal = false;
	bool yamagishiInteractionSignal = false;

	Yuki_Makoto_GlobalState() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_Makoto_GlobalState(const Yuki_Makoto_GlobalState&);
	Yuki_Makoto_GlobalState& operator=(const Yuki_Makoto_GlobalState&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_Makoto_GlobalState* Instance();

	//void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	//void Exit(Yuki_Makoto* entity) override;
	void OnMessage(Yuki_Makoto* entity, const string message) override;

	Day GetCurrentDay() const { return currentDay; }
	DayTime GetCurrentTime() const { return currentTime; }
	bool GetAegisInteractionSignal() const { return aegisInteractionSignal; }
	void SetAegisInteractionSignal(bool val) { aegisInteractionSignal = val; }
	bool GetYamagishiInteractionSignal() const { return yamagishiInteractionSignal; }
	void SetYamagishiInteractionSignal(bool val) { yamagishiInteractionSignal = val; }

	void CallTimeSignal() { timeChangeSignal = true; }
	void CallDaySignal() { dayChangeSignal = true; }
};

//============================아이기스 전역 상태==============================

class Aegis_GlobalState : public State<Aegis> {
private:
	Day currentDay = Day::Sunday; // 현재 요일을 나타내는 멤버 변수
	DayTime currentTime = DayTime::Night; // 현재 시간을 나타내는 멤버 변수
	bool dayChangeSignal = false;
	bool timeChangeSignal = false;

	bool yukiInteractionSignal = false;

	Aegis_GlobalState() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Aegis_GlobalState(const Aegis_GlobalState&);
	Aegis_GlobalState& operator=(const Aegis_GlobalState&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Aegis_GlobalState* Instance();

	//void Enter(Aegis* entity) override;
	void Execute(Aegis* entity) override;
	//void Exit(Aegis* entity) override;
	void OnMessage(Aegis* entity, const string message) override;

	Day GetCurrentDay() const { return currentDay; }
	DayTime GetCurrentTime() const { return currentTime; }
	bool GetYukiInteractionSignal() const { return yukiInteractionSignal; }
	void SetYukiInteractionSignal(bool val) { yukiInteractionSignal = val; }

	void CallTimeSignal() { timeChangeSignal = true; }
	void CallDaySignal() { dayChangeSignal = true; }
};

//========================야마기시 후카 전역 상태==============================

class Yamagishi_Fuka_GlobalState : public State<Yamagishi_Fuka> {
private:
	Day currentDay = Day::Sunday; // 현재 요일을 나타내는 멤버 변수
	DayTime currentTime = DayTime::Night; // 현재 시간을 나타내는 멤버 변수
	bool dayChangeSignal = false;
	bool timeChangeSignal = false;

	bool yukiInteractionSignal = false;

	Yamagishi_Fuka_GlobalState() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yamagishi_Fuka_GlobalState(const Yamagishi_Fuka_GlobalState&);
	Yamagishi_Fuka_GlobalState& operator=(const Yamagishi_Fuka_GlobalState&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yamagishi_Fuka_GlobalState* Instance();

	//void Enter(Yamagishi_Fuka* entity) override;
	void Execute(Yamagishi_Fuka* entity) override;
	//void Exit(Yamagishi_Fuka* entity) override;
	void OnMessage(Yamagishi_Fuka* entity, const string message) override;

	Day GetCurrentDay() const { return currentDay; }
	DayTime GetCurrentTime() const { return currentTime; }
	bool GetYukiInteractionSignal() const { return yukiInteractionSignal; }
	void SetYukiInteractionSignal(bool val) { yukiInteractionSignal = val; }

	void CallTimeSignal() { timeChangeSignal = true; }
	void CallDaySignal() { dayChangeSignal = true; }
};