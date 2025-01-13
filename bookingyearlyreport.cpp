#include "globals.h"
#include "bookingyearlyreport.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include "matplotlibcpp.h" // Assuming you have the matplotlibcpp library set up
namespace plt = matplotlibcpp;
using namespace std;

void bookingyearreport() {
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
    cout << "|           Year Booking report             |" << endl;
    cout << "|                                           |" << endl;
    cout << "*********************************************" << endl << endl;
    cout << endl << endl << endl;
    cout << "Generating report, please wait a few seconds..." << endl;

   generateyearlyReport(conn);
}

void generateyearlyReport(MYSQL* conn) {
    std::string query = R"(
       SELECT 
            YEAR(b_date) AS year, 
            COUNT(*) AS total_bookings, 
            COUNT(CASE WHEN b_status = 'confirm' THEN 1 END) AS confirmed_bookings, 
            COUNT(CASE WHEN b_status = 'reject' THEN 1 END) AS rejected_bookings 
        FROM 
            booking 
        GROUP BY 
            year 
        ORDER BY 
            year
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

    std::vector<int> year;
    std::vector<int> total_bookings;
    std::vector<int> confirmed_bookings;
    std::vector<int> rejected_bookings;

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        year.push_back(atoi(row[0]));
        total_bookings.push_back(atoi(row[1]));
        confirmed_bookings.push_back(atoi(row[2]));
        rejected_bookings.push_back(atoi(row[3]));
    }

    mysql_free_result(res);
    // Display the table
    cout << endl;
    cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
    cout << " | " << setw(10) << left << "Year:"
        << " | " << setw(15) << left << "Total Bookings:"
        << " | " << setw(20) << left << "Confirmed Bookings:"
        << " | " << setw(20) << left << "Rejected Bookings:"
        << " | " << endl;
    cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
    for (size_t i = 0; i < year.size(); ++i) {
        cout << " | " << setw(10) << left << std::to_string(year[i])
            << " | " << setw(15) << left << std::to_string(total_bookings[i])
            << " | " << setw(20) << left << std::to_string(confirmed_bookings[i])
            << " | " << setw(20) << left << std::to_string(rejected_bookings[i])
            << " | " << endl;
        cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
    }

    plt::figure_size(1200, 600);
    plt::bar(year, total_bookings, "g", "-", 0.4, { {"color","green"} });
    plt::bar(year, confirmed_bookings, "b", "-", 0.4, { {"color","green"} ,{ "label", "Confirmed Bookings" } });
    plt::bar(year, rejected_bookings, "r", "-", 0.4, { {"color","red"}, { "label", "Rejected Bookings" } });
    plt::title("Total Car Bookings Per Year ");
    plt::xlabel("Year");
    plt::ylabel("Total Booking");
    plt::xticks(year);
    plt::legend();
    plt::grid(true);
    plt::show();

    system("pause");
    system("cls");
    adminreportbooking();
}