## MarkDown File
###  数据库关系模式设计

<b>1.初始的关系模式
*R1 员工(Employee)*, <br>
( <br>
&emsp;  员工编号(emp_id), <br>
&emsp;	姓名(name), <br>
&emsp;	性别(sex), <br>
&emsp;	年龄(age), <br>
&emsp;	科室(department), <br>
&emsp;	职位(position)<br>
) <br>

*R2 工资(Salary)*<br>
( <br>
&emsp;  工资编号(salary_id), <br>
&emsp;  员工编号(emp_id), <br>
&emsp;  基本工资(basic_salary), <br>
&emsp;  福利补贴(welfare_salary), <br>
&emsp;  奖励工资(reward_salary), <br>
&emsp;  扣除奖金(unemp_insurance), <br>
&emsp;  实发工资(actual_salary), <br>
&emsp;  发放日期(pay_date)<br>
)
<br><br>
*2.第三范式(3NF)优化*<br>
*R1 Employee*<br>
&emsp; emp_id (Prime Key)<br>
&emsp; name<br>
&emsp; sex<br>
&emsp; age<br>
&emsp; position (Foreign Key reference by R3 PK)<br>
&emsp; department (Foreign Key reference by R4 PK)<br>
&emsp; basic_salary<br>
&emsp; weflare_subsidy<br>
&emsp; reward_salary<br>
&emsp; unemp_insurance<br>
&emsp; housing_fund<br>

*R2 SalaryRecord*
&emsp; sal_id (Prime Key) -> auto increase id<br>
&emsp; emp_id (Prime Key)<br>
&emsp; actual_salary (rely to R1 attribute)<br>
&emsp; pay_date<br>

*R3 Position_Tab*<br>
&emsp; pos_name (Prime Key) -> append concept to R1 (pos_name)<br>

*R4 Department_Tab*<br>
&emsp; dep_name (Prime Key) -> append concept to R1 (department)<br>

*R5 User*<br>
&emsp; user_name (Prime Key)<br>
&emsp; password<br>