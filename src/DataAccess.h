#ifndef CLASS_DATA_ACCESS
#define CLASS_DATA_ACCESS

#include <iostream>
#include <string>
using namespace std;

#include "pthread.h"

#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h" 
using namespace pqxx;

/**
 * Class to provide an application-wide database interface.
 *
 * This class creates a single static database connection, allowing all
 * instances of the class to share a common connection and reduce server
 * connection congestion and improve load \ response time.
 *
 * The connection is automatically established upon the creation of the first
 * instance of the class. Transaction handling is automatically handled,
 * creating a transaction if one is not currently open. Transactions should be
 * committed or aborted when a task is complete.
 */
class DataAccess {
    public:
        DataAccess();
        ~DataAccess();

        /// Execute an SQL query and return the result.
        Result exec(std::string query);
        /// Commit the open transaction applying all changes to the database.
        void commit();
        /// Abort the open transaction rolling back any changes made in the
        /// open transaction.
        void abort();
        /// Returns the connection string used to connect to database
        static std::string getConnectionString();

    protected:
        static Connection* C;
        static Transaction* T;
        static pthread_mutex_t* t_trans_mutex;
        static unsigned int instanceCount;
};

#endif
