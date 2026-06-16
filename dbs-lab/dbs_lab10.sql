-- Row Triggers
-- 1. Based on the University database Schema in Lab 2, write a row trigger that records along with the time any change made in the Takes table into log_change_Takes table.

create or replace trigger log_takes_insert_update
after insert  on takes
for each row
begin
case
	when inserting then
	insert into log_change_takes values(current_date,:NEW.ID,:NEW.course_id,:NEW.sec_id,:NEW.semester,:NEW.year,:NEW.grade);
	when updating then
	insert into log_change_takes values(current_date,:NEW.ID,:NEW.course_id,:NEW.sec_id,:NEW.semester,:NEW.year,:NEW.grade);
end case;
end;
/

create or replace trigger log_takes_update_delete
before update or delete on takes
for each row
begin
	case
	when updating then
	insert into log_change_takes values(current_date,:OLD.ID,:OLD.course_id,:OLD.sec_id,:OLD.semester,:OLD.year,:OLD.grade);
	when deleting then
	insert into log_change_takes values(current_date,:OLD.ID,:OLD.course_id,:OLD.sec_id,:OLD.semester,:OLD.year,:OLD.grade);
end case;
end;
/

__________________________________________________________________________________

-- 2. Based on the University database schema in Lab 2, write a row trigger to insert existing values of Instructor into Old_Data_Instructor when salary is updated.

create or replace trigger log_instructor_salary_update
before update of salary on instructor
for each row
begin
	insert into old_data_instructor values(:OLD.ID,:OLD.name,:OLD.dept_name,:OLD.salary);
end;
/

__________________________________________________________________________________

-- Database Triggers
-- 3. Based on the University Schema, write a database trigger on Instructor that validates name, salary, and department budget constraints.

create or replace trigger log_instructor_check
before insert or update of salary on instructor
for each row
declare
sal instructor.salary%TYPE;
budg department.budget%TYPE;
begin
	IF LENGTH(TRIM(TRANSLATE(:NEW.name, 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ', ' '))) > 0 then
		RAISE_APPLICATION_ERROR(-20100,'Name must contain only alphabets');
ELSE
    IF :NEW.salary < 1 THEN
        RAISE_APPLICATION_ERROR(-20100,'Salary must be greater than 0');
    ELSE
        SELECT SUM(salary) INTO sal FROM instructor WHERE dept_name = :NEW.dept_name;
        SELECT budget INTO budg FROM department WHERE dept_name = :NEW.dept_name;
        IF sal + :NEW.salary > budg THEN
            RAISE_APPLICATION_ERROR(-20100,'Not enough department budget');
        END IF;
    END IF;
END IF;
end;
/

__________________________________________________________________________________

-- 4. Create a transparent audit system for Client_master table to log delete or update operations into auditclient table.

create or replace trigger log_client
before update or delete on client_master
for each row
begin
	case
	when updating then
	insert into auditclient values(:OLD.client_no,:OLD.name,:OLD.bal_due,'UPDATE',1,current_date);
	when deleting then
	insert into auditclient values(:OLD.client_no,:OLD.name,:OLD.bal_due,'DELETE',1,current_date);
	end case;
end;
/

__________________________________________________________________________________

-- 5. Instead of Trigger: Create view Advisor_Student and delete corresponding Advisor entries.

Create or replace trigger advisor_delete
INSTEAD OF DELETE on Advisor_Student
FOR EACH ROW
BEGIN
delete from advisor where s_id= :OLD.s_id and i_id= :OLD.i_id;
END;
/