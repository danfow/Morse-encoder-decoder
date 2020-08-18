#ifndef BINARY_TREE_H
#define BINARY_TREE_H

/** Class for a binary tree. */

#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <fstream>
#include "tree_node.h"
#include <iostream>
#include <vector>
using namespace std;

template<typename Item_Type>
class Binary_Tree
{
public:

    // Constructors and Functions

    /** Construct an empty Binary_Tree. */
    Binary_Tree() : root(NULL) {}

    /** Construct a Binary_Tree with two subtrees.
        @param the_data The data at the root
        @param left_child The left subtree
        @param right_child The right subtree
    */
    Binary_Tree(const Item_Type& the_data,
        const Binary_Tree<Item_Type>& left_child
        = Binary_Tree(),
        const Binary_Tree<Item_Type>& right_child
        = Binary_Tree()) :
        root(new BTNode<Item_Type>(the_data, left_child.root,
            right_child.root)) {}

    /** Virtual destructor to avoid warnings */
    virtual ~Binary_Tree() {} // Do nothing.


    /** Return the left subtree. */
    Binary_Tree<Item_Type> get_left_subtree() const;

    /** Return the right subtree. */
    Binary_Tree<Item_Type> get_right_subtree() const;

    /** Return the data field of the root.
        @throws std::invalid_argument if empty tree
    */
    const Item_Type& get_data() const;

    /** Indicate that this is the empty tree. */
    bool is_null() const;

    /** Indicate that this tree is a leaf. */
    bool is_leaf() const;

    /** Return a string representation of this tree. */
    virtual std::string to_string() const;

    /** Read a binary tree */
    static Binary_Tree<Item_Type> read_binary_tree(std::istream& in);
  
    
    

    /** Return a string representation of the root */
    std::string root_to_string() const {
        return root->to_string();
    }

    /*<exercise chapter="8" section="3" type="programming" number="1">*/
    /** Return a pre-order traversal of the tree */
    std::string pre_order() const {
        return pre_order(root);
    }
    /*</exercise>*/

    /*<exercise chapter="8" section="3" type="programming" number="2">*/
    /** Return a post-order traversal of the tree */
    std::string post_order() const {
        return post_order(root);
    }
    /*</exercise>*/

    /*<exercise chapter="8" section="3" type="programming" number="5">*/
    std::string in_order() const {
        return in_order(root);
    }
    /*</exercise>*/

    /*<exercise chapter="8" section="3" type="programming" number="3">*/
    /** Return the height of the binary tree */
    int height() const {
        if (is_null()) return 0;
        return 1 + max(get_left_subtree().height(), get_right_subtree().height());
    }
    /*</exercise>*/

    /*<exercise chapter="8" section="3" type="programming" number="4">*/
    int number_of_nodes() const {
        if (is_null()) return 0;
        return 1 + get_left_subtree().number_of_nodes() + get_right_subtree().number_of_nodes();
    }

    Binary_Tree<Item_Type> create_empty_tree(); //returnes a binary tree with all of the nodes for each character in the correct position
    string encode(string user_phrase); // converts a phrase provided by the user to morse code
    void  decode(string encoded_message); // convertes a morse code string back to a regular message

   
  
    /*</exercise>*/


protected:

    // Protected constructor
    /** Construct a Binary_Tree with a given node as the root */
    Binary_Tree(BTNode<Item_Type>* new_root) : root(new_root) {}

    // Data Field
    BTNode<Item_Type>* root;

private:

    /*<exercise chapter="8" section="3" type="programming" number="1">*/
    /** Return a pre-order traversal of the tree */
    std::string pre_order(const BTNode<Item_Type>* local_root) const;
    /*</exercise>*/

    /*<exercise chapter="8" section="3" type="programming" number="2">*/
    /** Return a post-order traversal of the tree */
    std::string post_order(const BTNode<Item_Type>* local_root) const;
    /*</exercise>*/
    /*<exercise chapter="8" section="3" type="programming" number="5">*/
    std::string in_order(const BTNode<Item_Type>* local_root) const;
    /*</exercise>*/



};  // End Binary_Tree

// Overloading the ostream insertion operator.
template<typename Item_Type>
std::ostream& operator<<(std::ostream& out,
    const Binary_Tree<Item_Type>& tree)
{
    return out << tree.to_string();
}

// Overloading the istream extraction operator
template<typename Item_Type>
std::istream& operator>>(std::istream& in,
    Binary_Tree<Item_Type>& tree)
{
    tree = Binary_Tree<Item_Type>::read_binary_tree(in);
    return in;
}

