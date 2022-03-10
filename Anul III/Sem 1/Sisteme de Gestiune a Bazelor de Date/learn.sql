SET SERVEROUTPUT ON;
SET VERIFY OFF;
DECLARE 
    TYPE t_rec IS RECORD 
    (
        v_sal NUMBER(8),
        v_min_sal NUMBER(8) DEFAULT 100,
        v_hire_date employees.hire_date % TYPE,
        v_linie employees % rowtype
    );
    v_rec t_rec;
BEGIN 
    v_rec.v_sal := v_rec.v_min_sal + 200;
    SELECT * INTO v_rec.v_linie
    FROM employees
    WHERE employee_id = 130;
    
    DBMS_OUTPUT.PUT_LINE(v_rec.v_linie.last_name);
END;
/

DECLARE 
    TYPE secventa IS VARRAY(6) OF VARCHAR2(30);
    v_sec secventa := secventa('alb', 'negru', 'rosu');
BEGIN 
    v_sec(1) := 'rossuuuu';
    v_sec.EXTEND;
    v_sec.EXTEND;
    v_sec(5) := ' verde';
    DBMS_OUTPUT.PUT_LINE(v_sec(1));
    DBMS_OUTPUT.PUT_LINE(v_sec(2));
    DBMS_OUTPUT.PUT_LINE(v_sec(3));
    DBMS_OUTPUT.PUT_LINE(v_sec(4));
    DBMS_OUTPUT.PUT_LINE(v_sec(5));
END;
/

DECLARE 
    TYPE alfa IS TABLE OF VARCHAR2(20);
    tab1 alfa;
    tab2 alfa := alfa();
    tab3 alfa := alfa('mama');
BEGIN
    tab2.EXTEND;
    tab2(1) := 'Caca';
    dBMS_output.put_LINE(tab2(1));
    tab3.EXTEND;
    tab3(2) := 'tata';
    DBMS_OUTPUT.PUT_LINE(tab3(2));
--    tab2.EXTEND;
--    tab3.EXTEND;
END;
/


------------------------ LAB 2 -------------------------------

-- ex 2
DECLARE 
    TYPE emp_record IS RECORD 
    (cod employees.employee_id % TYPE,
     salariu employees.salary % TYPE,
     job employees.job_id % TYPE
    );
    v_ang emp_record;
BEGIN
    v_ang.cod := 700;
    v_ang.salariu := 9000;
    v_ang.job := 'SA_MAN';
    DBMS_OUTPUT.PUT_LINE('Angajatul cu codul ' || v_ang.cod || ' si ' || v_ang.job || ' castiga ' || v_ang.salariu);
    
    SELECT employee_id, salary, job_id
    INTO v_ang 
    FROM employees
    WHERE employee_id = 101;
    DBMS_OUTPUT.PUT_LINE('Angajatul cu codul ' || v_ang.cod || ' si ' || v_ang.job || ' castiga ' || v_ang.salariu);

END;
/

DECLARE 
    TYPE tablou_indexat IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
    t tablou_indexat;
BEGIN
    for i in 1..10 LOOP
        t(i) := i;
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE('Nr elemente: ' || t.COUNT);
    for i in 1..10 LOOP
        DBMS_OUTPUT.PUT_LINE(t(i));
    END LOOP;
    
    for i in 1..10 LOOP
        IF(i mod 2 = 1) 
            THEN t(i) := NULL;
        END IF;
    END LOOP;
    
    t.DELETE(t.FIRST);
    t.DELETE(5, 7);
    t.DELETE(t.LAST);
    t.DELETE(t.LAST);

    
    DBMS_OUTPUT.PUT_LINE(t.FIRST);
    DBMS_OUTPUT.PUT_LINE(t(t.FIRST));
    DBMS_OUTPUT.PUT_LINE(t.LAST);
    DBMS_OUTPUT.PUT_LINE(t(t.LAST));
END;
/

select * from employees;

-- ex 5
DECLARE
    TYPE tablou_indexat IS
        TABLE OF emp_ama%rowtype INDEX BY BINARY_INTEGER;
    t   tablou_indexat;
BEGIN
-- stergere din tabel si salvare in tablou
    DELETE FROM emp_ama
    WHERE
        ROWNUM <= 2
    RETURNING employee_id,
              first_name,
              last_name,
              email,
              phone_number,
              hire_date,
              job_id,
              salary,
              commission_pct,
              manager_id,
              department_id BULK COLLECT INTO t;
--afisare elemente tablou

    dbms_output.put_line(t(1).employee_id
                           || ' '
                           || t(1).last_name);

    dbms_output.put_line(t(2).employee_id
                           || ' '
                           || t(2).last_name);
