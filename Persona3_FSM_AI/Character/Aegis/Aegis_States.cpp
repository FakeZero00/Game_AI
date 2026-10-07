#include "Aegis_States.h"

#include <iostream>
#include "Aegis.h"
#include "GlobalState.h"
#include "Day.h"
#include "DayTime.h"
using namespace std;

//==================================취침 상태==============================
Aegis_State_Sleeping* Aegis_State_Sleeping::Instance() {
	static Aegis_State_Sleeping instance;
	return &instance;
}

void Aegis_State_Sleeping::Enter(Aegis* entity) {}

void Aegis_State_Sleeping::Execute(Aegis* entity) {
	Aegis_GlobalState* globalState = static_cast<Aegis_GlobalState*>(entity->GetFSM()->GetGlobalState());
	// 취침 상태에서 실행될 로직
	cout << "아이기스 : 전원을 휴면 상태로 전환합니다." << endl;
	globalState->CallTimeSignal();

	Day nextDay = static_cast<Day>((static_cast<int>(globalState->GetCurrentDay()) + 1) % 7);

	if (nextDay != Day::Sunday) entity->GetFSM()->ChangeState(Aegis_State_WakeUp::Instance());
	else entity->GetFSM()->ChangeState(Aegis_State_InteractionWait::Instance());
}

void Aegis_State_Sleeping::Exit(Aegis* entity) {}

//==================================기상 상태==============================
Aegis_State_WakeUp* Aegis_State_WakeUp::Instance() {
	static Aegis_State_WakeUp instance;
	return &instance;
}

void Aegis_State_WakeUp::Enter(Aegis* entity) {}

void Aegis_State_WakeUp::Execute(Aegis* entity) {
	Aegis_GlobalState* globalState = static_cast<Aegis_GlobalState*>(entity->GetFSM()->GetGlobalState());

	if (globalState->GetCurrentDay() != Day::Sunday) {
		cout << "아이기스 : 아침이 됬습니다. 학교에 갈 준비를 합니다." << endl;
		cout << "아이기스 : 학교에 도착했습니다. 수업을 들을 준비를 합니다." << endl;
		entity->GetFSM()->ChangeState(Aegis_State_School::Instance());
	}
	else {
		cout << "아이기스 : 아침이 밝았지만...오늘은 용무가 있습니다." << endl;
		entity->GetFSM()->ChangeState(Aegis_State_InteractionWait::Instance());
	}
}

void Aegis_State_WakeUp::Exit(Aegis* entity) {}

//============================학교 수업 상태==============================

Aegis_State_School* Aegis_State_School::Instance() {
	static Aegis_State_School instance;
	return &instance;
}

void Aegis_State_School::Enter(Aegis* entity) {}

void Aegis_State_School::Execute(Aegis* entity) {
	Aegis_GlobalState* globalState = static_cast<Aegis_GlobalState*>(entity->GetFSM()->GetGlobalState());

	cout << "아이기스 : 수업을 듣고 있는 마코토님을 지켜봅니다." << endl;

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Aegis_State_InteractionWait::Instance());
}

void Aegis_State_School::Exit(Aegis* entity) {}

//============================상호작용 대기 상태==============================

Aegis_State_InteractionWait* Aegis_State_InteractionWait::Instance() {
	static Aegis_State_InteractionWait instance;
	return &instance;
}

void Aegis_State_InteractionWait::Enter(Aegis* entity) {}

void Aegis_State_InteractionWait::Execute(Aegis* entity) {
	Aegis_GlobalState* globalState = static_cast<Aegis_GlobalState*>(entity->GetFSM()->GetGlobalState());

	if (globalState->GetCurrentTime() == DayTime::Morning) {
		cout << "아이기스 : 아침이 밝았지만...오늘은 용무가 있습니다." << endl;
		entity->GetFSM()->ChangeState(Aegis_State_BehaviorWait::Instance());
	}
	else if (globalState->GetCurrentTime() == DayTime::Afternoon) {
		if (globalState->GetCurrentDay() == Day::Monday ||
			globalState->GetCurrentDay() == Day::Wednesday ||
			globalState->GetCurrentDay() == Day::Friday ||
			globalState->GetCurrentDay() == Day::Saturday) {
			cout << "아이기스 : 수업이 끝났습니다. 마코토님과 시간을 보내고 싶습니다만..." << endl;
			gameWorld->Message2Makoto("Aegis_Interactable");
			entity->GetFSM()->ChangeState(Aegis_State_BehaviorWait::Instance());
		}
		else {
			cout << "아이기스 : 수업이 끝났습니다...오늘은 용무가 있습니다." << endl;
			entity->GetFSM()->ChangeState(Aegis_State_TimeSpent::Instance());
		}
	}
	else if (globalState->GetCurrentTime() == DayTime::Evening) {
		if (globalState->GetCurrentDay() == Day::Monday ||
			globalState->GetCurrentDay() == Day::Wednesday ||
			globalState->GetCurrentDay() == Day::Friday ||
			globalState->GetCurrentDay() == Day::Saturday) {
			cout << "아이기스 : 섀도우 타임이 다가옵니다. 마코토님, 타르타로스에 가실 건가요?" << endl;
			gameWorld->Message2Makoto("Aegis_Interactable");
			entity->GetFSM()->ChangeState(Aegis_State_NightBehaviorWait::Instance());
		}
		else {
			cout << "아이기스 : 오늘은 저녁까지 용무가 있습니다." << endl;
			entity->GetFSM()->ChangeState(Aegis_State_TimeSpent::Instance());
		}
	}
	else if (globalState->GetCurrentTime() == DayTime::Night) {
		cout << "아이기스 : 밤이 깊었으니 휴면 상태로 들어가기 위해 기숙사로 돌아가겠습니다." << endl;
		entity->GetFSM()->ChangeState(Aegis_State_Sleeping::Instance());
	}
}

