#ifndef APP_H
#define APP_H

#include <iostream>
#include <sstream>

#include "list.h"

using std::cout, std::cin, std::endl, std::string, std::stringstream;

void app(int argc, char** argv);
bool is_valid_list_or_delete_cmd(const string &str, int list_length);
bool is_valid_exit_or_quit_cmd(const string &str);
bool is_valid_insert_cmd(const string &str);
void add_or_insert(int cursor_pos, int list_length, LinkedList &list, const string &str);
void update_list(const LinkedList &list);
void save(LinkedList &list, const string& filename);
int file_to_linked_list(LinkedList& list, const string& filename);
void save_and_exit(const LinkedList& list, const string& filename);

#endif
