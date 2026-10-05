#pragma once
#include "AIEntity.h"
#include "StateMachine.h"
#include "Yuki_Makoto_States.h"
#include "GlobalState.h"

extern GameWorld* gameWorld; // 게임 월드 객체에 대한 전역 포인터

class Yuki_Makoto : public AIEntity {
private:
	GameWorld* globalGameWorld; // 게임 월드 객체에 대한 포인터
	StateMachine<Yuki_Makoto>* stateMachine;

	//스테이터스
	int charm = 0;
	int brave = 0;
	int wisdom = 0;
	int level = 1;
	
public:
	//생성자, 소멸자
	Yuki_Makoto() {
		globalGameWorld = gameWorld;
		stateMachine = new StateMachine<Yuki_Makoto>(this);

		//초기 상태 설정
		stateMachine->SetCurrentState(Yuki_State_Sleeping::Instance());
		stateMachine->SetGlobalState(Yuki_Makoto_GlobalState::Instance());
	}
	~Yuki_Makoto() = default;

	//상태 머신 게터
	StateMachine<Yuki_Makoto>* GetFSM() const { return stateMachine; }

	//Update 함수
	void Update() override {
		Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(stateMachine->GetGlobalState());

		if (globalState->GetCurrentDay() == gameWorld->GetCurrentDay() &&
			globalState->GetCurrentTime() == gameWorld->GetCurrentTime()) {
			stateMachine->Update();
		}
	}

	//메시지 처리 함수
	void OnMessage(const string message) override {
		stateMachine->OnMessage(message);
	}

	//스테이터스 게터
	int GetCharm() const { return charm; }
	int GetBrave() const { return brave; }
	int GetWisdom() const { return wisdom; }
	int GetLevel() const { return level; }
	
	//스테이터스 조절 함수
	void SetCharm(int value) { charm = value; }
	void SetBrave(int value) { brave = value; }
	void SetWisdom(int value) { wisdom = value; }
	void SetLevel(int value) { level = value; }
};