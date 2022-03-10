SET SERVEROUTPUT ON;
SET VERIFY OFF;

---Ex. 2---

DECLARE
    CURSOR cur_job IS (
        SELECT job_id, job_title
        FROM jobs);
        
    CURSOR cur_emp(param_cod employees.job_id%TYPE) IS (
        SELECT last_name, salary, commission_pct
        FROM employees
        WHERE job_id = param_cod);
    v_job_id     jobs.job_id%TYPE;
    v_job_title  jobs.job_title%TYPE;
    v_name       employees.last_name%TYPE;
    v_salary     employees.salary%TYPE;
    v_commission employees.commission_pct%TYPE;
    v_ind        NUMBER := 1;
    v_venit_job  NUMBER := 0;
    v_venit_total NUMBER := 0;
    v_nr_total   NUMBER := 0;
BEGIN
    OPEN cur_job;
    LOOP
    FETCH cur_job INTO v_job_id, v_job_title;
    EXIT WHEN cur_job%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Job-ul cu titlul ' || v_job_title || ' are angajatii:');
    
    OPEN cur_emp(v_job_id);
    
    --cazul in care nu are salariati
    IF cur_emp%NOTFOUND THEN RAISE_APPLICATION_ERROR(-1, 'Jobul nu are salariati');
    END IF;
    
    LOOP
    FETCH cur_emp INTO v_name, v_salary, v_commission;
    EXIT WHEN cur_emp%NOTFOUND;
    
    DBMS_OUTPUT.PUT_LINE(v_ind || '. Angajatul cu numele ' || v_name || ' are salariul ' || v_salary ||
                         ' si comisionul ' || NVL(v_commission,0));
    v_ind := v_ind + 1;
    v_venit_job := v_venit_job + v_salary * (1 + NVL(v_commission,0));
    END LOOP;
    v_ind := v_ind - 1;
    v_nr_total := v_nr_total + v_ind;
    
    DBMS_OUTPUT.PUT_LINE('Numarul de angajati: ' || v_ind);
    DBMS_OUTPUT.PUT_LINE('Valoarea veniturilor lunare: ' || v_venit_job);
    DBMS_OUTPUT.PUT_LINE('Media veniturilor lunare: ' || v_venit_job/v_ind);
    v_ind := 1;
    v_venit_total := v_venit_total + v_venit_job;
    v_venit_job := 0;
    DBMS_OUTPUT.PUT_LINE('-----------------------------------------------------');
    CLOSE cur_emp; 
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Venit total: ' || v_venit_total);
    DBMS_OUTPUT.PUT_LINE('Numar total de angajati: ' || v_nr_total);
    DBMS_OUTPUT.PUT_LINE('Media veniturilor: ' || ROUND(v_venit_total/v_nr_total,3));
    CLOSE cur_job;
END;
/


DECLARE
    CURSOR cur_job IS (
        SELECT job_id, job_title
        FROM jobs);
        
    CURSOR cur_emp(param_cod employees.job_id%TYPE) IS (
        SELECT last_name, salary, commission_pct
        FROM employees
        WHERE job_id = param_cod);
    v_job_id     jobs.job_id%TYPE;
    v_job_title  jobs.job_title%TYPE;
    v_name       employees.last_name%TYPE;
    v_salary     employees.salary%TYPE;
    v_commission employees.commission_pct%TYPE;
    v_ind        NUMBER := 1;
    v_venit_job  NUMBER := 0;
    v_venit_total NUMBER := 0;
    v_nr_total   NUMBER := 0;
    suma_salarii NUMBER := 0;
    suma_comisioane NUMBER := 0;
    TYPE rec IS RECORD (nume employees.last_name%TYPE,
                        salariu employees.salary%TYPE,
                        comision employees.commission_pct%TYPE);
    TYPE ind IS TABLE OF rec INDEX BY BINARY_INTEGER;
    v ind;
