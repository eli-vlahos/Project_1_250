/*
 * orderedlist.cpp
 *
 *  Created on: Oct. 5, 2020
 *      Author: elicv
 */
#include <iostream>
#include <cmath>
#include "Ordered_List.h"



Ordered_List::Ordered_List() {

	this->size = -1;

}

void Ordered_List::initializer(int const &m) {

	this->hash_table = std::vector<Information_Address> (m);

	for (int i = 0; i < m; i++) {
		this->hash_table[i].status = "empty";
		this->hash_table[i].head = nullptr;
	}

	this->size = m;


}

Ordered_List::~Ordered_List() {

	for (int i = 0; i < this->size; i++){
		Node *temp = this->hash_table[i].head;

		while (temp != nullptr){
			Node *temptemp = temp;
			temp = temp->get_next();
			delete temptemp;
		}

	}
}

void Ordered_List::pseudo_destructor() {

	for (int i = 0; i < this->size; i++){
		Node *temp = this->hash_table[i].head;

		while (temp != nullptr){
			Node *temptemp = temp;
			temp = temp->get_next();
			delete temptemp;
		}

	}
}

int Ordered_List::hash_1(double const &k) {

	int h;

	h = std::fmod(k,this->size);

	return h;
}

int Ordered_List::get_size(){
	return this->size;
}

std::vector<Information_Address> Ordered_List::get_hash_table(){
	return this->hash_table;
}

void Ordered_List::direct(std::vector<std::string> line) {

	if(line[0] == "n"){
		if (this->size != -1) {

			this->pseudo_destructor();
			this->hash_table.clear();
			this->initializer(stoi(line[1]));
			std::cout<<"success" <<std::endl;
		}
		else {
			this->initializer(stoi(line[1]));
			std::cout<< "success" << std::endl;
		}
	}

	else if(line[0] == "i") {

		line = this->vector_cleaner(line);


		double number = stod(line[0]);
		int probe = hash_1(number);
		if (this->insert(number, probe, line[1])){
			std::cout<<"success"<<std::endl;
		}
		else{
			std::cout<<"failure"<<std::endl;
		}


	}

	else if(line[0] == "s"){

		line = this->vector_cleaner(line);

		double number = stod(line[0]);
		int probe = hash_1(number);
		std::string name = this->search(number, probe);

		if(name != "null"){
			std::cout<< "found " << name << "in " << probe <<std::endl;;
		}

		else{
			std::cout<<"not found"<<std::endl;
		}


	}
	else if (line[0] == "d"){

		line = this->vector_cleaner(line);

		double number = stod(line[0]);
		int probe = hash_1(number);

		if (del(number, probe)){
			std::cout<<"success"<<std::endl;
		}
		else{
			std::cout<<"failure"<<std::endl;
		}

	}
	else if (line[0] == "p"){
		line = this->vector_cleaner(line);
		int probe = hash_1(stold(line[0]));

		this->print(probe);
	}

}

std::vector<std::string> Ordered_List::vector_cleaner(std::vector<std::string> line) {


	line.erase(line.begin());
	int size = line.size();
	std::string temp;


	int p = line[0].find(";");
	temp = line[0].substr(p+1);
	temp += " ";

	line[0] = line[0].substr(0,p);

	for (int i = 1; i < size; i++){
		temp +=line[i]+ " ";
	}

	line[1] = temp;

	return line;
}


std::string Ordered_List::search(double const &number, int const &probe) {

		if (this->hash_table[probe].status == "empty") {
			return "null";
		}
		else {

			if (number == hash_table[probe].number && hash_table[probe].status != "deleted") {
				return hash_table[probe].name;
			}
			else if (hash_table[probe].head == nullptr){
				return "null";
			}
			Node *pointer = hash_table[probe].head;


			while (pointer->get_next() != nullptr) {
				if (pointer->get_info().number == number) {
					return pointer->get_info().name;
					}
				pointer = pointer->get_next();
				}

			}
	return "null";
}


bool Ordered_List::insert(double const &number, int const &probe, std::string const &name) {

	if (this->search(number, probe) == "null") {


			if (this->hash_table[probe].status == "empty" || this->hash_table[probe].status == "deleted") {
				//if nothing is in the slot insert
				this->hash_table[probe].number = number;
				this->hash_table[probe].name = name;
				this->hash_table[probe].status = "occupied";

			}

			else {

				Node *pointer = this->hash_table[probe].head;
				Node *current = new Node(number, name, nullptr);

				if (number < this->hash_table[probe].number) {
					Node *temp = new Node(this->hash_table[probe].number, this->hash_table[probe].name, pointer);
					this->hash_table[probe].head = temp;
					this->hash_table[probe].number = number;
					this->hash_table[probe].name = name;
					delete current;
				}
				else if (this->hash_table[probe].head == nullptr) {
					current->set_next(pointer);
					this->hash_table[probe].head = current;
				}
				else if (pointer->get_next() == nullptr){
					if (pointer->get_info().number > number){

						this->hash_table[probe].head = current;
						current->set_next(pointer);

					}
					else {
						pointer->set_next(current);
					}
				}

				else {

					Node *last = pointer;
					pointer = pointer->get_next();

					while (number < pointer->get_info().number && pointer != nullptr){
						last = pointer;
						pointer = pointer->get_next();
					}

					last->set_next(current);
					current->set_next(pointer);

				}

			}
			return 1;
	}

	return 0;
}

bool Ordered_List::del(double const &number, int const &probe) {


			if (this->hash_table[probe].status == "empty") {
				return 0;
			}

			else {
				Node *pointer = hash_table[probe].head;
				Node *last = pointer;

				if (this->hash_table[probe].number == number) {
					hash_table[probe].status = "deleted";
					return 1;
				}
				else if (pointer == nullptr){
					return 0;
				}
				else if (pointer->get_info().number == number) {
					hash_table[probe].head = pointer->get_next();
					delete pointer;
					return 1;
				}
				else if (pointer->get_next() == nullptr){
					return 0;
				}
				else {

					while (number != pointer->get_info().number && pointer != nullptr) {
						last = pointer;
						pointer = pointer->get_next();
					}
					if (pointer != nullptr){
						last->set_next(pointer->get_next());
						delete pointer;
						return 1;
					}

				}
			}

	return 0;
}

void Ordered_List::print(int const &probe){

	bool check = 0;

	Node *pointer = this->hash_table[probe].head;
	if (this->hash_table[probe].status != "empty")	
	{
		if (this->hash_table[probe].status != "deleted"){
			std::cout<<static_cast<long>(hash_table[probe].number) << " ";
			check = 1;
		}

		if (pointer != nullptr) {
			while (pointer != nullptr) {
				std::cout<< static_cast<long>(pointer->get_info().number) << " ";
				pointer = pointer->get_next();
			}
			check = 1;
		}

	}

	if (check){
		std::cout<<std::endl;
	}
}
