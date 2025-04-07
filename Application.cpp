#include "application.h"
#include "database_templates.cpp"

#include <iostream>
#include <cstdio>
#include <cstdlib>

Application :: Application() {
    try{
        this->db = new Database();
    }
    catch (Error e) {
        cout<<e.getMessage();
        exit(EXIT_FAILURE);
    };
}

void Application :: gotoXY(int x, int y) const {
    printf("%c[%d;%df", 0x1B,y,x);
}

void Application :: renderMenu() {
    unsigned char choice = 1;

    while (true) {
        system("clear");

        gotoXY(25, 4);
        cout<<"Select Any option from below";
        gotoXY(25, 5);
        cout<<"1. Add New Vehicle";
        gotoXY(25, 6);
        cout<<"2. View Vehicle Datails";
        gotoXY(25, 7);
        cout<<"3. Edit Vehicle Details";
        gotoXY(25, 8);
        cout<<"4. Add New User";
        gotoXY(25, 9);
        cout<<"5. Add New Trip";
        gotoXY(25, 10);
        cout<<"6. View Trip";
        gotoXY(25, 11);
        cout<<"7. Start Trip";
        gotoXY(25, 12);
        cout<<"8. Complete Trip";
        gotoXY(25, 13);
        cout<<"9. Exit";
        
        gotoXY(30, 15);
        printf("Enter your choice: ");

        gotoXY(50, 15);
        cin>>choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case '1':
                this->renderAddNewVehicleMenu ( );
                break;
            case '2':
                this->renderViewVehicleMenu ( );
                break;
            case '3':
                this->renderEditVehicleMenu ( );
                break;
            case '4':
                this->renderAddNewUserMenu ( );
                break;
            case '5':
                this->renderAddNewTripMenu ( );
                break;
            case '6':
                this->renderViewTripMenu ( );
                break;
            case '7':
                this->renderStartTripMenu ( );
                break;
            case '8':
                this->renderCompleteTripMenu ( );
                break;
            case '9':
                this->cleanMemory ( );
                system("clear");
                exit(EXIT_SUCCESS);
                break;
            default:
                this->cleanMemory();
                system("clear");
                exit(EXIT_SUCCESS);
                break;    
        }
    }
}

void Application :: renderAddNewVehicleMenu ( ) const {
    string header = "Enter details of vehicle (All fields are required) ";
    string registrationNoLabel = "Enter vehicle registration number: ";
    string vehicleTypeLabel = "Enter vehicle type: ";
    string vehicleOptionLabel = "(1. Bike, 2. Car, 3. Towera)";
    string seatLabel = "Enter no. of seats: ";
    string companyNameLabel = "Enter name of company: ";
    string priceLabel = "Enter price per km: ";
    string pucExpirationDateLabel = "Enter PUC expiration date (d/m/yyyy): ";

    string registrationNo;
    int vehicleType;
    int seat;
    string companyName;
    double price;
    string pucExpirationDate;

    system ("clear");

    gotoXY(0, 1);
    cout<<header;

    gotoXY(0, 3);
    cout<<registrationNoLabel;

    gotoXY(0, 4);
    cout<<vehicleTypeLabel;

    gotoXY(0, 5);
    cout<<vehicleOptionLabel;

    gotoXY(0, 6);
    cout<<seatLabel;

    gotoXY(0, 7);
    cout<<companyNameLabel;

    gotoXY(0, 8);
    cout<<priceLabel;

    gotoXY(0, 9);
    cout<<pucExpirationDateLabel;

    gotoXY(int(registrationNoLabel.length()), 3);
    getline(cin, registrationNo);

    gotoXY(int(vehicleTypeLabel.length()), 4);
    cin >> vehicleType;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    gotoXY(int(seatLabel.length()), 6);
    cin >> seat;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    gotoXY(int(companyNameLabel.length()), 7);
    getline(cin, companyName);
    
    gotoXY(int(priceLabel.length()), 8);
    cin >> price;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    gotoXY(int(pucExpirationDateLabel.length()), 9);
    getline(cin, pucExpirationDate);

    Vehicle * vehicle;

    try{
        vehicle = new Vehicle(registrationNo, VehicleType(vehicleType), seat, companyName, price, Date(pucExpirationDate));
        this->db->addNewRecord(vehicle);
        stringstream ss;
        ss << "Vehicle Id: " << vehicle->getRecordId();
        showDialog("Vehicle added successfully", ss.str() );
    }
    catch (Error e) {
        showDialog(e.getMessage());
    }
    delete vehicle;
}

void Application :: renderViewVehicleMenu ( ) const {
    string header = "Enter registration no. of vehicle: ";
    string registrationNo;
    system("clear");

    gotoXY(0, 1);
    cout<<header;

    gotoXY(int(header.length()), 1);
    getline(cin, registrationNo);

    gotoXY(0, 3);
    try{
        auto vehicle = this->db->getVehicle(registrationNo);
        vehicle->display();

        cout<<endl<<"Press any key to continue";
        cin.get();
    }
    catch (Error e) {
        this->showDialog(e.getMessage() );
    }
}

void Application :: renderEditVehicleMenu ( ) const {
    string header = "Enter registration no. of vehicle you want to edit: ";
    string priceLabel = "Enter new price per km: ";
    string registrationNo;
    system("clear");

    gotoXY(0, 1);
    cout<<header;

    gotoXY(int(header.length()), 1);
    getline(cin, registrationNo);

    gotoXY(0, 3);
    Vehicle * modifiedVehicle;

    try{
        auto vehicle = this->db->getVehicle(registrationNo);
        modifiedVehicle = new Vehicle(*vehicle);
        vehicle->display();

        string newPrice;

        gotoXY(0, 12);
        cout<<priceLabel;

        gotoXY(int(priceLabel.length()), 12);
        getline(cin, newPrice);

        if(newPrice != "") {
            modifiedVehicle->setPricePerKm(stod(newPrice));
            this->db->updateRecord(modifiedVehicle);

            this->showDialog("Vehicle data updated successfully");
        }
    }
    catch(Error e) {
        this->showDialog(e.getMessage());
    }

    delete modifiedVehicle;
}

void Application :: renderAddNewUserMenu ( ) const {
    string header = "Enter details of user ";
    string userNameLabel = "Enter name of user: ";
    string usercontactLabel = "Enter contact no of user: ";
    string userEmailLabel = "Enter email of user (optional): ";

    string name;
    string contact;
    string email;

    system("clear");

    gotoXY(0, 1);
    cout << header;

    gotoXY(0, 3);
    cout << userNameLabel;

    gotoXY(0, 4);
    cout << usercontactLabel;

    gotoXY(0, 5);
    cout << userEmailLabel;


    gotoXY(int(userNameLabel.length()), 3);
    getline(cin, name);
    
    gotoXY(int(usercontactLabel.length()), 4);
    getline(cin, contact);
    
    gotoXY(int(userEmailLabel.length()), 5);
    getline(cin, email);

    User * user;

    try{
        user = new User(name, contact, email);
        
    }
}