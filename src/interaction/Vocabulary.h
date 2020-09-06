#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <string>
#include <unordered_map>

#include "core/stringutils.h"
#include "core/ReturnCode.h"
#include "VocabRC.h"
#include "Action.h"

class Vocabulary {
    typedef std::unordered_map<std::string, Verb> VocabList;
    VocabList vocab;

public:
    //Finds an action the is mapped to the word
    ErrorCode GetVerb(std::string word, Verb& verb);

    ErrorCode AddWord(std::string word, Verb verb);
};

#endif