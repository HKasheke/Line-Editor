#ifndef LIST_H
#define LIST_H

#include <iostream>

using std::string;

class LinkedList {
    struct Node {
        int _line_number{-1}; // Used to list and delete specific nodes, faster to compare an integer
    	string _data;
        Node* _next{nullptr};
    };

    Node* _start{nullptr};

public:
    class iterator {
        Node* _node{nullptr};

    public:
        explicit iterator(Node* node) : _node(node){}
        bool operator!=(const iterator& rhs) const;
        iterator& operator++();
        Node* operator*() const;
    };

    iterator begin() const { return iterator(_start); }
	static iterator end() { return iterator(nullptr); }
    void add(int line_num, const string &data);

    ///
    /// @param line_num nodes line number
    /// @param before_value the value of the node to insert before
    /// @param data the data to be inserted
    void insert(int line_num, int before_value, const string& data);
    void remove(int line_num);
    friend std::ostream& operator<<(std::ostream& output, const LinkedList& list);
};

void listing();

#endif
