#ifndef ACTION_H
#define ACTION_H

#include "main/ReturnCode.h"
#include "main/GameState.h"
#include "data/Entity.h"
#include "data/Location.h"

enum Verb {
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
    Inventory,
    VerbLength
};

class Action {
public:
    virtual void perform(GameState &state) = 0;
};

class ActionPerformer {

private:
    ActionPerformer();
    static ActionPerformer* mpActionPerformerInst;

    std::unordered_map<Verb, Action*> actions;
public:
    static ActionPerformer* getInstance();

    ErrorCode perform(Verb verb, GameState &state);
};

class QuitAction : public Action {
public:
    virtual void perform(GameState &state) override;
};

#endif