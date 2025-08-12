#include "list.h"

void LinkedList::add(const int line_num, const string& data) {
	const auto node = new Node({line_num, data});

	// is this the first node?
	if (_start == nullptr) {
		// yes!
		_start = node;
	}
	else {
		// no.
		auto prev = static_cast<Node *>(nullptr);
		auto curr = _start;

		// loop until the end of the chain is found
		while (curr != nullptr) {
			prev = curr;
			curr = curr->_next;
		}

		// did I find the end of the chain?
		if (prev != nullptr) {
			prev->_next = node;
		}
	}
}

///
/// @param line_num node's line number
/// @param before_value the value of the node to insert before
/// @param data the data to be inserted
void LinkedList::insert(const int line_num, const int before_value, const string& data) {
	const auto new_node = new Node({line_num, data});

	auto node = _start;
	auto prev = static_cast<Node*>(nullptr);

	// find the node to insert before
	while (node != nullptr) {
		// look for value to insert before
		if (node->_line_number == before_value) {
			break;
		}
		prev = node;
		node = node->_next;
	}

	// did we find our node?
	if (node != nullptr) {
		// are we inserting at the beginning?
		if (prev == nullptr) {
			// yes! we are at the start
			new_node->_next = _start;
			_start = new_node;
		}
		else {
			// no, just in the middle
			new_node->_next = prev->_next;
			prev->_next = new_node;
		}
	}
}

void LinkedList::remove(const int line_num) {
	auto prev = static_cast<Node*>(nullptr);
	auto node = _start;

	// find the node to delete
	while (node != nullptr) {
		// look for the node with a particular value
		if (node->_line_number == line_num) {
			// we found the node!
			break;
		}
		prev = node;
		node = node->_next;
	}

	// did we find the node to delete?
	if (node != nullptr) {
		// yes! we did find the node!

		// is this node the first node?
		if (prev == nullptr) {
			// yes! it is the first node!
			_start = node->_next;
		}
		else {
			// no, it isn't.
			prev->_next = node->_next;
		}

		delete node;
	}
}

bool LinkedList::iterator::operator!=(const iterator& rhs) const { return _node != rhs._node; }

LinkedList::iterator& LinkedList::iterator::operator++() {
	_node = _node->_next;
	return *this;
}

LinkedList::Node *LinkedList::iterator::operator*() const { return _node; }

std::ostream& operator<<(std::ostream& output, const LinkedList& list) {
    auto node = list._start;

    while (node != nullptr) {
        output << node->_line_number << ">" << node->_data << std::endl;
        node = node->_next;
    }

    return output;
}