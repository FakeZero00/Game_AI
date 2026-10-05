#pragma once
#include "AIEntity.h"
#include "StateMachine.h"
#include "Aegis_States.h"
#include "GlobalState.h"

extern GameWorld* gameWorld; // 게임 월드 객체에 대한 전역 포인터

class Aegis : public AIEntity {
private:
	GameWorld* globalGameWorld; // 게임 월드 객체에 대한 포인터
	StateMachine<Aegis>* stateMachine;

	int level = 1;
	int likeability = 0;

public:
	//생성자, 소멸자
	Aegis() {
		globalGameWorld = gameWorld;
		stateMachine = new StateMachine<Aegis>(this);

		//초기 상태 설정
		stateMachine->SetCurrentState(Aegis_State_Sleeping::Instance());
		stateMachine->SetGlobalState(Aegis_GlobalState::Instance());
	}
	~Aegis() = default;

	//상태 머신 게터
	StateMachine<Aegis>* GetFSM() const { return stateMachine; }

	//스테이터스 게터
	int GetLevel() const { return level; }
	int GetLikeability() const { return likeability; }

	//스테이터스 조절 함수
	void SetLevel(int value) { level = value; }
	void SetLikeability(int value) { likeability = value; }

	//Update 함수
	void Update() override {
		Aegis_GlobalState* globalState = static_cast<Aegis_GlobalState*>(stateMachine->GetGlobalState());

		if (globalState->GetCurrentDay() == gameWorld->GetCurrentDay() &&
			globalState->GetCurrentTime() == gameWorld->GetCurrentTime()) {
			stateMachine->Update();
		}
	}

	//메시지 처리 함수
	void OnMessage(const string message) override {
		stateMachine->OnMessage(message);
	}
};