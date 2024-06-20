/*****************************************************************//**
 * \file   sql_Tools.cpp
 * \brief  realize SQL operator for ODBC
 * \brief  add new function to match right date format for line 83
 *		   add new function	`clearErrorSalary` to check where actual_salary > 3000
 *		   add fetch to funtion `insertEmployee`
 *         move function `insertEmployee` `insertSalaryRecord` to file Login.cpp -> class RootUser
 * \author Li Xiang
 * \date   June 4 2024

 *********************************************************************/
#include"DataBaseTools.hpp"
#include <mysql.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
import <iostream>;
import <iomanip>;
import <print>;
import <regex>;

namespace SQL
{
	extern SQLRETURN ret = NULL;// return message
	extern SQLHENV henv = NULL;// environment handle
	extern SQLHDBC hdbc = NULL;// connect handle
	extern SQLHSTMT hstmt = NULL;// sentence handles

	DataBaseTools::DataBaseTools() {
		connectDataBase();
	}

	bool DataBaseTools::connectDataBase() {
		SQLAllocHandle(SQL_HANDLE_ENV, nullptr, &henv);// request environment
		SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);// set environment
		SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);// request database connect

		ret = SQLConnect(hdbc, (SQLCHAR*)("mysql"), SQL_NTS, (SQLCHAR*)(""), SQL_NTS, (SQLCHAR*)(""), SQL_NTS);

		return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) ? true : false;
	}

	void DataBaseTools::useDataBase(const std::string& db_name) {
		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);// request handle
		std::string content = "use " + db_name;// sql sentence to choose database
		ret = SQLExecDirect(hstmt, (SQLCHAR*)(content.c_str()), SQL_NTS);// retire sql sentence
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			std::cout << content << '\n';
		else
			std::cout << "falied\n";
	}

	void DataBaseTools::selectEmployee() {
		updateActualSalary();

		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

		std::string content = "select * from employee where ";
		std::string temp_str;
		std::println("please input >> select condition\n");
		std::getline(std::cin, temp_str);
		content += temp_str;

		ret = SQLExecDirect(hstmt, (SQLCHAR*)(content.c_str()), SQL_NTS);

		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			std::println("\nselect employee successful ");

			SQLCHAR str1[10]{}, str2[20]{}, str3[10]{}, str4[10]{}, str5[10]{}, str6[10]{}, str7[10]{},
				str8[10]{}, str9[10]{}, str10[10]{}, str11[10]{};
			SQLLEN in1{}, in2{}, in3{}, in4{}, in5{}, in6{}, in7{}, in8{}, in9{}, in10{}, in11{};
			while (SQLFetch(hstmt) == SQL_SUCCESS) {
				SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 10, &in1);
				SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 20, &in2);
				SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 10, &in3);
				SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 10, &in4);
				SQLGetData(hstmt, 5, SQL_C_CHAR, str5, 10, &in5);
				SQLGetData(hstmt, 6, SQL_C_CHAR, str6, 10, &in6);
				SQLGetData(hstmt, 7, SQL_C_CHAR, str7, 10, &in7);
				SQLGetData(hstmt, 8, SQL_C_CHAR, str8, 10, &in8);
				SQLGetData(hstmt, 9, SQL_C_CHAR, str9, 10, &in9);
				SQLGetData(hstmt, 10, SQL_C_CHAR, str10, 10, &in10);
				SQLGetData(hstmt, 11, SQL_C_CHAR, str11, 10, &in11);
				std::cout
					<< "emp_id:          |" << std::setw(11) << std::setiosflags(std::ios::left) << str1 << "|\n"
					<< "name:            |" << std::setw(11) << std::setiosflags(std::ios::left) << str2 << "|\n"
					<< "sex:             |" << std::setw(11) << std::setiosflags(std::ios::left) << str3 << "|\n"
					<< "age:             |" << std::setw(11) << std::setiosflags(std::ios::left) << str4 << "|\n"
					<< "position:        |" << std::setw(11) << std::setiosflags(std::ios::left) << str5 << "|\n"
					<< "department:      |" << std::setw(11) << std::setiosflags(std::ios::left) << str6 << "|\n"
					<< "basic_salary:    |" << std::setw(11) << std::setiosflags(std::ios::left) << str7 << "|\n"
					<< "welfare_subsidy: |" << std::setw(11) << std::setiosflags(std::ios::left) << str8 << "|\n"
					<< "reward_salary:   |" << std::setw(11) << std::setiosflags(std::ios::left) << str9 << "|\n"
					<< "unemp_insurance: |" << std::setw(11) << std::setiosflags(std::ios::left) << str10 << "|\n"
					<< "housing_fund:    |" << std::setw(11) << std::setiosflags(std::ios::left) << str11 << "|\n";
				std::cout << "\n";
			}
		}
		else
			std::cerr << "select emoloyee failed\n";

		updateActualSalary();
	}

	void DataBaseTools::selectSalaryRecord() {
		updateActualSalary();

		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		std::string content = "select * from salary_record where ";
		std::string temp_str;
		std::println("please input >> select condition\n");
		std::getline(std::cin, temp_str);
		content += temp_str;

		ret = SQLExecDirect(hstmt, (SQLCHAR*)(content.c_str()), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			std::println("select salary_record successful");

			SQLCHAR str1[10]{}, str2[10]{}, str3[10]{}, str4[11]{};
			SQLLEN in1{}, in2{}, in3{}, in4{};
			while (SQLFetch(hstmt) == SQL_SUCCESS) {
				SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 10, &in1);
				SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 10, &in2);
				SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 10, &in3);
				SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 11, &in4);
				std::cout
					<< "sal_id:        |" << std::setw(5) << std::setiosflags(std::ios::left) << str1 << "|\n"
					<< "emp_id:        |" << std::setw(5) << std::setiosflags(std::ios::left) << str2 << "|\n"
					<< "actual_salary: |" << std::setw(5) << std::setiosflags(std::ios::left) << str3 << "|\n"
					<< "pay_data:      |" << std::setw(5) << std::setiosflags(std::ios::left) << str4 << "|\n";
				std::cout << "\n";
			}
		}
		else
			std::cerr << "select salary_record failed\n";
	}

	void DataBaseTools::freeHandle() {
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
		SQLDisconnect(hdbc);
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
	}

	DataBaseTools::~DataBaseTools() {
		this->freeHandle();
	}

	void DataBaseTools::sqlExecute(const std::string& content) {
		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		ret = SQLExecDirect(hstmt, (SQLCHAR*)(content.c_str()), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			std::cout << content << " successful" << '\n';
		else
			std::cerr << "failed\n";
	}

	void DataBaseTools::updateActualSalary() {
		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

		std::string content1 = "UPDATE salary_record ";
		std::string content2 = "INNER JOIN employee ON salary_record.emp_id = employee.emp_id ";
		std::string content3 = "SET actual_salary = employee.basic_salary + employee.reward_salary + employee.welfare_subsidy - employee.unemp_insurance - employee.housing_fund";
		auto content = content1 + content2 + content3;
		ret = SQLExecDirect(hstmt, (SQLCHAR*)(content.c_str()), SQL_NTS);

		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			std::println("Now database data is update ");
		else
			std::println("Now database data is new ");
	}

	void DataBaseTools::clearErrorSalary() {
		// use select sentence to check error actual_salary data.
		ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		int rowCount = 0;
		ret = SQLExecDirect(hstmt, (SQLCHAR*)("select * from salary_record where actual_salary > 3000"), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
				rowCount++;
				ret = SQLFetch(hstmt);// get next row
			}
		}
		if (rowCount - 1) {
			ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
			std::println("There are wrong salary datas, which have been cleared.");
			ret = SQLExecDirect(hstmt, (SQLCHAR*)("delete from salary_record where actual_salary > 3000"), SQL_NTS);
		}
		else {
			std::cerr << "Insert check pass." << '\n';
		}
	}
}