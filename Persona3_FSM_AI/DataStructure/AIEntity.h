#pragma once

#include <string>
using namespace std;

class AIEntity {
public:
	AIEntity() = default;
	virtual ~AIEntity() = default;

	virtual void Update() {}
	virtual void OnMessage(const string message) {}
};