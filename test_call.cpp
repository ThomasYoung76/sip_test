#include <stdio.h>
#include <string.h>
#include "gtest/gtest.h"
#include "TestForUA.h"
#include <string>
#include <unistd.h>
#include <time.h>

namespace call{

class TestSipCall : public testing::Test
    {
	public:
		TestForCall ua;
	void SetUp()
	{
		UserAgent::setIpAddress( "10.1.77.85");
		UserAgent::setPort(6111);
		// 用户代理初始化
		EXPECT_TRUE(UserAgent::initialize());
		// 启动用户代理
		EXPECT_TRUE(ua.start()); 
	}
	void TearDown()
	{
		ua.stop(); 
		UserAgent::quit();
	}
    }; 

	
TEST_F(TestSipCall, Lev1_call_01)
{
    ua.setUsername("ysf");
    char sipAddr[1024] = "010001000101010101@10.1.77.87:6068";
	
	ASSERT_EQ(0, ua.call(sipAddr, true)); //call initial and invite (bDirectCallOut=true)

    sleep(1);
    EXPECT_STREQ("onPeerRinging", ua.callFlag); //对端铃响
    
    EXPECT_EQ(0,ua.terminate(0));
    sleep(2);
}

TEST_F(TestSipCall, Lev3_call_02_01)
{
    ua.setUsername("ysf");
	char sipAddr[1024] = "010001000101010101@10.1.77.83:6068";
	
	ASSERT_EQ(0, ua.call(sipAddr, true)); //call initial (bDirectCallOut=true)

	// wait for peer answer
	while(!ua.isTerminated)
	
	{
        usleep(10);
	}
	EXPECT_STREQ("onCallProxyFailed", ua.callFlag);  // peer is nonexist. call fail

}

TEST_F(TestSipCall, Lev3_call_02_02)
{
    ua.setUsername("ysf");
	char sipAddr[1024] = "010001000101010101@10.1.77.87:6111";
	
	ASSERT_EQ(0, ua.call(sipAddr, true)); //call initial (bDirectCallOut=true)

	// wait for peer answer
	while(!ua.isTerminated)
	
	{
        usleep(10);
	}
	EXPECT_STREQ("onCallProxyFailed", ua.callFlag);  // peer is nonexist. call fail

}

TEST_F(TestSipCall, Lev3_call_02_03)
{
    ua.setUsername("ysf");
	char sipAddr[1024] = "010001000101010101@10.1.77.83:6068";
	
	ASSERT_EQ(-1, ua.call(sipAddr, false)); //未注册，非呼叫失败

}

TEST_F(TestSipCall, Lev3_call_03_01)
{
    ua.setUsername("ysf");
	char sipAddr[1024] = "010001000101010199@10.1.77.87:6068";
	
	ASSERT_EQ(0, ua.call(sipAddr, true)); //call initial (bDirectCallOut=true)

	
    const time_t start = time(NULL);
    std::cout << "start time is : "<< start << std::endl;
    
    // wait for call terminated
    while(!ua.isTerminated)
	{
        usleep(10);
	}
    const time_t end=time(NULL);
    double time_gap;
    time_gap = difftime(end, start);
    std::cout << "end time is: "<< end<< std::endl;
    std::cout << "time gap is: " << time_gap << std::endl;
    
    EXPECT_GE(time_gap, 180);
    EXPECT_LT(time_gap, 200);
    
    ua.stop(); 
    UserAgent::quit();
}

TEST_F(TestSipCall, Lev3_call_03_02)
{
    ua.setUsername("ysf");
	char sipAddr[1024] = "010001000201010101@10.1.77.87:6068";
	
	ASSERT_EQ(0, ua.call(sipAddr, true)); //call initial (bDirectCallOut=true)

	
    const time_t start = time(NULL);
    std::cout << "start time is : "<< start << std::endl;
    
    // wait for call terminated
    while(!ua.isTerminated)
	{
        usleep(10);
	}
    const time_t end=time(NULL);
    double time_gap;
    time_gap = difftime(end, start);
    std::cout << "end time is: "<< end<< std::endl;
    std::cout << "time gap is: " << time_gap << std::endl;
    
    EXPECT_GE(time_gap, 180);
    EXPECT_LT(time_gap, 200);
}

TEST_F(TestSipCall, Lev3_call_03_03)
{
    ua.setUsername("ysf");
	char sipAddr[1024] = "ysf@10.1.77.87:6068";
	
	ASSERT_EQ(0, ua.call(sipAddr, true)); //call initial (bDirectCallOut=true)

	
    const time_t start = time(NULL);
    std::cout << "start time is : "<< start << std::endl;
    
    // wait for call terminated
    while(!ua.isTerminated)
	{
        usleep(10);
	}
    const time_t end=time(NULL);
    double time_gap;
    time_gap = difftime(end, start);
    std::cout << "end time is: "<< end<< std::endl;
    std::cout << "time gap is: " << time_gap << std::endl;
    
    EXPECT_GE(time_gap, 180);
    EXPECT_LT(time_gap, 200);
}

TEST_F(TestSipCall, Lev2_call_04)
{
	ua.setUsername("ysf");
    char sipAddr[1024] = "010001000101010101@10.1.77.87:6068";
	
	ASSERT_EQ(0, ua.call(sipAddr, true)); // (bDirectCallOut=true)

    sleep(2);
    EXPECT_STREQ("onPeerRinging", ua.callFlag); 
    
    EXPECT_TRUE(ua.isCallBusy());
    
    EXPECT_EQ(0, ua.call(sipAddr, true));
    sleep(1);
    EXPECT_STREQ("onPeerBusy", ua.callFlag); //对端铃响

    EXPECT_EQ(0,ua.terminate(0));
    sleep(2);
}

TEST_F(TestSipCall, Lev4_call_05)
{
    ua.setUsername("ysf");
	char sipAddr[1024] = "010001000101010101@10.1.77.87:6068";
	
	
	ASSERT_EQ(0, ua.call(sipAddr, true)); //call initial (bDirectCallOut=true)
	
	sleep(1);
	
	printf("accept the call and input 'y' to continue or declare the call\n");
	
	char buf[1024];
   	memset(buf, 0, 1024);
   	scanf("%s", buf);
   	if (strcmp( buf, "y") == 0 or strcmp(buf, "Y") == 0)
    {
        EXPECT_STREQ("onConfirmed", ua.callFlag);
    }
    else
    {
        EXPECT_STREQ("onPeerRinging", ua.callFlag);
    }
}

TEST_F(TestSipCall, Lev2_call_06)
{
    ua.setUsername("ysf");
	char sipAddr[1024] = "010001000101010101@10.1.77.87:6068";
	
	EXPECT_EQ(-1, ua.call(sipAddr, false)); //call initial (bDirectCallOut=false)
	EXPECT_EQ(0, ua.call(sipAddr, true)); //call initial (bDirectCallOut=true)
	
	sleep(2);
	
	EXPECT_STREQ("onPeerRinging", ua.callFlag); //对端铃响

	EXPECT_EQ(0,ua.terminate());
	sleep(2);
}

TEST_F(TestSipCall, Lev1_call_07)
{
    // 注册到服务器       
    ua.setUsername("010001000101000001");
    ua.setRegistrar("10.1.77.235");
    EXPECT_EQ(0, ua.addAuthenticationInfo(ua.getUsername(), ua.getUsername(),NULL));
    EXPECT_TRUE(ua.registerToProxy(ua.getRegistrar(), 600));

    sleep(1);
    // 呼叫 (bDirectCallOut=false)
	char sipAddr[1024] = "010001000101010101@10.1.77.87:6068";
	EXPECT_EQ(0, ua.call(sipAddr, false)); 
	
	sleep(5);
	EXPECT_STREQ("onPeerRinging", ua.callFlag); //对端铃响
	
	EXPECT_EQ(0,ua.terminate(0));
	sleep(2);
	ua.unregisterToProxy();
}

TEST_F(TestSipCall, Lev3_call_08)
{
    sleep(1);
    // 呼叫
    //ua.setUsername("10000");
    printf("-> get username: %s\n", ua.getUsername());
	char sipAddr[1024] = "010001000101010101@10.1.77.87:6068";
	EXPECT_EQ(0, ua.call(sipAddr,true));
	
	sleep(5);
	EXPECT_STREQ("onPeerRinging", ua.callFlag); //对端铃响
	char buffer[1024];
    while (1)
    {
        printf( "command>");
        memset( buffer, 0, 1024);
        // gets( buffer);
		scanf("%s", &buffer);

        if (strcmp( buffer, "q") == 0)
            break;
		usleep(10);
    }
	ua.unregisterToProxy();
}

TEST(TestCallLev2, call_09_01)
{  
	UserAgent::setIpAddress( "10.1.77.85");
    UserAgent::setPort(6111);

    EXPECT_TRUE(UserAgent::initialize(true));  //UserAgent initial
    TestForCall ua;
    EXPECT_TRUE(ua.start());    // call start
	
    char sipAddr[1024] = "010001000101010101@10.1.77.87:6068";
    EXPECT_EQ(-1, ua.callForceBreak(sipAddr));  //call fail without reg
     
    // 注册到服务器       
    ua.setUsername("010001000101000001");
    ua.setRegistrar("10.1.77.235");
    EXPECT_EQ(0, ua.addAuthenticationInfo(ua.getUsername(), ua.getUsername(),NULL));
    EXPECT_TRUE(ua.registerToProxy(ua.getRegistrar(), 600));

    sleep(1);
    
    // 呼叫
    EXPECT_EQ(0, ua.callForceBreak(sipAddr));
	
	sleep(5);
	EXPECT_STREQ("onPeerRinging", ua.callFlag); //对端铃响
	
	EXPECT_EQ(0,ua.terminate(0));
	ua.unregisterToProxy();
	ua.stop(); 
    UserAgent::quit();
}

TEST(TestCallLev2, call_09_02)
{  
	UserAgent::setIpAddress( "10.1.77.85");
    UserAgent::setPort(6111);

    EXPECT_TRUE(UserAgent::initialize());  //UserAgent initial
    TestForCall ua;
    EXPECT_TRUE(ua.start());    // call start

    // 注册到服务器       
    ua.setUsername("010001000101000001");
    ua.setRegistrar("10.1.77.235");
    EXPECT_EQ(0, ua.addAuthenticationInfo(ua.getUsername(), ua.getUsername(),NULL));
    EXPECT_TRUE(ua.registerToProxy(ua.getRegistrar(), 600));

    sleep(1);
    
    // 呼叫
	char sipAddr[1024] = "010001000101010101@10.1.77.87:6068";
    EXPECT_EQ(-1, ua.callForceBreak(sipAddr));
	
	EXPECT_EQ(-1,ua.terminate(0));
	ua.unregisterToProxy();
	ua.stop(); 
    UserAgent::quit();
}

TEST_F(TestSipCall, Lev2_call_10)
{
    // 注册到服务器       
    ua.setUsername("010001000101000001");
    ua.setRegistrar("10.1.77.235");
    EXPECT_EQ(0, ua.addAuthenticationInfo(ua.getUsername(), ua.getUsername(),NULL));
    EXPECT_TRUE(ua.registerToProxy(ua.getRegistrar(), 600));

    sleep(1);
    
    // 呼叫
    char sipAddr[1024] = "010001000101010101@10.1.77.87:6068";
    EXPECT_EQ(0, ua.set_call_forward("010001000101010199@10.1.77.87:6068"));
	EXPECT_EQ(0, ua.call(sipAddr, false)); 
	
	sleep(5);
	EXPECT_STREQ("onPeerRinging", ua.callFlag); //对端铃响
	
	EXPECT_EQ(0,ua.terminate(0));
	//EXPECT_EQ(0, ua.call(sipAddr)); 
	sleep(60);
	ua.unregisterToProxy();	
}

TEST(TestCallLev2, call_11)
{
	
	UserAgent::setIpAddress( "10.1.77.85");
    UserAgent::setPort(6111);
    UserAgent::initOsipTrace("./osip.log");

    EXPECT_TRUE(UserAgent::initialize(true));  //UserAgent initial
    

    TestForCall ua;
    
    EXPECT_TRUE(ua.start());    // call start
     
    
    // 注册到服务器       
    ua.setUsername("010001000101000001");
    ua.setRegistrar("10.1.77.235");
    EXPECT_EQ(0, ua.addAuthenticationInfo(ua.getUsername(), ua.getUsername(),NULL));
    EXPECT_TRUE(ua.registerToProxy(ua.getRegistrar(), 600));

    sleep(1);
    
    EXPECT_FALSE(ua.isCallBusy());
    
    // 呼叫
    //ua.setCallBusy(true);
    
    char sipAddr[1024] = "010001000101010101@10.1.77.87:6068";
    EXPECT_EQ(0, ua.call(sipAddr,false));
	
	sleep(2);
	EXPECT_STREQ("onPeerRinging", ua.callFlag); //对端铃响

	EXPECT_TRUE(ua.isCallBusy());
	
	EXPECT_EQ(0,ua.terminate(0));
	
    ua.stop(); 
    UserAgent::quit();
    UserAgent::quitOsipTrace();
}

TEST_F(TestSipCall, Lev3_call_12)
{
    // 注册到服务器       
    ua.setUsername("010001000101000001");
    ua.setRegistrar("10.1.77.235");
    EXPECT_EQ(0, ua.addAuthenticationInfo(ua.getUsername(), ua.getUsername(),NULL));
    EXPECT_TRUE(ua.registerToProxy(ua.getRegistrar(), 600));

    sleep(1);
    ua.setUsername("ysf");
	char sipAddr[1024] = "010001000101010101@10.1.77.87:6068";
	
	ASSERT_EQ(0, ua.call(sipAddr, false));

	
    const time_t start = time(NULL);
    std::cout << "start time is : "<< start << std::endl;
    
    // wait for call terminated
    while(!ua.isTerminated)
	{
        usleep(10);
	}
    const time_t end=time(NULL);
    double time_gap;
    time_gap = difftime(end, start);
    std::cout << "end time is: "<< end<< std::endl;
    std::cout << "time gap is: " << time_gap << std::endl;
    
    EXPECT_GE(time_gap, 180);
    EXPECT_LT(time_gap, 200);
}
}



    
