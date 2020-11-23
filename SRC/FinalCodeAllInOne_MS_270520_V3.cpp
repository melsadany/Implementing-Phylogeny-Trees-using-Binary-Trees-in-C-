// A Quick Implementation of UPGMA (Unweighted Pair Group Method with Arithmetic Mean)

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//lowest_cell:
//Locates the smallest cell in the table
void lowestcell(vector<vector<int>> table, int &x, int &y){
    //Set default to large number
    int min_cell = 999;
    //Go through every cell, looking for the lowest
    for (int i=0; i< table.size(); i++){
        for (int j=0; j<table[i].size(); j++){
            if (table[i][j] < min_cell){
                min_cell = table[i][j];
                x = i;
                y = j;
            }
        }
    }
    //Return the x, y co-ordinate of cell in the enetered initial values
}


//join_labels:
//Combines two labels in a list of labels

void join_labels(vector<string>&labels, int a, int b){
    //Swap if the indices are not ordered
    int c;
    if (b<a){
        c = a;
        a = b;
        b = c;
    };
    //Join the labels in the first index
    labels[a]= "("+labels[a]+","+labels[b]+")";

    //Remove the (now redundant) label in the second index
    labels.erase(labels.begin()+b);
}


//join_table:
//Joins the entries of a table on the cell (a, b) by averaging their data entries

void join_table (vector<vector<int>>&table, int &a, int&b){
    //Swap if the indices are not ordered
    int c;
    if (b<a){
        c=a;
        a=b;
        b=c;
    }
    //For the lower index, reconstruct the entire row (A, i), where i < A
    vector<int> row;
    for (int i=0; i<a;i++){
        row.push_back((table[a][i]+table[b][i])/2);
    }

    table[a]=row;

    //Then, reconstruct the entire column (i, A), where i > A
    //Note: Since the matrix is lower triangular, row b only contains values for indices < b
    for (int i=a+1; i<b; i++){
        table[i][a] = (table[i][a]+table[b][i])/2;
    }

    //We get the rest of the values from row i
    for (int i=b+1; i<table.size(); i++){
        table[i][a] = (table[i][a]+table[i][b])/2;
        table[i].erase(table[i].begin()+b-1);       
    }

    //Remove the (now redundant) second index row
    table.erase(table.begin()+b);
}


//UPGMA:
//Runs the UPGMA algorithm on a labelled table

string UPGMA(vector<vector<int>>table, vector<string>labels){
    int x = -1;
    int y = -1;
    //Until all labels have been joined...
    while(labels.size()>1){
        //Locate lowest cell in the table
        lowestcell(table, x, y);

        //Join the table on the cell co-ordinates
        join_table(table,x,y);
        
        //Update the labels accordingly
        join_labels(labels,x,y);
    }

    //Return the final label
    return labels[0];
}




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
    	cout << "----" << root->data << endl;
    print_tree_structure(root->left, spaces + 5);
  }
}






//A test using an example calculation from http://www.nmsr.org/upgma.htm for the distance matrix
int main()
{
    //Test table data and corresponding labels
    //table vector represents the distance matrix in a lower triangle form
    vector<vector<int>> table = { {},                       //A
                                {19},                       //B
                                {27, 31},                   //C
                                {8, 18, 26},                //D
                                {33, 36, 41, 31},           //E
                                {18, 1, 32, 17, 35},        //F
                                {13, 13, 29, 14, 28, 12}    //G
                                };
    vector<vector<string>> table1;
    
    //the M_labels vector represents species characters
    vector<string> M_labels = {"A", "B", "C", "D", "E", "F", "G"};

    //UPGMA(table, M_labels) should output: '((((A,D),((B,F),G)),C),E)'
    //cout<< UPGMA(table, M_labels)<< endl;


    cout<< "your tree root is"<< UPGMA(table, M_labels)<<endl;
    cout<< "your tree structure in a newick format is: "<<UPGMA(table, M_labels)<<endl;
    
    //string newick = "((((A,D),((B,F),G)),C),E)";
    string newick = UPGMA(table, M_labels);
    
    //building tree root 
    struct Node* root2 = newNode(' ');
    
    //giving the function its root input with the newick tree format and a true boolean operator
    createtree(root2, newick, 1);
    
    //printing tree in inorder format
    //inorder(root2);
    
    
    cout << "Height of tree is " << maxDepth(root2)<< '\n'; 
    
    
    cout << "your tree leaves are: ";
    printLeafNodes(root2);
    cout<<endl;
    
    
    cout<< "the following is the visualization for your final tree"<<endl;
    int spaces = 3;
    print_tree_structure(root2, spaces);
    
    return 0;
}
