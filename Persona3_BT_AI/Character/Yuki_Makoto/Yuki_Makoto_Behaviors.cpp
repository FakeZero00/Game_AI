#include "Yuki_Makoto_Behaviors.h"
#include "Yuki_Makoto.h"
#include <iostream>
#include <random>
using namespace std;

extern GameWorld* gameWorld; // 게임 월드 객체에 대한 전역 포인터

//==================컨디션 노드용 판정 함수=========================
//시간 감지(아침)
bool IsMorning(Yuki_Makoto* entity) {
	return entity->currentTime == DayTime::Morning;
}

bool IsAfternoon(Yuki_Makoto* entity) {
	return entity->currentTime == DayTime::Afternoon;
}

bool IsEvening(Yuki_Makoto* entity) {
	return entity->currentTime == DayTime::Evening;
}

bool IsNight(Yuki_Makoto* entity) {
	return entity->currentTime == DayTime::Night;
}

bool IsSunday(Yuki_Makoto* entity) {
	return entity->currentDay == Day::Sunday;
}

bool IsBothInteractionable(Yuki_Makoto* entity) {
	if (entity->currentTime == DayTime::Morning || entity->currentTime == DayTime::Afternoon) {
		return (entity->aegisInteractionSiganl != -1 && entity->aegisInteractionSiganl != 0) &&
			(entity->yamagishiInteractionSignal != -1 && entity->yamagishiInteractionSignal != 0);
	}
	else {
		if ((entity->aegisInteractionSiganl != -1 && entity->aegisInteractionSiganl != 0) &&
			(entity->yamagishiInteractionSignal != -1 && entity->yamagishiInteractionSignal != 0)) {
			cout << "모두와 함께 타르타로스에 가기로 했다." << endl;
			gameWorld->Message2Aegis("Selected");
			gameWorld->Message2Yamagishi("Selected");
			return true;
		}
		else {
			gameWorld->Message2Aegis("Unselected");
			gameWorld->Message2Yamagishi("Unselected");
			return false;
		}
	}
}

bool IsAegisInteractionable(Yuki_Makoto* entity) {
	//cout << "아이기스와 상호작용 가능한지 확인 중... : " << entity->aegisInteractionSiganl << endl;
	if (entity->aegisInteractionSiganl != -1 && entity->aegisInteractionSiganl != 0) {
		if (entity->aegisInteractionSiganl == 1) {
			if (entity->currentTime == DayTime::Afternoon) cout << "아이기스와 시간을 보내기로 했다." << endl;
			else if (entity->currentTime == DayTime::Evening) cout << "아이기스와 타르타로스에 가기로 했다." << endl;
			gameWorld->Message2Aegis("Selected");
			gameWorld->Message2Yamagishi("Unselected");
		}
		return true;
	};
	return false;
}

bool IsYamagishiInteractionable(Yuki_Makoto* entity) {
	//cout << "야마기시 후카와 상호작용 가능한지 확인 중... : " << entity->yamagishiInteractionSignal << endl;
	if (entity->yamagishiInteractionSignal != -1 && entity->yamagishiInteractionSignal != 0) {
		if (entity->yamagishiInteractionSignal == 1) {
			if (entity->currentTime == DayTime::Afternoon) cout << "야마기시 후카와 시간을 보내기로 했다." << endl;
			else if (entity->currentTime == DayTime::Evening) cout << "야마기시 후카와 타르타로스에 가기로 했다." << endl;
			gameWorld->Message2Aegis("Unselected");
			gameWorld->Message2Yamagishi("Selected");
		}
		return true;
	};
	return false;
}

//==================액션 노드 클래스=========================

//기상 & 등교 액션 노드
class Yuki_Action_WakeUp : public BehaviorNode<Yuki_Makoto> {
public:
	BehaviorStatus Tick(Yuki_Makoto* entity) override {
		if (entity->currentDay != Day::Sunday) {
			cout << "아침이 밝았다. 기숙사에서 나와서 학교로 가자." << endl;
			cout << "기숙사에서 학교로 왔다. 수업을 들을 준비를 하자." << endl;
		}
		else {
			cout << "아침이 밝았다. 오늘은 일요일이라 학교를 가지 않아도 된다." << endl;
		}
		
		return Success;
	}
};

