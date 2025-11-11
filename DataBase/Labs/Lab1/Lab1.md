# Q1

     Nouns
        Offices
            ID
            Address
            contactno
        Owner 
            name
            nationalID(UID)
            Bankaccount
        Tenant
            nationalID
            valid Driver licence
            Mobile number  
        Car
            ID
            Model
                brand
                model name
                model year
            valid licensce
            rent amount
            car status
        Transaction
            start date
            duration
            payment method

    Verbs
            orders
            rent 
            transfer
            apply for rent
            rent
    Relations 
            car     M  Must Must   1 owner
            owner   M  May  May    1 office
            car     M  May  Must   M tennant
            car     M  May  May    1 office
            owner   1  May  Must   M Transaction
            Teneant 1  May  Must   M Transaction
            car     1  May  Must   1 Transaction
    
<Map>
    Owner[#ownerNationalID,fullName,bankAccount,#FK:officeID,carID,rentAmount,#Fk:modelID,validCarLicense,carStatus] 
    Car[#PK:carID,#FK:officeID,,rentAmount,#Fk:modelID,validCarLicense,carStatus]
    Offices[#officeID,contactNo,address]

    Model[#modelID,modelName,brand,modelYear]

    Tenant[#tenantNationalID,validDriverLicencse,mobileNumber]

    CarAndTenant[PK:{FK:carID,Fk:tenantNationalID}]

    Transaction[PK:{#FK:ownerNationalID,#FK:tenantNationalID,#Fk:carID},startDate,Duration,PaymentMethod]


# Q2

    Noun
        Lab
        Branch
            code
            shortname
            address
                city 
                street 
                building number
        Medical Tests
            code
            name 
            cost
            duration
        Patient
            PatientID
            FullName
            Age (drived)
            mobileNumber
            DateOFbirth
            gender
            chronic diseases
        Date and time(Patient)
        Employees
            employeeID
            full name
            salary
            start and end time
            manager
            team

    Verbs
        provide test
        visit branch
        preform test
        work
        record
        assigned
        supervise


    Relations
        Test     M May  May M Branch
        Patient  M Must May M Branch
        Patient  M Must May M Test
        Employee M Must May 1 Branch
        Employee M May  May 1 Manager
<Map>
      Employee[#employeeID,fullName,manager,salary, team ,startAndEndTime,FK:#BranchCode,managerID]

      Branch[#BranchCode,addressID,shortName]

      Address[AddressID,city,street,buildingNumber]

      Patient[#PatientID,gender,fullName,dateOFBirth,mobileNumber,chronicDiseases]

      MedicalTest[#TestCode,name,duration,cost]
      
      getsTest[PK={FK:#PatientID,FK:#BranchCode,FK:TestCode},dateAndTime]



 


# Q3

    Noun
        branches
            ID
            address
            contact number
        staff
            manager
            ID
            full name
            age
            address
            role
            joining date 
            monthly salary
            date of birth
        customer
            code
            name
            contact number
        menu
            item name
            unit price
            category
        order
            Id
            address
            date&time
            bill
        [order items]
        dilevery
            national id 
            contact number
            names
            

