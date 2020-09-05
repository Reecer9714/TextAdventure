#include "Action.h"

void QuitAction::perform(GameState &state) {
    state.running = false;
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

ErrorCode ActionPerformer::perform(Verb a, GameState& ref) {
    
    
    return NOT_IMPLEMENTED;
};