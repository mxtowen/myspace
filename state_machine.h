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
    eDisconnect         = 1,        // plug out iphone        
    eStarting           = 2,        // start session
    eForegroud          = 3,        // phonecall | siri | media in foreground
    eForegroudTemp      = 4,        // alert | phonecall, controller borrow screen and audio
    eBackgroudHalf      = 5,        // screen : accessary, audio : controller
    eBackgroudFull      = 6,        // screen : accessary, audio : acceessary
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
        StateType current_state_;
        StateType last_state_;
};

class  StateDisconnect : public State
{
    public:
        void Handle(Context* pContext, TestEvent event);
        // void StateIn();
        // void StateOut();
        StateDisconnect() : State("StateDisconnect")
        {
        }
};

class StateStarting : public State
{
    public:
        void Handle(Context* pContext, TestEvent event);
        // void StateIn();
        // void StateOut();
        StateStarting() : State("StateStarting")
        {
        }

};

class StateForegroud : public State
{
    public:
        void Handle(Context* pContext, TestEvent event);
        // void StateIn();
        // void StateOut();
        StateForegroud() : State("StateForegroud")
        {
        }
};

class StateForegroudTemp : public State
{
    public:
        void Handle(Context* pContext, TestEvent event);
        // void StateIn();
        // void StateOut();
        StateForegroudTemp() : State("StateForegroudTemp")
        {
        }
};

class StateBackgroudHalf : public State
{
    public:
        void Handle(Context* pContext, TestEvent event);
        // void StateIn();
        // void StateOut();
        StateBackgroudHalf() : State("StateBackgroudHalf")
        {
        }
};

class StateBackgroudFull : public State
{
    public:
        void Handle(Context* pContext, TestEvent event);
        // void StateIn();
        // void StateOut();
        StateBackgroudFull() : State("StateBackgroudFull")
        {
        }
};

#endif
