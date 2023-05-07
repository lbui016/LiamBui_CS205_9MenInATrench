#include "8puzzle.h"
#include <iostream>
#include "math.h"

//priority_queue<Node*, vector<Node*>, reversePrio> frontier;
//vector<vector<vector<char> > > explored;
//int numNodesExpanded = 0;
//int numNodesInQueue = 0;

Node::Node() {
    this->parent = NULL;
    this->h = 0;
    this->depth = 0;
}

Node::Node(vector<vector<char> > puzzle) {
    this->currentPuzzle = puzzle;
    this->parent = NULL;
    this->h = 0;
    this->depth = 0;
}

bool checkGoal(vector<vector<char> > puzzleToCheck) {
    vector<vector<char> > goalPuzzle;
    
    /*vector<int> row1;
    row1.push_back(1);
    row1.push_back(2);
    row1.push_back(3);
    
    vector<int> row2;
    row2.push_back(4);
    row2.push_back(5);
    row2.push_back(6);
    
    vector<int> row3;
    row3.push_back(7);
    row3.push_back(8);
    row3.push_back(0);

    goalPuzzle.push_back(row1);
    goalPuzzle.push_back(row2);
    goalPuzzle.push_back(row3);*/

    vector<char> row1;
    row1.push_back('x');
    row1.push_back('x');
    row1.push_back('x');
    row1.push_back('*');
    row1.push_back('x');
    row1.push_back('*');
    row1.push_back('x');
    row1.push_back('*');
    row1.push_back('x');
    row1.push_back('x');

    vector<char> row2;
    row2.push_back('1');
    row2.push_back('2');
    row2.push_back('3');
    row2.push_back('4');
    row2.push_back('5');
    row2.push_back('6');
    row2.push_back('7');
    row2.push_back('8');
    row2.push_back('9');
    row2.push_back('*');

    goalPuzzle.push_back(row1);
    goalPuzzle.push_back(row2);
    

    if (puzzleToCheck == goalPuzzle) {
        return true;
    }
    else {
        return false;
    }
}

