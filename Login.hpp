/*****************************************************************//**
 * \file   Login.hpp
 * \brief
 *		   For two user classes,  fill sql_Tools.cpp API whth twice of them.
 *		   Specially, RootUser need more permissions than RehularUser.
 *		   For class Login ,  design a static function to check login status.
 *
 * \brief  Add new concept (Foreign Key) for table employee (department_tab, position_tab).
 *         Add two public function 'addUser' 'deleteUser' in class RootUser.
 *		   Add new interface `Count` to class RootUser.
 * \author Li Xiang
 * \date   June 4 2024

 *********************************************************************/
#pragma once

#include "DataBaseTools.hpp"
#include <conio.h>

namespace SQL
{
	/**
	 * \brief class Login offer a static function to choose user .
	 */
	class Login {
	public:
		Login() = default;
		~Login();
		Login(Login const&) = delete;
		Login operator=(Login const&) = delete;

		/**
		 * \brief the function .
		 *
		 * \return user attribute flag
		 * \return 0 => Login Failed
		 * \return 1 => Root User
		 * \return 2 => Regular User
		 */
		static int checkLogin();
	};

	/**
	 * \brief RootUser has the permissions of delete records
	 */
	class RootUser :public DataBaseTools {
	public:
		RootUser() :DataBaseTools() {}
		void deleteEmployee();
		void menuOption();

		/**
		 * \brief a function that insert 11 datas in table Employee.
		 */
		void insertEmployee();

		/**
		 * \brief a fuction that insert salary_record.
		 */
		void insertSalaryRecord();

		/**
		 * \brief count for custom condition in all tables.
		 *
		 */
		void selectCount();

		void addUser();

		void deleteUser();
	};

	/**
	 * \brief Regular's delete permissions are limited.
	 */
	class RegularUser :public DataBaseTools {
	public:
		RegularUser() :DataBaseTools() {}
		void menuOption();
	};
}