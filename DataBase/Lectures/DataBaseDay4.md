# DB day 4

# View
        create or replace view emps_depts_view
        as
        select employee_id, last_name, salary, email, hire_date,
            employees.department_id, department_name
        from employees, departments
        where employees.department_id = departments.department_id;

        -- calling view
        select employee_id, last_name, department_id
        from emps_depts_view
        where department_id = 90;

        --does the query violate the condition of the view or not
        create or replace view simple_vu20
        as select * from employees
        where department_id = 20
        with check option;
# indexing
    -- ---------- ########## DB index ###### الفهرسة ############### ------------
        -- To Speed up retrieve of data during select, join
        -- db index [ Object stored in the db ( on a column ) in a table
        /*
        1. Hardware [ server, Memory, cpu ... ]
        2. Networking [ fiber .. bandwidth .. ]

        3. software [ application issues - Nested Loops .. Alogrithms ..
        change app scenario ]
        4. Database [ dba ] [ db index ]
        */
# Normalization
        > 1NF {Multi values attributes - Composite attributes - Repeating Groups (Multi Values + related attributes ) }

        MULTIVALUE:take them into a seprate table

        > 2NF { Partial dependency = attribute depend Partially on composite key attribute }

        > 3nf{ Transitive [ Fake dependency ] :> Attribute depend on a NON PK. Key Attribute }