//학교 수업 액션 노드
class Yuki_Action_School : public BehaviorNode<Yuki_Makoto> {
private:
	//랜덤 엔진
	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urd{ 0.0f, 1.0f };

public:
	BehaviorStatus Tick(Yuki_Makoto* entity) override {
		float rand = urd(dre);
		if (rand < 0.3f) {
			cout << "수업 중에 졸았지만, 들키지 않았다! 용기가 상승했다" << endl;
			entity->SetBrave(entity->GetBrave() + 1);
		}
		else {
			cout << "졸지 않고 수업을 성실히 들었다. 지혜가 상승했다" << endl;
			entity->SetWisdom(entity->GetWisdom() + 1);
		}

		entity->progressTime();
		return Success;
	}
};

//랜덤 선택 액션 노드
class Yuki_Action_RandomChoice : public BehaviorNode<Yuki_Makoto> {
private:
	//랜덤 엔진
	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urd{ 0.0f, 1.0f };

public:
	BehaviorStatus Tick(Yuki_Makoto* entity) override {
		entity->tempRand = urd(dre);
		return Success;
	}
};

//카페 샤갈 액션 노드
class Yuki_Action_CafeShagal : public BehaviorNode<Yuki_Makoto> {
public:
	BehaviorStatus Tick(Yuki_Makoto* entity) override {
		if (entity->tempRand < 0.3f) {
			cout << "커피를 마시며 여유를 즐겼다. 주변에서 시선을 받는 느낌이 든다." << endl;
			cout << "매력이 상승했다." << endl;
			entity->SetCharm(entity->GetCharm() + 1);

			entity->progressTime();
			return Success;
		}
		return Failure;
	}
};

//노래방 액션 노드
class Yuki_Action_Karaoke : public BehaviorNode<Yuki_Makoto> {
public:
	BehaviorStatus Tick(Yuki_Makoto* entity) override {
		if (entity->tempRand < 0.6f) {
			cout << "노래방에서 혼자 노래를 불렀다. 혼자라 그런지 끝까지 부를 수 있었다." << endl;
			cout << "용기가 상승했다." << endl;
			entity->SetBrave(entity->GetBrave() + 1);

			entity->progressTime();
			return Success;
		}
		return Failure;
	}
};

//공부하기 액션 노드
class Yuki_Action_Study : public BehaviorNode<Yuki_Makoto> {
public:
	BehaviorStatus Tick(Yuki_Makoto* entity) override {
		cout << "공부를 했다." << endl;
		cout << "지혜가 상승했다." << endl;
		entity->SetWisdom(entity->GetWisdom() + 1);

		entity->progressTime();
		return Success;
	}
};

//취침 액션 노드
class Yuki_Action_Sleep : public BehaviorNode<Yuki_Makoto> {
public:
	BehaviorStatus Tick(Yuki_Makoto* entity) override {
		cout << "잠자는 중..." << endl;

		entity->progressTime();
		return Success;
	}
};

//랜덤 상호작용 액션 노드
class Yuki_Action_RandomInteraction : public BehaviorNode<Yuki_Makoto> {
	BehaviorStatus Tick(Yuki_Makoto* entity) override {
		if (entity->aegisInteractionSiganl == 1 && entity->yamagishiInteractionSignal == 1) {
			if (entity->tempRand < 0.5f) {
				cout << "아이기스와 시간을 보내기로 했다." << endl;
				gameWorld->Message2Aegis("Selected");
				gameWorld->Message2Yamagishi("Unselected");
			}
			else {
				cout << "후카와 시간을 보내기로 했다." << endl;
				gameWorld->Message2Aegis("Unselected");
				gameWorld->Message2Yamagishi("Selected");
			}

			return Success;
		}
		else return Failure;
	}
};

//아이기스 상호작용 액션 노드
class Yuki_Action_AegisInteraction : public BehaviorNode<Yuki_Makoto> {
	BehaviorStatus Tick(Yuki_Makoto* entity) override {
		if (entity->aegisInteractionSiganl == 2) {
			cout << "아이기스와 얘기를 하고 있다..." << endl;
			return Running;
		}
		else if (entity->aegisInteractionSiganl == 3) {
			cout << "아이기스와 얘기를 했다. 아이기스와의 관계가 깊어진 기분이 든다." << endl;
			entity->aegisInteractionSiganl = -1; // 신호 초기화

			entity->progressTime();
			return Success;
		}
		else return Failure;
	}
};

