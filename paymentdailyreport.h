#ifndef PAYMENTDAILYREPORT_H
#define PAYMENTDAILYREPORT_H

void adminreportpayment();
void paymentdailyreport();
void generatepaymentdailyReport(MYSQL* conn, int year1, int month);

#endif // PAYMENTDAILYREPORT_H