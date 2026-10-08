#include "Yamagishi_Fuka_Behaviors.h"
#include "Yamagishi_Fuka.h"
#include <iostream>
#include <random>
using namespace std;

extern GameWorld* gameWorld; // 게임 월드 객체에 대한 전역 포인터

//==================컨디션 노드용 판정 함수=========================
//시간 감지(아침)
bool IsMorning(Yamagishi_Fuka* entity) {
	return entity->currentTime == DayTime::Morning;
}

bool IsAfternoon(Yamagishi_Fuka* entity) {
	return entity->currentTime == DayTime::Afternoon;
}

bool IsEvening(Yamagishi_Fuka* entity) {
	return entity->currentTime == DayTime::Evening;
}

bool IsNight(Yamagishi_Fuka* entity) {
	return entity->currentTime == DayTime::Night;
}

bool IsSunday(Yamagishi_Fuka* entity) {
	return entity->currentDay == Day::Sunday;
}

bool IsInteractionable(Yamagishi_Fuka* entity) {
	return (entity->currentDay == Day::Monday ||
			entity->currentDay == Day::Friday ||
			entity->currentDay == Day::Saturday);
}

//==================액션 노드 클래스=========================

//기상 & 등교 액션 노드
class Yamagishi_Fuka_Action_WakeUp : public BehaviorNode<Yamagishi_Fuka> {
public:
	BehaviorStatus Tick(Yamagishi_Fuka* entity) override {
		entity->yukiInteractionSignal = -1; // 신호 초기화

		if (entity->currentDay != Day::Sunday) {
			cout << "야마기시 후카 : 아침이네. 학교에 갈 준비를 하자." << endl;
			cout << "야마기시 후카 : 학교에 도착! 오늘 수업은..." << endl;
		}
		else {
			cout << "야마기시 후카 : 아침이 밝았지만...오늘은 볼일이 있었지." << endl;
		}
		
		return Success;
	}
};

//학교 수업 액션 노드
class Yamagishi_Fuka_Action_School : public BehaviorNode<Yamagishi_Fuka> {
public:
	BehaviorStatus Tick(Yamagishi_Fuka* entity) override {
		cout << "야마기시 후카 : (수업 듣는 중)" << endl;

		entity->progressTime();
		return Success;
	}
};

//취침 액션 노드
class Yamagishi_Fuka_Action_Sleep : public BehaviorNode<Yamagishi_Fuka> {
public:
	BehaviorStatus Tick(Yamagishi_Fuka* entity) override {
		cout << "야마기시 후카 : ...ZZZZ" << endl;

		entity->progressTime();
		return Success;
	}
};

//시간 보내기 액션 노드
class Yamagishi_Fuka_Action_TimeSpent : public BehaviorNode<Yamagishi_Fuka> {
	BehaviorStatus Tick(Yamagishi_Fuka* entity) override {
		cout << "후카는 시간을 보내고 있다." << endl;
		entity->yukiInteractionSignal = -1; // 신호 초기화

		entity->progressTime();
		return Success;
	}
};

//유키 마코토 메시지 대기 액션 노드
class Yamagishi_Fuka_Action_WaitForYuki : public BehaviorNode<Yamagishi_Fuka> {
	BehaviorStatus Tick(Yamagishi_Fuka* entity) override {
		if (entity->currentTime == DayTime::Afternoon) {
			if (entity->yukiInteractionSignal == -1) {
				cout << "야마기시 후카 : 수업이 끝났네. 마코토와 시간을 보내고 싶은데..." << endl;
				cout << "(debug) 유키 마코토에게 상호작용 가능 메세지 송신" << endl;
				gameWorld->Message2Makoto("Yamagishi_Fuka_Interactable");
				return Running;
			}
			else if (entity->yukiInteractionSignal == 0) {
				cout << "야마기시 후카 : 마코토, 바빠 보이네...어쩔 수 없지." << endl;
				entity->yukiInteractionSignal = -1; // 신호 초기화
				return Failure;
			}
			else if (entity->yukiInteractionSignal == 1) {
				cout << "야마기시 후카 : 정말? 그럼 빨리 가자." << endl;
				gameWorld->Message2Makoto("Yamagishi_Fuka_Interact");
				cout << "(debug) 유키 마코토에게 상호작용 중 메세지 송신" << endl;
				entity->yukiInteractionSignal = -1; // 신호 초기화
				return Success;
			}
		}
		else if (entity->currentTime == DayTime::Evening) {
			if (entity->yukiInteractionSignal == -1) {
				cout << "야마기시 후카 : 섀도우 타임이 올 거야. 오늘은 타르타로스에 갈 거야?" << endl;
				cout << "(debug) 유키 마코토에게 상호작용 가능 메세지 송신" << endl;
				gameWorld->Message2Makoto("Yamagishi_Fuka_Interactable");
				return Running;
			}
			else if (entity->yukiInteractionSignal == 0) {
				cout << "야마기시 후카 : 마코토, 바빠 보이네...어쩔 수 없지." << endl;
				entity->yukiInteractionSignal = -1; // 신호 초기화
				return Failure;
			}
			else if (entity->yukiInteractionSignal == 1) {
				cout << "야마기시 후카 : 알겠어. 그럼 모두에게 전해놓을게!" << endl;
				gameWorld->Message2Makoto("Yamagishi_Fuka_Interact");
				cout << "(debug) 유키 마코토에게 상호작용 중 메세지 송신" << endl;
				entity->yukiInteractionSignal = -1; // 신호 초기화
				return Success;
			}
		}
	}
};