--inserare cele 2 linii in tabel

    INSERT INTO emp_ama VALUES t ( 1 );

    INSERT INTO emp_ama VALUES t ( 2 );

END;
/

-- ex 6 (rezolvarea lui 4 cu tablouri imbricate)
DECLARE
    TYPE tablou_imbricat IS
        TABLE OF NUMBER;
    t   tablou_imbricat := tablou_imbricat ();
BEGIN
-- punctul a
    FOR i IN 1..10 LOOP
        t.extend;
        t(i) := i;
    END LOOP;

    FOR i IN t.FIRST .. t.LAST LOOP
        dbms_output.put_line(t(i));
    END LOOP;
-- punctul b
    
    FOR i in t.FIRST .. t.LAST LOOP 
        if(i mod 2 = 1) 
            THEN t(i) := null;
        END IF;
    END LOOP;
    
    FOR i in t.FIRST .. t.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(t(i));
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE(t.COUNT);
    
    
END;
/

-- ex 7
DECLARE 
    TYPE tablou_imbricat IS TABLE OF CHAR(1);
    t tablou_imbricat := tablou_imbricat('1', '2', '3', '4', '5');
    i INTEGER;
BEGIN
    i := t.FIRST;
    WHILE i <= t.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(t(i));
        i := t.NEXT(i);
    END LOOP;
    
    DBMS_OUTPUT.NEW_LINE;
    
    i := t.LAST;
    
    WHILE i >= t.FIRST LOOP
         DBMS_OUTPUT.PUT_LINE(t(i));
         i := t.PRIOR(i);
    END LOOP;
    
    t.DELETE(2);
    t.DELETE(4);
    
        i := t.FIRST;
    WHILE i <= t.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(t(i));
        i := t.NEXT(i);
    END LOOP;
    
    DBMS_OUTPUT.NEW_LINE;
    
    i := t.LAST;
    
    WHILE i >= t.FIRST LOOP
         DBMS_OUTPUT.PUT_LINE(t(i));
         i := t.PRIOR(i);
    END LOOP;
END;
/

-- ex 10
CREATE TABLE emp_test_ama AS 
    SELECT employee_id, last_name
    FROM employees
    WHERE ROWNUM <= 2;

CREATE OR REPLACE TYPE tip_telefon_ama IS TABLE OF VARCHAR2(12);
/
ALTER TABLE emp_test_ama
ADD (telefon tip_telefon_ama)
NESTED TABLE telefon STORE AS tabel_telefon_ama;

INSERT INTO emp_test_ama
VALUES(500, 'nume1', tip_telefon_ama('0752', '2321', '07699'));

INSERT INTO emp_test_ama
VALUES(501, 'nume2', tip_telefon_ama('0755', '0788'));

select a.employee_id, b.*
From emp_test_ama a, TABLE (a.telefon) b;


-------- ex 1 de jos
DECLARE 
    TYPE angajati IS TABLE OF employees % rowtype;
    v_ang angajati;
BEGIN
    SELECT * BULK COLLECT INTO v_ang
    FROM (SELECT *
          FROM employees
          WHERE commission_pct IS NULL
          ORDER BY salary ASC
          )WHERE ROWNUM <= 5;
    
    FOR i in v_ang.FIRST .. v_ang.LAST LOOP
        DBMS_OUTPUT.PUT_LINE('Old value: ' || v_ang(i).employee_id || ' castiga ' || v_ang(i).salary);
    END LOOP;  
    
    FOR i in v_ang.FIRST .. v_ang.LAST LOOP
        UPDATE emp_ama
        SET salary = 1.05 * salary
        WHERE employee_id = v_ang(i).employee_id
        RETURNING salary INTO v_ang(i).salary;
        
        DBMS_OUTPUT.PUT_LINE('NEW value: ' || v_ang(i).employee_id || ' castiga ' || v_ang(i).salary);
    END LOOP;
    
    DBMS_OUTPUT.NEW_LINE;
    
--    FOR i in v_ang.FIRST .. v_ang.LAST LOOP
--    END LOOP;  
END;
/
select * from employee_ama;
SET SERVEROUTPUT ON;
SET VERIFY OFF;

-- ex 2

    CREATE OR REPLACE TYPE tip_orase IS TABLE OF VARCHAR2(100);
    /
    CREATE TABLE excursie(
        cod_excursie NUMBER(4),
        denumire VARCHAR2(20),
        orase tip_orase,
        status VARCHAR2(15)
    ) NESTED TABLE orase STORE AS tabel_orase;
    
INSERT INTO excursie VALUES(1, 'Excursia 1', tip_orase('Bucuresti', 'Iasi', 'Timisoara'), 'disponibil');

INSERT INTO excursie VALUES(2, 'Excursia 2', tip_orase('Bucuresti'), 'disponibil');

