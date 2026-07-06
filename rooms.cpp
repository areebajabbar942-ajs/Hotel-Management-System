#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>   
using namespace std;

struct rooms
{
	int roomNo;
	string type;
	string AC, AC_status;
	string meal, meal_status;
	string room_status = "Available";
	const int S_cost = 20000;
	const int D_cost = 40000;
	const int Suit_cost = 60000;
	int readRoomNo;
	string readType;
	string readAC_status;
	string readmeal_status;
	string readstatus;
	int readCost;
	const int Meal_cost = 5000;
};

void WriteFor_Rooms()
{
	rooms R;
	ofstream outFile("Rooms.txt", ios::app);


	if (!outFile.is_open()) {
		cout << "Error: Could not open Rooms file for writing." << endl;
		return;
	}
	ifstream inFile("Rooms.txt");
	int roomCount = 0;
	string line;
	while (getline(inFile, line)) {
		if (!line.empty()) roomCount++;
	}
	inFile.close();


	if (roomCount >= 30) {
		cout << "Cannot add more rooms. Maximum 30 rooms allowed." << endl;
		return;
	}

	cout << "Enter room number (numeric): ";
	bool validRoom = false;
	do {
		cin >> R.roomNo;
		if (cin.fail()) {
			cout << "Invalid input! Room no must be numeric: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else validRoom = true;
	} while (!validRoom);


	ifstream chkRoom("Rooms.txt");
	bool roomExists = false;

	while (!chkRoom.eof())
	{
		string line;
		getline(chkRoom, line);
		if (line.empty()) continue;

		int pos = line.find('|');
		int existingRoom = stoi(line.substr(0, pos));

		if (existingRoom == R.roomNo)
		{
			roomExists = true;
			break;
		}
	}
	chkRoom.close();

	if (roomExists)
	{
		cout << "Room number already exists! Enter a different room number." << endl;
		return;
	}

	bool validType = false;
	do {
		cout << "Which type of room would you prefer?(single/double/suite): ";
		cin >> R.type;

		for (int i = 0; i < R.type.length(); i++)
			R.type[i] = tolower(R.type[i]);

		if (R.type == "single" || R.type == "double" || R.type == "suite") {
			validType = true;
		}
		else {
			cout << "Invalid input! Please enter (single/double/suite)" << endl;
		}

	} while (!validType);


	cout << "Do you prefer a room with air conditioning? (enter Y/y for yes or N/n for no): ";

	validType = false;
	do {
		cin >> R.AC;
		for (int i = 0; i < R.AC.length(); i++)
			R.AC[i] = tolower(R.AC[i]);
		if (R.AC == "y" || R.AC == "n")
			validType = true;
		else
			cout << "Invalid input! Enter Y or N only: ";
	} while (!validType);


	cout << "would you like to add meal service to your room? (enter Y/y for yes or N/n for no): ";

	validType = false;
	do {
		cin >> R.meal;
		for (int i = 0; i < R.meal.length(); i++)
			R.meal[i] = tolower(R.meal[i]);

		if (R.meal == "y" || R.meal == "n")
			validType = true;
		else
			cout << "Invalid input! Enter Y or N only: ";

	} while (!validType);


	int cost = 0;
	if (R.type == "single") {
		cost = R.S_cost;
	}
	else if (R.type == "double") {
		cost = R.D_cost;
	}
	else if (R.type == "suite") {
		cost = R.Suit_cost;
	}

	if (R.AC == "y" || R.AC == "Y") {
		R.AC_status = "ac";
	}
	else {
		R.AC_status = "noac";

	}

	if (R.meal == "y" || R.meal == "Y") {
		R.meal_status = "meal";
		cost += R.Meal_cost;
	}
	else {
		R.meal_status = "nomeal";
	}


	outFile << R.roomNo << '|' << R.type << '|' << R.AC_status << '|' << R.meal_status << '|'
		<< R.room_status << '|' << cost << endl;


	outFile.close();
	cout << "Rooms added successfully." << endl;
}


void ReadFrom_Rooms()
{
	rooms R;
	ifstream inFile("Rooms.txt", ios::in);

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

			R.readRoomNo = stoi(line.substr(0, pos1));
			R.readType = line.substr(pos1 + 1, (pos2 - pos1) - 1);
			R.readAC_status = line.substr(pos2 + 1, (pos3 - pos2) - 1);
			R.readmeal_status = line.substr(pos3 + 1, (pos4 - pos3) - 1);
			R.readstatus = line.substr(pos4 + 1, (pos5 - pos4) - 1);
			R.readCost = stoi(line.substr(pos5 + 1));

			cout << "Room No: " << R.readRoomNo << ", type: " << R.readType << ", " << R.readAC_status
				<< ", " << R.readmeal_status << ", " << R.readstatus << ", price is: " << R.readCost << endl;
		}
		inFile.close();
	}
	else
	{
		cout << "Error opening file for read." << endl;
	}
}
int search_rooms() {
	rooms R;
	bool validType = false;
	ifstream inFile("Rooms.txt", ios::in);
	cout << "Which type of room would you prefer?(single/double/suite): ";
	do {
		cin >> R.type;

		if (R.type == "single" || R.type == "double" || R.type == "suite") {
			validType = true;
		}
		else {
			cout << "Invalid room type! Please enter single, double, or suite." << endl;
		}
	} while (validType == false);

	for (int i = 0; i < R.type.length(); i++)
	{
		R.type[i] = tolower(R.type[i]);
	}
	do {
		cout << "Do you prefer your room with air conditioning? (AC / noAC): ";
		cin >> R.AC;

		for (int i = 0; i < R.AC.length(); i++)
			R.AC[i] = tolower(R.AC[i]);

		if (R.AC != "ac" && R.AC != "noac") {
			cout << "Invalid input! Please enter (ac/noac)." << endl;

			cin.clear();
			cin.ignore(1000, '\n');
		}

	} while (R.AC != "ac" && R.AC != "noac");


	do {
		cout << "would you like to add meal service to your room?(meal / nomeal): ";
		cin >> R.meal;

		for (int i = 0; i < R.meal.length(); i++)
			R.meal[i] = tolower(R.meal[i]);

		if (R.meal != "meal" && R.meal != "nomeal") {
			cout << "Invalid input! Please enter (meal/nomeal)." << endl;

			cin.clear();
			cin.ignore(1000, '\n');
		}

	} while (R.meal != "meal" && R.meal != "nomeal");


	bool found = false;
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

			R.readRoomNo = stoi(line.substr(0, pos1));
			R.readType = line.substr(pos1 + 1, (pos2 - pos1) - 1);
			R.readAC_status = line.substr(pos2 + 1, (pos3 - pos2) - 1);
			R.readmeal_status = line.substr(pos3 + 1, (pos4 - pos3) - 1);
			R.readstatus = line.substr(pos4 + 1, (pos5 - pos4) - 1);
			R.readCost = stoi(line.substr(pos5 + 1));

			if (R.type == R.readType && R.AC == R.readAC_status && R.meal == R.readmeal_status && R.readstatus == "Available") {
				found = true;
				cout << "we have room no: " << R.readRoomNo << " " << R.readType << " type , with "
					<< R.readAC_status << " ," << R.readmeal_status << " , " << R.readstatus << " for " << R.readCost << endl;
				return R.readRoomNo;
				break;
			}
		}
		if (found == false) {
			cout << "sorry! no room is available according to your requirements" << endl;
			return 0;
		}
		inFile.close();
	}
	else {
		cout << "Error: could not open rooms file to search." << endl;
	}
}

