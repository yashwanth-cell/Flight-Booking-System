#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Flight class to handle flight information
class Flight {
public:
    string flightNumber;
    string departureCity;
    string arrivalCity;
    string departureTime;
    string arrivalTime;
    int availableSeats;

    Flight(string flightNum, string depCity, string arrCity, string depTime, string arrTime, int seats)
        : flightNumber(flightNum), departureCity(depCity), arrivalCity(arrCity), departureTime(depTime), arrivalTime(arrTime), availableSeats(seats) {}

    void displayFlight() {
        cout << "Flight Number: " << flightNumber << endl;
        cout << "Departure City: " << departureCity << endl;
        cout << "Arrival City: " << arrivalCity << endl;
        cout << "Departure Time: " << departureTime << endl;
        cout << "Arrival Time: " << arrivalTime << endl;
        cout << "Available Seats: " << availableSeats << endl;
    }
};

// Customer class to manage customer information
class Customer {
public:
    string name;
    string contactInfo;

    Customer(string customerName, string customerContact)
        : name(customerName), contactInfo(customerContact) {}

    void displayCustomer() {
        cout << "Customer Name: " << name << endl;
        cout << "Contact Info: " << contactInfo << endl;
    }
};

// Booking class to handle flight booking and cancellations
class Booking {
private:
    vector<Flight> availableFlights;
    vector<pair<Flight, Customer>> bookedFlights;  // pair of Flight and Customer

public:
    void addFlight(const Flight& flight) {
        availableFlights.push_back(flight);
    }

    void displayAvailableFlights() {
        if (availableFlights.empty()) {
            cout << "No flights available!" << endl;
            return;
        }
        cout << "Available Flights: " << endl;
        for (int i = 0; i < availableFlights.size(); i++) {
            cout << "--------------------------" << endl;
            availableFlights[i].displayFlight();
            cout << "--------------------------" << endl;
        }
    }

    void bookFlight(Customer& customer) {
        string flightNumber;
        cout << "Enter Flight Number to Book: ";
        cin >> flightNumber;
        bool flightFound = false;

        for (int i = 0; i < availableFlights.size(); i++) {
            if (availableFlights[i].flightNumber == flightNumber && availableFlights[i].availableSeats > 0) {
                availableFlights[i].availableSeats--;
                bookedFlights.push_back(make_pair(availableFlights[i], customer));
                cout << "Flight booked successfully!" << endl;
                flightFound = true;
                break;
            }
        }

        if (!flightFound) {
            cout << "Flight not found or no seats available!" << endl;
        }
    }

    void cancelBooking() {
        string flightNumber;
        cout << "Enter Flight Number to Cancel: ";
        cin >> flightNumber;
        bool bookingFound = false;

        for (int i = 0; i < bookedFlights.size(); i++) {
            if (bookedFlights[i].first.flightNumber == flightNumber) {
                bookedFlights[i].first.availableSeats++;
                bookedFlights.erase(bookedFlights.begin() + i);
                cout << "Booking canceled successfully!" << endl;
                bookingFound = true;
                break;
            }
        }

        if (!bookingFound) {
            cout << "Booking not found!" << endl;
        }
    }

    void displayBookedFlights() {
        if (bookedFlights.empty()) {
            cout << "No bookings found!" << endl;
            return;
        }
        cout << "Booked Flights: " << endl;
        for (int i = 0; i < bookedFlights.size(); i++) {
            cout << "--------------------------" << endl;
            bookedFlights[i].first.displayFlight();
            bookedFlights[i].second.displayCustomer();
            cout << "--------------------------" << endl;
        }
    }
};

// Main function to interact with the user
int main() {
    Booking bookingSystem;

    // Adding some flights to the system
    Flight flight1("FL001", "New York", "Los Angeles", "2025-03-01 08:00", "2025-03-01 11:30", 10);
    Flight flight2("FL002", "Los Angeles", "Chicago", "2025-03-01 09:00", "2025-03-01 12:30", 8);
    Flight flight3("FL003", "Chicago", "Miami", "2025-03-01 07:00", "2025-03-01 10:30", 5);
    
    bookingSystem.addFlight(flight1);
    bookingSystem.addFlight(flight2);
    bookingSystem.addFlight(flight3);

    int choice;
    while (true) {
        cout << "\nFlight Booking System\n";
        cout << "1. Display Available Flights\n";
        cout << "2. Book a Flight\n";
        cout << "3. Cancel a Booking\n";
        cout << "4. Display Booked Flights\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                bookingSystem.displayAvailableFlights();
                break;
            }
            case 2: {
                string name, contact;
                cout << "Enter Customer Name: ";
                cin >> name;
                cout << "Enter Customer Contact Info: ";
                cin >> contact;

                Customer customer(name, contact);
                bookingSystem.bookFlight(customer);
                break;
            }
            case 3: {
                bookingSystem.cancelBooking();
                break;
            }
            case 4: {
                bookingSystem.displayBookedFlights();
                break;
            }
            case 5: {
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        }
    }

    return 0;
}
