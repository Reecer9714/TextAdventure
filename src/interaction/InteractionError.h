#ifndef INTERACTIONERROR_H
#define INTERACTIONERROR_H

#include "core/ReturnCode.h"

constexpr const std::array<const char*, 4> VocabMessages = {
    "Failed to match verb", "Duplicate word", "Failed to load verbs", "No direction"
};

struct InteractionSubSystem : public SubSystem
{
    constexpr InteractionSubSystem( uint8_t n, ErrorMessageArray msgs = { 0, nullptr } )
        : SubSystem( n, msgs ){};
    static const InteractionSubSystem VOCAB;
};

inline constexpr const InteractionSubSystem InteractionSubSystem::VOCAB{
    0, CastErrorMessageArray( VocabMessages )
};

static constexpr const ReturnCode FAILED_MATCH_VERB =
    ReturnCode( System::INTERACTION, InteractionSubSystem::VOCAB, 1 );
static constexpr const ReturnCode DUPLICATE_WORD =
    ReturnCode( System::INTERACTION, InteractionSubSystem::VOCAB, 2 );
static constexpr const ReturnCode FAILED_LOAD_VERBS =
    ReturnCode( System::INTERACTION, InteractionSubSystem::VOCAB, 3 );
static constexpr const ReturnCode MOVE_NO_PARAM =
    ReturnCode( System::INTERACTION, InteractionSubSystem::VOCAB, 4 );

#endif