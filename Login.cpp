/*****************************************************************//**
 * \file   Login.cpp
 * \brief
 * \brief  change std::regex to boost::regex , because of the std::regex efficiency questions
 *
 * \author Li Xiang
 * \date   June 10 2024

 *********************************************************************/
#include "Login.hpp"
#include <boost/regex.hpp>
#include <mysql.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

import <print>;
import <iostream>;
import <chrono>;

namespace SQL
{
	static void sleepAndClearTerminal() {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		system("cls");
	}

	extern SQLRETURN ret;// return message
	extern SQLHENV henv;// environment handle
	extern SQLHDBC hdbc;// connect handle
	extern SQLHSTMT hstmt;// sentence handles

	Login::~Login() {
		DataBaseTools::freeHandle();
	}

	int Login::checkLogin() {
		if (!DataBaseTools::connectDataBase()) {
			std::println("database init failed");
			return 0;
		}

		std::string content0 = "sql_zero";
		DataBaseTools::useDataBase(content0);

		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

		// get user name
		std::string user_name;
		std::println("Please input >> user_name ");
		std::getline(std::cin, user_name);

		// get user password
		char password[20]{};// set string buffer = 20
		int i{};
		std::println("Please input >> password");
		while ((password[i] = _getch()) != 13) { // 13 -> Enter
			if (password[i] == 8) { // 8->BackSpace
				if (i > 0) {
					i--;
					std::cout << "\b \b"; // remove one char and back
				}
			}
			else {
				i++;
				std::cout << '*';
			}
		}
		password[i] = '\0'; // add end flag
		std::string password_org(password);// use C style string to construct wstirng object

		std::string content1 = "select * from user where user_name= '";
		std::string content2 = "' AND ";
		std::string content3 = "password = ";
		std::string content = content1 + user_name + content2 + content3 + password_org;

		int rowCount = 0;
		if (user_name.empty() || password_org.empty()) {
			std::cerr << "\nlogin failed" << '\n' << '\n';
			return 0;
		}

		ret = SQLExecDirect(hstmt, (SQLCHAR*)(content.c_str()), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
				rowCount++;
				ret = SQLFetch(hstmt);// get next row
			}
		}

