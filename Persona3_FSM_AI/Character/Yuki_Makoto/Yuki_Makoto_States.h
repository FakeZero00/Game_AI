#pragma once

#include "State.h"
#include <random>
using namespace std;

class Yuki_Makoto;

//==================================취침 상태==============================

class Yuki_State_Sleeping : public State<Yuki_Makoto> {
private:
	Yuki_State_Sleeping() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_State_Sleeping(const Yuki_State_Sleeping&);
	Yuki_State_Sleeping& operator=(const Yuki_State_Sleeping&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_State_Sleeping* Instance();

	void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	void Exit(Yuki_Makoto* entity) override;
};

//==================================기상 상태==============================

class Yuki_State_WakeUp : public State<Yuki_Makoto> {
private:
	Yuki_State_WakeUp() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_State_WakeUp(const Yuki_State_WakeUp&);
	Yuki_State_WakeUp& operator=(const Yuki_State_WakeUp&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_State_WakeUp* Instance();

	void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	void Exit(Yuki_Makoto* entity) override;
};

//============================학교 수업 상태==============================

class Yuki_State_School : public State<Yuki_Makoto> {
private:
	Yuki_State_School() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_State_School(const Yuki_State_School&);
	Yuki_State_School& operator=(const Yuki_State_School&);

	//랜덤 엔진
	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urd{ 0.0, 1.0 };

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_State_School* Instance();

	void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	void Exit(Yuki_Makoto* entity) override;
};

//============================상호작용 대기 상태==============================

class Yuki_State_InteractionWait : public State<Yuki_Makoto> {
private:
	Yuki_State_InteractionWait() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_State_InteractionWait(const Yuki_State_InteractionWait&);
	Yuki_State_InteractionWait& operator=(const Yuki_State_InteractionWait&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_State_InteractionWait* Instance();

	void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	void Exit(Yuki_Makoto* entity) override;
};

//==================아침 or 방과 후 상호작용 대기 상태========================

class Yuki_State_BehaviorWait : public State<Yuki_Makoto> {
private:
	Yuki_State_BehaviorWait() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_State_BehaviorWait(const Yuki_State_BehaviorWait&);
	Yuki_State_BehaviorWait& operator=(const Yuki_State_BehaviorWait&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_State_BehaviorWait* Instance();

	void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	void Exit(Yuki_Makoto* entity) override;
};

//=====================아이기스 상호작용 상태==========================

class Yuki_State_AegisInteraction : public State<Yuki_Makoto> {
private:
	Yuki_State_AegisInteraction() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_State_AegisInteraction(const Yuki_State_AegisInteraction&);
	Yuki_State_AegisInteraction& operator=(const Yuki_State_AegisInteraction&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_State_AegisInteraction* Instance();

	void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	void Exit(Yuki_Makoto* entity) override;
};

//====================밤 상호작용 랜덤 선택 상태============================

class Yuki_State_NightBehaviorWait : public State<Yuki_Makoto> {
private:
	Yuki_State_NightBehaviorWait() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_State_NightBehaviorWait(const Yuki_State_NightBehaviorWait&);
	Yuki_State_NightBehaviorWait& operator=(const Yuki_State_NightBehaviorWait&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_State_NightBehaviorWait* Instance();

	void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	void Exit(Yuki_Makoto* entity) override;
};

//====================타르타로스 전투 상태============================

class Yuki_State_TartarosBattle : public State<Yuki_Makoto> {
private:
	Yuki_State_TartarosBattle() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_State_TartarosBattle(const Yuki_State_TartarosBattle&);
	Yuki_State_TartarosBattle& operator=(const Yuki_State_TartarosBattle&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_State_TartarosBattle* Instance();

	void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	void Exit(Yuki_Makoto* entity) override;
};

//==================스테이터스 행동 랜덤 선택 상태===========================

class Yuki_State_StatusBehavior : public State<Yuki_Makoto> {
private:
	Yuki_State_StatusBehavior() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_State_StatusBehavior(const Yuki_State_StatusBehavior&);
	Yuki_State_StatusBehavior& operator=(const Yuki_State_StatusBehavior&);

	//랜덤 엔진
	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urd{ 0.0, 1.0 };

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_State_StatusBehavior* Instance();

	void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	void Exit(Yuki_Makoto* entity) override;
};

//==========================카페 샤갈 상태===========================

class Yuki_State_CafeShagal : public State<Yuki_Makoto> {
private:
	Yuki_State_CafeShagal() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_State_CafeShagal(const Yuki_State_CafeShagal&);
	Yuki_State_CafeShagal& operator=(const Yuki_State_CafeShagal&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_State_CafeShagal* Instance();

	void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	void Exit(Yuki_Makoto* entity) override;
};

//==========================노래방 상태===========================

class Yuki_State_Karaoke : public State<Yuki_Makoto> {
private:
	Yuki_State_Karaoke() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_State_Karaoke(const Yuki_State_Karaoke&);
	Yuki_State_Karaoke& operator=(const Yuki_State_Karaoke&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_State_Karaoke* Instance();

	void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	void Exit(Yuki_Makoto* entity) override;
};

//==========================공부하기 상태===========================

class Yuki_State_Study : public State<Yuki_Makoto> {
private:
	Yuki_State_Study() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yuki_State_Study(const Yuki_State_Study&);
	Yuki_State_Study& operator=(const Yuki_State_Study&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yuki_State_Study* Instance();

	void Enter(Yuki_Makoto* entity) override;
	void Execute(Yuki_Makoto* entity) override;
	void Exit(Yuki_Makoto* entity) override;
};