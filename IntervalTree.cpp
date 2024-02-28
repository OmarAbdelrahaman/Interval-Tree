#include <iostream>

using namespace std;

// class represent interval abstraction
class interval
{
public:
    // low and high in each interval
    int lo, hi;
    // constructor
    interval(int lo = 0, int hi = 0) 
    {
        this->lo = lo;
        this->hi = hi;
    }
    // check if interval object is Null
    bool isNull() 
    {
        if (this->lo > this->hi) {
            return false;
        }
        return true;
    }
};


// class represent Node abstraction
class Node 
{
public:
    Node *left, *right;
    interval interval;
    int mx;

    Node() 
    {
        this->interval.lo = this->mx = this->interval.hi = 0;
        this->left = this->right = NULL;
    }

    Node(int lo, int hi, int max, Node *l = NULL, Node *r = NULL)
    {
        this->interval.lo = lo;
        this->interval.hi = hi;
        this->mx = max;
        this->left = l;
        this->right = r;
    }

    int getKey() 
    {
        return interval.lo;
    }

};

// actual class for Build Dynamic_interval_Tree With insert and Search methods
class IntervalTree
{
private:
    Node *root;
public:
    // Default constructor For initilize root with NULL
    IntervalTree() 
    { 
        root = NULL; 
    }

    // internal version of search Using Recsuison
    interval *search(Node *node, int lo, int hi) 
    {
        // if node is null reutrn Null
        if (node == NULL) return NULL;

        // check if query interval can can be found in Left SubTree
        if (node->left != NULL && lo <= node->left->mx)
        {
            // search again in left Sub Tree
            interval *result = search(node->left, lo, hi);
            // if found in left Sub tree return this interval as it with min low intervla overlap than node 
            if (result != NULL) 
                return result;
            // if pass which mean Don't overlap with left Sub tree..check cureent node overlap Condtion
            if (lo <= node->interval.hi && hi >= node->interval.lo)
                return new interval(node->interval.lo, node->interval.hi);
            // if not found in left and cureent node and Got gere ..means not Overlap At all
            // Don't need to check right Subtree
            return NULL;
        } else
        {
            // if not overlap with Left Try current and right Sub tree
            // check if overlap condtion with current
            if (lo <= node->interval.hi && hi >= node->interval.lo)
                return new interval(node->interval.lo, node->interval.hi);
            // not in lft nor node .. so try search in right Subtree
            return search(node->right, lo, hi);
        }


    }

    // User version of search to print result and call internal Searech Recursion function
    void search(int lo, int hi) 
    {
        interval *x = search(root, lo, hi);

        if (x != NULL) 
        {
            // found in Tree and return minimuim low interval Overlap with Query interval
            cout << "{ " << x->lo << ", " << x->hi << " }" << "\n\n";

        } else 
        {
            // if not overlap with any interval in tree
            cout << "Not Found...!" << "\n\n";
        }
    }

    // the main insert function
    Node *insert(Node *node, int lo, int hi) 
    {
        // base case if the node is null just create a new node with max = hi
        if (node == NULL) 
        {
            Node *x = new Node(lo, hi, hi);
            node = x;
        }
        // search for the node's place in BST
        // check if the currentNode.low > newNode.low
        // then go left recursively
        else if (node->interval.lo > lo) 
        {
            node->left = insert(node->left, lo, hi);
        }
        // check if the currentNode.low <= newNode.low
        // then go right recursively
        else if (node->interval.lo <= lo) 
        {
            node->right = insert(node->right, lo, hi);
        }

        // update the max of each node (affected by inserting the new one) recursively
        int leftMax = -1; // initialize the value of leftMax to -1 in order if has no leftNode
        int rightMax = -1;  // initialize the value of rightMax to -1 in order if has no rightNode
        // if the node has right then update the rightMax variable with node->right->max
        if (node->right != NULL) 
        {
            rightMax = node->right->mx;
        }
        // if the node has left then update the leftMax variable with node->left->max
        if (node->left != NULL) 
        {
            leftMax = node->left->mx;
        }

        //update Node Max Value with the maximum of max(its high value, rightMax, leftMax)
        node->mx = max(node->interval.hi, max(rightMax, leftMax));

        //return Node
        return node;
    }

    // User version of insert function just to insert in Root Firstly..calling main insert function
    void insert(int lo, int hi)
    {
        root = insert(root, lo, hi);
    }
};


