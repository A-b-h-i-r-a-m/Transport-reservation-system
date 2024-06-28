#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class TransportReservationSystem {
private:
    string filename;

public:
    TransportReservationSystem(const string& filename) : filename(filename) {}

    void displayMenu() {
        cout<<endl;
        cout << "Transport Reservation System" << endl;
        cout<<"---------------------------------"<<endl;
        
        cout << " 1. Book a seat" << endl;
        cout << " 2. View reservations" << endl;
        cout << " 3. Cancel reservation" << endl;
        cout << " 4. Exit" << endl;
        cout << " Enter your choice: ";
    }

    void bookSeat() {
        string name;
        int seatNumber;

        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter seat number: ";
        cin >> seatNumber;

        ifstream inFile(filename);
        ofstream outFile("temp.txt");

        int seat;
        string passenger;

        bool isSeatBooked = false;

        while (inFile >> seat >> passenger) {
            if (seat == seatNumber) {
                cout << "Seat " << seatNumber << " is already booked by " << passenger << endl;
                isSeatBooked = true;
            }
            outFile << seat << " " << passenger << endl;
        }

        if (!isSeatBooked) {
            outFile << seatNumber << " " << name << endl;
            cout << "Seat " << seatNumber << " booked for " << name << endl;
        }

        inFile.close();
        outFile.close();

        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }

    void viewReservations() {
        ifstream inFile(filename);

        if (!inFile) {
            cout << "No reservations found." << endl;
            return;
        }

        cout << "Seat  Passenger" << endl;
        int seat;
        string passenger;

        while (inFile >> seat >> passenger) {
            cout << seat << "     " << passenger << endl;
        }

        inFile.close();
    }

    void cancelReservation() {
        int seatNumber;
        cout << "Enter seat number to cancel reservation: ";
        cin >> seatNumber;

        ifstream inFile(filename);
        ofstream outFile("temp.txt");

        int seat;
        string passenger;
        bool isCanceled = false;

        while (inFile >> seat >> passenger) {
            if (seat == seatNumber) {
                cout << "Canceled reservation for seat " << seatNumber << " by " << passenger << endl;
                isCanceled = true;
            } else {
                outFile << seat << " " << passenger << endl;
            }
        }

        inFile.close();
        outFile.close();

        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        if (!isCanceled) {
            cout << "No reservation found for seat " << seatNumber << endl;
        }
    }
};

int main() {
    TransportReservationSystem reservationSystem("reservations.txt");

    while (true) {
        int choice;
        reservationSystem.displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                reservationSystem.bookSeat();
                break;
            case 2:
                reservationSystem.viewReservations();
                break;
            case 3:
                reservationSystem.cancelReservation();
                break;
            case 4:
                cout << "THANK YOU!!!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
