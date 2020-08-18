#ifndef BTNODE_H_
#define BTNODE_H_
#include <sstream>

/** A node for a Binary Tree. */
template<typename Item_Type>
struct BTNode
{
    // Data Fields
    Item_Type data;
    BTNode<Item_Type>* left;
    BTNode<Item_Type>* right;
    
    // Constructor
    BTNode(const Item_Type& the_data,
        BTNode<Item_Type>* left_val = NULL,
        BTNode<Item_Type>* right_val = NULL) :
        data(the_data), left(left_val), right(right_val) {}

    // Destructor (to avoid warning message)
    virtual ~BTNode() {}

    // to_string
    virtual std::string to_string() const {
        std::ostringstream os;
        os << data;
        return os.str();
    }

    BTNode<Item_Type>* BuildTree(int height_needed);

    
}; // End BTNode

template<typename Item_Type>
BTNode<Item_Type>* BTNode<Item_Type>::BuildTree(int height) {
    if (height <= 0)
        return nullptr;
    const char dummy = 'Z';
    auto node = new BTNode<Item_Type>(dummy);

    node->left = BuildTree(height - 1);
    node->right = BuildTree(height - 1);
    return node;
}
// Overloading the ostream insertion operator
template<typename Item_Type>
std::ostream& operator<<(std::ostream& out,
    const BTNode<Item_Type>& node) {
    return out << node.to_string();
}



#endif