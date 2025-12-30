#include <bits/stdc++.h>
using namespace std;

class UserVehicle{
    public:
    string UserEmail;
    string namePlate;
    VehicleType type;
};

enum VehicleType{
    Bike,
    Car,
    Truck
};

class Slot{
    public:
    int priorityNo;
    string slotID;
    VehicleType type;

    Slot(int p, string id, VehicleType t)
        : priorityNo(p), slotID(id), type(t) {}

    // For priority_queue (max heap by default)
    bool operator<(const Slot& other) const {
        return priorityNo > other.priorityNo;
    }
};

class Ticket{
    public:
    string ticketID;
    string startTime;
    string slotID;
    string namePlate;
};

enum PaymentType{
    Card,
    Cash,
    UPI
};

class Payment{
    public:
    string paymentID;
    PaymentType type;
    int amount;
};

class ParkingLot{
    priority_queue<Slot> carQ, bikeQ, truckQ;
    void AddSlot(Slot slot){
        if(slot.type == VehicleType::Car){
            carQ.push(slot);
        }
        else if(slot.type == VehicleType::Bike){
            bikeQ.push(slot);
        }
        else{
            truckQ.push(slot);
        }
        // add slot into the DB table
    }

    Ticket AllocateSlot(UserVehicle uv){
        if(uv.type == VehicleType::Bike){
            if(!bikeQ.empty()){
                auto topSlot = bikeQ.top();
                bikeQ.pop();
                // generate ticket
            }
            else{
                cout<<"No slots available\n";
            }
            // check for car and truck slot simpultaneously if
            // reqs says
        }
        else if(uv.type == VehicleType::Car){
            if(!carQ.empty()){
                auto topSlot = carQ.top();
                carQ.pop();
                // generate ticket
            }
            else{
                cout<<"No slots available\n";
            }
            // check for car and truck slot simpultaneously if
            // reqs says
        }
        else{
            if(!truckQ.empty()){
                auto topSlot = truckQ.top();
                truckQ.pop();
                // generate ticket
            }
            else{
                cout<<"No slots available\n";
            }
            // check for car and truck slot simpultaneously if
            // reqs says
        }
    }

    void DeallocateSlot(Ticket ticket){
        // calculate charges
        Slot slot = GetSlotFromDB(ticket.slotID);
        int cost=0, bikeCharges=5, carChages=8, truckCharges=10;
        if(slot.type == VehicleType::Bike){
            int hours = currTime - ticket.startTime;
            cost = hours*bikeCharges;
            bikeQ.push(slot);
        }
        else if(slot.type == VehicleType::Car){
            int hours = currTime - ticket.startTime;
            cost = hours*carChages;
            carQ.push(slot);
        }
        else if(slot.type == VehicleType::Truck){
            int hours = currTime - ticket.startTime;
            cost = hours*truckCharges;
            truckQ.push(slot);
        }
        // initiate payment process
        // Once payment succeed, initiate notification service to share
        // invoice
    }
};

class PaymentStrategy{
    public:
    virtual void pay(int amount) = 0;  // pure virtual
    virtual ~PaymentStrategy() = default;
};

struct CardPayment: public PaymentStrategy{
    void pay(double amount) {
        cout << "Paid ₹" << amount << " using Credit/Debit Card\n";
    }
};

struct CashPayment: public PaymentStrategy{
    void pay(double amount) {
        cout << "Paid ₹" << amount << " in Cash\n";
    }
};

struct UPIPayment: public PaymentStrategy{
    void pay(double amount) {
        cout << "Paid ₹" << amount << " using UPI\n";
    }
};

int main(){


    return 0;
}