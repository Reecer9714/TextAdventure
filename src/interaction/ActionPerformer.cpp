#include "ActionPerformer.h"

ErrorCode QuitAction::Perform(GameState &state) {
    state.running = false;
    return SUCCESS;
};

ActionPerformer* ActionPerformer::inst = nullptr;

ActionPerformer::ActionPerformer() {
    this->actions.emplace(Verb::Quit, new QuitAction());
};

ActionPerformer* ActionPerformer::GetInstance() {
    if( inst == nullptr ){
        inst = new ActionPerformer();
    }

    return inst;
};

ErrorCode ActionPerformer::Perform(Verb verb, GameState& ref) {
    std::unordered_map<Verb, Action *>::const_iterator match = this->actions.find(verb);
    
    if( match != this->actions.end() ) {
        return this->actions.find(verb)->second->Perform(ref);
    }
    
    return NOT_IMPLEMENTED;
};