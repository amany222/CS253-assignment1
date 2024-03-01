#include <iostream>
#include <vector>
#include <string>
#include <ctime>      // For time-related functions
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;
class Car {
public:
    int id;
    string model;
    bool isAvailable;
    string condition;
    time_t dueDate;  

    Car(int id,string model, bool isAvailable,string condition = "Good")
        : id(id), model(model), isAvailable(isAvailable), condition(condition), dueDate(0) {}

    void rent(int rentalDays) {
    if (isAvailable) {
        isAvailable = false;
                               
        dueDate = time(0) + rentalDays * 24 * 60 * 60;   // Set due date to rentalDays from now

    } else {
        cout << "Car is not available for rent." << endl;
    }
}

    void returned(string returnCondition) {
        isAvailable = true;
        condition = returnCondition;
        dueDate = 0;  
    }

    void showDueDate() {
        if (dueDate > 0) {
            cout << "Due date: " << ctime(&dueDate);
        } else {
            cout << "This car is not currently rented." << endl;
        }
    }
    
     // Save car data to a file
    void save(std::ofstream& file) {
        file << id << " " << model << " " << isAvailable << " " << condition << " " << dueDate << "\n";
    }

    // Load car data from a file
    void load(std::ifstream& file) {
        std::string line;
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> id >> model >> isAvailable >> condition >> dueDate;
        }
    }
};

class Person {
public:
   string name;
    int id;
    int recordScore;  
    vector<int> rentedCars;

    Person(string name, int id, int recordScore = 75) : name(name), id(id), recordScore(recordScore) {}

    void updateRecord(int daysLate, bool carDamaged) {
        if (daysLate <= 0 && !carDamaged) {
            recordScore = min(100, recordScore + 5);           // Increase recordScore by 5, not exceeding 100
        } else {
            if (daysLate > 0) {
                recordScore -= daysLate * 10;                         // Deduct 10 points per day late
            }
            if (carDamaged) {
                recordScore -= 20;                                  // Deduct 20 points if car is damaged
            }
        }
        
        recordScore = max(0, min(100, recordScore));
    }

    void rentCar(int carId) {
        if (recordScore >= 50) {  
            rentedCars.push_back(carId);
        }
    }
    
};



class Customer : public Person {
public:
    static const int MAX_RENTAL_CARS = 3;                  // Maximum number of cars a customer can rent
    static const int FINE_PER_DAY = 250;                   // Fine imposed per day from the day of return

    int fineDue;

    Customer(string name, int id, int recordScore = 75) : Person(name, id, recordScore), fineDue(0) {}

    void seeAvailableCars(const vector<Car>& cars) {
        for (const auto& car : cars) {
            if (car.isAvailable) {
                cout << "Car ID: " << car.id << ", Model: " << car.model << endl;
            }
        }
    }

    void browseRentedCars() {
        cout << "Currently rented cars: ";
        for (const auto& carId : rentedCars) {
            cout << carId << " ";
        }
        cout << endl;
    }

   void rentCar(int carId, vector<Car>& cars, int rentalDays) {
    if (recordScore >= 50 && rentedCars.size() < MAX_RENTAL_CARS) {
        for (auto& car : cars) {
            if (car.id == carId && car.isAvailable) {
                car.rent(rentalDays);                         // Rent Car for no of rentalDays
                rentedCars.push_back(carId);
                cout << "Car rented successfully." << endl;
                return;
            }
        }
    }
   cout << "Unable to rent car. Please check your record or availability of cars." << endl;
}


    void returnCar(int carId, vector<Car>& cars, string returnCondition) {
    auto it = find(rentedCars.begin(), rentedCars.end(), carId);
    if (it != rentedCars.end()) {
        rentedCars.erase(it);
        for (auto& car : cars) {
            if (car.id == carId) {
                int daysLate = (time(0) - car.dueDate) / (24 * 60 * 60);
                if (daysLate > 0) {
                    fineDue += daysLate * FINE_PER_DAY;
                   cout << "Fine for late return: " << fineDue << endl;
                }
                car.returned(returnCondition);  
                bool carDamaged = returnCondition != "Good";
                updateRecord(daysLate, carDamaged);
                break;
            }
        }
    } else {
        cout << "No record of renting this car." << endl;
    }
}
    void clearDue() {
        fineDue = 0;
    }
    
                                          // Save customer data to a file
    void save(std::ofstream& file) {
        file << id << " " << name << " " << recordScore << " " << fineDue << "\n";
        for (int carId : rentedCars) {
            file << carId << " ";
        }
        file << "\n";
    }

                                         // Load customer data from a file
    void load(std::ifstream& file) {
        std::string line;
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> id >> name >> recordScore >> fineDue;
            while (iss >> line) {
                rentedCars.push_back(std::stoi(line));
            }
        }
    }
};


class Employee : public Person {
public:
    static const int MAX_RENTAL_CARS = 3;  
    static const int FINE_PER_DAY = 100;  
    static constexpr double DISCOUNT = 0.15;

    int fineDue;

    Employee(string name, int id, int recordScore = 100) : Person(name, id, recordScore), fineDue(0) {}

    void seeAvailableCars(const vector<Car>& cars) {
        for (const auto& car : cars) {
            if (car.isAvailable) {
                cout << "Car ID: " << car.id << ", Model: " << car.model << endl;
            }
        }
    }

    void browseRentedCars() {
        cout << "Currently rented cars: ";
        for (const auto& carId : rentedCars) {
           cout << carId << " ";
        }
       cout << endl;
    }

