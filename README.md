# Car Rental System

This is a simple car rental system implemented in C++. It uses object-oriented programming principles and uses File Handling through C++ for data storage. The data is stored in text files, and the program reads from and writes to these files whenever necessary.

## Program Structure

The software is divided into several directories and files:

- `src/`: This directory contains all the source code files.
    - `main.cpp`: This is the main program file. It includes the `main` function which drives the program.
    - `Person.cpp`: This file contains the implementation of the `Person` class. It includes functions for reading from and writing to the Person data file.
    - `Customer.cpp`: This file contains the implementation of the `Customer` class, which inherits from `Person`. It includes functions for reading from and writing to the Customer data file.
    - `Employee.cpp`: This file contains the implementation of the `Employee` class, which also inherits from `Person`. It includes functions for reading from and writing to the Employee data file.
    - `Manager.cpp`: This file contains the implementation of the `Manager` class. It includes functions for reading from and writing to the Manager data file.
    - `Car.cpp`: This file contains the implementation of the `Car` class. It includes functions for reading from and writing to the Car data file.
- `include/`: This directory contains all the header files.
    - `Person.h`: This file contains the declaration of the `Person` class.
    - `Customer.h`: This file contains the declaration of the `Customer` class.
    - `Employee.h`: This file contains the declaration of the `Employee` class.
    - `Manager.h`: This file contains the declaration of the `Manager` class.
    - `Car.h`: This file contains the declaration of the `Car` class.


## Assumptions

While developing this software, the following assumptions were made:

1. Each person (customer or employee) can rent a maximum of 3 cars at a time.
2. The rental period for a car is variable and is specified when the car is rented.
3. The condition of a car when it's returned can be variable.
4. A person's record score increases by 10 (not exceeding 100) each time they return a car within the due date and in good condition.
5. A person's record score decreases by 10 multiplied with number of days of late return from dueDate.
6. A manager can add, update, or delete any customer, employee, or car in the store.
