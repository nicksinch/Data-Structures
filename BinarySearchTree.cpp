/* An example implementation of a Binary Search Tree that allows duplicate values. */

#include <iostream>
#include <stack>
void Swap(int& FirstValue, int& SecondValue)
{
	int Temp = FirstValue;
	FirstValue = SecondValue;
	SecondValue = Temp;
}



// The structure of the nodes that represent the tree
struct Node { 
	Node(int _key) {
		Key = _key;
        Count = 1;
		Left = nullptr;
		Right = nullptr;
	}
	int Key;
	int Count; // This will be used to store duplicate values in the BST
	Node* Left;
	Node* Right;
};

/* Finding the Node that contains the minimum element Recursively */
Node* TreeMinimum(Node* x) // O(h), h is the height of the tree
{
	if (x == nullptr)
		return nullptr;
	if (x->Left != nullptr)
		return TreeMinimum(x->Left);
	else
		return x;
}

/* Minimum element implemented iteratively */
Node* TreeMinimumIteratively(Node* x) // O(h), h is the height of the tree
{
	while (x->Left != nullptr)
		x = x->Left;
	return x;
}

/* Maximum function is symmetric to the minimum*/
Node* TreeMaximum(Node* x) // O(h), h is the height of the tree
{
	while (x->Right != nullptr)
		x = x->Right;
	return x;
}


/* Counts the UNIQUE Nodes in the tree
 ( if a node is duplicated ( occurs more than once ) , it is only counted once */
int CountNodes(Node* Root)
{
	if (Root == nullptr)
		return 0;
	return 1 + CountNodes(Root->Left) + CountNodes(Root->Right);
}
void AddNode(Node*& Dest, int Key)
{
	if (Dest == nullptr)
	{
		Node* NewNode = new Node(Key);
		Dest = NewNode;
	}
	else
	{
	    if( Key == Dest->Key) // If the value already exists
        {
	        ++(Dest->Count); // Increment its count by 1
	        return;
        }
		if (Key > Dest->Key)
			AddNode(Dest->Right, Key);
		else AddNode(Dest->Left, Key);
	}
}
void DeleteNode(Node*& N, int Key)
{
	if (N == nullptr) // Base case
		return;
	else if (N->Key == Key)
	{
	    if(N->Count > 1) // If the key is presented more than once
        {
	        --(N->Count); // Simply decrement it and exist
	        return;
        }
		if (N->Left == nullptr && N->Right == nullptr) // There are no subtrees
		{
			delete N;
            N = nullptr;
		}
		else if (N->Left == nullptr) // Only Right subtree
		{
			Node* Temp = N->Right;
			delete N;
			N = Temp;
		}
		else if (N->Right == nullptr) // Only Left Subtree
		{
			Node* Temp = N->Left;
			delete N;
            N = Temp;
		}
		else   // Left and Right Subtrees
		{
			Node* Min = TreeMinimum(N->Right);//finding the min element from the right subtree

			//Swapping two elements;
			Swap(Min->Key, N->Key);

			DeleteNode(N->Right, Key); // we could use it directly the pointer min,but we wouldn't take care of the pointer from the parrent
		}
	}
	else if (Key > N->Key)
		DeleteNode(N->Right, Key);
	else
		DeleteNode(N->Left, Key);
}
Node* Search(Node* x, int Key) /* Time complexity is, of course, O(h), where h is the height of the tree */
{
	if (x == nullptr || x->Key == Key )
		return x;
	else if (x->Key > Key)
		return Search(x->Left, Key);
	else return Search(x->Right, Key);
};

/*
	An iterative implementation of searching a BST
	Note: More efficient than the recursive one.
*/
Node* IterativeSearch(Node* x, int Key)
{
	Node* Current = x;
	while (x != nullptr)
	{
		if (Current->Key == Key)
			return Current;
		else if (Key < Current->Key)
			Current = Current->Left;
		else Current = Current->Right;
	}
	return x; // If we don't return a Node from the while loop, it means that
			 // x ( root ) is nullptr therefore we return nullptr;
}
void FreeTree(Node* Root)
{
	if (Root == nullptr)
		return;
	FreeTree(Root->Left);
	FreeTree(Root->Right);
	delete Root;
}


/* It takes Theta(n) time to walk an n-node BST, since after the initial call,
the procedure calls itself recursively exactly twice for each node in the
tree — once for its left child and once for its right child. */
void InOrderTreeWalk(Node* Root)
{
	if (Root != nullptr)
	{
		InOrderTreeWalk(Root->Left);
		std::cout << Root->Key<<"("<<Root->Count<<")"<<" ";
		InOrderTreeWalk(Root->Right);
	}
	/* 
		Note: For Pre-Order-Tree-Walk, the function will look like:
		
		std::cout<< Root->Key;
		PreOrderTreeWalk(Root->Left);
		PreOrderTreeWalk(Root->Right);
		Analogically, for Post-Order-Tree-Walk, the function will look like:
		
		PostOrderTreeWalk(Root->Left);
		PostOrderTreeWalk(Root->Right);
		std::cout<< Root->Key;
	*/

}
/* The above algorithm implemented iteratively */
void InOrderTreeWalkIterative(Node* Root)
{
	std::stack<Node*> NodeKeys;
	Node* Current = Root;
	while (true)
	{
		if (Current != nullptr)
		{
			NodeKeys.push(Current);
			Current = Current->Left;
		}
		else
		{
			if (!NodeKeys.empty())
			{
				Current = NodeKeys.top();
				NodeKeys.pop();
				std::cout << Current->Key << "( " <<Current->Count<<" )"<<" ";
				Current = Current->Right;
			}
			else
				break;
		}
	}
}


bool CheckBSTProperty(Node* Root, Node* L = NULL, Node* R = NULL) // Returns true if the tree is a BST, false otherwise
{
	if( Root = NULL)
		return true;
	if( L != NULL && Root->Key <= L->Key)
		return false;
	if( R != NULL && Root->Key >= R->Key)
		return false;
	return CheckBSTProperty(Root->Left, L, Root) && CheckBSTProperty(Root->Right, Root, R);
}

int main()
{
	Node* Root = nullptr;

    AddNode(Root, 7);
    AddNode(Root, 7);
    AddNode(Root, 15);
    AddNode(Root, 16);
    AddNode(Root, 14);
	AddNode(Root, 5);
	AddNode(Root, 2);
	AddNode(Root, 8);
	AddNode(Root, 7);

	DeleteNode(Root,7);
    //DeleteNode(Root, 7);

	InOrderTreeWalk(Root);

	std::cout<<std::endl;
	std::cout<<"Count: "<<CountNodes(Root);
//	Node* foundNode = IterativeSearch(Root, 8);
//	std::cout << foundNode->Key;
	FreeTree(Root);
}