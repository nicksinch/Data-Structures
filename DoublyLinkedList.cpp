#pragma once

/*
    An example implementation of a Doubly Linked List.
    Iterator operators are redefined here. ( Not like the implementation of the Singly Linked List)
*/

#include <iostream>

template <typename T>
class DoubleLinkedList
{
    public:
        class Box
        {
            public:
                T Data;
                Box* pNext;
                Box* pPrevious;

                Box(T Data, Box* pNext = nullptr, Box* pPrevious = nullptr) : Data(Data), pNext(pNext), pPrevious(pPrevious) {}
        };

        class Iterator
        {
            private:
                Box* ptr;
            public:
                Iterator() // Default Constructor
                {
                    ptr = nullptr;
                }
                Iterator(Box* otherP) // Copy Constructor
                {
                    ptr = otherP;
                }
                Iterator& operator=(const Iterator & Other) // Assignment operator
                {
                    ptr = Other.ptr;
                }
                bool operator!=(const Iterator& Other) const // Not equal operator
                {
                    return ptr != Other.ptr;
                }
                bool operator==(const Iterator& Other) const  // Equals operator
                {
                    return ptr == Other.ptr;
                }
                Iterator& operator++() // Moves the iterator to the next Box
                {
                    ptr = ptr->pNext;
                }
                Iterator& operator--() // Moves the iterator to the previous Box
                {
                    ptr = ptr->pPrevious;
                }
                Iterator operator+(const unsigned int Num) // Moves the iterator Num Boxes forward
                {
                    Box* tmp = ptr;
                    for (int i = 0; i < Num && tmp ; i++)
                        tmp = tmp->pNext;

                    return Iterator(tmp);
                }
                Iterator operator-(const unsigned int Num) // Moves the iterator Num Boxes backwards
                {
                    Box* tmp = ptr;
                    for (int i = 0; i < Num && tmp ; i++)
                        tmp = tmp->pPrevious;

                    return Iterator(tmp);
                }

                T& operator*() // Dereferencing operator ( returns the value of the pointed Box)
                {
                    return ptr->Data;
                }

                friend void DoubleLinkedList<T>::InsertAfter(Iterator, const T &);
                friend void DoubleLinkedList<T>::InsertBefore(Iterator, const T &);
                friend void DoubleLinkedList<T>::DeleteAt(Iterator);

               
        };

    private:
        Box *pFirst;
        Box *pLast;
        void CopyList(const DoubleLinkedList& Other) // A helper function used in Copy Constructor
        {
            pFirst = nullptr;
            Box* tmp = Other.pFirst;
            while(tmp)
            {
                PushBack(tmp->Data);
                tmp = tmp->pNext;
            }
        }
        void DeleteList() // A helper function used in Destructor
        {
            while(pFirst)
            {
                Box* tmp = pFirst;
                pFirst = pFirst->pNext;
                delete tmp;
            }
            pFirst = pLast = nullptr;
        }

        public:
            DoubleLinkedList()
            {
                pFirst = pLast = nullptr;
            }
            DoubleLinkedList(const DoubleLinkedList & Other)
            {
                CopyList(Other);
            }
            DoubleLinkedList& operator=(const DoubleLinkedList & Other)
            {
                if(this != &Other)
                {
                    DeleteList();
                    CopyList(Other);
                }
                return *this;
            }
            ~DoubleLinkedList()
            {
                DeleteList();
            }
            bool isEmpty() // Returns true if the List is Empty, false otherwise
            {
                return pFirst == nullptr;
            }
            void PushBack(const T& Value)
            {
                Box* newValue = new Box(Value);
                if(isEmpty())
                    pFirst = newValue;
                else{
                    pLast->pNext = newValue;
                    newValue->pPrevious = pLast;
                }
                pLast = newValue;
            }
            void InsertAfter(Iterator Position, const T& Value) // Inserts a new Box at a specific position in the chain
            {
                if(Position == End() || isEmpty())
                {
                    PushBack(Value);
                    return;
                }
                Box* newValue = new Box(Value); // Create the new Box
                
                newValue->pNext = Position.ptr->pNext; 
                newValue->pPrevious = Position.ptr;
                Position.ptr->pNext = newValue; 
                (newValue->pNext)->pPrevious = newValue; // Don't forget this!
            }
            void InsertBefore(Iterator Position, const T& Value)
            {
                if(isEmpty())
                {
                    PushBack(Value);
                    return;
                }
                Box* newValue = new Box(Value);
                newValue->pNext = Position.ptr;
                if(Position != Begin())
                {
                    (Position.ptr->pPrevious)->pNext = newValue;
                    newValue->pPrevious = Position.ptr->pPrevious;
                }
                Position.ptr->pPrevious = newValue;
            }
            void DeleteAt(Iterator Position)
            {
                if(isEmpty())
                    return;
                if(Position == End())
                {
                    Box* tmp = pLast->pPrevious;
                    delete pLast;
                    pLast = tmp;
                }
                else
                {
                    Box* temp = Position.ptr->pNext;
                    temp->pPrevious = Position.ptr->pPrevious;
                    (Position.ptr->pPrevious)->pNext = temp;
                    delete Position.ptr;
                    Position.ptr = temp->pNext;
                }
            }
            Iterator Begin()const
            {
                return Iterator(pFirst);
            }
            Iterator End()const
            {
                if(pLast != nullptr)
                    return Iterator(pLast->pNext);
                return Iterator(nullptr);
            }
};
int main()
{
    DoubleLinkedList<int> LinkedInts;
    for (int i = 0; i < 10; i++)
    {
        LinkedInts.PushBack(i);
    }
    int i = 0;
    for(DoubleLinkedList<int>::Iterator it = LinkedInts.Begin(); it!= LinkedInts.End(); ++it)
    {
        if(i == 3)
        {
            LinkedInts.InsertBefore(it, 3579);
        }
        std::cout<<*it<<std::endl;
        i++;
    }
    
}