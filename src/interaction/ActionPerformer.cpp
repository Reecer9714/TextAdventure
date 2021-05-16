#include "ActionPerformer.h"

#include <memory>

ReturnCode QuitAction::Perform( GameState& state )
{
    state.running = false;
    return SUCCESS;
};

const std::shared_ptr<ActionPerformer> ActionPerformer::inst{ new ActionPerformer() };

ActionPerformer::ActionPerformer()
{
    this->actions.emplace( Verb::Quit, std::make_unique<QuitAction>() );
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