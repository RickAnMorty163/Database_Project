/*****************************************************************//**
 * \file   main.cc
 * \brief  Complier by MSVC 14.3
 *		   Cpp Standerd 23 lastest preview
 * \brief  Add branches for two different authority users.
 * \author Li Xiang
 * \date   June 4 2024

 *********************************************************************/

#include<Windows.h>
#include "Login.hpp"

import <string>;
import <print>;

static void SetEncode(int Encode = 936) {
	SetConsoleCP(Encode);
	SetConsoleOutputCP(Encode);
}

int main(int argc, char* argv[]) {
	SetEncode();

	using namespace SQL;

	int login_flag{};
	do {
		login_flag = Login::checkLogin();
	} while (!login_flag);

	switch (login_flag) {
	case 1: {
		RootUser root;
		root.menuOption();
		break;
	}
	case 2: {
		RegularUser regular;
		regular.menuOption();
		break;
	}
	default:
		std::println("Unknown Error");
	}
}