void Aegis_State_InteractionWait::Exit(Aegis* entity) {
	Aegis_GlobalState* globalState = static_cast<Aegis_GlobalState*>(entity->GetFSM()->GetGlobalState());
}

//==================아침 or 방과 후 상호작용 대기 상태========================

Aegis_State_BehaviorWait* Aegis_State_BehaviorWait::Instance() {
	static Aegis_State_BehaviorWait instance;
	return &instance;
}

void Aegis_State_BehaviorWait::Enter(Aegis* entity) {}

void Aegis_State_BehaviorWait::Execute(Aegis* entity) {
	Aegis_GlobalState* globalState = static_cast<Aegis_GlobalState*>(entity->GetFSM()->GetGlobalState());

	if (globalState->GetYukiInteractionSignal()) {
		cout << "아이기스 : 알겠습니다. 그럼 옥상으로 가죠." << endl;
		globalState->SetYukiInteractionSignal(false);
		entity->GetFSM()->ChangeState(Aegis_State_YukiInteraction::Instance());
	}
	else {
		cout << "마코토님이 바빠보이시니 저는 혼자 시간을 보내겠습니다." << endl;
		entity->GetFSM()->ChangeState(Aegis_State_TimeSpent::Instance());
	}
}

void Aegis_State_BehaviorWait::Exit(Aegis* entity) {}

//==================유키 마코토와 상호작용 상태========================

Aegis_State_YukiInteraction* Aegis_State_YukiInteraction::Instance() {
	static Aegis_State_YukiInteraction instance;
	return &instance;
}

void Aegis_State_YukiInteraction::Enter(Aegis* entity) {}

void Aegis_State_YukiInteraction::Execute(Aegis* entity) {
	Aegis_GlobalState* globalState = static_cast<Aegis_GlobalState*>(entity->GetFSM()->GetGlobalState());

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

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Aegis_State_InteractionWait::Instance());
}

void Aegis_State_YukiInteraction::Exit(Aegis* entity) {}

//====================밤 상호작용 선택 상태============================

Aegis_State_NightBehaviorWait* Aegis_State_NightBehaviorWait::Instance() {
	static Aegis_State_NightBehaviorWait instance;
	return &instance;
}

void Aegis_State_NightBehaviorWait::Enter(Aegis* entity) {}

void Aegis_State_NightBehaviorWait::Execute(Aegis* entity) {
	Aegis_GlobalState* globalState = static_cast<Aegis_GlobalState*>(entity->GetFSM()->GetGlobalState());

	if (globalState->GetYukiInteractionSignal()) {
		cout << "아이기스 : 알겠습니다. 타르타로스에 가죠!" << endl;
		globalState->SetYukiInteractionSignal(false);
		entity->GetFSM()->ChangeState(Aegis_State_TartarosBattle::Instance());
	}
	else {
		cout << "아이기스 : 마코토님이 바빠보이시니 저는 혼자 시간을 보내겠습니다." << endl;
		entity->GetFSM()->ChangeState(Aegis_State_TimeSpent::Instance());
	}
}

void Aegis_State_NightBehaviorWait::Exit(Aegis* entity) {}

//====================타르타로스 전투 상태============================

Aegis_State_TartarosBattle* Aegis_State_TartarosBattle::Instance() {
	static Aegis_State_TartarosBattle instance;
	return &instance;
}

void Aegis_State_TartarosBattle::Enter(Aegis* entity) {}

void Aegis_State_TartarosBattle::Execute(Aegis* entity) {
	Aegis_GlobalState* globalState = static_cast<Aegis_GlobalState*>(entity->GetFSM()->GetGlobalState());
	globalState->SetYukiInteractionSignal(false);

	cout << "아이기스 : 타겟을 무력화했습니다!" << endl;
	cout << "아이기스 : 레벨 업! 입니다." << endl;
	entity->SetLevel(entity->GetLevel() + 1);

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Aegis_State_InteractionWait::Instance());
}

void Aegis_State_TartarosBattle::Exit(Aegis* entity) {}

//========================시간 보내기 상태============================

Aegis_State_TimeSpent* Aegis_State_TimeSpent::Instance() {
	static Aegis_State_TimeSpent instance;
	return &instance;
}

void Aegis_State_TimeSpent::Enter(Aegis* entity) {}

void Aegis_State_TimeSpent::Execute(Aegis* entity) {
	Aegis_GlobalState* globalState = static_cast<Aegis_GlobalState*>(entity->GetFSM()->GetGlobalState());

	cout << "아이기스는 시간을 보내고 있다." << endl;

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Aegis_State_InteractionWait::Instance());
}

void Aegis_State_TimeSpent::Exit(Aegis* entity) {}