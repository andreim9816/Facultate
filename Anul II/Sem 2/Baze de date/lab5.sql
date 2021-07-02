-- ex 1

-- daca vrem dupa mai multe criterii , folosim ROLLUP sau CUBE
-- daca astea nu respecta cerintele, facem altfel

--a) ROLLUP le face pe toate 3
SELECT department_name , job_title , ROUND(AVG(salary))
FROM departments
JOIN employees USING(department_id)
JOIN jobs USING(job_id)
GROUP BY ROLLUP(department_name , job_title); 

-- b)
SELECT department_name , GROUPING(department_name) , 
job_title , GROUPING(job_title) , ROUND(avg(salary))
FROM departments
JOIN employees USING (department_id)
JOIN jobs USING(job_id)
GROUP BY (department_name , job_title);

-- ex 2

-- a)
SELECT  job_title , ROUND(AVG(salary)),
DECODE (GROUPING(department_name) , 0 , DECODE(GROUPING(job_title) , 0 , 'dept si job' , 1 , 'dep') , 1 , DECODE(GROUPING(job_title) , 0 , 'JOB' , '-')) as "Participare"          
FROM departments
JOIN employees USING(department_id)
JOIN jobs USING(job_id)
GROUP BY CUBE(department_name , job_title); 

-- b)
SELECT department_name , GROUPING(department_name) , 
job_title , GROUPING(job_title) , ROUND(avg(salary))
FROM departments
JOIN employees USING (department_id)
JOIN jobs USING(job_id)
GROUP BY (department_name , job_title);

-- ex 3

SELECT department_name , job_title , employees.manager_id , MAX(salary) , MIN(salary)
FROM departments
JOIN employees USING (department_id)
JOIN jobs USING(job_id)
GROUP BY GROUPING SETS((department_name , job_title) , (job_title , employees.manager_id) , ());

-- ex 4

SELECT MAX(salary)
FROM employees
WHERE salary > 15000;

SELECT MAX(salary) 
FROM employees
HAVING max(salary) > 15000;

-- ex 5

SELECT employee_id , last_name , salary 
FROM employees e
WHERE salary >
                (SELECT AVG(salary)
                 from EMPLOYEES
                 WHERE department_id = e.department_id AND employee_id <> e.employee_id);

-- b)
SELECT employee_id , last_name , salary , department_name
, (SELECT AVG(salary) 
   FROM employees
   WHERE department_id = e.department_id) "Medie"
FROM employees e
JOIN departments d ON (d.department_id = e.department_id)
WHERE salary > 
                (SELECT avg(salary) FROM employees
                 WHERE department_id = e.department_id AND employee_id <> e.employee_id);

-- ex 5
SELECT employee_id , last_name , salary , department_name , medie
FROM employees e JOIN (SELECT AVG(salary) medie , department_id FROM employees GROUP BY department_id FROM employees
GROUP BY department_id) aux ON (aux.department_id = e.department_id)
JOIN departments d ON (d.department_id = e.department_id)
WHERE salary > medie;

-- ex 6

SELECT last_name , salary
FROM employees
WHERE salary > 
                ALL(SELECT AVG(salary)
                FROM employees
                GROUP BY department_id);
                
-- var 2

SELECT last_name , salary
FROM employees
WHERE salary > (Select MAX(AVG(salary))
                FROM employees
                GROUP BY department_id);
                
-- ex 7

-- var 1

SELECT last_name , salary
FROM employees e
WHERE salary = (
                SELECT MIN(salary)
                FROM employees
                WHERE e.department_id = department_id);

-- var 2
SELECT last_name , salary
FROM employees
WHERE (salary , department_id) IN (
                                SELECT MIN(salary) , department_id
                                FROM employees
                                GROUP BY department_id);

-- var 3
SELECT last_name , salary
FROM employees e
JOIN (
        SELECT MIN(salary) mini, department_id
        FROM employees
        GROUP BY department_id) aux
        
ON (e.department_id = aux.department_id)
WHERE salary = mini;

-- ex 8

SELECT last_name , department_id
FROM employees e
WHERE HIRE_DATE = (
                    SELECT MIN(hire_date)
                    FROM employees
                    WHERE e.department_id = department_id);

-- ex 9
SELECT last_name
FROM employees e
WHERE EXISTS (
                SELECT 1 -- macar o linie care sa respecte conditia department_d = e.department_id si salariul = max. Exists intoarce mai repede rezultat
                FROM employees
                WHERE department_id = e.department_id AND salary = (
                                                                    SELECT MAX(salary)
                                                                    FROM employees
                                                                    WHERE department_id = 30));
                                                                    
--ex10                                                          



-- NU MERGE !!!!!
SELECT last_name , salary
FROM employees
WHERE ROWNUM <= 5
ORDER BY salary desc;

-- CAND NI SE CERE TOP N, TREBUIE SA AM 2 CERERI, IN CARE UNA FACE ORDONARE

SELECT*
FROM (
        SELECT last_name , salary
        FROM employees
        ORDER BY salary DESC)
        WHERE ROWNUM <= 5;
        
-- ex 11

SELECT employee_id , last_name
FROM employees e
WHERE (
        SELECT COUNT(manager_id)
        FROM employees
        WHERE e.employee_id = manager_id
        GROUP BY manager_id
       ) >= 2;
       
-- ex 12
SELECT city
FROM locations l
WHERE EXISTS(
                SELECT 'c'
                FROM departments
                WHERE location_id = l.location_id);
                
-- varianta cu IN 

SELECT city
FROM locations 
WHERE location_id IN (
                SELECT location_id
                FROM departments);
                
-- DE GANDIT CU OP. MINUS SAU JOIN

-- ex 13

SELECT department_id , department_name
FROM departments d
WHERE NOT EXISTS (
                SELECT -1
                FROM employees
                WHERE d.department_id = department_id);
     
-- tema JOIN

-- ex 14

SELECT employee_id , last_name , hire_date , salary , manager_id
FROM employees
WHERE LEVEL = 2 -- radacina are level 1
START WITH employee_id = (
                            SELECT employee_id 
                            FROM employees
                            WHERE UPPER(last_name)
                            LIKE 'DE HAAN')
CONNECT BY PRIOR  employee_id = manager_id;

-- ex 15

SELECT LEVEL , employee_id , last_name, hire_date , salary , manager_id
FROM employees
START WITH employee_id = 114
CONNECT BY PRIOR employee_id = manager_id;

--TEMA AFISARE LAST NAME INDENTAT IN FUNCTIE DE LEVEL WTF
--TEMA TOT PANA LA CLAUZA WITH