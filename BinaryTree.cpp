/* An example implementation of a Binary Tree */

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
		Left = nullptr;
		Right = nullptr;
	}
	int Key;
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
		if (Key > Dest->Key)
			AddNode(Dest->Right, Key);
		else if (Key < Dest->Key)
			AddNode(Dest->Left, Key);
		else
			throw "This element exists!";
	}
}
void DeleteNode(Node*& st, int Key)
{
	if (st == nullptr)
		return;
	else if (st->Key == Key)
	{
		if (st->Left == nullptr && st->Right == nullptr) // There are no subtrees
		{
			delete st;
			st == nullptr;
		}
		else if (st->Left == nullptr) // Only Right subtree
		{
			Node* Temp = st->Right;
			delete st;
			st = Temp;
		}
		else if (st->Right == nullptr) // Only Left Subtree
		{
			Node* Temp = st->Left;
			delete st;
			st = Temp;
		}
		else   // Left and Right Subtrees
		{
			Node* Min = FindMinNode(st->Right);//finding the min element from the right subtree

			//Swapping two elements;
			Swap(Min->Key, st->Key);

			DeleteNode(st->Right, Key); // we could use it directly the pointer min,but we wouldn't take care of the pointer from the parrent 
		}
	}
	else if (Key > st->Key)
		DeleteNode(st->Right, Key);
	else
		DeleteNode(st->Left, Key);
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
		std::cout << Root->Key;
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
				std::cout << Current->Key << " ";
				Current = Current->Right;
			}
			else
				break;
		}
	}

}


void PrintNode(Node* Node_)
{
	if (Node_ == nullptr)
		std::cerr << "Node doesn't exist!" << std::endl;
	else
		std::cout << "Node with key: " << Node_->Key << std::endl;
}

int main()
{
	Node* Root = new Node(6);
	//AddNode(Root, 3);
	//AddNode(Root, 6);
	//AddNode(Root, 99);
	//AddNode(Root, 4);
	//AddNode(Root, 2);
	//AddNode(Root, 70);
	//AddNode(Root, 100);
	//std::cout << CountNodes(Root);
	//DeleteNode(Root, 99);
	//std::cout << CountNodes(Root);
	AddNode(Root, 5);
	AddNode(Root, 2);
	AddNode(Root, 7);
	AddNode(Root, 8);
	AddNode(Root, 9);
	//InOrderTreeWalk(Root);
	Node* foundNode = IterativeSearch(Root, 8);
	std::cout << foundNode->Key;
	FreeTree(Root);
}
