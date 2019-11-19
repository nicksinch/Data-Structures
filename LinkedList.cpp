/*
    An example implementation of a Singly Linked List
*/

#pragma once

#include <assert.h>
#include <iostream>

template <typename T>
class List
{
    public:
    class Box
    {
        public:
            T Data;
            Box* pNext;

            Box(const T & Data, Box* pNext = nullptr): Data(Data), pNext(pNext) {}
            bool HasSuccessor() const 
            { 
                return pNext != nullptr;
            }
    };

    class Iterator
    {
        private:
            Box* pStart; // Points to the first Box of the Linked List
            Box* pCurrent; // Points to the current Box of the Linked List
    
        public:
            Iterator(Box* pStart) : pStart(pStart), pCurrent(pStart) {}

            T const & GetCurrent() const // Retrieves the value of the current box
            {
                return pCurrent->Data;
            }

            void SetCurrent(T const & Element) // Sets a value to the current box
            {
                pCurrent->Data = Element;
            }

            void MoveNext() // Moves the iterator one step forward
            {
                if(pCurrent)
                    pCurrent = pCurrent->pNext; 
            }

            void Rewind()
            {
                pCurrent = pStart;
            }

            bool EndReached() const
            {
                return pCurrent == nullptr;
            }
    };

    private:
        Box* pFirst; // Points to the first element of the Linked List
        Box* pLast; // Points to the last element of the Linked List
        size_t Size; // Tracks the Size of the Linked List

        void ZeroVariables() // Initial values state
        {
            pFirst = pLast = nullptr;
            Size = 0;
        }

        static void DestroyChain(Box* pFirstBox) // Destroys the whole List starting from the first Box
        {
            Box* pCurrent = pFirstBox;
            Box* pOld = pFirstBox;

            while (pCurrent)
            {
                pOld = pCurrent;
                pCurrent = pCurrent->pNext;
                delete pOld;
            }
    }


        /*
            The function receives a pointer to the first box of the chain that is to be copied
            and creates a new, identical chain

            Paramter pCloneStart:
            If cloning has finished successfully, the function will use this parameter to return a pointer
            to the first box of the cloned chain, otherwise it will set the passed argument to nullptr

            Paramter pCloneEnd:
            If cloning has finished successfully, the function will use this parameter to return a pointer
            to the last box of the cloned chain, otherwise it will set the passed argument to nullptr
        */
        static void CloneChain(Box* pFirstBox, Box*& pCloneStart, Box*& pCloneEnd)
        {
            pCloneStart = nullptr;
            pCloneEnd = nullptr;

        if (pFirstBox == nullptr)
            return;

        Box* pNewChain = nullptr;

        try
        {
            // Pointer to the start of the new chain
            pNewChain = new Box(pFirstBox->Data); 

            // Pointer to the element that we have to copy next
            Box* pReadFrom = pFirstBox->pNext;

            // Pointer to the element after which we have to copy the new element
            Box* pWriteAfter = pNewChain;

            while (pReadFrom)
            {
                pWriteAfter->pNext = new Box(pReadFrom->Data);
                pWriteAfter = pWriteAfter->pNext;
                pReadFrom = pReadFrom->pNext;
            }

            pCloneStart = pNewChain;
            pCloneEnd = pWriteAfter;
        }
            catch (std::bad_alloc&)
            {
                DestroyChain(pNewChain);
            }
        }

        /*
            Finds and returns a Box at a specific index
        */
        Box* FindBoxAt(size_t Index) const
        {
            if(Index >= this->Size || Index < 0)
                return nullptr;
            
            Box *p = pFirst;

            for (size_t i = 0; i < Index; i++)
            {
                p = p->pNext;
            }
            return p;
        }


    public:

        List() // Default Constructor 
        {
            ZeroVariables();
        }

        List(const List & Other) // Copy Constructor
        {
            Append(Other);
        }

        List& operator=(const List & Other) // Operator =
        {
            if(this != &Other)
            {
                DestroyChain(pFirst);
                Append(Other);
            }
            return *this;   
        }

        ~List() // Destructor
        {
            DestroyChain(pFirst);
            ZeroVariables();
        }