BEGIN
    OPEN cur_job;
    LOOP
    FETCH cur_job INTO v_job_id, v_job_title;
    EXIT WHEN cur_job%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Job-ul cu titlul ' || v_job_title || ' are angajatii:');
    
    OPEN cur_emp(v_job_id);
    
    --cazul in care nu are salariati
    IF cur_emp%NOTFOUND THEN RAISE_APPLICATION_ERROR(-1, 'Jobul nu are salariati');
    END IF;
    
    FETCH cur_emp BULK COLLECT INTO v;
    
    FOR i IN v.FIRST..v.LAST LOOP
        SELECT SUM(salary) INTO suma_salarii
        FROM employees;
        SELECT SUM(salary * NVL(commission_pct,0)) INTO suma_comisioane
        FROM employees;
        
        DBMS_OUTPUT.PUT_LINE(v_ind || '. Angajatul cu numele ' || v(i).nume || ' are salariul ' || 
                            v(i).salariu || ' si comisionul ' || NVL(v(i).comision,0)
                            || ' si castiga ' || ROUND(v(i).salariu/suma_salarii,3)
                            || ' si ' || ROUND((v(i).salariu * NVL(v(i).comision,0))/suma_comisioane,3));
        
        v_ind := v_ind + 1;
        v_venit_job := v_venit_job + v(i).salariu * (1 + NVL(v(i).comision,0));
                
        v_ind := v_ind - 1;
        v_nr_total := v_nr_total + v_ind;
        
        DBMS_OUTPUT.PUT_LINE('Numarul de angajati: ' || v_ind);
        DBMS_OUTPUT.PUT_LINE('Valoarea veniturilor lunare: ' || v_venit_job);
        DBMS_OUTPUT.PUT_LINE('Media veniturilor lunare: ' || v_venit_job/v_ind);
    
    END LOOP;
    v_ind := 1;
    v_venit_total := v_venit_total + v_venit_job;
    v_venit_job := 0;
    DBMS_OUTPUT.PUT_LINE('-----------------------------------------------------');
    CLOSE cur_emp; 
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Venit total: ' || v_venit_total);
    DBMS_OUTPUT.PUT_LINE('Numar total de angajati: ' || v_nr_total);
    DBMS_OUTPUT.PUT_LINE('Media veniturilor: ' || ROUND(v_venit_total/v_nr_total,3));
    CLOSE cur_job;
END;
/

---Ex. 4---

DECLARE
    CURSOR cur_job IS (
        SELECT job_id, job_title
        FROM jobs);
        
    CURSOR cur_emp(param_cod employees.job_id%TYPE) IS (
        SELECT * FROM (
                        SELECT last_name, salary, commission_pct
                        FROM employees
                        WHERE job_id = param_cod
                         ORDER BY salary DESC
                      )
       );
    v_job_id     jobs.job_id%TYPE;
    v_job_title  jobs.job_title%TYPE;
    v_name       employees.last_name%TYPE;
    v_salary     employees.salary%TYPE;
    v_commission employees.commission_pct%TYPE;

BEGIN
    OPEN cur_job;
    LOOP
    FETCH cur_job INTO v_job_id, v_job_title;
    EXIT WHEN cur_job%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Job-ul cu titlul ' || v_job_title || ' are angajatii:');
    
    OPEN cur_emp(v_job_id);
    --cazul in care nu are salariati
    IF cur_emp%NOTFOUND THEN RAISE_APPLICATION_ERROR(-1, 'Jobul nu are salariati');
    END IF;
    
    LOOP
    FETCH cur_emp INTO v_name, v_salary, v_commission;
    EXIT WHEN cur_emp%NOTFOUND OR cur_emp%ROWCOUNT > 5;
    DBMS_OUTPUT.PUT_LINE('Angajatul cu numele ' || v_name || ' are salariul ' || v_salary ||
                         ' si comisionul ' || NVL(v_commission,0));
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('-----------------------------------------------------');
    CLOSE cur_emp; 
    END LOOP;
    CLOSE cur_job;
END;
/

---- Ex 5 ----

DECLARE
    CURSOR cur_job IS (
        SELECT job_id, job_title
        FROM jobs);
        
    CURSOR cur_emp(param_cod employees.job_id%TYPE) IS (
        SELECT * FROM (
                        SELECT last_name, salary, commission_pct
                        FROM employees
                        WHERE job_id = param_cod
                        ORDER BY salary DESC
                      )
       );
    v_job_id     jobs.job_id%TYPE;
    v_job_title  jobs.job_title%TYPE;
    v_name       employees.last_name%TYPE;
    v_salary     employees.salary%TYPE;
    v_commission employees.commission_pct%TYPE;
    v_last_salary employees.salary % TYPE := -1;
    v_count_salary employees.salary % TYPE := 0;
