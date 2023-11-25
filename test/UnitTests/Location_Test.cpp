#include "GTest/gtest.h"
#include <core/GlobalError.h>
#include <data/DataError.h>
#include <data/Location.h>
#include <stdexcept>

using namespace ::testing;

class Location_Test : public Test
{
public:
    Location* intro;
    Location* west;
    Location* west2;

    void SetUp() override
    {
        intro = new Location( "Intro", "This is the intro room yay!!" );
        west = new Location( "West", "Room to the west" );
        west2 = new Location( "West2", "Room to the west2" );
    }

    void TearDown() override
    {
        delete intro;
        intro = nullptr;

        delete west;
        west = nullptr;

        delete west2;
        west2 = nullptr;
    }
};

TEST_F( Location_Test, connectLocation_NullLocation_int )
{
    ReturnCode ret = intro->connectLocation( Direction::WEST, nullptr );

    EXPECT_EQ( ret, NULLPTR_INPUT );
};

TEST_F( Location_Test, connectLocation_DuplicateConnection_int )
{

    ReturnCode ret = intro->connectLocation( Direction::WEST, west );
    EXPECT_EQ( ret, SUCCESS );

    ReturnCode ret2 = intro->connectLocation( Direction::WEST, west2 );
    EXPECT_EQ( ret2, DUPLICATE_CONNECTION );
};

TEST_F( Location_Test, connectLocation_ConnectedSuccess_int )
{

    ReturnCode ret = intro->connectLocation( Direction::WEST, west );
    EXPECT_EQ( ret, SUCCESS );

    auto connection = intro->getExits().at( Direction::WEST );

    EXPECT_NE( connection.loc, nullptr );
};

TEST_F( Location_Test, connectLocation_StatusSuccess_int )
{

    ReturnCode ret = intro->connectLocation( Direction::WEST, west, CLOSED );
    EXPECT_EQ( ret, SUCCESS );

    ExitStatus status = intro->getExits().at( Direction::WEST ).status;

    EXPECT_EQ( status, CLOSED );
};

TEST_F( Location_Test, connectLocation_VisibleSuccess_int )
{

    ReturnCode ret = intro->connectLocation( Direction::WEST, west, CLOSED, false );
    EXPECT_EQ( ret, SUCCESS );

    bool visible = intro->getExits().at( Direction::WEST ).visible;

    EXPECT_EQ( visible, false );
};

TEST_F( Location_Test, disconnectLocation_Success_void )
{
    intro->disconnectLocation( Direction::WEST );

    EXPECT_THROW( auto& connection = intro->getExits().at( Direction::WEST ), std::out_of_range );
};

TEST_F( Location_Test, disconnectLocation_CleanDisconnect_void )
{
    ReturnCode retConnectWest = intro->connectLocation( Direction::WEST, west );
    EXPECT_EQ( retConnectWest, SUCCESS );

    intro->disconnectLocation( Direction::WEST );
    EXPECT_THROW( auto& connection = intro->getExits().at( Direction::WEST ), std::out_of_range );

    ReturnCode retConnectWest2 = intro->connectLocation( Direction::WEST, west2, CLOSED, false );
    EXPECT_EQ( retConnectWest2, SUCCESS );

    Connection expected;
    expected.loc = west2;
    expected.status = CLOSED;
    expected.visible = false;

    Connection returned = intro->getExits().at( Direction::WEST );

    EXPECT_EQ( returned.loc, expected.loc );
    EXPECT_EQ( returned.status, expected.status );
    EXPECT_EQ( returned.visible, expected.visible );
};