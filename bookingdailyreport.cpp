#include "globals.h"
#include "bookingdailyreport.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include "matplotlibcpp.h" // Assuming you have the matplotlibcpp library set up
namespace plt = matplotlibcpp;
using namespace std;

bool checkYearExists(MYSQL* conn, int year) {
    std::string query = "SELECT 1 FROM booking WHERE YEAR(b_date) = " + std::to_string(year) + " LIMIT 1";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Error in executing the query: " << mysql_error(conn) << endl;
        return false;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        cerr << "Error in retrieving results: " << mysql_error(conn) << endl;
        return false;
    }

    bool yearExists = (mysql_num_rows(res) > 0);
    mysql_free_result(res);
    return yearExists;
}

void bookingdailyreport() {
    system("cls");
    system("Color 17");//Blue background, black text


    if (!conn) {
        std::cerr << "Database connection is not established." << std::endl;
        system("pause");
        system("cls");
        adminreportbooking();
    }

    cout << "*********************************************" << endl;
    cout << "|                                           |" << endl;
    cout << "|           Daily Booking report            |" << endl;
    cout << "|                                           |" << endl;
    cout << "*********************************************" << endl << endl;

    int year;
    cout << "Enter the year for the report: ";
    cin >> year;

    if (checkYearExists(conn, year)) {
        int month;
        cout << "Enter the month for the report (1-12): ";
        cin >> month;

        if (month < 1 || month > 12) {
            cerr << "Invalid month! Please enter a month between 1 and 12." << endl;
            system("pause");
            system("cls");
            bookingdailyreport();
        }
        else {
            cout << endl;
            cout << "Generating report, please wait a few seconds..." << endl;
            generatedailyReport(conn, year, month);
        }
    }
    else {
        cerr << "No bookings found for the year " << year << "." << endl;
        system("pause");
        system("cls");
        adminreportbooking();
    }
    mysql_close(conn);
}

void generatedailyReport(MYSQL* conn, int year, int month) {
    std::string query = R"(
        SELECT 
            DAY(b_date) AS day, 
            COUNT(*) AS total_bookings, 
            COUNT(CASE WHEN b_status = 'confirm' THEN 1 END) AS confirmed_bookings, 
            COUNT(CASE WHEN b_status = 'reject' THEN 1 END) AS rejected_bookings 
        FROM 
            booking 
        WHERE 
            YEAR(b_date) = )" + std::to_string(year) + R"( AND MONTH(b_date) = )" + std::to_string(month) + R"(
        GROUP BY 
            day 
        ORDER BY 
            day
    )";

    if (mysql_query(conn, query.c_str())) {
        cerr << "Error in executing the query: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        cerr << "Error in retrieving results: " << mysql_error(conn) << endl;
        return;
    }

    std::vector<int> days;
    std::vector<int> total_bookings;
    std::vector<int> confirmed_bookings;
    std::vector<int> rejected_bookings;

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        days.push_back(atoi(row[0]));
        total_bookings.push_back(atoi(row[1]));
        confirmed_bookings.push_back(atoi(row[2]));
        rejected_bookings.push_back(atoi(row[3]));
    }

    mysql_free_result(res);

    const char* month_names[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Display the table
    cout << endl;
    cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
    cout << " | " << setw(10) << left << "Day:"
        << " | " << setw(15) << left << "\tMonth:"
        << " | " << setw(15) << left << "Year:"
        << " | " << setw(15) << left << "Total Bookings:"
        << " | " << setw(20) << left << "Confirmed Bookings:"
        << " | " << setw(20) << left << "Rejected Bookings:"
        << " | " << endl;
    cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
    for (size_t i = 0; i < days.size(); ++i) {
        cout << " | " << setw(10) << left << std::to_string(days[i])
            << " | " << setw(15) << left  << "\t" + std::string(month_names[month - 1])
            << " | " << setw(15) << left << std::to_string(year)
            << " | " << setw(15) << left  <<  std::to_string(total_bookings[i])
            << " | " << setw(20) << left  << std::to_string(confirmed_bookings[i])
            << " | " << setw(20) << left  <<  std::to_string(rejected_bookings[i])
            << " | " << endl;
        cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
    }

    plt::figure_size(1200, 600);
    plt::bar(days, total_bookings, "g", "-", 0.4, { {"color","green"} });
    plt::bar(days, confirmed_bookings, "b", "-", 0.4, { {"color","green"} ,{ "label", "Confirmed Bookings" } });
    plt::bar(days, rejected_bookings, "r", "-", 0.4, { {"color","red"}, { "label", "Rejected Bookings" } });
    plt::title("Total Car Bookings in " + std::string(month_names[month - 1]) + " " + std::to_string(year));
    plt::xlabel("Day");
    plt::ylabel("Total Booking");
    plt::xticks(days);
    plt::legend();
    plt::grid(true);
    plt::show();

    system("pause");
    system("cls");
    adminreportbooking();
}