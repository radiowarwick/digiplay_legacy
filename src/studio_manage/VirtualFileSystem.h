#ifndef CLASS_VIRTUAL_FILE_SYSTEM

#define CLASS_VIRTUAL_FILE_SYSTEM
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include "config.h"
#include "pqxx/connection.h"
#include "pqxx/transaction.h"
#include "pqxx/result.h"

class QString;
using namespace pqxx;

class VirtualDirectory : QDir {
	Q_OBJECT
	public:	
		VirtualDirectory();
		VirtualDirectory( const QString & path, ,const QString & 
			nameFilter = QString::null, int sortSpec = Name |
			IgnoreCase, int filterSpec = All );
		VirtualDirectry( VirtualDirectory & d );
		~VirtualDirectory();
		virtual void setPath ( const QString & path )
		virtual QString path () const
//		virtual QString absPath () const
//		virtual QString canonicalPath () const
//		virtual QString dirName () const
//		virtual QString filePath ( const QString & fileName, bool
//			acceptAbsPath = TRUE ) const
//		virtual QString absFilePath ( const QString & fileName,
//			bool acceptAbsPath = TRUE ) const
//		virtual bool cd ( const QString & dirName,
//			bool acceptAbsPath = TRUE )
//		virtual bool cdUp ()
//		virtual void setNameFilter ( const QString & nameFilter )
//		virtual void setFilter ( int filterSpec )
//		virtual void setSorting ( int sortSpec )
//		virtual void setMatchAllDirs ( bool enable )
//		virtual QStringList entryList ( int filterSpec = DefaultFilter,
//			int sortSpec = DefaultSort ) const
//		virtual QStringList entryList ( const QString & nameFilter,
//			int filterSpec = DefaultFilter, int sortSpec =
//			DefaultSort ) const
		virtual const VirtualFileInfoList * entryInfoList ( int 
			filterSpec = DefaultFilter, int sortSpec =
			DefaultSort ) const
//		virtual const VirtualFileInfoList * entryInfoList ( const 
//			QString & nameFilter, int filterSpec = DefaultFilter,
//			 int sortSpec = DefaultSort ) const
//		virtual bool mkdir ( const QString & dirName, bool acceptAbsPath
//			= TRUE ) const
//		virtual bool rmdir ( const QString & dirName, bool acceptAbsPath
//			= TRUE ) const
		virtual bool isReadable () const
//		virtual bool exists () const
//		virtual bool isRoot () const
//		virtual bool isRelative () const
//		virtual void convertToAbs ()
//		virtual bool operator== ( const VirtualDirectory & d ) const
//		virtual bool operator!= ( const VirtualDirectory & d ) const
//		virtual bool remove ( const QString & fileName, bool
//			acceptAbsPath = TRUE )
//		virtual bool rename ( const QString & oldName, const QString &
//			newName, bool acceptAbsPaths = TRUE )
//		virtual bool exists ( const QString & name, bool acceptAbsPath = TRUE )
//		void refresh () const
//
	private:
		int getIDFromPath(QString & path);
		QString GetNameFromID(int id);

		Connection *C;
		QString _path;
		QString _name;
		int _id;
		//Owner
		//User
}

class VirtualFile:QFile {
	Q_OBJECT

	public:
		VirtualFile ();
		VirtualFile ( const QString & name, cost int type );
		~VirtualFile ();
		QString name () const;
		void setName ( const QString & name );
//		virtual bool open ( int m )
//		virtual void close ()
//		virtual void flush ()
//		virtual Offset size () const
//		virtual bool atEnd () const
//		virtual Q_LONG readLine ( char * p, Q_ULONG maxlen )
//		virtual int getch ()
//		virtual int putch ( int ch )
//		virtual int ungetch ( int ch )

	private:
		QString _name;
		int _type;

}

class VirtualFileInfo {

	O_OBJECT

	public:
//		enum PermissionSpec { ReadOwner = 04000, WriteOwner = 02000, ExeOwner = 
//		01000, ReadUser = 00400, WriteUser = 00200, ExeUser = 00100, ReadGroup = 
//		00040, WriteGroup = 00020, ExeGroup = 00010, ReadOther = 00004, WriteOther = 
//		00002, ExeOther = 00001 }
		VirtualFileInfo ()
		VirtualFileInfo ( const QString & file )
		VirtualFileInfo ( const QFile & file )
		VirtualFileInfo ( const QDir & d, const QString & fileName )
		VirtualFileInfo ( const QFileInfo & fi )
		~VirtualFileInfo ()
//		QFileInfo & operator= ( const QFileInfo & fi )
//		void setFile ( const QString & file )
//		void setFile ( const QFile & file )
//		void setFile ( const QDir & d, const QString & fileName )
//		bool exists () const
//		void refresh () const
//		bool caching () const
//		void setCaching ( bool enable )
//		QString filePath () const
		QString fileName () const
//		QString absFilePath () const
//		QString baseName ( bool complete = FALSE ) const
//		QString extension ( bool complete = TRUE ) const
//		QString dirPath ( bool absPath = FALSE ) const
//		QDir dir ( bool absPath = FALSE ) const
//		bool isReadable () const
//		bool isWritable () const
//		bool isExecutable () const
//		bool isHidden () const
//		bool isRelative () const
//		bool convertToAbs ()
//		bool isFile () const
		int getType () const
//		QString readLink () const
//		QString owner () const
//		uint ownerId () const
//		QString group () const
//		uint groupId () const
//		bool permission ( int permissionSpec ) const
//		uint size () const
//		QDateTime created () const
//		QDateTime lastModified () const
//		QDateTime lastRead () const

}
