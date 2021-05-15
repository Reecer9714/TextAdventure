#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <string>
#include <unordered_map>

#include "ActionPerformer.h"
#include "InteractionError.h"
#include "core/ReturnCode.h"
#include "core/stringutils.h"

class Vocabulary
{
    typedef std::unordered_map<std::string, Verb> VocabList;

public:
    // Finds a verb that is mapped to the word
    ReturnCode GetVerb( std::string word, Verb& verb );

    ReturnCode AddWord( std::string word, Verb verb );

private:
    VocabList vocab;
};

#endif