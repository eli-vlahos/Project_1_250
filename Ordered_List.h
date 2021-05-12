/*
 * Ordered_List.h
 *
 *  Created on: Oct. 5, 2020
 *      Author: elicv
 */

#ifndef ORDEREDLIST_H_
#define ORDEREDLIST_H_

#include <iostream>
#include <vector>
#include "Node.h"

struct Information_Address {
	std::string name;
	double number;
	std::string status;
	Node *head;

};

class Ordered_List {
public:
	Ordered_List();
	void initializer(int const &m);
	virtual ~Ordered_List();

	void pseudo_destructor();
	void direct(std::vector<std::string> line);
	int hash_1(double const &k);
	std::vector<Information_Address> get_hash_table();
	int get_size();

	std::vector<std::string> vector_cleaner(std::vector<std::string>);
	std::string search(double const &number, int const &probe);
	bool insert(double const &number, int const &probe, std::string const &name);
	bool del(double const &number, int const &probe);
	void print(int const &probe);

private:
	std::vector<Information_Address> hash_table;
	int size;
};

#endif /* OrderedLIST_H_ */
