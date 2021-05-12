/**

*/

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "Struct_Information.h"

class Node {


    // class variables
	private:
		Information info;  // slot for all info
		Node *p_next_node;  // address of next node


    // class functions
    public:
		Node (double const &number, std::string const &name, Node *p_next_node);
		~Node();


		Node *get_next();
		Information get_info();
		void set_next(Node *next);



};

#endif
