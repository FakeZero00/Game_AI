#include "Yamagishi_Fuka_States.h"

#include <iostream>
#include "Yamagishi_Fuka.h"
#include "GlobalState.h"
#include "Day.h"
#include "DayTime.h"
using namespace std;

//==================================취침 상태==============================
Yamagishi_Fuka_State_Sleeping* Yamagishi_Fuka_State_Sleeping::Instance() {
	static Yamagishi_Fuka_State_Sleeping instance;
	return &instance;
}

void Yamagishi_Fuka_State_Sleeping::Enter(Yamagishi_Fuka* entity) {}

void Yamagishi_Fuka_State_Sleeping::Execute(Yamagishi_Fuka* entity) {
	Yamagishi_Fuka_GlobalState* globalState = static_cast<Yamagishi_Fuka_GlobalState*>(entity->GetFSM()->GetGlobalState());
	// 취침 상태에서 실행될 로직
	cout << "야마기시 후카 : ...ZZZZ" << endl;
	globalState->CallTimeSignal();

	Day nextDay = static_cast<Day>((static_cast<int>(globalState->GetCurrentDay()) + 1) % 7);

	if (nextDay != Day::Sunday) entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_WakeUp::Instance());
	else entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_InteractionWait::Instance());
}

void Yamagishi_Fuka_State_Sleeping::Exit(Yamagishi_Fuka* entity) {}

//==================================기상 상태==============================
Yamagishi_Fuka_State_WakeUp* Yamagishi_Fuka_State_WakeUp::Instance() {
	static Yamagishi_Fuka_State_WakeUp instance;
	return &instance;
}

void Yamagishi_Fuka_State_WakeUp::Enter(Yamagishi_Fuka* entity) {}

void Yamagishi_Fuka_State_WakeUp::Execute(Yamagishi_Fuka* entity) {
	Yamagishi_Fuka_GlobalState* globalState = static_cast<Yamagishi_Fuka_GlobalState*>(entity->GetFSM()->GetGlobalState());

	if (globalState->GetCurrentDay() != Day::Sunday) {
		cout << "야마기시 후카 : 아침이네. 학교에 갈 준비를 하자." << endl;
		cout << "야마기시 후카 : 학교에 도착! 오늘 수업은..." << endl;
		entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_School::Instance());
	}
	else {
		cout << "야마기시 후카 : 아침이 밝았지만...오늘은 볼일이 있었지." << endl;
		entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_InteractionWait::Instance());
	}
}

void Yamagishi_Fuka_State_WakeUp::Exit(Yamagishi_Fuka* entity) {}

//============================학교 수업 상태==============================

Yamagishi_Fuka_State_School* Yamagishi_Fuka_State_School::Instance() {
	static Yamagishi_Fuka_State_School instance;
	return &instance;
}

void Yamagishi_Fuka_State_School::Enter(Yamagishi_Fuka* entity) {}

void Yamagishi_Fuka_State_School::Execute(Yamagishi_Fuka* entity) {
	Yamagishi_Fuka_GlobalState* globalState = static_cast<Yamagishi_Fuka_GlobalState*>(entity->GetFSM()->GetGlobalState());

	cout << "야마기시 후카 : (수업 듣는 중)" << endl;

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_InteractionWait::Instance());
}

void Yamagishi_Fuka_State_School::Exit(Yamagishi_Fuka* entity) {}

//============================상호작용 대기 상태==============================

Yamagishi_Fuka_State_InteractionWait* Yamagishi_Fuka_State_InteractionWait::Instance() {
	static Yamagishi_Fuka_State_InteractionWait instance;
	return &instance;
}

void Yamagishi_Fuka_State_InteractionWait::Enter(Yamagishi_Fuka* entity) {}

void Yamagishi_Fuka_State_InteractionWait::Execute(Yamagishi_Fuka* entity) {
	Yamagishi_Fuka_GlobalState* globalState = static_cast<Yamagishi_Fuka_GlobalState*>(entity->GetFSM()->GetGlobalState());

	if (globalState->GetCurrentTime() == DayTime::Morning) {
		cout << "야마기시 후카 : 아침이 밝았지만...오늘은 볼일이 있었지." << endl;
		entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_BehaviorWait::Instance());
	}
	else if (globalState->GetCurrentTime() == DayTime::Afternoon) {
		if (globalState->GetCurrentDay() == Day::Monday ||
			globalState->GetCurrentDay() == Day::Friday ||
			globalState->GetCurrentDay() == Day::Saturday) {
			cout << "야마기시 후카 : 수업이 끝났네. 마코토와 시간을 보내고 싶은데..." << endl;
			gameWorld->Message2Makoto("Yamagishi_Fuka_Interactable");
			entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_BehaviorWait::Instance());
		}
		else {
			cout << "야마기시 후카 : 수업이 끝났네...오늘은 용무가 있었지." << endl;
			entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_TimeSpent::Instance());
		}
	}
	else if (globalState->GetCurrentTime() == DayTime::Evening) {
		if (globalState->GetCurrentDay() == Day::Monday ||
			globalState->GetCurrentDay() == Day::Friday ||
			globalState->GetCurrentDay() == Day::Saturday) {
			cout << "야마기시 후카 : 섀도우 타임이 올 거야. 오늘은 타르타로스에 갈 거야?" << endl;
			gameWorld->Message2Makoto("Yamagishi_Fuka_Interactable");
			entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_NightBehaviorWait::Instance());
		}
		else {
			cout << "야마기시 후카 : 오늘은 저녁까지 볼 일이 있어서 타르타로스는 쉬어 줘." << endl;
			entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_TimeSpent::Instance());
		}
	}
	else if (globalState->GetCurrentTime() == DayTime::Night) {
		cout << "야마기시 후카 : 밤이 깊었네. 기숙사로 돌아가야지." << endl;
		entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_Sleeping::Instance());
	}
}

