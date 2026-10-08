//2022182034 임성진
#include <iostream>
#include <windows.h>

#include "Character/Yuki_Makoto/Yuki_Makoto.h"
#include "Character/Aegis/Aegis.h"
#include "Character/Yamagishi_Fuka/Yamagishi_Fuka.h"
#include "Character/GlobalState.h"

GameWorld* gameWorld;

int main() {
	Yuki_Makoto* yuki = new Yuki_Makoto();
	Aegis* aegis = new Aegis();
	Yamagishi_Fuka* yamagishi = new Yamagishi_Fuka();
	gameWorld = new GameWorld(yuki, aegis, yamagishi);

	int delay = 100;
	int loopCount = 1;

	cout << "2022182034 임성진 : BT AI 실행 화면" << endl;

	//일주일 동안 시뮬레이션
	while (gameWorld->loop < loopCount + 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		gameWorld->PrintCurrentTime();

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		aegis->Update();

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		yamagishi->Update();

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		yuki->Update();

		gameWorld->Update();
		Sleep(delay);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "====================시뮬레이션 종료====================" << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "유키 마코토의 스테이터스: " << endl;
	cout << "레벨: " << yuki->GetLevel() << ", 매력: " << yuki->GetCharm() << ", 용기: " << yuki->GetBrave() << ", 지혜: " << yuki->GetWisdom() << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "아이기스의 스테이터스: " << endl;
	cout << "레벨: " << aegis->GetLevel() << ", 호감도: " << aegis->GetLikeability() << endl;
	if (aegis->GetLikeability() >= 3) {
		cout << "====================아이기스 호감도 MAX====================" << endl;
		cout << "나는 그대...그대는 나..." << endl;
		cout << "그대, 마침내 진실된 인연을 얻었나니..." << endl;
		cout << "이로써 [영겁]의 힘은, 가장 깊은 곳까지 열렸도다." << endl;
		cout << "우리, 그대에게 내리노니..." << endl;
		cout << "[영겁]의 궁극의 힘, 그대 안에 충만하기를..." << endl;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "야마기시 후카의 스테이터스: " << endl;
	cout << "레벨: " << yamagishi->GetLevel() << ", 호감도: " << yamagishi->GetLikeability() << endl;
	if (yamagishi->GetLikeability() >= 3) {
		cout << "====================야마기시 후카 호감도 MAX====================" << endl;
		cout << "나는 그대...그대는 나..." << endl;
		cout << "그대, 마침내 진실된 인연을 얻었나니..." << endl;
		cout << "이로써 [여법황]의 힘은, 가장 깊은 곳까지 열렸도다." << endl;
		cout << "우리, 그대에게 내리노니..." << endl;
		cout << "[여법황]의 궁극의 힘, 그대 안에 충만하기를..." << endl;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	system("pause");
}