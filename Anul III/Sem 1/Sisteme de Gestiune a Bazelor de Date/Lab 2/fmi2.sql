VARIABLE g_mesaj VARCHAR2(50)
BEGIN
:g_mesaj := 'Invat PL/SQL';
DBMS_OUTPUT.PUT_LINE(:g_mesaj);
END;
/

DECLARE 
    v_dep departments.department_name %TYPE;
BEGIN
    SELECT department_name
    INTO v_dep
    FROM employees e, departments d
    WHERE e.department_id = d.department_id
    GROUP BY department_name
    HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                        FROM employees
                        GROUP BY department_id);
    DBMS_OUTPUT.PUT_LINE('Departamentul '|| v_dep);
END;
/
                        
-- ex 6
DECLARE 
    v_dep departments.department_name %TYPE;
    v_nr NUMBER := 0;
BEGIN
    SELECT department_name, COUNT(*)
    INTO v_dep, v_nr
    FROM employees e, departments d
    WHERE e.department_id = d.department_id
    GROUP BY department_name
    HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                        FROM employees
                        GROUP BY department_id);
    DBMS_OUTPUT.PUT_LINE('Departamentul '|| v_dep || ' care are ' || v_nr || ' angajati');
END;

-- ex 7
SET VERIFY OFF -- sa nu afiseze de 2 ori codul inainte de introducerea valorilor de substutie de la tastatura
DECLARE
    v_cod employees.employee_id % TYPE := &p_cod;
    v_bonus NUMBER(8);
    v_salariu_anual NUMBER(8);
BEGIN
    SELECT salary * 12
    INTO v_salariu_anual
    FROM employees
    WHERE employee_id = v_cod;
    IF v_salariu_anual>=200001
        THEN v_bonus := 20000;
    ELSIF v_salariu_anual BETWEEN 100001 AND 200000
      THEN v_bonus := 10000;
    ELSE v_bonus := 5000;
    END IF;
    DBMS_OUTPUT.PUT_LINE('Bonusul este ' || v_bonus);
END;
/
SET VERIFY ON

-- ex 8

DECLARE
    v_cod employees.employee_id%TYPE:=&p_cod;
    v_bonus NUMBER(8);
    v_salariu_anual NUMBER(8);
BEGIN
    SELECT salary*12
    INTO v_salariu_anual
    FROM employees
    WHERE employee_id = v_cod;
    CASE WHEN v_salariu_anual >= 200001
        THEN v_bonus:=20000;
    WHEN v_salariu_anual BETWEEN 100001 AND 200000
        THEN v_bonus:=10000;
    ELSE v_bonus:=5000;
    END CASE;
    DBMS_OUTPUT.PUT_LINE('Bonusul este ' || v_bonus);
END;
/

-- ex 9
-- atribuire in afara lui PLSQL pt var de subsitutie:

DEFINE p_cod_sal= 200
DEFINE p_cod_dept = 80
DEFINE p_procent = 20
DECLARE
    v_cod_sal emp_ama.employee_id%TYPE:= &p_cod_sal;
    v_cod_dept emp_ama.department_id%TYPE:= &p_cod_dept;
    v_procent NUMBER(8):=&p_procent;
BEGIN
    UPDATE emp_***
    SET department_id = v_cod_dept,
    salary=salary + (salary* v_procent/100)
    WHERE employee_id= v_cod_sal;
    IF SQL % ROWCOUNT = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista un angajat cu acest cod');
    ELSE DBMS_OUTPUT.PUT_LINE('Actualizare realizata');
END IF;
END;
/
ROLLBACK;    

-- ex 10

CREATE TABLE zile_ama (id NUMBER,
                       data DATE,
                       nume_zi VARCHAR2(10)
                      );
DECLARE
    contor NUMBER(6) := 1;
    v_data DATE;
    maxim NUMBER(2) := LAST_DAY(SYSDATE)-SYSDATE;