/*void topLeft(Node* curr) {
    //* X X
    //X X X
    //X X X
    //2 possible children: swap right, swap bottom
    
    Node *child1 = new Node(curr->currentPuzzle); //create new Node child
    swap(child1->currentPuzzle.at(0).at(0), child1->currentPuzzle.at(0).at(1)); //first .at is for the row (top), second .at is for column
    child1->depth = curr->depth + 1; //increment path cost by 1 and put into depth of child, every child is created by 1 move so 1 "depth"

    Node *child2 = new Node(curr->currentPuzzle);
    swap(child2->currentPuzzle.at(0).at(0), child2->currentPuzzle.at(1).at(0)); //swap the blank tile into posistion
    child2->depth = curr->depth + 1;

    //assigned child here because every time a swap happens, children are created
    curr->child1 = child1; //assign newly create children nodes to children node arguments of current node
    curr->child2 = child2; //in this case, we only have 2 possible children

}

void topMiddle(Node* curr) {
    //X * X
    //X X X
    //X X X
    //3 possible children: swap left, swap right, swap bottom
    
    Node *child1 = new Node(curr->currentPuzzle);
    swap(child1->currentPuzzle.at(0).at(1), child1->currentPuzzle.at(0).at(0));
    child1->depth = curr->depth + 1;

    Node *child2 = new Node(curr->currentPuzzle);
    swap(child2->currentPuzzle.at(0).at(1), child2->currentPuzzle.at(0).at(2));
    child2->depth = curr->depth + 1;

    Node *child3 = new Node(curr->currentPuzzle);
    swap(child3->currentPuzzle.at(0).at(1), child3->currentPuzzle.at(1).at(1));
    child3->depth = curr->depth + 1;

    curr->child1 = child1;
    curr->child2 = child2;
    curr->child3 = child3;

}

void topRight(Node* curr) {
    //X X *
    //X X X
    //X X X
    //2 possible children: swap bottom, swap left
    
    Node *child1 = new Node(curr->currentPuzzle);
    swap(child1->currentPuzzle.at(0).at(2), child1->currentPuzzle.at(1).at(2)); 
    child1->depth = curr->depth + 1;

    Node *child2 = new Node(curr->currentPuzzle);
    swap(child2->currentPuzzle.at(0).at(2), child2->currentPuzzle.at(0).at(1)); 
    child2->depth = curr->depth + 1;

    curr->child1 = child1;
    curr->child2 = child2;

}

void middleLeft(Node* curr) {
    //X X X
    //* X X
    //X X X
    //3 possible children: swap right, swap bottom, swap up
    
    Node *child1 = new Node(curr->currentPuzzle);
    swap(child1->currentPuzzle.at(1).at(0), child1->currentPuzzle.at(1).at(1));
    child1->depth = curr->depth + 1;

    Node *child2 = new Node(curr->currentPuzzle);
    swap(child2->currentPuzzle.at(1).at(0), child2->currentPuzzle.at(2).at(0));
    child1->depth = curr->depth + 1;

    Node *child3 = new Node(curr->currentPuzzle);
    swap(child3->currentPuzzle.at(1).at(0), child3->currentPuzzle.at(0).at(0));
    child3->depth = curr->depth + 1;
    
    curr->child1 = child1;
    curr->child2 = child2;
    curr->child3 = child3;


}

void middleMiddle(Node* curr) {
    //X X X
    //X * X
    //X X X
    //4 possible children: swap right, swap left, swap bottom, swap up 
    Node *child1 = new Node (curr->currentPuzzle);
    swap(child1->currentPuzzle.at(1).at(1), child1->currentPuzzle.at(1).at(2));
    child1->depth = curr->depth + 1;

    Node *child2 = new Node (curr->currentPuzzle);
    swap(child2->currentPuzzle.at(1).at(1), child2->currentPuzzle.at(1).at(0));
    child2->depth = curr->depth + 1;

    Node *child3 = new Node (curr->currentPuzzle);
    swap(child3->currentPuzzle.at(1).at(1), child3->currentPuzzle.at(2).at(1));
    child3->depth = curr->depth + 1;

    Node *child4 = new Node (curr->currentPuzzle);
    swap(child4->currentPuzzle.at(1).at(1), child4->currentPuzzle.at(0).at(1));
    child4->depth = curr->depth + 1;

    curr->child1 = child1;
    curr->child2 = child2;
    curr->child3 = child3;
    curr->child4 = child4;


}

void middleRight(Node* curr) {
    //X X X
    //X X *
    //X X X
    //3 possible children: swap left, swap bottom, swap up

    Node *child1 = new Node(curr->currentPuzzle);
    swap(child1->currentPuzzle.at(1).at(2), child1->currentPuzzle.at(1).at(1));
    child1->depth = curr->depth + 1;

    Node *child2 = new Node(curr->currentPuzzle);
    swap(child2->currentPuzzle.at(1).at(2), child2->currentPuzzle.at(2).at(2));
    child2->depth = curr->depth + 1;

    
    Node *child3 = new Node(curr->currentPuzzle);
    swap(child3->currentPuzzle.at(1).at(2), child3->currentPuzzle.at(0).at(2));
    child3->depth = curr->depth + 1;

    curr->child1 = child1;
    curr->child2 = child2;
    curr->child3 = child3;

}

void bottomLeft(Node* curr) {
    //X X X
    //X X X
    //* X X
    //2 possible children: swap right, swap up

    Node *child1 = new Node(curr->currentPuzzle);
    swap(child1->currentPuzzle.at(2).at(0), child1->currentPuzzle.at(2).at(1));
    child1->depth = curr->depth + 1;

    Node *child2 = new Node(curr->currentPuzzle);
    swap(child2->currentPuzzle.at(2).at(0), child2->currentPuzzle.at(1).at(0));
    child2->depth = curr->depth + 1;

    curr->child1 = child1;
    curr->child2 = child2;


}


void bottomMiddle(Node* curr) {
    //X X X
    //X X X
    //X * X
    //3 possible children: swap right, swap left, swap up

    Node *child1 = new Node(curr->currentPuzzle);
    swap(child1->currentPuzzle.at(2).at(1), child1->currentPuzzle.at(2).at(2));
    child1->depth = curr->depth + 1;

    Node *child2 = new Node(curr->currentPuzzle);
    swap(child2->currentPuzzle.at(2).at(1), child2->currentPuzzle.at(2).at(0));
    child2->depth = curr->depth + 1;

    Node *child3 = new Node(curr->currentPuzzle);
    swap(child3->currentPuzzle.at(2).at(1), child3->currentPuzzle.at(1).at(1));
    child3->depth = curr->depth + 1;

    curr->child1 = child1;
    curr->child2 = child2;
    curr->child3 = child3;


}

void bottomRight(Node* curr) {
    //X X X
    //X X X
    //X X *
    //2 possible children: swap left, swap up

    Node *child1 = new Node(curr->currentPuzzle);
    swap(child1->currentPuzzle.at(2).at(2), child1->currentPuzzle.at(2).at(1));
    child1->depth = curr->depth + 1;

    Node *child2 = new Node(curr->currentPuzzle);
    swap(child2->currentPuzzle.at(2).at(2), child2->currentPuzzle.at(1).at(2));
    child2->depth = curr->depth + 1;

    curr->child1 = child1;
    curr->child2 = child2;

    


}*/

