#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>   
using namespace std;

struct Booking {
	int roomNo, readroomNo;
	int customerID, readcustid;
	int checkIn, readcheckin;
	int checkOut, readcheckout;
	int maxDaysIn;
	int checkInMonth;
	int checkOutMonth;
	float bill, readbill;
	string status = "confirmed", readStatus;
	int checkInHour;
	int checkOutHour;
	int readCheckInHour;
	int readCheckOutHour;
};

void MakeBooking()
{
	rooms R;
	Booking B;

	ofstream outFile("Bookings.txt", ios::app);

	if (outFile.is_open())
	{
		
		bool validCustomer = false;
		cout << "Enter Customer ID: ";
		cin >> B.customerID;

		customer C;
		ifstream inFile("Customers.txt", ios::in);

		if (inFile.is_open())
		{
			while (!inFile.eof())
			{
				string line;
				getline(inFile, line);
				if (line.empty()) continue;

				int pos1 = line.find('|');
				int pos2 = line.find('|', pos1 + 1);

				C.readCustID = stoi(line.substr(0, pos1));
				C.readName = line.substr(pos1 + 1, (pos2 - pos1) - 1);
				C.readPassport = line.substr(pos2 + 1);

				if (B.customerID == C.readCustID) {
					validCustomer = true;
					break;
				}
			}
			inFile.close();
			if (!validCustomer) {
				cout << "customer ID not found, please add customer details first." << endl;
				WriteFor_Customers();
			}


			do {
				cout << "Enter check-in month (1-12): ";
				cin >> B.checkInMonth;

				if (B.checkInMonth < 1 || B.checkInMonth > 12)
					cout << "Invalid month! Enter again.\n";

			} while (B.checkInMonth < 1 || B.checkInMonth > 12);

			cout << "Enter check-in date: ";
			cin >> B.checkIn;
			int checkinhour;
			string checkInampm;

			do {
				cout << "Enter check-in hour (2-12): ";
				cin >> checkinhour;

				cout << "Enter AM/PM: ";
				cin >> checkInampm;

				
				if (checkinhour < 1 || checkinhour > 12)
				{
					cout << "Invalid hour! Enter between 1-12\n";
					continue;
				}

				
				if (checkInampm == "PM" || checkInampm == "pm")
				{
					if (checkinhour != 12)
						checkinhour += 12;
				}
				else if (checkInampm == "AM" || checkInampm == "am")
				{
					if (checkinhour == 12)
						checkinhour = 0;
				}
				else
				{
					cout << "Invalid AM/PM! Enter AM or PM\n";
					continue;
				}

				B.checkInHour = checkinhour;
				break;

			} while (true);


			int maxDaysIn = getDaysInMonth(B.checkInMonth);

			while (B.checkIn < 1 || B.checkIn > maxDaysIn)
			{
				cout << "Invalid date for this month! Enter again: ";
				cin >> B.checkIn;
			}

			do {
				cout << "Enter check-out month (1-12): ";
				cin >> B.checkOutMonth;

				if (B.checkOutMonth < 1 || B.checkOutMonth > 12)
					cout << "Invalid month! Enter again.\n";

			} while (B.checkOutMonth < 1 || B.checkOutMonth > 12);

			cout << "Enter check-out date: ";
			cin >> B.checkOut;
			

			int checkouthour;
			string checkOutampm;

			do {
				cout << "Enter check-out hour (1-12): ";
				cin >> checkouthour;

				cout << "Enter AM/PM: ";
				cin >> checkOutampm;

				if (checkouthour < 1 || checkouthour > 12)
				{
					cout << "Invalid hour! Enter between 1-12\n";
					continue;
				}

				if (checkOutampm == "PM" || checkOutampm == "pm")
				{
					if (checkouthour != 12)
						checkouthour += 12;
				}
				else if (checkOutampm == "AM" || checkOutampm == "am")
				{
					if (checkouthour == 12)
						checkouthour = 0;
				}
				else
				{
					cout << "Invalid AM/PM! Enter AM or PM\n";
					continue;
				}

				B.checkOutHour = checkouthour;
				break;

			} while (true);

			int maxDaysOut = getDaysInMonth(B.checkOutMonth);

			while (B.checkOut < 1 || B.checkOut > maxDaysOut)
			{
				cout << "Invalid date for this month! Enter again: ";
				cin >> B.checkOut;
			}

			bool validDates = false;

			while (!validDates)
			{
				if (B.checkOutMonth < B.checkInMonth)
				{
					cout << "Check-out month cannot be before check-in month!\n";
				}
				else if (B.checkOutMonth == B.checkInMonth && B.checkOut <= B.checkIn)
				{
					cout << "Check-out must be after check-in in same month!\n";
				}
				else
				{
					validDates = true;
					break;
				}

				cout << "Enter check-out month: ";
				cin >> B.checkOutMonth;

				cout << "Enter check-out date: ";
				cin >> B.checkOut;
			}

			string bookChoice;
			string addMore;

			int ROOMNO, count = 0;
			double totalbill = 0;
			int nights = 0;
			int roomCost = 0;

			if (B.checkInMonth == B.checkOutMonth)
			{
				nights = B.checkOut - B.checkIn;
			}
			else
			{
				int daysInCheckInMonth = getDaysInMonth(B.checkInMonth);
			    nights = (daysInCheckInMonth - B.checkIn ) + B.checkOut;
			}

			double extraChargeDays = 0;

			if (B.checkInHour < 14)
			{
				extraChargeDays += 0.5;
			}

			if (B.checkOutHour > 12 && B.checkOutHour<=18)
			{
				extraChargeDays += 0.5;
			}
			else if (B.checkOutHour > 18) {
				extraChargeDays += 1;                                                                                                                                           
			}

			double totalDays = nights + extraChargeDays;

			if (totalDays < 1)
				totalDays = 1;

			while (addMore != "n")
			{
				bool validType = false;
				do {
					ROOMNO = search_rooms();
					if (ROOMNO == 0) {
						cout << "Do you want to try searching again? (y/n): ";

						do {
							cin >> addMore;

							for (int i = 0; i < addMore.length(); i++)
								addMore[i] = tolower(addMore[i]);

							if (addMore == "y" || addMore == "n")
								validType = true;
							else
								cout << "Invalid input! Enter (Y/N): ";

						} while (!validType);
					}
				} while (ROOMNO == 0 && addMore != "n");

				if (ROOMNO == 0) break;

				cout << "Do you want to book this room? (y/n): ";

				do {
					cin >> bookChoice;
					for (int i = 0; i < bookChoice.length(); i++)
						bookChoice[i] = tolower(bookChoice[i]);

					if (bookChoice == "y" || bookChoice == "n")
						validType = true;
					else
						cout << "Invalid input! Enter Y or N only: ";

				} while (!validType);



				if (bookChoice == "n") {
					cout << "User don't want to book room." << endl;
					break;
				}
				count++;

				if (!checkAvailability(ROOMNO)) {
					cout << "Room not available!" << endl;
					continue;
				}

				ifstream inFile("Rooms.txt", ios::in);
				

				while (!inFile.eof()) {
					string line;
					getline(inFile, line);
					if (line.empty()) continue;

					int pos1 = line.find('|');
					int pos2 = line.find('|', pos1 + 1);
					int pos3 = line.find('|', pos2 + 1);
					int pos4 = line.find('|', pos3 + 1);
					int pos5 = line.find('|', pos4 + 1);

					R.readRoomNo = stoi(line.substr(0, pos1));
					R.readType = line.substr(pos1 + 1, (pos2 - pos1) - 1);
					R.readAC_status = line.substr(pos2 + 1, (pos3 - pos2) - 1);
					R.readmeal_status = line.substr(pos3 + 1, (pos4 - pos3) - 1);
					R.readstatus = line.substr(pos4 + 1, (pos5 - pos4) - 1);
					R.readCost = stoi(line.substr(pos5 + 1));

					if (R.readRoomNo == ROOMNO) {
						roomCost = R.readCost;
						break;
					}
				}
				inFile.close();

				
				double baseBill = roomCost * nights;
				double extraAmount = 0.0;

				if (B.checkInHour < 14)
					extraAmount += 0.5 * roomCost;

				if (B.checkOutHour > 12 && B.checkOutHour <= 18)
					extraAmount += 0.5 * roomCost;
				else if (B.checkOutHour > 18)
					extraAmount += 1.0 * roomCost;

				B.bill = baseBill + extraAmount;

				


				updateRoom(ROOMNO);

				totalbill = totalbill + B.bill;
				outFile << ROOMNO << "|" << B.customerID << "|"
					<< B.checkInMonth << "|" << B.checkIn << "|"
					<< B.checkInHour << "|"  
					<< B.checkOutMonth << "|" << B.checkOut << "|"
					<< B.checkOutHour << "|"  
					<< B.bill << "|" << B.status << endl;

				cout << "Customer ID " << B.customerID << " has successfully booked this room. Total rooms booked: " << count << endl;
				cout << "Do you want to book another room? (y/n): ";

				bool valid = false;
				do {

					cin >> addMore;
					for (int i = 0; i < addMore.length(); i++)
						addMore[i] = tolower(addMore[i]);
					if (addMore == "y" || addMore == "n")
						valid = true;
					else
						cout << "Invalid input! Enter Y or N only: ";
				} while (!valid);
			}

			outFile.close();
			cout << "Booking process completed successfully!" << endl;
			check_bill(B.customerID);

		}
		else
		{
			cout << "Error: opening file for reading." << endl;
		}
	}
	else {
		cout << "Error: opening file for booking." << endl;
	}
}

