/*****************************************************************//**
 * \file   sql_Tools.hpp
 * \brief  When I try to think about these APIs ,the first I must know
 *		   is use these RAII design ideas.
 *	       remove interface	`selectCount`
 *
 * \author Li Xiang
 * \date   June 4 2024

 *********************************************************************/
#pragma once

import<string>;

namespace SQL
{
	/**
	 * \brief class DataBaseTools append some functions to deal with SQL sentences.
	 */
	class DataBaseTools {
	public:

		/**
		 * \brief RAII -> get resources.
		 *
		 */
		DataBaseTools();

		/**
		 * \brief the function is connect MySQL DataBase and it's a static function.
		 * \return boolean
		 */
		static bool connectDataBase();

		/**
		 * \brief choose database to use.
		 *
		 * \param db_name -> string
		 */
		static void useDataBase(const std::string& db_name);

		/**
		 * \brief select and show table employee's message.
		 */
		void selectEmployee();

		/**
		 * \brief select and show table salary_record's message.
		 */
		void selectSalaryRecord();

		DataBaseTools(const DataBaseTools&) = delete;
		DataBaseTools operator=(const DataBaseTools&) = delete;

		/**
		 *  freeHandle -> void
		 */
		static void freeHandle();

		/**
		 * \brief RAII -> free handles.
		 *
		 */
		~DataBaseTools();
		/**
		 * \brief The function of this function is similar to a trigger that update Actual_Sarlary.
		 *
		 */
		void updateActualSalary();

		/**
		 * \brief The function can clear the actual_salary that should not be exist.
		 *
		 */
		void clearErrorSalary();
	private:
		/**
		 * \brief TODO SQL sentence.
		 */
		void sqlExecute(const std::string& content);
	};
}