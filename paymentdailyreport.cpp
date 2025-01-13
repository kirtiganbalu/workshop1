#include "globals.h"
#include "paymentdailyreport.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include"matplotlibcpppayment.h"
namespace plt = matplotlibcpppayment;
using namespace std;

bool checkYearExistspaymentdaily(MYSQL* conn, int year) {
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

void paymentdailyreport() {

    system("cls");
    system("Color 17");//Blue background, black text


    if (!conn) {
        std::cerr << "Database connection is not established." << std::endl;
        system("pause");
        system("cls");
        adminreportpayment();
    }

    cout << "*********************************************" << endl;
    cout << "|                                           |" << endl;
    cout << "|           Daily Payment report            |" << endl;
    cout << "|                                           |" << endl;
    cout << "*********************************************" << endl << endl;

    int year;
    cout << "Enter the year for the report: ";
    cin >> year;

    if (checkYearExistspaymentdaily(conn, year)) {
        int month;
        cout << "Enter the month for the report (1-12): ";
        cin >> month;

        if (month < 1 || month > 12) {
            cerr << "Invalid month! Please enter a month between 1 and 12." << endl;
            system("pause");
            system("cls");
            paymentdailyreport();
        }
        else {
            cout << endl;
            cout << "Generating report, please wait a few seconds..." << endl;
            generatepaymentdailyReport(conn, year, month);
        }
    }
    else {
        cerr << "No bookings found for the year " << year << "." << endl;
        system("pause");
        system("cls");
        adminreportpayment();
    }
    mysql_close(conn);
}


void generatepaymentdailyReport(MYSQL* conn, int year1, int month) {
    std::string query1 = R"(
        SELECT 
            DAY(b.b_date) AS day, 
            COALESCE(SUM(p.pay_amount), 0) AS total_payments
        FROM 
            booking b
        LEFT JOIN 
            payment p ON b.bookingid = p.bookingid
        WHERE 
            YEAR(b.b_date) = )" + std::to_string(year1) + R"( AND MONTH(b_date) = )" + std::to_string(month) + R"(
            AND p.pay_status = 'repaid'  -- Filter to include only repaid payments
        GROUP BY 
            day 
        ORDER BY 
            day
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

    std::vector<int> days;
    std::vector<double> total_payments;  // Use double for payments

    MYSQL_ROW row1;
    while ((row1 = mysql_fetch_row(res1))) {
        int day = atoi(row1[0]);
        double payment = atof(row1[1]);  // Keep as double

        days.push_back(day);
        total_payments.push_back(payment);
    }

    mysql_free_result(res1);

    if (days.empty()) {
        cout << "No data found for the year " << year1 << endl;
        return;
    }

    const char* month_names1[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };


    // Display the table
    cout << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;
    cout << " | " << setw(10) << left << "Day:"
        << " | " << setw(15) << left << "Month:"
        << " | " << setw(15) << left << "Year:"
        << " | " << setw(15) << left << "Total Amount:"
        << " | " << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;
    for (size_t i = 0; i < days.size(); ++i) {
        cout << " | " << setw(10) << left << std::to_string(days[i])
            << " | " << setw(15) << left << std::string(month_names1[month - 1])
            << " | " << setw(15) << left << std::to_string(year1)
            << " | " << setw(15) << left << total_payments[i]
            << " | " << endl;
        cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;
    }



    plt::figure_size(1200, 600);

    // Plotting the total payments as a bar chart with double values
    plt::bar(days, total_payments, "g", "-", 0.4, { {"label", "Total Payments"}, {"color", "purple"} });

    // Adding the text labels for total payments
    for (size_t i = 0; i < days.size(); ++i) {
        // Set text position slightly above the top of the bar
        plt::text(days[i], total_payments[i] + 0.1, total_payments[i]);
    }

    plt::title("Total Amounts in " + std::string(month_names1[month - 1]) + " " + std::to_string(year1));
    plt::xlabel("Day");
    plt::ylabel("Total Amounts");
    plt::xticks(days);
    plt::legend();
    plt::grid(true);
    plt::show();

    system("pause");
    system("cls");
    adminreportpayment();

}