void viewbookings() {
	Booking B;
	ifstream inFile("Bookings.txt", ios::in);

	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			string line;
			getline(inFile, line);
			if (line.empty()) continue;
			int pos1 = line.find('|');
			int pos2 = line.find('|', pos1 + 1);
			int pos3 = line.find('|', pos2 + 1);
			int pos4 = line.find('|', pos3 + 1);
			int pos5 = line.find('|', pos4 + 1);
			int pos6 = line.find('|', pos5 + 1);
			int pos7 = line.find('|', pos6 + 1);
			int pos8 = line.find('|', pos7 + 1);
			int pos9 = line.find('|', pos8 + 1);

			if (pos1 == -1 || pos2 == -1 || pos3 == -1 || pos4 == -1 ||
				pos5 == -1 || pos6 == -1 || pos7 == -1 ||
				pos8 == -1 || pos9 == -1)
			{
				continue;
			}

			B.readroomNo = stoi(line.substr(0, pos1));
			B.readcustid = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));

			int inMonth = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
			int inDay = stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
			int inHour = stoi(line.substr(pos4 + 1, pos5 - pos4 - 1));

			int outMonth = stoi(line.substr(pos5 + 1, pos6 - pos5 - 1));
			int outDay = stoi(line.substr(pos6 + 1, pos7 - pos6 - 1));
			int outHour = stoi(line.substr(pos7 + 1, pos8 - pos7 - 1));

			B.readbill = stod(line.substr(pos8 + 1, pos9 - pos8 - 1));
			B.readStatus = line.substr(pos9 + 1);

			cout << "----------------------------------------" << endl;
			cout << "Room No       : " << B.readroomNo << endl;
			cout << "Customer ID   : " << B.readcustid << endl;

			cout << "Check-In      : "
				<< inDay << "/" << inMonth
				<< " at " << inHour << ":00" << endl;

			cout << "Check-Out     : "
				<< outDay << "/" << outMonth
				<< " at " << outHour << ":00" << endl;

			cout << "Final Bill    : " << B.readbill << endl;
			cout << "Status        : " << B.readStatus << endl;
			cout << "----------------------------------------" << endl;

		}
		inFile.close();
	}
	else {
		cout << "error in opening file for read." << endl;
	}
}
void cancel_booking()
{
	Booking B;
	ifstream inFile("Bookings.txt", ios::in);

	if (inFile.is_open())
	{
		int roomno, id;
		bool found = false;

		cout << "enter customer id:";
		bool validCID = false;
		do {
			cin >> id;
			if (cin.fail()) {
				cout << "Invalid input! Customer ID must be numeric: ";
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else validCID = true;
		} while (!validCID);


		cout << "Enter room no to cancel your booking: ";
		bool validRoomNo = false;
		do {
			cin >> roomno;
			if (cin.fail()) {
				cout << "Invalid input! room number must be numeric: ";
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else validRoomNo = true;
		} while (!validRoomNo);


		while (!inFile.eof())
		{
			string line;
			getline(inFile, line);
			if (line.empty()) continue;

			int pos1 = line.find('|');
			int pos2 = line.find('|', pos1 + 1);
			int pos3 = line.find('|', pos2 + 1);
			int pos4 = line.find('|', pos3 + 1);
			int pos5 = line.find('|', pos4 + 1);

			B.readroomNo = stoi(line.substr(0, pos1));
			B.readcustid = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
			B.readcheckin = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
			B.readcheckout = stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
			B.readbill = stof(line.substr(pos4 + 1, pos5 - pos4 - 1));
			B.readStatus = line.substr(pos5 + 1);

			if (roomno == B.readroomNo && id == B.readcustid)
			{
				cancel_room(roomno);
				B.readStatus = "cancelled";
				found = true;
				break;
			}
		}

		inFile.close();

		if (found)
		{
			ofstream outFile("Bookings.txt", ios::app);
			if (outFile.is_open()) {
				outFile << B.readroomNo << "|" << B.readcustid << "|"
					<< B.readcheckin << "|" << B.readcheckout << "|"
					<< B.readbill << "|" << B.readStatus << endl;
			}
			outFile.close();

			cout << "Booking cancelled successfully!" << endl;
		}
		else
		{
			cout << "booking not found!" << endl;
		}
	}
	else
	{
		cout << "Error: opening file for reading." << endl;
	}
}

void check_bill(int custid)
{
	Booking B;
	int checkInMonth = 0, checkOutMonth = 0;
	double finalBill = 0;
	double extraCharge = 0.0;
	double totalExtraCharges = 0.0;
	int checkInHour = 0, checkOutHour = 0;


	ifstream inFile("Bookings.txt");
	if (!inFile.is_open())
	{
		cout << "Error: opening in booking file." << endl;
		return;
	}

	int count = 0, totalDays = 0;
	int checkIn = 0, checkOut = 0;

	string line;
	while (getline(inFile, line)) {

		if (line.empty()) continue;

		int pos1 = line.find('|');
		int pos2 = line.find('|', pos1 + 1);
		int pos3 = line.find('|', pos2 + 1);
		int pos4 = line.find('|', pos3 + 1);
		int pos5 = line.find('|', pos4 + 1);
		int pos6 = line.find('|', pos5 + 1);
		int pos7 = line.find('|', pos6 + 1);
		int pos8 = line.find('|', pos7 + 1);
		int pos9 = line.find('|', pos8 + 1);

		if (pos1 == -1 || pos2 == -1 || pos3 == -1 || pos4 == -1 ||
			pos5 == -1 || pos6 == -1 || pos7 == -1 ||
			pos8 == -1 || pos9 == -1)
		{
			continue;
		}


		B.readroomNo = stoi(line.substr(0, pos1));
		B.readcustid = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));

		checkInMonth = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
		checkIn = stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
		checkInHour = stoi(line.substr(pos4 + 1, pos5 - pos4 - 1));
		checkOutMonth = stoi(line.substr(pos5 + 1, pos6 - pos5 - 1));

		checkOut = stoi(line.substr(pos6 + 1, pos7 - pos6 - 1));

	    checkOutHour = stoi(line.substr(pos7 + 1, pos8 - pos7 - 1));

		string billStr = line.substr(pos8 + 1, pos9 - pos8 - 1);
		if (billStr.empty()) continue;

		try {
			B.readbill = stod(billStr);
		}
		catch (...) {
			continue; 
		}


		B.readStatus = line.substr(pos9 + 1);

		
		if (B.readcustid == custid && B.readStatus == "confirmed")
		{
			count++;
			int nights = 0;
			if (checkInMonth == checkOutMonth)
			{
				 nights= checkOut - checkIn ;
			}
			else
			{
				int daysInMonth = getDaysInMonth(checkInMonth);
				nights = (daysInMonth - checkIn ) + checkOut;
			}

			if (nights < 0) nights = 0;
			
			totalDays += nights;
			
			double extraCharge = 0.0;

			if (checkOutHour < 14)
			{
				extraCharge = 0.0;
			}
			else if (checkOutHour <= 18)
			{
				extraCharge = 0.5;
			}
			else
			{
				extraCharge = 1.0;
			}

			totalExtraCharges += extraCharge;
			finalBill += B.readbill;
		}
	}

	inFile.close();

	if (count == 0)
	{
		cout << "No booking found for this customer." << endl;
		return;
	}


	cout << fixed << setprecision(2);
	cout << endl;
	cout << "============== HOTEL CHECKOUT BILL =============" << endl;
	cout << "Customer ID     : " << custid << endl;
	cout << "Number of rooms : " << count << endl;
	string inFormat = (checkInHour >= 12) ? "PM" : "AM";
	int displayInHour = (checkInHour % 12 == 0) ? 12 : checkInHour % 12;

	string outFormat = (checkOutHour >= 12) ? "PM" : "AM";
	int displayOutHour = (checkOutHour % 12 == 0) ? 12 : checkOutHour % 12;

	cout << "Check In Day    : " << checkIn << endl;
	cout << "Check In Hour   : " << displayInHour << " " << inFormat << endl;

	cout << "Check Out Day   : " << checkOut << endl;
	cout << "Check Out Hour  : " << displayOutHour << " " << outFormat << endl;

	cout << "Total Nights    : " << totalDays << endl;
	cout << "Extra Charges   : " << totalExtraCharges << endl;
	cout << "----------------------------------------------" << endl;
	cout << "TOTAL BILL      : " << finalBill << endl;
	cout << "==============================================" << endl;
}

int getDaysInMonth(int month)
{
	if (month == 2) {
		return 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		return 30;
	}
	else {
		return 31;
	}

}
