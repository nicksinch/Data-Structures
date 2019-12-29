/*
    An example implementation of AVL - Tree
*/

/*
    Def: (Height of BST ) - Length of longest path from root down to a leaf

    Balanced: if h = Theta(log(n)), h is height of the tree

    Def: ( Height of a Node ) - Length of longest path from it down to a leaf
    = max ( height of left child, height of right child ) + 1
*/

// Idea of AVL Trees : Require the height of left and right children differ by AT MOST 1

/* Nh - min # of nodes in an AVL tree of height h, Nh = 1 + Nh(n-2) + Nh(n-1),
    Nh > Fh ( fib)
*/

#include <iostream>

int max(int a, int b) // Helper function to find max of two elements, used for updating the height of traversed nodes
{
    return (a > b) ? a : b;
}

// An AVL Node Representation
class Node
{
    public:
        int Key;
        Node* Left;
        Node* Right;
        int Height;

        Node(int Key_)
        {
            Key = Key_;
            Left = nullptr;
            Right = nullptr;
            Height = 1;
        }
};

Node* TreeMinimum(Node* x) // O(log(n)), since we maintain balanced BST
{
    if (x == nullptr)
        return nullptr;
    if (x->Left != nullptr)
        return TreeMinimum(x->Left);
    else
        return x;
}

int GetHeight(Node* N) // A getter for the height of an arbitrary node, looks smoother
{
    if(N == nullptr)
        return 0;
    return N->Height;
}

/*
    A function to Right-Rotate a Subtree
*/
Node* RotateRight(Node* Root)
{
    Node* LeftChild = Root->Left;
    Node* Subtree = LeftChild->Right; // Could be empty

    // Perform Rotation
    LeftChild->Right = Root;
    Root->Left = Subtree;

    // Update The Heights of LeftChild And Root ( Because only they are Rotated)
    Root->Height = max(GetHeight(Root->Left), GetHeight(Root->Right)) + 1;
    LeftChild->Height = max(GetHeight(LeftChild->Left), GetHeight(LeftChild->Right)) + 1;

    return LeftChild; // Return the new Root
}

/*
    A function to Left-Rotate a Subtree
*/
Node* RotateLeft(Node* Root)
{
    Node* RightChild = Root->Right;
    Node* Subtree = RightChild->Left; // Could be empty

    // Perform Rotation
    RightChild->Left = Root;
    Root->Right = Subtree;

    // Update The Heights of LeftChild And Root ( Because only they are Rotated)
    Root->Height = max(GetHeight(Root->Left), GetHeight(Root->Right)) + 1;
    RightChild->Height = max(GetHeight(RightChild->Left), GetHeight(RightChild->Right)) + 1;

    return RightChild; // Return the new Root
}

// Function to get the Balance of a particular SubTree root with N
int GetBalance(Node* N)
{
    if (N == nullptr)
        return 0;
    return GetHeight(N->Left) - GetHeight(N->Right);
}

/*
    Inserts a new node in our tree in the correct position and if AVL tree property
    is violated, it fixes it automatically and maintains it all the time
*/
Node* Insert(Node* N, int Key)
{
    // 1. Perform the Normal BST Insertion
    if ( N == nullptr) // Empty Tree
    {
        Node* NewNode = new Node(Key);
        N = NewNode;
        return N;
    }
    if( Key < N->Key)
        N->Left = Insert(N->Left, Key);
    else if( Key > N->Key)
        N->Right = Insert(N->Right, Key);
    else
        return N; // If we end up here, it means that this key is already presented , which is not allowed or our tree has a single Node

    // 2. Update the height value of this Ancestor Node , as new Node was inserted
    N->Height = max(GetHeight(N->Left), GetHeight(N->Right)) + 1;

    int Balance = GetBalance(N); // If this is > 1 ( means tree is unbalanced ), then we should take care for all the four cases:

    // Left Left Case
    if (Balance > 1 && Key < N->Left->Key)
    {
        return RotateRight(N);
    }

    // Right Right Case
    if (Balance < -1 && Key > N->Right->Key)
    {
        return RotateLeft(N);
    }

    // Left Right Case
    if (Balance > 1 && Key > N->Left->Key)
    {
        N->Left = RotateLeft(N->Left);
        return RotateRight(N);
    }

    // Right Left Case
    if (Balance < -1 && Key < N->Right->Key)
    {
        N->Right = RotateRight(N->Right);
        return RotateLeft(N);
    }

    /* Return the (unchanged) node pointer */
    return N;
}

