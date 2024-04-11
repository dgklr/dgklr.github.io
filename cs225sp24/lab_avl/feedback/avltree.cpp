/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "avltree.h"

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
int AVLTree<K, V>::getHeight(Node*& t) { // assume this node doesn't have the right height
    int lh = -1, rh = -1;
    if (t == nullptr) return -1;
    if (t -> left != nullptr) lh = t -> left -> height;
    if (t -> right != nullptr) rh = t -> right -> height;
    return max(lh, rh) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    if (t == nullptr || t -> right == nullptr) return;
    nodeptr now = t, rs = t -> right, rls = t -> right -> left;
    rs -> left = now;
    now -> right = rls;
    t = rs;
    now -> height = getHeight(now);
    rs -> height = getHeight(rs);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    if (t == nullptr || t -> left == nullptr) return;
    nodeptr now = t, ls = t -> left, lrs = t -> left -> right;
    ls -> right = now;
    now -> left = lrs;
    t = ls;
    now -> height = getHeight(now);
    ls -> height = getHeight(ls);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if (subtree == nullptr) return;
    subtree -> height = getHeight(subtree);
    int diff = getHeight(subtree -> left) - getHeight(subtree -> right);
    if (diff >= -1 && diff <= 1) return;
    if (diff < 0)
        if (getHeight(subtree -> right -> left) > getHeight(subtree -> right -> right))
            rotateRightLeft(subtree);
        else
            rotateLeft(subtree);
    else
        if (getHeight(subtree -> left -> right) > getHeight(subtree -> left -> left))
            rotateLeftRight(subtree);
        else
            rotateRight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == nullptr) {
        subtree = new Node(key, value);
        return;
    }

    if (subtree -> key == key) {
        subtree -> value = value;
        return;
    }

    if (subtree -> key > key)
        insert(subtree -> left, key, value);
    else
        insert(subtree -> right, key, value);

    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL) {
        return;
    }
 
    if (key < subtree->key) {
        remove(subtree -> left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        remove(subtree -> right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            delete subtree;
            subtree = nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            Node*& tmp = rightestNode(subtree -> left);
            swap(tmp, subtree);
            delete tmp;
            tmp = nullptr;
        } else {
            Node* tmp;
            if (subtree->left != nullptr)
                tmp = subtree->left;
            else
                tmp = subtree->right;
            delete subtree;
            subtree = tmp;
        }
        rebalance(subtree);
    }
}
template <class K, class V>
typename AVLTree<K, V>::Node*& AVLTree<K, V>::rightestNode(Node*& subtree) {
    if (subtree->right == nullptr) return subtree;
    return rightestNode(subtree->right);
}