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
public:
    // Finds a verb that is mapped to the word
    ReturnCode GetVerb( const std::string& word, Verb& verb );

    ReturnCode AddWord( std::string word, Verb verb );

    ReturnCode LoadFromFile( const std::string& file );

private:
    std::unordered_map<std::string, Verb> vocab;
};

#endif