BEGIN
    OPEN cur_job;
    LOOP
        FETCH cur_job INTO v_job_id, v_job_title;
        EXIT WHEN cur_job%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('Job-ul cu titlul ' || v_job_title || ' are angajatii:');
        
        OPEN cur_emp(v_job_id);
        --cazul in care nu are salariati
        IF cur_emp%NOTFOUND 
            THEN RAISE_APPLICATION_ERROR(-1, 'Jobul nu are salariati');
        END IF;

        v_count_salary := 1;
        v_last_salary := -1;
        LOOP
            FETCH cur_emp INTO v_name, v_salary, v_commission;
            EXIT WHEN cur_emp%NOTFOUND OR v_count_salary > 5; -- a gasit mai mult de 5 salarii
            DBMS_OUTPUT.PUT_LINE('Angajatul cu numele ' || v_name || ' are salariul ' || v_salary ||
                                 ' si comisionul ' || NVL(v_commission,0));
  
            IF(v_salary != v_last_salary) 
                THEN v_count_salary := v_count_salary + 1;
            END IF;            
            v_last_salary := v_salary;
        END LOOP;
        
        DBMS_OUTPUT.PUT_LINE('-----------------------------------------------------');
        CLOSE cur_emp; 
    END LOOP;
    CLOSE cur_job;
END;
/

--------- Ex 1 folosind expresii cursor --------



----------- Lab 4 ex 1 ------------

CREATE TABLE info (
    utilizator VARCHAR2(50),
    data DATE DEFAULT SYSDATE,
    comanda VARCHAR2(500),
    nr_linii NUMBER,
    eroare VARCHAR2(500)
    );

CREATE OR REPLACE PROCEDURE p4(v_nume employees.last_name%TYPE)
    IS
    salariu employees.salary%TYPE;
    v_nr NUMBER;
    v_msg_err VARCHAR2(500);
    BEGIN
        SELECT salary INTO salariu
        FROM employees
        WHERE last_name = v_nume;
        
        SELECT COUNT(*) INTO v_nr
        FROM employees
        WHERE last_name = v_nume;
        
        INSERT INTO info
        VALUES(user, SYSDATE, 'SELECT', 1, 'Fara eroare');
        
        DBMS_OUTPUT.PUT_LINE('Salariul este '|| salariu);
    EXCEPTION
    WHEN NO_DATA_FOUND THEN
        v_msg_err := SUBSTR(SQLERRM, 1, 500);
        INSERT INTO info
        VALUES(user, SYSDATE, 'SELECT', 0, v_msg_err);
        RAISE_APPLICATION_ERROR(-20000, 'Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
        v_msg_err := SUBSTR(SQLERRM, 1, 500);
        INSERT INTO info
        VALUES(user, SYSDATE, 'SELECT', v_nr, v_msg_err);
        RAISE_APPLICATION_ERROR(-20001,'Exista mai multi angajati cu numele dat');
    WHEN OTHERS THEN 
        v_msg_err := SUBSTR(SQLERRM, 1, 500);
        INSERT INTO info
        VALUES(user, SYSDATE, 'SELECT', -1, v_msg_err);
        RAISE_APPLICATION_ERROR(-20002,'Alta eroare!');
END p4;
/
BEGIN
    p4('Beladsl');
    p4('Kimbal');
END;
/
select * from info;
    
-------- Ex 3 ---------

CREATE OR REPLACE FUNCTION f3(oras locations.city % TYPE) RETURN NUMBER 
    IS v_nr NUMBER := 0;
    
    BEGIN 
        SELECT COUNT (*) INTO v_nr
        FROM employees
        JOIN departments USING(department_id)
        JOIN locations USING (location_id)
        JOIN job_history USING(employee_id)
        WHERE UPPER(city) = oras
        GROUP BY employee_id 
        HAVING COUNT(job_history.job_id) >= 2;
        
        INSERT INTO info
        VALUES(user, SYSDATE, 'SELECT', 1, 'Fara eroare');
    END;
/    

BEGIN 
    DBMS_OUTPUT.PUT_LINE(f3('oxford'));
END;
/