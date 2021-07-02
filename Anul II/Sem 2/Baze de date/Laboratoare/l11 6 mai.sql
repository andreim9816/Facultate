
-- 6 mai
-- lab sapt 11

desc emp_ama;
select * from emp_ama;

-- ex 6
INSERT INTO emp_ama
VALUES(EMPLOYEES_SEQ.nextval, NULL, 'ceva', 'ana@palmier.com', NULL, SYSDATE, 'jobul', NULL,NULL,NULL,NULL);
COMMIT;

-- ex 7
SELECT *
FROM dept_ama;

INSERT INTO dept_ama(department_id, department_name)
VALUES(300, 'PROGRAMARE');

INSERT INTO emp_ama(employee_id, last_name, hire_date, job_id, email, department_id)
VALUES(EMPLOYEES_SEQ.nextval, 'altceva', SYSDATE, 'alt job', 'mirela@gmail.com', 300);

-- ex 8

INSERT INTO EMP_AMA(employee_id, last_name, hire_date, job_id, email)
VALUES((SELECT MAX(EMPLOYEE_ID) + 1
        FROM emp_ama
        ), 'inna', SYSDATE, 'alt_job', 'mini@email');

-- var 2
INSERT INTO EMP_ama(employee_id, last_name, hire_date, job_id, email)
SELECT (SELECT MAX(employee_id) +1
        FROM emp_ama), 'inna', SYSDATE, 'alt_job', 'mini@email'
FROM DUAL;        

-- ex 9
CREATE TABLE empl_ama as SELECT * FROM EMPLOYEES WHERE 1 = -1;

INSERT INTO empl_ama
SELECT * FROM employees WHERE commission_pct > 0.25;

-- ex 10

/*
INSERT INTO emp_ama (employee_id, last_name, first_name, hire_date, job_id, email)
VALUES(0, USER, USER, SYSDATE,'TOTAL',... )
*/

-- ex 11
INSERT INTO emp_ama(employee_id, last_name, first_name, hire_date, job_id, email, salary)
VALUES (&p_cod, '&&p_nume', '&&p_prenume', SYSDATE, 'oarecare', substr('&p_prenume', 1, 1)|| substr('&p_nume', 1, 7), &p_salary);

-- ex 12
CREATE TABLE emp2_ama as SELECT * FROM employees WHERE 1 = -1;
CREATE TABLE emp3_ama as SELECT * FROM employees WHERE 1 = -1;

INSERT ALL
WHEN salary < 5000 THEN INTO emp1_ama
WHEN salary BETWEEN 5000 AND 10000 THEN INTO emp2_ama
ELSE INTO emp3_ama -- nu intra pe niciun WHEN
SELECT * FROM employees;


-- ex 13 TEMAAAA 

-- ex 14

UPDATE emp_ama
SET salary = salary * 1.05;
ROLLBACK;

-- ex 15

UPDATE emp_ama
SET job_id ='SA_REP'
WHERE department_id = 80;

-- ex 16
UPDATE dept_ama
SET manager_id = (SELECT employee_id
                  FROM emp_ama
                  WHERE lower(first_name)||' '||lower(last_name) ='douglas grant'
                  )
WHERE department_id = 20;

UPDATE emp_ama
SET salary = 1000 + salary
WHERE employee_id = (SELECT employee_id
                  FROM emp_ama
                  WHERE lower(first_name)||' '||lower(last_name) ='douglas grant'
                  );
                  
-- ex 17
update emp_ama e
SET (salary, commission_pct) = (SELECT salary, commission_pct
                                FROM employees
                                WHERE