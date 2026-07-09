-- 1. Retrieve birth date and address of employee ‘John B. Smith’
select Bdate, Address
from employee1
where Fname = 'John'
  and Minit = 'B'
  and Lname = 'Smith';

/* Retrieve name and address of all employees who work for the ‘Research’ department */
select E.Fname, E.Lname, E.Address
from employee1 E
join department1 D on E.Dno = D.Dnumber
where D.Dname = 'Research';

/* 2. For every project located in ‘Stanford’, list project number, controlling department number, and manager details */
select 
    P.Pnumber as Project_Number,
    P.Dnum as Controlling_Dept_Number,
    E.Lname as Manager_Last_Name,
    E.Address as Manager_Address,
    E.Bdate as Manager_Birth_Date
from project P
join department1 D on P.Dnum = D.Dnumber
join employee1 E on D.Mgr_ssn = E.Ssn
where P.Plocation = 'Stanford';

/* 3. For each employee, retrieve employee name and their supervisor’s name */
select 
    E.Fname as Employee_First_Name,
    E.Lname as Employee_Last_Name,
    S.Fname as Supervisor_First_Name,
    S.Lname as Supervisor_Last_Name
from employee1 E
left join employee1 S on E.Super_ssn = S.Ssn;

/* 4. List project numbers involving employees named ‘Smith’ (worker or department manager) */
select distinct
    P.Pnumber as Project_Number
from project P
join works_on W on P.Pnumber = W.Pno
join employee1 E on W.Essn = E.Ssn
join department1 D on P.Dnum = D.Dnumber
left join employee1 M on D.Mgr_ssn = M.Ssn
where E.Lname = 'Smith'
   or M.Lname = 'Smith';

/* 5. Apply 10% raise to employees working on ‘ProductX’ */
update employee1
set Salary = Salary * 1.1
where Ssn in (
    select W.Essn
    from works_on W
    join project P on W.Pno = P.Pnumber
    where P.Pname = 'ProductX'
);

/* 6. List employees and projects they work on, ordered by department, last name, first name */
select 
    E.Fname as Employee_First_Name,
    E.Lname as Employee_Last_Name,
    P.Pname as Project_Name,
    D.Dname as Department_Name
from employee1 E
join department1 D on E.Dno = D.Dnumber
left join works_on W on E.Ssn = W.Essn
left join project P on W.Pno = P.Pnumber
order by D.Dname, E.Lname, E.Fname;

/* 7. Employees whose dependent has same name and sex as them */
select distinct
    E.Fname as Employee_First_Name,
    E.Lname as Employee_Last_Name
from employee1 E
join dependent D on E.Ssn = D.Essn
where D.Dependent_name = E.Fname
  and D.Sex = E.Sex;

/* 8. Employees with no dependents */
select 
    E.Fname as Employee_First_Name,
    E.Lname as Employee_Last_Name
from employee1 E
left join dependent D on E.Ssn = D.Essn
where D.Essn is null;