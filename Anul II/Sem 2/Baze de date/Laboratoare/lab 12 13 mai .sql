-- ex 18
UPDATE emp_ama
SET email = INITCAP(last_name) || NVL(first_name, '.')
WHERE (department_id, salary) IN (SELECT department_id, MAX(salary)
                                  FROM employees
                                  GROUP BY department_id
                                  );
                                  
-- ex 22
SELECT * FROM dept_ama;
DELETE FROM dept_ama;

-- ex 23
DELETE FROM emp_ama
WHERE commission_pct is NULL;

-- ex 24

-- nu merge de ce??
DELETE FROM dept_ama d
WHERE NOT EXSITS (SELECT 1
                  FROM employees
                  WHERE d.department_id = department_id
                  );
                  
-- ex 25
ACCEPT p_cod PROMPT "Dati un co de angajat: ";
SELECT * FROM emp_ama
WHERE employee_id = &&p_cod;
DELETE FROM emp_ama
WHERE employee_id = &&p_cod;

SAVEPOINT A;            

-- ex 28
DELETE FROM emp_ama;
SELECT * FROM emp_ama;
ROLLBACK TO A;

-- comanda MERGE

MERGE INTO emp_ama x
USING employees e
ON (x.employee_id = e.employee_id)
WHEN MATCHED THEN 
    UPDATE SET 
        x.first_name = e.first_name,
        x.last_name = e.last_name,
        x.email = e.email,
        x.phone_number = e.phone_number,
        x.hire_date = e.hire_date,
        x.job_id = e.job_id,
        x.salary = e.salary,
        x.commission_pct = e.commission_pct,
        x.manager_id = e.department_id
WHEN NOT MATCHED THEN
    INSERT VALUES(e.employee_id, e.first_name, e.last_name, e.email,e.phone_number,
                    e.hire_date, e.job_id, e.salary, e.commission_pct,
                    e.department_id);
                    
-- LABORATOR 8       
-- LABORATORUL 8 --
-- EX 1 --
-- A) --

CREATE TABLE angajati_ama (
                            cod_ang NUMBER(4),
                            nume VARCHAR2(20),
                            prenume VARCHAR2(20),
                            email CHAR(15),
                            data_ang DATE,
                            job VARCHAR2(10),
                            cod_sef NUMBER(4),
                            salariu NUMBER(8,2),
                            cod_dep NUMBER(2)
                         );
    	
DESC angajati_ama
DROP TABLE angajati_ama;
-- B) --
CREATE TABLE angajati_ama (
    	cod_ang NUMBER(4) PRIMARY KEY,
    	nume VARCHAR2(20) NOT NULL,
    	prenume VARCHAR2(20),
    	email CHAR(15),
    	data_ang DATE,
    	job VARCHAR2(10),
    	cod_sef NUMBER(4),
    	salariu NUMBER(8,2) NOT NULL,
    	cod_dep NUMBER(2));
    	
-- C) --
DROP TABLE angajati_ama;

CREATE TABLE angajati_ama (
    	cod_ang NUMBER(4),
    	nume VARCHAR2(20) NOT NULL,
    	prenume VARCHAR2(20),
    	email CHAR(15),
    	data_ang DATE,
    	job VARCHAR2(10),
    	cod_sef NUMBER(4),
    	salariu NUMBER(8,2) NOT NULL,
    	cod_dep NUMBER(2),
    	CONSTRAINT ang_pk PRIMARY KEY (cod_ang)
    	);
    	
DROP TABLE angajati_ama;
CREATE TABLE angajati_ama (
    	cod_ang NUMBER(4),
    	nume VARCHAR2(20) NOT NULL,
    	prenume VARCHAR2(20),
    	email CHAR(15),
    	data_ang DATE default SYSDATE,
    	job VARCHAR2(10),
    	cod_sef NUMBER(4),
    	salariu NUMBER(8,2) NOT NULL,
    	cod_dep NUMBER(2),
    	CONSTRAINT ang_pk PRIMARY KEY (cod_ang)
    	);
    	
    	
