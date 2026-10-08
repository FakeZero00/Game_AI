//2022182034 임성진
#pragma once
#include "State.h"

#include <random>

class Aegis;

//==================================취침 상태==============================

class Aegis_State_Sleeping : public State<Aegis> {
private:
	Aegis_State_Sleeping() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Aegis_State_Sleeping(const Aegis_State_Sleeping&);
	Aegis_State_Sleeping& operator=(const Aegis_State_Sleeping&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Aegis_State_Sleeping* Instance();

	void Enter(Aegis* entity) override;
	void Execute(Aegis* entity) override;
	void Exit(Aegis* entity) override;
};

//==================================기상 상태==============================

class Aegis_State_WakeUp : public State<Aegis> {
private:
	Aegis_State_WakeUp() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Aegis_State_WakeUp(const Aegis_State_WakeUp&);
	Aegis_State_WakeUp& operator=(const Aegis_State_WakeUp&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Aegis_State_WakeUp* Instance();

	void Enter(Aegis* entity) override;
	void Execute(Aegis* entity) override;
	void Exit(Aegis* entity) override;
};

//============================학교 수업 상태==============================

class Aegis_State_School : public State<Aegis> {
private:
	Aegis_State_School() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Aegis_State_School(const Aegis_State_School&);
	Aegis_State_School& operator=(const Aegis_State_School&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Aegis_State_School* Instance();

	void Enter(Aegis* entity) override;
	void Execute(Aegis* entity) override;
	void Exit(Aegis* entity) override;
};

//============================상호작용 대기 상태==============================

class Aegis_State_InteractionWait : public State<Aegis> {
private:
	Aegis_State_InteractionWait() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Aegis_State_InteractionWait(const Aegis_State_InteractionWait&);
	Aegis_State_InteractionWait& operator=(const Aegis_State_InteractionWait&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Aegis_State_InteractionWait* Instance();

	void Enter(Aegis* entity) override;
	void Execute(Aegis* entity) override;
	void Exit(Aegis* entity) override;
};

//==================아침 or 방과 후 상호작용 대기 상태========================

class Aegis_State_BehaviorWait : public State<Aegis> {
private:
	Aegis_State_BehaviorWait() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Aegis_State_BehaviorWait(const Aegis_State_BehaviorWait&);
	Aegis_State_BehaviorWait& operator=(const Aegis_State_BehaviorWait&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Aegis_State_BehaviorWait* Instance();

	void Enter(Aegis* entity) override;
	void Execute(Aegis* entity) override;
	void Exit(Aegis* entity) override;
};

//==================유키 마코토와 상호작용 상태========================

class Aegis_State_YukiInteraction : public State<Aegis> {
private:
	Aegis_State_YukiInteraction() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Aegis_State_YukiInteraction(const Aegis_State_YukiInteraction&);
	Aegis_State_YukiInteraction& operator=(const Aegis_State_YukiInteraction&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Aegis_State_YukiInteraction* Instance();

	void Enter(Aegis* entity) override;
	void Execute(Aegis* entity) override;
	void Exit(Aegis* entity) override;
};

//====================밤 상호작용 선택 상태============================

class Aegis_State_NightBehaviorWait : public State<Aegis> {
private:
	Aegis_State_NightBehaviorWait() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Aegis_State_NightBehaviorWait(const Aegis_State_NightBehaviorWait&);
	Aegis_State_NightBehaviorWait& operator=(const Aegis_State_NightBehaviorWait&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Aegis_State_NightBehaviorWait* Instance();

	void Enter(Aegis* entity) override;
	void Execute(Aegis* entity) override;
	void Exit(Aegis* entity) override;
};

//====================타르타로스 전투 상태============================

class Aegis_State_TartarosBattle : public State<Aegis> {
private:
	Aegis_State_TartarosBattle() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Aegis_State_TartarosBattle(const Aegis_State_TartarosBattle&);
	Aegis_State_TartarosBattle& operator=(const Aegis_State_TartarosBattle&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Aegis_State_TartarosBattle* Instance();

	void Enter(Aegis* entity) override;
	void Execute(Aegis* entity) override;
	void Exit(Aegis* entity) override;
};

//========================시간 보내기 상태============================

class Aegis_State_TimeSpent : public State<Aegis> {
private:
	Aegis_State_TimeSpent() = default;

	//복사 생성자와 대입 연산자 private로 선언하여 외부에서 접근하지 못하도록 함
	Aegis_State_TimeSpent(const Aegis_State_TimeSpent&);
	Aegis_State_TimeSpent& operator=(const Aegis_State_TimeSpent&);

public:
	//싱글톤 패턴을 위한 인스턴스 접근 함수
	static Aegis_State_TimeSpent* Instance();

	void Enter(Aegis* entity) override;
	void Execute(Aegis* entity) override;
	void Exit(Aegis* entity) override;
};