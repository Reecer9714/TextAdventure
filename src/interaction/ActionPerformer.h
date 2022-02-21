#ifndef ACTION_H
#define ACTION_H

#include <memory>

#include "Verb.h"
#include "core/GameState.h"
#include "core/ReturnCode.h"
#include "data/Entity.h"
#include "data/Location.h"

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

class MoveAction : public Action
{
public:
    ReturnCode Perform( GameState& state ) override;
};

#endif