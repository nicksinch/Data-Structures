/*

    This problem was asked by Google.

    In linear algebra, a Toeplitz matrix is one in which the elements on any given diagonal
    from top left to bottom right are identical.

    Example:
    1 2 3 4 8 1
    5 1 2 3 4 8
    4 5 1 2 3 4
    7 4 5 1 2 3

    This solution is not quite elegant. However, the algorithm terminates
    with the correct output given a particular matrix. The idea is to start from
    the upper right corner of the matrix and explore every diagonal until we reach the
    bottom left corner.

*/

#include <iostream>
#include <vector>
using namespace std;

bool IsToeplitz(int **Matrix, int Rows, int Cols)
{
    int preFirstRow = 1;
    int postFirstRow = 0;

    bool zeroColumnReached = false;

    // Indices to refer to matrix elements
    int i = 0;
    int j = Cols - preFirstRow;

    while(!(i == Rows - 1 && j == 0)) // While we are not at the bottom left angle, do ...
        {
            if(!zeroColumnReached)
            {
                j == 0 ? i++ : i = 0;

                if(i == 0)
                {
                    preFirstRow++;
                    j = Cols - preFirstRow;
                }
                else // if we are here, i > 0 (first time we are here, i = 1, second i = 2, third i = 3, so on ...)
                {
                    postFirstRow++;
                    j = postFirstRow;
                }

                if(i == 0 && j == 0)
                    zeroColumnReached = true;
            }
            else
            {
                postFirstRow++;
                i = postFirstRow;
                j = 0;
            }

        while(j < Cols - 1 && i != Rows - 1)
        {
            int first = Matrix[i][j];
            int second = Matrix[i+1][j+1];
            if(first != second)
                return false; // Toeplitz matrix property violated

            j++;
            i++;
        }
    }
    return true; // no violation found
}
int main()
{
    int **arr = new (nothrow) int*[4];
    if(!arr)
        cerr<<"Error allocating memory!"<<endl;
    for (int i = 0; i < 4; i++)
    {
        arr[i] = new int[6];
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cin>>arr[i][j];
        }
        cout<<endl;
    }

    cout<<IsToeplitz(arr,4,6);

    // 1 2 3 4 8 1 5 1 2 3 4 8 4 5 1 2 3 4 7 4 5 1 2 3 copy the input
}