/*
    Recursive function to delete a node
    with given key from subtree with
    given root. It returns root of the
    modified subtree.
 */
Node* Delete(Node* Root, int Key)
{
    // 1. Perform standard BST Node Deletion
    if (Root == nullptr) // Noting to Delete
        return Root;

    if ( Key < Root->Key )
        Root->Left = Delete(Root->Left, Key);

    else if( Key > Root->Key )
        Root->Right = Delete(Root->Right, Key);

    else // If we enter this 'else' , this means that we found the searched node to be deleted
    {
        // node with only one child or no child
        if( (Root->Left == nullptr) ||
            (Root->Right == nullptr) )
        {
            Node *Temp = Root->Left ?
                         Root->Left :
                         Root->Right;

            // No child case
            if (Temp == nullptr)
            {
                Temp = Root;
                Root = nullptr;
            }
            else // One child case
                *Root = *Temp; // Copy the contents of
            // the non-empty child
            delete Temp;
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node* Temp = TreeMinimum(Root->Right);

            // Copy the inorder successor's
            // data to this node
            Root->Key = Temp->Key;

            // Delete the inorder successor
            Root->Right = Delete(Root->Right,
                                     Temp->Key);
        }
    }

    // If the tree had just one node, it should be have been deleted, so we return nullptr
    if (Root == nullptr)
        return Root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    Root->Height = 1 + max(GetHeight(Root->Left),
                           GetHeight(Root->Right));

    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int Balance = GetBalance(Root);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case
    if (Balance > 1 &&
        GetBalance(Root->Left) >= 0)
        return RotateRight(Root);

    // Left Right Case
    if (Balance > 1 &&
        GetBalance(Root->Left) < 0)
    {
        Root->Left = RotateLeft(Root->Left);
        return RotateRight(Root);
    }

    // Right Right Case
    if (Balance < -1 &&
        GetBalance(Root->Right) <= 0)
        return RotateLeft(Root);

    // Right Left Case
    if (Balance < -1 &&
        GetBalance(Root->Right) > 0)
    {
        Root->Right = RotateRight(Root->Right);
        return RotateLeft(Root);
    }

    return Root;
}

void preOrder(Node *root)
{
    if(root != NULL)
    {
        std::cout << root->Key << " ";
        preOrder(root->Left);
        preOrder(root->Right);
    }
}

void FreeTree(Node* Root)
{
    if (Root == nullptr)
        return;
    FreeTree(Root->Left);
    FreeTree(Root->Right);
    delete Root;
}

int main() {
    /*
        Example simulation:
     */

    Node *root = new Node(10);

    root = Insert(root, 20);
    root = Insert(root, 30);
    root = Insert(root, 40);
    root = Insert(root, 50);
    root = Insert(root, 25);

    std::cout << "Pre-order traversal of the "
                 "constructed AVL tree is: \n";
    preOrder(root);

    /* The constructed AVL Tree would be
            30
           /  \
         20    40
        / \     \
       10 25     50
    */

    root = Delete(root,50);
    root = Delete(root,40);

    std::cout << "Pre-order traversal of the "
                 "constructed AVL tree after removing some nodes is: \n";
    preOrder(root);

    /* The constructed AVL Tree after deleting some nodes would be
           20
          /  \
        10   30
            /
           25
   */

    FreeTree(root);
}