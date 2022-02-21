#include "Vocabulary.h"

#include <fstream>
#include <string>

#include "core/ReturnCode.h"
#include "interaction/Verb.h"

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

ReturnCode Vocabulary::LoadFromFile( const std::string& file )
{
    ReturnCode rc = FAILED_LOAD_VERBS;
    std::ifstream infile( file );
    std::string line;
    while( std::getline( infile, line ) )
    {
        Verb v = Verb::INVALID;
        size_t first = 0;
        size_t space = line.find( ' ' );
        if( space == std::string::npos )
        {
            break;
        }

        std::string verb = line.substr( first, space );
        v = tokenToVerb( verb );
        if( v != Verb::INVALID )
        {
            while( space != std::string::npos )
            {
                first = space + 1;
                space = line.find( ' ', first );
                if( space == std::string::npos )
                {
                    break;
                }
                std::string word = line.substr( first, space - first );
                rc = AddWord( word, v );
            }
        }
    }

    return rc;
};