void Yamagishi_Fuka_State_InteractionWait::Exit(Yamagishi_Fuka* entity) {
	Yamagishi_Fuka_GlobalState* globalState = static_cast<Yamagishi_Fuka_GlobalState*>(entity->GetFSM()->GetGlobalState());
}

//==================아침 or 방과 후 상호작용 대기 상태========================

Yamagishi_Fuka_State_BehaviorWait* Yamagishi_Fuka_State_BehaviorWait::Instance() {
	static Yamagishi_Fuka_State_BehaviorWait instance;
	return &instance;
}

void Yamagishi_Fuka_State_BehaviorWait::Enter(Yamagishi_Fuka* entity) {}

void Yamagishi_Fuka_State_BehaviorWait::Execute(Yamagishi_Fuka* entity) {
	Yamagishi_Fuka_GlobalState* globalState = static_cast<Yamagishi_Fuka_GlobalState*>(entity->GetFSM()->GetGlobalState());

	if (globalState->GetYukiInteractionSignal()) {
		cout << "야마기시 후카 : 정말? 그럼 빨리 가자." << endl;
		globalState->SetYukiInteractionSignal(false);
		entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_YukiInteraction::Instance());
	}
	else {
		cout << "야마기시 후카 : 마코토, 바빠 보이네...어쩔 수 없지." << endl;
		entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_TimeSpent::Instance());
	}
}

void Yamagishi_Fuka_State_BehaviorWait::Exit(Yamagishi_Fuka* entity) {}

//==================유키 마코토와 상호작용 상태========================

Yamagishi_Fuka_State_YukiInteraction* Yamagishi_Fuka_State_YukiInteraction::Instance() {
	static Yamagishi_Fuka_State_YukiInteraction instance;
	return &instance;
}

void Yamagishi_Fuka_State_YukiInteraction::Enter(Yamagishi_Fuka* entity) {}

void Yamagishi_Fuka_State_YukiInteraction::Execute(Yamagishi_Fuka* entity) {
	Yamagishi_Fuka_GlobalState* globalState = static_cast<Yamagishi_Fuka_GlobalState*>(entity->GetFSM()->GetGlobalState());

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

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_InteractionWait::Instance());
}

void Yamagishi_Fuka_State_YukiInteraction::Exit(Yamagishi_Fuka* entity) {}

//====================밤 상호작용 선택 상태============================

Yamagishi_Fuka_State_NightBehaviorWait* Yamagishi_Fuka_State_NightBehaviorWait::Instance() {
	static Yamagishi_Fuka_State_NightBehaviorWait instance;
	return &instance;
}

void Yamagishi_Fuka_State_NightBehaviorWait::Enter(Yamagishi_Fuka* entity) {}

void Yamagishi_Fuka_State_NightBehaviorWait::Execute(Yamagishi_Fuka* entity) {
	Yamagishi_Fuka_GlobalState* globalState = static_cast<Yamagishi_Fuka_GlobalState*>(entity->GetFSM()->GetGlobalState());

	if (globalState->GetYukiInteractionSignal()) {
		cout << "야마기시 후카 : 알겠어. 그럼 모두에게 전해놓을게!" << endl;
		globalState->SetYukiInteractionSignal(false);
		entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_TartarosBattle::Instance());
	}
	else {
		cout << "오늘은 안되는 모양이네...그럼 나도 적당히 시간을 보내볼까." << endl;
		entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_TimeSpent::Instance());
	}
}

void Yamagishi_Fuka_State_NightBehaviorWait::Exit(Yamagishi_Fuka* entity) {}

//====================타르타로스 전투 상태============================

Yamagishi_Fuka_State_TartarosBattle* Yamagishi_Fuka_State_TartarosBattle::Instance() {
	static Yamagishi_Fuka_State_TartarosBattle instance;
	return &instance;
}

void Yamagishi_Fuka_State_TartarosBattle::Enter(Yamagishi_Fuka* entity) {}

void Yamagishi_Fuka_State_TartarosBattle::Execute(Yamagishi_Fuka* entity) {
	Yamagishi_Fuka_GlobalState* globalState = static_cast<Yamagishi_Fuka_GlobalState*>(entity->GetFSM()->GetGlobalState());
	globalState->SetYukiInteractionSignal(false);

	cout << "야마기시 후카 : 적의 약점을 찾았어!" << endl;
	cout << "야마기시 후카 : 레벨이 올랐어!" << endl;
	entity->SetLevel(entity->GetLevel() + 1);

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_InteractionWait::Instance());
}

void Yamagishi_Fuka_State_TartarosBattle::Exit(Yamagishi_Fuka* entity) {}

//========================시간 보내기 상태============================

Yamagishi_Fuka_State_TimeSpent* Yamagishi_Fuka_State_TimeSpent::Instance() {
	static Yamagishi_Fuka_State_TimeSpent instance;
	return &instance;
}

void Yamagishi_Fuka_State_TimeSpent::Enter(Yamagishi_Fuka* entity) {}

void Yamagishi_Fuka_State_TimeSpent::Execute(Yamagishi_Fuka* entity) {
	Yamagishi_Fuka_GlobalState* globalState = static_cast<Yamagishi_Fuka_GlobalState*>(entity->GetFSM()->GetGlobalState());

	cout << "후카는 시간을 보내고 있다." << endl;

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Yamagishi_Fuka_State_InteractionWait::Instance());
}

void Yamagishi_Fuka_State_TimeSpent::Exit(Yamagishi_Fuka* entity) {}