BEGIN
    LOOP
        v_data := SYSDATE +contor;
        INSERT INTO zile_ama
        VALUES (contor, v_data, to_char(v_data, 'Day'));
        contor := contor + 1;
--        DBMS_OUTPUT.PUT_LINE(to_char(v_data, 'Day'));
        EXIT WHEN contor > maxim;
    END LOOP;
END;
/

SELECT * FROM zile_ama;



-- ex 11

DECLARE
    contor NUMBER(6) := 1;
    v_data DATE;
    maxim NUMBER(2) := LAST_DAY(SYSDATE)-SYSDATE;
BEGIN
    WHILE contor <= maxim LOOP
        v_data := sysdate+contor;
        INSERT INTO zile_ama
        VALUES (contor,v_data,to_char(v_data,'Day'));
        contor := contor + 1;
    END LOOP;
END;
/

-- ex 13
DECLARE
    i POSITIVE:=1;
    max_loop CONSTANT POSITIVE:=10;
BEGIN
LOOP
    i:=i+1;
    IF i>max_loop THEN
        DBMS_OUTPUT.PUT_LINE('in loop i=' || i);
        GOTO urmator;
    END IF;
END LOOP;
<<urmator>>
i:=1;
DBMS_OUTPUT.PUT_LINE('dupa loop i=' || i);
END;
/

DECLARE
    i POSITIVE:=1;
    max_loop CONSTANT POSITIVE:=10;
BEGIN
i:=1;
LOOP
        i:=i+1;
        DBMS_OUTPUT.PUT_LINE('in loop i=' || i);
        EXIT WHEN i>max_loop;
END LOOP;
i := 1;
DBMS_OUTPUT.PUT_LINE('dupa loop i=' || i);
END;
/

-- EXERCITII
-- ex 1
DECLARE
    numar number(3):=100;
    mesaj1 varchar2(255):='text 1';
    mesaj2 varchar2(255):='text 2';
BEGIN
    DECLARE
        numar number(3):=1;
        mesaj1 varchar2(255):='text 2';
        mesaj2 varchar2(255):='text 3';
        BEGIN
            DBMS_OUTPUT.PUT_LINE('Inainte numar: ' || numar || ' mesaj ' || mesaj1 || ' measaj2: ' || mesaj2);
            numar:=numar+1;
            mesaj2:=mesaj2||' adaugat in sub-bloc';
        END;
  numar := numar+1;
  mesaj1 := mesaj1||' adaugat un blocul principal';
  mesaj2 := mesaj2||' adaugat in blocul principal';
  DBMS_OUTPUT.PUT_LINE('Inainte numar: ' || numar || ' mesaj ' || mesaj1 || ' measaj2: ' || mesaj2);

END;
/
-- ex 2

--b 
DECLARE
    v_nr NUMBER;
    data_curr DATE := TO_DATE('1 OCTOBER', 'DD MONTH');
BEGIN 
    for contor in 1...31 LOOP
        SELECT COUNT(*)
        INTO v_nr
        FROM rental
        WHERE TO_CHAR(book_date, 'DD MM') = TO_CHAR(data_curr + contor - 1, 'DD MM');
        INSERT INTO oct_ama VALUES(v_nr, data_curr + contor - 1);
    END LOOP;
END;
/

-- ex 1
-- Definiti un bloc anonim care citeste de la tastatura un
-- cod de angajat si ii afiseaza numele.

DECLARE
    v_last_name VARCHAR2(30);
BEGIN
    SELECT last_name
    INTO v_last_name
    FROM  employees
    WHERE employee_id = &emp_id;
    DBMS_OUTPUT.PUT_LINE('Angajatul cu codul introdus se numeste ' || v_last_name);
  
    EXCEPTION
    WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Angajatul respectiv nu exista!');
END;
/

-- ex 2
-- Definiti un bloc anonim care citeste de la tastatura un
-- nume de angajat si afiseaza salariul.

--ex 2b)
DECLARE
    v_salariu NUMBER;
