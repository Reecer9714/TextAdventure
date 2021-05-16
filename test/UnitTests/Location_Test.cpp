#include "GTest/gtest.h"
#include <data/Location.h>

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
    ReturnCode ret = intro->connectLocation( WEST, nullptr );

    EXPECT_EQ( ret, NULLPTR_INPUT );
};

TEST_F( Location_Test, connectLocation_DuplicateConnection_int )
{

    ReturnCode ret = intro->connectLocation( WEST, west );
    EXPECT_EQ( ret, SUCCESS );

    ReturnCode ret2 = intro->connectLocation( WEST, west2 );
    EXPECT_EQ( ret2, DUPLICATE_CONNECTION );
};

TEST_F( Location_Test, connectLocation_ConnectedSuccess_int )
{

    ReturnCode ret = intro->connectLocation( WEST, west );
    EXPECT_EQ( ret, SUCCESS );

    bool connected = intro->getExits()->at( WEST ).connected;

    EXPECT_EQ( connected, true );
};

TEST_F( Location_Test, connectLocation_StatusSuccess_int )
{

    ReturnCode ret = intro->connectLocation( WEST, west, CLOSED );
    EXPECT_EQ( ret, SUCCESS );

    ExitStatus status = intro->getExits()->at( WEST ).status;

    EXPECT_EQ( status, CLOSED );
};

TEST_F( Location_Test, connectLocation_VisibleSuccess_int )
{

    ReturnCode ret = intro->connectLocation( WEST, west, CLOSED, false );
    EXPECT_EQ( ret, SUCCESS );

    bool visible = intro->getExits()->at( WEST ).visible;

    EXPECT_EQ( visible, false );
};

TEST_F( Location_Test, disconnectLocation_Success_void )
{
    intro->disconnectLocation( WEST );

    bool connected = intro->getExits()->at( WEST ).connected;

    EXPECT_EQ( connected, false );
};

TEST_F( Location_Test, disconnectLocation_CleanDisconnect_void )
{
    ReturnCode retConnectWest = intro->connectLocation( WEST, west );
    EXPECT_EQ( retConnectWest, SUCCESS );

    intro->disconnectLocation( WEST );
    bool connected = intro->getExits()->at( WEST ).connected;
    EXPECT_EQ( connected, false );

    ReturnCode retConnectWest2 = intro->connectLocation( WEST, west2, CLOSED, false );
    EXPECT_EQ( retConnectWest2, SUCCESS );

    Connection expected;
    expected.loc = west2;
    expected.status = CLOSED;
    expected.visible = false;
    expected.connected = true;

    Connection returned = intro->getExits()->at( WEST );

    EXPECT_EQ( returned.loc, expected.loc );
    EXPECT_EQ( returned.status, expected.status );
    EXPECT_EQ( returned.visible, expected.visible );
    EXPECT_EQ( returned.connected, expected.connected );
};