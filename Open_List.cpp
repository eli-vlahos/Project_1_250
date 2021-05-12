/*
 * openlist.cpp
 *
 *  Created on: Oct. 5, 2020
 *      Author: elicv
 */
#include <iostream>
#include <cmath>
#include "Open_List.h"



Open_List::Open_List() {

	this->size = -1;


}

void Open_List::initializer(int const &m) {

	this->hash_table = std::vector<Information> (m);

	for (int i = 0; i < m; i++){
		this->hash_table[i].status = "empty";
	}

	this->size = m;


}

Open_List::~Open_List() {
	// TODO Auto-generated destructor stub
}

int Open_List::hash_1(double const &k) {

	int h;

	h = std::fmod(k,this->size);

	return h;
}

int Open_List::hash_2(double const &k) {

	int h;

	h = std::fmod((k/this->size), this->size);

	if (h %2 ==0){
		h +=1;
	}

	return h;
}

int Open_List::get_size(){
	return this->size;
}

std::vector<Information> Open_List::get_hash_table(){
	return this->hash_table;
}

void Open_List::direct(std::vector<std::string> line) {

	if(line[0] == "n"){
		if (this->size != -1) {
			this->hash_table.clear();
			this->initializer(stoi(line[1]));
			std::cout<<"success" <<std::endl;
		}
		else {
			this->initializer(stoi(line[1]));
			std::cout<< "success" << std::endl;
		}
	}

	else if(line[0] == "i"){

		line = this->vector_cleaner(line);

		double number = stod(line[0]);
		int probe = hash_1(number);
		int offset = hash_2(number);
		int position = this->search(number, probe, offset);

		if (position != -1){
			std::cout << "failure" <<std::endl;
		}
		else {
			std::string name = line[1];

			if (this->insert(number, probe, offset, name)){
				std::cout<< "success"<<std::endl;
			}
			else{
				std::cout<<"failure"<<std::endl;
			}
		}

	}
	else if(line[0] == "s"){

		line = this->vector_cleaner(line);

		double number = stod(line[0]);
		int probe = hash_1(number);
		int offset = hash_2(number);
		int position = search(number, probe, offset);

		if ( position != -1){
			std::cout << "found " << this->hash_table[position].name << "in " << position << std::endl;
		}
		else{
			std::cout << "not found" <<std::endl;
		}


	}
	else if (line[0] == "d"){

		line = this->vector_cleaner(line);

		double number = stod(line[0]);
		int probe = hash_1(number);
		int offset = hash_2(number);
		int position = search(number, probe, offset);

		if ( position != -1){
			this->hash_table[position].status = "deleted";
			std::cout << "success" <<std::endl;
		}
		else{
			std::cout << "failure" <<std::endl;
		}

	}

}

std::vector<std::string> Open_List::vector_cleaner(std::vector<std::string> line) {

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


int Open_List::search( double const &number, int probe, int const &offset) {

	for (int i = 0; i < this->size; i++) {
		if (this->hash_table[probe].status == "empty" || this->hash_table[probe].status == "deleted") {
			return -1;
		}
		else {

			if (number == this->hash_table[probe].number) {
				return probe;
			}

			probe = (offset+probe) % this->size;
		}

	}

	return -1;
}

bool Open_List::insert(double const &number, int probe, int const &offset, std::string const &name) {

	if (search(number, probe, offset) == -1) {

		for (int i = 0; i < this->size; i++) {
			if (this->hash_table[probe].status == "empty" || this->hash_table[probe].status == "deleted") {
				this->hash_table[probe].number = number;
				this->hash_table[probe].name = name;
				this->hash_table[probe].status = "occupied";

				return 1;
			}

			else {
				probe = (offset+probe) % this->size;
			}
		}

	}

	return 0;
}