int main() 
{



    /* 1 -> 5 test cases */
    IntervalTree intervalTree1;
    intervalTree1.insert(50, 51);
    intervalTree1.insert(3, 30);
    intervalTree1.insert(4, 40);
    intervalTree1.insert(8, 88);
    intervalTree1.insert(-100, 100);


    cout << "Test1" << endl;
    intervalTree1.search(1, 15);        // Prints { -100, 100 }
    cout << "Test2" << endl;
    intervalTree1.search(45, 46);       // Prints { -100, 100 }
    cout << "Test3" << endl;
    intervalTree1.search(45, 100);      // Prints { -100, 100 }
    cout << "Test4" << endl;
    intervalTree1.search(1, 100);       // Prints { -100, 100 }
    cout << "Test5" << endl;
    intervalTree1.search(-200, -201);   // Prints Not Found...!
    cout << "--------------------\n\n";

    /* 6 -> 10 test cases */
    IntervalTree intervalTree2;
    intervalTree2.insert(10, 20);
    intervalTree2.insert(-4, 4);
    intervalTree2.insert(300, 333);
    intervalTree2.insert(70, 79);
    intervalTree2.insert(3, 55);
    intervalTree2.insert(40, 66);
    intervalTree2.insert(1, 1);
    intervalTree2.insert(2, 2);

    cout << "Test6" << endl;
    intervalTree2.search(1, 1);         // Prints { -4, 4 }
    cout << "Test7" << endl;
    intervalTree2.search(-11, 2);       // Prints { -4, 4 }
    cout << "Test8" << endl;
    intervalTree2.search(9, 9);         // Prints { 3, 55 }
    cout << "Test9" << endl;
    intervalTree2.search(11, 33);       // Prints { 3, 55 }
    cout << "Test10" << endl;
    intervalTree2.search(0, 13);        // Prints { -4, 4 }
    cout << "--------------------\n\n";


    /* 11 -> 15 test cases */
    IntervalTree intervalTree3;
    intervalTree3.insert(1, 14);
    intervalTree3.insert(2, 4);
    intervalTree3.insert(3, 16);
    intervalTree3.insert(30, 29);
    intervalTree3.insert(7, 55);
    intervalTree3.insert(40, 46);
    intervalTree3.insert(21, 74);
    intervalTree3.insert(-100, 3);
    intervalTree3.insert(-2, 5);
    intervalTree3.insert(0, 0);

    cout << "Test11" << endl;
    intervalTree3.search(-1, 1);        // Prints { -100, 3 }
    cout << "Test12" << endl;
    intervalTree3.search(-10, 5);       // Prints { -100, 3 }
    cout << "Test13" << endl;
    intervalTree3.search(-5, 8);        // Prints { -100, 3 }
    cout << "Test14" << endl;
    intervalTree3.search(1, 33);        // Prints { -100, 3 }
    cout << "Test15" << endl;
    intervalTree3.search(0, 1);         // Prints { -100, 3 }
    cout << "--------------------\n\n";


    /* 16 -> 20 test cases */
    IntervalTree intervalTree4;
    intervalTree4.insert(17, 19);
    intervalTree4.insert(5, 11);
    intervalTree4.insert(22, 23);
    intervalTree4.insert(4, 8);
    intervalTree4.insert(15, 18);
    intervalTree4.insert(7, 10);


    cout << "Test16" << endl;
    intervalTree4.search(14, 16);       // Prints { 15, 18 }
    cout << "Test17" << endl;
    intervalTree4.search(12, 14);       // Prints Not Found...!
    cout << "Test18" << endl;
    intervalTree4.search(8, 8);         // Prints { 4, 8 }
    cout << "Test19" << endl;
    intervalTree4.search(1, 4);         // Prints { 4, 8 }
    cout << "Test20" << endl;
    intervalTree4.search(23, 300);      // Prints { 22, 23 }
    cout << "--------------------\n\n";

    /* 21 -> 30 test cases */
    IntervalTree intervalTree5;

    intervalTree5.insert(2, 7);
    intervalTree5.insert(4, 5);
    intervalTree5.insert(4, 15);
    intervalTree5.insert(7, 12);
    intervalTree5.insert(9, 13);
    intervalTree5.insert(11, 13);
    intervalTree5.insert(11, 15);

    cout << "Test21" << endl;
    intervalTree5.search(6, 10);        // Prints { 2, 7 }
    cout << "Test22" << endl;
    intervalTree5.search(4, 20);        // Prints { 2, 7 }
    cout << "Test23" << endl;
    intervalTree5.search(11, 15);       // Prints { 4, 15 }
    cout << "Test24" << endl;
    intervalTree5.search(10, 16);       // Prints { 4, 15 }
    cout << "Test25" << endl;
    intervalTree5.search(12, 16);       // Prints { 4, 15 }
    cout << "Test26" << endl;
    intervalTree5.search(14, 16);       // Prints { 4, 15 }
    cout << "Test27" << endl;
    intervalTree5.search(15, 17);       // Prints { 4, 15 }
    cout << "Test28" << endl;
    intervalTree5.search(0, 2);         // Prints { 2, 7 }
    cout << "Test28" << endl;
    intervalTree5.search(0, 1);         // Prints Not Found...!
    cout << "Test29" << endl;
    intervalTree5.search(8, 8);         // Prints { 4, 15 }
    cout << "Test30" << endl;
    intervalTree5.search(10, 10);       // Prints { 4, 15 }

}
