#include <stdio.h>
#include <iostream>
#include <string>

#include "state_machine.h"

using namespace std;

const char *TestEventStr[] = 
{
    "UNKOWNTESTEVENT",
    "TESTEVENT1",
    "TESTEVENT2",
    "TESTEVENT3",
};

State::State(string initStateStr) : d_stateStr(initStateStr)
{

}

string State::getStateStr()
{
    return d_stateStr; 
}

void State1::Handle(Context* pContext, TestEvent event)
{
    switch(event)
    {
        case TESTEVENT1:
          pContext->ChangeState(new State2);
            break;
        default:
            break;
    } 
}

void State2::Handle(Context* pContext, TestEvent event)
{
    switch(event)
    {
        case TESTEVENT2:
            pContext->ChangeState(new State3);
            break;
        default:
            break;
    }
}

void State3::Handle(Context* pContext, TestEvent event)
{
    switch(event)
    {
        case TESTEVENT3:
            pContext->ChangeState(new State1);
            break;
        default:
            break;
    }
}

Context::Context(State* pState) : d_state(pState)
{

}

Context::~Context()
{
    delete d_state;
    d_state = NULL;
}

void Context::Request(TestEvent event)
{
    d_state->Handle(this, event);
}

void Context::ChangeState(State *pState)
{
    if (d_state != NULL)
    {
        delete d_state;
        d_state = NULL;
    }

    d_state = pState;
}

string Context::getStateStr()   
{
    return d_state->getStateStr();
}

int main(int argc, char *argv[])
{
    char i = 0;
    string lastStateStr;

    //事件
    enum TestEvent event = UNKOWNTESTEVENT;  

    //初始状态
    Context context(new State1);

    while(1)
    {  
        cout << "input event (0-2):" << endl;
        cin >> i;
        switch(i)
        {  
            case '0': event = TESTEVENT1; break;  
            case '1': event = TESTEVENT2; break;  
            case '2': event = TESTEVENT3; break;
            case 'x': goto EXIT;
            default: break;  
        }

        lastStateStr = context.getStateStr();

        context.Request(event);

        printf("[%s]-[%s]->[%s]\n", lastStateStr.c_str(), TestEventStr[event], context.getStateStr().c_str());

        //sleep(1);
    }

EXIT:

    return 0;
}
