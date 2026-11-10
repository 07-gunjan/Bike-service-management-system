# 🏍️ Bike Service Management System

### A C++ Based Console Application for Managing Bike Service Records

A simple, efficient and user-friendly **Bike Service Management System** developed using C++. This project helps manage bike service registrations, customer information, service status and billing through a menu-driven console interface.

The system uses Object-Oriented Programming (OOP) concepts and file handling to organize and maintain service records.

---

## 📌 Project Overview

Managing bike service records manually can be time-consuming and difficult to maintain. This project provides a basic computerized solution to register bikes, track their service progress, search records and calculate service bills.

It is designed as an academic project to demonstrate practical implementation of C++ programming concepts.

## ✨ Features

- **Bike Registration:** Register new bikes with customer details.
- **View All Records:** Display all registered bike service records.
- **Search Bike:** Find a bike using its registration number.
- **Service Status Management:** Update service status as Pending, In Progress or Completed.
- **Automatic Billing:** Calculate service charges according to the selected service plan.
- **Duplicate Registration Check:** Prevent duplicate vehicle registration numbers.
- **Data Persistence:** Save and load service records using file handling.
- **Input Validation:** Handle invalid menu choices and empty inputs.

## 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C++ | Core programming language |
| OOP | Classes, inheritance and polymorphism |
| File Handling | Storing and retrieving records |
| STL | Vector, algorithms and smart pointers |
| Standard Library | Input/output and string operations |

## 💰 Service Plans & Pricing

| Service Type | Price |
|---|---:|
| Basic Service | ₹500 |
| Full Service | ₹1,200 |
| Repair Service | ₹800 |

## 📋 Application Menu

The application provides the following options:

1. Register New Bike
2. View All Service Records
3. Search Bike
4. Update Service Status
5. Calculate / View Bill
6. Exit

## 🧠 OOP Concepts Implemented

This project demonstrates important Object-Oriented Programming concepts:

- **Abstraction:** An abstract `ServicePlan` class defines the service plan interface.
- **Inheritance:** `BasicService`, `FullService` and `RepairService` inherit from `ServicePlan`.
- **Polymorphism:** Virtual functions and method overriding are used to calculate service costs.
- **Encapsulation:** The `BikeService` class manages customer and service information using private data members.

## ⚙️ Installation & Execution

### Prerequisites

- A computer with Windows, Linux or macOS.
- A C++ compiler (GCC or MinGW).
- C++17 or later support.

### Step 1: Clone the Repository

```bash
git clone https://github.com/07-gunjan/Bike-service-management-system.git
```

### Step 2: Open the Project Directory

```bash
cd Bike-service-management-system
```

### Step 3: Compile the Program

```bash
g++ -std=c++17 main.cpp -o bike_service
```

### Step 4: Run the Application

**Windows:**
```bash
bike_service.exe
```

**Linux / macOS:**
```bash
./bike_service
```

## 💾 Data Storage

The application uses a text file named `service_records.txt` to store bike service information.

- Records are saved automatically after registration.
- Updated service statuses are saved to the file.
- Existing records are loaded when the application starts.
- The file is created automatically when records are first saved.

## 📂 Project Structure

```text
Bike-service-management-system/
│
├── main.cpp
├── service_records.txt
└── README.md
```

*Note: `service_records.txt` is generated automatically when the application saves records.*

## 🚀 Future Improvements

Some features that could be added in future versions:

- Graphical User Interface (GUI).
- Database integration using MySQL.
- Admin and customer login system.
- Online appointment booking.
- Service history and reports.
- Custom service pricing.

## 👨‍💻 Project Information

**Project Name:** Bike Service Management System

**Language:** C++

**Project Type:** Console-Based Application

**Domain:** Bike Service Management

**Repository:** [GitHub – Bike Service Management System](https://github.com/07-gunjan/Bike-service-management-system)

---

### ⭐ Support

If you find this project useful, consider giving the repository a star on GitHub!

**Thank you for visiting our project!** 🏍️