//유키 마코토와 상호작용 액션 노드
class Yamagishi_Fuka_Action_YukiInteraction : public BehaviorNode<Yamagishi_Fuka> {
	BehaviorStatus Tick(Yamagishi_Fuka* entity) override {
		if (entity->GetLikeability() == 0) {
			cout << "야마기시 후카 : 모두에게 은혜를 갚고 싶어서 말이야." << endl;
			cout << "야마기시 후카 : 그래서 요리라도 대접하려고 연습삼아 도시락을 만들어 봤는데..." << endl;
			cout << "야마기시 후카 : 먹어봐 줬으면 해서." << endl;
			cout << "야마기시 후카 : 어때...?" << endl;
			cout << "야마기시 후카 : (마코토가 다 먹기를 기다린다...마코토의 안색이 좋지 않다!)" << endl;
			cout << "야마기시 후카 : 괘, 괜찮아?! 으으...잘 안됬나봐." << endl;
			cout << "야마기시 후카 : 오늘은 심한 꼴을 당하게 해서 미안해..." << endl;
			cout << "야마기시 후카 : 다음엔 더 잘할 수 있을테니까...조금만 더 어울려 줄래?" << endl;
			entity->SetLikeability(entity->GetLikeability() + 1);
		}
		else if (entity->GetLikeability() == 1) {
			cout << "야마기시 후카 : 오늘도 도시락을 만들어왔으니까 한 번 먹어봐줘." << endl;
			cout << "야마기시 후카 : (마코토가 다 먹기를 기다린다...마코토의 표정이 좋다!)" << endl;
			cout << "야마기시 후카 : 맛있어? 다행이다! 이번엔도 잘 안되면 어쩌나 했거든." << endl;
			cout << "야마기시 후카 : 네 생각을 하면서 만들었더니 잘 됬나봐." << endl;
			cout << "야마기시 후카 : ...사실은 요리로 은혜를 갚는 건 그만하려고." << endl;
			cout << "야마기시 후카 : 요리에 흥미가 없어진 게 아니야! 그저..만들다 보니까 그런 생각이 들었어." << endl;
			cout << "야마기시 후카 : 내가 평소에 못하는 요리가 아니라 내가 잘 하는 걸로 답례를 하는게 맞는 것 같아." << endl;
			cout << "야마기시 후카 : 그래서 다음에 한 번 더 어울려 줄래? 주고 싶은게 있거든." << endl;
			entity->SetLikeability(entity->GetLikeability() + 1);
		}
		else if (entity->GetLikeability() == 2) {
			cout << "야마기시 후카 : 전에 내가 잘하는 걸로 은혜를 갚고 싶다고 했잖아." << endl;
			cout << "야마기시 후카 : 그래서 여기..." << endl;
			cout << "야마기시 후카 : (마코토에게 수제 이어폰을 건네준다.)" << endl;
			cout << "야마기시 후카 : 여자답지 않다고 생각할지도 모르겠지만, 역시 나는 이쪽이 더 나 답다고 생각해." << endl;
			cout << "야마기시 후카 : (이어폰을 사용하는 마코토의 표정이 좋다!)" << endl;
			cout << "야마기시 후카 : 후후, 기뻐해주는 것 같아서 다행이야." << endl;
			entity->SetLikeability(entity->GetLikeability() + 1);
		}
		else {
			cout << "야마기시 후카 : 이렇게 둘이서 시간을 보내는 것도 오랜만이네." << endl;
			entity->SetLikeability(entity->GetLikeability() + 1);
		}

		gameWorld->Message2Makoto("Yamagishi_Fuka_InteractComplete");
		entity->progressTime();
		return Success;
	}
};

//타르타로스 전투 액션 노드
class Yamagishi_Fuka_Action_Tartarus : public BehaviorNode<Yamagishi_Fuka> {
	BehaviorStatus Tick(Yamagishi_Fuka* entity) override {
		cout << "야마기시 후카 : 적의 약점을 찾았어!" << endl;
		cout << "야마기시 후카 : 레벨이 올랐어!" << endl;
		entity->SetLevel(entity->GetLevel() + 1);

		gameWorld->Message2Makoto("Yamagishi_Fuka_InteractComplete");
		entity->progressTime();
		return Success;
	}
};

