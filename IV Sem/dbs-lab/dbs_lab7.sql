set serveroutput on

-- Use a table StudentTable(RollNo, GPA) and populate the table with {(1, 5.8); (2, 6.5); (3, 3.4); (4,7.8); (5, 9.5)} unless a different DB schema is explicitly specified.

create table studenttable(rollno integer, gpa number(2,1));

insert into studenttable (rollno, gpa) values (1,5.8);
insert into studenttable (rollno, gpa) values (2,6.5);
insert into studenttable (rollno, gpa) values (3,3.4);
insert into studenttable (rollno, gpa) values (4,7.8);
insert into studenttable (rollno, gpa) values (5,9.5);

/* 1. Write a PL/SQL block to display the GPA of given student. */

declare
srollno studenttable.rollno%type;
sgpa studenttable.gpa%type;
rno int;
begin
rno := &enter;
select rollno into srollno from studenttable where rollno = rno;
select gpa into sgpa from studenttable where rollno = rno;
dbms_output.put_line('rollno:' || to_char(srollno));
dbms_output.put_line('gpa: ' || to_char(sgpa));
dbms_output.put_line('worked');
end;
/

/* 2. Write a PL/SQL block to display the letter grade(0-4: F; 4-5: E; 5-6: D; 6-7: C; 
7-8: B; 8-9: A; 9-10: A+} of given student. */

declare
sgpa studenttable.gpa%type;
grade char(1);
input number(2,1);
begin
input := '&enter';
if input>0 and input<4 then
dbms_output.put_line('F');
elsif input>4 and input<5 then
dbms_output.put_line('E');
elsif input>5 and input<6 then
dbms_output.put_line('D');
elsif input>6 and input<7 then
dbms_output.put_line('C');
elsif input>7 and input<8 then
dbms_output.put_line('B');
elsif input>8 and input<9 then
dbms_output.put_line('A');
elsif input>9 and input<10 then
dbms_output.put_line('A+');
else
dbms_output.put_line('no such gpa');
end if;
end;
/

/* 3. Input the date of issue and date of return for a book. Calculate and display the fine 
with the appropriate message using a PL/SQL block. The fine is charged as per 
the table 8.1: */

declare
doi int;
dor int;
late int;
begin
late := '&enter';
if input=7 then
dbms_output.put_line('NIL');
elsif input>8 and input<15 then
dbms_output.put_line('Rs.1/day');
elsif input>5 and input<6 then
dbms_output.put_line('D');
elsif input>6 and input<7 then
dbms_output.put_line('C');
elsif input>7 and input<8 then
dbms_output.put_line('B');
elsif input>8 and input<9 then
dbms_output.put_line('A');
elsif input>9 and input<10 then
dbms_output.put_line('A+');
else
dbms_output.put_line('no such gpa');
end if;
end;
/