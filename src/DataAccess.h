#ifndef CLASS_DATA_ACCESS
#define CLASS_DATA_ACCESS
#include <string>

#include <pqxx/pqxx>

#include "pthread.h"

typedef pqxx::connection    PqxxConnection;
typedef pqxx::work          PqxxWork;
typedef pqxx::result        PqxxResult;

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
        PqxxResult exec(std::string query);
        /// Commit the open transaction applying all changes to the database.
        void commit();
        /// Abort the open transaction rolling back any changes made in the
        /// open transaction.
        void abort();
        /// Returns the connection string used to connect to database
        static std::string getConnectionString();

    protected:
        static PqxxConnection* C;
        static PqxxWork* W;
        static pthread_mutex_t* t_trans_mutex;
        static unsigned int instanceCount;
};

#endif
