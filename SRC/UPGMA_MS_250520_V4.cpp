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





//A test using an example calculation from http://www.nmsr.org/upgma.htm
int main()
{
    //Test table data and corresponding labels
    vector<vector<int>> table = { {},                       //A
                                {19},                       //B
                                {27, 31},                   //C
                                {8, 18, 26},                //D
                                {33, 36, 41, 31},           //E
                                {18, 1, 32, 17, 35},        //F
                                {13, 13, 29, 14, 28, 12}    //G
                                };

    vector<string> M_labels = {"A", "B", "C", "D", "E", "F", "G"};
    int x = -1;
    int y = -1;

    //UPGMA(table, M_labels) should output: '((((A,D),((B,F),G)),C),E)'
    cout<< UPGMA(table, M_labels);
    
    return 0;
}
