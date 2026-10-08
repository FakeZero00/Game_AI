#pragma once
#include <vector>
using namespace std;

enum BehaviorStatus
{
	Success,
	Failure,
	Running
};

template <class T>
class BehaviorNode {
public:
	virtual ~BehaviorNode() {}

	virtual BehaviorStatus Tick(T* entity) { return Success; }
};

template <class T>
class CompositeNode : public BehaviorNode<T> {
protected:

	typedef vector<BehaviorNode<T>*> Childredn;

	Childredn children;

public:
	virtual ~CompositeNode() {
		for (auto child : this->children) {
			delete child;
		}
	}

	void AddChild(BehaviorNode<T>* child) {
		children.push_back(child);
	}
};

template <class T>
class SequenceNode : public CompositeNode<T> {
private:
	typedef typename CompositeNode<T>::Childredn Childredn;

public:
	BehaviorStatus Tick(T* entity) override {
		for (auto& child : this->children) {
			BehaviorStatus status = child->Tick(entity);
			if (status != Success) {
				return status;
			}
		}
		return Success;
	}
};

template <class T>
class SelectorNode : public CompositeNode<T> {
private:
	typedef typename CompositeNode<T>::Childredn Childredn;

public:
	virtual BehaviorStatus Tick(T* entity) override {
		for (auto& child : this->children) {
			BehaviorStatus status = child->Tick(entity);
			if (status != Failure) {
				return status;
			}
		}
		return Failure;
	}
};

template <class T>
class ConditionNode : public BehaviorNode<T> {
private:
	bool (*condition)(T*);

public:
	ConditionNode(bool (*cond)(T*)) : condition(cond) {}

	BehaviorStatus Tick(T* entity) override {
		return condition(entity) ? Success : Failure;
	}
};