-- EX 2 --
INSERT INTO angajati_ama (cod_ang, nume, prenume, data_ang, job, salariu, cod_dep)
VALUES (100, 'Nume1', 'Prenume1', null, 'Director', 20000, 10);
INSERT INTO angajati_ama (cod_ang, nume, prenume, email, data_ang, job,cod_sef, salariu, cod_dep)
VALUES (101, 'Nume2', 'Prenume2','Nume2', TO_DATE('02-02-2004', 'DD-MM-YYYY'), 'Inginer',100, 10000, 10);
INSERT INTO angajati_ama (cod_ang, nume, prenume, email, data_ang, job,cod_sef, salariu, cod_dep)
VALUES (102, 'Nume3', 'Prenume3','Nume3', TO_DATE('05-06-2000', 'DD-MM-YYYY'), 'Analist',101, 5000, 20);
INSERT INTO angajati_ama (cod_ang, nume, prenume, data_ang, job,cod_sef, salariu, cod_dep)
VALUES (103, 'Nume4', 'Prenume4', null, 'Inginer',100, 9000, 20);
INSERT INTO angajati_ama (cod_ang, nume, prenume,email, data_ang, job,cod_sef, salariu, cod_dep)
VALUES (104, 'Nume5', 'Prenume5', 'Nume5', null, 'Analist',101, 3000, 30);
-- Ex 3 --

CREATE TABLE ANGAJATI10_ama AS
SELECT * FROM angajati_ama
WHERE cod_dep = 10;
SELECT * FROM ANGAJATI10_ama;
DESC angajati_ama
DESC ANGAJATI10_ama
SELECT * FROM USER_CONSTRAINTS WHERE TABLE_NAME LIKE 'ANGAJATI%';
-- EX 4 --
ALTER TABLE angajati_ama
ADD comision NUMBER(4,2);
desc angajati_ama
-- EX 5 --
ALTER TABLE angajati_ama
MODIFY salariu NUMBER(6,2); -- NU SE POATE
ALTER TABLE angajati_ama
MODIFY salariu NUMBER(9,2);
desc angajati_ama
-- EX 6 --
ALTER TABLE angajati_ama
MODIFY salariu DEFAULT 0;
SELECT * FROM angajati_ama;
-- EX 7 --
ALTER TABLE angajati_ama
MODIFY ( comision NUMBER(2,2), salariu NUMBER(10,2));
desc angajati_ama
-- EX 8 --
UPDATE angajati_ama
SET comision = 0.1
WHERE job LIKE 'A%';
-- EX 9 --
ALTER TABLE angajati_ama
MODIFY email VARCHAR2; -- nu ruleaza pt ca nu avem dimensiune
-- EX 10 --
ALTER TABLE angajati_ama
ADD nr_telefon NUMBER DEFAULT 0;
-- EX 11 --
SELECT * FROM angajati_ama;
ALTER TABLE angajati_ama
DROP COLUMN nr_telefon;
ROLLBACK; -- NU REVIN MODIFICARILE

-- EX 12 --
RENAME angajati_ama TO ANGAJATI3_ama;
-- EX 13 --
RENAME ANGAJATI3_ama TO angajati_ama;
SELECT * FROM TAB;
-- EX 14 --
TRUNCATE TABLE angajati_ama;
SELECT * FROM angajati_ama;
ROLLBACK;
-- EX 15 --
CREATE TABLE DEPARTAMENTE_ama (
    	cod_dep NUMBER(2),
    	nume VARCHAR2(15),
    	cod_director NUMBER(4));
    	
DROP TABLE DEPARTAMENTE_ama;

CREATE TABLE DEPARTAMENTE_ama (
    	cod_dep NUMBER(2),
    	nume VARCHAR2(15) NOT NULL,
    	cod_director NUMBER(4));
    	
INSERT INTO DEPARTAMENTE_ama
VALUES (10, 'Administrativ', 100);
INSERT INTO DEPARTAMENTE_ama
VALUES (20, 'Proiectare', 101);
INSERT INTO DEPARTAMENTE_ama
VALUES (30, 'Programare', null);
-- EX 17 --
ALTER TABLE DEPARTAMENTE_ama
ADD CONSTRAINT dep_pk_ama PRIMARY KEY (cod_dep);
-- EX 18 --
-- A) --
ALTER TABLE angajati_ama
ADD CONSTRAINT emp_fk_ama FOREIGN KEY (cod_dep)
                        	REFERENCES DEPARTAMENTE_ama (cod_dep);
                        	
-- B) --
DROP TABLE angajati_ama;
CREATE TABLE angajati_ama (
    	cod_ang NUMBER(4) PRIMARY KEY,
    	nume VARCHAR2(20) NOT NULL,
    	prenume VARCHAR2(20),
    	email CHAR(15) UNIQUE,
    	data_ang DATE default SYSDATE,
    	job VARCHAR2(10),
    	cod_sef NUMBER(4) REFERENCES angajati_ama (cod_ang),
    	salariu NUMBER(8,2) NOT NULL,
    	cod_dep NUMBER(2) CHECK (cod_dep > 0) REFERENCES DEPARTAMENTE_ama (cod_dep),
    	comision NUMBER(2,2),
    	CONSTRAINT ang_ama_u UNIQUE(nume, prenume),
    	CONSTRAINT ang2_ama_ck CHECK (salariu > comision*100)
    	);
