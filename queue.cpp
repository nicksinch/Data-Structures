// /*
//     An example implementation (Contiguous) of a Queue Data Structure.
// */

// #include <iostream>

// const int MAX_SIZE = 6;

// template <typename T>
// class Queue
// {
//     private:
//         T arr[MAX_SIZE];
//         int Front, Back, Size;
//         bool isFull() const;
    
//     public:
//     Queue(); // Default Constructor
    
//     bool isEmpty() const; // Returns true if Queue is empty, false otherwise
//     void Push(const T&); // Adds a new element
//     T Pop(); // Removes the first element of the Queue
//     T front() const; // Returns the first element of the Queue
// };

// template <typename T>
// Queue<T>::Queue() :  Back(0), Front(0), Size(0) {}

// template <typename T>
// bool Queue<T>::isFull() const
// {
//     return Size == MAX_SIZE;
// }

// template <typename T>
// bool Queue<T>::isEmpty() const
// {
//     return Size == 0;
// }

// template <typename T>
// T Queue<T>::front() const
// {
//     if(isEmpty())
//     {
//         return T();
//         std::cerr<<"Queue is empty!"<<std::endl;
//     }
//     return arr[Front];
// }

// template <typename T>
// void Queue<T>::Push(const T & Element)
// {
//     if(isFull())
//     {
//         std::cerr<<"Queue is Full!"<<std::endl;
//         return;
//     }
//     arr[Back++] = Element;
//     Size++;
//     Back = Back % MAX_SIZE;
// }

// template <typename T>
// T Queue<T>::Pop()
// {
//     if(isEmpty())
//     {
//         std::cerr<<"Queue is empty!"<<std::endl;
//         return T();
//     }
//     T Removed = arr[Front];
//     Size--;
//     Front++;
//     Front = Front % MAX_SIZE;
//     return Removed;
// }

// int main()
// {
//     Queue<int> People;
//     People.Push(1);
//     People.Push(2);
//     People.Push(3);
//     People.Push(4);
//     People.Push(5);
//     People.Push(6);
//     People.Push(7);
//     std::cout<<People.Pop()<<std::endl;
//     std::cout<<People.Pop()<<std::endl;
//     std::cout<<People.Pop()<<std::endl;
//     std::cout<<People.Pop()<<std::endl;
//     std::cout<<People.Pop()<<std::endl;
//     std::cout<<People.Pop()<<std::endl;

// }