/*
 * Filename: AVLTree.cpp
 * Contains: Implementation of AVL Trees for CPSC 223
 * Part of: Homework assignment "AVL Trees" for CPSC 223
 * Joshua Zhang
 * CPSC 223 PSET 5
 * 4/14/23
 */

#include <iostream>

#include "AVLTree.h"
#include "pretty_print.h"

using namespace std;

/*
 * Input: data (the value to store), multiplicity of the node, height of the
 *      node, left and right child pointers
 * Returns: avl tree node.
 * Does: creates a new node with values given as input parameter
 */
static Node *new_node(int data, int multiplicity, int height, Node *left, Node *right)
{
    Node *node = new Node();

    node->data = data;
    node->count = multiplicity;
    node->height = height;
    node->left = left;
    node->right = right;

    return node;
}

/*
 * Input: data (the value to store)
 * Returns: avl tree node.
 * Does: calls a helper function to create a new node with default
 *        values parameter
 */
static Node *new_node(int data)
{
    return new_node(data, 1, 0, NULL, NULL);
}

/********************************
 * BEGIN PUBLIC AVLTREE SECTION *
 ********************************/

// Constructor
AVLTree::AVLTree()
{
    root = NULL;
}

// Copy Constructor
AVLTree::AVLTree(const AVLTree &source)
{
    root = pre_order_copy(source.root);
}

// Destructor
AVLTree::~AVLTree()
{
    post_order_delete(root);
}

// Assignment Overload
AVLTree &AVLTree::operator=(const AVLTree &source)
{
    // check for self-assignment
    if (this == &source) {
        return *this;
    }

    // delete current tree if it exists
    post_order_delete(root);

    // use pre-order traversal to copy the tree
    root = pre_order_copy(source.root);

    // don't forget to "return *this"
    return *this;
}

int AVLTree::find_min() const
{
    return find_min(root)->data;
}

int AVLTree::find_max() const
{
    return find_max(root)->data;
}

bool AVLTree::contains(int value) const
{
    return contains(root, value);
}

void AVLTree::insert(int value)
{
    root = insert(root, value);
}

void AVLTree::remove(int value)
{
    root = remove(root, value);
}

int AVLTree::tree_height() const
{
    return tree_height(root);
}

int AVLTree::node_count() const
{
    return node_count(root);
}

int AVLTree::count_total() const
{
    return count_total(root);
}

void AVLTree::print_tree() const
{
    print_pretty(root, 1, 0, std::cout);
}

/*************************
 * BEGIN PRIVATE SECTION *
 *************************/

Node *AVLTree::find_min(Node *node) const
{
    // If left child is not null, recursively search
    // for minimum in left subtree. Otherwise, return node
    return node->left ? find_min(node->left) : node;
}

Node *AVLTree::find_max(Node *node) const
{
    // If right child is not null, recursively search
    // for maximum in right subtree. Otherwise, return node
    return node->right ? find_max(node->right) : node;
}

bool AVLTree::contains(Node *node, int value) const
{
    // Covers null pointer case
    if (node == NULL) {
        return false;
    }

    // Recursively search down the tree based on the value
    // Recurse left if value is < current node value, right if >,
    // until value is found or a null pointer is reached
    if (value < node->data) {
        return contains(node->left, value);
    } 
    else if (value > node->data) {
        return contains(node->right, value);
    }
    else {
        return true;
    }
}

