//2022182034 임성진
#pragma once
#include "AIEntity.h"
#include "BehaviorTree.h"
#include "Yuki_Makoto_Behaviors.h"
#include "GlobalState.h"
#include "Day.h"
#include "DayTime.h"
#include <iostream>
using namespace std;

extern GameWorld* gameWorld; // 게임 월드 객체에 대한 전역 포인터

class Yuki_Makoto : public AIEntity {
private:
	BehaviorNode<Yuki_Makoto>* behaviorTree;

	//스테이터스
	int charm = 0;
	int brave = 0;
	int wisdom = 0;
	int level = 1;
	
public:
	//블랙 보드(공용 변수)
	Day currentDay = Day::Sunday;			// 현재 요일
	DayTime currentTime = DayTime::Night;	// 현재 시간
	float tempRand;							// 랜덤 값 임시 저장
	int aegisInteractionSiganl = -1;		//아이기스 상호작용 준비 신호(-1: 신호 없음, 0: 상호작용 불가능, 1: 상호작용 가능, 상호작용 중, 2: 상호작용 완료)
	int yamagishiInteractionSignal = -1;		//야마기시 상호작용 준비 신호(-1: 신호 없음, 0: 상호작용 불가능, 1: 상호작용 가능, 상호작용 중, 2: 상호작용 완료)

	//생성자, 소멸자
	Yuki_Makoto() {
		behaviorTree = CreateYukiMakotoBehaviorTree();
	}
	~Yuki_Makoto() = default;

	//Update 함수
	void Update() override {
		if (currentTime == gameWorld->GetCurrentTime() && currentDay == gameWorld->GetCurrentDay()) {
			behaviorTree->Tick(this);
		}
	}

	//메시지 처리 함수
	void OnMessage(const string message) override {
		if (message == "Aegis_Interactable") {
			cout << "(debug) 아이기스와 상호작용가능 메세지 수신" << endl;
			aegisInteractionSiganl = 1;
		}
		else if (message == "Aegis_Interact") {
			cout << "(debug) 아이기스와 상호작용 중 메세지 수신" << endl;
			aegisInteractionSiganl = 2;
		}
		else if (message == "Aegis_InteractComplete") {
			cout << "(debug) 아이기스와 상호작용 완료 메세지 수신" << endl;
			aegisInteractionSiganl = 3;
		}
		else if (message == "Yamagishi_Fuka_Interactable") {
			cout << "(debug) 야마기시 후카와 상호작용가능 메세지 수신" << endl;
			yamagishiInteractionSignal = 1;
		}
		else if (message == "Yamagishi_Fuka_Interact") {
			cout << "(debug) 야마기시 후카와 상호작용 중 메세지 수신" << endl;
			yamagishiInteractionSignal = 2;
		}
		else if (message == "Yamagishi_Fuka_InteractComplete") {
			cout << "(debug) 야마기시 후카와 상호작용 완료 메세지 수신" << endl;
			yamagishiInteractionSignal = 3;
		}
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

	//시간 조절 함수
	void progressTime() {
		currentTime = static_cast<DayTime>((static_cast<int>(currentTime) + 1) % 4);
		if (currentTime == DayTime::Morning) {
			currentDay = static_cast<Day>((static_cast<int>(currentDay) + 1) % 7);
		}
	}
};