/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
#include "binarytree.h"
#include <stack>
#include <tuple>
#include <utility>

template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    if (root == nullptr) return;
    stack <Node*> s;
    s.push(root);
    while (s.size()){
        auto top = s.top();
        s.pop();
        swap(top->left, top->right);
        if (top->left != nullptr) s.push(top->left);
        if (top->right != nullptr) s.push(top->right);
    }
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    if (root == nullptr) return true;
    stack <tuple<Node*, T, T, bool, bool> > s;
    s.push(make_tuple(root, T(), T(), 0, 0));
    while (s.size()) {
        auto top = s.top(); s.pop();
        if (get<3>(top) && get<0>(top)->elem < get<1>(top)) return false;
        if (get<4>(top) && get<0>(top)->elem > get<2>(top)) return false;
        if (get<0>(top)->left != nullptr)
            s.push(make_tuple(get<0>(top)->left, get<1>(top), get<0>(top)->elem, get<3>(top), 1));
        if (get<0>(top)->right != nullptr)
            s.push(make_tuple(get<0>(top)->right, get<0>(top)->elem, get<2>(top), 1, get<4>(top)));
    }
    return true;
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    if (root == nullptr) {
        paths.clear();
        return;
    }
    helper_printPaths(paths, vector<T>(), root);
}
template <typename T>
void BinaryTree<T>::helper_printPaths(vector<vector<T> > &paths, vector <T> path, Node* now) const
{
    path.push_back(now->elem);
    if (now->left == nullptr && now->right == nullptr) {
        paths.push_back(path);
    } else {
        if (now->left != nullptr) helper_printPaths(paths, path, now->left);
        if (now->right != nullptr) helper_printPaths(paths, path, now->right);
    }
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    if (root == nullptr) return 0;
    return helper_sumDistances(root, 0);
}

template <typename T>
int BinaryTree<T>::helper_sumDistances(Node* now, int depth) const
{
    int ret = depth;
    if (now->left != nullptr) ret += helper_sumDistances(now->left, depth + 1);
    if (now->right != nullptr) ret += helper_sumDistances(now->right, depth + 1);
    return ret;
}

