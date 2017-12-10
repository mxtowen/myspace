#ifndef STATEPATTERN
#define STATEPATTERN

#include <stdio.h>
#include <string>
#include <map>

using namespace std;

enum TestEvent
{
    UNKOWNTESTEVENT     =   0,
    TESTEVENT1          =   1,
    TESTEVENT2          =   2,
    TESTEVENT3          =   3,
};

enum StateType
{
    enull = 0,
    eState1 = 1,
    eState2 = 2,
    eState3 = 3,
    eState4 = 4,
    eState_Max,
};

class Context;

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

class Context
{
    public:
        Context();
        ~Context();
        void Request(const TestEvent event);
        void ChangeState(const StateType state);
        string getStateStr(void);
    private:
        void StateFactory(const StateType state);
        void Init(void);
        void Release(void);
        map<StateType, State*> state_list_;
        State* d_state;
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
