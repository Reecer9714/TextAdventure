#ifndef ACTION_H
#define ACTION_H

#include <memory>

#include "core/GameState.h"
#include "core/ReturnCode.h"
#include "data/Entity.h"
#include "data/Location.h"

enum class Verb
{
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

class Action
{
public:
    virtual ~Action() = default;

    virtual ReturnCode Perform( GameState& state ) = 0;
};

class ActionPerformer
{
public:
    static std::shared_ptr<ActionPerformer> GetInstance();

    ReturnCode Perform( Verb verb, GameState& state );

private:
    ActionPerformer();
    static const std::shared_ptr<ActionPerformer> inst;

    std::unordered_map<Verb, std::unique_ptr<Action>> actions;
};

class QuitAction : public Action
{
public:
    ReturnCode Perform( GameState& state ) override;
};

#endif