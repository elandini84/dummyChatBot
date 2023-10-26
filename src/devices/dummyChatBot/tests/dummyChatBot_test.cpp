/*
 * SPDX-FileCopyrightText: 2023-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <yarp/os/Network.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/WrapperSingle.h>
#include <yarp/dev/IChatBot.h>
#include <yarp/dev/tests/IChatBotTest.h>

#include <catch2/catch_amalgamated.hpp>
#include <harness.h>

using namespace yarp::dev;
using namespace yarp::os;

TEST_CASE("dev::dummyChatBotTest", "[yarp::dev]")
{
    YARP_REQUIRE_PLUGIN("dummyChatBot", "device");

    Network::setLocalMode(true);

    SECTION("Checking dummyChatBot")
    {
        PolyDriver dummyChatBotdev;
        IChatBot* iChatBot = nullptr;

        ////////"Checking opening polydriver"
        {
            Property chatBot_cfg;
            chatBot_cfg.put("device", "dummyChatBot");
            REQUIRE(dummyChatBotdev.open(chatBot_cfg));
            REQUIRE(dummyChatBotdev.view(iChatBot));
        }

        //execute tests
        yarp::dev::tests::exec_iChatBot_test_1(iChatBot);

        //"Close all polydrivers and check"
        CHECK(dummyChatBotdev.close());
    }

    Network::setLocalMode(false);
}
