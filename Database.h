#ifndef DATABASE_H
#define DATABASE_H

#include "vehicle.h"
#include "user.h"
#include "trip.h"
#include "table.h"
#include "error.h"

#include <string>
#include <vector>

class Database {
private:
    Table<Vehicle>* vehicleTable;
    Table<User>* userTable;
    Table<Trip>* tripTable;

    void fetchAllVehicles();
    void fetchAllUsers();
    void fetchAllTrips();
    void cleanUp();

public:
    Database();
    ~Database();

    const Table<Vehicle>* getVehicleRef() const;
    const Table<User>* getUserRef() const;
    const Table<Trip>* getTripRef() const;

    const Vehicle* getVehicle(std::string registrationNo) const;
    const User* getUser(std::string contactNo) const;

    std::vector<const Vehicle*> getVehicle(Date startDate, Date endDate, VehicleType type) const;

    template <class T>
    void addNewRecord(T* record);

    template <class T>
    void updateRecord(T* record);
};

#endif