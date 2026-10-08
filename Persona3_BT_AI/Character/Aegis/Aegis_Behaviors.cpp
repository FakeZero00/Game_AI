//2022182034 임성진
#include "Aegis_Behaviors.h"
#include "Aegis.h"
#include <iostream>
#include <random>
using namespace std;

extern GameWorld* gameWorld; // 게임 월드 객체에 대한 전역 포인터

//==================컨디션 노드용 판정 함수=========================
//시간 감지(아침)
bool IsMorning(Aegis* entity) {
	return entity->currentTime == DayTime::Morning;
}

bool IsAfternoon(Aegis* entity) {
	return entity->currentTime == DayTime::Afternoon;
}

bool IsEvening(Aegis* entity) {
	return entity->currentTime == DayTime::Evening;
}

bool IsNight(Aegis* entity) {
	return entity->currentTime == DayTime::Night;
}

bool IsSunday(Aegis* entity) {
	return entity->currentDay == Day::Sunday;
}

bool IsInteractionable(Aegis* entity) {
	return (entity->currentDay == Day::Monday ||
			entity->currentDay == Day::Wednesday ||
			entity->currentDay == Day::Friday ||
			entity->currentDay == Day::Saturday);
}

//==================액션 노드 클래스=========================

//기상 & 등교 액션 노드
class Aegis_Action_WakeUp : public BehaviorNode<Aegis> {
public:
	BehaviorStatus Tick(Aegis* entity) override {
		entity->yukiInteractionSignal = -1; // 신호 초기화

		if (entity->currentDay != Day::Sunday) {
			cout << "아이기스 : 아침이 됬습니다. 학교에 갈 준비를 합니다." << endl;
			cout << "아이기스 : 학교에 도착했습니다. 수업을 들을 준비를 합니다." << endl;
		}
		else {
			cout << "아이기스 : 아침이 밝았지만...오늘은 용무가 있습니다." << endl;
		}
		
		return Success;
	}
};

//학교 수업 액션 노드
class Aegis_Action_School : public BehaviorNode<Aegis> {
public:
	BehaviorStatus Tick(Aegis* entity) override {
		cout << "아이기스 : 수업을 듣고 있는 마코토님을 지켜봅니다." << endl;

		entity->progressTime();
		return Success;
	}
};

//취침 액션 노드
class Aegis_Action_Sleep : public BehaviorNode<Aegis> {
public:
	BehaviorStatus Tick(Aegis* entity) override {
		cout << "아이기스 : 전원을 휴면 상태로 전환합니다." << endl;

		entity->progressTime();
		return Success;
	}
};

//시간 보내기 액션 노드
class Aegis_Action_TimeSpent : public BehaviorNode<Aegis> {
	BehaviorStatus Tick(Aegis* entity) override {
		cout << "아이기스는 시간을 보내고 있다." << endl;
		entity->yukiInteractionSignal = -1; // 신호 초기화

		entity->progressTime();
		return Success;
	}
};

//유키 마코토 메시지 대기 액션 노드
class Aegis_Action_WaitForYuki : public BehaviorNode<Aegis> {
	BehaviorStatus Tick(Aegis* entity) override {
		if (entity->currentTime == DayTime::Afternoon) {
			if (entity->yukiInteractionSignal == -1) {
				cout << "아이기스 : 수업이 끝났습니다. 마코토님과 시간을 보내고 싶습니다만..." << endl;
				cout << "(debug) 유키 마코토에게 상호작용 가능 메세지 송신" << endl;
				gameWorld->Message2Makoto("Aegis_Interactable");
				return Running;
			}
			else if (entity->yukiInteractionSignal == 0) {
				cout << "마코토님이 바빠보이시니 저는 혼자 시간을 보내겠습니다." << endl;
				entity->yukiInteractionSignal = -1; // 신호 초기화
				return Failure;
			}
			else if (entity->yukiInteractionSignal == 1) {
				cout << "아이기스 : 알겠습니다. 그럼 옥상으로 가죠." << endl;
				gameWorld->Message2Makoto("Aegis_Interact");
				cout << "(debug) 유키 마코토에게 상호작용 중 메세지 송신" << endl;
				entity->yukiInteractionSignal = -1; // 신호 초기화
				return Success;
			}
		}
		else if (entity->currentTime == DayTime::Evening) {
			if (entity->yukiInteractionSignal == -1) {
				cout << "아이기스 : 섀도우 타임이 다가옵니다. 마코토님, 타르타로스에 가실 건가요?" << endl;
				cout << "(debug) 유키 마코토에게 상호작용 가능 메세지 송신" << endl;
				gameWorld->Message2Makoto("Aegis_Interactable");
				return Running;
			}
			else if (entity->yukiInteractionSignal == 0) {
				cout << "마코토님이 바빠보이시니 저는 혼자 시간을 보내겠습니다." << endl;
				entity->yukiInteractionSignal = -1; // 신호 초기화
				return Failure;
			}
			else if (entity->yukiInteractionSignal == 1) {
				cout << "아이기스 : 알겠습니다. 타르타로스에 가죠!" << endl;
				gameWorld->Message2Makoto("Aegis_Interact");
				cout << "(debug) 유키 마코토에게 상호작용 중 메세지 송신" << endl;
				entity->yukiInteractionSignal = -1; // 신호 초기화
				return Success;
			}
		}
	}
};

