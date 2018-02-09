#ifndef _EVENT_QUEUE_
#define _EVENT_QUEUE_

#include "D:/soft/MinGW/lib/gcc/mingw32/5.3.0/include/c++/mutex"

class EventQueue
{

};

template<class T>
class SeqQueue{
    protected:
        T *element;
        int front,rear;
        int maxSize;
        std::mutex mtx_;
    public:
        SeqQueue(int sz=10){
            front=rear=0;
            maxSize=sz;
            element=new T[maxSize];
        }
        ~SeqQueue(){
            delete[] element;
        }
        bool EnQueue(const T& x){//入队 
            if(isFull()) return false;
            mtx_.lock();
            element[rear]=x;
            rear=(rear+1)%maxSize;
            mtx_.unlock();
            return true;
        }
        bool DeQueue(T& x){//出队 
            if(isEmpty()) return false;
            mtx_.lock();
            x=element[front];
            front=(front+1)%maxSize;
            mtx_.unlock();
            return true;
        }
        bool getFront(T& x){//获取队首元素 
            if(isEmpty()) return false;
            x=element[front];
            return true;
        }
        void makeEmpty(){//队列置空 
            front=rear=0;
        }
        bool isEmpty()const{//判断队列是否为空 
            return (rear==front)?true:false;
        }
        bool isFull()const{//队列是否为满
             return ((rear+1)%maxSize==front)?true:false;
        }
        int getSize()const{
            return (rear-front+maxSize)%maxSize;
        }
};

#endif