/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <algorithm>
#include <stack>
#include <utility>

#include "kdtree.h"

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
    const Point<Dim>& second, int curDim) const
{
    if (first[curDim] < second[curDim])
        return true;

    if (first[curDim] > second[curDim])
        return false;

    return first < second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
    const Point<Dim>& currentBest,
    const Point<Dim>& potential) const
{
    double sumCurr = 0, sumPotential = 0;
    for (int i = 0; i < Dim; i++)
        sumPotential += (target[i] - potential[i]) * (target[i] - potential[i]);
    for (int i = 0; i < Dim; i++)
        sumCurr += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
    if (sumPotential < sumCurr)
        return true;
    if (sumPotential > sumCurr)
        return false;

    return potential < currentBest;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    vector<Point<Dim>> tmp = newPoints;
    buildKDTree(root, tmp.begin(), tmp.end(), 0);
    //printTree();
}

template <int Dim>
template <class T>
void KDTree<Dim>::getKthElem(T begin, T end, size_t place, size_t dim)
{
    random_shuffle(begin, end); // randomize the array
    auto tmpbegin = begin, tmpend = end;
    while (tmpbegin != tmpend) {
        auto now = *tmpbegin;
        auto left = tmpbegin, right = tmpend - 1;
        while (left < right) {
            while (left < right && smallerDimVal(now, *right, dim))
                right--;
            *left = *right;
            while (left < right && smallerDimVal(*left, now, dim))
                left++;
            *right = *left;
        }
        *left = now;
        if (left == begin + place)
            return;
        if (left < begin + place)
            tmpbegin = left + 1;
        if (left > begin + place)
            tmpend = left;
    }
}

template <int Dim>
template <class T>
void KDTree<Dim>::buildKDTree(KDTreeNode*& now, T begin, T end, size_t dim)
{
    size_t len = end - begin;
    if (len == 0) {
        now = nullptr;
        return;
    }
    if (len == 1) {
        now = new KDTreeNode(*begin);
        now->left = now->right = nullptr;
    }
    T mid = begin + (len - 1) / 2;
    getKthElem(begin, end, (len - 1) / 2, dim);
    now = new KDTreeNode(*mid);
    buildKDTree(now->left, begin, mid, (dim + 1) % Dim);
    buildKDTree(now->right, mid + 1, end, (dim + 1) % Dim);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other)
{
    if (other->root == nullptr) {
        root = nullptr;
        return;
    }

    stack<pair<decltype(root), decltype(root)>> s;
    s.push(make_pair(root, other->root));
    root = new decltype(root)(other->root->point);
    while (s.size()) {
        auto now = s.top().first, ref = s.top().second;
        s.pop();
        if (ref->left != nullptr)
            now->left = new decltype(ref)(ref->left->point),
            s.push(make_pair(now->left, ref->left));
        else
            now->left = nullptr;

        if (ref->right != nullptr)
            now->right = new decltype(ref)(ref->right->point),
            s.push(make_pair(now->right, ref->right));
        else
            now->right = nullptr;
    }
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs)
{
    if (&rhs == this) {
        return *this;
    }
    auto& other = rhs;

    if (other->root == nullptr) {
        root = nullptr;
        return *this;
    }
    stack<pair<decltype(root), decltype(root)>> s;
    s.push(make_pair(root, other->root));
    root = new decltype(root)(other->root->point);
    while (s.size()) {
        auto now = s.top().first, ref = s.top().second;
        s.pop();
        if (ref->left != nullptr)
            now->left = new decltype(ref)(ref->left->point),
            s.push(make_pair(now->left, ref->left));
        else
            now->left = nullptr;

        if (ref->right != nullptr)
            now->right = new decltype(ref)(ref->right->point),
            s.push(make_pair(now->right, ref->right));
        else
            now->right = nullptr;
    }

    return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree()
{
    if (root == nullptr)
        return;
    stack<decltype(root)> s;
    s.push(root);
    while (s.size() < 0) {
        auto now = s.top();
        if (now->left != nullptr)
            s.push(now->left);
        if (now->right != nullptr)
            s.push(now->right);

        now = s.top();
        if (now->left != nullptr)
            delete now->left;
        if (now->right != nullptr)
            delete now->right;
        s.pop();
    }
    delete root;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    if (root == nullptr) return Point<Dim>();
    return findNearest(root, Point<Dim>(), query, 0, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearest(KDTreeNode* now, Point<Dim> best, Point<Dim> query, size_t dim, bool recursive) const
{ // recursive means whether we have found a best

    Point<Dim> here;
    if (recursive == 0) {
        if (now->left != nullptr) {
            best = findNearest(now->left, best, query, (dim + 1) % Dim, 0);
            // check right
            auto tmp = query;
            tmp[dim] = now->point[dim]; // get the value of nearest point on the plane
            if (now -> right != nullptr && (
                shouldReplace(query, best, tmp) || // cannot cut off this brench because the hyper-ball cut with the hyper-plane
                query[dim] > tmp[dim]// this query point is on the right side of the plane
            )){
                auto bestright = findNearest(now->right, best, query, (dim + 1) % Dim, 1);
                if (shouldReplace(query, best, bestright))
                    best = bestright;
            }
            if (shouldReplace(query, best, now->point))
                best = now->point;
            return best;
        } else if (now->right != nullptr) {
            best = findNearest(now->right, best, query, (dim + 1) % Dim, 0);
            if (shouldReplace(query, best, now->point))
                best = now->point;
            return best;
        }
        else return now->point;
    }
    else {
        auto tmp = query;
        tmp[dim] = now->point[dim]; // get the value of nearest point on the plan
        if (now -> left != nullptr && (
            shouldReplace(query, best, tmp) || // cannot cut off this brench because the hyper-ball cut with the hyper-plane
            query[dim] < tmp[dim]// this query point is on the left side of the plane
        )) {
            auto bestleft = findNearest(now->left, best, query, (dim + 1) % Dim, 1);
            if (shouldReplace(query, best, bestleft))
                best = bestleft;
        }

        if (now -> right != nullptr && (
            shouldReplace(query, best, tmp) || // cannot cut off this brench because the hyper-ball cut with the hyper-plane
            query[dim] > tmp[dim]// this query point is on the right side of the plane
        )) {
            auto bestright = findNearest(now->right, best, query, (dim + 1) % Dim, 1);
            if (shouldReplace(query, best, bestright))
                best = bestright;
        }
        if (shouldReplace(query, best, now->point))
            best = now->point;
        return best;
    }
}