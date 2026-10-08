#pragma once
#include "AIEntity.h"
#include "BehaviorTree.h"
#include "Aegis_Behaviors.h"
#include "GlobalState.h"

extern GameWorld* gameWorld; // 게임 월드 객체에 대한 전역 포인터

class Aegis : public AIEntity {
private:
	BehaviorNode<Aegis>* behaviorTree;

	int level = 1;
	int likeability = 0;

public:
	//블랙 보드(공용 변수)
	Day currentDay = Day::Sunday;			// 현재 요일
	DayTime currentTime = DayTime::Night;	// 현재 시간
	int yukiInteractionSignal = -1;			// 유키 마코토 상호작용 신호(-1: 신호 없음, 0: 상호작용 불가능, 1: 상호작용 가능)

	//생성자, 소멸자
	Aegis() {
		behaviorTree = CreateAegisBehaviorTree();
	}
	~Aegis() = default;

	//스테이터스 게터
	int GetLevel() const { return level; }
	int GetLikeability() const { return likeability; }

	//스테이터스 조절 함수
	void SetLevel(int value) { level = value; }
	void SetLikeability(int value) { likeability = value; }

	//Update 함수
	void Update() override {
		if (currentTime == gameWorld->GetCurrentTime() && currentDay == gameWorld->GetCurrentDay()) {
			behaviorTree->Tick(this);
		}
	}

	//메시지 처리 함수
	void OnMessage(const string message) override {
		if (message == "Selected") yukiInteractionSignal = 1;
		else if (message == "Unselected") yukiInteractionSignal = 0;
	}

	//시간 조절 함수
	void progressTime() {
		currentTime = static_cast<DayTime>((static_cast<int>(currentTime) + 1) % 4);
		if (currentTime == DayTime::Morning) {
			currentDay = static_cast<Day>((static_cast<int>(currentDay) + 1) % 7);
		}
	}
};