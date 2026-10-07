#pragma once

#include "State.h"

#include <random>

class Yamagishi_Fuka;

//==================================취침 상태==============================

class Yamagishi_Fuka_State_Sleeping : public State<Yamagishi_Fuka> {
private:
	Yamagishi_Fuka_State_Sleeping() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yamagishi_Fuka_State_Sleeping(const Yamagishi_Fuka_State_Sleeping&);
	Yamagishi_Fuka_State_Sleeping& operator=(const Yamagishi_Fuka_State_Sleeping&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yamagishi_Fuka_State_Sleeping* Instance();

	void Enter(Yamagishi_Fuka* entity) override;
	void Execute(Yamagishi_Fuka* entity) override;
	void Exit(Yamagishi_Fuka* entity) override;
};

//==================================기상 상태==============================

class Yamagishi_Fuka_State_WakeUp : public State<Yamagishi_Fuka> {
private:
	Yamagishi_Fuka_State_WakeUp() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yamagishi_Fuka_State_WakeUp(const Yamagishi_Fuka_State_WakeUp&);
	Yamagishi_Fuka_State_WakeUp& operator=(const Yamagishi_Fuka_State_WakeUp&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yamagishi_Fuka_State_WakeUp* Instance();

	void Enter(Yamagishi_Fuka* entity) override;
	void Execute(Yamagishi_Fuka* entity) override;
	void Exit(Yamagishi_Fuka* entity) override;
};

//============================학교 수업 상태==============================

class Yamagishi_Fuka_State_School : public State<Yamagishi_Fuka> {
private:
	Yamagishi_Fuka_State_School() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yamagishi_Fuka_State_School(const Yamagishi_Fuka_State_School&);
	Yamagishi_Fuka_State_School& operator=(const Yamagishi_Fuka_State_School&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yamagishi_Fuka_State_School* Instance();

	void Enter(Yamagishi_Fuka* entity) override;
	void Execute(Yamagishi_Fuka* entity) override;
	void Exit(Yamagishi_Fuka* entity) override;
};

//============================상호작용 대기 상태==============================

class Yamagishi_Fuka_State_InteractionWait : public State<Yamagishi_Fuka> {
private:
	Yamagishi_Fuka_State_InteractionWait() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yamagishi_Fuka_State_InteractionWait(const Yamagishi_Fuka_State_InteractionWait&);
	Yamagishi_Fuka_State_InteractionWait& operator=(const Yamagishi_Fuka_State_InteractionWait&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yamagishi_Fuka_State_InteractionWait* Instance();

	void Enter(Yamagishi_Fuka* entity) override;
	void Execute(Yamagishi_Fuka* entity) override;
	void Exit(Yamagishi_Fuka* entity) override;
};

//==================아침 or 방과 후 상호작용 대기 상태========================

class Yamagishi_Fuka_State_BehaviorWait : public State<Yamagishi_Fuka> {
private:
	Yamagishi_Fuka_State_BehaviorWait() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yamagishi_Fuka_State_BehaviorWait(const Yamagishi_Fuka_State_BehaviorWait&);
	Yamagishi_Fuka_State_BehaviorWait& operator=(const Yamagishi_Fuka_State_BehaviorWait&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yamagishi_Fuka_State_BehaviorWait* Instance();

	void Enter(Yamagishi_Fuka* entity) override;
	void Execute(Yamagishi_Fuka* entity) override;
	void Exit(Yamagishi_Fuka* entity) override;
};

//==================유키 마코토와 상호작용 상태========================

class Yamagishi_Fuka_State_YukiInteraction : public State<Yamagishi_Fuka> {
private:
	Yamagishi_Fuka_State_YukiInteraction() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yamagishi_Fuka_State_YukiInteraction(const Yamagishi_Fuka_State_YukiInteraction&);
	Yamagishi_Fuka_State_YukiInteraction& operator=(const Yamagishi_Fuka_State_YukiInteraction&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yamagishi_Fuka_State_YukiInteraction* Instance();

	void Enter(Yamagishi_Fuka* entity) override;
	void Execute(Yamagishi_Fuka* entity) override;
	void Exit(Yamagishi_Fuka* entity) override;
};

//====================밤 상호작용 선택 상태============================

class Yamagishi_Fuka_State_NightBehaviorWait : public State<Yamagishi_Fuka> {
private:
	Yamagishi_Fuka_State_NightBehaviorWait() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yamagishi_Fuka_State_NightBehaviorWait(const Yamagishi_Fuka_State_NightBehaviorWait&);
	Yamagishi_Fuka_State_NightBehaviorWait& operator=(const Yamagishi_Fuka_State_NightBehaviorWait&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yamagishi_Fuka_State_NightBehaviorWait* Instance();

	void Enter(Yamagishi_Fuka* entity) override;
	void Execute(Yamagishi_Fuka* entity) override;
	void Exit(Yamagishi_Fuka* entity) override;
};

//====================타르타로스 전투 상태============================

class Yamagishi_Fuka_State_TartarosBattle : public State<Yamagishi_Fuka> {
private:
	Yamagishi_Fuka_State_TartarosBattle() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yamagishi_Fuka_State_TartarosBattle(const Yamagishi_Fuka_State_TartarosBattle&);
	Yamagishi_Fuka_State_TartarosBattle& operator=(const Yamagishi_Fuka_State_TartarosBattle&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yamagishi_Fuka_State_TartarosBattle* Instance();

	void Enter(Yamagishi_Fuka* entity) override;
	void Execute(Yamagishi_Fuka* entity) override;
	void Exit(Yamagishi_Fuka* entity) override;
};

//========================시간 보내기 상태============================

class Yamagishi_Fuka_State_TimeSpent : public State<Yamagishi_Fuka> {
private:
	Yamagishi_Fuka_State_TimeSpent() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Yamagishi_Fuka_State_TimeSpent(const Yamagishi_Fuka_State_TimeSpent&);
	Yamagishi_Fuka_State_TimeSpent& operator=(const Yamagishi_Fuka_State_TimeSpent&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Yamagishi_Fuka_State_TimeSpent* Instance();

	void Enter(Yamagishi_Fuka* entity) override;
	void Execute(Yamagishi_Fuka* entity) override;
	void Exit(Yamagishi_Fuka* entity) override;
};