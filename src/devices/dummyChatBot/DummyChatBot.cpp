/*
 * SPDX-FileCopyrightText: 2023-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "DummyChatBot.h"
#include <yarp/os/Log.h>
#include <yarp/os/LogStream.h>

YARP_LOG_COMPONENT(DUMMYCHATBOT, "yarp.devices.DummyChatBot")

DummyChatBot::DummyChatBot() :
    m_lang{"eng"},
    m_fallback{"Sorry, I did not get that. Can you repeat?"},
    m_noInput{"I heard nothing. Can you please speak up?"},
    m_status{"greetings"},
    m_qAndA{
            {"greetings",
             {{"Hello!","Hello there."},{"Who are you?","I am just a fake chatbot"},
              {"Goodbye!", "Already? Ok... bye."}}
            },
            {"chatting",
             {{"Hello!","Hello again."},{"Who are you?","I am just a fake chatbot"},
              {"Goodbye!", "Bye bye!"}}
            }
        }
{}

bool DummyChatBot::interact(const std::string& messageIn, std::string& messageOut)
{
    if(messageIn.empty())
    {
        messageOut = m_noInput;
        return true;
    }
    if(m_qAndA[m_status].count(messageIn) < 1)
    {
        messageOut = m_fallback;
        return true;
    }

    messageOut = m_qAndA[m_status][messageIn];

    if(m_status == std::string("greetings"))
    {
        m_status = "chatting";
    }

    return true;
}

bool DummyChatBot::setLanguage(const std::string& language)
{
    if (language != "eng")
    {
        yCError(DUMMYCHATBOT) << "Unsopported language. Only English is supported for the moment being";
        return false;
    }
    m_lang = language;

    return true;
}

bool DummyChatBot::getLanguage(std::string& language)
{
    language = m_lang;

    return true;
}

bool DummyChatBot::getStatus(std::string& status)
{
    status = m_status;
    return true;
}

bool DummyChatBot::resetBot()
{
    m_status = "greetings";
    return true;
}
