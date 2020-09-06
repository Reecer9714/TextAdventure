#include "Vocabulary.h"

ErrorCode Vocabulary::GetVerb(std::string word, Verb& verb){
    VocabList::iterator match = vocab.find(word);
    if(match == vocab.end()){
        return FAILED_MATCH_VERB;
    }

    verb = match->second;
    return SUCCESS;
};

ErrorCode Vocabulary::AddWord(std::string word, Verb verb){
    std::pair<VocabList::iterator, bool> ret = this->vocab.emplace(tolowercase(word), verb);
    if( ret.second == false ){
        return DUPLICATE_WORD;
    }
    return SUCCESS;
};