INSERT INTO excursie VALUES(3, 'Excursia 3', tip_orase('Ploiesti'), 'disponibil');

INSERT INTO excursie VALUES(4, 'Excursia 4', tip_orase('Bacau', 'Suceava', 'Galati'), 'disponibil');

INSERT INTO excursie VALUES(5, 'Excursia 5', tip_orase('Roman', 'Cazanesti'), 'indisponibil');
delete from excursie where cod_excursie = 5;

-- b)
DECLARE
--    v_oras_nou VARCHAR2(20) := '&p_oras_nou';
--    v_oras_nou_2 VARCHAR2(20) := '&p_oras_nou_2';
    
--    v_cod_excursie excursie.cod_excursie % TYPE := &p_cod;
--    v_cod_excursie_2 excursie.cod_excursie % TYPE := &p_cod_2;
--    v_cod_excursie_3 excursie.cod_excursie % TYPE := &p_cod_3;
    v_cod_excursie_c excursie.cod_excursie % TYPE := &p_cod_4;    
    
    v_lista tip_orase;
BEGIN
--    SELECT orase INTO v_lista
--    FROM excursie
--    WHERE cod_excursie = v_cod_excursie;
    
--    SELECT orase INTO v_lista
--    FROM excursie
--    WHERE cod_excursie = v_cod_excursie_c;
--    
--    v_lista.EXTEND();
--    for i in REVERSE 2 .. (v_lista.LAST - 1) LOOP
--        v_lista(i + 1) := v_lista(i);
--    END LOOP;
--    v_lista(2) := v_oras_nou_2;
    
--    SELECT orase INTO v_lista
--    FROM excursie
--    WHERE cod_excursie = v_cod_excursie_c;
--    
--    DBMS_OUTPUT.PUT_LINE('Nr = ' || v_lista.COUNT);
--    DBMS_OUTPUT.NEW_LINE;
--    
--    FOR i in v_lista.FIRST .. v_lista.LAST LOOP
--        DBMS_OUTPUT.PUT_LINE(v_lista(i));
--    END LOOP;
END;
/

DECLARE
    TYPE t_ind IS TABLE OF excursie.cod_excursie % TYPE INDEX BY BINARY_INTEGER;
    TYPE numar IS TABLE OF NUMBER INDEX BY BINARY_INTEGER;
    id_excursie numar;
    t t_ind;
    v_orase excursie.orase % TYPE;
    minim NUMBER := 1000000;
BEGIN
    SELECT cod_excursie BULK COLLECT INTO t
    FROM excursie;
    
    FOR i IN t.FIRST .. t.LAST LOOP
        SELECT orase INTO v_orase
        FROM excursie WHERE cod_excursie = t(i);
        
        IF (v_orase IS NULL)
            THEN 
                minim := 0;
                id_excursie.DELETE(1, id_excursie.COUNT);
                id_excursie(1) := t(i);
                
        ELSIF (minim > v_orase.COUNT)
            THEN 
                minim := v_orase.COUNT;
                id_excursie.DELETE(1, id_excursie.COUNT);
                id_excursie(1) := t(i);
        ELSIF (minim = v_orase.COUNT)
            THEN
                id_excursie(id_excursie.LAST + 1) := t(i);
        END IF;
--        DBMS_OUTPUT.PUT_LINE('Excursie = ' || t(i) || ' Nr = ' || v_orase.COUNT);
        
--        FOR j IN v_orase.FIRST .. v_orase.LAST LOOP
--            DBMS_OUTPUT.PUT_LINE(v_orase(j));
--        END LOOP;    
--        DBMS_OUTPUT.NEW_LINE;
    END LOOP;
    
    FOR i IN 1 .. id_excursie.COUNT LOOP
        DBMS_OUTPUT.PUT_LINE(id_excursie(i));
    END LOOP;
END;
/


---------------- lab 3 CURSOARE ---------------------

-- ex 1
DECLARE 
    v_nr number(4);
    v_nume departments.department_name % TYPE;
    CURSOR c IS 
        SELECT department_name nume, COUNT(employee_id) nr
        FROM departments d, employees e
        WHERE d.department_id = e.department_id (+)
        GROUP BY department_name;
BEGIN
    OPEN c;
    LOOP 
        FETCH c INTO v_nume, v_nr;
        EXIT WHEN c % NOTFOUND;
        IF v_nr = 0 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || v_nume || ' nu lucreaza angajati');
        ELSIF v_nr = 1 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || v_nume || ' lucreaza un angajat');
        ELSE 
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || v_nume || ' lucreaza ' || v_nr || ' angajati');
        END IF;
    END LOOP;
    CLOSE c;
END;    
/

