#include "Action.h"

ErrorCode QuitAction::perform(GameState &state) {
    state.running = false;
    return SUCCESS;
};

ActionPerformer* ActionPerformer::mpActionPerformerInst = nullptr;

ActionPerformer::ActionPerformer() {
    this->actions.emplace(Quit, new QuitAction());
};

ActionPerformer* ActionPerformer::getInstance() {
    if( mpActionPerformerInst == nullptr ){
        mpActionPerformerInst = new ActionPerformer();
    }

    return mpActionPerformerInst;
};

ErrorCode ActionPerformer::perform(Verb verb, GameState& ref) {
    std::unordered_map<Verb, Action *>::const_iterator match = this->actions.find(verb);
    
    if( match != this->actions.end() ) {
        return this->actions.find(verb)->second->perform(ref);
    }
    
    return NOT_IMPLEMENTED;
};