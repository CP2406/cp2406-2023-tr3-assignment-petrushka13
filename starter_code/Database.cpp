#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Database.h"

using namespace std;

namespace Records {

	Employee& Database::addEmployee(const string& firstName,
		const string& lastName)
	{
		log("start");
		Employee theEmployee(firstName, lastName);
		theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
		theEmployee.hire();
		mEmployees.push_back(theEmployee);
        log("end");
		return mEmployees[mEmployees.size() - 1];
	}

	Employee& Database::addEmployee(
		const string& firstName,
		const string& middleName,
		const string& lastName)
	{
		log("start");
		Employee theEmployee(firstName, middleName, lastName);
		theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
		theEmployee.hire();
		mEmployees.push_back(theEmployee);
        log("end");
		return mEmployees[mEmployees.size() - 1];
	}

	Employee& Database::getEmployee(int employeeNumber)
	{
		for (auto& employee : mEmployees) {
			if (employee.getEmployeeNumber() == employeeNumber) {
				return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	Employee& Database::getEmployee(const string& firstName, const string& lastName)
	{
		for (auto& employee : mEmployees) {
			if (employee.getFirstName() == firstName &&
				employee.getLastName() == lastName) {
					return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	void Database::displayAll() const
	{
		for (const auto& employee : mEmployees) {
			employee.display();
		}
	}

	void Database::saveToFile(const string& fileName) const
	{
		ofstream dbFile(fileName, ios_base::trunc);
		if (dbFile.fail()) {
			cerr << "Unable to open debug file" << endl;
			return;
		}


        dbFile << "EmployeeNumber";
		dbFile << ", " << "Address";
		dbFile << endl;
		for (const auto& employee : mEmployees) {
			string emplNumStr = to_string(employee.getEmployeeNumber());
			dbFile << emplNumStr;
			string addr = employee.getAddress();

			std::replace(addr.begin(), addr.end(), ',', ' ');

            dbFile << ", " << addr;
			dbFile << endl;
		}
	}

	void Database::displayCurrent() const
	{
		for (const auto& employee : mEmployees) {
			if (employee.isHired())
				employee.display();
		}
	}

	void Database::displayFormer() const
	{
		for (const auto& employee : mEmployees) {
			if (!employee.isHired())
				employee.display();
		}
	}

}
