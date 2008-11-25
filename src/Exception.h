/*
 * $Id: Exception.h 128 2008-07-06 18:30:47Z cc $
 *
 * Copyright (c) 2005 - $Date: 2008-07-06 19:30:47 +0100 (Sun, 06 Jul 2008) $ Chris Cantwell and Paul Clifford
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef CLASS_EXCEPTION
#define CLASS_EXCEPTION

#include <string>
#include <sstream>

/** 
 * \def NEW_EXCEPTION(X)
 * Creates a new exception object called \a X
 */
#define NEW_EXCEPTION(X) \
    class X : public Exception { \
        public: \
            X(std::string file, unsigned long line, std::string message) \
                : Exception(file,line,message) {} \
            X(const X &x) : Exception(x) {} \
            ~X() {} \
    }
/** 
 * \def MKEX(X)
 * Populates the parameter list of an \a Exception constructor with the file
 * and line number at which the exception occured.
 */
#define MKEX(X) __FILE__, __LINE__, (X)

/**
 * \brief Defines a base class for an exception.
 *
 * This is a base class for all exceptions thrown by classes in the pdesolver.
 * New exceptions for a particular class are created before the classes
 * definition using the \c NEW_EXCEPTION macro which generates a new exception
 * class derived from \a Exception. For instance
 * \code
 *   NEW_EXCEPTION(EMyError);
 * \endcode
 *
 * When throwing an exception, use the MKEX macro which automatically inserts
 * the filename and line number where the error is thrown, as follows:
 * \code
 *   throw EMyError(MKEX("Some exception has occured"));
 * \endcode
 */
class Exception {
    public:
        /// Constructor.
        Exception(std::string pFile, unsigned int pLine, std::string pMessage)
            : mFile     ( pFile ), 
              mLine     ( pLine ), 
              mMessage  ( pMessage ) {}
        /// Copy constructor.
        Exception(const Exception &E) 
            : mFile     ( E.mFile ), 
              mLine     ( E.mLine ), 
              mMessage  ( E.mMessage ) {}
        /// Destructor.
        virtual ~Exception() {}

        /// Returns a string describing the exception.
        std::string what() { 
            std::stringstream vTemp;
            vTemp << mFile << ":" << mLine << ": " << mMessage;
            return vTemp.str(); 
        }
        /// Returns the filename where the exception occured.
        std::string getFile() {
            return mFile;
        }
        /// Returns the line number on which the exception occured.
        unsigned long getLine() {
            return mLine;
        }
        /// Returns a description of the exception.
        std::string getMessage() {
            return mMessage;
        }

    private:
        /// Name of the file in which the exception occured.
        std::string mFile;
        /// Line number at which the exception occured.
        unsigned long mLine;
        /// Message describing the exception.
        std::string mMessage;
};

#endif
