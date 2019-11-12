/*
    An example implementation of a Stack with dynamic array.
*/
#include <iostream>

const int INITIAL_CAPACITY = 16; // The default capacity when a Stack is created.

template <typename T>
class Stack
{
    private:
        T* arr; // Where stack elements will be saved.
        int topIdx; // The index of the top element
        int Capacity; // The current max capacity of the Stack

        bool isFull() const; // Returns true if the Stack is full, false otherwise
        void CopyStack(const Stack &); // A helper function to copy the data of other Stack
        void Resize(); // Doubles the capacity of the Stack when it goes full
        void DeleteStack(); // Destroys the Stack
    public:
        Stack(); // Default Constructor
        Stack(const Stack &); // Copy Constructor
        Stack& operator=(const Stack &); // Operator =
        ~Stack(); // Destructor

        bool Empty() const; // Returns true if the Stack is empty, false otherwise
        void Push(T const &); // Pushes a new element at the top of the Stack
        T Pop(); // Removes an element from the top of the Stack        
        T Top() const; // Returns the top element of the Stack
        void PrintElements() const;
};

template <typename T>
Stack<T>::Stack(): topIdx(-1), Capacity(INITIAL_CAPACITY)
{
    arr = new T[Capacity];
}

template <typename T>
Stack<T>::Stack(const Stack<T> & Other)
{
    CopyStack(Other);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T> & Other)
{
    if(this != &Other)
    {
        DeleteStack();
        CopyStack(Other);
    }
    return *this;
}

template <typename T>
Stack<T>::~Stack()
{
    DeleteStack();
}

template <typename T>
void Stack<T>::Resize()
{
    Capacity *= 2;
    T* newArr = new T[Capacity];
    for (int i = 0; i <= topIdx; i++)
    {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}

template <typename T>
void Stack<T>::Push(const T & el)
{
    if(isFull())
    {
        Resize();
    }
    arr[++topIdx] = el;
}


template <typename T>
void Stack<T>::CopyStack(const Stack<T> & Other)
{
    topIdx = Other.topIdx;
    Capacity = Other.Capacity;
    arr = new T[Capacity];
    for (int i = 0; i < topIdx; i++)
    {
        arr[i] = Other.arr[i];
    }   
}

template <typename T>
bool Stack<T>::isFull() const
{
    return topIdx == Capacity  - 1;
}

template <typename T>
bool Stack<T>::Empty() const
{
    return topIdx == -1;
}
template <typename T>
void Stack<T>::DeleteStack()
{
    delete[] arr;
}
template <typename T>
T Stack<T>::Top() const
{
    return arr[topIdx];
}
template <typename T>
T Stack<T>::Pop()
{
    if(Empty())
    {
        std::cerr<<"Empty Stack!"<<std::endl;
        return T();
    }
    return arr[topIdx--];
}

template <typename T>
void Stack<T>::PrintElements() const
{
    for (int i = 0; i < topIdx; i++)
    {
        std::cout<<arr[i]<<std::endl;
    }
    
}

int main()
{
    Stack<int> Numbers;
    
    for (int i = 0; i < 30; i++)
    {
        Numbers.Push(i);
    }
    Numbers.PrintElements();
}

