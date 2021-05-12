/*
 * openhttest.cpp
 *
 *  Created on: Oct. 5, 2020
 *      Author: elicv
 */

#include <iostream>
#include <vector>
#include <regex>
#include <math.h>
#include <cmath>

using namespace std;


#include "Open_List.h"

int main()
{

	Open_List list;


	std::regex ws_re("\\s+");

	std::string cmdline;
	getline(std::cin, cmdline);


		while(! std::cin.eof()) {


			if (cmdline == "exit") {
				return 0;
			}

			std::vector<std::string> line {
				std::sregex_token_iterator(cmdline.begin(), cmdline.end(), ws_re, -1), {}
			};

			list.direct(line);

			getline(std::cin, cmdline);


		}


	return 0;

}