BEGIN
    SELECT salary
    INTO v_salariu
    FROM  employees
    WHERE LOWER(last_name) = LOWER('&last_name_employee');
    DBMS_OUTPUT.PUT_LINE('Angajatul respectiv castiga ' || v_salariu);
   
    EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Angajatul respectiv nu exista!');
    WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('Sunt prea multi angajati cu numele respectiv!');
END;
/
-- ex 2 a)
SELECT TRUNC(SYSDATE, 'month') + LEVEL -1 ziua
FROM dual
CONNECT BY LEVEL <+ EXTRACT (DAY FROM LAST_DAY(SYSDATE));

SELECT ziua, (SELECT COUNT(*)
              FROM rental
              WHERE TO_CHAR(book_date, 'dd.mm.yyyy') = TO_CHAR(ziua, 'dd.mm.yyyy')) as nr
FROM (SELECT TRUNC(SYSDATE, 'month') + LEVEL -1 ziua
      FROM dual
      CONNECT BY LEVEL <+ EXTRACT (DAY FROM LAST_DAY(SYSDATE))
     );             
     
-- ex 3
DECLARE
    v_nume member.last_name%type:='&p_nume';
    v_numar NUMBER;
BEGIN
    SELECT COUNT(*) INTO v_numar
    FROM MEMBER
    WHERE LOWER(last_name) = v_nume;
     IF v_numar = 0
        THEN RAISE_APPLICATION_ERROR(-20000, 'Nu exista membru cu numele dat!');
    END IF;
   
    SELECT COUNT(*)
    INTO v_numar
    FROM MEMBER
    JOIN RENTAL USING (member_id)
    WHERE LOWER(last_name) = v_nume;
     IF v_numar = 0
        THEN RAISE_APPLICATION_ERROR(-20001, 'Membrul nu a imprumutat filme!');
     END IF;
    dbms_output.put_line('Membru cu numele ' || v_nume || ' a imprumutat ' || v_numar || ' filme');
    EXCEPTION
    WHEN TOO_MANY_ROWS THEN dbms_output.put_line('Exista mai multi membri cu numele dat!');
END;
/
SET SERVEROUTPUT ON

-- ex 4

SELECT * FROM title;

DECLARE
    v_nume member.last_name %type:='&p_nume';
    v_numar NUMBER; 
    v_numar2 v_numar % TYPE;
BEGIN
SELECT COUNT(*)
INTO v_numar
FROM MEMBER
WHERE LOWER(last_name) = v_nume;
IF v_numar = 0 THEN RAISE_APPLICATION_ERROR(-20000, 'Nu exista membru cu numele dat!');
END IF;
SELECT COUNT(*) INTO v_numar2
FROM title;

SELECT COUNT(*)
INTO v_numar
FROM MEMBER
JOIN RENTAL USING (member_id)
WHERE LOWER(last_name) = v_nume;
IF v_numar = 0 THEN RAISE_APPLICATION_ERROR(-20001, 'Membrul nu a imprumutat filme!');
END IF;
dbms_output.put_line('Membru cu numele ' || v_nume || ' a imprumutat ' || v_numar || ' filme');

IF v_numar > 0.75 * v_numar2 THEN dbms_output.put_line('Categoria 1');
ELSIF v_numar > 0.5 * v_numar2 THEN dbms_output.put_line('Categoria 2');
ELSIF v_numar > 0.25 * v_numar2 THEN dbms_output.put_line('Categoria 3');
ELSE dbms_output.put_line('Categoria 4');
END IF;
EXCEPTION
WHEN TOO_MANY_ROWS THEN dbms_output.put_line('Exista mai multi membri cu numele dat!');
END;
/

-- ex 5

CREATE TABLE member_ama
AS SELECT * FROM member;

ALTER TABLE member_ama
ADD discount NUMBER(2,2);

DECLARE
    v_nume member.last_name %type:='&p_nume';
    v_numar NUMBER; 
    v_numar2 v_numar % TYPE;
    v_categorie VARCHAR2(20);
    v_discount member_ama.discount %type;
