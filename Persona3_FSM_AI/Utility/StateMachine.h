//2022182034 임성진
#pragma once
#include <string>
#include "State.h"
using namespace std;

template <class T>
class StateMachine {
private:
	T* owner;
	State<T>* currentState;
	State<T>* previousState;
	State<T>* globalState;

public:
	StateMachine(T* owner) : owner(owner), currentState(NULL), previousState(NULL), globalState(NULL) {}
	virtual ~StateMachine() {}

	//상태 설정 함수
	void SetCurrentState(State<T>* state) { currentState = state; }
	void SetPreviousState(State<T>* state) { previousState = state; }
	void SetGlobalState(State<T>* state) { globalState = state; }
	
	//상태 실행 함수
	void Update() const {
		//if (globalState) globalState->Execute(owner);
		if (currentState) currentState->Execute(owner);
	}

	//메시지 처리 함수
	void OnMessage(const string message) const {
		currentState->OnMessage(owner, message);
		globalState->OnMessage(owner, message);
	}

	//상태 전환 함수
	void ChangeState(State<T>* newState) {
		previousState = currentState;

		currentState->Exit(owner);
		currentState = newState;
		currentState->Enter(owner);
	}
	void RevertToPreviousState() {
		ChangeState(previousState);
	}

	//상태 확인 함수
	bool isInState(const State<T>& state) const {
		if (typeid(*currentState) == typeid(state)) return true;
		return false;
	}

	//상태 접근 함수
	State<T>* GetCurrentState() const { return currentState; }
	State<T>* GetPreviousState() const { return previousState; }
	State<T>* GetGlobalState() const { return globalState; }

	//상태 이름 게터 함수
	string GetNameOfCurrentState() const {
		return typeid(*currentState).name();
	}
};