void misplacedTileHeuristic(Node* curr) {
    int distance1;
    int distance2;
    int distance3;
    int distance4;
    int distance5;
    int distance6;
    int distance7;
    int distance8;
    int distance9;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            if (curr->currentPuzzle.at(i).at(j) == '1') {
                if (i == 0) {
                    distance1 = j + 1;
                }
                else {
                    distance1 = j;
                }
            }
        }
    }

    int index2 = 1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            if (curr->currentPuzzle.at(i).at(j) == '2') {
                if (i == 0) {
                    distance2 = abs(j - index2) + 1;
                }
                else {
                    distance2 = abs(j - index2);
                }
            }
        }
    }

    int index3 = 2;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            if (curr->currentPuzzle.at(i).at(j) == '3') {
                if (i == 0) {
                    distance3 = abs(j - index3) + 1;
                }
                else {
                    distance3 = abs(j - index3);
                }
            }
        }
    }

    int index4 = 3;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            if (curr->currentPuzzle.at(i).at(j) == '4') {
                if (i == 0) {
                    distance4 = abs(j - index4) + 1;
                }
                else {
                    distance4 = abs(j - index4);
                }
            }
        }
    }

    int index5 = 4;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            if (curr->currentPuzzle.at(i).at(j) == '5') {
                if (i == 0) {
                    distance5 = abs(j - index5) + 1;
                }
                else {
                    distance5 = abs(j - index5);
                }
            }
        }
    }

    int index6 = 5;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            if (curr->currentPuzzle.at(i).at(j) == '6') {
                if (i == 0) {
                    distance6 = abs(j - index6) + 1;
                }
                else {
                    distance6 = abs(j - index6);
                }
            }
        }
    }

    int index7 = 6;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            if (curr->currentPuzzle.at(i).at(j) == '7') {
                if (i == 0) {
                    distance7 = abs(j - index7) + 1;
                }
                else {
                    distance7 = abs(j - index7);
                }
            }
        }
    }

    int index8 = 7;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            if (curr->currentPuzzle.at(i).at(j) == '8') {
                if (i == 0) {
                    distance8 = abs(j - index8) + 1;
                }
                else {
                    distance8 = abs(j - index8);
                }
            }
        }
    }

    int index9 = 8;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            if (curr->currentPuzzle.at(i).at(j) == '9') {
                if (i == 0) {
                    distance9 = abs(j - index9) + 1;
                }
                else {
                    distance9 = abs(j - index9);
                }
            }
        }
    }

    curr->h = distance1+distance2+distance3+distance4+distance5+distance6+distance7+distance8+distance9;

}

