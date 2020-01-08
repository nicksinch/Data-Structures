/*

    An example implementation of an Expression Tree.
    Data Structures and Programming - FMI - HomeWork #3.

    Given a .txt file with a particular 'Prefix' Expression on every line,
    builds a Binary Expression tree. Then prints its equivalent Infix Notation (In Order Traversal)
    also prints its Reverse Polish Notation ( Post-Order Traversal ) and finally,
    The expression value is evaluated.

    Example:

    Expression : - 51 * 24 3
    An Expression Tree would be :
                                -
                              /   \
                            51     *
                                  / \
                                 24  3
 */

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

// Used to track the index of the Expression string during Building the tree recursively
static int From = 0;

struct Node
{
    string Data;
    Node *Left, *Right;
    Node(string Data_)
    {
        Data = Data_;
        Left = nullptr;
        Right = nullptr;
    }
};

// Starting from N, deletes the tree ( subtrees ) recursively
void DeleteNode(Node* N)
{
    if (N->Left) DeleteNode(N->Left);

    if (N->Right) DeleteNode(N->Right);

    delete N;
}

// Returns true if the string is a digit, false otherwise ( used when evaluating the tree )
bool IsNumber(const string& s)
{
    return s[0] >= '0' && s[0] <= '9';
}

/*
    Given a string Expression, extracts everything into a string , starting from
    'From' var until a ' ' ( space ) has occured.
 */
string ExtractWord(string Expression, int &From)
{
    string Word = "";
    while(Expression[From] != ' ')
    {
        Word += Expression[From++];
    }
    /*
        Moving the 'cursor' one position forward, since it has stopped on the 'space'
        so that the next time we have to extract a word, it won't start from the space
     */
    From++;
    return Word;
}

/*
  Recursively builds an expression tree given an Expression,
  the additional parameter 'CurrNode' is needed here because
  the implementation uses while(true) loop in a recursively way
  so CurrNode prevents data from the Expression from being lost
  Note: when calling the function, CurrNode start is "" initially
 */
Node* BuildTree(Node *&N, string Expression, string &CurrNode) {
    while (true)
    {
        if (!N)
        {
            CurrNode = ExtractWord(Expression, From); // Recall it starts from 0
            Node *Root = new Node(CurrNode);
            N = Root;
        }
        else
            {
                if (CurrNode != "-" && CurrNode != "*" && CurrNode != "+")
                {
                    return N;
                }
                N->Left = BuildTree(N->Left, Expression, CurrNode);
                N->Right = BuildTree(N->Right, Expression,CurrNode);
        }
    }
}

/* Prints the Expression in Infix Manner, pasting brackets where needed
    Note that this is an In-Oder Traversal of the Tree.
  */
void PrintInfix(Node* Root)
{
    if(Root)
    {
        if(Root->Left) std::cout<<"(";

        PrintInfix(Root->Left);

        std::cout<<Root->Data<<" ";

        PrintInfix(Root->Right);
        if(Root->Right) std::cout<<")";
    }
}

/* Prints the Expression in a Reverse Polish Notating Manner ( Post-Order Traversal ) */
void PrintPostfix(Node* Root)
{
    if(Root)
    {
        PrintPostfix(Root->Left);
        PrintPostfix(Root->Right);
        std::cout<<Root->Data<<" ";
    }
}

int EvaluateTree(Node* Root, unordered_map<string, int>& Variables)
{
    if (!Root) return 0;

    if (!Root->Left && !Root->Right) // A leaf is reached ( some value )
    {
        if (IsNumber(Root->Data)) return stoi(Root->Data);

        if (Variables.count(Root->Data) > 0) return Variables[Root->Data];

        cout << "Enter " << Root->Data << " value: ";
        int Var;
        cin >> Var;
        Variables[Root->Data] = Var;

        return Var;
    }

    int LeftSubTree = EvaluateTree(Root->Left, Variables);
    int RightSubTree = EvaluateTree(Root->Right, Variables);

    if (Root->Data == "+") return LeftSubTree + RightSubTree;

    if (Root->Data == "-") return LeftSubTree - RightSubTree;

    return LeftSubTree * RightSubTree;
}

int main()
{
    ifstream Expressions("/home/nick/CLionProjects/ClassWork-2/Expressions.txt");
    if(!Expressions) return -1;

    string Expr, CurrNode="";
    while(getline(Expressions, Expr))
    {
        Expr+=" "; // Fixes a bug with the spaces when printing the last expression
        Node* Root = nullptr;
        BuildTree(Root, Expr, CurrNode);
        std::cout<<"Expression: "<<Expr<<std::endl;

        std::cout<<"Infix Equivallence is : "<<std::endl;
        PrintInfix(Root);
        std::cout<<endl;

        std::cout<<"Postfix ( Reverse Polish Notation ) Equivallence is : "<<std::endl;
        PrintPostfix(Root);

        std::cout<<endl;
        unordered_map<string, int> Variables;
        std::cout<<"Expression Value is: "<<endl<<EvaluateTree(Root, Variables)<<std::endl;

        std::cout<<endl;

        // Resetting values for the Next Tree
        DeleteNode(Root);
        From = 0;
        CurrNode = "";
    }

    Expressions.close();
}
