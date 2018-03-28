#ifndef TEST_FOR_CALL_INCLUDE
#define TEST_FOR_CALL_INCLUDE

#include <stdio.h>
#include <pthread.h>
#include "UserAgent.h"
#include <time.h>
#include <string>
#include <iostream>

class TestForCall : public UserAgent
{
public:
    TestForCall();
    virtual ~TestForCall();

private:
    static void * timeThreadProc(void * data);
    
private:
    pthread_t m_pthreadStruc;

protected:
    virtual void onCallProxyFailed( int linuNumber, const char * remoteUsername, const char * remoteHost); //Proxy is offline when call
    virtual void onTerminated( int lineNumber, const char * remoteUsername, const char * remoteHost);//自身或对方挂断时，被触发
    virtual void onPeerRinging( int lineNumber, const char * remoteUsername, const char * remoteHost); // 对方振铃时被触发
    virtual void onPeerBusy( int lineNumber, const char * remoteUsername, const char * remoteHost); //对方忙时，被触发
    virtual void onStartMedia( int lineNumber, const char * remoteHost,
                               int remoteVideoPort, int remoteAudioPort, bool bSelfDialled); //接听后打开多媒体视频
    virtual void onStopMedia( int lineNumber); //关闭通话视频
    virtual void onConfirmed( int lineNumber, const char * remoteUsername, const char * remoteHost);//UAC receives 200 response for INVITE or UAS receives ACK request
    virtual void onRegistrationSuccess();//注册成功时，被触发
    virtual void onRegistrationFailure();//注册失败时，被触发
    
public:
	char callFlag[1024];
	bool isTerminated;
	time_t m_beginTime;
    std::string m_registrar;
	
public:
    const time_t * getBeginTime() const {return &m_beginTime;}

    void setRegistrar( const char * registrar) {m_registrar = registrar;}
    const char * getRegistrar() const {return m_registrar.c_str();}
};


#endif /* TEST_FOR_CALL_INCLUDE */
