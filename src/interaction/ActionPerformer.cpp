#include "ActionPerformer.h"

#include <memory>

ReturnCode QuitAction::Perform( GameState& state )
{
    state.running = false;
    return SUCCESS;
};

std::shared_ptr<ActionPerformer> ActionPerformer::inst = nullptr;

ActionPerformer::ActionPerformer()
{
    this->actions.emplace( Verb::Quit, new QuitAction() );
};

std::shared_ptr<ActionPerformer> ActionPerformer::GetInstance()
{
    if( inst == nullptr )
    {
        inst = std::make_shared<ActionPerformer>();
    }

    return inst;
};

ReturnCode ActionPerformer::Perform( Verb verb, GameState& state )
{
    std::unordered_map<Verb, Action*>::const_iterator match = this->actions.find( verb );

    if( match != this->actions.end() )
    {
        return this->actions.find( verb )->second->Perform( state );
    }

    return NOT_IMPLEMENTED;
};