-- ex 2
DECLARE
    TYPE tab_nume IS TABLE OF departments.department_name % TYPE;
    TYPE tab_nr IS TABLE OF NUMBER(4);
    t_nr tab_nr;
    t_nume tab_nume;
    CURSOR c IS 
        SELECT department_name nume, COUNT(employee_id) nr
        FROM departments d, employees e
        WHERE d.department_id = e.department_id (+)
        GROUP BY department_name;
BEGIN
    OPEN c;
    FETCH c BULK COLLECT INTO t_nume, t_nr;
    CLOSE c;
    FOR i in t_nume.FIRST .. t_nume.LAST LOOP
       IF t_nr(i) = 0 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || t_nume(i) || ' nu lucreaza angajati');
        ELSIF t_nr(i) = 1 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || t_nume(i) || ' lucreaza un angajat');
        ELSE 
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || t_nume(i) || ' lucreaza ' || t_nr(i) || ' angajati');
        END IF;
    END LOOP;
END;
/

-- ex 3
DECLARE 
    CURSOR c IS 
        SELECT department_name nume, COUNT(employee_id) nr
        FROM departments d, employees e
        WHERE d.department_id = e.department_id (+)
        GROUP BY department_name;
BEGIN
    FOR i in c LOOP
        IF i.nr = 0 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.nume || ' nu lucreaza angajati');
        ELSIF i.nr = 1 THEN
                DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.nume || ' lucreaza un angajat');
        ELSE 
                DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.nume || ' lucreaza ' || i.nr || ' angajati');
        END IF;
    END LOOP;
END;
/

-- ex 4

BEGIN
    FOR i in ( SELECT department_name nume, COUNT(employee_id) nr
                FROM departments d, employees e
                WHERE d.department_id = e.department_id (+)
                GROUP BY department_name) LOOP
        IF i.nr = 0 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.nume || ' nu lucreaza angajati');
        ELSIF i.nr = 1 THEN
                DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.nume || ' lucreaza un angajat');
        ELSE 
                DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.nume || ' lucreaza ' || i.nr || ' angajati');
        END IF;
    END LOOP;       
END;
/

-- ex 5

DECLARE
    v_cod employees.employee_id % TYPE;
    v_nume employees.last_name % TYPE;
    v_nr NUMBER(4);
    CURSOR C is 
        SELECT sef.employee_id cod, MAX(sef.last_name) nume, count(*) nr
        FROM employees sef, employees ang
        WHERE ang.manager_id = sef.employee_id
        GROUP BY sef.employee_id
        ORDER BY nr DESC;
BEGIN
    OPEN c;
    LOOP 
        FETCH c INTO v_cod, v_nume, v_nr;
        EXIT WHEN c % ROWCOUNT > 3 OR c % NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('Managerul ' || v_cod || ' avand numele ' || v_nume || ' are ' || v_nr || ' angajati');
    END LOOP;
    CLOSE c;
END;
/

-- ex 6
DECLARE 
    CURSOR C IS 
        SELECT sef.employee_id cod, MAX(sef.last_name) nume, COUNT(*) nr
        FROM  employees sef, employees ang
        WHERE ang.manager_id = sef.employee_id
        GROUP BY sef.employee_id
        ORDER BY nr DESC;
BEGIN 
    FOR i in c LOOP
        EXIT WHEN c % ROWCOUNT > 3 OR c % NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('Managerul ' || i.cod || ' avand numele ' || i.nume || ' are ' || i.nr || ' angajati');
    END LOOP;
END;
/

-- ex 7
DECLARE 
    top number(1) := 0;
BEGIN
    FOR i in (SELECT sef.employee_id cod, MAX(sef.last_name) nume, COUNT(*) nr
              FROM  employees sef, employees ang
              WHERE ang.manager_id = sef.employee_id
              GROUP BY sef.employee_id
              ORDER BY nr DESC
              ) LOOP
        DBMS_OUTPUT.PUT_LINE('Managerul ' || i.cod || ' avand numele ' || i.nume || ' are ' || i.nr || ' angajati');
        top := top + 1;
        EXIT WHEN top = 3;
    END LOOP;
END;
/

-- ex 8
DECLARE 
    v_x number(4) := &p_x;
    v_nr number(4);
    v_nume departments.department_name % TYPE;
    CURSOR c (parametru NUMBER) IS
        SELECT department_name nume, COUNT(employee_id) nr
        FROM departments d, employees e
        WHERE d.department_id = e.department_id (+)
        GROUP BY department_name
        HAVING COUNT(employee_id) > parametru;
BEGIN
    OPEN c(v_x);
    LOOP 
        FETCH c INTO v_nume, v_nr;
        EXIT WHEN c % NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('In departamentul ' || v_nume || ' lucreaza ' || v_nr);
    END LOOP;
CLOSE c;
END;
/
    