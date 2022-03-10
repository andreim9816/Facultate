-- lab 6
set serveroutput on;
set verify off;

create table info_dept_ama(id number, nume_dept varchar2(25), plati NUMBER);

insert into info_dept_ama
SELECT department_id, department_name, sum(salary)
FROM employees 
JOIN departments USING(department_id)
GROUP BY department_id, department_name;

select *from info_dept_ama;

ALTER TABLE info_dept_ama
ADD (numbar NUMBER);

UPDATE info_dept_ama d
SET numbar = (SELECT COUNT(employee_id)
             FROM employees
             WHERE department_id = d.id
             );
             
-- b) definiti un declansator .. 

CREATE OR REPLACE PROCEDURE actualizare_nr_ang(cod NUMBER, numar_ang NUMBER)
IS

BEGIN 
    UPDATE info_dept_ama
    SET numbar = numar_ang + numbar
    WHERE id = cod;
END;
/

CREATE TABLE info_emp_ama(id, nume, prenume, salariu, id_dept)
AS Select employee_id, last_name, first_name, salary, department_id
FROM employees;

CREATE OR REPLACE TRIGGER trig3
AFTER UPDATE OR DELETE OR INSERT ON info_emp_ama
FOR EACH ROW
BEGIN
    IF INSERTING 
        THEN actualizare_nr_ang(:NEW.id_dept, 1);
    ELSIF UPDATING('id_dept') 
        THEN
            actualizare_nr_ang(:OLD.id_dept, -1);
            actualizare_nr_ang(:NEW.id_dept,  1);
    ELSE 
        actualizare_nr_ang(:OLD.id_dept, -1);
    END IF;        
            
END;
/

UPDATE info_emp_ama
SET id_dept = 60
WHERE id = 100;

INSERT INTO info_emp_ama
VALUES(500, 'aaa', 'aa', 100000, 60);

select * from info_dept_ama;

DELETE from info_dept_ama
WHERE id = 500;

-- ex 4
CREATE OR REPLACE TRIGGER trig4
BEFORE INSERT OR UPDATE on emp_ama
FOR EACH ROW 
DECLARE
v_nr NUMBER;
    BEGIN
        SELECT COUNT(employee_id) INTO v_nr
        FROM emp_ama;
        
        IF v_nr > 45 THEN
            RAISE_APPLICATION_ERROR(-20001, 'Nu puteti insera mai mult de 45 de persoane!');
        END IF;    
    END;
/

SELECT COUNT(employee_id), department_id
FROM emp_ama
GROUP BY department_id;

INSERT INTO emp_ama 
VALUES(employees_seq.NEXTVAL, 'Prenume', 'Nume', 'a', 't', SYSDATE,'IT_PROG', 10000, 0.15, 2, 30);