void manhattanDistance (Node* curr) {
    int distance;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 10; j++) {
            if (curr->currentPuzzle.at(i).at(j) == '1') {
                if (i == 0) {
                    distance = j + 1;
                }
                else {
                    distance = j;
                }
            }
        }
    }
    curr->h = distance;
}

void uniformCostHeuristic(Node* curr) {
    curr->h = 0;
}

Node* moveBlankDown(Node* curr, int rowIndex, int blankPos) {
    Node *child = new Node (curr->currentPuzzle);
    bool repeat = false;
    //if(child->currentPuzzle.at(rowIndex+1).at(blankPos) != '*') { 
    swap(child->currentPuzzle.at(rowIndex).at(blankPos), child->currentPuzzle.at(rowIndex+1).at(blankPos));
    child->depth = curr->depth+1;
    //uniformCostHeuristic(child);
    misplacedTileHeuristic(child);
    //manhattanDistance(child);
    return child;
    //frontier.push(child);

    /*cout << "EXPLORED:" << endl;
    for (int x = 0; x < explored.size(); x++) {
        for (int y = 0; y < explored.at(0).size(); y++) {
            for (int z = 0; z < explored.at(0).at(0).size(); z++) {
                cout << explored.at(x).at(y).at(z) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }*/ 

    /*for (int i = 0; i <explored.size(); i ++) {
        if (child->currentPuzzle == explored.at(i)) { //state has already been explored
            cout << "REPEAT STATE FOUND:" << endl;
            printPuzzle(child);
            for (int x = 0; x < explored.at(0).size(); x++) {
                for(int y = 0; y < explored.at(0).at(0).size(); y++) {
                    cout << explored.at(i).at(x).at(y) << " ";
                }
                cout << endl;
            }
            cout << endl;
            repeat = true;
        }
    }

    if (repeat == false) { //new state
        frontier.push(child);
        explored.push_back(child->currentPuzzle);
        if (numNodesInQueue < frontier.size()) {
            numNodesInQueue = frontier.size();
        }
    }
    else if (repeat == true) {
        child->currentPuzzle.clear();
    }*/
        
    //}

    


}

Node* moveBlankUp(Node* curr, int rowIndex, int blankPos) {
    Node *child = new Node (curr->currentPuzzle);
    bool repeat = false;
    //if(child->currentPuzzle.at(rowIndex-1).at(blankPos) != '*') {
        swap(child->currentPuzzle.at(rowIndex).at(blankPos), child->currentPuzzle.at(rowIndex-1).at(blankPos));
        child->depth = curr->depth+1;
        //uniformCostHeuristic(child);
        misplacedTileHeuristic(child);
        //manhattanDistance(child);
        return child;
        //frontier.push(child);
        
        /*for (int i = 0; i <explored.size(); i ++) {
            if (child->currentPuzzle == explored.at(i)) { //state has already been explored
                cout << "REPEAT STATE FOUND:"<<endl;
                printPuzzle(child);
                for (int x = 0; x < explored.at(0).size(); x++) {
                    for(int y = 0; y < explored.at(0).at(0).size(); y++) {
                        cout << explored.at(i).at(x).at(y) << " ";
                    }
                    cout << endl;
                }
                cout << endl;
                repeat = true;
            }
        }

        if (repeat == false) { //new state
            frontier.push(child);
            explored.push_back(child->currentPuzzle);
            if (numNodesInQueue < frontier.size()) {
                numNodesInQueue = frontier.size();
            }
        }
        else if (repeat == true) {
            child->currentPuzzle.clear();
        }*/
    //}
}