//야마기시 후카 상호작용 액션 노드
class Yuki_Action_YamagishiInteraction : public BehaviorNode<Yuki_Makoto> {
	BehaviorStatus Tick(Yuki_Makoto* entity) override {
		if (entity->yamagishiInteractionSignal == 2) {
			cout << "야마기시 후카와 얘기를 하고 있다..." << endl;
			return Running;
		}
		else if (entity->yamagishiInteractionSignal == 3) {
			cout << "후카와 얘기를 했다. 야마기시 후카와의 관계가 깊어진 기분이 든다." << endl;
			entity->yamagishiInteractionSignal = -1; // 신호 초기화

			entity->progressTime();
			return Success;
		}
		else return Failure;
	}
};

//타르타로스 전투 액션 노드
class Yuki_Action_Tartarus : public BehaviorNode<Yuki_Makoto> {
	BehaviorStatus Tick(Yuki_Makoto* entity) override {
		if (entity->aegisInteractionSiganl == 2) {
			cout << "타르타로스에서 전투중!" << endl;
			return Running;
		}
		else if (entity->aegisInteractionSiganl == 3) {
			cout << "마음 속에서 페르소나가 성장하는게 느껴진다." << endl;
			cout << "레벨이 상승했다." << endl;
			entity->SetLevel(entity->GetLevel() + 1);
			entity->aegisInteractionSiganl = -1; // 신호 초기화
			entity->yamagishiInteractionSignal = -1; // 신호 초기화

			entity->progressTime();
			return Success;
		}
	}
};

//==================노드 생성 함수=========================
//시퀀스 노드 생성 함수
SequenceNode<Yuki_Makoto>* MakeSequence(BehaviorNode<Yuki_Makoto>* action) {
	SequenceNode<Yuki_Makoto>* sequence = new SequenceNode<Yuki_Makoto>();
	sequence->AddChild(action);
	return sequence;
}

//셀렉터 노드 생성 함수
SelectorNode<Yuki_Makoto>* MakeSelector(BehaviorNode<Yuki_Makoto>* action) {
	SelectorNode<Yuki_Makoto>* selector = new SelectorNode<Yuki_Makoto>();
	selector->AddChild(action);
	return selector;
}

