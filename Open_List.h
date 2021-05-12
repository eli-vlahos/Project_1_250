/*
 * Open_List.h
 *
 *  Created on: Oct. 5, 2020
 *      Author: elicv
 */

#ifndef OPENLIST_H_
#define OPENLIST_H_

#include <iostream>
#include <vector>
#include "Struct_Information.h"

class Open_List {
public:
	Open_List();
	void initializer(int const &m);
	virtual ~Open_List();

	void direct(std::vector<std::string> line);
	int hash_1(double const &k);
	int hash_2(double const &k);
	std::vector<Information>get_hash_table();
	int get_size();

	std::vector<std::string> vector_cleaner(std::vector<std::string>);
	int search(double const &number, int probe, int const &offset);
	bool insert(double const &number, int probe, int const &offset, std::string const &name);

private:
	std::vector<Information> hash_table;
	int size;
};

#endif /* OPENLIST_H_ */
