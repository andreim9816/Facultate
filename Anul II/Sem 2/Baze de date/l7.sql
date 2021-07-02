-- MANOLACHE ANDREI
-- 244
-- tema laborator 7 ( din laboratorul 5)

-- ex 12 with JOIN

SELECT DISTINCT city
FROM locations l
JOIN departments d ON(l.location_id = d.location_id);

-- ex 13 with JOIN

SELECT d.department_name , d.department_id 
FROM departments d
LEFT JOIN employees e ON (d.department_id = e.department_id)

MINUS

SELECT d.department_name , d.department_id
FROM departments d
JOIN employees e ON (d.department_id = e.department_id);

-- ex 15 with ierarchy

SELECT employee_id , manager_id , LEVEL , LPAD( ' ', LEVEL , ' ' ) || first_name || ' ' || last_name  as "Nume" , hire_date , salary
FROM employees
START WITH employee_id = 114
CONNECT BY PRIOR employee_id = manager_id 
ORDER BY LEVEL;

-- ex 16

SELECT first_name , last_name , employee_id , manager_id , LEVEL
FROM employees
WHERE LEVEL =  2 + (
                    SELECT LEVEL -- DE HAAN's level
                    FROM employees
                    WHERE LOWER(last_name) LIKE 'de haan'
                    START WITH  employee_id = (
                                                SELECT employee_id
                                                FROM employees
                                                WHERE manager_id IS NULL -- starts with KING
                                               ) 
                    CONNECT BY PRIOR employee_id = manager_id
                    )
START WITH employee_id = (
                          SELECT employee_id
                          FROM employees
                          WHERE manager_id IS NULL-- starts the hierarchy with KING
                         ) 
CONNECT BY PRIOR employee_id = manager_id;

-- ex 17

SELECT  employee_id ,  manager_id , level,
       lpad ( ' ', LEVEL , ' ' ) || first_name || ' ' || last_name as "Name"
FROM  employees
START WITH manager_id is null
CONNECT BY PRIOR employee_id = manager_id;

-- ex 18

SELECT employee_id , last_name , salary , LEVEL , manager_id
FROM employees
WHERE LEVEL <> 1 and salary > 5000 -- without him 
START WITH employee_id = ( -- employee with the maximum salary
                            SELECT employee_id
                            FROM employees
                            WHERE salary = (
                                                SELECT MAX(salary)
                                                FROM employees
                                            )
                         )
CONNECT BY PRIOR employee_id = manager_id;         
