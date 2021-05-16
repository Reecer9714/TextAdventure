#include "Vocabulary.h"

ReturnCode Vocabulary::GetVerb( const std::string& word, Verb& verb )
{
    auto match = vocab.find( word );
    if( match == vocab.end() )
    {
        return FAILED_MATCH_VERB;
    }

    verb = match->second;
    return SUCCESS;
};

ReturnCode Vocabulary::AddWord( std::string word, Verb verb )
{
    auto ret = this->vocab.emplace( tolowercase( word ), verb );
    if( !ret.second )
    {
        return DUPLICATE_WORD;
    }
    return SUCCESS;
};