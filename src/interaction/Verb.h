#ifndef __VERB_H__
#define __VERB_H__

#include <string>
#include <unordered_map>

enum class Verb
{
    Quit,
    Move,
    Look,
    Open,
    Close,
    Lock,
    Unlock,
    Equip,
    Grab,
    Buy,
    Sell,
    List,
    Attack,
    Stealth,
    Steal,
    Inventory,
    INVALID
};

static std::unordered_map<std::string, Verb> const VerbString = {
    { "Quit", Verb::Quit },     { "Move", Verb::Move },
    { "Look", Verb::Look },     { "Open", Verb::Open },
    { "Close", Verb::Close },   { "Lock", Verb::Lock },
    { "Unlock", Verb::Unlock }, { "Equip", Verb::Equip },
    { "Grab", Verb::Grab },     { "Buy", Verb::Buy },
    { "Sell", Verb::Sell },     { "List", Verb::List },
    { "Attack", Verb::Attack }, { "Stealth", Verb::Stealth },
    { "Steal", Verb::Steal },   { "Inventory", Verb::Inventory }
};

inline Verb tokenToVerb( std::string token )
{
    Verb d = Verb::INVALID;
    auto it = VerbString.find( token );
    if( it != VerbString.end() )
    {
        d = it->second;
    }
    return d;
}

#endif // __VERB_H__