Node *AVLTree::insert(Node *node, int value)
{
    /* BST insertion start */
    if (node == NULL)
    {
        return new_node(value);
    }
    else if (value < node->data)
    {
        node->left = insert(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = insert(node->right, value);
    }
    else if (value == node->data)
    {
        node->count++;
        return node;
    }
    /* BST insertion ends */

    /* AVL maintenance start */
    node->height = 1 + max(tree_height(node->left), tree_height(node->right));
    node = balance(node);
    /* AVL maintenace end */

    return node;
}

Node *AVLTree::remove(Node *node, int value)
{
    /* BST removal begins */
    if (node == NULL)
    {
        return NULL;
    }

    Node *root = node;
    if (value < node->data)
    {
        node->left = remove(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = remove(node->right, value);
    }
    else
    {
        // We found the value. Remove it.
        if (node->count > 1)
        {
            node->count--;
        }
        else
        {
            if (node->left == NULL && node->right == NULL)
            {
                root = NULL;
                delete node;
                return root;
            }
            else if (node->left != NULL && node->right == NULL)
            {
                root = node->left;
                node->left = NULL;
                delete node;
            }
            else if (node->left == NULL && node->right != NULL)
            {
                root = node->right;
                node->right = NULL;
                delete node;
            }
            else
            {
                Node *replacement = find_min(node->right);
                root->data = replacement->data;
                root->count = replacement->count;
                replacement->count = 1;
                root->right = remove(root->right, replacement->data);
            }
        }
    }
    /* BST removal ends */

    /* AVL maintenance begins */
    if (root != NULL)
    {
        root->height = 1 + max(tree_height(root->left), tree_height(root->right));
        root = balance(root);
    }
    /* AVL maintenance ends */

    return root;
}

int AVLTree::tree_height(Node *node) const
{
    // If the node is null, height is -1
    // Otherwise, return the height from node struct
    return node ? node->height : -1;
}

int AVLTree::node_count(Node *node) const
{
    // If the node is null, count is 0
    // Otherwise, add 1 to the count and
    // recursively count left and right subtrees
    return node ? 1 + node_count(node->left) + node_count(node->right) : 0;
}

int AVLTree::count_total(Node *node) const
{
    // If the node is null, count total is 0
    if (node == NULL) {
        return 0;
    }

    // Otherwise, add the multiplicity of the node times the node's
    // value and then recursively count total of left and right subtrees
    return (node->count * node->data) + 
            count_total(node->left) + count_total(node->right);
}

Node *AVLTree::pre_order_copy(Node *node) const
{
    if (node == NULL)
    {
        return NULL;
    }
    Node *new_node = new Node();

    // Copy current node struct to new_node
    // Assign left/right children recursively
    new_node->data = node->data;
    new_node->height = node->height;
    new_node->count = node->count;
    new_node->left = pre_order_copy(node->left);
    new_node->right = pre_order_copy(node->right);

    return new_node;
}

void AVLTree::post_order_delete(Node *node)
{
    // If node is null, do nothing
    if (node == NULL) {
        return;
    }

    // Delete left/right children recursively
    // Then delete current node
    post_order_delete(node->left);
    post_order_delete(node->right);
    delete node;
}

Node *AVLTree::balance(Node *node)
{
    // Cover null case
    if (node == NULL) {
        return NULL;
    }

    // Update height of node before balancing
    node->height = 1 + max(tree_height(node->left), tree_height(node->right));

    // Check to see if left or right subtree is taller 
    if (height_diff(node) > 1) {
        if (height_diff(node->left) >= 0) {
            // Straight line left-left case, perform right rotation
            return right_rotate(node);
        } else {
            // Zig zag left-right case, perform left rotation on left child
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
    }
    else if (height_diff(node) < -1) {
        if (height_diff(node->right) <= 0) {
            // Straight line right-right case, perform left rotation
            return left_rotate(node);
        } else {
            // Zig zag right-left case, perform right rotation on right child
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }
    }

    return node;
}

Node *AVLTree::right_rotate(Node *node)
{
    // Use the left child as the new root node
    // Reassign current node as the right child of new_root
    Node *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;

    // Update heights by finding the maximum of the left and right subtree heights plus 1
    node->height = 1 + max(tree_height(node->left), tree_height(node->right));
    new_root->height = 1 + max(tree_height(new_root->left), tree_height(new_root->right));

    return new_root;
}

Node *AVLTree::left_rotate(Node *node)
{
    // Use the right child as the new root node
    // Reassign current node as the left child of new_root
    Node *new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;

    // Update heights by finding the maximum of the left and right subtree heights plus 1
    node->height = 1 + max(tree_height(node->left), tree_height(node->right));
    new_root->height = 1 + max(tree_height(new_root->left), tree_height(new_root->right));

    return new_root;
}

int AVLTree::height_diff(Node *node) const
{
    // If node is null, height difference is 0
    // Return difference between height of left and right subtree
    return node ? tree_height(node->left) - tree_height(node->right) : 0;
}

Node *AVLTree::find_parent(Node *node, Node *child) const
{
    if (node == NULL)
        return NULL;

    // if either the left or right is equal to the child,
    // we have found the parent
    if (node->left == child or node->right == child)
    {
        return node;
    }

    // Use the binary search tree invariant to walk the tree
    if (child->data > node->data)
    {
        return find_parent(node->right, child);
    }
    else
    {
        return find_parent(node->left, child);
    }
}