		if (rowCount - 1 && rowCount != 0) {
			std::println("\nlogin successful");
			if (user_name == "root") { std::println("root user >> \n"); return 1; }
			else {
				std::cout << "regular user >> " + user_name << '\n'; return 2;
			}
		}
		else {
			std::cerr << "\nlogin failed" << '\n' << '\n';
			return 0;
		}
	}
	void RootUser::deleteEmployee() {
		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

		std::string content = "delete from employee where emp_id = ";
		std::string temp_str;
		std::println("Please input >> delete employee id");

		std::getline(std::cin, temp_str);
		content += temp_str;

		ret = SQLExecDirect(hstmt, (SQLCHAR*)(content.c_str()), SQL_NTS);

		std::cout << content << '\n';
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			std::cout << "delete id " << temp_str << " employee successful" << '\n';
		else
			std::cerr << "delete id " << temp_str << " employee failed" << '\n';
	}

	void RootUser::menuOption() {
		boost::regex parttern(R"(^[0-8]$)");
		std::string option{};
		do {
			std::println("Root User >>");
			std::println("1 -> Select Employee       ");
			std::println("2 -> Select SalaryRecord   ");
			std::println("3 -> Insert Employee       ");
			std::println("4 -> Insert SalaryRecord   ");
			std::println("5 -> Count  Employee/Salary");
			std::println("6 -> Delete employee       ");
			std::println("7 -> Add    User           ");
			std::println("8 -> Delete User           ");
			std::println("0 -> Exit                  ");

			std::print("Please one option >> ");
			while (true) {
				std::getline(std::cin, option);
				if (boost::regex_search(option.begin(), option.end(), parttern))
					break;
				else std::cerr << "Wrong option \n";
			}

			sleepAndClearTerminal();
			std::println("");
			int op = std::stoi(option);
			switch (op) {
			case 1:
				selectEmployee();
				break;
			case 2:
				selectSalaryRecord();
				break;
			case 3:
				insertEmployee();
				break;
			case 4:
				insertSalaryRecord();
				break;
			case 5:
				selectCount();
				break;
			case 6:
				deleteEmployee();
				break;
			case 7:
				addUser();
				break;
			case 8:
				deleteUser();
				break;
			case 0:
				std::cout << "Exit\n";
				break;
			default:
				std::cerr << "Unknown option" << '\n';
			}
		} while (option != "0");
	}

	void RootUser::insertEmployee() {
		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		std::string content;

		std::cout
			<< "please input >>\n"
			<< " emp_id, name(string), sex(string), age \n"
			<< " position   (1-技术人员 2-管理人员 3-财务人员 4-销售人员) \n"
			<< " department (1-技术科  2-经理室  3-财务科  4-销售科 ) \n"
			<< " basic_salary,  welfare_subsidy \n"
			<< " reward_salary, unemp_insurance, housing_fund \n";

		int count{ 11 };
		std::string temp_str;
		int transCheckInt{};

		/**
		 * \brief Lambda Function to choose right department.
		 * \return boolean flag
		 */
		auto choosePostion = [&]()->bool {
			transCheckInt = std::stoi(temp_str);
			switch (transCheckInt) {
			case 1: { content += " '技术人员' ,";  return true; }
			case 2: { content += " '管理人员' ,";  return true; }
			case 3: { content += " '财务人员' ,";  return true; }
			case 4: { content += " '销售人员' ,";  return true; }
			default: { std::cerr << "wrong option\n";  return false; }
			}
			};

		/**
		 * \brief Lambda Function to choose right department.
		 * \return boolean flag
		 */
		auto chooseDepartment = [&]()->bool {
			transCheckInt = std::stoi(temp_str);
			switch (transCheckInt) {
			case 1: { content += " '技术科' ,";  return true; }
			case 2: { content += " '经理室' ,";  return true; }
			case 3: { content += " '财务科' ,";  return true; }
			case 4: { content += " '销售科' ,";  return true; }
			default: { std::cerr << "wrong option\n"; return false; }
			}
			};

		while (count--) {
			std::getline(std::cin, temp_str);
			if (count == 6) {
				while (!choosePostion()) { std::getline(std::cin, temp_str); };
				continue;
			}

			if (count == 5) {
				while (!chooseDepartment()) { std::getline(std::cin, temp_str); };
				continue;
			}
			content += (temp_str + ",");// add sign comma to divide token
		}
		content.pop_back();// remove last comma that unused
		content = "insert into employee values (" + content + ")";

		ret = SQLExecDirect(hstmt, (SQLCHAR*)(content.c_str()), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			std::cout << content << " successful" << '\n';
		else
			std::cerr << "failed\n";
	}

	void RootUser::insertSalaryRecord() {
		updateActualSalary();
		clearErrorSalary();
		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

		std::string content, temp_str;
		std::println("please input >> employee's id");
		std::getline(std::cin, temp_str);
		content += (temp_str + ",");// add sign comma

		boost::regex parttern(R"('\d{4}-\d{2}-\d{2}')");
		while (true) {
			std::println(R"(please input >> pay_data (like"xxxx-xx-xx"))");
			std::getline(std::cin, temp_str);
			if (boost::regex_search(temp_str.begin(), temp_str.end(), parttern)) {
				content += temp_str;
				break;
			}
			else {
				std::println("match error , please input right format date ");
			}
		}
		content = "insert into salary_record (emp_id,pay_date) values (" + content + ")";

		ret = SQLExecDirect(hstmt, (SQLCHAR*)(content.c_str()), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			std::cout << "insert salary_record sucessful " << '\n';
		else
			std::cerr << "insert salary_record failed " << '\n';
		clearErrorSalary();
		updateActualSalary();
	}

	void RootUser::selectCount() {
		updateActualSalary();

		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

		std::string temp_str1;
		std::string temp_str2;

		std::println("Please input >> which table 1-employee 2-salary_record");
		while (true) {
			std::getline(std::cin, temp_str1);
			if (std::stoi(temp_str1) == 1) {
				temp_str1 = "employee"; break;
			}
			else if (std::stoi(temp_str1) == 2) {
				temp_str1 = "salary_record"; break;
			}
			else {
				std::cerr << "Please choose 1|2 \n";
			}
		}
		std::println("Please input >> count condition ");
		std::getline(std::cin, temp_str2);

		std::string content = "select count(*) from " + temp_str1 + " where " + temp_str2;
		ret = SQLExecDirect(hstmt, (SQLCHAR*)(content.c_str()), SQL_NTS);

		if (ret == SQL_SUCCESS || SQL_SUCCESS_WITH_INFO) {
			SQLCHAR str1[10]{};
			SQLLEN in1{};
			while (SQLFetch(hstmt) == SQL_SUCCESS) {
				SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 10, &in1);
				std::cout << "\ncount: "
					<< "|" << std::setw(6) << std::setiosflags(std::ios::left) << str1 << "|" << '\n';
				std::cout << "\n";
			}
		}
		else {
			std::cerr << "count failed" << 'n';
		}
	}

	void RootUser::addUser() {
		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

		std::string content = "insert into user values ";
		std::string user_name;

		//check user_name parttern
		boost::regex parttern(R"(^[a-zA-Z][a-zA-Z0-9_]*$)");
		while (true) {
			std::println("Please input >> User Name (Username cannot start with numbers) ");
			std::getline(std::cin, user_name);
			if (boost::regex_search(user_name.begin(), user_name.end(), parttern))
				break;
			else
				std::println("Error Parttern, Please Input right User Name");
		}

		//check password parttern
		parttern = R"(^[0-9a-zA-Z]+$)";
		std::string password_org, password_check;
		while (true) {
			// input password
			char password[20]{};
			int i{};
			std::println("Please input >> password (Password can not include special characters)");
			while ((password[i] = _getch()) != 13) { // 13 -> E
				if (password[i] == 8) { // 8->BackSpace
					if (i > 0) {
						i--;
						std::cout << "\b \b"; // remove one char and back
					}
				}
				else {
					i++;
					std::cout << '*';
				}
			}
			password[i] = '\0';

			password_org = password;
			if (boost::regex_search(password_org.begin(), password_org.end(), parttern)) {
				std::println("\nPlease check your input again >> ");
				std::getline(std::cin, password_check);
				if (password_org == password_check) {
					system("cls");
					break;
				}
				else {
					std::println("Check your password setting again");
					continue;
				}
			}
			else
				std::println("\nError Parttern, Please input right PassWord ");
		}
		std::println("");

		content += " ( '" + user_name + "', '" + password_org + "' )";
		ret = SQLExecDirect(hstmt, (SQLCHAR*)(content.c_str()), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			std::cout << "Insert User " << user_name << " successful \n";
		else
			std::cerr << "Insert User " << user_name << " failed \n";
	}

	void RootUser::deleteUser() {
		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

		std::string content = "delete from user where user_name = ";
		std::string temp_str;

		std::println("please input >> user_name ");
		std::getline(std::cin, temp_str);
		if (temp_str == "root") {
			std::cerr << "can not delete root user \n";
			return;
		}

		content += (" '" + temp_str + "' ");
		ret = SQLExecDirect(hstmt, (SQLCHAR*)(content.c_str()), SQL_NTS);

		if (SQL_SUCCESS || SQL_SUCCESS_WITH_INFO)
			std::cout << "delete user " << temp_str << " successful\n";
		else
			std::cerr << "delete user " << temp_str << " failed\n";
	}

	void RegularUser::menuOption() {
		boost::regex parttern(R"(^[0-2]$)");
		std::string option{};
		do {
			std::println("\nRegular User >>");
			std::println("1 -> Select Employee    ");
			std::println("2 -> Select SalaryRecord");
			std::println("0 -> Exit               ");

			std::print("Please input one option >> ");
			while (true) {
				std::getline(std::cin, option);
				if (boost::regex_search(option.begin(), option.end(), parttern))
					break;
				else std::cerr << "Wrong option \n";
			}

			sleepAndClearTerminal();
			std::println("");
			int op = std::stoi(option);
			switch (op) {
			case 1:
				selectEmployee();
				break;
			case 2:
				selectSalaryRecord();
				break;
			case 0:
				std::cout << "Exit\n";
				break;
			default:
				std::cerr << "Unknown option" << '\n';
			}
		} while (option != "0");
	}
}