#include <stdio.h>
#include <string.h>
#include "gtest/gtest.h"
#include "TestForUA.h"
#include <string>



class ParamTestReg : public testing::TestWithParam<const char *>
{
	
};

TEST_P(ParamTestReg, reg_02)
{
	
	UserAgent::setIpAddress( "10.1.77.85");
    UserAgent::setPort(6111);
    
    EXPECT_TRUE(UserAgent::initialize()); //initialize

    TestForCall ua; 

    EXPECT_TRUE(ua.start()); //启动UserAgent

    ua.setUsername(GetParam());
    ua.setRegistrar("10.1.77.235");
    
    ua.addAuthenticationInfo(ua.getUsername(), ua.getUsername(),NULL); // add auth info
    
    
    EXPECT_TRUE(ua.registerToProxy(ua.getRegistrar(), 600));// 注册到服务器

    sleep(2);

    EXPECT_STREQ(ua.callFlag, "onRegistrationFailure");
    ua.stop(); 
    UserAgent::quit();
}

INSTANTIATE_TEST_CASE_P(ParamRegisterFailed, ParamTestReg, testing::Values("010001000101","010001000101000099","010001000102000001",""));
    
