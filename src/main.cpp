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
    ReturnCode rc = SUCCESS;
    GameState state;

    Vocabulary vocab;

    std::shared_ptr<ActionPerformer> af = ActionPerformer::GetInstance();

    rc = vocab.LoadFromFile( "./data/verbs.txt" );

    if( rc.Success() )
    {
        auto* intro = new Location( "Intro", "This is the intro room yay!!" );
        auto* northRoom = new Location( "North Room", "This is the room to the North" );
        auto* seRoom = new Location( "SE Room", "This is the room to the SE" );
        auto* basement = new Location( "Basement", "This is the creepy basement" );

        intro->connectBothLocations( NORTH, northRoom );
        intro->connectBothLocations( SE, seRoom );
        intro->connectBothLocations( DOWN, basement );

        state.currentLocation = intro;
    }

    if( rc.Success() )
    {
        state.running = true;
    }

    while( state.running )
    {
        string input;
        cout << state.currentLocation->getDesc() << endl;
        getline( cin, input );
        // cout << input << endl;
        // Parse input
        parseInput( input, state.currentTokens );
        // Change state
        // Display state
        size_t wordCount = state.currentTokens.size();
        bool verbFound = false;
        for( state.tokenLocation = 0; state.tokenLocation < wordCount; state.tokenLocation++ )
        {
            Verb verb;
            state.code = vocab.GetVerb( state.currentTokens[ state.tokenLocation ], verb );
            if( state.code.Success() )
            {
                verbFound = true;
                state.code = af->Perform( verb, state );
                if( !state.code.Success() )
                {
                    cout << "Error: " << state.code.ToString() << endl;
                }
            }
        }

        if( !verbFound )
        {
            cout << "No Verb Found" << endl;
        }
    }

    if( rc.Success() && state.code.Failed() )
    {
        rc = state.code;
    }

    if( !rc.Success() )
    {
        cout << "Exit Error: " << rc.ToString() << endl;
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
