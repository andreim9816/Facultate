/* ex 14 */

/* argumentele functiei NVL trebuie sa aiba acelasi tip sau sa se poata converti la tipul primului argument, de asta pun to_char */

SELECT last_name , NVL(to_char(commission_pct) , 'Fara Comision') as "Comision"
FROM employees;

/* varianta 2 cu NVL2 */

SELECT last_name , NVL2(to_char(commission_pct) , to_char(commission_pct), 'Fara comision') as "Comision"
FROM employees;

/* varianta 3 cu DECODE */

SELECT last_name , DECODE(commission_pct , NULL , 'Fara comision') as "Comision"
FROM employees;

/* ex 15 */
SELECT last_name , salary , commission_pct 
FROM employees
WHERE salary * (1 + NVL( commission_pct , 0)) > 10000;

/* ex 16 */

SELECT last_name , JOB_ID , salary ,  DECODE(upper(job_id) , 'IT_PROG' , salary * 1.2 , 'SA_REP' , salary * 1.25 , 'SA_MAN' , salary * 1.35 , salary)
as "Salariu renegociat"
from EMPLOYEES;

SELECT last_name , JOB_id, salary , 
CASE UPPER(job_id) 
    WHEN 'IT_PROG' THEN salary * 1.2
    WHEN 'SA_REP' THEN salary * 1.25
    WHEN 'SA_MAN' THEN salary * 1.35
    ELSE salary
END "SALARIU RENEGOCIAT"
FROM employees;

/* ex 17 */

-- var STANDARD
/* este o coloana cu acelasi nume pentru ambele tabele */
SELECT last_name ,  department_id , department_name 
FROM employees 
JOIN departments USING (department_id);

-- var folosind clauza ON
SELECT last_name , e.department_id , department_name 
FROM employees e
JOIN departments d ON (e.department_id = d.department_id);  

-- var nonStandard

SELECT last_name , e.department_id , department_name 
FROM employees e, departments d
WHERE(e.department_id = d.department_id);  

/* ex 18 */

SELECT job_title
FROM jobs
JOIN EMPLOYEES USING (job_id)
WHERE department_id = 30 ;

/* ex 19 */

SELECT last_name , department_name , city 
FROM employees
JOIN departments USING (department_id)
JOIN locations USING (location_id)
WHERE commission_pct is NOT NULL;

/* ex 20 */
-- ON e mai general, e mai recomandat de stiut mai bine 

SELECT last_name , department_name
FROM employees e
JOIN departments d ON(e.department_id = d.department_id AND upper(last_name) LIKE '%A%');

/* ex 21 */
-- using, scrii mai putin daca ai coloane cu acelasi nume in tabele

SELECT last_name , job_id , department_id, department_name 
FROM employees 
JOIN departments USING (department_id)
JOIN locations USING(location_id)
WHERE INITCAP(city) LIKE '%Oxford%';

/* ex 22 */

SELECT ang.employee_id AS "Ang#", ang.last_name AS "Angajat", sef.employee_id AS "Mgr#" , sef.last_name AS "Manager"
FROM employees ang
JOIN employees sef ON (ang.manager_id = sef.employee_id);

/* ex 23 */

-- am pus LEFT ca sa-mi ia valorile NULL pentru ang.manager
-- daca pun RIGHT, afiseaza angajati care nu au pe nimeni in subordonare ( sef peste nimeni)

SELECT ang.employee_id AS "Ang#", ang.last_name AS "Angajat", sef.employee_id AS "Mgr#" , sef.last_name AS "Manager"
FROM employees ang
LEFT JOIN employees sef ON (ang.manager_id = sef.employee_id);

/* ex 24 */

-- punem conditii cat sa triem din cazuri ( sa nu am A-B si B-A)
SELECT ang.last_name as "NUME", ang.department_id , coleg.last_name as "COLEG"
FROM employees ang
JOIN employees coleg ON (ang.department_id = coleg.department_id AND ang.employee_id < coleg.employee_id);

/* ex 25 TEMA */

/* ex 26 */

select e.last_name , e.hire_date , g.last_name , g.hire_date
FROM employees e
JOIN employees g ON (e.hire_date > g.hire_date AND INITCAP(g.last_name) LIKE '%Gates%');

/* ex 27 TEMA */
