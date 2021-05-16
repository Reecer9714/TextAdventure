#include <cstddef>
#include <iostream>
#include <regex>

#include "core/GameState.h"
#include "core/stringutils.h"
#include "data/Entity.h"
#include "data/Location.h"
#include "interaction/ActionPerformer.h"
#include "interaction/Vocabulary.h"

using namespace std;

void parseInput( string input, vector<string>& tokens );

int main()
{
    GameState state;

    Vocabulary vocab;

    std::shared_ptr<ActionPerformer> af = ActionPerformer::GetInstance();

    vocab.AddWord( "quit", Verb::Quit );
    vocab.AddWord( "q", Verb::Quit );
    vocab.AddWord( "exit", Verb::Quit );

    auto* intro = new Location( "Intro", "This is the intro room yay!!" );
    auto* northRoom = new Location( "North Room", "This is the to the North" );
    auto* seRoom = new Location( "SE Room", "This is the room to the SE" );
    auto* basement = new Location( "Basement", "This is the creepy basement" );

    intro->connectLocation( NORTH, northRoom );
    intro->connectLocation( SE, seRoom );
    intro->connectLocation( DOWN, basement );

    state.currentLocation = intro;

    string input;

    cout << state.currentLocation->getDesc() << endl;

    while( state.running )
    {
        getline( cin, input );
        // cout << input << endl;
        // Parse input
        parseInput( input, state.currentTokens );
        // Change state
        // Display state
        size_t wordCount = state.currentTokens.size();
        bool verbFound = false;
        for( size_t i = 0; i < wordCount; i++ )
        {
            Verb verb;
            ReturnCode ec = vocab.GetVerb( state.currentTokens[ i ], verb );
            if( ec.Success() )
            {
                verbFound = true;
                ec = af->Perform( verb, state );
                if( !ec.Success() )
                {
                    cout << "Error: " << ec.ToString() << endl;
                }
            }
        }

        if( !verbFound )
        {
            cout << "No Verb Found" << endl;
        }
    }

    return 0;
}

void parseInput( string input, vector<string>& tokens )
{
    tokens.clear();
    if( input.length() != 0 )
    {
        input = tolowercase( trim( input ) );
        std::regex re( "\\s+" );
        std::sregex_token_iterator curToken( input.begin(), input.end(), re, -1 );
        std::sregex_token_iterator endOfTokens;

        for( ; curToken != endOfTokens; ++curToken )
        {
            tokens.push_back( curToken->str() );
        }
    }
}
