#include "app.h"
#include "list.h"
#include <fstream>
#include <filesystem>

using std::cout, std::cin, std::endl, std::string, std::stringstream;

void app(int argc, char **argv) {
	cout << argv[1] << endl;

	//const string EXIT_CMD = "E";
	//const string QUIT_CMD = "Q";
	//const string INSERT_CMD = "I";
	//const string DELETE_CMD = "D";
	//const string LIST_CMD = "L";

	bool quit = false;

	LinkedList list;
	string command;
	string filename = argv[1];

	int list_length = file_to_linked_list(list, filename);
	int cursor_location = list_length;

	do {
		int first_param = -1;
		int second_param = -1;
		string input;

		cout << cursor_location << ">";
		getline(cin, input);

		stringstream ss(input);

		ss >> command;

		if (input.empty()) {
			command = input;
		}

		switch (command[1]) {
			constexpr char EXIT_CMD = 'E'; //constexpr at compile time rather than run time
			constexpr char QUIT_CMD = 'Q';
			constexpr char INSERT_CMD = 'I';
			constexpr char DELETE_CMD = 'D';
			constexpr char LIST_CMD = 'L';

			case EXIT_CMD:
				if (is_valid_exit_or_quit_cmd(input)) {
					save_and_exit(list, filename);
					quit = true;
				} else {
					add_or_insert(cursor_location, list_length, list, input);
				}
			break;

			case QUIT_CMD:
				if (is_valid_exit_or_quit_cmd(input)) {
					quit = true;
				} else {
					add_or_insert(cursor_location, list_length, list, input);
				}
			break;

			case INSERT_CMD:
				if (is_valid_insert_cmd(input)) {
					if (ss.eof()) {
						cursor_location--;
						continue;
					}

                    ss >> cursor_location;
					continue;
				}

				add_or_insert(cursor_location, list_length, list, input);
			break;

			case DELETE_CMD:
				if (is_valid_list_or_delete_cmd(input, list_length)) {
					if (ss.eof()) {
						list.remove(cursor_location - 1);
						cursor_location--;
						list_length--;
						continue;
					}

					ss >> first_param;
					if (ss.eof()) {
						list.remove(first_param);
						list_length--;
						cursor_location = list_length;
						update_list(list);
						continue;
					}

					ss >> second_param;
					list.remove(second_param);

					if (first_param > second_param) {
						//quick swap of the values if the first is bigger than the second
						first_param += second_param;
						second_param = first_param - second_param;
						first_param -= second_param;
					}

					for (int i = first_param; i <= second_param; i++) {
						list.remove(i);
						list_length--;
					}

					cursor_location = list_length;
					update_list(list);
					continue;
				}

				add_or_insert(cursor_location, list_length, list, input);
			break;

			case LIST_CMD:
				if (is_valid_list_or_delete_cmd(input, list_length)) {
					if (ss.eof()) {
						cout << list;
						cursor_location = list_length;
						continue;
					}

					ss >> first_param;
					if (ss.eof()) {
						for (auto n: list) {
							if (n->_line_number == first_param) {
								cout << n->_line_number << ">" << n->_data << endl;
							}
						}
						cursor_location = ++first_param;
						continue;
					}

					ss >> second_param;
					if (first_param > second_param) {
						first_param += second_param;
						second_param = first_param - second_param;
						first_param -= second_param;
					}
					for (auto n: list) {
						if ((n->_line_number >= first_param) && (n->_line_number <= second_param)) {
							cout << n->_line_number << ">" << n->_data << endl;
						}
					}
					cursor_location = ++second_param;
					continue;
				}

				add_or_insert(cursor_location, list_length, list, input);
				break;

			default:
				add_or_insert(cursor_location, list_length, list, input);

		}

		update_list(list);

		cursor_location++;
		list_length++;
	} while (!quit);

	cout << list << endl;
}

bool is_valid_list_or_delete_cmd(const string& str, const int list_length) {
	//List and delete both use this function because they are the only function that can have 0 - 2 parameters
	string first_word;
	int first_param = -1;
	int second_param = -1;
	stringstream ss(str);


	ss >> first_word;
	if (ss.eof()) {
		return true;
	}

	string second_word;
	ss >> second_word;
	if ((ss.eof() && (stringstream(second_word) >> first_param) && (first_param <= list_length))) {
		return true;
	}

	if ((stringstream(second_word) >> first_param) && (first_param <= list_length)) {
		string third_word;
		ss >> third_word;

		if (ss.eof() && (stringstream(third_word) >> second_param)) {
			return true;
		}
	}

	return false;
}

bool is_valid_insert_cmd(const string& str) {
	string first_word;
	string third_word;
	int second_param = -1;
	stringstream ss(str);

	ss >> first_word;
	if (ss.eof()) {
		return true;
	}

	string second_word;
	ss >> second_word;
	if ((ss.eof() && (stringstream(second_word) >> second_param))) {
		return true;
	}

	return false;
}

bool is_valid_exit_or_quit_cmd(const string &str) {
	string first_word;
	stringstream ss(str);

	ss >> first_word;
	if (ss.eof()) {
		return true;
	}

	return false;
}

void add_or_insert(const int cursor_pos, const int list_length, LinkedList& list, const string& str) {
	if (cursor_pos == list_length) {
		list.add(list_length, str);
	} else {
		list.insert(cursor_pos, cursor_pos, str);
	}
}

void update_list(const LinkedList &list) {
	//This function is to keep the Linked list's line number current for listing purposes
	int lines = 1;
	for (const auto n: list) {
		n->_line_number = lines++;
	}
}

int file_to_linked_list(LinkedList& list, const string& filename) {
	int list_length = 1; // initialized to 1 for printing to match desired output

	if (std::filesystem::exists(filename)) {
		std::ifstream file;
		string line;
		file.open(filename);
		while (getline(file, line)) {
			cout << list_length << ">" << line << endl;
			list.add(list_length, line);
			list_length++;
		}
		file.close();
	}

	return list_length;
}

void save_and_exit(const LinkedList& list, const string& filename) {
	std::ofstream file;
	string line;
	file.open(filename);

	if (file.is_open()) {
		for (const auto n: list) {

			if ( n->_next == nullptr ) {
                file << n->_data ;
				return;
			}

            file << n->_data << endl;
		}
	}

	file.close();
}
