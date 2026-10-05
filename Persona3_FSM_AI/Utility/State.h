#pragma once
#include <string>
using namespace std;

template<class T>
class State {
public:
	virtual ~State() = default;
	virtual void Enter(T* entity) {}
	virtual void Execute(T* entity) {}
	virtual void Exit(T* entity) {}
	virtual void OnMessage(T* entity, const string message) {}
};