Node* moveBlankRight(Node* curr, int rowIndex, int blankPos) {
    Node *child = new Node (curr->currentPuzzle);
    bool repeat = false;
    //if(child->currentPuzzle.at(rowIndex).at(blankPos+1) != '*') {
        swap(child->currentPuzzle.at(rowIndex).at(blankPos), child->currentPuzzle.at(rowIndex).at(blankPos+1));
        child->depth = curr->depth+1;
        //uniformCostHeuristic(child);
        misplacedTileHeuristic(child);
        //manhattanDistance(child);
        return child;
        //frontier.push(child);
        
        /*for (int i = 0; i <explored.size(); i ++) {
            if (child->currentPuzzle == explored.at(i)) { //state has already been explored
                cout << "REPEAT STATE FOUND:"<<endl;
                printPuzzle(child);
                for (int x = 0; x < explored.at(0).size(); x++) {
                    for(int y = 0; y < explored.at(0).at(0).size(); y++) {
                        cout << explored.at(i).at(x).at(y) << " ";
                    }
                    cout << endl;
                }
                cout << endl;
                repeat = true;
            }
        }

        if (repeat == false) { //new state
            frontier.push(child);
            explored.push_back(child->currentPuzzle);
            if (numNodesInQueue < frontier.size()) {
                numNodesInQueue = frontier.size();
            }
        }
        else if (repeat == true) {
            child->currentPuzzle.clear();
        }*/
    //}
}

Node* moveBlankLeft(Node* curr, int rowIndex, int blankPos) {
    Node *child = new Node (curr->currentPuzzle);
    bool repeat = false;
    //if(child->currentPuzzle.at(rowIndex).at(blankPos-1) != '*'){
        swap(child->currentPuzzle.at(rowIndex).at(blankPos), child->currentPuzzle.at(rowIndex).at(blankPos-1));
        child->depth = curr->depth+1;
        //uniformCostHeuristic(child);
        misplacedTileHeuristic(child);
        //manhattanDistance(child);
        return child;
        //frontier.push(child);
        
        /*for (int i = 0; i <explored.size(); i ++) {
            if (child->currentPuzzle == explored.at(i)) { //state has already been explored
                cout << "REPEAT STATE FOUND"<<endl;
                printPuzzle(child);
                for (int x = 0; x < explored.at(0).size(); x++) {
                    for(int y = 0; y < explored.at(0).at(0).size(); y++) {
                        cout << explored.at(i).at(x).at(y) << " ";
                    }
                    cout << endl;
                }
                cout << endl;
                repeat = true;
            }
        }

        if (repeat == false) { //new state
            frontier.push(child);
            explored.push_back(child->currentPuzzle);
            if (numNodesInQueue < frontier.size()) {
                numNodesInQueue = frontier.size();
            }
        }
        else if (repeat == true) {
            child->currentPuzzle.clear();
        }*/
    //}
}


Position::Position() {
    this->blankPos = 0;
    this->rowIndex = 0;
}

Position::Position(int blankPos, int rowIndex) {
    this->blankPos = blankPos;
    this->rowIndex = rowIndex;
}

