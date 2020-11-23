#include<string>
#include<iostream>
using namespace std;

unsigned int i;
/* A binary tree node has data, pointer to left child
and a pointer to right child */
// A Binary Tree Node 
struct Node
{
    string data;
    struct Node* left, * right;
};

/* Helper function that allocates a new node with the
given data and NULL left and right pointers. */
Node* newNode(char data)
{
    Node* temp = new Node;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}






// function to print leaf  
// nodes from left to right 
void printLeafNodes(Node* root)
{
    // if node is null, return 
    if (!root)
        return;

    // if node is leaf node, print its data     
    if (!root->left && !root->right)
    {
        cout << root->data[0] << " ";
        return;
    }

    // if left child exists, check for leaf  
    // recursively 
    if (root->left)
        printLeafNodes(root->left);

    // if right child exists, check for leaf  
    // recursively 
    if (root->right)
        printLeafNodes(root->right);
}



/* Compute the "maxDepth" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
int maxDepth(Node* node)
{
    if (node == NULL)
        return 0;
    else
    {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);

        /* use the larger one */
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}

//this function creates a binary tree from a newick format in a recursive way
void createtree(Node* tree, string word, bool left) {
    if (i >= word.size())
        return;
        //stopping statement
    else
    {
        if (word[i] > 44 && left) {
            tree->left = newNode(word[i]);
            i++;
            createtree(tree, word, 1);
        }
        if (word[i] > 44 && !left) {
            tree->right = newNode(word[i]);
            i++;
            createtree(tree, word, 1);
        }
        
        //whenever it finds a "(" with a true operator, it creates a node in the left child of its input 
        if (word[i] == '(' && left) {
            tree->left = newNode(' ');
            i++;
            createtree(tree->left, word, 1);
            i++;
        }
        
        //whenever it finds a "(" with a false operator, it creates a node in the right child of its input
        if (word[i] == '(' && !left) {
            tree->right = newNode(' ');
            i++;
            createtree(tree->right, word, 1);
            i++;
        }
        
        //whenever it finds a "," ,it changes the operator value to create the new child in the right node of its input
        if (word[i] == ',') {
            i++;
            createtree(tree, word, 0);
        }
        
        ////whenever it finds a ")", it returns to the original node of its input
        if (word[i] == ')') {
            // i++;
            return;
        }
    }
    //i++;
    return;

}



//this is to visualze tree structure built
void print_tree_structure(Node *root, int spaces)
{
  if(root != NULL)
  {
    print_tree_structure(root->right, spaces + 5);
    for(int i = 0; i < spaces; i++)
      	cout << ' ';
    	cout << "   " << root->data << endl;
    print_tree_structure(root->left, spaces + 5);
  }
}





// Driver code     
int main()
{

    string newick = "((((A,D),((B,F),G)),C),E)";
    //struct Node *root2 = newNode(newick);
    struct Node* root2 = newNode(' ');
    createtree(root2, newick, 1);
    //inorder(root2);
    cout << "Height of tree is " << maxDepth(root2)<< '\n'; 
    printLeafNodes(root2);
    int spaces = 3;
    print_tree_structure(root2, spaces);


    return 0;
}
