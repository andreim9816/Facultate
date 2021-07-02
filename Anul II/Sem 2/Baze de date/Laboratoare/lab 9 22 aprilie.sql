--- minus cu not exists si de 2 ori minus ?? ca tema
SELECT * 
FROM WORKS_ON;

SELECT * 
FROM projects;

-- ex 1
-- varianta cu dubla negatie

SELECT employee_id, last_name, salary
FROM employees e
WHERE NOT EXISTS(SELECT 1
                 FROM projects p
                 WHERE EXTRACT(YEAR FROM start_date) = 2006 AND
                       EXTRACT(MONTH FROM start_date) BETWEEN 1 AND 6 AND
                       NOT EXISTS(SELECT 'q'
                                  FROM works_on w
                                  WHERE w.project_id = p.project_id AND w.employee_id = e.employee_id
                                  )
                );

-- varianta cu COUNT
SELECT employee_id, last_name, salary
FROM employees
JOIN works_on USING(employee_id)
WHERE project_id IN(SELECT project_id
                    FROM projects
                    WHERE EXTRACT(YEAR FROM start_date) = 2006 AND
                       EXTRACT(MONTH FROM start_date) BETWEEN 1 AND 6
                    )
GROUP BY employee_id, last_name, salary
HAVING COUNT(project_id) = (SELECT COUNT(project_id)
                            FROM projects
                            WHERE EXTRACT(YEAR FROM start_date) = 2006 AND
                            EXTRACT(MONTH FROM start_date) BETWEEN 1 AND 6
                           );

-- tema variantele 3 si 4 !!!!!!!!!!!!!!!!!!! !!!!!!!!!!!!!! !!!!!!!!!!!!!! !!!!!!!!!!!!!! 

-- ex 2

-- de facut si cu alte variante("daca vrem")
SELECT *
FROM projects p 
WHERE NOT EXISTS(SELECT 2
                 FROM job_history jh
                 WHERE NOT EXISTS(SELECT 'd'
                                  FROM works_on  w
                                  WHERE w.employee_id = jh.employee_id AND
                                        w.project_id = p.project_id
                                 )
                 GROUP BY employee_id
                 HAVING COUNT(employee_id) = 2
                 );
                 
SELECT *
FROM job_history
ORDER BY 1;

-- ex 3
SELECT COUNT(COUNT(employee_id))
FROM job_history
GROUP BY employee_id
HAVING COUNT(employee_id) >= 2;

-- ex 4

SELECT COUNT(employee_id), country_name
FROM employees
JOIN departments USING(department_id)
JOIN locations USING(location_id)
JOIN countries USING(country_id)
GROUP BY country_name;

-- ex 5
SELECT employee_id, last_name
FROM employees e
WHERE (SELECT COUNT(COUNT(w.project_id))
                FROM works_on w
                JOIN projects p ON(w.project_id = p.project_id)
                WHERE e.employee_id = w.employee_id AND
                      delivery_date > deadline
                   
              GROUP BY w.project_id
       ) >= 2;

-- ex 6
SELECT w.employee_id, last_name, w.project_id, p.project_name
FROM employees e
LEFT JOIN works_on w ON(e.employee_id = w.employee_id)
LEFT JOIN projects p ON(p.project_id = w.project_id);

-- ex 7
SELECT e.employee_id, e.last_name
FROM employees e
WHERE department_id IN(SELECT department_id
                       FROM employees
                       WHERE employee_id IN(SELECT project_manager
                                            FROM projects
                                           )
                      );
                      
-- ex 8
SELECT employee_id, last_name, salary
FROM employees
MINUS
SELECT e.employee_id, e.last_name, e.salary
FROM employees e
WHERE department_id IN(SELECT department_id
                       FROM employees
                       WHERE employee_id IN(SELECT project_manager
                                            FROM projects
                                           )
                      );

-- ex 9
SELECT department_id
FROM employees
GROUP BY department_id
HAVING AVG(salary) > &&p;

SElECt employee_id
FROM employees
WHERE salary = &w;

UNDEFINE p

ACCEPt w PROMPT 'W='

-- ex 10
SELECT last_name, first_name, salary, nr_proiecte
FROM employees e
JOIN (SELECT project_manager, COUNT(project_id) nr_proiecte
      FROM projects 
      GROUP BY project_manager
      ) t ON (e.employee_id = t.project_manager)
WHERE nr_proiecte = 2;

-- ex 11
SELECT *
FROM employees e
WHERE NOT EXISTS(SELECT 'UNU'
                 FROM projects p
                 WHERE project_manager = 102 AND
                       NOT EXISTS(SELECT 'altul'
                                  FROM works_on w
                                  WHERE w.employee_id = e.employee_id AND
                                        w.project_id = p.project_id
                                  )
                );
      
-- 12 similiar cu ce avem in DIVISION PDF
-- 13 si 14 + "primul exercitiu cu celelalte 2 variante"