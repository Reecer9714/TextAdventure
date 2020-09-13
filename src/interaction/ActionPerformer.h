#ifndef ACTION_H
#define ACTION_H

#include <iostream>

#include "ActionRC.h"
#include "core/GameState.h"
#include "data/Entity.h"
#include "data/Location.h"

enum class Verb {
    Quit,
    Move,
    Look,
    Open,
    Close,
    Lock,
    Unlock,
    Equip,
    Grab,
    Buy,
    Sell,
    List,
    Attack,
    Stealth,
    Steal,
    Inventory
};

class Action {
public:
    virtual ErrorCode Perform(GameState &state) = 0;
};

class ActionPerformer {
    ActionPerformer();
    static ActionPerformer* inst;

    std::unordered_map<Verb, Action*> actions;
public:
    static ActionPerformer* GetInstance();

    ErrorCode Perform(Verb verb, GameState &state);
};

class QuitAction : public Action {
public:
    virtual ErrorCode Perform(GameState &state) override;
};

class LookAction : public Action {
public:
    virtual ErrorCode Perform(GameState& state) override;
};

#endif