// Implementation of member functions


// Accessors
/** Return the left-subtree. */
template<typename Item_Type>
Binary_Tree<Item_Type>
Binary_Tree<Item_Type>::get_left_subtree() const {
    if (root == NULL) {
        throw std::invalid_argument("get_left_subtree on empty tree");
    }
    return Binary_Tree<Item_Type>(root->left);
}


/** Return the right-subtree */
template<typename Item_Type>
Binary_Tree<Item_Type>
Binary_Tree<Item_Type>::get_right_subtree() const {
    if (root == NULL) {
        throw std::invalid_argument("get_right_subtree on null tree");
    }
    return Binary_Tree<Item_Type>(root->right);
}

/** Return the data field of the root
    @throws std::invalid_argument if null tree
*/
template<typename Item_Type>
const Item_Type& Binary_Tree<Item_Type>::get_data() const {
    if (root == NULL) {
        throw std::invalid_argument("get_data on null tree");
    }
    return root->data;
}

template<typename Item_Type>
bool Binary_Tree<Item_Type>::is_null() const {
    return root == NULL;
}

/** Indicate that this tree is a leaf. */
template<typename Item_Type>
bool Binary_Tree<Item_Type>::is_leaf() const {
    if (root != NULL) {
        return root->left == NULL && root->right == NULL;
    }
    else
        return true;
}

/** Return a string representation of this tree */
template<typename Item_Type>
std::string Binary_Tree<Item_Type>::to_string() const {
    std::ostringstream os;
    if (is_null())
        os << "NULL\n";
    else {
        os << *root << '\n';
        os << get_left_subtree().to_string();
        os << get_right_subtree().to_string();
    }
    return os.str();
}

template<typename Item_Type>
Binary_Tree<Item_Type> Binary_Tree<Item_Type>::
read_binary_tree(std::istream& in) {
    std::string next_line;
    getline(in, next_line);
    if (next_line == "NULL") {
        return Binary_Tree<Item_Type>();
    }
    else {
        Item_Type the_data;
        std::istringstream ins(next_line);
        ins >> the_data;
        Binary_Tree<Item_Type> left = read_binary_tree(in);
        Binary_Tree<Item_Type> right = read_binary_tree(in);
        return Binary_Tree<Item_Type>(the_data, left, right);
    }
}
template<typename Item_Type>
Binary_Tree<Item_Type> Binary_Tree<Item_Type>::create_empty_tree() {
    /*create empty tree*/
    char user_data = '.';
    BTNode<char> root_node(user_data);
    BTNode<char> e_node('E');
    BTNode<char> t_node('T');
    BTNode<char> i_node('I');
    BTNode<char> a_node('A'); 
    BTNode<char> n_node('N');
    BTNode<char> m_node('M');
    BTNode<char> s_node('S');
    BTNode<char> u_node('U');
    BTNode<char> h_node('H');
    BTNode<char> v_node('V');
    BTNode<char> f_node('F');
    BTNode<char> r_node('R');
    BTNode<char> w_node('W');
    BTNode<char> L_node('l');
    BTNode<char> p_node('p');
    BTNode<char> j_node('j');
    BTNode<char> d_node('d');
    BTNode<char> k_node('k');
    BTNode<char> b_node('b');
    BTNode<char> x_node('x');
    BTNode<char> c_node('c');
    BTNode<char> y_node('y');
    BTNode<char> g_node('g');
    BTNode<char> o_node('O');
    BTNode<char> z_node('z');
    BTNode<char> q_node('q');


    Binary_Tree<Item_Type> g_tree(g_node, z_node, q_node);
    Binary_Tree<Item_Type> m_tree(m_node, g_tree, o_node);
    Binary_Tree<Item_Type> k_tree(k_node, c_node, y_node);
    Binary_Tree<Item_Type> d_tree(d_node, b_node, x_node);
    Binary_Tree<Item_Type> n_tree(n_node, d_tree, k_tree);
    Binary_Tree<Item_Type> w_tree(w_node, p_node, j_node);
    Binary_Tree<Item_Type> r_tree(r_node, L_node);
    Binary_Tree<Item_Type> a_tree(a_node,r_tree, w_tree);
    Binary_Tree<Item_Type> u_tree(u_node, f_node);
    Binary_Tree<Item_Type> s_tree(s_node, h_node, v_node);
    Binary_Tree<Item_Type> i_tree(i_node, s_tree, u_tree);
    Binary_Tree<Item_Type> e_tree(e_node, i_tree, a_tree);
    Binary_Tree<Item_Type> t_tree(t_node, n_tree, m_tree);
    Binary_Tree<Item_Type> tree(root_node, e_tree, t_tree);
    
    
   

    
    
    

    
    return tree;

}

