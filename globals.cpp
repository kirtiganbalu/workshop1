#include "globals.h"

// Define the global variables
MYSQL* conn = nullptr;
MYSQL_RES* res = nullptr;
MYSQL_ROW row = nullptr;
int qstate = 0;
