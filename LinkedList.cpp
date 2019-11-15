// /*
//     An example implementation of a Singly Linked List
// */

// #include <iostream>

// template <typename T>
// class List
// {
//     class Box
//     {
//         public:
//             T Data;
//             Box* pNext;

//             Box(const T & Data, Box* pNext = nullptr): Data(Data), pNext(pNext) {}
//             bool HasSuccessor() const 
//             { 
//                 return pNext != nullptr;
//             }
//     };

//     class Iterator
//     {
//         private:
//             Box* pStart; // Points to the first Box of the Linked List
//             Box* pCurrent; // Points to the current Box of the Linked List

//         public:
//             Iterator(Box* pStart) : pStart(pStart), pCurrent(pStart) {}

//             T const & GetCurrent() const // Retrieves the value of the current box
//             {
//                 return pCurrent->Data;
//             }

//             void SetCurrent(T const & Element) // Sets a value to the current box
//             {
//                 pCurrent->Data = Element;
//             }

//             void MoveNext() // Moves the iterator one step forward
//             {
//                 if(pCurrent)
//                     pCurrent = pCurrent->pNext; 
//             }

//             void Rewind()
//             {
//                 pCurrent = pStart;
//             }

//             bool EndReached() const
//             {
//                 return pCurrent = nullptr;
//             }
//     };

//     private:
//         Box* pFirst; // Points to the first element of the Linked List
//         Box* pLast; // Points to the last element of the Linked List
//         size_t Size; // Tracks the Size of the Linked List

//         void ZeroVariables() // Initial values state
//         {
//             pFirst = pLast = nullptr;
//             Size = 0;
//         }

//         void DestroyChain() // Destroys the whole List
//         {
//             Box* pCurrent = pFirst;
//             Box* pOld = pFirst;

//             while(pCurrent)
//             {
//                 pOld = pCurrent;
//                 pCurrent = pCurrent->pNext;
//                 delete pOld;
//             }
//         }


//     public:

//         List() // Default Constructor 
//         {
//             ZeroVariables();
//         }

//         List(const List & Other) // Copy Constructor
//         {
//             CopyList(Other);
//         }

//         List& operator=(const List & Other) // Operator =
//         {
//             if(this != &Other)
//             {
//                 DestroyChain();
//                 CopyList(Other);
//             }
//             return *this;   
//         }

//         ~List() // Destructor
//         {
//             DestroyChain();
//             ZeroVariables();
//         }

//         bool isEmpty() const // Returns true if the List is Empty, false otherwise
//         {
//             return (pFirst == nullptr);
//         }

//         T& Front() const // Returns the value from the first box
//         {
//             if(isEmpty())
//                 throw std::exception();
//             return pFirst->Data;
//         }

//         T& Back() const // Returns the value from the last box
//         {
//             if(isEmpty())
//                 throw std::exception();
//             return pLast->Data;
//         }

//         void PushBack(const T& Element) // Pushes an element at the back of the List
//         {
//             Box* newValue = new Box(Element);

//             if(isEmpty())
//                 pFirst = newValue;
//             else
//                 pLast->pNext = newValue;
            
//             pLast = newValue;
//             ++Size;
//         }


//         // void InsertAfter(Iterator position, const T& Element)
//         // {
//         //     if(position == end() || empty()){
//         //         push_back(value_);
//         //         return;
//         //     }
//         //     Node *node = new Node(value_);
//         //     node->next = position.ptr->next;
//         //     position.ptr->next = node;
//         // }

//         Iterator GetIterator() const
//         {
//             return Iterator(pFirst);
//         }
// };

// int main()
// {
//     List<int> RandomInts;
//     RandomInts.PushBack(4);
//     RandomInts.GetIterator();
//     std::cout<<RandomInts.Front();
// }