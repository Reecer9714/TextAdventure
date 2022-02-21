#include "ActionPerformer.h"

#include <memory>

#include "InteractionError.h"
#include "data/Location.h"

ReturnCode QuitAction::Perform( GameState& state )
{
    state.running = false;
    return SUCCESS;
};

ReturnCode MoveAction::Perform( GameState& state )
{
    ReturnCode rc = MOVE_NO_PARAM;
    Direction eMoveDir = tokenToDirection( state.currentTokens[ state.tokenLocation ] );
    rc = state.TryMoveDirection( eMoveDir );
    if( rc.Success() )
    {
        state.tokenLocation++;
    }
    return rc;
};

const std::shared_ptr<ActionPerformer> ActionPerformer::inst{ new ActionPerformer() };

ActionPerformer::ActionPerformer()
{
    this->actions.emplace( Verb::Quit, std::make_unique<QuitAction>() );
    this->actions.emplace( Verb::Move, std::make_unique<MoveAction>() );
};

std::shared_ptr<ActionPerformer> ActionPerformer::GetInstance()
{
    return inst;
};

ReturnCode ActionPerformer::Perform( Verb verb, GameState& state )
{
    auto match = this->actions.find( verb );

    if( match != this->actions.end() )
    {
        return this->actions.find( verb )->second->Perform( state );
    }

    return NOT_IMPLEMENTED;
};