template<typename Item_Type>
string Binary_Tree<Item_Type>::encode(string user_phrase) {
    //vector of pairs that has stores each character alongside its morse code equivilent
    vector <pair<char, string>> decode_vector{ {'A',"*-"},{'B',"-***"}, {'C',"-*-*"},{'D',"-**"},
    {'E',"*"},{'F',"**-*"},{'G',"--*"},{'H', "****"},{'I',"**"},{'J',"*---"}, {'K',"-*-"},
    {'L',"*-**"},{'M',"--"},{'N',"-*"},{'O',"---"},{'P',"*--*"},{'Q',"--*-"},{'R',"*-*"},
    {'S',"***"},{'T',"-"},{'U',"**-"},{'V',"***-"},{'W',"*--"},{'X',"-**-"},{'Y',"-*--"},{'Z',"--**"}
    };
    
    //Iterate through uncoded message. Check character by character. If character matches character in decode_vector append that morse code match to our new coded_phrase string. After all iterations are done return coded_phrase;
    string coded_phrase;
    for (int i = 0; i < user_phrase.length(); i++) {
        for (int j = 0; j < decode_vector.size(); j++) {
            if (decode_vector.at(j).first == user_phrase.at(i)) {
                string temp = decode_vector.at(j).second;
                coded_phrase.append(temp);
                coded_phrase += "    ";
            }
        }
    }

    return coded_phrase;

}


/*Uses the binary tree I created to decode a morse string. Iterates through the decoded string character by character. If it encounters a "*" it goes left and if it encounters a "-" it goes right. 
Once it encounters 3 spaces (start of a new word) we are done with that morse code so output data where the pointer is currently located.*/
template<typename Item_Type>
void Binary_Tree<Item_Type>::decode(string encoded_message) {
    Binary_Tree<BTNode<char>> morse_tree = create_empty_tree();
    string decoded_message;
    BTNode<Item_Type>* travel_pointer = morse_tree.root;
    int num_spaces = 0;
   
   

    for (int i = 0; i < encoded_message.length(); i++) {
        if (isspace(encoded_message.at(i)) && num_spaces == 3) {
            
            Item_Type user_char = travel_pointer->data;
            cout << user_char;
            travel_pointer = morse_tree.root; 
            num_spaces = 0;
            
            
              
 
        }
        else if (encoded_message.at(i) == '*') {
            travel_pointer = travel_pointer->left;

        }
        else if (encoded_message.at(i) == '-') {
            travel_pointer = travel_pointer->right;

        }

        else {
            num_spaces += 1;
        }

        
        
        
    }

   
}










/*<exercise chapter="8" section="3" type="programming" number="1">*/
/** Return a pre-order traversal of the tree */
template<typename Item_Type>
std::string Binary_Tree<Item_Type>::pre_order(const BTNode<Item_Type>* local_root) const {
    std::string result;
    if (local_root != NULL) {
        result += local_root->to_string();
        if (local_root->left != NULL) {
            result += " ";
            result += pre_order(local_root->left);
        }
        if (local_root->right != NULL) {
            result += " ";
            result += pre_order(local_root->right);
        }
    }
    return result;
}
/*</exercise>*/

/*<exercise chapter="8" section="3" type="programming" number="2">*/
/** Return a post-order traversal of the tree */
template<typename Item_Type>
std::string Binary_Tree<Item_Type>::post_order(const BTNode<Item_Type>* local_root) const {
    std::string result;
    if (local_root != NULL) {
        if (local_root->left != NULL) {
            result += post_order(local_root->left);
            result += " ";
        }
        if (local_root->right != NULL) {
            result += post_order(local_root->right);
            result += " ";
        }
        result += local_root->to_string();
    }
    return result;
}
/*</exercise>*/

/*<exercise chapter="8" section="3" type="programming" number="2">*/
/** Return an in-order traversal of the tree */
template<typename Item_Type>
std::string Binary_Tree<Item_Type>::in_order(const BTNode<Item_Type>* local_root) const {
    std::string result;
    if (local_root != NULL) {
        result += "(";
        if (local_root->left != NULL) {
            result += in_order(local_root->left);
            result += " ";
        }
        result += local_root->to_string();
        if (local_root->right != NULL) {
            result += " ";
            result += in_order(local_root->right);
        }
        result += ")";
    }
    return result;
}
/*</exercise>*/

#endif

