#include <stdio.h>
#include <string.h>
#include "gtest/gtest.h"
#include "TestForUA.h"
#include <string>
#include <unistd.h>
#include <time.h>

namespace Agent{



TEST(ParamTestCall, agent_01)
{
    EXPECT_TRUE(UserAgent::initialize());  //UserAgent initial
    
    TestForCall ua;
    EXPECT_TRUE(ua.start());    // UserAgent start

    ua.stop(); 
    UserAgent::quit();
}

TEST(ParamTestCall, agent_02)
{
    UserAgent::setPort(6111);
    EXPECT_TRUE(UserAgent::initialize());  
    
    EXPECT_FALSE(UserAgent::initialize());  //initialize again
    
    UserAgent::quit();  
    
    EXPECT_TRUE(UserAgent::initialize()); 
    
    TestForCall ua;
    EXPECT_TRUE(ua.start()); 

    ua.stop(); 
    UserAgent::quit();
}

TEST(ParamTestCall, agent_03)
{
    UserAgent::setPort(6111);
    EXPECT_TRUE(UserAgent::initialize());  
    
    TestForCall ua;
    EXPECT_TRUE(ua.start()); 
    EXPECT_FALSE(ua.start());  //start again

    
    ua.stop(); 
    EXPECT_TRUE(ua.start());  //start nonal
    ua.stop(); 
    
    UserAgent::quit();
}



}



    
