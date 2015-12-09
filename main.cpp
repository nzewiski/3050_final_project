#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits.h>
#include "finalproj.h"
using namespace std;
#define MAZEMAX 256


int main(void) {
    //Variable initializations
    Node* nodeArr[MAZEMAX][MAZEMAX] = {NULL};
    Node *start1, *end1, *start2, *end2;
    string path1, path2, filestr;
    char Maze[MAZEMAX][MAZEMAX] = {NULL};
    char hold;
    char Wall = '#';
    char Free = ' ';
    char Start1 = 'S';
    char End1 = 'E';
    char Start2 = 'F';
    char End2 = 'L';
    char EOL = '\n';
    bool Start1set = 1;
    bool End1set = 1;
    bool Start2set = 1;
    bool End2set = 1;
    int Start1Num = 0;
    int Start2Num = 0;
    int End1Num = 0;
    int End2Num = 0;
    int V = 0;
    int E = 0;
    int row, col, error, cntr, moveMax1, moveMax2;
    FILE *fPtr;

try {
    cout << "Enter the name of the maze file you wish to open: " << endl;
    cin >> filestr;

    // Open file and read into Maze array character by character
    if( ( fPtr = fopen( filestr.c_str(), "r") ) == NULL )
        throw error = 103;
    else {
        cout << "Opening file..." << endl;
        for( row = 0 ; row < MAZEMAX ; ++row ) {
            for( col = 0 ; col < MAZEMAX ; ++col ) {
                fscanf( fPtr, "%c", &hold );
                if( feof( fPtr ) || hold == EOL )
                    break;
                else{
                    Maze[row][col] = hold;
                    if( hold != Wall && col > 0)
                        ++V;
                }
            } //End for
            if( feof(fPtr) )
                break;
        } //End for
    } //End for

    // Check that file closes successfully.
    if ( !fclose( fPtr ) ) {
        cout << "Closing file..." << endl;
    }
    else {
        throw error = 104;
    }

    // Reports success and prints maze if Maze array is successfully populated with
    // valid characters and file opening and closing is successful.
    cout << "\nRead successful.\nPrinting Maze...\n" << endl;
    printMaze( Maze );
    cout << endl;

    // NODE POPULATION BLOCK
    // Populates nodeArr with nodes based on contents of Maze. Nodes are created for
    // every free space and a single node for each start and end position.
    for( row = 0 ; row < MAZEMAX ; ++row ) {
        for( col = 1 ; col < MAZEMAX ; ++col ) {
            if( Maze[row][col] == Free ) {
                nodeArr[row][col] = new Node("Free", row, col);
            } //End if
            else if( toupper(Maze[row][col]) == Start1 ) {
                if(Start1set)
                    nodeArr[row][col] = new Node("Start1", row, col);
                else
                    throw error = 201;
                Maze[row][col] = Free;
                start1 = nodeArr[row][col];
                Start1set = 0;
                Start1Num = nodeArr[row][col]->vertexNum;
            } //End if
            else if( toupper(Maze[row][col]) == End1 ) {
                if(End1set)
                    nodeArr[row][col] = new Node("End1", row, col);
                else
                    throw error = 202;
                Maze[row][col] = Free;
                end1 = nodeArr[row][col];
                End1set = 0;
                End1Num = nodeArr[row][col]->vertexNum;
            } //End if
            else if( toupper(Maze[row][col]) == Start2 ) {
                if(Start2set)
                    nodeArr[row][col] = new Node("Start2", row, col);
                else
                    throw error = 203;
                Maze[row][col] = Free;
                start2 = nodeArr[row][col];
                Start2set = 0;
                Start2Num = nodeArr[row][col]->vertexNum;
            } //End if
            else if( toupper(Maze[row][col]) == End2) {
                if(End2set)
                    nodeArr[row][col] = new Node("End2", row, col);
                else
                    throw error = 204;
                Maze[row][col] = Free;
                end2 = nodeArr[row][col];
                End2set = 0;
                End2Num = nodeArr[row][col]->vertexNum;
            } //End if
            else if( Maze[row][col] == EOL ) {
                break;
            }
            else if( Maze[row][col] != Wall && Maze[row][col] != NULL ) {
                throw error = 101;
            }

            // Increments edge count if nodes exist to the left or above the current node.
            // This count is done here in order to have the count ready for preparation of the graph.
            if( (row>0) && (col>0) ) {
                if( (nodeArr[row-1][col] != NULL) && (nodeArr[row][col] != NULL) )
                    E += 2;
                if( (nodeArr[row][col-1] != NULL) && (nodeArr[row][col] != NULL) )
                    E += 2;
            } //End if
        } //End for
    } //End for
    // Reports success if NODE POPULATION BLOCK exits successfully.
    cout << "\nNode Array populated." << endl;

    if( nodeArr[0][0]->vertex(1) && E ) {
        cout << "Total Vertices: " << V << "\nTotal Edges: " << E << endl;
    }
    else {
        throw error = 102;
    }

    Graph *graph1 = new Graph(V, E);
    cntr = 1;

    for( row = 0 ; row < MAZEMAX ; ++row ) {
        for( col = 1 ; col < MAZEMAX ; ++col ) {
            if( (row>0) && (col>0) ) {
                if( (nodeArr[row-1][col] != NULL) && (nodeArr[row][col] != NULL) ) {
                    nodeArr[row][col]->setU(nodeArr[row-1][col]);
                    graph1->edgeArr[cntr].source = nodeArr[row][col]->vertexNum;
                    graph1->edgeArr[cntr].destination = nodeArr[row-1][col]->vertexNum;
                    graph1->edgeArr[cntr].weight = 1;
                    graph1->edgeArr[cntr].type = 'U';
                    ++cntr;
                    nodeArr[row-1][col]->setD(nodeArr[row][col]);
                    graph1->edgeArr[cntr].source = nodeArr[row-1][col]->vertexNum;
                    graph1->edgeArr[cntr].destination = nodeArr[row][col]->vertexNum;
                    graph1->edgeArr[cntr].weight = 1;
                    graph1->edgeArr[cntr].type = 'D';
                    ++cntr;
                } //End if
                if( (nodeArr[row][col-1] != NULL) && (nodeArr[row][col] != NULL) ) {
                    nodeArr[row][col]->setL(nodeArr[row][col-1]);
                    graph1->edgeArr[cntr].source = nodeArr[row][col]->vertexNum;
                    graph1->edgeArr[cntr].destination = nodeArr[row][col-1]->vertexNum;
                    graph1->edgeArr[cntr].weight = 1;
                    graph1->edgeArr[cntr].type = 'L';
                    ++cntr;
                    nodeArr[row][col-1]->setR(nodeArr[row][col]);
                    graph1->edgeArr[cntr].source = nodeArr[row][col-1]->vertexNum;
                    graph1->edgeArr[cntr].destination = nodeArr[row][col]->vertexNum;
                    graph1->edgeArr[cntr].weight = 1;
                    graph1->edgeArr[cntr].type = 'R';
                    ++cntr;
                } //End if
            } //End if
        } //End for
    } //End for

    int dist1[V];
    int dist2[V];

    Bell_Ford(graph1, Start1Num, dist1);
    moveMax1 = dist1[End1Num];
    if( moveMax1 < E && moveMax1 > 0 ) {
        cout << "\nSource Vertex 1: " << Start1Num << "\nEnd Vertex 1: " << End1Num << endl;
        cout << "Shortest distance from start vertex " << Start1Num << " to end vertex " << End1Num << ": " << moveMax1 << endl;
        path1 = getPath( nodeArr, dist1, End1Num, moveMax1);
        path1 = rev(path1);
        cout << path1 << endl;
    }
    else if( moveMax1 == 0 ) {
        cout << "\nNo start and/or end for robot 1 detected." << endl;
    }
    else {
        cout << "\nNo path exists between start and exit for robot 1." << endl;
    }

    Bell_Ford(graph1, Start2Num, dist2);
    moveMax2 = dist2[End2Num];
    if( moveMax2 < E && moveMax2 > 0 ) {
        cout << "\nSource Vertex 2: " << Start2Num << "\nEnd Vertex 2: " << End2Num << endl;
        cout << "Shortest distance from start vertex " << Start2Num << " to end vertex " << End2Num << ": " << moveMax2 << endl;
        path2 = getPath( nodeArr, dist2, End2Num, moveMax2);
        path2 = rev(path2);
        cout << path2 << endl;
    }
    else if( moveMax2 == 0 ) {
        cout << "\nNo start and/or end for robot 2 detected." << endl;
    }
    else {
        cout << "\nNo path exists between start and exit for robot 2." << endl;
    }

}



//Error catch block
catch (int error) {
    cout << "\nError: " << error << endl;
    switch(error) {
    case 101:
        cout << "Incompatible maze character encountered." << endl;
        cout << "Row: " << row << "\nColumn: " << col << endl;
        break;
    case 102:
        cout << "Static counters uninitialized." << endl;
        break;
    case 103:
        cout << "Unable to open file." << endl;
        break;
    case 104:
        cout << "Unable to close file." << endl;
        break;
    case 201:
        cout << "Multiple start positions for robot 1." << endl;
        break;
    case 202:
        cout << "Multiple end positions for robot 1." << endl;
        break;
    case 203:
        cout << "Multiple start positions for robot 2." << endl;
        break;
    case 204:
        cout << "Multiple end positions for robot 2." << endl;
        break;
    }
}
    return 0;
}
