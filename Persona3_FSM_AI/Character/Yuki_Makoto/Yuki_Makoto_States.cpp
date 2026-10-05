#include "Yuki_Makoto_States.h"

#include <iostream>
#include "Yuki_Makoto.h"
#include "GlobalState.h"
#include "Day.h"
#include "DayTime.h"
using namespace std;

//==================================취침 상태==============================
Yuki_State_Sleeping* Yuki_State_Sleeping::Instance() {
	static Yuki_State_Sleeping instance;
	return &instance;
}

void Yuki_State_Sleeping::Enter(Yuki_Makoto* entity) {}

void Yuki_State_Sleeping::Execute(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());
	// 취침 상태에서 실행될 로직
	cout << "잠자는 중..." << endl;
	globalState->CallTimeSignal();

	Day nextDay = static_cast<Day>((static_cast<int>(globalState->GetCurrentDay()) + 1) % 7);

	if(nextDay != Day::Sunday) entity->GetFSM()->ChangeState(Yuki_State_WakeUp::Instance());
	else entity->GetFSM()->ChangeState(Yuki_State_InteractionWait::Instance());
}

void Yuki_State_Sleeping::Exit(Yuki_Makoto* entity) {}

//==================================기상 상태==============================
Yuki_State_WakeUp* Yuki_State_WakeUp::Instance() {
	static Yuki_State_WakeUp instance;
	return &instance;
}

void Yuki_State_WakeUp::Enter(Yuki_Makoto* entity) {}

void Yuki_State_WakeUp::Execute(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	if (globalState->GetCurrentDay() != Day::Sunday) {
		cout << "아침이 밝았다. 기숙사에서 나와서 학교로 가자." << endl;
		cout << "기숙사에서 학교로 왔다. 수업을 들을 준비를 하자." << endl;
		entity->GetFSM()->ChangeState(Yuki_State_School::Instance());
	}
	else {
		cout << "아침이 밝았다. 오늘은 일요일이라 학교를 가지 않아도 된다." << endl;
		entity->GetFSM()->ChangeState(Yuki_State_InteractionWait::Instance());
	}
	
}

void Yuki_State_WakeUp::Exit(Yuki_Makoto* entity) {}

//============================학교 수업 상태==============================

Yuki_State_School* Yuki_State_School::Instance() {
	static Yuki_State_School instance;
	return &instance;
}

void Yuki_State_School::Enter(Yuki_Makoto* entity) {}

void Yuki_State_School::Execute(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	float rand = urd(dre);
	if (rand < 0.3f) {
		cout << "수업 중에 졸았지만, 들키지 않았다! 용기가 상승했다" << endl;
		entity->SetBrave(entity->GetBrave() + 1);
	}
	else {
		cout << "졸지 않고 수업을 성실히 들었다. 지혜가 상승했다" << endl;
		entity->SetWisdom(entity->GetWisdom() + 1);
	}

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Yuki_State_InteractionWait::Instance());
}

void Yuki_State_School::Exit(Yuki_Makoto* entity) {}

//============================상호작용 대기 상태==============================

Yuki_State_InteractionWait* Yuki_State_InteractionWait::Instance() {
	static Yuki_State_InteractionWait instance;
	return &instance;
}

void Yuki_State_InteractionWait::Enter(Yuki_Makoto* entity) {}

void Yuki_State_InteractionWait::Execute(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	if (globalState->GetCurrentTime() == DayTime::Morning) {
		entity->GetFSM()->ChangeState(Yuki_State_BehaviorWait::Instance());
	}
	else if (globalState->GetCurrentTime() == DayTime::Afternoon) {
		cout << "수업이 끝나고 방과후가 되었다." << endl;
		entity->GetFSM()->ChangeState(Yuki_State_BehaviorWait::Instance());
	}
	else if (globalState->GetCurrentTime() == DayTime::Evening) {
		cout << "저녁이 되었다." << endl;
		entity->GetFSM()->ChangeState(Yuki_State_NightBehaviorWait::Instance());
	}
	else if (globalState->GetCurrentTime() == DayTime::Night) {
		cout << "밤이 깊었다. 기숙사로 돌아가자." << endl;
		entity->GetFSM()->ChangeState(Yuki_State_Sleeping::Instance());
	}
}

void Yuki_State_InteractionWait::Exit(Yuki_Makoto* entity) {}

//==================아침 or 방과 후 상호작용 대기 상태========================

Yuki_State_BehaviorWait* Yuki_State_BehaviorWait::Instance() {
	static Yuki_State_BehaviorWait instance;
	return &instance;
}

void Yuki_State_BehaviorWait::Enter(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	//아이기스 선택
	if (globalState->GetAegisInteractionSignal()) {
		cout << "아이기스가 나와 상호작용하고 싶어하는 것 같다." << endl;
		gameWorld->Message2Aegis("Selected");
	}
}

void Yuki_State_BehaviorWait::Execute(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	//아이기스 선택
	if (globalState->GetAegisInteractionSignal()) {
		entity->GetFSM()->ChangeState(Yuki_State_AegisInteraction::Instance());
	}
	//선택 안함
	else {
		entity->GetFSM()->ChangeState(Yuki_State_StatusBehavior::Instance());
	}
}

void Yuki_State_BehaviorWait::Exit(Yuki_Makoto* entity) {}

//=====================아이기스 상호작용 상태==========================

Yuki_State_AegisInteraction* Yuki_State_AegisInteraction::Instance() {
	static Yuki_State_AegisInteraction instance;
	return &instance;
}

