#ifndef _8PUZZLE_H_
#define _8PUZZLE_H_

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <list>

using namespace std;

struct Node {
    public:
        Node(); //default constructor
        Node(vector<vector<char> > puzzle); //constructor with puzzle passed in
        vector<Node*> children;
        Node* parent; //parent for node
        vector<vector<char> > currentPuzzle; //stores current state of the puzzle
        double h; //heuristic
        int depth;

};

struct Position {
    public:
        Position();
        Position(int blankPos, int rowIndex);
        int blankPos;
        int rowIndex;
};

class reversePrio {
    //from cplusplus.com
    //template <class T, class Container = vector<T>, class Compare = less<typename Container::value_type> > class priority_queue;
    //Compare
    /*A binary predicate that takes two elements (of type T) as arguments and returns a bool.
    The expression comp(a,b), where comp is an object of this type and a and b are elements in the container, shall return true if a is considered to go before b in the strict weak ordering the function defines.
    The priority_queue uses this function to maintain the elements sorted in a way that preserves heap properties (i.e., that the element popped is the last according to this strict weak ordering).
    This can be a function pointer or a function object, and defaults to less<T>, which returns the same as applying the less-than operator (a<b).
    */
    //since default is <, so we use > since we need to reverse priority queue
    public:
        bool operator() (Node* board1, Node* board2) {
            /*if ((board1->depth + board1->h) > (board2->depth + board2->h)) {
                return true;
            }
            return false;*/
            //return board1->h > board2->h;

            return board1->depth + board1->h > board2->depth + board2->h;
        }
};

void printPuzzle(Node *curr); //print current puzzle
double misplacedTile(vector<vector<int> > curr); //calculate misplace tile heuristic
double manhattanDistance(vector<vector<int> > curr); //calculate euclidean tile heuristic

//operators
void topLeft(Node *curr); //each moves the blank tile accordingly, creates the children that comes from the move, and assigns them
void topMiddle(Node *curr);
void topRight(Node *curr);
void middleLeft(Node *curr);
void middleMiddle(Node *curr);
void middleRight(Node *curr);
void bottomLeft(Node *curr);
void bottomMiddle(Node *curr);
void bottomRight(Node *curr);

Node* moveBlankUp(Node *curr, int rowIndex, int blankIndex);
Node* moveBlankDown(Node *curr, int rowIndex, int blankIndex);
Node* moveBlankLeft(Node *curr, int rowIndex, int blankIndex);
Node* moveBlankRight(Node *curr, int rowIndex, int blankIndex);

void expand(Node* curr); //performs the operators to expand the node
bool checkGoal (vector<vector<char> > puzzleToCheck); //checks if current puzzle board is the goal state
void uniformCostHeuristic(Node* child);
void calcHeuChild1(Node* curr, int selectAlgo); //calculate heuristic for child, one for each possible child
void calcHeuChild2(Node* curr, int selectAlgo);
void calcHeuChild3(Node* curr, int selectAlgo);
void calcHeuChild4(Node* curr, int selectAlgo);
void search(Node* start); //performs the search
void initializePuzzle(Node*start); //initializes the start state according to user input or default

#endif