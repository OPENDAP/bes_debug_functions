// DebugFunctions.h

// This file is part of bes, A C++ back-end server implementation framework
// for the OPeNDAP Data Access Protocol.

// Copyright (c) 2013 OPeNDAP, Inc.
// Author: Nathan Potter <ndp@opendap.org>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// You can contact OPeNDAP, Inc. at PO Box 112, Saunderstown, RI. 02874-0112.

#ifndef DEBUGFUNCTIONS_H_
#define DEBUGFUNCTIONS_H_

#include <sstream>      // std::stringstream

#include <BaseType.h>
#include <DDS.h>
#include <ServerFunction.h>
#include <Int32.h>
#include <Str.h>
#include <BESError.h>
#include <BESInternalError.h>
#include <BESInternalFatalError.h>
#include <BESSyntaxUserError.h>
#include <BESForbiddenError.h>
#include <BESNotFoundError.h>


#include "BESAbstractModule.h"

namespace debug_function {

class DebugFunctions: public BESAbstractModule {
public:
    DebugFunctions()
    {
    }
    virtual ~DebugFunctions()
    {
    }
    virtual void initialize(const string &modname);
    virtual void terminate(const string &modname);

    virtual void dump(ostream &strm) const;
};

/*****************************************************************************************
 * 
 * Abort Function (Debug Functions)
 * 
 * This server side function calls abort(). (boom)
 *
 */
string abort_usage="abort(##) Where ## is the number of milliseconds to sleep before calling abort.";

/*****************************************************************************************
 * 
 * Abort Function (Debug Functions)
 * 
 * This server side function calls abort(). (boom)
 *
 */
void abort_ssf(int argc, libdap::BaseType * argv[], libdap::DDS &dds, libdap::BaseType **btpp){

    std::stringstream msg;
    libdap::Str *response = new libdap::Str("info");
    *btpp = response;

    if(argc!=1){
        msg << "Missing time parameter!  USAGE: " 
            << abort_usage;
    }
    else {
        libdap::Int32 *param1 = dynamic_cast<libdap::Int32*>(argv[0]) ;  
        if(param1){
           libdap::dods_int32 milliseconds = param1->value();
           usleep(milliseconds * 1000);   
           std::abort();
        }
        else {
            msg << "This function only accepts integer values "
                << "for the time (in milliseconds) parameter.  USAGE: " 
                << abort_usage;
        }
        
    }
    
    response->set_value(msg.str());
    return;
};


class AbortFunc: public libdap::ServerFunction {
public:
    AbortFunc()
{
        setName("abort");
        setDescriptionString((string)"This function calls abort() killing the beslistner process.");
        setUsageString("abort()");
        setRole("http://services.opendap.org/dap4/server-side-function/debug/abort");
        setDocUrl("http://docs.opendap.org/index.php/Debug_Functions");
        setFunction(debug_function::abort_ssf);
        setVersion("1.0");
}
    virtual ~AbortFunc()
    {
    }

};



/*****************************************************************************************
 * 
 * Sleep Function (Debug Functions)
 * 
 * This server side function calls sleep() for the number 
 * of millisecs passed in at argv[0]. (Zzzzzzzzzzzzzzz)
 *
 */
string sleep_usage = "sleep(##) where ## is the number of milliseconds to sleep.";
 
/*****************************************************************************************
 * 
 * Sleep Function (Debug Functions)
 * 
 * This server side function calls sleep() for the number 
 * of millisecs passed in at argv[0]. (Zzzzzzzzzzzzzzz)
 *
 */
 
void sleep_ssf(int argc, libdap::BaseType * argv[], libdap::DDS &dds, libdap::BaseType **btpp){

    std::stringstream msg;
    libdap::Str *response = new libdap::Str("info");
    *btpp = response;

    if(argc!=1){
        msg << "Missing time parameter!  USAGE: " 
            << sleep_usage;
    }
    else {
        libdap::Int32 *param1 = dynamic_cast<libdap::Int32*>(argv[0]) ;  
        if(param1){
           libdap::dods_int32 milliseconds = param1->value();
            usleep(milliseconds * 1000);   
            msg << "Slept for " 
                << milliseconds 
                << " ms.";
        }
        else {
            msg << "This function only accepts integer values "
                << "for the time (in milliseconds) parameter.  USAGE: " 
                << sleep_usage;
        }
        
    }
    
    response->set_value(msg.str());
    return;
};

class SleepFunc: public libdap::ServerFunction {
public:
    SleepFunc()
{
        setName("sleep");
        setDescriptionString((string)"This function calls sleep() for the specified number of millisecs.");
        setUsageString(sleep_usage);
        setRole("http://services.opendap.org/dap4/server-side-function/debug/sleep");
        setDocUrl("http://docs.opendap.org/index.php/Debug_Functions");
        setFunction(debug_function::sleep_ssf);
        setVersion("1.0");
}
    virtual ~SleepFunc()
    {
    }

};



/*****************************************************************************************
 * 
 * Error Function (Debug Functions)
 * 
 * This server side function calls calls sleep() for the number 
 * of ms passed in at argv[0]. (Zzzzzzzzzzzzzzz)
 *
 */
string error_usage = "error(##) where ## is the BESError type to generate.";

/*****************************************************************************************
 * 
 * Error Function (Debug Functions)
 * 
 * This server side function calls calls sleep() for the number 
 * of ms passed in at argv[0]. (Zzzzzzzzzzzzzzz)
 *
 */
void error_ssf(int argc, libdap::BaseType * argv[], libdap::DDS &dds, libdap::BaseType **btpp){

    std::stringstream msg;
    libdap::Str *response = new libdap::Str("info");
    *btpp = response;

    if(argc!=1){
        msg << "Missing error type parameter!  USAGE: " 
            << error_usage;
    }
    else {
        libdap::Int32 *param1 = dynamic_cast<libdap::Int32*>(argv[0]) ;  
        if(param1){
            libdap::dods_int32 error_type = param1->value();
        
            switch(error_type) {
            
                case BES_INTERNAL_ERROR:
                {
                    msg << "A BESInternalError was requested.";
                    BESInternalError error(msg.str(),__FILE__,__LINE__);
                    throw error;
                }
                break;
                
                case BES_INTERNAL_FATAL_ERROR:
                {
                    msg << "A BESInternalFatalError was requested.";
                    BESInternalFatalError error(msg.str(),__FILE__,__LINE__);
                    throw error;
                }
                break;
                
                case BES_SYNTAX_USER_ERROR:
                {
                    msg << "A BESSyntaxUserError was requested.";
                    BESSyntaxUserError error(msg.str(),__FILE__,__LINE__);
                    throw error;
                }
                break;
                
                case BES_FORBIDDEN_ERROR:
                {
                    msg << "A BESForbiddenError was requested.";
                    BESForbiddenError error(msg.str(),__FILE__,__LINE__);
                    throw error;
                }
                break;
                
                case BES_NOT_FOUND_ERROR:
                {
                    msg << "A BESNotFoundError was requested.";
                    BESNotFoundError error(msg.str(),__FILE__,__LINE__);
                    throw error;
                }
                break;
                
                default:
                msg << "An unrecognized error_type parameter was received. error_type: " << error_type;
                break;
            }
            

        }
        else {
            msg << "This function only accepts integer values "
                << "for the error type parameter.  USAGE: " 
                << error_usage;
        }
        
    }
    
    response->set_value(msg.str());
    return;

};

class ErrorFunc: public libdap::ServerFunction {
public:
    ErrorFunc()
{
        setName("error");
        setDescriptionString((string)"This function triggers a BES Error of the type specified");
        setUsageString(error_usage);
        setRole("http://services.opendap.org/dap4/server-side-function/debug/error");
        setDocUrl("http://docs.opendap.org/index.php/Debug_Functions");
        setFunction(debug_function::error_ssf);
        setVersion("1.0");
}
    virtual ~ErrorFunc()
    {
    }

};



} // namespace debug
#endif /* DEBUGFUNCTIONS_H_ */
