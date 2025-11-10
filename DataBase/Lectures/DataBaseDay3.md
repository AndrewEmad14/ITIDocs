# DB day 3


# Structure Query Language
        >Data Defention Language
                CREATE
                ALTER
                DROP
                TRUNCATE
        >Data Manpulation Language
                SELECT
                UPDATE
                INSERT
                DELETE
                MERGE
        >Data Contorl Language
                GRANT
                REVOKE


        DECEMIAL(10,2)
                10 digits with two of them after the decimal point
        STR_TO_DATE("17-6-2022","%d-%m-%Y")

        >Aggregated functions
        sum(salary), max(salary), min(salary), count(*),AVG()
        
        Groupby()                                               //if you want to group by column

        USE having with aggregate functions
        
        cant use the alias with

        INNER JOIN
                every value must have another value oppisite to it
                **Example**
                    select *
                    form employee,department
                    where fk=pk
                if there is a duplicate the use the name of the table before it

                full join isnt in SQL
        LEFT OUTER JOIN             //no null on left
        RIGHT OUTER JOIN            //no null on right
        FULL OUTER JOIN             //can be null on both
        

        from employee emps employee mgrs

# FAQ
    DDL does auto commit , so any actions or quiries you did is auto commited

    think of enity or attribute as something that is sperable from the other enitty or not

    transaction from the first question is a relation 

    bill is a drived attribute

    when implemting the data base start with the smallest entities
    remeber to set the current schema u are working on into default

    IN INSERT : put the column names
                dont insert an auto incremeted value
    
    test every action

    USING WHERE OR ON AND JOIN
        it improves readablity to use on and join 
        where is implict and it would result in an inner join most of the time
        in orderer to use another type of join we use JOIN