//==================노드 생성 함수=========================
//시퀀스 노드 생성 함수
SequenceNode<Yamagishi_Fuka>* MakeSequence(BehaviorNode<Yamagishi_Fuka>* action) {
	SequenceNode<Yamagishi_Fuka>* sequence = new SequenceNode<Yamagishi_Fuka>();
	sequence->AddChild(action);
	return sequence;
}

//셀렉터 노드 생성 함수
SelectorNode<Yamagishi_Fuka>* MakeSelector(BehaviorNode<Yamagishi_Fuka>* action) {
	SelectorNode<Yamagishi_Fuka>* selector = new SelectorNode<Yamagishi_Fuka>();
	selector->AddChild(action);
	return selector;
}

BehaviorNode<Yamagishi_Fuka>* CreateYamagishiBehaviorTree() {
	SelectorNode<Yamagishi_Fuka>* root = new SelectorNode<Yamagishi_Fuka>();

	//============================행동 트리 구성===========================
	//커뮤니케이션 행동(시퀀스 행동)
	SequenceNode<Yamagishi_Fuka>* communicationSequence = MakeSequence(new ConditionNode<Yamagishi_Fuka>(IsInteractionable));
	communicationSequence->AddChild(new Yamagishi_Fuka_Action_WaitForYuki());
	communicationSequence->AddChild(new Yamagishi_Fuka_Action_YukiInteraction());
	
	//통상 행동 서브 트리
	SelectorNode<Yamagishi_Fuka>* normalBehavior = new SelectorNode<Yamagishi_Fuka>();
	normalBehavior->AddChild(communicationSequence);
	normalBehavior->AddChild(new Yamagishi_Fuka_Action_TimeSpent());

	//요일 감지(시퀀스 노드)
	SequenceNode<Yamagishi_Fuka>* dayDetectionSequence = MakeSequence(new ConditionNode<Yamagishi_Fuka>(IsSunday));
	dayDetectionSequence->AddChild(normalBehavior);
	
	//평일 루틴(시퀀스 노드)
	SequenceNode<Yamagishi_Fuka>* weekdaySequence = new SequenceNode<Yamagishi_Fuka>();
	weekdaySequence->AddChild(new Yamagishi_Fuka_Action_WakeUp());
	weekdaySequence->AddChild(new Yamagishi_Fuka_Action_School());

	//요일 분기(셀렉터 노드)
	SelectorNode<Yamagishi_Fuka>* daySelector = new SelectorNode<Yamagishi_Fuka>();
	daySelector->AddChild(dayDetectionSequence);
	daySelector->AddChild(weekdaySequence);

	//아침 행동(시퀀스 노드)
	SequenceNode<Yamagishi_Fuka>* morningSequence = MakeSequence(new ConditionNode<Yamagishi_Fuka>(IsMorning));
	morningSequence->AddChild(daySelector);

	//방과후 행동(시퀀스 노드)
	SequenceNode<Yamagishi_Fuka>* afternoonSequence = MakeSequence(new ConditionNode<Yamagishi_Fuka>(IsAfternoon));
	afternoonSequence->AddChild(normalBehavior);

	//타르타로스(시퀀스 노드)
	SequenceNode<Yamagishi_Fuka>* tartarusSequence = MakeSequence(new ConditionNode<Yamagishi_Fuka>(IsInteractionable));
	tartarusSequence->AddChild(new Yamagishi_Fuka_Action_WaitForYuki());
	tartarusSequence->AddChild(new Yamagishi_Fuka_Action_Tartarus());

	//행동 분기(셀렉터 노드)(시간 보내기만 추가)
	SelectorNode<Yamagishi_Fuka>* actionSelector = new SelectorNode<Yamagishi_Fuka>();
	actionSelector->AddChild(tartarusSequence);
	actionSelector->AddChild(new Yamagishi_Fuka_Action_TimeSpent());

	//밤 행동(시퀀스 노드)
	SequenceNode<Yamagishi_Fuka>* eveningSequence = MakeSequence(new ConditionNode<Yamagishi_Fuka>(IsEvening));
	eveningSequence->AddChild(actionSelector);

	//심야 행동(시퀀스 노드)
	SequenceNode<Yamagishi_Fuka>* nightSequence = MakeSequence(new ConditionNode<Yamagishi_Fuka>(IsNight));
	nightSequence->AddChild(new Yamagishi_Fuka_Action_Sleep());

	//Root 노드에 추가
	root->AddChild(morningSequence);
	root->AddChild(afternoonSequence);
	root->AddChild(eveningSequence);
	root->AddChild(nightSequence);

	return root;
};