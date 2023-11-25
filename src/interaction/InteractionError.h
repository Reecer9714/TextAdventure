#ifndef INTERACTIONERROR_H
#define INTERACTIONERROR_H

#include "core/ReturnCode.h"

constexpr const std::array VocabMessages = {
    "Failed to match verb", "Duplicate word", "Failed to load verbs", "No direction"
};

inline constexpr const SubSystem InteractionSubSystem{ System::INTERACTION, VocabMessages };
enum InteractionSubSystemCode
{
    VOCAB
};

static constexpr const ReturnCode FAILED_MATCH_VERB =
    ReturnCode( System::INTERACTION, InteractionSubSystemCode::VOCAB, 1 );
static constexpr const ReturnCode DUPLICATE_WORD =
    ReturnCode( System::INTERACTION, InteractionSubSystemCode::VOCAB, 2 );
static constexpr const ReturnCode FAILED_LOAD_VERBS =
    ReturnCode( System::INTERACTION, InteractionSubSystemCode::VOCAB, 3 );
static constexpr const ReturnCode MOVE_NO_PARAM =
    ReturnCode( System::INTERACTION, InteractionSubSystemCode::VOCAB, 4 );

#endif