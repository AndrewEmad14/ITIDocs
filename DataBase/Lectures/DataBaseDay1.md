# DataBase Day 1

any app has application layer and database layer

MYSQL DB / Postgress                openSource                  small projects
Microsoft sql/oracle/ibm db         closedSource                big projects

>disadvantage of EXCEL

            cant handle big data
            cant have a foreign key
            redudndency (leads to)
            inconsistency in the data
            incompatible file sysytem

# meta data
        +Schema information: Table names, column names, data types (e.g., integer, string), and primary/foreign keys.
        +Structural information: How tables are related and how views are defined.
        +Administrative details: User information, ownership, and creation or modification dates.
        +Descriptive information: Descriptions of tables and columns, business definitions, and tags or keywords.
        +Performance and usage information: Database size, storage information, and performance metrics. 
# DBMS
    >External Shema: what data will the user see and how will it be presented
    >Conceptual Schema: contains all tables and relation between data
    >Physical Schema: contain access pathes for teh data base(where the data base is located in the hard disk)

# SDLC (Software Development Life Cycle)
        Steps for the software dev:
                    1> Analysis and gathering Req       (System Analyst)
                    2> Data base desgin                 (Data base desginer)       [ERD]
                    3>Implementation                    (DB admin/DB dev/dev)       
                                                        DB admin [installation,backup]
                                                        DB dev   [develops the database]
                                                        app dev
                    4>APP dev                           (maintaince)
# Data models
    conceptual
            provides concepts that are close to the way many users percive data 
    physical
            descirbes how data is stored in the computer and access teh path needed to access and serach for data
# DBMS Enviroment
        >Centerlaized Enviroment
                1.MainFrame     slow and single point of failure
                2.Client server 2Tier
                3.Internent computing 3Tier
        >Distributed Enviroment
                1.Replication       (Homogenous)
                    partial Replica
                    Full    Replica
                2.fragmentation     (Hetrogenous)
                    Horizontal 
                    Vertical
# Non Releational Data Base
                no table
                no fk
                no pk
                no integrity constraints
                no relation
                no security
                BUT IT is very quick AND sutiable for media storing
                data stored as jason
        <3 kinds of NoSQL>
                1.Document oriented             MongoDB
                2.Key-value                     Redis/Oracale
                3.Column based                  ApacheHBase/cassandara
                4.graph                         neo4j

        when to use
                    >hight data velocity
                    >varitey 
                    >complexity
                    >volume
# ERD
            Entities:
                Strong Entity : it has 1 attribute that is unique
                weak Entity:no unique identifier
                            must be fully dependant on antoher entity
            
            Attributes:
                    attribute on relationship
                    Pk
                    drived
                    multivalued
            Relations:
                Degree:
                    Binary
                    Tirnary:
                        Love triangle with MtoMtoM
                        new table with fk of each entity
                    Unary
                Cardinality:
                    OneToMany
                    ManyToMany
                    OneToOne
                Participation:
                    Must
                    May
# Mapping
        Emp[#SSN,name,salary,image,DOB,Street,Zone]   
        Emp[#fk1,#fk2]
        Cardinality:       
        Emp : Dep
        1 >     1       put fk in the smaller attr table
                        to avoid null attr
        M       <1      add PK of one to M-side table as FK

        M       <M      new table with  FK of both tables

        Participation
            may must    put may pk into must as fk

            may may     pk second to first OR
                           first to second OR
                           first and second in a table
            must must   Merge the two tables
  
        NOTE: 
            >if you have a multi value attr you have to take it to a seprate table  
            >Preferably dont use two pks , use a pk and 
            a unique value

# FAQ
            Customer Relationship Management (CRM)
            Point Of Sale                    (POS)
            Enterprise Source Planing        (ERP)
            Today assigment:
                   > ERD diagram
                   > table mapping
            PK: cant be null, must be unique,only one pk
            

            Weak Entity: 
                        doesnt have an id cant coexsit without the entity it depends on
            UInary : may may
            Tiernary : must must must