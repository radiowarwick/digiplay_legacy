#ifndef CLASS_DB_TRIGGER
#define CLASS_DB_TRIGGER

#include <string>

//#include "pqxx/connection.h"
#include "pqxx/trigger.h"

#include <qthread.h>
#include <qobject.h>
#include <qapplication.h>

#include "DataAccess.h"

/**
 * Creates a database trigger on the digiplay database which responds to the
 * specified trigger name registered in the database, emitting the trigger()
 * signal.
 *
 * The trigger is registered on the static database connection used by the
 * DataAccess class from which this class is derived. Thus, a caveat of this is
 * that the trigger will not be activated during transactions. It is therefore
 * imperative that good database practice is ensured and each batch of activity
 * on the database is finished with a commit() or abort() command to close the
 * transaction and allow the processing of any trigger events.
 *
 * To use the trigger, create an instance of this class, specifying the name of
 * the trigger on which to act. Then call the QThread start() routine to begin
 * monitoring. Connect the DbTrigger objects trigger() signal to whatever slots
 * should be processed upon this event.
 */
class DbTrigger:    public QObject,
                    public QThread, 
                    public pqxx::trigger,
                    public DataAccess {
    Q_OBJECT

    public:
        /// Creates a new trigger on the database trigger \c trigger.
        //DbTrigger(QWidget* parent, const char* name, std::string trigger);
        DbTrigger(const char* name, std::string trigger);
        ~DbTrigger() throw();
        void operator()(int be_pid);
        void run();
        void stop();

    signals:
        // Signal emitted when the database trigger is triggered.
        void trigger();

    private:
        bool enabled;
};

#endif
