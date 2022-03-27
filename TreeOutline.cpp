// Drawing the Tree Outline such that the Top view of the Tree for the Left Subtree is printed in opposite way and the 
// Top view of the Right Subtree is printed in the Normal way after the Left Subtree
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
class Node                    // Node class created for each Tree Node creation
{
    public:
    int data;         // Data member
    Node* left;      // Left Node pointer
    Node* right;     // Right Node pointer
    Node* root;      // Root Node pointer
    bool visited;
    public:
    Node (int val)    // Parametrized Constructor
    {
        data = val;
        left = NULL;
        right = NULL;
        visited = false;
        root = NULL;
    }
};
class BinaryTree     //  Class created for Binary Tree Implementation ( Non-Linear Data Structure )
{
    public:
    Node* InsertNodeInTree(Node* root, int val)   // Inserting Node recursively.. O(log n) time
    {
        if(root == NULL)               // If No root node is there, create one
            return new Node(val);
        if(val <= root -> data)   // If data is lesser than or equal to parent store in left subtree
            root -> left = InsertNodeInTree(root -> left, val);
        else         // If data is greater than the parent stor it in right subtree
            root -> right = InsertNodeInTree(root -> right, val);
        return root;
    }
    void ShowTree(Node* root)   // Displaying tree with Node.. O(log n) time
    {
        if(root == NULL)   // If Tree is empty nothing to show
            return;            // Control moves out of the function
        Node* temp = root;
        ShowTree(root -> left);     // Recursive Call
        cout << "Node: " << endl;
        if(root -> left != NULL)    // If left subtree is not empty
            cout << "\t" << temp -> data << " ---> " << root -> left -> data << "\t Left ( Occupied )" << endl;
        else      // If left subtree is empty
            cout << "\t" << temp -> data << "\t\t Left ( Empty )" << endl;
        if(root -> right != NULL)   // If right subtree is not empty
            cout << "\t" << temp -> data << " ---> " << root -> right -> data << "\t Right ( Occupied ) " << endl;
        else     // If right subtree is empty
            cout << "\t" << temp -> data << "\t\t Right ( Empty )" << endl;
        ShowTree(root -> right);     // Recursive Call
    }
    void OutlineViewOfTree(Node* root)  // Function for printing Outline of Tree
    {
        if(root == NULL)      // If Root node is empty, return
            return;
        queue<Node*> Queue;    // Queue creation for Breadth First Search ( BFS )
        stack<int> Left;       // Stack creation for storing Leftmost Nodes of the Tree
        queue<int> Right;      // Another Queue creation for storing Rightmost nodes of the Tree
        Queue.push(root);      // Enqueuing Root Node 
        while(!Queue.empty())    // If the BFS Queue is not empty
        {
            int size = Queue.size();        // size of the BFS Queue
            for(int i = 0; i < size; i++)
            {
                Node* curr = Queue.front();    // Storing the front pointer reference
                curr -> visited = false;    // The current node is not yet visited
                Queue.pop();    // Dequeuing the Front Node from the BFS Queue
                if(i == 0)      //  If the first Node in the level is present
                {
                    curr -> visited = true;     // The Node is visited
                    Left.push(curr -> data);        // Pushing the data into the stack
                }
                if(i == size-1)    // If the End Node in a level is found
                {
                    if(curr -> visited == true)     // If there is only one Node in a level
                    {                               // The Node is already visited
                        Left.pop();
                        Left.push(curr -> data);
                    }
                    else     // Otherwise
                        Right.push(curr -> data);    // Enqueuing the Rightmost Node into the Queue
                }
                if(curr -> left)      // If the Left Subtree exists, Enqueue it into BFS Queue
                    Queue.push(curr -> left);
                if(curr -> right)     // If the Right Subtree exists, Enqueue it into BFS Queue
                    Queue.push(curr -> right);
            }
        }
        cout << "The Outline of the Binary Tree is : " << endl;
        while(!Left.empty())     // Stack created in the first instance to call and print the Left
        {                        // view of the Binary Tree in Reverse Order due to Last-In First-Out ( LIFO )
            cout << Left.top() << " --> ";
            Left.pop();     // Popping every element of Stack till it is made empty
        }
        while(!Right.empty())   // Queue created to call and print the Right view of the Binary Tree in 
        {                       // normal order due to First-In First-Out ( FIFO )
            cout << Right.front() << " --> ";
            Right.pop();    // Dequeuing every element of Queue till it is made empty
        }
        cout << endl;  // Endline to mark the end of the Function
    }
};
int main()   // main method begins
{
    Node* root = NULL;      // Root node initialization
    BinaryTree binarytree;      // Object creation of Binary Tree
    int s, x;
    cout << "Enter root Node value : ";
    cin >> x;
    root = binarytree.InsertNodeInTree(root, x);    // Root Node created
    cout << "Enter the number of Nodes to Insert in the Binary Search Tree : ";
    cin >> s;
    for(int i = 1; i <= s; i++)
    {
        cout << "Enter the New Node value : ";
        cin >> x;
        root = binarytree.InsertNodeInTree(root, x);   // Calling Insert Tree function
    }
    binarytree.ShowTree(root);    // Displaying binary tree with Nodes
    binarytree.OutlineViewOfTree(root);    // Calling the Outline View Function
    return 0;     // End of the program
}