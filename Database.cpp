#include "database.h"
#include "string_helper.h"

#include <iostream>
#include <fstream>

const char DELIMITER = ';';

Database::Database() {
    try {
        vehicleTable = new Table<Vehicle>("vehicles.txt");
        userTable = new Table<User>("users.txt");
        tripTable = new Table<Trip>("trips.txt");

        fetchAllVehicles();
        fetchAllUsers();
        fetchAllTrips();
    }
    catch(...) {
        cleanUp();
        throw;
    }
}

void Database::fetchAllVehicles() {
    vehicleTable->fileStream.open(vehicleTable->fileName);
    
    if(!vehicleTable->fileStream.is_open()) {
        throw IOError();
    }

    std::string line;
    while(std::getline(vehicleTable->fileStream, line)) {
        std::vector<std::string> components = split(line, DELIMITER);
        
        long recordId = std::stol(components[0]);
        std::string registrationNumber = components[1];
        VehicleType type = static_cast<VehicleType>(std::stoi(components[2]));
        int seats = std::stoi(components[3]);
        std::string companyName = components[4];
        double pricePerKm = std::stod(components[5]);
        Date PUCExpirationDate(components[6]);

        Storable* record = new Vehicle(
            registrationNumber, type, seats, 
            companyName, pricePerKm, PUCExpirationDate, recordId
        );
        vehicleTable->records->push_back(record);
    }
    vehicleTable->fileStream.close();
}

void Database::fetchAllUsers() {
    userTable->fileStream.open(userTable->fileName);
    
    if(!userTable->fileStream.is_open()) {
        throw IOError();
    }

    std::string line;
    while(std::getline(userTable->fileStream, line)) {
        std::vector<std::string> components = split(line, DELIMITER);

        long recordId = std::stol(components[0]);
        std::string name = components[1];
        std::string contact = components[2];
        std::string email = components[3];

        Storable* record = new User(name, contact, email, recordId);
        userTable->records->push_back(record);
    }
    userTable->fileStream.close();
}

void Database::fetchAllTrips() {
    tripTable->fileStream.open(tripTable->fileName);
    
    if(!tripTable->fileStream.is_open()) {
        throw IOError();
    }

    std::string line;
    while(std::getline(tripTable->fileStream, line)) {
        try {
            std::vector<std::string> components = split(line, DELIMITER);

            long recordId = std::stol(components[0]);
            long vehicleId = std::stol(components[1]);
            long userId = std::stol(components[2]);
            Date startDate(components[3]);
            Date endDate(components[4]);
            long startReading = std::stol(components[5]);
            long endReading = std::stol(components[6]);
            double fare = std::stod(components[7]);
            bool isCompleted = (components[8] == "1");

            Vehicle* vehiclePtr = vehicleTable->getReferenceOfRecordForId(vehicleId);
            User* userPtr = userTable->getReferenceOfRecordForId(userId);

            Storable* record = new Trip(
                vehiclePtr, userPtr, startDate, endDate,
                recordId, startReading, endReading, fare, isCompleted
            );
            tripTable->records->push_back(record);
        }
        catch(...) {
            // Handle or log exception here if needed
        }
    }
    tripTable->fileStream.close();
}

const Vehicle* Database::getVehicle(std::string registrationNo) const {
    for(auto& record : *vehicleTable->records) {
        Vehicle* vehicle = dynamic_cast<Vehicle*>(record);
        if(vehicle && vehicle->getRegistrationNumber() == registrationNo) {
            return vehicle;
        }
    }
    throw NoSuchRecordError();
}

const User* Database::getUser(std::string contactNo) const {
    for(auto& record : *userTable->records) {
        User* user = dynamic_cast<User*>(record);
        if(user && user->getContact() == contactNo) {
            return user;
        }
    }
    throw NoSuchRecordError();
}

std::vector<const Vehicle*> Database::getVehicle(Date startDate, Date endDate, VehicleType type) const {
    std::vector<const Vehicle*> availableVehicles;
    
    for(auto& vrecord : *vehicleTable->records) {
        Vehicle* vehicle = dynamic_cast<Vehicle*>(vrecord);
        if(vehicle && vehicle->getVehicleType() == type) {
            bool hasConflict = false;
            
            for(auto& trecord : *tripTable->records) {
                Trip* trip = dynamic_cast<Trip*>(trecord);
                if(trip && !trip->isCompleted() && 
                   trip->getVehicle().getRecordId() == vehicle->getRecordId()) 
                {
                    if(!(trip->getEndDate() <= startDate || trip->getStartDate() >= endDate)) {
                        hasConflict = true;
                        break;
                    }
                }
            }
            
            if(!hasConflict) {
                availableVehicles.push_back(vehicle);
            }
        }
    }
    return availableVehicles;
}

void Database::cleanUp() {
    delete vehicleTable;
    delete userTable;
    delete tripTable;
}

Database::~Database() {
    cleanUp();
}

const Table<Vehicle>* Database::getVehicleRef() const { return vehicleTable; }
const Table<User>* Database::getUserRef() const { return userTable; }
const Table<Trip>* Database::getTripRef() const { return tripTable; }

// Template implementations
template <class T>
void Database::addNewRecord(T* record) {
    // Implement your template logic here
}

template <class T>
void Database::updateRecord(T* record) {
    // Implement your template logic here
}