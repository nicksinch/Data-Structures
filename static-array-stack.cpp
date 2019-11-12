/*
    An example implementation of a Stack using static array.
*/

#include <iostream>

const int MAX_SIZE = 32; // The default max size of the Stack

template <typename T>
class Stack
{
    private:
        T arr[MAX_SIZE]; // An array to store the elements
        int topIdx; //  Size of Stack is topIdx - 1 and accesses the top element of the Stack
        bool isFull() const; // Returns true if the Stack is Full, false otherwise
    public:
    Stack(); // Default Constructor
    
    bool Empty() const; // Returns true if the Stack is Empty, false otherwise
    void Push(T const &);
    T Pop(); //Deletes the element at the top of the Stack        
    T Top() const; // Returns the element at top of the Stack, if there is any
    
    void PrintElements() const; // Prints the elements of the Stack
};
template <typename T>
Stack<T>::Stack(): topIdx(-1){}

template <typename T>
bool Stack<T>::isFull() const
{
    return topIdx == MAX_SIZE  - 1;
}

template <typename T>
bool Stack<T>::Empty() const
{
    return topIdx == -1;
}

template <typename T>
void Stack<T>::Push(T const & el)
{
    if(isFull())
    {
        std::cerr<<"Stack is full!"<<std::endl;
        return;
    }
    arr[++topIdx] = el;
}
template <typename T>
T Stack<T>::Pop()
{
    if(Empty())
    {
        std::cerr<<"Stack is empty!";
        return T();
    }
    return arr[topIdx--];
}
template <typename T>
T Stack<T>::Top() const
{
    if(Empty())
    {
        std::cerr<<"Stack is empty!";
        return T();
    }
    return arr[topIdx];
}

template <typename T>
void Stack<T>::PrintElements() const
{
    for (int i = 0; i < topIdx; i++)
    {
        std::cout<<arr[i]<<std::endl;
    }   
}

int main() {
    Stack<int> Numbers;
    
    for (int i = 50; i < 80; i++)
    {
        Numbers.Push(i);
    }

    Numbers.PrintElements();
}