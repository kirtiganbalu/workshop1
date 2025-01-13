#include "globals.h"
#include "paymentyearlyreport.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include "matplotlibcpppayment.h" // Assuming you have the matplotlibcpp library set up
namespace plt = matplotlibcpppayment;
using namespace std;

void paymentyearreport() {
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
    cout << "|           Year Payment report             |" << endl;
    cout << "|                                           |" << endl;
    cout << "*********************************************" << endl << endl;
    cout << endl;
    cout << "Generating report, please wait a few seconds..." << endl;

    generatepaymentyearlyReport(conn);
}

void generatepaymentyearlyReport(MYSQL* conn) {
    std::string query1 = R"(
        SELECT 
            YEAR(b.b_date) AS year, 
            COALESCE(SUM(p.pay_amount), 0) AS total_payments
        FROM 
            booking b
        LEFT JOIN 
            payment p ON b.bookingid = p.bookingid
        WHERE 
            p.pay_status = 'repaid'  -- Filter to include only repaid payments
        GROUP BY 
            year 
        ORDER BY 
            year
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

    std::vector<int> years;
    std::vector<double> total_payments;  // Use double for payments

    MYSQL_ROW row1;
    while ((row1 = mysql_fetch_row(res1))) {
        int year = atoi(row1[0]);
        double payment = atof(row1[1]);  // Keep as double

        years.push_back(year);
        total_payments.push_back(payment);
    }

    mysql_free_result(res1);

    // Display the table
    cout << endl;
    cout << setfill('-') << setw(38) << "-" << setfill(' ') << endl;
    cout
        << " | " << setw(15) << left << "Year:"
        << " | " << setw(15) << left << "Total Amount:"
        << " | " << endl;
    cout << setfill('-') << setw(38) << "-" << setfill(' ') << endl;
    for (size_t i = 0; i < years.size(); ++i) {
        cout
            << " | " << setw(15) << left << std::to_string(years[i])
            << " | " << setw(15) << left << total_payments[i]
            << " | " << endl;
        cout << setfill('-') << setw(38) << "-" << setfill(' ') << endl;
    }

    plt::figure_size(1200, 600);

    // Plotting the total payments as a bar chart with double values
    plt::bar(years, total_payments, "g", "-", 0.4, { {"label", "Total Payments"}, {"color", "purple"} });

    // Adding the text labels for total payments
    for (size_t i = 0; i < years.size(); ++i) {
        // Set text position slightly above the top of the bar
        plt::text(years[i], total_payments[i] + 0.1, total_payments[i]);
    }

    plt::title("Total Amounts Per Year ");
    plt::xlabel("Year");
    plt::ylabel("Total Amounts");
    plt::xticks(years);
    plt::legend();
    plt::grid(true);
    plt::show();

    system("pause");
    system("cls");
    adminreportpayment();
}