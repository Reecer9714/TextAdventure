#ifndef INTERACTIONERROR_H
#define INTERACTIONERROR_H

#include "core/ReturnCode.h"

struct InteractionSubSystem : public SubSystem
{
    static const InteractionSubSystem VOCAB;
};

constexpr const InteractionSubSystem
InteractionSubSystem::VOCAB{ 0 };

static constexpr ReturnCode FAILED_MATCH_VERB = ReturnCode(System::INTERACTION, InteractionSubSystem::VOCAB, 0x0001);
static constexpr ReturnCode DUPLICATE_WORD = ReturnCode(System::INTERACTION, InteractionSubSystem::VOCAB, 0x0002);

#endif