    void rentCar(int carId, vector<Car>& cars, int rentalDays) {
        if (recordScore >= 50 && rentedCars.size() < MAX_RENTAL_CARS) {
            for (auto& car : cars) {
                if (car.id == carId && car.isAvailable) {
                    car.rent(rentalDays);  
                    rentedCars.push_back(carId);
                    cout << "Car rented successfully with 15% Discount." << endl;
                    return;
                }
            }
        }
        cout << "Unable to rent car. Please check your record or availability of cars." << endl;
    }

    void returnCar(int carId, vector<Car>& cars, string returnCondition) {
        auto it = find(rentedCars.begin(), rentedCars.end(), carId);
        if (it != rentedCars.end()) {
            rentedCars.erase(it);
            for (auto& car : cars) {
                if (car.id == carId) {
                    int daysLate = (time(0) - car.dueDate) / (24 * 60 * 60);
                    if (daysLate > 0) {
                        fineDue += daysLate * FINE_PER_DAY;
                        cout << "Fine for late return: " << fineDue << endl;
                    }
                    car.returned(returnCondition); 
                    bool carDamaged = returnCondition != "Good";
                    updateRecord(daysLate, carDamaged);
                    break;
                }
            }
        } else {
            cout << "No record of renting this car." << endl;
        }
    }

    void clearDue() {
        fineDue = 0;
    }
    
                                       // Save Employee data to a file
    void save(std::ofstream& file) {
        file << id << " " << name << " " << recordScore << " " << fineDue << "\n";
        for (int carId : rentedCars) {
            file << carId << " ";
        }
        file << "\n";
    }

                                             // Load Employee data from a file
    void load(std::ifstream& file) {
        std::string line;
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> id >> name >> recordScore >> fineDue;
            while (iss >> line) {
                rentedCars.push_back(std::stoi(line));
            }
        }
    }
    
};

class Manager {
public:
   string name;
    int id;
    vector<Car> cars;
    vector<Customer> customers;
    vector<Employee> employees;

    Manager(string name, int id) : name(name), id(id) {}

    void addCar(Car car) {
        cars.push_back(car);
    }

    void updateCar(int carId, Car updatedCar) {
        for (auto& car : cars) {
            if (car.id == carId) {
                car = updatedCar;
                break;
            }
        }
    }

    void deleteCar(int carId) {
    cars.erase(remove_if(cars.begin(), cars.end(),
                               [carId](const Car& car) { return car.id == carId; }),
                cars.end());
}

    void addCustomer(Customer customer) {
        customers.push_back(customer);
    }

    void updateCustomer(int customerId, Customer updatedCustomer) {
        for (auto& customer : customers) {
            if (customer.id == customerId) {
                customer = updatedCustomer;
                break;
            }
        }
    }

   void deleteCustomer(int customerId) {
    customers.erase(remove_if(customers.begin(), customers.end(),
                                   [customerId](const Customer& customer) { return customer.id == customerId; }),
                    customers.end());
}


    void addEmployee(Employee employee) {
        employees.push_back(employee);
    }

    void updateEmployee(int employeeId, Employee updatedEmployee) {
        for (auto& employee : employees) {
            if (employee.id == employeeId) {
                employee = updatedEmployee;
                break;
            }
        }
    }

   void deleteEmployee(int employeeId) {
    employees.erase(remove_if(employees.begin(), employees.end(),
                                   [employeeId](const Employee& employee) { return employee.id == employeeId; }),
                    employees.end());
}


    void seeAllCars() {
        for (const auto& car : cars) {
            cout << "car ID: " << car.id << ", Model: " << car.model << ", is Available: " << (car.isAvailable ? "Yes" : "No") << endl;
        }
    }

    void seeRentedCars() {
        for (const auto& customer : customers) {
            for (const auto& carId : customer.rentedCars) {
                cout << "car ID: " << carId << " is rented by customer ID: " << customer.id << endl;
            }
        }
        for (const auto& employee : employees) {
            for (const auto& carId : employee.rentedCars) {
                cout << "car ID: " << carId << " is rented by Employee ID: " << employee.id << endl;
            }
        }
    }
                                             
        
};

    int main() {
    
    Manager manager("AMAN", 1);

   
    Car car1(1, "FORD", true);
    Car car2(2, "TATA", true);
    Car car3(3, "HONDA CITY", true);
    Car car4(4, "HYUNDAI", true);
    Car car5(5, "TOYOTA", true);

    
    manager.addCar(car1);
    manager.addCar(car2);
    manager.addCar(car3);
    manager.addCar(car4);
    manager.addCar(car5);

   
    Customer customer1("Customer 1", 1);
    Customer customer2("Customer 2", 2);
    Customer customer3("Customer 3", 3);
    Customer customer4("Customer 4", 4);
    Customer customer5("Customer 5", 5);

   
    manager.addCustomer(customer1);
    manager.addCustomer(customer2);
    manager.addCustomer(customer3);
    manager.addCustomer(customer4);
    manager.addCustomer(customer5);

   
    Employee employee1("Employee 1", 1);
    Employee employee2("Employee 2", 2);
    Employee employee3("Employee 3", 3);
    Employee employee4("Employee 4", 4);
    Employee employee5("Employee 5", 5);

    
    manager.addEmployee(employee1);
    manager.addEmployee(employee2);
    manager.addEmployee(employee3);
    manager.addEmployee(employee4);
    manager.addEmployee(employee5);

   

    
    return 0;
}
