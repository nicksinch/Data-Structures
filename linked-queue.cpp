/*
    An example implementation ( Non - Contiguous ) of a Queue Data Structure.
*/

#include <iostream>

template <typename T>
class LinkedQueue
{
    class Box
    {
        public:
            T Data;
             Box* pNext;

            Box(const T& Data, pNext = nullptr): Data(Data), pNext(pNext){}
    };

    private:
        Box* frontElement, *rearElement;
        void CopyQueue(const LinkedQueue<T> &); // A helper function to copy from other Queue
        void DestroyQueue();
    
    public:
        LinkedQueue(); // Default Constructor
        LinkedQueue(const LinkedQueue<T> &); // Copy Constructor
        LinkedQueue& operator=(const LinkedQueue<T> &); // Operator =
        ~LinkedQueue(); // Destructor
    
        bool isEmpty() const; // Returns true if Queue is empty, false otherwise
        void Push(const T&); // Adds a new element
        void Pop(); // Removes the first element of the Queue
        const T& Front() const; // Returns the first element of the Queue
};

template <typename T>
void LinkedQueue<T>::CopyQueue(const LinkedQueue<T>& Other )
{
    if(Other.isEmpty())
        {
            std::cerr<<"Nothing to Copy because Queue is Empty!"<<std::endl;
            return;
        }
    Box* otherPtr = Other.frontElement;
    while(otherPtr)
    {
        Push(otherPtr->value);
        otherPtr = otherPtr->pNext;
    }    
}

template <typename T>
void LinkedQueue<T>::DestroyQueue()
{
    while(!isEmpty())
        Pop();
}

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
    frontElement = rearElement = nullptr; // In the beginning every queue is empty!
}

 template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& Other)
{
    frontElement = rearElement = nullptr;
    CopyQueue(Other);
}   

template <typename T>
LinkedQueue<T>& LinkedQueue<T>:: operator=(const LinkedQueue<T>& Other)
{
    if(this!= &Other)
    {
        DestroyQueue();
        CopyQueue(Other);
    }
    return *this;
}   

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    DestroyQueue();
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
    return (frontElement == nullptr);
}

template <typename T>
const T& LinkedQueue<T>::Front() const
{
    if(isEmpty())
    {
        std::cerr<<"Queue is empty!"<<std::endl;
        return T();
    }
    return frontElement->Data;
}

template <typename T>
void LinkedQueue<T>::Push(const T & Element)
{
    Box* newValue = new Box(Element);
    if(isEmpty())
    {
        frontElement = newValue;
    }
    else{       
        rearElement->pNext = newValue;
        rearElement = newValue;
    }
}

template <typename T>
void LinkedQueue<T>::Pop()
{
    if(isEmpty())
    {
        std::cerr<<"Queue is empty!"<<std::endl;
        return;
    }
    Box* tempFront = frontElement;
    frontElement = frontElement->pNext;
    delete tempFront;
}

int main()
{
    LinkedQueue<int> People;
    People.Push(1);
    People.Push(2);
    People.Push(3);
    People.Push(4);
    People.Push(5);
    People.Push(6);
    People.Push(7);
    
    for (size_t i = 0; i < 7; i++)
    {
        std::cout<<People.Front();
    }
    

}