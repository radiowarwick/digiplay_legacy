#ifndef CLASS_DB_TRIGGER
#define CLASS_DB_TRIGGER

#include <string>

#include <qthread.h>
#include <qobject.h>
#include <qapplication.h>

#include <pqxx/pqxx>

/**
 * This is a helper class, which implements the actual trigger. This should not
 * be used directly, instead use DbTrigger class which is a wrapper designed to
 * set up the database connection as well. Use this class with a different
 * database connection at your own risk.
 */
class DbPqxxTrigger:    public QObject,
                        public pqxx::trigger {
    Q_OBJECT

    public:
        DbPqxxTrigger(const char* name, pqxx::connection *C, 
                        std::string trigger);
        ~DbPqxxTrigger() throw();
        void operator()(int be_pid);
        
    signals:
        void trigger();
};

/**
 * Creates a database trigger on the digiplay database which responds to the
 * specified trigger name registered in the database, emitting the trigger()
 * signal.
 *
 * The trigger is registered on a separate static database connection created
 * by this class. This ensures that the connection is always available to
 * register notifications immediately and not be held up by transactions from
 * elsewhere being open.
 *
 * To use the trigger, create an instance of this class, specifying the name of
 * the trigger on which to act. Then call the QThread start() routine to begin
 * monitoring. Connect the DbTrigger objects trigger() signal to whatever slots
 * should be processed upon this event.
 */
class DbTrigger:    public QObject,
                    public QThread { 
    Q_OBJECT

    public:
        /// Creates a new trigger on the database trigger \c trigger.
        //DbTrigger(QWidget* parent, const char* name, std::string trigger);
        DbTrigger(const char* name, std::string trigger);
        ~DbTrigger() throw();
        void run();
        void stop();

    private slots:
        void triggered();

    signals:
        // Signal emitted when the database trigger is triggered.
        void trigger();

    private:
        DbPqxxTrigger* Trig;
        std::string trigname;
		bool enabled;
        static unsigned int instanceCount;
        static pqxx::connection* Ctrig;
};



#endif
