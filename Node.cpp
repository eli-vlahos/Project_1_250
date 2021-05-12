/**

*/



#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;

#include "Node.h"

/**


*/

Node::Node(double const &number, std::string const &name, Node *p_next_node) {

	this->info.name = name;
	this->info.number = number;
	this->info.status = "occupied";
	this->p_next_node = p_next_node;

 }


Node::~Node(){

}

Node *Node::get_next() {
	return this->p_next_node;
}

Information Node::get_info(){

	return this->info;
}

void Node::set_next(Node *next) {
	this->p_next_node = next;
}
 


