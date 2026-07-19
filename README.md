 # Hotel-Management-System
Hotels often face difficulties in managing room availability, customer records, bookings, and billing manually, which can lead to errors and inefficient operations. This Hotel Management System provides a simple console-based solution that automates room management, customer registration, booking, billing, and cancellation while securely storing records using file handling. The system improves accuracy, reduces manual work, and makes hotel operations more organized and efficient.

Features:
<br>
Add new rooms,
View all available rooms,
Search rooms based on customer preferences,
Add and manage customer records,
Search customers by ID,
Make room bookings,
View booking details,
Cancel bookings,
Automatic room availability updates,
Hotel bill calculation,
File handling for permanent data storage,
User input validation and error handling

## File Structure

```text
Hotel-Management-System
│
├── main.cpp
│   ├── Structures
│   └── main()
│
├── customer.cpp
│   ├── WriteFor_Customers()
│   ├── ReadFrom_Customers()
│   └── Search_Customer()
│
├── rooms.cpp
│   ├── WriteFor_Rooms()
│   ├── ReadFrom_Rooms()
│   ├── search_rooms()
│   ├── updateRoom()
│   ├── cancel_room()
│   └── checkAvailability()
│
├── booking.cpp
│   ├── getDaysInMonth()
│   ├── MakeBooking()
│   ├── check_bill()
│   ├── viewbookings()
│   └── cancel_booking()
│
├── Customers.txt
├── Rooms.txt
├── Bookings.txt
└── README.md
```

## Concepts Used
- Structures
- Structure Arrays
- Dynamic Arrays
- File Handling
- Searching
- Validation
- Stock Management
