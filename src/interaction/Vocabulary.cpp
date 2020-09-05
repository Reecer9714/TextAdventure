#include "Vocabulary.h"

ErrorCode Vocabulary::GetVerb(std::string word, Verb& verb){
    std::unordered_map<std::string, Verb>::iterator match = vocab.find(word);
    if(match == vocab.end()){
        return FAILED_GET_ACTION;
    }

    verb = match->second;
    return SUCCESS;
};

ErrorCode Vocabulary::AddWord(std::string word, Verb verb){
    this->vocab.emplace(tolowercase(word), verb);
    return SUCCESS;
};