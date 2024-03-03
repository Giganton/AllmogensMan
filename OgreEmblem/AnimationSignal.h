#pragma once
#include<vector>

enum class SignalType { noSignal, animationStarted, animationDone };
enum class SignalSubType { noSignal, Battle, Movement, Death , Victory};

class AnimationSignal
{
private:
	int address = -1;
	SignalType type = SignalType::noSignal;
	SignalSubType subType = SignalSubType::noSignal;
public:
	AnimationSignal() {};
	AnimationSignal(int addr, SignalType tp) { address = addr; type = tp; };
	AnimationSignal(int addr, SignalType tp, SignalSubType stp) : AnimationSignal(addr, tp) { subType = stp; };
	
	int getAddress() { return address; };
	SignalType getType() { return type; };
	SignalSubType getSubType() { return subType; };
};