#pragma once
#include "String.h"
#include <filesystem>
using namespace std;

struct RowEntry
{
	long long rowIndex;
	String name;
	int age;
	String gender;
	String bloodType;
	String medicalCondition;
	String dateOfAdmission;
	String doctor;
	String hospital;
	String insuranceProvider;
	double billingAmount;
	int roomNumber;
	String admissionType;
	String dischargeDate;
	String medication;
	String testResults;

	//writing
	friend ostream& operator<<(ostream& os, const RowEntry& row)
	{
		os << row.name << ',' << row.age << ',' << row.gender << ',' << row.bloodType << ','
			<< row.medicalCondition << ',' << row.dateOfAdmission << ',' << row.doctor << ','
			<< row.hospital << ',' << row.insuranceProvider << ',' << row.billingAmount << ','
			<< row.roomNumber << ',' << row.admissionType << ',' << row.dischargeDate << ','
			<< row.medication << ',' << row.testResults;
		return os;
	}

	//reading
    friend istream& operator>>(istream& is, RowEntry& row) {
        char delimiter;
        getline(is, row.name, ',');
        is >> row.age >> delimiter;
        getline(is, row.gender, ',');
        getline(is, row.bloodType, ',');
        getline(is, row.medicalCondition, ',');
        getline(is, row.dateOfAdmission, ',');
        getline(is, row.doctor, ',');
        getline(is, row.hospital, ',');
        getline(is, row.insuranceProvider, ',');
        is >> row.billingAmount >> delimiter;
        is >> row.roomNumber >> delimiter;
        getline(is, row.admissionType, ',');
        getline(is, row.dischargeDate, ',');
        getline(is, row.medication, ',');
        getline(is, row.testResults);
        return is;
    }
};
