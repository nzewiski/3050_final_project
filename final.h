#ifndef FINALPROJ_H_INCLUDED
#define FINALPROJ_H_INCLUDED

function void createNodeArr(Node* nodeArr) {
    char Free = ' ';
    int row, col;

    for( row = 0 ; row < MAZEMAX ; ++row ) {
        for( col = 0 ; col < MAZEMAX ; ++col ) {
            cout << row << " " << col << " " << Maze[row][col] << endl;
            if( Maze[row][col] == Free ) {
                nodeArr[row][col] = new Node();
            } //End if
            if( (row>0) && (col>0) ){
                if( (nodeArr[row-1][col] != NULL) && (nodeArr[row][col] != NULL) ) {
                    nodeArr[row][col]->setU(nodeArr[row-1][col]);
                    nodeArr[row-1][col]->setD(nodeArr[row][col]);
                }
                if( (nodeArr[row][col-1] != NULL) && (nodeArr[row][col] != NULL) ) {
                    nodeArr[row][col]->setL(nodeArr[row][col-1]);
                    nodeArr[row][col-1]->setR(nodeArr[row][col]);
                }
            }
        } //End for
    } //End for
}

#endif // FINAL_H_INCLUDED
