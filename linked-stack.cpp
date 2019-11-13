// /*
//     An example implementation of a Stack using Singly Linked List.
// */

// #include <iostream>

// template <typename T>
// class LinkedStack
// {
//     class Box
//     {
//         public:
//             T Data;
//             Box* pNext;

//             Box(const T & Data, Box* pNext = NULL ):Data(Data),pNext(pNext){} 
//     };
//     private:
        
//         Box* pTop; // Pointer to the top of the Stack
//         size_t Size; // Size of the Stack

//         void ZeroVariables() // Default values
//         {
//             pTop = nullptr;
//             Size = 0;
//         }

//         void Destroy()
//         {
//             Box* tmpPoint;
//             while(pTop)
//             {
//                 tmpPoint = pTop;
//                 pTop = pTop->pNext;
//                 delete tmpPoint;
//             }
//             ZeroVariables();
//         } 
    
//     public:

//         LinkedStack() //Default Constructor
//         {
//             ZeroVariables(); 
//         }
//         LinkedStack(const LinkedStack & Other)
//         {
//             ZeroVariables(); 
//             CopyFrom(Other); // Cleans up all the resources if copying fails
//         }

//         /*
//             The operator frees the currently allocated memory first and after that performs copying
//             If copyting fails, Stack will be left empty
//         */
//         LinkedStack& operator=(const LinkedStack & Other)
//         {
//             if(this != &Other)
//             {
//                 Destroy();
//                 CopyFrom(Other);
//             }
//             return *this;
//         }
//         ~LinkedStack() // Destructor
//         {
//             Destroy();
//         }

//         void Push(const T & Element) // Pushes a new element on top of the Stack
//         {
//                 pTop = new Box(Element, pTop);
//                 ++Size;
//         }

//         void Pop()
//         {
//             if(pTop)
//             {
//                 Box* pOld = pTop;
//                 pTop = pTop->pNext;
//                 delete pOld;
//                 --Size;
//             }
//         }

//         bool isEmpty() const // Returns true if Stack is Empty
//         {
//             return Size == 0;
//         }

//         const T& Top() const
//         {
//             if(isEmpty())
//                 std::cerr<<"Stack is Empty!"<<std::endl;
            
//             return pTop->Data;
//         }
//         void CopyFrom(const LinkedStack & Other)
//         {
//             if(Other.isEmpty()) // If the other Stack is Empty, we do nothing
//                 return;
            
//             Box* oursTmp, *otherTmp; // Helper pointers for our New and Old Stacks respectively
//             try
//             {
//                 pTop = new Box(Other.pTop->Data);
//                 oursTmp = pTop;
//                 otherTmp = Other.pTop->pNext;

//                 while(otherTmp)
//                 {
//                     oursTmp->pNext = new Box(otherTmp->Data);
//                     oursTmp = oursTmp->pNext;
//                     otherTmp = otherTmp->pNext; 
//                 }
//                 Size = Other.Size;
//             }
//             catch (std::bad_alloc&)
//             {
//                 Destroy();	    // OK to call it, because:
//                                     // 1. pTop points to the top of the cloned chain
//                                   // 2. Boxes are allocated in such a manner, so that the
//                                 //    for the last box pNext == NULL
//                 throw;
//             }
//         }
// };
// int main()
// {
//     LinkedStack<int> Numbers;
//     for (int i = 10; i < 20; i++)
//     {
//         Numbers.Push(i);
//     }
//     LinkedStack<int> CopyNums(Numbers);
    
//     for (size_t i = 0; i < 10; i++)
//     {
//         std::cout<<CopyNums.Top()<<std::endl;
//         CopyNums.Pop();
//     }
// }