BehaviorNode<Yuki_Makoto>* CreateYukiMakotoBehaviorTree() {
	SelectorNode<Yuki_Makoto>* root = new SelectorNode<Yuki_Makoto>();

	//============================행동 트리 구성===========================
	//스테이터스 행동 랜덤 선택 분기(셀렉터 노드)
	SelectorNode<Yuki_Makoto>* statusRandomSelector = new SelectorNode<Yuki_Makoto>();
	statusRandomSelector->AddChild(new Yuki_Action_CafeShagal());
	statusRandomSelector->AddChild(new Yuki_Action_Karaoke());
	statusRandomSelector->AddChild(new Yuki_Action_Study());

	//아이기스, 후카 랜덤 선택 분기(셀렉터 노드)
	SelectorNode<Yuki_Makoto>* randomInteractionSelector = new SelectorNode<Yuki_Makoto>();
	randomInteractionSelector->AddChild(new Yuki_Action_RandomInteraction());
	randomInteractionSelector->AddChild(new Yuki_Action_AegisInteraction());
	randomInteractionSelector->AddChild(new Yuki_Action_YamagishiInteraction());

	//커뮤니케이션 랜덤 선택 분기(시퀀스 노드)
	SequenceNode<Yuki_Makoto>* randomInteraction = new SequenceNode<Yuki_Makoto>();
	randomInteraction->AddChild(new Yuki_Action_RandomChoice());
	randomInteraction->AddChild(randomInteractionSelector);

	//아이기스, 후카 동시 감지(시퀀스 노드)
	SequenceNode<Yuki_Makoto>* bothDetection = MakeSequence(new ConditionNode<Yuki_Makoto>(IsBothInteractionable));
	bothDetection->AddChild(randomInteraction);

	//아이기스 감지(시퀀스 노드)
	SequenceNode<Yuki_Makoto>* aegisDetection = MakeSequence(new ConditionNode<Yuki_Makoto>(IsAegisInteractionable));
	aegisDetection->AddChild(new Yuki_Action_AegisInteraction());

	//후카 감지(시퀀스 노드)
	SequenceNode<Yuki_Makoto>* yamagishiDetection = MakeSequence(new ConditionNode<Yuki_Makoto>(IsYamagishiInteractionable));
	yamagishiDetection->AddChild(new Yuki_Action_YamagishiInteraction());

	//커뮤니케이션 행동 가능 여부 분기(셀렉터 노드)
	SelectorNode<Yuki_Makoto>* communicationSelector = new SelectorNode<Yuki_Makoto>();
	communicationSelector->AddChild(bothDetection);
	communicationSelector->AddChild(aegisDetection);
	communicationSelector->AddChild(yamagishiDetection);

	//스테이터스 행동 서브 트리
	SequenceNode<Yuki_Makoto>* statusBehavior = new SequenceNode<Yuki_Makoto>();
	statusBehavior->AddChild(new Yuki_Action_RandomChoice());
	statusBehavior->AddChild(statusRandomSelector);

	//통상 행동 서브 트리
	SelectorNode<Yuki_Makoto>* normalBehavior = new SelectorNode<Yuki_Makoto>();
	normalBehavior->AddChild(communicationSelector);
	normalBehavior->AddChild(statusBehavior);
	
	//요일 감지(시퀀스 노드)
	SequenceNode<Yuki_Makoto>* dayDetection = MakeSequence(new ConditionNode<Yuki_Makoto>(IsSunday));
	dayDetection->AddChild(normalBehavior);

	//평일 루틴(시퀀스 노드)
	SequenceNode<Yuki_Makoto>* weekdaySequence = new SequenceNode<Yuki_Makoto>();
	weekdaySequence->AddChild(new Yuki_Action_WakeUp());
	weekdaySequence->AddChild(new Yuki_Action_School());

	//요일 분기(셀렉터 노드)
	SelectorNode<Yuki_Makoto>* daySelector = new SelectorNode<Yuki_Makoto>();
	daySelector->AddChild(dayDetection);
	daySelector->AddChild(weekdaySequence);

	//아침 행동(시퀀스 노드)
	SequenceNode<Yuki_Makoto>* morningSequence = MakeSequence(new ConditionNode<Yuki_Makoto>(IsMorning));
	morningSequence->AddChild(daySelector);

	//방과후 행동(시퀀스 노드)
	SequenceNode<Yuki_Makoto>* afternoonSequence = MakeSequence(new ConditionNode<Yuki_Makoto>(IsAfternoon));
	afternoonSequence->AddChild(normalBehavior);

	//타르타로스(시퀀스 노드)
	SequenceNode<Yuki_Makoto>* tartarusSequence = MakeSequence(new ConditionNode<Yuki_Makoto>(IsBothInteractionable));
	tartarusSequence->AddChild(new Yuki_Action_Tartarus());

	//행동 분기(셀렉터 노드)
	SelectorNode<Yuki_Makoto>* actionSelector = new SelectorNode<Yuki_Makoto>();
	actionSelector->AddChild(tartarusSequence);
	actionSelector->AddChild(statusBehavior);

	//밤 행동(시퀀스 노드)
	SequenceNode<Yuki_Makoto>* eveningSequence = MakeSequence(new ConditionNode<Yuki_Makoto>(IsEvening));
	eveningSequence->AddChild(actionSelector);

	//심야 행동(시퀀스 노드)
	SequenceNode<Yuki_Makoto>* nightSequence = MakeSequence(new ConditionNode<Yuki_Makoto>(IsNight));
	nightSequence->AddChild(new Yuki_Action_Sleep());

	//Root 노드에 추가
	root->AddChild(morningSequence);
	root->AddChild(afternoonSequence);
	root->AddChild(eveningSequence);
	root->AddChild(nightSequence);

	return root;
};