void updateRoom(int roomNo) {
	ifstream inroom("Rooms.txt", ios::in);
	if (!inroom.is_open()) {
		cout << "Error: Could not open Rooms file for reading." << endl;
		return;
	}
	int NoOfRoom = 0;
	string line;
	while (!inroom.eof()) {
		string line;
		getline(inroom, line);
		if (!line.empty()) {
			NoOfRoom++;
		}
	}
	if (NoOfRoom == 0) {
		cout << "No room is found in file." << endl;;
		inroom.close();
		return;
	}
	inroom.clear();
	inroom.seekg(0);

	int indexRoom = 0;
	rooms* arryRoom = new rooms[NoOfRoom];
	while (!inroom.eof() && indexRoom < NoOfRoom) {
		string line;
		getline(inroom, line);
		if (line.empty())continue;

		int pos1 = line.find('|');
		int pos2 = line.find('|', pos1 + 1);
		int pos3 = line.find('|', pos2 + 1);
		int pos4 = line.find('|', pos3 + 1);
		int pos5 = line.find('|', pos4 + 1);

		arryRoom[indexRoom].readRoomNo = stoi(line.substr(0, pos1));
		arryRoom[indexRoom].readType = line.substr(pos1 + 1, (pos2 - pos1) - 1);
		arryRoom[indexRoom].readAC_status = line.substr(pos2 + 1, (pos3 - pos2) - 1);
		arryRoom[indexRoom].readmeal_status = line.substr(pos3 + 1, (pos4 - pos3) - 1);
		arryRoom[indexRoom].readstatus = line.substr(pos4 + 1, (pos5 - pos4) - 1);
		arryRoom[indexRoom].readCost = stoi(line.substr(pos5 + 1));
		indexRoom++;

	}
	inroom.close();
	bool found = false;
	for (int i = 0; i < NoOfRoom; i++) {
		if (roomNo == arryRoom[i].readRoomNo) {
			found = true;
			if (arryRoom[i].readstatus == "Available") {
				arryRoom[i].readstatus = "Booked";
				cout << "Room booked successfully." << endl;
			}
			else {
				cout << "Room is already booked." << endl;
			}
			break;
		}
	}
	if (!found) {
		cout << "Room not found." << endl;
		delete[] arryRoom;
		return;
	}
	ofstream outroom("Rooms.txt");
	for (int i = 0; i < NoOfRoom; i++) {
		outroom << arryRoom[i].readRoomNo << '|' << arryRoom[i].readType << '|' << arryRoom[i].readAC_status << '|' << arryRoom[i].readmeal_status << '|' << arryRoom[i].readstatus << '|' << arryRoom[i].readCost << endl;
	}
	outroom.close();

	delete[] arryRoom;
}

