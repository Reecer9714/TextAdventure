#include <iostream>
#include <regex>

#include "core/stringutils.h"
#include "core/GameState.h"
#include "interaction/Vocabulary.h"
#include "interaction/ActionPerformer.h"
#include "data/Location.h"
#include "data/Entity.h"

using namespace std;

void parseInput(string input, vector<string> &tokens);

int main() {
    GameState state;

    Vocabulary vocab;

    ActionPerformer* af = ActionPerformer::GetInstance();

    vocab.AddWord( "quit", Verb::Quit );
    vocab.AddWord( "q", Verb::Quit );
    vocab.AddWord( "exit", Verb::Quit );

    vocab.AddWord( "look", Verb::Look);


    Location* intro = new Location( "Intro", "This is the intro room yay!!" );
    Location* northRoom = new Location( "North Room", "This is the to the North" );
    Location* seRoom = new Location( "SE Room", "This is the room to the SE" );
    Location* basement = new Location( "Basement", "This is the creepy basement" );

    intro->connectLocation( NORTH, northRoom );
    intro->connectLocation( SE, seRoom );
    intro->connectLocation( DOWN, basement );

    state.currentLocation = intro;

    string input;

    cout << state.currentLocation->getDesc() << endl;
    
    ErrorCode ec;

    while( state.running ){

        getline( cin, input );
        // cout << input << endl;
        //Parse input
        parseInput( input, state.currentTokens );
        //Change state
        //Display state
        int wordCount = state.currentTokens.size();
        bool verbFound = false;
        for( int i = 0; i < wordCount; i++ ){
            Verb verb;
            ec = vocab.GetVerb( state.currentTokens[ i ], verb );
            if( ec == SUCCESS ) {
                verbFound = true;
                ec = af->Perform( verb, state );
                if( ec != SUCCESS ) {
                    cout << "Error: " << ec << endl;
                }
            }
        }

        if( !verbFound ){
            cout << "No Verb Found" << endl;
        }
    }

    return 0;
}

void parseInput(string input, vector<string> &tokens) {
    tokens.clear();
    if( input.length() ) {
        input = tolowercase( trim( input ) );
        std::regex re( "\\s+" );
        std::sregex_token_iterator curToken( input.begin(), input.end(), re, -1 );
        std::sregex_token_iterator endOfTokens;

        for( ; curToken != endOfTokens; ++curToken ) {
            tokens.push_back( curToken->str() );
        }
    }
}
