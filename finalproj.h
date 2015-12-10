#ifndef FINALPROJ_H_INCLUDED
#define FINALPROJ_H_INCLUDED
using namespace std;
#define MAZEMAX 256
#define INT_MAX 4000000000

class Node{
    private:
        string property;
        static int vertexCount;
    public:
        int vertexNum, row, col, visited;
        Node *u, *d, *l, *r;
        Node();
        Node(string prop, int row, int col);
        void setU(Node *node);
        void setD(Node *node);
        void setL(Node *node);
        void setR(Node *node);
        static int vertex( int choice );
        string getProp();
};
Node::Node() {
    this->property = "EMPTY";
    this->row = 0;
    this->col = 0;
    this->visited = 0;
//    this->u = NULL;
//    this->d = NULL;
//    this->l = NULL;
//    this->r = NULL;
    this->vertex(0);
    this->vertexNum = this->vertex(1);
    cout << this->property << " Node created" << endl;
}
Node::Node( string prop, int row, int col ) {
    this->property = prop;
    this->row = row;
    this->col = col;
    this->visited = 0;
//    this->u = NULL;
//    this->d = NULL;
//    this->l = NULL;
//    this->r = NULL;
    this->vertex(0);
    this->vertexNum = this->vertex(1);
}
void Node::setU( Node *node ) {
    this->u = node;
}
void Node::setD( Node *node ) {
    this->d = node;
}
void Node::setL( Node *node ) {
    this->l = node;
}
void Node::setR( Node *node ) {
    this->r = node;
}
int Node::vertex( int choice ) {
    static int vertexCount = 0;
    int cnt;
    switch (choice) {
    case 0:
        ++vertexCount;
        return 0;
    case 1:
        cnt = vertexCount;
        return cnt;
    }
    return 0;
}
string Node::getProp() {
    return this->property;
}

class Edge{
    public:
        int source, destination, weight;
        char type;
};

class Graph{
    public:
        int V, E;
        Edge *edgeArr;
        Graph();
        Graph( int V, int E );
};
Graph::Graph( int V, int E ) {
   this->V = V;
   this->E = E;
   this->edgeArr = (Edge*) malloc( (E+1) * sizeof(Edge) );
}

void printArr( int dist[], int n ) {
    printf("Vertex   Distance from Source\n");
    for( int i = 1 ; i < n+1 ; ++i ) {
        printf("%d \t %d\n", i, dist[i] );
    }
}
void Bell_Ford( Graph* graph, int src, int dist[] ) {
    int V = graph->V;
    int E = graph->E;
    int i, j, u, v, weight;

    for( i = 0 ; i <= V ; ++i )
        dist[i] = INT_MAX;
    dist[src] = 0;

    for( i = 1 ; i <= V ; ++i ) {
        for( j = 1 ; j <= E ; ++j ) {
            u = graph->edgeArr[j].source;
            v = graph->edgeArr[j].destination;
            weight = graph->edgeArr[j].weight;
            if( dist[u] != INT_MAX && dist[u] + weight < dist[v] ) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    //printArr(dist, V);
    return;
}
void printMaze( char Maze[][MAZEMAX] ) {
    int i, j;
    for( i = 0 ; i < MAZEMAX ; ++i ) {
        for( j = 0 ; j < MAZEMAX ; ++j ) {
            if ( Maze[i][j] )
                cout << Maze[i][j];
        }
        if ( Maze[i][j] )
            cout << endl;
    }
}
string getPath( Node *nodeArr[][MAZEMAX], int distArr[], int endIndex, int endDist ) {
    string path;
    int index = endIndex;
    int dist = endDist;
    int numNodes = nodeArr[0][0]->vertex(1);
    Node *nodes[numNodes+1];
    int i, j, k;

    k = 1;
    for( i = 0 ; i < MAZEMAX ; ++i ) {
        for( j = 0 ; j < MAZEMAX ; ++j ) {
            if( nodeArr[i][j] ) {
                nodes[k] = nodeArr[i][j];
                ++k;
            }
        }
    }


    while( dist != 0 ){
        for( i = 0 ; i < numNodes ; ++i ) {
            if( distArr[i] == dist - 1 ) {
                if( nodes[i]->u && nodes[i]->u->vertexNum == index ) {
                    path = path + 'U';
                    index = i;
                    i = numNodes;
                    --dist;
                }
                else if( nodes[i]->d && nodes[i]->d->vertexNum == index ) {
                    path = path + 'D';
                    index = i;
                    i = numNodes;
                    --dist;
                }
                else if( nodes[i]->l && nodes[i]->l->vertexNum == index ) {
                    path = path + 'L';
                    index = i;
                    i = numNodes;
                    --dist;
                }
                else if( nodes[i]->r && nodes[i]->r->vertexNum == index ) {
                    path = path + 'R';
                    index = i;
                    --dist;
                    i = numNodes;
                }
            }
        }
    }

    return path;
}
string rev( string s ) {
    string result = "";
    for( int i = 0 ; i < s.length() ; ++i ) {
        result = s[i] + result;
    }
    return result;
}

#endif // FINALPROJ_H_INCLUDED
