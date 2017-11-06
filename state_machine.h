#ifndef STATEPATTERN
#define STATEPATTERN

#include <stdio.h>
#include <string>

using namespace std;

enum TestEvent
{
    UNKOWNTESTEVENT     =   0,
    TESTEVENT1          =   1,
    TESTEVENT2          =   2,
    TESTEVENT3          =   3,
};

class State;

class Context
{
    public:
        Context(State* pState);
        ~Context();
        void Request(TestEvent event);
        void ChangeState(State *pState);
        string getStateStr(void);   
    private:
        State *d_state;
};

class State
{
    public:
        State(string initStateStr="unknown_state");

        virtual ~State(){}

        virtual void Handle(Context* pContext, TestEvent event) = 0;

        //virtual void StateIn() = 0;

        //virtual void StateOut() = 0;

        string getStateStr();

        string d_stateStr;
};

class  State1 : public State
{
    public:
        void Handle(Context* pContext, TestEvent event);
        // void StateIn();
        // void StateOut();
        State1() : State("state1")
        {
        }
};

class State2: public State
{
    public:
        void Handle(Context* pContext, TestEvent event);
        // void StateIn();
        // void StateOut();
        State2() : State("state2")
        {
        }

};

class State3: public State
{
    public:
        void Handle(Context* pContext, TestEvent event);
        // void StateIn();
        // void StateOut();
        State3() : State("state3")
        {
        }
};

#endif