void expand(Node* curr, vector<Position*> blank_positions) {
    for (int i = 0; i < blank_positions.size(); i++) {
        cout<<"("<<blank_positions.at(i)->rowIndex << "," << blank_positions.at(i)->blankPos<< ") ";
    }
    cout << endl;


    for (int i = 0; i < blank_positions.size(); i++) {
        if (blank_positions.at(i)->rowIndex == 0) {
            moveBlankDown(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
        }
        else if (blank_positions.at(i)->rowIndex == 1) {
            if (blank_positions.at(i)->blankPos == 3 || blank_positions.at(i)->blankPos == 5 || blank_positions.at(i)->blankPos == 7) {
                moveBlankUp(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                moveBlankLeft(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                moveBlankRight(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
            }
            else if (blank_positions.at(i)->blankPos == 1 || blank_positions.at(i)->blankPos == 2 || blank_positions.at(i)->blankPos == 4 || blank_positions.at(i)->blankPos == 8) {
                moveBlankLeft(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                moveBlankRight(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
            }
            else if (blank_positions.at(i)->blankPos == 0) {
                moveBlankRight(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
            }
            else if (blank_positions.at(i)->blankPos == 9) {
                moveBlankLeft(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
            }
        }
    }
    cout <<endl;


    //blankPos possible positions
    //0 1 2
    //3 4 5
    //6 7 8

    /*if (blankPos == 0) { //if in position 0 then it is in the top left of the board
        topLeft(curr);
    }
    else if (blankPos == 1) {
        topMiddle(curr);
    }
    else if (blankPos == 2) {
        topRight(curr);
    }
    else if (blankPos == 3) {
        middleLeft(curr);
    }
    else if (blankPos == 4) {
        middleMiddle(curr);
    }
    else if (blankPos == 5) {
        middleRight(curr);
    }
    else if (blankPos == 6) {
        bottomLeft(curr);
    }
    else if (blankPos == 7) {
        bottomMiddle(curr);
    }
    else if (blankPos == 8) {
        bottomRight(curr);
    }*/

}

void initializePuzzle(Node* start) {

    /*vector<char> row1;
    row1.push_back('x');
    row1.push_back('x');
    row1.push_back('x');
    row1.push_back('*');
    row1.push_back('x');
    row1.push_back('*');
    row1.push_back('x');
    row1.push_back('*');
    row1.push_back('x');
    row1.push_back('x');

    vector<char> row2;
    row2.push_back('*'); 
    row2.push_back('2'); 
    row2.push_back('3'); 
    row2.push_back('4'); 
    row2.push_back('5'); 
    row2.push_back('6'); 
    row2.push_back('7'); 
    row2.push_back('8'); 
    row2.push_back('9'); 
    row2.push_back('1');*/

    vector<char> row1;
    row1.push_back('x');
    row1.push_back('x');
    row1.push_back('x');
    row1.push_back('4');
    row1.push_back('x');
    row1.push_back('1');
    row1.push_back('x');
    row1.push_back('8');
    row1.push_back('x');
    row1.push_back('x');

    vector<char> row2;
    row2.push_back('2'); 
    row2.push_back('3'); 
    row2.push_back('5'); 
    row2.push_back('6'); 
    row2.push_back('*'); 
    row2.push_back('*'); 
    row2.push_back('*'); 
    row2.push_back('*'); 
    row2.push_back('7'); 
    row2.push_back('9');

    //step 13 works depth of solution was 44
    //step 14 works depth of solution was 34
    //step 16 works depth of solution was 34
    //step 16 works depth of solution was 32
    //step 17 from online solution works (depth of solution was 28)
    /*vector<char> row1;
    row1.push_back('x');
    row1.push_back('x');
    row1.push_back('x');
    row1.push_back('1');
    row1.push_back('x');
    row1.push_back('5');
    row1.push_back('x');
    row1.push_back('8');
    row1.push_back('x');
    row1.push_back('x');

    vector<char> row2;
    row2.push_back('2'); 
    row2.push_back('3'); 
    row2.push_back('*'); 
    row2.push_back('*'); 
    row2.push_back('*'); 
    row2.push_back('*'); 
    row2.push_back('4'); 
    row2.push_back('6'); 
    row2.push_back('7'); 
    row2.push_back('9');*/ 

    start->currentPuzzle.push_back(row1);
    start->currentPuzzle.push_back(row2);

    cout <<"Puzzle initialized" << endl;




}

void printPuzzle(Node* curr) {
    for (int r = 0; r < curr->currentPuzzle.size(); r++) {
        for (int c = 0; c < curr->currentPuzzle.at(0).size(); c++) {
            cout<<curr->currentPuzzle.at(r).at(c) << " ";
        }
        cout<<endl;
    }
}

void search(Node* start) {
    /*while(!frontier.empty()) {
        frontier.pop();
    }
    explored.clear();*/
    Node* curr = start;
    //curr->h = 0; //0 for uniform cost search
    //curr->h = 9;

    priority_queue<Node*, vector<Node*>, reversePrio> frontier; //lowest heuristic is on top
    
    vector<Node*> explored;
    frontier.push(curr);
    //explored.push_back(curr);

    //bool repeat;
    int rowIndex;
    int blankPos;

    int test = 0;
    //!frontier.empty()
    while (!frontier.empty()) {

        curr = frontier.top();
        frontier.pop();
        //numNodesExpanded++;

        misplacedTileHeuristic(curr);

        vector<Position*> blank_positions;

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 10; j++) {
                if(curr->currentPuzzle.at(i).at(j) == '*') {
                    rowIndex = i;
                    blankPos = j;
                    Position *blank_position = new Position(blankPos, rowIndex);
                    blank_positions.push_back(blank_position);
                }
            }
        }

        if(checkGoal(curr->currentPuzzle)) {
            printPuzzle(curr);
            cout<<"Goal state reached!" << endl;
            return;
        }

        //uniformCostHeuristic(curr);
        //misplacedTileHeuristic(curr);
        
        /*cout << "EXPLORED:" << endl;
        for (int i = 0; i < explored.size(); i++) {
            printPuzzle(explored.at(i));
        }*/

        bool repeatCurr = false;
        for (int i = 0; i < explored.size(); i ++) {
            if (curr->currentPuzzle == explored.at(i)->currentPuzzle) {
                repeatCurr = true;
            }
        }

        if (repeatCurr == false) {
            cout<<"The best node to expand with g(n) = " << curr->depth << " and h(n) = " << curr->h << " is:" << endl;
            printPuzzle(curr);
            //expand(curr, blank_positions);
            for (int i = 0; i < blank_positions.size(); i++) {
                cout<<"("<<blank_positions.at(i)->rowIndex << "," << blank_positions.at(i)->blankPos<< ") ";
            }
            cout << endl;

            


        
            //expanding children for each blank in the current puzzle
            for (int i = 0; i < blank_positions.size(); i++) {
                if (blank_positions.at(i)->rowIndex == 0) {
                    if (blank_positions.at(i)->blankPos == 3)
                    {
                        Node* child = moveBlankDown(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child);
                            }
                            
                        }
                        
                    }
                    else if (blank_positions.at(i)->blankPos == 5) {
                        Node* child = moveBlankDown(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child);
                            }
                        }
                    }
                    else if (blank_positions.at(i)->blankPos == 7) {
                        Node* child = moveBlankDown(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child);
                            }
                        }
                    }    
                }
                else if (blank_positions.at(i)->rowIndex == 1) {
                    if (blank_positions.at(i)->blankPos == 3) {
                        Node* child1 = moveBlankUp(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        Node* child2 = moveBlankLeft(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        Node* child3 = moveBlankRight(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child1->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child1->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child1);
                            }
                        }
                        if (child2->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child2->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child2);
                            }
                        }
                        if (child3->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child3->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child3);
                            }
                        } 
                        


                    }
                    else if (blank_positions.at(i)->blankPos == 5) {
                        Node* child1 = moveBlankUp(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        Node* child2 = moveBlankLeft(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        Node* child3 = moveBlankRight(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child1->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child1->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child1);
                            }
                        }
                        if (child2->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child2->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child2);
                            }
                        }
                        if (child3->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child3->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child3);
                            }
                        } 

                    
                    }
                    else if (blank_positions.at(i)->blankPos == 7) {
                        Node* child1 = moveBlankUp(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        Node* child2 = moveBlankLeft(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        Node* child3 = moveBlankRight(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child1->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child1->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child1);
                            }
                        }
                        if (child2->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child2->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child2);
                            }
                        }
                        if (child3->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child3->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child3);
                            }
                        } 

                    }
                    else if (blank_positions.at(i)->blankPos == 1) {
                        Node* child1 = moveBlankLeft(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        Node* child2 = moveBlankRight(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child1->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child1->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child1);
                            }
                        }
                        if (child2->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child2->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child2);
                            }
                        } 

                    
                    }
                    else if (blank_positions.at(i)->blankPos == 2) {
                        Node* child1 = moveBlankLeft(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        Node* child2 = moveBlankRight(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child1->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child1->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child1);
                            }
                        }
                        if (child2->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child2->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child2);
                            }
                        } 

                    
                    }
                    else if (blank_positions.at(i)->blankPos == 4) {
                        Node* child1 = moveBlankLeft(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        Node* child2 = moveBlankRight(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child1->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child1->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child1);
                            }
                        }
                        if (child2->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child2->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child2);
                            }
                        } 
                    }
                    else if (blank_positions.at(i)->blankPos == 6) {
                        Node* child1 = moveBlankLeft(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        Node* child2 = moveBlankRight(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child1->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child1->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child1);
                            }
                        }
                        if (child2->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child2->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child2);
                            }
                        } 
                    }
                    else if (blank_positions.at(i)->blankPos == 8) {
                        Node* child1 = moveBlankLeft(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        Node* child2 = moveBlankRight(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child1->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child1->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child1);
                            }
                        }
                        if (child2->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child2->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child2);
                            }
                        } 

                    }
                    else if (blank_positions.at(i)->blankPos == 0) {
                        Node* child = moveBlankRight(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child);
                            }
                        }
                    }
                    else if (blank_positions.at(i)->blankPos == 9) {
                        Node* child = moveBlankLeft(curr, blank_positions.at(i)->rowIndex, blank_positions.at(i)->blankPos);
                        if (child->currentPuzzle != curr->currentPuzzle) {
                            bool repeat = false;
                            for (int j = 0; j < explored.size(); j++) {
                                if (child->currentPuzzle == explored.at(j)->currentPuzzle ) {
                                    repeat = true;
                                }
                            }

                            if (repeat == false) {
                                curr->children.push_back(child);
                            }
                        }
                    }
                }
            }

            //cout <<"CHILDREN: " << curr->children.size() << endl;
            int repeated = 0;

            /*for (int i = 0; i < curr->children.size(); i++) {
                printPuzzle(curr->children.at(i));
                cout << endl;
            }
            cout<<endl;*/

            for (int i = 0; i < curr->children.size(); i++) {
                //cout << "TEST" << endl;
                //printPuzzle(curr->children.at(i));
                //cout<<endl;
                bool repeat = false;

                if (curr->children.at(i)->currentPuzzle == curr->currentPuzzle) {
                    repeat = true;
                    cout << "CHILD SAME AS CURRENT:" << endl;
                    printPuzzle(curr->children.at(i));
                }
                //cout <<endl;

                for (int j = 0; j < explored.size(); j++) {
                    if (curr->children.at(i)->currentPuzzle == explored.at(j)->currentPuzzle ) {
                        repeat = true;
                    }
                }

                if (repeat == false) {
                    cout << "NEW STATE PUSHING TO FRONTIER: " << endl;
                    printPuzzle(curr->children.at(i));
                    frontier.push(curr->children.at(i));
                }
                else {
                    repeated++;
                }
            }

            explored.push_back(curr);

            cout << "REPEATED: " << repeated << endl;

            cout<<"Expanding this node..."<<endl;

            cout <<"FRONTIER SIZE: " << frontier.size() << endl;
            cout <<"EXPLORED SIZE: " << explored.size() << endl;
            cout << endl;

            //uniformCostHeuristic(curr);

            test++;
        }
    }

}

int main() {
    Node* start = new Node();

    initializePuzzle(start);

    printPuzzle(start);
    search(start);

    return 0;
}