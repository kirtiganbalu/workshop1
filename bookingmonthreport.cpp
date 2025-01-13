#include "globalsmonth.h"
#include "bookingmonthreport.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include "matplotlibcppmonth.h" // Assuming you have the matplotlibcpp library set up
namespace plt = matplotlibcppmonth;
using namespace std;

bool checkYearExists1(MYSQL* conn, int year1) {
    std::string query1 = "SELECT 1 FROM booking WHERE YEAR(b_date) = " + std::to_string(year1) + " LIMIT 1";
    if (mysql_query(conn, query1.c_str())) {
        cerr << "Error in executing the query: " << mysql_error(conn) << endl;
        return false;
    }

    MYSQL_RES* res1 = mysql_store_result(conn);
    if (!res1) {
        cerr << "Error in retrieving results: " << mysql_error(conn) << endl;
        return false;
    }

    bool yearExists1 = (mysql_num_rows(res1) > 0);
    mysql_free_result(res1);
    return yearExists1;
}

void bookingmonthlyreport() {
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
    cout << "|          Monthly Booking report           |" << endl;
    cout << "|                                           |" << endl;
    cout << "*********************************************" << endl << endl;

    int year1;
    cout << "Enter the year for the report: ";
    cin >> year1;

    if (checkYearExists1(conn, year1)) {
        cout << endl;
        cout << "Generating report, please wait a few seconds..." << endl;
        generatemonthlyReport(conn, year1);
    }
    else {
        cerr << "No bookings found for the year " << year1 << "." << endl;
        system("pause");
        system("cls");
        adminreportbooking();
    }
    mysql_close(conn);

}

void generatemonthlyReport(MYSQL* conn, int year1) {
    std::string query1 = R"(
        SELECT 
            MONTH(b_date) AS month, 
            COUNT(*) AS total_booking, 
            COUNT(CASE WHEN b_status = 'CONFIRM' THEN 1 END) AS confirm_booking, 
            COUNT(CASE WHEN b_status = 'REJECT' THEN 1 END) AS reject_booking 
        FROM 
            booking 
        WHERE 
            YEAR(b_date) = )" + std::to_string(year1) + R"(
        GROUP BY 
            month 
        ORDER BY 
            month
    )";

    if (mysql_query(conn, query1.c_str())) {
        cerr << "Error in executing the query: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* res1 = mysql_store_result(conn);
    if (!res1) {
        cerr << "Error in retrieving results: " << mysql_error(conn) << endl;
        return;
    }

    std::vector<int> months;
    std::vector<int> total_booking;
    std::vector<int> confirm_booking;
    std::vector<int> reject_booking;

    MYSQL_ROW row1;
    while ((row1 = mysql_fetch_row(res1))) {
        months.push_back(atoi(row1[0]));
        total_booking.push_back(atoi(row1[1]));
        confirm_booking.push_back(atoi(row1[2]));
        reject_booking.push_back(atoi(row1[3]));
    }

    mysql_free_result(res1);

    const char* month_names1[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Convert months from int to string month names for x-ticks
    std::vector<std::string> month_names_vector;
    for (int month : months) {
        month_names_vector.push_back(month_names1[month - 1]);
    }

    cout << endl;
    cout << setfill('-') << setw(94) << "-" << setfill(' ') << endl;
    cout << " | " << setw(10) << left << "Month:"
        << " | " << setw(10) << left << "Year:"
        << " | " << setw(15) << left << "Total Bookings"
        << " | " << setw(20) << left << "Confirmed Bookings:"
        << " | " << setw(20) << left << "Rejected Bookings:"
        << " | " << endl;
    cout << setfill('-') << setw(94) << "-" << setfill(' ') << endl;
    for (size_t i = 0; i < months.size(); ++i) {
        cout
            << " | " << setw(10) << left << string(month_names1[months[i] - 1])
            << " | " << setw(10) << left << std::to_string(year1)
            << " | " << setw(15) << left << std::to_string(total_booking[i])
            << " | " << setw(20) << left << std::to_string(confirm_booking[i])
            << " | " << setw(20) << left << std::to_string(reject_booking[i])
            << " | " << endl;
        cout << setfill('-') << setw(94) << "-" << setfill(' ') << endl;
    }


    plt::figure_size(1200, 600);
    plt::bar(months, total_booking, "g", "-", 0.4, { {"color","green"} });
    plt::bar(months, confirm_booking, "b", "-", 0.4, { {"color","green"} ,{ "label", "Confirmed Bookings" } });
    plt::bar(months, reject_booking, "r", "-", 0.4, { {"color","red"}, { "label", "Rejected Bookings" } });
    plt::title("Total Car Bookings Per Month for " + std::to_string(year1));
    plt::xlabel("Month");
    plt::ylabel("Total Booking");
    plt::xticks(months, month_names_vector);
    plt::legend();
    plt::grid(true);
    plt::show();


    system("pause");
    system("cls");
    adminreportbooking();
}
