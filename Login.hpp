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
	private:
		Login() = default;
	public:
		~Login() = default;

		/**
		 * \brief the function .
		 *
		 * \return user attribute flag
		 * \return 0 => Login Failed
		 * \return 1 => Root User
		 * \return 2 => Regular User
		 */
		static int checkLogin()noexcept;
	};

	/**
	 * \brief RootUser has the permissions of delete records
	 */
	class RootUser :public DataBaseTools {
	public:
		using DataBaseTools::DataBaseTools;

		void deleteEmployee()noexcept;

		void menuOption()noexcept;

		/**
		 * \brief a function that insert 11 datas in table Employee.
		 */
		void insertEmployee()noexcept;

		/**
		 * \brief a fuction that insert salary_record.
		 */
		void insertSalaryRecord()noexcept;

		/**
		 * \brief count for custom condition in all tables.
		 *
		 */
		void selectCount()noexcept;

		void addUser()noexcept;

		void deleteUser()noexcept;
	};

	/**
	 * \brief Regular's delete permissions are limited.
	 */
	class RegularUser :public DataBaseTools {
	public:
		using DataBaseTools::DataBaseTools;

		RegularUser() :DataBaseTools() {}
		void menuOption()noexcept;
	};
}