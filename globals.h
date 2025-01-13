#ifndef GLOBALS_H
#define GLOBALS_H

#include <mysql.h> // MySQL header

// Declare global variables with extern
extern MYSQL* conn;
extern MYSQL_RES* res;
extern MYSQL_ROW row;
extern int qstate;

#endif // GLOBALS_H
#pragma once