void Yuki_State_AegisInteraction::Enter(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	globalState->SetAegisInteractionSignal(false);
}

void Yuki_State_AegisInteraction::Execute(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	cout << "아이기스와 얘기를 했다. 아이기스와의 관계가 깊어진 기분이 든다." << endl;

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Yuki_State_InteractionWait::Instance());
}

void Yuki_State_AegisInteraction::Exit(Yuki_Makoto* entity) {}

//====================밤 상호작용 랜덤 선택 상태============================

Yuki_State_NightBehaviorWait* Yuki_State_NightBehaviorWait::Instance() {
	static Yuki_State_NightBehaviorWait instance;
	return &instance;
}

void Yuki_State_NightBehaviorWait::Enter(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	//타르타로스 선택
	if (globalState->GetAegisInteractionSignal()) {
		cout << "모두와 함께 타르타로스로 향했다." << endl;
		gameWorld->Message2Aegis("Selected");
	}
}

void Yuki_State_NightBehaviorWait::Execute(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	if (globalState->GetAegisInteractionSignal()) {
		globalState->SetAegisInteractionSignal(false);

		entity->GetFSM()->ChangeState(Yuki_State_TartarosBattle::Instance());
	}
	else {
		entity->GetFSM()->ChangeState(Yuki_State_StatusBehavior::Instance());
	}
}

void Yuki_State_NightBehaviorWait::Exit(Yuki_Makoto* entity) {}

//====================타르타로스 전투 상태============================

Yuki_State_TartarosBattle* Yuki_State_TartarosBattle::Instance() {
	static Yuki_State_TartarosBattle instance;
	return &instance;
}

void Yuki_State_TartarosBattle::Enter(Yuki_Makoto* entity) {}

void Yuki_State_TartarosBattle::Execute(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	cout << "마음 속에서 페르소나가 성장하는게 느껴진다." << endl;
	cout << "레벨이 상승했다." << endl;
	entity->SetLevel(entity->GetLevel() + 1);

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Yuki_State_StatusBehavior::Instance());
}

void Yuki_State_TartarosBattle::Exit(Yuki_Makoto* entity) {}

//==================스테이터스 행동 랜덤 선택 상태==========================

Yuki_State_StatusBehavior* Yuki_State_StatusBehavior::Instance() {
	static Yuki_State_StatusBehavior instance;
	return &instance;
}

void Yuki_State_StatusBehavior::Enter(Yuki_Makoto* entity) {}

void Yuki_State_StatusBehavior::Execute(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	float rand = urd(dre);
	if (rand < 0.3f) {
		cout << "카페 샤갈에 가기로 했다." << endl;
		entity->GetFSM()->ChangeState(Yuki_State_CafeShagal::Instance());
	}
	else if (rand < 0.6f) {
		cout << "노래방애 가기로 했다." << endl;
		entity->GetFSM()->ChangeState(Yuki_State_Karaoke::Instance());
	}
	else {
		cout << "기숙사에 돌아가서 공부하기로 했다." << endl;
		entity->GetFSM()->ChangeState(Yuki_State_Study::Instance());
	}
}

void Yuki_State_StatusBehavior::Exit(Yuki_Makoto* entity) {}

//==========================카페 샤갈 상태===========================

Yuki_State_CafeShagal* Yuki_State_CafeShagal::Instance() {
	static Yuki_State_CafeShagal instance;
	return &instance;
}

void Yuki_State_CafeShagal::Enter(Yuki_Makoto* entity) {}

void Yuki_State_CafeShagal::Execute(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	cout << "커피를 마시며 여유를 즐겼다. 주변에서 시선을 받는 느낌이 든다." << endl;
	cout << "매력이 상승했다." << endl;
	entity->SetCharm(entity->GetCharm() + 1);

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Yuki_State_InteractionWait::Instance());
}

void Yuki_State_CafeShagal::Exit(Yuki_Makoto* entity) {}

//==========================노래방 상태===========================

Yuki_State_Karaoke* Yuki_State_Karaoke::Instance() {
	static Yuki_State_Karaoke instance;
	return &instance;
}

void Yuki_State_Karaoke::Enter(Yuki_Makoto* entity) {}

void Yuki_State_Karaoke::Execute(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	cout << "노래방에서 혼자 노래를 불렀다. 혼자라 그런지 끝까지 부를 수 있었다." << endl;
	cout << "용기가 상승했다." << endl;
	entity->SetBrave(entity->GetBrave() + 1);

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Yuki_State_InteractionWait::Instance());
}

void Yuki_State_Karaoke::Exit(Yuki_Makoto* entity) {}

//==========================공부하기 상태===========================

Yuki_State_Study* Yuki_State_Study::Instance() {
	static Yuki_State_Study instance;
	return &instance;
}

void Yuki_State_Study::Enter(Yuki_Makoto* entity) {}

void Yuki_State_Study::Execute(Yuki_Makoto* entity) {
	Yuki_Makoto_GlobalState* globalState = static_cast<Yuki_Makoto_GlobalState*>(entity->GetFSM()->GetGlobalState());

	cout << "공부를 했다." << endl;
	cout << "지혜가 상승했다." << endl;
	entity->SetWisdom(entity->GetWisdom() + 1);

	globalState->CallTimeSignal();
	entity->GetFSM()->ChangeState(Yuki_State_InteractionWait::Instance());
}

void Yuki_State_Study::Exit(Yuki_Makoto* entity) {}