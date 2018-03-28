
#include <stdio.h>
#include "TestForUA.h"
#include <assert.h>
#include <string.h>
#include "RegistrationProcessor.h"
#include <unistd.h>

TestForCall::TestForCall()
                        :m_pthreadStruc(0),
                        m_beginTime(),
                        m_registrar(),
						callFlag(),
						isTerminated(false)
{
    int cid;
    cid = pthread_create(&m_pthreadStruc, NULL, timeThreadProc, this);
    if (cid == 0)
    {
        printf("* pthread timeThreadProc create success\n");
    }
    else
    {
        printf("* pthread timeThreadProc create fail\n");
    }
}

TestForCall::~TestForCall()
{
     pthread_cancel( m_pthreadStruc);
}


void * 
TestForCall::timeThreadProc(void* data)
{
    TestForCall * ua = static_cast<TestForCall *> (data);
    assert (ua != NULL);
    
    //ua->setRegistrar("10.1.77.222");
    
    while (1)
    {
        time_t now;
        time( &now);
        double timeResult = difftime( now, *(ua->getBeginTime()));
        /*if (timeResult >=10)
        {
            ua->unregisterToProxy();
            
            //if (ua->registrationProcessor().isRegistrationSuccessful())
                // ua->unregisterToProxy();

            ua->registerToProxy( ua->getRegistrar());
            break;
        }
        
        if (timeResult >= 120)
        {
            printf( "*** In timeThreadProc, time out ***\n");
            ua->terminate( 0);
            break;
        }*/

        usleep(10);
    }
}

void
TestForCall::onCallProxyFailed( int linuNumber, const char * remoteUsername, const char * remoteHost)
{
    printf( "*** In TestForCall::onCallProxyFailed, remoteUsername is %s ***\n", remoteUsername);
    memset(callFlag, 0, 1024);
	strcpy(callFlag, "onCallProxyFailed");
}

void
TestForCall::onTerminated( int lineNumber, const char * remoteUsername, const char * remoteHost)
{
    printf( "*** In TestForCall::onTerminated, remoteHost is %s ***\n", remoteHost);
	isTerminated = true;
}

void 
TestForCall::onPeerRinging( int lineNumber, const char * remoteUsername, const char * remoteHost)
{
    printf( "*** In TestForCall::onPeerRinging, remoteHost is %s ***\n", remoteHost);
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onPeerRinging");
}

void 
TestForCall::onPeerBusy( int lineNumber, const char * remoteUsername, const char * remoteHost)
{
    printf( "*** In TestForCall::onPeerBusy, remoteUsername is %s ***\n", remoteUsername);
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onPeerBusy");
}

void
TestForCall::onStartMedia( int lineNumber, const char * remoteHost,
                         int remoteVideoPort, int remoteAudioPort, bool bSelfDialled)
{
    printf( "*** In TestForCall::onStartMedia, remoteHost is: %s ***\n", remoteHost);
    if (bSelfDialled)
        printf( "*** In TestForCall::onStartMedia, self call ***\n");
    else
        printf( "*** In TestForCall::onStartMedia, remote call ***\n");
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onStartMedia");
}

void
TestForCall::onStopMedia( int lineNumber)
{
    printf( "*** In TestForCall::onStopMedia ***\n");
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onStopMedia");
}

void
TestForCall::onConfirmed( int lineNumber, const char * remoteUsername, const char * remoteHost)
{
    printf( "*** In TestForCall::onConfirmed, remoteHost is %s ***\n", remoteHost);
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onConfirmed");
}

void
TestForCall::onRegistrationSuccess()
{
    printf( "*** In TestForCall::onRegistrationSuccess ***\n");
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onRegistrationSuccess");
}

void
TestForCall::onRegistrationFailure()
{
    printf( "*** In TestForCall::onRegistrationFailure ***\n");
    memset(callFlag, 0, 1024);
    strcpy(callFlag, "onRegistrationFailure");
}

