/*****************************************************************//**
 * \file   main.cc
 * \brief  Complier by MSVC 14.3
 *		   Cpp Standerd 23 lastest preview
 * \brief  Add branches for two different authority users.
 *		   Add exception catching for error handling.
 * \author Li Xiang
 * \date   June 4 2024

 *********************************************************************/

#include "Login.hpp"

import <string>;
import <print>;
import <exception>;

#ifdef _WIN32
#include<Windows.h>
 // windows poewrshell for GBK(936) coding
static void SetEncode(int Encode = 936) {
	SetConsoleCP(Encode);// set input
	SetConsoleOutputCP(Encode);// set output
}
#endif

/// custom exception
struct LoginFlag_Error :std::exception {
	const char* what() const noexcept override { return "Error Optional Flag"; }
};

int main(int argc, char* argv[]) {
	using namespace SQL;

#ifdef _WIN32
	SetEncode();
#endif

	int login_flag{};
	do {
		login_flag = Login::checkLogin();
	} while (!login_flag);

	try {
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
			throw LoginFlag_Error();
		}
	}
	catch (LoginFlag_Error& e) {
		std::println("Excepection called : {}", e.what());
	}
	catch (...) {
		std::println("Unknown exception");
	}
}