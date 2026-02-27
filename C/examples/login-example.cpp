#include <iostream>
#include <mysql/mysql.h>
#include <string.h>

struct userInfo {
    std::string Firstname;
    std::string Lastname;
    std::string Password;
}; userInfo userinfo;

struct dbSetup{
    std::string host = "127.0.0.1";
    std::string username = "fenen";
    std::string password = "qcupupust";
    int port = 3306;
    std::string db = "assigning_users_to_locations";
}; dbSetup dbsetup;


// Connect to database with spefied with the 
int conToDB(MYSQL * conn) {
    if( !mysql_real_connect(
        conn, 
        dbsetup.host.c_str(), 
        dbsetup.username.c_str(), 
        dbsetup.password.c_str(), 
        dbsetup.db.c_str(), 
        dbsetup.port, 
        NULL, 0)) {

        std::cerr << "Connection failure: " << mysql_error(conn) << "\n";
        mysql_close(conn);
        return 1;

    }

    std::cout << "Connection success: access granted" << std::endl;

    return 0;
}

void getUsernamePassword(std::string * firstname, std::string * lastname, std::string * password) {


    std::cout << "Enter Firstname: "; std::getline(std::cin, *firstname);
    std::cout << "Enter Lastname: "; std::getline(std::cin, *lastname);
    std::cout << "Password: "; std::getline(std::cin, *password);
    
}



// Main structure
int main() {

    MYSQL * conn = mysql_init(NULL);

    userInfo userinfo;

    conToDB(conn);
    getUsernamePassword(
        &userinfo.Firstname, 
        &userinfo.Lastname, 
        &userinfo.Password
    );

    // Set Query and argument parameter ready
    std::string query = "SELECT Password FROM users WHERE Firstname = ? AND Lastname = ?;";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    mysql_stmt_prepare(stmt, query.c_str(), query.size());

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (void*)userinfo.Firstname.c_str();
    bind[0].buffer_length = userinfo.Firstname.size();

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (void*)userinfo.Lastname.c_str();
    bind[1].buffer_length = userinfo.Lastname.size();

    // Bind the sql query and the arguments
    mysql_stmt_bind_param(stmt, bind);

    // execute query
    mysql_stmt_execute(stmt);

    /* ---------- store result set ---------- */
    mysql_stmt_store_result(stmt);

    /* ---------- bind result buffer ---------- */
    char passwordBuffer[255];
    unsigned long passwordLength = 0;
    my_bool is_null = 0;

    MYSQL_BIND result[1];
    memset(result, 0, sizeof(result));

    result[0].buffer_type = MYSQL_TYPE_STRING;
    result[0].buffer = passwordBuffer;
    result[0].buffer_length = sizeof(passwordBuffer);
    result[0].length = &passwordLength;
    result[0].is_null = &is_null;

    mysql_stmt_bind_result(stmt, result);

    /* ---------- fetch ---------- */
    int fetch_status = mysql_stmt_fetch(stmt);

    if (fetch_status == 0 && !is_null) {
        if (userinfo.Password == passwordBuffer)
            std::cout << "Login success\n";
        else
            std::cout << "Wrong password\n";

    } else if (fetch_status == MYSQL_NO_DATA) {
        
        std::cout << "User not found\n";
    } else {
        std::cout << "Fetch error: " << mysql_stmt_error(stmt) << "\n";
    }

    return 0;
}

