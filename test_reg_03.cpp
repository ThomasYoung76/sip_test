#include <stdio.h>
#include <string.h>
#include "gtest/gtest.h"
#include "TestForUA.h"
#include <string>

class ParamTestReg : public testing::TestWithParam<int>
{
	
};

TEST_P(ParamTestReg, reg_03)
{
	
	UserAgent::setIpAddress( "10.1.77.85");
    UserAgent::setPort(6111);
    
    EXPECT_TRUE(UserAgent::initialize()); //initialize

    TestForCall ua; 

    EXPECT_TRUE(ua.start()); //启动UserAgent
    
    
    ua.setUsername("010001000101000001");
    ua.setRegistrar("10.1.77.235");
    
    int addAuth;
    addAuth = ua.addAuthenticationInfo(ua.getUsername(), ua.getUsername(),NULL);
    EXPECT_EQ(0, addAuth);
    
    sleep(1);
    
    EXPECT_FALSE(ua.registerToProxy(ua.getRegistrar(), GetParam()));// 注册到服务器

    sleep(1);

    //EXPECT_STREQ(ua.callFlag, "onRegistrationSuccess");
    
    ua.stop(); 
    UserAgent::quit();
}


INSTANTIATE_TEST_CASE_P(ParamRegisterFailed, ParamTestReg, testing::Values(0, -100));
    