void cancel_room(int roomno) {
	ifstream inroom("Rooms.txt", ios::in);
	if (!inroom.is_open()) {
		cout << "Error opening file to read room file." << endl;
		return;
	}
	int NoOfRoom = 0;
	string line;
	while (!inroom.eof()) {
		string line;
		getline(inroom, line);
		if (!line.empty()) {
			NoOfRoom++;
		}
	}
	if (NoOfRoom == 0) {
		cout << "No room is found in file." << endl;
		inroom.close();
		return;
	}
	inroom.clear();
	inroom.seekg(0);

	int indexRoom = 0;
	rooms* arryRoom = new rooms[NoOfRoom];
	while (!inroom.eof() && indexRoom < NoOfRoom) {
		string line;
		getline(inroom, line);
		if (line.empty())continue;

		int pos1 = line.find('|');
		int pos2 = line.find('|', pos1 + 1);
		int pos3 = line.find('|', pos2 + 1);
		int pos4 = line.find('|', pos3 + 1);
		int pos5 = line.find('|', pos4 + 1);

		arryRoom[indexRoom].readRoomNo = stoi(line.substr(0, pos1));
		arryRoom[indexRoom].readType = line.substr(pos1 + 1, (pos2 - pos1) - 1);
		arryRoom[indexRoom].readAC_status = line.substr(pos2 + 1, (pos3 - pos2) - 1);
		arryRoom[indexRoom].readmeal_status = line.substr(pos3 + 1, (pos4 - pos3) - 1);
		arryRoom[indexRoom].readstatus = line.substr(pos4 + 1, (pos5 - pos4) - 1);
		arryRoom[indexRoom].readCost = stoi(line.substr(pos5 + 1));
		indexRoom++;

	}
	inroom.close();
	bool found = false;
	for (int i = 0; i < NoOfRoom; i++) {
		if (roomno == arryRoom[i].readRoomNo) {
			found = true;
			if (arryRoom[i].readstatus == "Booked" || arryRoom[i].readstatus == "booked") {
				arryRoom[i].readstatus = "Available";
				cout << "Room canceled successfully." << endl;
			}
			else {
				cout << "Room is already free." << endl;;
			}
			break;
		}
	}
	if (!found) {
		cout << "Room not found." << endl;
		delete[] arryRoom;
		return;
	}
	ofstream outroom("Rooms.txt");
	for (int i = 0; i < NoOfRoom; i++) {
		outroom << arryRoom[i].readRoomNo << '|' << arryRoom[i].readType << '|' << arryRoom[i].readAC_status << '|' << arryRoom[i].readmeal_status << '|' << arryRoom[i].readstatus << '|' << arryRoom[i].readCost << endl;
	}
	outroom.close();

	delete[] arryRoom;
}

bool checkAvailability(int roomNo)
{
	rooms R;

	ifstream inFile("Rooms.txt");
	while (!inFile.eof()) {
		string line;
		getline(inFile, line);
		if (line.empty())continue;
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

		if (roomNo == R.readRoomNo && R.readstatus == "Available") {
			inFile.close();
			return true;
		}

	}
	inFile.close();
	return false;
}