//유키 마코토와 상호작용 액션 노드
class Aegis_Action_YukiInteraction : public BehaviorNode<Aegis> {
	BehaviorStatus Tick(Aegis* entity) override {
		if (entity->GetLikeability() == 0) {
			cout << "아이기스 : 저는 여기가 좋아요. 거리가 한눈에 보이니까요..." << endl;
			cout << "아이기스 : 아, 알고 계셨나요? 저희 기숙사도 여기서 보여요." << endl;
			cout << "아이기스 : 여기에 오기 전에는 이런 \"생각\"도 해본 적이 없었는데..." << endl;
			cout << "아이기스 : 이 변화가 당신과 함께 있어 변해 가는 거라면..." << endl;
			cout << "아이기스 : 저는 그런 자신을 소중히 여기고 싶어요." << endl;
			entity->SetLikeability(entity->GetLikeability() + 1);
		}
		else if (entity->GetLikeability() == 1) {
			cout << "아이기스 : 문득, 그런 생각이 듭니다." << endl;
			cout << "아이기스 : 생명이란...어디서 오고, 어디로 사라지는 건가요?" << endl;
			cout << "아이기스 : 무엇을 위해, 생명이 있는 거죠?" << endl;
			cout << "아이기스 : 생명이 있다는 것은 언젠가 죽는다는 것." << endl;
			cout << "아이기스 : 저에게도...언젠가 마코토 님과 영원히 이별하는 날이 오는 걸까요...?" << endl;
			cout << "아이기스 : ...죄송해요. 저도 뭘 하고 싶은 건지 모르겠어서..." << endl;
			cout << "아이기스 : 기숙사로 돌아가죠!" << endl;
			entity->SetLikeability(entity->GetLikeability() + 1);
		}
		else if (entity->GetLikeability() == 2) {
			cout << "아이기스 : 전에 한 질문에 대해서 많이 생각해 봤어요." << endl;
			cout << "아이기스 : 저는 역시 인간이 아니라 기계에요." << endl;
			cout << "아이기스 : 전에는 그걸 후카님이나 다른 분들과 비교하며 분하다고 생각했는데..." << endl;
			cout << "아이기스 : 지금은 기계인 저니까 해드릴 수 있는게 있다고 느꼈어요." << endl;
			cout << "아이기스 : 저는...당신을 절대로 혼자 두지 않겠어요." << endl;
			cout << "아이기스 : 설령 당신의 생명이 끝날 때가 언제 어떤 식으로 찾아오더라도..." << endl;
			cout << "아이기스 : 저는 반드시 당신 곁에 있을게요." << endl;
			entity->SetLikeability(entity->GetLikeability() + 1);
		}
		else {
			cout << "아이기스 : 옥상에는 경치가 잘 보이니까 마음이 편해지네요." << endl;
			entity->SetLikeability(entity->GetLikeability() + 1);
		}

		gameWorld->Message2Makoto("Aegis_InteractComplete");
		entity->progressTime();
		return Success;
	}
};

