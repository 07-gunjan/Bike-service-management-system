
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cctype>

using namespace std;

const string FILE_NAME = "service_records.txt";

// ---------- Helper Functions ----------

string cleanInput(string text) {
    replace(text.begin(), text.end(), '|', '/');
    return text;
}

string toUpperCase(string text) {
    transform(text.begin(), text.end(), text.begin(),
              [](unsigned char c) { return toupper(c); });
    return text;
}

string readText(const string& prompt) {
    string value;

    while (true) {
        cout << prompt;
        getline(cin, value);

        value = cleanInput(value);

        if (value.find_first_not_of(" \t") != string::npos) {
            return value;
        }

        cout << "Input cannot be empty. Try again.\n";
    }
}

int readChoice(const string& prompt, int minimum, int maximum) {
    int choice;

    while (true) {
        cout << prompt;

        if (cin >> choice && choice >= minimum &&
            choice <= maximum) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }

        cout << "Invalid choice. Enter a number from "
             << minimum << " to " << maximum << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// ---------- Abstract Base Class ----------

class ServicePlan {
public:
    virtual string getName() const = 0;
    virtual double calculateCost() const = 0;

    virtual ~ServicePlan() = default;
};

// ---------- Derived Classes ----------

class BasicService : public ServicePlan {
public:
    string getName() const override {
        return "Basic Service";
    }

    double calculateCost() const override {
        return 500.0;
    }
};

class FullService : public ServicePlan {
public:
    string getName() const override {
        return "Full Service";
    }

    double calculateCost() const override {
        return 1200.0;
    }
};

class RepairService : public ServicePlan {
public:
    string getName() const override {
        return "Repair Service";
    }

    double calculateCost() const override {
        return 800.0;
    }
};

unique_ptr<ServicePlan> createServicePlan(const string& type) {
    if (type == "Basic Service")
        return make_unique<BasicService>();

    if (type == "Full Service")
        return make_unique<FullService>();

    return make_unique<RepairService>();
}

// ---------- Bike Service Record Class ----------

class BikeService {
private:
    int id;
    string customerName;
    string phone;
    string bikeModel;
    string registrationNo;
    string serviceType;
    string status;

public:
    BikeService(int recordId, string customer, string mobile,
                string model, string registration,
                string service, string serviceStatus)
        : id(recordId),
          customerName(customer),
          phone(mobile),
          bikeModel(model),
          registrationNo(registration),
          serviceType(service),
          status(serviceStatus) {}

    int getId() const {
        return id;
    }

    string getRegistrationNo() const {
        return registrationNo;
    }

    string getStatus() const {
        return status;
    }

    void setStatus(const string& newStatus) {
        status = newStatus;
    }

    double calculateBill() const {
        auto plan = createServicePlan(serviceType);
        return plan->calculateCost();
    }

    void display() const {
        cout << "\n----------------------------------------\n";
        cout << "          BIKE SERVICE DETAILS\n";
        cout << "----------------------------------------\n";
        cout << "Service ID      : " << id << '\n';
        cout << "Customer Name   : " << customerName << '\n';
        cout << "Phone Number    : " << phone << '\n';
        cout << "Bike Model      : " << bikeModel << '\n';
        cout << "Registration No : " << registrationNo << '\n';
        cout << "Service Type    : " << serviceType << '\n';
        cout << "Service Status  : " << status << '\n';
        cout << fixed << setprecision(2);
        cout << "Service Bill    : Rs. " << calculateBill() << '\n';
        cout << "----------------------------------------\n";
    }

    string toFileString() const {
        ostringstream out;
        out << id << '|'
            << customerName << '|'
            << phone << '|'
            << bikeModel << '|'
            << registrationNo << '|'
            << serviceType << '|'
            << status;
        return out.str();
    }
};

// ---------- Main Management System ----------

class ServiceManagementSystem {
private:
    vector<BikeService> records;
    int nextId = 1;

    void saveRecords() const {
        ofstream file(FILE_NAME);

        if (!file) {
            cout << "Error: Could not save records.\n";
            return;
        }

        for (const auto& record : records) {
            file << record.toFileString() << '\n';
        }
    }

    void loadRecords() {
        ifstream file(FILE_NAME);

        if (!file) {
            return; // First run: no file exists yet.
        }

        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string fields[7];

            bool valid = true;

            for (int i = 0; i < 7; i++) {
                if (!getline(ss, fields[i], '|')) {
                    valid = false;
                    break;
                }
            }

            if (!valid)
                continue;

            // Reject lines containing unexpected extra fields.
            string extra;
            if (getline(ss, extra, '|'))
                continue;

            try {
                int recordId = stoi(fields[0]);

                if (recordId < 1 ||
                    (fields[5] != "Basic Service" &&
                     fields[5] != "Full Service" &&
                     fields[5] != "Repair Service") ||
                    (fields[6] != "Pending" &&
                     fields[6] != "In Progress" &&
                     fields[6] != "Completed")) {
                    continue;
                }

                records.emplace_back(
                    recordId, fields[1], fields[2],
                    fields[3], fields[4], fields[5], fields[6]
                );

                nextId = max(nextId, recordId + 1);
            }
            catch (...) {
                // Skip malformed records.
                continue;
            }
        }
    }

    int findByRegistration(const string& registration) const {
        string target = toUpperCase(registration);

        for (int i = 0; i < static_cast<int>(records.size()); i++) {
            if (toUpperCase(records[i].getRegistrationNo()) == target)
                return i;
        }

        return -1;
    }

    void registerBike() {
        cout << "\n========== REGISTER BIKE ==========\n";

        string customer = readText("Customer name: ");
        string phone = readText("Phone number: ");
        string model = readText("Bike model: ");
        string registration = toUpperCase(
            readText("Registration number: ")
        );

        if (findByRegistration(registration) != -1) {
            cout << "This registration number already exists.\n";
            return;
        }

        cout << "\nChoose service type:\n";
        cout << "1. Basic Service - Rs. 500\n";
        cout << "2. Full Service  - Rs. 1200\n";
        cout << "3. Repair Service - Rs. 800\n";

        int choice = readChoice("Enter choice: ", 1, 3);

        string service;

        if (choice == 1)
            service = "Basic Service";
        else if (choice == 2)
            service = "Full Service";
        else
            service = "Repair Service";

        records.emplace_back(
            nextId++, customer, phone, model,
            registration, service, "Pending"
        );

        saveRecords();

        cout << "\nBike registered successfully!\n";
        records.back().display();
    }

    void viewAllRecords() const {
        cout << "\n========== ALL SERVICE RECORDS ==========\n";

        if (records.empty()) {
            cout << "No service records found.\n";
            return;
        }

        for (const auto& record : records) {
            record.display();
        }
    }

    void searchBike() const {
        cout << "\n========== SEARCH BIKE ==========\n";

        string registration = readText(
            "Enter registration number: "
        );

        string target = toUpperCase(registration);
        bool found = false;

        for (const auto& record : records) {
            if (toUpperCase(record.getRegistrationNo()) == target) {
                record.display();
                found = true;
                break;
            }
        }

        if (!found)
            cout << "No bike found with that registration number.\n";
    }

    void updateStatus() {
        cout << "\n========== UPDATE SERVICE STATUS ==========\n";

        string registration = toUpperCase(
            readText("Enter registration number: ")
        );

        int index = findByRegistration(registration);

        if (index == -1) {
            cout << "Bike record not found.\n";
            return;
        }

        cout << "\n1. Pending\n";
        cout << "2. In Progress\n";
        cout << "3. Completed\n";

        int choice = readChoice("Select new status: ", 1, 3);

        string newStatus;

        if (choice == 1)
            newStatus = "Pending";
        else if (choice == 2)
            newStatus = "In Progress";
        else
            newStatus = "Completed";

        records[index].setStatus(newStatus);
        saveRecords();

        cout << "Service status updated successfully!\n";
        records[index].display();
    }

    void displayBill() const {
        cout << "\n========== SERVICE BILL ==========\n";

        string registration = toUpperCase(
            readText("Enter registration number: ")
        );

        int index = findByRegistration(registration);

        if (index == -1) {
            cout << "Bike record not found.\n";
            return;
        }

        records[index].display();
    }

public:
    ServiceManagementSystem() {
        loadRecords();
    }

    void run() {
        int choice;

        do {
            cout << "\n========================================\n";
            cout << "      BIKE SERVICE MANAGEMENT SYSTEM\n";
            cout << "========================================\n";
            cout << "1. Register New Bike\n";
            cout << "2. View All Service Records\n";
            cout << "3. Search Bike\n";
            cout << "4. Update Service Status\n";
            cout << "5. Calculate / View Bill\n";
            cout << "6. Exit\n";
            cout << "========================================\n";

            choice = readChoice("Enter your choice: ", 1, 6);

            switch (choice) {
                case 1:
                    registerBike();
                    break;

                case 2:
                    viewAllRecords();
                    break;

                case 3:
                    searchBike();
                    break;

                case 4:
                    updateStatus();
                    break;

                case 5:
                    displayBill();
                    break;

                case 6:
                    saveRecords();
                    cout << "Records saved. Thank you!\n";
                    break;
            }

        } while (choice != 6);
    }
};

// ---------- Main Function ----------

int main() {
    ServiceManagementSystem system;
    system.run();

    return 0;
}