        bool isEmpty() const // Returns true if the List is Empty, false otherwise
        {
            return (pFirst == nullptr);
        }

        T& Front() const // Returns the value from the first box
        {
            if(isEmpty())
                throw std::exception();
            return pFirst->Data;
        }

        T& Back() const // Returns the value from the last box
        {
            if(isEmpty())
                throw std::exception();
            return pLast->Data;
        }

        size_t GetSize() const
        {
            return Size;

        }
        void PushBack(const T& Element) // Pushes an element at the back of the List
        {
            Box* newValue = new Box(Element);

            if(isEmpty())
                pFirst = newValue;
            else
                pLast->pNext = newValue;
            
            pLast = newValue;
            ++Size;
        }

        void PushFront(const T& Element) // Pushes an element at the front of the list
        {
            Box* newValue = new Box(Element, pFirst);
            if(isEmpty())
                pLast = newValue;
            pFirst = newValue;
            ++Size;
        }


        void PopFront()
        {
            if(isEmpty()) 
                return; // We can only remove the head of a non-empty list
            
            Box* pOldHead = pFirst; // Point to the old first element
            
            pFirst = pFirst->pNext; // Advance the pointer one position forward
            
            // If this was the last element, the list is now empty and we have to set the last element pointer to null also
            if(pFirst == nullptr)
                pLast == nullptr;

            --Size;
            delete pOldHead;
        }
        void PopBack() // Removes an element from the end of the list, does nothing if the list is empty
        {
            if(!isEmpty())
                RemoveAt(Size - 1);
        }

        /*
            Copies and appends the contents of the other list to this one
            Returns:
                true, if the function succeeds in copying the data
                false, if the function fails and the list remains unchanged
        */
        bool Append(List const & Other)
        {
               // If there is nothing to copy, don't copy :-)
        if (Other.isEmpty())
            return true;

        // Try to clone the data from the other list
        Box *pNewChainStart, *pNewChainEnd;
        CloneChain(Other.pFirst, pNewChainStart, pNewChainEnd);

        if (!pNewChainStart)
            return false;

        if (Size == 0)
            pFirst = pNewChainStart;
        else
            pLast->pNext = pNewChainStart;

        pLast = pNewChainEnd;            

        Size += Other.Size;

        return pNewChainStart != nullptr;
        }

        /* Removes the element at the specified index */
        void RemoveAt(size_t Index)
        {
            if(Index>=Size)
                throw std::out_of_range("Index exceeds the number of elements in the list");
            
            if(Index == 0)
                PopFront();
            /*
                If we reach this case, it means the following should be true:
                    1. We are not trying to remove the first element
                    2. Index != 0
                    3. There are at least two elements in the list
            */
            else
            {
                assert(this->GetSize() >= 2);

                Box* pBoxBeforeIndex = FindBoxAt(Index - 1); // Find the box before the one we want to remove
                assert(pBoxBeforeIndex != nullptr);
                
                Box* pBoxToRemove = pBoxBeforeIndex->pNext;

                // Now if the box that we want to remove is the last one, update the new pointer to the last element (pLast)
                if(Index == Size - 1)
                    pLast = pBoxBeforeIndex;
                
                pBoxBeforeIndex->pNext = pBoxToRemove->pNext;

                delete pBoxToRemove;

                --Size; 
            
        }
    }


        // void InsertAfter(Iterator position, const T& Element)
        // {
        //     if(position == end() || empty()){
        //         push_back(value_);
        //         return;
        //     }
        //     Node *node = new Node(value_);
        //     node->next = position.ptr->next;
        //     position.ptr->next = node;
        // }

        Iterator GetIterator() const
        {
            return Iterator(pFirst);
        }
};

int main()
{
    List<int> RandomInts;
    for (size_t i = 0; i < 6; i++)
    {
        RandomInts.PushBack(i);
    }
    RandomInts.RemoveAt(2);

    List<int> CopyInts(RandomInts);

    for (List<int>::Iterator it = CopyInts.GetIterator(); !it.EndReached();it.MoveNext())
    {
        std::cout<<it.GetCurrent()<<std::endl;
    }
}