//타르타로스 전투 액션 노드
class Aegis_Action_Tartarus : public BehaviorNode<Aegis> {
	BehaviorStatus Tick(Aegis* entity) override {
		cout << "아이기스 : 타겟을 무력화했습니다!" << endl;
		cout << "아이기스 : 레벨 업! 입니다." << endl;
		entity->SetLevel(entity->GetLevel() + 1);

		gameWorld->Message2Makoto("Aegis_InteractComplete");
		entity->progressTime();
		return Success;
	}
};

//==================노드 생성 함수=========================
//시퀀스 노드 생성 함수
SequenceNode<Aegis>* MakeSequence(BehaviorNode<Aegis>* action) {
	SequenceNode<Aegis>* sequence = new SequenceNode<Aegis>();
	sequence->AddChild(action);
	return sequence;
}

//셀렉터 노드 생성 함수
SelectorNode<Aegis>* MakeSelector(BehaviorNode<Aegis>* action) {
	SelectorNode<Aegis>* selector = new SelectorNode<Aegis>();
	selector->AddChild(action);
	return selector;
}

BehaviorNode<Aegis>* CreateAegisBehaviorTree() {
	SelectorNode<Aegis>* root = new SelectorNode<Aegis>();

	//============================행동 트리 구성===========================
	//커뮤니케이션 행동(시퀀스 행동)
	SequenceNode<Aegis>* communicationSequence = MakeSequence(new ConditionNode<Aegis>(IsInteractionable));
	communicationSequence->AddChild(new Aegis_Action_WaitForYuki());
	communicationSequence->AddChild(new Aegis_Action_YukiInteraction());
	
	//통상 행동 서브 트리
	SelectorNode<Aegis>* normalBehavior = new SelectorNode<Aegis>();
	normalBehavior->AddChild(communicationSequence);
	normalBehavior->AddChild(new Aegis_Action_TimeSpent());

	//요일 감지(시퀀스 노드)
	SequenceNode<Aegis>* dayDetectionSequence = MakeSequence(new ConditionNode<Aegis>(IsSunday));
	dayDetectionSequence->AddChild(normalBehavior);
	
	//평일 루틴(시퀀스 노드)
	SequenceNode<Aegis>* weekdaySequence = new SequenceNode<Aegis>();
	weekdaySequence->AddChild(new Aegis_Action_WakeUp());
	weekdaySequence->AddChild(new Aegis_Action_School());

	//요일 분기(셀렉터 노드)
	SelectorNode<Aegis>* daySelector = new SelectorNode<Aegis>();
	daySelector->AddChild(dayDetectionSequence);
	daySelector->AddChild(weekdaySequence);

	//아침 행동(시퀀스 노드)
	SequenceNode<Aegis>* morningSequence = MakeSequence(new ConditionNode<Aegis>(IsMorning));
	morningSequence->AddChild(daySelector);

	//방과후 행동(시퀀스 노드)
	SequenceNode<Aegis>* afternoonSequence = MakeSequence(new ConditionNode<Aegis>(IsAfternoon));
	afternoonSequence->AddChild(normalBehavior);

	//타르타로스(시퀀스 노드)
	SequenceNode<Aegis>* tartarusSequence = MakeSequence(new ConditionNode<Aegis>(IsInteractionable));
	tartarusSequence->AddChild(new Aegis_Action_WaitForYuki());
	tartarusSequence->AddChild(new Aegis_Action_Tartarus());

	//행동 분기(셀렉터 노드)(시간 보내기만 추가)
	SelectorNode<Aegis>* actionSelector = new SelectorNode<Aegis>();
	actionSelector->AddChild(tartarusSequence);
	actionSelector->AddChild(new Aegis_Action_TimeSpent());

	//밤 행동(시퀀스 노드)
	SequenceNode<Aegis>* eveningSequence = MakeSequence(new ConditionNode<Aegis>(IsEvening));
	eveningSequence->AddChild(actionSelector);

	//심야 행동(시퀀스 노드)
	SequenceNode<Aegis>* nightSequence = MakeSequence(new ConditionNode<Aegis>(IsNight));
	nightSequence->AddChild(new Aegis_Action_Sleep());

	//Root 노드에 추가
	root->AddChild(morningSequence);
	root->AddChild(afternoonSequence);
	root->AddChild(eveningSequence);
	root->AddChild(nightSequence);

	return root;
};