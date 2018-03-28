#include <stdio.h>
#include <string.h>
#include "gtest/gtest.h"
#include "TestForUA.h"
#include <string>

namespace reg_04{
TEST(Test, reg_04)
{
	
	UserAgent::setIpAddress( "10.1.77.85");
    UserAgent::setPort(6111);
    
    EXPECT_TRUE(UserAgent::initialize()); //initialize

    TestForCall ua; 

    EXPECT_TRUE(ua.start()); //启动UserAgent
    
    
    ua.setUsername("010001000101000001");
    ua.setRegistrar("10.1.77.83");
    
    int addAuth;
    addAuth = ua.addAuthenticationInfo(ua.getUsername(), ua.getUsername(),NULL);
    EXPECT_EQ(0, addAuth);
    
    sleep(1);
    EXPECT_TRUE(ua.registerToProxy(ua.getRegistrar()));// 注册到服务器

    sleep(10);

    EXPECT_STREQ(ua.callFlag, "");
    
    ua.unregisterToProxy();
    ua.stop(); 
    UserAgent::quit();
}

TEST(Test, reg_05)
{
	
	UserAgent::setIpAddress( "10.1.77.85");
    UserAgent::setPort(6111);
    
    EXPECT_TRUE(UserAgent::initialize()); //initialize

    TestForCall ua; 

    EXPECT_TRUE(ua.start()); //启动UserAgent
    
    
    ua.setUsername("010001000101000099");
    ua.setRegistrar("10.1.77.235");
    
    int addAuth;
    addAuth = ua.addAuthenticationInfo(ua.getUsername(), ua.getUsername(),NULL);
    EXPECT_EQ(0, addAuth);
    
    sleep(1);
    EXPECT_TRUE(ua.registerToProxy(ua.getRegistrar()));// 注册到服务器

    sleep(10);

    EXPECT_STREQ(ua.callFlag, "");
    
    ua.unregisterToProxy();
    ua.stop(); 
    UserAgent::quit();
}

}
    