/*
===============================================================================
DATABASE LOGIN PROGRAM — DEEP TECHNICAL STUDY NOTES
===============================================================================

This program demonstrates how a C++ application communicates with a MariaDB/MySQL
database using the LOW-LEVEL C CLIENT API and prepared statements.

This is NOT an ORM, NOT a framework, and NOT automatic memory handling.
You directly manage memory buffers, pointers, and data transfer between:

    Program memory  ↔  MySQL client library  ↔  Database server

This is why the API looks "manual" — it is designed for performance and control.

===============================================================================
SECTION 1 — OVERALL EXECUTION PIPELINE
===============================================================================

The program performs authentication using this sequence:

    1. Create connection object
    2. Connect to database server
    3. Read user input from terminal
    4. Prepare SQL statement template
    5. Bind input values (Firstname, Lastname)
    6. Execute SQL on server
    7. Prepare memory buffer for returned data
    8. Bind result buffer to statement
    9. Fetch row from server into memory
   10. Compare returned password with input

Important concept:
SQL does NOT return std::string.
SQL writes raw bytes into memory YOU provide.

===============================================================================
SECTION 2 — MYSQL CONNECTION OBJECT
===============================================================================

MYSQL *conn = mysql_init(NULL);

mysql_init() allocates and initializes a connection structure.
It does NOT connect to the server yet.

Think of MYSQL as:
    → session handle
    → network context
    → authentication state container

After initialization, mysql_real_connect() performs:

    ✔ TCP connection to server
    ✔ User authentication
    ✔ Database selection
    ✔ Session creation

If connection fails:
mysql_error(conn) returns human-readable error message.

===============================================================================
SECTION 3 — PREPARED STATEMENT SYSTEM
===============================================================================

Prepared statements separate:
    SQL structure
    from
    SQL data

SQL Template:
    SELECT Password FROM employee_users
    WHERE Firstname = ? AND Lastname = ?;

The '?' markers are placeholders.
They are NOT replaced with string concatenation.

Benefits:
    ✔ Prevent SQL injection
    ✔ Faster execution for repeated queries
    ✔ Binary-safe data transfer
    ✔ Server compiles query once

Prepared statement workflow:

    mysql_stmt_init()
        Creates statement handler.

    mysql_stmt_prepare()
        Sends SQL template to server.
        Server parses and compiles it.

    mysql_stmt_bind_param()
        Provides values for '?' placeholders.

    mysql_stmt_execute()
        Server executes query with bound values.

===============================================================================
SECTION 4 — PARAMETER BINDING (PROGRAM → SQL)
===============================================================================


MYSQL_BIND bind[2];

Each MYSQL_BIND structure describes ONE parameter.

Fields explained:

buffer_type
    Data type sent to SQL.
    Example: MYSQL_TYPE_STRING

buffer
    Pointer to memory containing data.

buffer_length
    Size of data in bytes.

When binding Firstname:

    bind[0].buffer = userinfo.Firstname.c_str();

Important:
std::string manages memory internally.
.c_str() gives pointer to raw char array.

MySQL reads directly from this memory when executing query.

Data flow direction here is:
    Program memory → SQL engine

===============================================================================
SECTION 5 — EXECUTION PHASE
===============================================================================

mysql_stmt_execute(stmt);

This sends to server:
    prepared SQL
    bound parameter values

Server performs:
    parameter substitution
    query execution
    result set creation

At this moment:
    Result exists on server
    BUT NOT yet copied into your variables

===============================================================================
SECTION 6 — RESULT STORAGE STRATEGY
===============================================================================

mysql_stmt_store_result(stmt);

This downloads entire result set from server to client memory.

Why it exists:
    Without it → rows streamed one-by-one
    With it → rows buffered locally

For login queries (single row), both work.

===============================================================================
SECTION 7 — RESULT BINDING (SQL → PROGRAM)
===============================================================================

This is the reverse of parameter binding.

You must provide memory where SQL will write returned data.

Memory allocated:

    char passwordBuffer[255];

This is raw character array capable of storing 254 characters + null terminator.

Additional metadata variables:

unsigned long passwordLength
    Stores actual length of returned string.

my_bool is_null
    Indicates whether DB value is NULL.

MYSQL_BIND result[1];

Fields explained:

buffer_type
    Expected data type of column.

buffer
    Memory address where SQL writes bytes.

buffer_length
    Maximum allowed write size.

length
    Pointer where actual size is stored.

is_null
    Pointer where NULL flag is stored.

Binding result does NOT fetch data.
It only registers destination memory.

Data flow direction here is:
    SQL engine → Program memory

===============================================================================
SECTION 8 — FETCH OPERATION (DATA TRANSFER MOMENT)
===============================================================================

mysql_stmt_fetch(stmt);

This is the exact moment data moves.

Internal process:

    Server sends row packet
    Client library receives packet
    Client library writes bytes into passwordBuffer
    passwordLength is updated
    is_null flag updated

After fetch:

    passwordBuffer contains database password.

Return values:

    0                → success
    MYSQL_NO_DATA    → no matching row
    nonzero          → error occurred

===============================================================================
SECTION 9 — PASSWORD COMPARISON
===============================================================================

if (userinfo.Password == passwordBuffer)

Comparison happens entirely in program memory.
Database is no longer involved.

Important security note:
This compares plain text passwords.
Real systems store HASHES, not raw passwords.

===============================================================================
SECTION 10 — MEMORY OWNERSHIP SUMMARY
===============================================================================

Memory provided by program:

    userinfo strings        → input parameters
    passwordBuffer          → output result
    MYSQL connection object → session state
    MYSQL_STMT object       → prepared query

Memory provided by MySQL client library:

    network buffers
    protocol parser
    result metadata

Database server memory:

    query execution plan
    table data
    result set

===============================================================================
SECTION 11 — DATA FLOW DIAGRAM
===============================================================================

USER INPUT
    ↓
std::string memory
    ↓ (bind_param)
MySQL client library
    ↓
Database server executes query
    ↓
Result set produced
    ↓ (fetch)
MySQL client writes into passwordBuffer
    ↓
Program compares password

===============================================================================
SECTION 12 — WHY THIS API IS LOW-LEVEL
===============================================================================

This design provides:

    ✔ Cross-platform portability (Linux + Windows)
    ✔ Zero hidden allocations
    ✔ Full memory control
    ✔ High performance
    ✔ Binary-safe communication

Trade-off:
    More manual steps required.

===============================================================================
END OF STUDY NOTES
===============================================================================
*/