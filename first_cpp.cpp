
#include <iostream>
#include <vector>

using namespace std;

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
    int i = 0;
    string lastStateStr;

    //事件
    enum TestEvent event = UNKOWNTESTEVENT;  

    //初始状态
    Context context(new State1);

    while(1)
    {  
        int a = 0;
        cout << "input event (0-2): " << endl;
        cin >> a;
        switch(a)
        {  
            case 0: event = TESTEVENT1; break;  
            case 1: event = TESTEVENT2; break;  
            case 2: event = TESTEVENT3; break;  
            default: break;  
        }

        i++;  

        lastStateStr = context.getStateStr();

        context.Request(event);

        printf("[%s]-[%s]->[%s]\n", lastStateStr.c_str(), TestEventStr[event], context.getStateStr().c_str());

        //sleep(1);
    }

    return 0;
}





/*

void func (const char* name, char* mac = nullptr)
{
    printf ("sizeof name = %d\n", sizeof(name));
}

int main ()
{

    char name1[] = "abc";
    char name2[10] = "abc";
    char* name3 = "abc";

    char* name4 = name2;

    func(name1);
    func(name2);
    func(name3);
    func(name4);

    int x = 1;

    [&](void)
    {
        x = 2;
    };

    while (x)
    {
        cout << "hello world!" << endl;
        vector<int> age;
        age.push_back(10);
        age.push_back(12);
        age.push_back(15);
        age.push_back(30);
        for (auto i : age)
        {
            cout << i << endl;
        }
        cin >> x;
    }
    return 0;
}

*/