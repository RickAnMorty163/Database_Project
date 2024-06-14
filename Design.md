## MarkDown File
###  数据库关系模式设计

<b>1.初始的关系模式
*R1 员工(Employee)*
( 
&emsp;  员工编号(emp_id), 
&emsp;	姓名(name), 
&emsp;	性别(sex),
&emsp;	年龄(age),
&emsp;	科室(department),
&emsp;	职位(position)
) 

*R2 工资(Salary)*
( 
&emsp;  工资编号(salary_id),
&emsp;  员工编号(emp_id),
&emsp;  基本工资(basic_salary),
&emsp;  福利补贴(welfare_salary),
&emsp;  奖励工资(reward_salary),
&emsp;  扣除奖金(unemp_insurance),
&emsp;  实发工资(actual_salary),
&emsp;  发放日期(pay_date)
)
<br><br>
*2.第三范式(3NF)优化*
*R1 Employee*
&emsp; emp_id (Prime Key)
&emsp; name
&emsp; sex
&emsp; age
&emsp; position (Foreign Key reference by R3 PK)
&emsp; department (Foreign Key reference by R4 PK)
&emsp; basic_salary
&emsp; weflare_subsidy
&emsp; reward_salary
&emsp; unemp_insurance
&emsp; housing_fund

*R2 SalaryRecord*
&emsp; sal_id (Prime Key) -> auto increase id
&emsp; emp_id (Prime Key)
&emsp; actual_salary (rely to R1 attribute)
&emsp; pay_date

*R3 Position_Tab*
&emsp; pos_name (Prime Key) -> append concept to R1 (pos_name)

*R4 Department_Tab*
&emsp; dep_name (Prime Key) -> append concept to R1 (department)

*R5 User*
&emsp; user_name (Prime Key)
&emsp; password