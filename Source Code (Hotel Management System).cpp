#include <iostream>
#include <fstream>  // Used for file handling.
#include <limits>   // It is used to use functions like clear or ignore which help in handlig error.
using namespace std;

struct Guest {   
    string name;
    int roomNumber;
    string checkInDate;
    string checkOutDate;
    long long idCardNumber;
    string phoneNumber;
    int numberOfNights;
    string roomType;
    double billAmount;
};

// Function to check if a string is a valid integer and help to display error messege.
bool isInteger(const string &str) 
{
    for (char c : str) 
	{
        if (!isdigit(c)) 
		{
            return false;
        }
    }
    return true;
}

// Function to check if the format of date is valid or not.
bool isValidDate(const string &date) 
{
    if (date.size() != 10) return false;
    if (date[2] != '/' || date[5] != '/') return false;
    for (int i = 0; i < date.size(); i++) 
	{
        if (i != 2 && i != 5 && !isdigit(date[i])) 
		{
            return false;
        }
    }
    return true;
}

int main() 
{
    const int totalRooms = 20;
    bool rooms[totalRooms] = {false};
    Guest guests[totalRooms];
    int guestCount = 0;
    int choice;
    int roomChoice;
    string userName = "M_Awais";
    string password = "drowssap";
    string inputUserName, inputPassword;
    bool found;

    // Ask user to add username and password using do-while loop.
    do {
        cout << "\t\tPlease Enter Your Username and Password!" << endl;
        cout << "Enter username: ";
        cin >> inputUserName;
        cout << "Enter password: ";
        cin >> inputPassword;

        if (inputUserName != userName || inputPassword != password) 
		{
            cout << "Incorrect credentials. Try again.\n";
        }
    } 
	while (inputUserName != userName || inputPassword != password);

    do {  // Display the main menu.
        cout << "\n\t\t\t\t\t*******************************";
        cout << "\n\t\t\t\t\t  WELLCOME TO HOTEL BALISTAVA";
        cout << "\n\t\t\t\t\t   * HERE IS THE MAIN MENU *";
        cout << "\n\t\t\t\t\t*******************************";
        cout << "\n1. Display Available Rooms\n";
        cout << "2. Book a Room\n";
        cout << "3. Display All Guests\n";
        cout << "4. Check-out\n";
        cout << "5. Save Data to File\n";
        cout << "6. Read Data From File\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1:
                // Display Available Rooms Uisng for loop.
                cout << "\nAvailable Rooms:\n";
                for (int i = 0; i < totalRooms; i++) 
				{
                    if (!rooms[i]) 
					{
                        cout << "Room " << i + 1 << " is available.\n";
                    }
                }
                break;

            case 2:
                // Book a Room and ask for details.
                cout << "Enter room number to book (1 to " << totalRooms << "): ";
                while (!(cin >> roomChoice) || roomChoice < 1 || roomChoice > totalRooms) 
				{
                    cout << "Invalid input. Please enter a valid room number between 1 and " << totalRooms << ".\n";
                    cin.clear();    //Fixes the error in input.
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // cin.ignore clear the remaining invalid input.
                }

                if (rooms[roomChoice - 1]) 
				{
                    cout << "Room " << roomChoice << " is already booked.\n";
                } else 
				{
                    rooms[roomChoice - 1] = true;

                    Guest newGuest;

                    cout << "Enter guest name: ";
                    cin >> newGuest.name;

                    bool validId = false;
                    string idCardNumber;
                    while (!validId) 
					{
                        cout << "Enter guest ID card number (13 digits): ";
                        cin >> idCardNumber;
                        if (idCardNumber.size() == 13 && isInteger(idCardNumber)) 
						{
                            newGuest.idCardNumber = stoll(idCardNumber); // stoll built in function is used to convert string to long long to store large numbers.
                            validId = true;
                        } else {
                            cout << "Invalid ID card number. It should be exactly 13 digits long.\n";
                        }
                    }

                    bool validPhoneNumber = false;
                    while (!validPhoneNumber) {
                        cout << "Enter guest phone number (starts with 0 and 3, 11 digits): ";
                        cin >> newGuest.phoneNumber;
        
                        // Check if phone number has 11 digits and starts with '0' and '3'
                        if (newGuest.phoneNumber.size() == 11 && newGuest.phoneNumber[0] == '0' && newGuest.phoneNumber[1] == '3') 
						{
                        validPhoneNumber = true;
                        } else 
						{
                            cout << "Phone number must start with '0' and '3', and be exactly 11 digits long.\n";
                            }
                        }

                    do {
                        cout << "Enter check-in date (DD/MM/YYYY): ";
                        cin >> newGuest.checkInDate;
                        if (!isValidDate(newGuest.checkInDate)) 
						{
                            cout << "Invalid date format. Please use DD/MM/YYYY.\n";
                        }
                    } while (!isValidDate(newGuest.checkInDate));

                    do {
                        cout << "Enter check-out date (DD/MM/YYYY): ";
                        cin >> newGuest.checkOutDate;
                        if (!isValidDate(newGuest.checkOutDate)) 
						{
                            cout << "Invalid date format. Please use DD/MM/YYYY.\n";
                        }
                    } while (!isValidDate(newGuest.checkOutDate));

                    do {
                        cout << "Enter number of nights: ";
                        cin >> newGuest.numberOfNights;
                        if (cin.fail() || newGuest.numberOfNights <= 0) 
						{
                            cout << "Please enter a valid number of nights (positive integer).\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    } while (newGuest.numberOfNights <= 0);

                    // Select Room Type using switch and calculate price accordingly.
                    int roomTypeChoice;
                    cout << "Select Room Type:\n1. 100$ for Standard Room per night\n2. 200$ for Deluxe Room per night\n3. 300$ for VVIP Room per night\nEnter choice: ";
                    cin >> roomTypeChoice;

                    switch (roomTypeChoice) {
                        case 1:
                            newGuest.roomType = "Standard";
                            newGuest.billAmount = 100.0 * newGuest.numberOfNights;
                            break;
                        case 2:
                            newGuest.roomType = "Deluxe";
                            newGuest.billAmount = 200.0 * newGuest.numberOfNights;
                            break;
                        case 3:
                            newGuest.roomType = "VVIP";
                            newGuest.billAmount = 300.0 * newGuest.numberOfNights;
                            break;
                        default:
                            cout << "Invalid choice. Defaulting to Standard.\n";
                            newGuest.roomType = "Standard";
                            newGuest.billAmount = 100.0 * newGuest.numberOfNights;
                    }

                    newGuest.roomNumber = roomChoice;
                    guests[guestCount] = newGuest;
                    guestCount++;
                    cout << "Room " << roomChoice << " booked for " << newGuest.name << ". Total bill: $" << newGuest.billAmount << endl;
                }
                break;

            case 3:
                // Display All Guests that are check in at that time.
                if (guestCount == 0) {
                    cout << "No guests have checked in yet.\n";
                } else {
                    cout << "\nList of Guests:\n";
                    for (int i = 0; i < guestCount; i++) {
                        cout << "Name: " << guests[i].name;
                        cout << ", \tRoom: " << guests[i].roomNumber;
                        cout << ", \tID: " << guests[i].idCardNumber;
                        cout << ", \tPhone # "<< guests[i].phoneNumber;
                        cout << ", \tCheck-in: " << guests[i].checkInDate;
                        cout << ", \tCheck-out: " << guests[i].checkOutDate;
                        cout << ", \tNights: " << guests[i].numberOfNights;
                        cout << ", \tRoom Type: " << guests[i].roomType;
                        cout << ", \tBill: $" << guests[i].billAmount << endl;
                    }
                }
                break;

            case 4:
                // Check-out the particular guest.
                cout << "Enter room number to check-out (1 to " << totalRooms << "): ";
                while (!(cin >> roomChoice) || roomChoice < 1 || roomChoice > totalRooms) 
				{
                    cout << "Invalid input. Please enter a valid room number between 1 and " << totalRooms << ".\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                found = false;
                for (int i = 0; i < guestCount; i++) 
				{
                    if (guests[i].roomNumber == roomChoice) 
					{
                        found = true;
                        rooms[roomChoice - 1] = false;
                        cout << "Guest " << guests[i].name << " checked out successfully.\n";
                        for (int j = i; j < guestCount - 1; j++) {
                            guests[j] = guests[j + 1];
                        }
                        guestCount--;
                        break;
                    }
                }
                if (!found) 
				{
                    cout << "No guest found in room " << roomChoice << ".\n";
                }
                break;

            case 5:
                // Save Data to File.
                {
                    ofstream out("guests.txt");
                    if (!out) {
                        cout << "Error opening file for writing.\n";
                    } else {
                        for (int i = 0; i < guestCount; i++) 
						{
                            out << guests[i].name << "\n"; 
                            out << guests[i].roomNumber << "\n"; 
                            out << guests[i].checkInDate << "\n"; 
                            out << guests[i].checkOutDate << "\n";
                            out << guests[i].idCardNumber << "\n";
                            out << guests[i].phoneNumber << "\n";
                            out << guests[i].numberOfNights << "\n";
                            out << guests[i].roomType << "\n"; 
                            out << guests[i].billAmount << "\n";
                        }
                        out.close();
                        cout << "Guest data saved to file.\n";
                    }
                }
                break;

            case 6:
                // Read Data from File
                {
                    ifstream in("guests.txt");
                    if (!in) 
					{
                        cout << "Error opening file for reading.\n";
                    } 
					else 
					{
                        string name, roomNumber, checkInDate, checkOutDate, idCardNumber, phoneNumber, roomType;
                        int numberOfNights;
                        double billAmount;

                        while (getline(in, name)) {  // Getline built in function is used to read the complete line from file.
                            getline(in, roomNumber);
                            getline(in, checkInDate);
                            getline(in, checkOutDate);
                            getline(in, idCardNumber);
                            getline(in, phoneNumber);
                            in >> numberOfNights;
                            in.ignore();
                            getline(in, roomType);
                            in >> billAmount;
                            in.ignore();

                            cout << "Name: " << name << "\n";
                            cout << "Room Number: " << roomNumber << "\n";
                            cout << "Check-In Date: " << checkInDate << "\n";
                            cout << "Check-Out Date: " << checkOutDate << "\n";
                            cout << "ID Card Number: " << idCardNumber << "\n";
                            cout << "Phone Number: " << phoneNumber << "\n";
                            cout << "Number of Nights: " << numberOfNights << "\n";
                            cout << "Room Type: " << roomType << "\n";
                            cout << "Bill Amount: " << billAmount << "\n\n";
                        }
                        in.close();
                        cout << "Guest data read from file.\n";
                    }
                }
                break;

            case 7:
                cout << "Exiting the system.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
