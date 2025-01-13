#include "globals.h"
#include "paymentmonthlyreport.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include"matplotlibcpppayment.h"
namespace plt = matplotlibcpppayment;
using namespace std;

bool checkYearExistspaymentmonthly(MYSQL* conn, int year) {
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

void paymentmonthlyreport() {

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
    cout << "|          Monthly Payment report           |" << endl;
    cout << "|                                           |" << endl;
    cout << "*********************************************" << endl << endl;

    int year;
    cout << "Enter the year for the report: ";
    cin >> year;

    if (checkYearExistspaymentmonthly(conn, year)) {
        cout << endl;
        cout << "Generating report, please wait a few seconds..." << endl;

        generatepaymentmonthlyReport(conn, year);
    }
    else {
        cerr << "No bookings found for the year " << year << "." << endl;
        system("pause");
        system("cls");
        adminreportpayment();
    }
    mysql_close(conn);
}


void generatepaymentmonthlyReport(MYSQL* conn, int year1) {
    std::string query1 = R"(
        SELECT 
            MONTH(b.b_date) AS month, 
            COALESCE(SUM(p.pay_amount), 0) AS total_payments
        FROM 
            booking b
        LEFT JOIN 
            payment p ON b.bookingid = p.bookingid
        WHERE 
            YEAR(b.b_date) = )" + std::to_string(year1) + R"(
            AND p.pay_status = 'repaid'  -- Filter to include only repaid payments
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
    std::vector<double> total_payments;  // Use double for payments

    MYSQL_ROW row1;
    while ((row1 = mysql_fetch_row(res1))) {
        int month = atoi(row1[0]);
        double payment = atof(row1[1]);  // Keep as double

        months.push_back(month);
        total_payments.push_back(payment);
    }

    mysql_free_result(res1);

    if (months.empty()) {
        cout << "No data found for the year " << year1 << endl;
        return;
    }

    const char* month_names1[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    std::vector<std::string> month_names_vector;
    for (int month : months) {
        month_names_vector.push_back(month_names1[month - 1]);
    }


    // Display the table
    cout << endl;
    cout << setfill('-') << setw(58) << "-" << setfill(' ') << endl;
    cout
        << " | " << setw(15) << left << "Month:"
        << " | " << setw(15) << left << "Year:"
        << " | " << setw(15) << left << "Total Amount:"
        << " | " << endl;
    cout << setfill('-') << setw(58) << "-" << setfill(' ') << endl;
    for (size_t i = 0; i < months.size(); ++i) {
        cout
            << " | " << setw(15) << left << std::string(month_names1[months[i] - 1])
            << " | " << setw(15) << left << std::to_string(year1)
            << " | " << setw(15) << left << total_payments[i]
            << " | " << endl;
        cout << setfill('-') << setw(58
        ) << "-" << setfill(' ') << endl;
    }

    plt::figure_size(1200, 600);

    // Plotting the total payments as a bar chart with double values
    plt::bar(months, total_payments, "g", "-", 0.4, { {"label", "Total Payments"}, {"color", "purple"} });

    // Adding the text labels for total payments
    for (size_t i = 0; i < months.size(); ++i) {
        // Set text position slightly above the top of the bar
        plt::text(months[i], total_payments[i] + 0.1, total_payments[i]);
    }

    plt::title("Total Amounts Per Month for " + std::to_string(year1));
    plt::xlabel("Month");
    plt::ylabel("Total Amounts");
    plt::xticks(months, month_names_vector);
    plt::legend();
    plt::grid(true);
    plt::show();

    system("pause");
    system("cls");
    adminreportpayment();
}