BEGIN
    SELECT COUNT(*)
    INTO v_numar
    FROM MEMBER
    WHERE LOWER(last_name) = v_nume;
   
    IF v_numar = 0 THEN RAISE_APPLICATION_ERROR(-20000, 'Nu exista membru cu numele dat!');
    END IF;
   
    SELECT COUNT(*) INTO v_numar2
    FROM title;
    
    SELECT COUNT(*)
    INTO v_numar
    FROM MEMBER
    JOIN RENTAL USING (member_id)
    WHERE LOWER(last_name) = v_nume;
   
    IF v_numar = 0 THEN RAISE_APPLICATION_ERROR(-20001, 'Membrul nu a imprumutat filme!');
    END IF;
    
    dbms_output.put_line('Membru cu numele ' || v_nume || ' a imprumutat ' || v_numar || ' filme');
    
    IF v_numar > 0.75 * v_numar2 THEN v_categorie := 'Categoria 1'; v_discount := 0.1 ;
    ELSIF v_numar > 0.5 * v_numar2 THEN v_categorie := 'Categoria 1'; v_discount := 0.05 ;
    ELSIF v_numar > 0.25 * v_numar2 THEN v_categorie := 'Categoria 1'; v_discount := 0.03 ;
    ELSE v_categorie := 'Categoria 1'; v_discount := 0;
    END IF;
    
    dbms_output.put_line('Membrul ' || v_nume || ' face parte din cateogria ' || v_categorie);
    
    UPDATE member_ama
    SET discount = v_discount
    WHERE LOWER(last_name) = LOWER(v_nume);
    
    IF SQL % ROWCOUNT = 0
        THEN dbms_output.put_line('Actualizarea NU s-a produs!');
    ELSE dbms_output.put_line('Actualizarea s-a produs!');
    END IF;
    
    EXCEPTION
    WHEN TOO_MANY_ROWS THEN dbms_output.put_line('Exista mai multi membri cu numele dat!');
END;
/


-- aceeasi chestie, dar face cu CASE in loc la declarare

DECLARE
    v_nume member.last_name %type:='&p_nume';
    v_numar NUMBER; 
    v_numar2 v_numar % TYPE;
    v_categorie VARCHAR2(20);
    v_discount member_ama.discount %type;
BEGIN
    SELECT COUNT(*)
    INTO v_numar
    FROM MEMBER
    WHERE LOWER(last_name) = v_nume;
   
    IF v_numar = 0 THEN RAISE_APPLICATION_ERROR(-20000, 'Nu exista membru cu numele dat!');
    END IF;
   
    SELECT COUNT(*) INTO v_numar2
    FROM title;
    
    SELECT COUNT(*)
    INTO v_numar
    FROM MEMBER
    JOIN RENTAL USING (member_id)
    WHERE LOWER(last_name) = v_nume;
   
    IF v_numar = 0 THEN RAISE_APPLICATION_ERROR(-20001, 'Membrul nu a imprumutat filme!');
    END IF;
    
    dbms_output.put_line('Membru cu numele ' || v_nume || ' a imprumutat ' || v_numar || ' filme');
    
    v_discount := CASE 
                        WHEN v_numar > 0.75 * v_numar2 THEN  0.1 
                        WHEN v_numar > 0.5  * v_numar2 THEN  0.05 
                        WHEN v_numar > 0.25 * v_numar2 THEN  0.03 
                        ELSE  0
                  END; 
    
    dbms_output.put_line('Membrul ' || v_nume || ' face parte din cateogria ' || v_categorie);
    
    UPDATE member_ama
    SET discount = v_discount
    WHERE LOWER(last_name) = LOWER(v_nume);
    
    IF SQL % ROWCOUNT = 0
        THEN dbms_output.put_line('Actualizarea NU s-a produs!');
    ELSE dbms_output.put_line('Actualizarea s-a produs!');
    END IF;
    
    EXCEPTION
    WHEN TOO_MANY_ROWS THEN dbms_output.put_line('Exista mai multi membri cu numele dat!');
END;
/

