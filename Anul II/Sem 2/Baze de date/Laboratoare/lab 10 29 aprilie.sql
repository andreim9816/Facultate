--lab 6
-- ex 11

SELECT *
FROM works_on
ORDER BY 1,2;

SELECT * 
FROM projects;

SELECT last_name, employee_id
FROM employees e
WHERE NOT EXISTS(SELECT '*'
                 FROM projects p
                 WHERE project_manager = 102 AND
                 NOT EXISTS (SELECT 1
                             FROM works_on
                             WHERE employee_id = e.employee_id
                             AND project_id = p.project_id
                             )
                 );
                 
-- ex 12

SELECT last_name, employee_id
FROM employees e
WHERE e.employee_id <> 200 AND NOT EXISTS(SELECT 1
                                         FROM works_on w
                                         WHERE employee_id = 200
                                         AND NOT EXISTS(SELECT 1
                                                        FROM works_on
                                                        WHERE employee_id = e.employee_id AND project_id = w.project_id
                                                        )
                                         );                

-- b)                                            
-- varianta 4

SELECT DISTINCT e.last_name, e.employee_id
FROM employees e
JOIN works_on aux ON(aux.employee_id = e.employee_id)
WHERE e.employee_id <> 200 AND NOT EXISTS(SELECT project_id
                                          FROM works_on w
                                          WHERE e.employee_id = employee_id
                                          
                                          MINUS
                                          
                                          SELECT project_id
                                          FROM works_on w1
                                          WHERE employee_id = 200
                                           ); 
                                            
-- ex 13 
SELECT last_name, employee_id
FROM employees e
WHERE e.employee_id <> 200 AND NOT EXISTS(SELECT 1
                                         FROM works_on w
                                         WHERE employee_id = 200
                                         AND NOT EXISTS(SELECT 1
                                                        FROM works_on
                                                        WHERE employee_id = e.employee_id AND project_id = w.project_id
                                                        )
                                        )
                            AND NOT EXISTS(SELECT project_id
                              FROM works_on w
                              WHERE e.employee_id = employee_id
                              
                              MINUS
                              
                              SELECT project_id
                              FROM works_on w1
                              WHERE employee_id = 200
                               ); 
                               
-- ex 14

desc job_grades

select *
FROM job_grades;

SELECT last_name, employee_id, salary, grade_level
FROM employees
CROSS JOIN job_grades
WHERE salary BETWEEN LOWEST_SAL AND highest_sal;

-- ex 15

SELECT employee_id, last_name, salary, department_id
FROM employees WHERE employee_id = &p_cod;

DEFINE p_cod -- Ce efect are?
SELECT employee_id, last_name, salary, department_id
FROM employees WHERE employee_id = &p_cod;
UNDEFINE p_cod

DEFINE p_cod = 100
SELECT employee_id, last_name, salary, department_id
FROM employees WHERE employee_id = &p_cod;
UNDEFINE p_cod

ACCEPT p_cod PROMPT "cod= "
SELECT employee_id, last_name, salary, department_id
FROM employees WHERE employee_id = &p_cod;

-- ex 16

ACCEPT p_jobId PROMPT "job_id= "
SELECT employee_id, department_id, last_name, salary * 12
FROM employees
WHERE UPPER(job_id) = '&p_jobId';

-- ex 17
ACCEPT p_date PROMPT "data ="
SELECT employee_id, department_id, last_name, salary * 12
FROM employees
WHERE HIRE_DATE >= TO_DATE('&p_date', 'DD-MM-YYYY');
UNDEFINE p_date

-- ex 18

SELECT *
FROM (SELECT &&p_coloana
      FROM &p_tabel
      ORDER BY &p_coloana
      )
WHERE ROWNUM <= 5;

-- ex 19

ACCEPT p_date1 PROMPT "data1 ="
ACCEPT p_date2 PROMPT "data2 ="
SELECT last_name || ', ' || job_id "Angajati", hire_date
FROM employees
WHERE HIRE_DATE BETWEEN TO_DATE('&p_date1', 'MM/DD/YY') AND TO_DATE('&p_date2', 'MM/DD/YY');

-- ex 20 TEMA! (folositi CITY)

SELECT last_name, job_id, salary, department_name
FROM employees
JOIN departments USING(department_id)
JOIN locations USING(location_id)
WHERE city = '&p_city_name';

-- ex 21

UNDEFINE p_date1
UNDEFINE p_date2

ACCEPT p_date1 PROMPT "data1 ="
ACCEPT p_date2 PROMPT "data2 ="
SELECT TO_DATE('&p_date1', 'MM/DD/YY') + ROWNUM -1
FROM DUAL
CONNECT BY ROWNUM < TO_DATE('&p_date2', 'MM/DD/YY') - TO_DATE('&p_date1', 'MM/DD/YY') + 1;

-- b) TEMA!!

-- LABORATOR 7

CREATE TABLE emp_ama AS SELECT * FROM EMPLOYEES;
CREATE TABLE dept_ama AS SELECT * FROM departments;

desc emp_ama
desc employees
desc dept_ama

SELECT *
FROM user_constraints 
WHERE UPPER(table_name) LIKE ('EMP_%')
ORDER BY table_name;

-- ex 3 datele sunt identice, structura tabelelor nu e la fel
SELECT * 
FROM emp_ama;

-- ex 4
ALTER TABLE emp_ama
ADD CONSTRAINT pk_emp_ama PRIMARY KEY(employee_id);

ALTER TABLE dept_ama
ADD CONSTRAINT pk_dept_ama PRIMARY KEY(department_id);

ALTER TABLE emp_ama
ADD CONSTRAINT fk_emp_ama FOREIGN KEY(department_id) REFERENCES dept_ama(department_id);

-- ex 5

INSERT INTO DEPT_ama -- eroare not enough values
VALUES (300, 'Programare');

INSERT INTO DEPT_ama (department_id, department_name)
VALUES (300, 'Programare');

INSERT INTO DEPT_ama (department_name, department_id) -- eroare semantica diferita 
VALUES (300, 'Programare');

INSERT INTO DEPT_ama (department_id, department_name, location_id) -- unique constraint (GRUPA44.PK_DEPT_AMA) violated
VALUES (300, 'Programare', null); -- inserez din nou cu aceeasi primary key

INSERT INTO DEPT_ama (department_name, location_id) -- cannot insert NULL into primary key field
VALUES ('Programare', null);

-- ex 6

select *
FROM dept_ama;

INSERT INTO emp_ama(employee_id, last_name, department_id, job_id, hire_date, email)
VALUES (EMPLOYEES_SEQ.nextval, 'Manolache', 300, 'IT_PROG', SYSDATE, 'andrei@yahoo.com');

select *
FROM emp_ama;

COMMIT;

-- tema pana la 10!