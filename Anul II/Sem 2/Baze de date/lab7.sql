-- ex 16

SELECT employee_id , manager_id , last_name , LEVEL
FROM employees
WHERE LEVEL = 3
START WITH UPPER(last_name) LIKE ('DE HAAN')
CONNECT BY PRIOR employee_id = manager_id;

-- ex 17

SELECT LEVEL , employee_id , manager_id , last_name , LPAD(last_name , 3 * level )
FROM employees
CONNECT BY PRIOR manager_id = employee_id;

-- ex 18
-- nu e corect ce am scris eu, cand rula profa dadea altceva

SELECT level , employee_id , last_name , salary , manager_id
FROM employees
-- WHERE salary > 15000 cica nu e bine
START WITH employee_id = (
                            SELECT employee_id
                            FROM employees
                            WHERE salary = (
                                            SELECT max(salary)
                                            FROM employees
                                            )
                         )
CONNECT BY PRIOR salary > 15000 and employee_id = manager_id ;

-- WITH --------------------

/*
WITH 
aux AS (SELECT ... )
aux2 AS (SELECT ... )
...
auxn as (SELECT ... )


SELECT ... 
FROM aux CROSS JOIN aux2
         CROSS JOIN auxn
WHERE ...
...
*/

-- ex 19

WITH 
total AS (
            SELECT department_id , SUM (salary) AS suma
            FROM employees
            GROUP BY department_id 
         )
SELECT department_name , suma
FROM departments d
JOIN total t ON (d.department_id = t.department_id)
WHERE suma > (
                SELECT AVG(suma)
                FROM total
             );
             
-- ex 20

WITH 
king as (
            SELECT employee_id kod
            FROM employees
           -- WHERE manager_id IS NULL
            WHERE LOWER(last_name) LIKE 'king' and LOWER(first_name) LIKE 'steven'
            
        )   
SELECT employees.employee_id , first_name || ' ' || last_name , hire_date
FROM employees CROSS JOIN king
WHERE level = 2 /*and hire_date = ( 
                                    SELECT MIN(hire_date)
                                    FROM employees
                                ) */
                                AND EXTRACT(year FROM hire_date) <> 1970
START WITH employees.employee_id = kod 
CONNECT BY PRIOR employees.employee_id = manager_id;

-- ex 21

-- intai e WHERE si apoi ORDER BY, daca scriam doar SELECT ... order by WHERE .. nu afisa ce trbuie
SELECT *
FROM (
        SELECT last_name , salary
        FROM employees
        ORDER BY salary DESC
     )
WHERE ROWNUM <11;

-- ex 22

--tema de facut cu decode

SELECT *
FROM (  SELECT job_title
        FROM JOBS
        ORDER BY ( min_salary + max_salary) /2 
     )
WHERE ROWNUM <= 3;

-- ex 23
SELECT 'Departamentul ' || department_name || ' este condus de ' || NVL(to_char(manager_id) , 'nimeni') || ' si are ' ,
CASE WHEN nr > 0 THEN ' are numerul de salariati ' || nr
ELSE ' nu are salariati' 
END as "INFORMATII"
FROM departments d LEFT JOIN (
                                SELECT department_id , COUNT(employee_id) nr
                                FROM employees
                                GROUP BY department_id
                              ) aux
                              
                              ON (d.department_id = aux.department_id);
                              
                              
-- ex 24
SELECT last_name , first_name , length(last_name)
FROM employees
WHERE NULLIF(length(last_name) , length(first_name)) IS NOT NULL;

-- ex 25

-- de facut cu CASE ca tema

SELECT last_name , hire_date,  salary,
DECODE (to_char(hire_date , 'YYYY') , 1989 , salary * 1.2 , 1990 , salary * 1.15 , 1991 , salary * 1.10 , salary) marire
FROM employees;

-- ex 26

SELECT (
        SELECT sum(salary)
        FROM employees
        WHERE job_id LIKE 'S%'
       ) suma,
       
       (SELECT AVG(salary)
        FROM employees
        WHERE (job_id , salary ) IN (SELECT job_id, max(salary)
                                    FROM employees
                                    GROUP BY job_id
                                    )) medie
/*, (SELECT MIN(salary)
     FROM employees
     WHERE job_id NOT LIKE 'S%' (AND job_id  , salary) != (SELECT .... cel luung) minim
*/
FROM DUAL;

-- tema cu CASE 
/*
SELECT CASE SI EVALUATI JOB ID 
WHEN JOB_ID LIKE S THEN..
WHEN JOB_ID LIKE THEN AVG(SALARY)
ELSE MIN(SALARY
FROM EMPLOYEES 

-- eventual si cu decode
*/