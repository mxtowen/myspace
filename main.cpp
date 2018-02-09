#include <stdio.h>
#include <iostream>
#include <string>

#include "state_machine.h"
//#include "event_queue.h"

#include <mutex>

#include <tuple>

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

void StateDisconnect::Handle(Context* pContext, TestEvent event)
{
    switch(event)
    {
        case TESTEVENT1:
          pContext->ChangeState(eDisconnect);
            break;
        default:
            break;
    } 
}

void StateStarting::Handle(Context* pContext, TestEvent event)
{
    switch(event)
    {
        case TESTEVENT2:
            pContext->ChangeState(eDisconnect);
            break;
        default:
            break;
    }
}

void StateForegroud::Handle(Context* pContext, TestEvent event)
{
    switch(event)
    {
        case TESTEVENT3:
            pContext->ChangeState(eDisconnect);
            break;
        default:
            break;
    }
}

void StateForegroudTemp::Handle(Context* pContext, TestEvent event)
{
    switch(event)
    {
        case TESTEVENT3:
            pContext->ChangeState(eDisconnect);
            break;
        default:
            break;
    }
}

void StateBackgroudFull::Handle(Context* pContext, TestEvent event)
{
    switch(event)
    {
        case TESTEVENT3:
            pContext->ChangeState(eDisconnect);
            break;
        default:
            break;
    }
}

void StateBackgroudHalf::Handle(Context* pContext, TestEvent event)
{
    switch(event)
    {
        case TESTEVENT3:
            pContext->ChangeState(eDisconnect);
            break;
        default:
            break;
    }
}

Context::Context()
{
    Init();
    // init state
    //d_state = state_list_[eDisconnect];
}

Context::~Context()
{
    //delete d_state;
    Release();
}

void Context::Init(void)
{
    for (int i = 1; i < eState_Max; ++i)
    {
        StateFactory((StateType)i);
    }
}

void Context::Release(void)
{
    for (auto& i : state_list_)
    {
        delete i.second;
        i.second = NULL;
    }
    state_list_.clear();

    d_state = NULL;
}


void Context::Request(TestEvent event)
{
    d_state->Handle(this, event);
}

void Context::ChangeState(StateType state)
{
    auto it = state_list_.find(state);
    if (it != state_list_.end())
    {// find it
        d_state = it->second;
    }
    // if (d_state != NULL)
    // {
    //     delete d_state;
    //     d_state = NULL;
    // }

    // d_state = pState;
}

string Context::getStateStr()   
{
    return d_state->getStateStr();
}

void Context::StateFactory(StateType state)
{
    // switch (state)
    // {
    // case eState1:
    //     state_list_[state] = new State1;
    //     break;
    // case eState2:
    //     state_list_[state] = new State2;
    //     break;
    // case eState3:
    //     state_list_[state] = new State3;
    //     break;
    // default:
    //     break;
    // }
}


int main(int argc, char *argv[])
{
    //SeqQueue<int> queue;
    std::tuple<int, int> ll;
    std::mutex mtx;

    char i = 0;
    string lastStateStr;

    //事件
    enum TestEvent event = UNKOWNTESTEVENT;  

    //初始状态
    Context context;

    //context.Request(TESTEVENT1);

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
