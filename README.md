# Vehicle Rental System

<br>
author- Aditya Shankar Khorne

<br>
Vehicle Rental System is an application built using C++ that helps an operator to maintain records related to users, vehicles and trips at the vehicle rental office. 
<br>
<br>
The application includes the following functionalities:
<br>
1. Addition of new vehicles trips and users.
<br>
2. Editing vehicle and trip information.
<br>
3. Viewing historical data of past trips or the trips scheduled in the future.

<br>
<br>
The application is built on the concepts of Object-oriented Programming such as Inheritance, Abstraction, Virtualization, Templates, STL, Polymorphism, I/O Operations, among others.

<br>
<br>
A database class provides abstraction layer for I/O operations. Data is brought from files to the memory and can be accessed through a Generic class table. Table can hold data of type Vehicle, User and Trip. The overload subscript operator [] is used inside the Table class to fetch record at a particular index. Further, exceptions have been added to handle invalid inputs.
<br>
While accessing the information, the actual data is never shared; instead, only the constant references of the data are shared. This helps to prevent accidental data corruption.