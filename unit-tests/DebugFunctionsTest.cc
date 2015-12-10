// -*- mode: c++; c-basic-offset:4 -*-

// This file is part of libdap, A C++ implementation of the OPeNDAP Data
// Access Protocol.

// Copyright (c) 2005 OPeNDAP, Inc.
// Author: Nathan David Potter <ndp@opendap.org>
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

#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#define DODS_DEBUG

#include <BESDebug.h>

#include "util.h"
#include "debug.h"
#include "Array.h"
#include "Int32.h"
#include "Float64.h"
#include "DebugFunctions.h"
#include <BaseTypeFactory.h>

#include "GetOpt.h"

static bool debug = false;

#undef DBG
#define DBG(x) do { if (debug) (x); } while(false);

namespace libdap {

class DebugFunctionsTest: public CppUnit::TestFixture {
private:
    BaseTypeFactory btf;
    DDS *testDDS;

public:
    // Called once before everything gets tested
    DebugFunctionsTest()
    {

    }

    // Called at the end of the test
    ~DebugFunctionsTest()
    {
    }

    // Called before each test
    void setUp()
    {
        try {
            testDDS = new DDS(&btf);
        }
        catch (Error & e) {
            cerr << "SetUp: " << e.get_error_message() << endl;
            throw;
        }
    }

    // Called after each test
    void tearDown()
    {
        delete testDDS;
    }

CPPUNIT_TEST_SUITE( DebugFunctionsTest );

    CPPUNIT_TEST(abortFunctionTest);
    CPPUNIT_TEST(sleepFunctionTest);
    CPPUNIT_TEST(errorFunctionTest);

    CPPUNIT_TEST_SUITE_END()
    ;

    void abortFunctionTest()
    {
        DBG(cerr << " abortFunctionTest() - BEGIN." << endl);
      
        debug_function::AbortFunc abortFunc;
        
        libdap::btp_func btp_abort_func = abortFunc.get_btp_func();
   
        libdap::BaseType **btpp;
        
        libdap::BaseType *argv[0];
#if 0
      

      
        btp_abort_func(0, argv, *testDDS, btpp);
        
        cerr << endl;
        cerr << " btpp: " << hex  << btpp << endl;
        cerr << "*btpp: " << hex  << *btpp << endl;

        cerr << "(*btpp)->is_constructor_type(): " << (*btpp)->is_constructor_type() << endl;
        cerr << "(*btpp)->type_name(): " << (*btpp)->type_name() << endl;
        cerr << "(*btpp)->print_val(cerr,"",false): ";
        (*btpp)->print_val(cerr,"",false);
        cerr << endl;
        
        if(debug){
        
            (*btpp)->print_val(cerr,"",false);
        
        }
              
        
#endif

        CPPUNIT_ASSERT(true);
        
        DBG(cerr << " abortFunctionTest() - END." << endl);
    }

    void sleepFunctionTest()
    {
        DBG(cerr << " sleepFunctionTest() - BEGIN." << endl);
     
        debug_function::SleepFunc sleepFunc;
        
        libdap::btp_func btpf=sleepFunc.get_btp_func();
   
        CPPUNIT_ASSERT(true);
        
        DBG(cerr << " sleepFunctionTest() - END." << endl);
    }

    void errorFunctionTest()
    {
        DBG(cerr << " errorFunctionTest() - BEGIN." << endl);
        
        debug_function::ErrorFunc errorFunc;
        
        libdap::btp_func btpf=errorFunc.get_btp_func();
           
        CPPUNIT_ASSERT(true);
        
        DBG(cerr << " errorFunctionTest() - END." << endl);
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION(DebugFunctionsTest);

} /* namespace libdap */

int main(int argc, char*argv[])
{
    CppUnit::TextTestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());

    GetOpt getopt(argc, argv, "d");
    int option_char;
    while ((option_char = getopt()) != -1)
        switch (option_char) {
        case 'd':
            debug = 1;  // debug is a static global
            BESDebug::SetUp("cerr,ugrid");
            break;
        default:
            break;
        }

    bool wasSuccessful = true;
    string test = "";
    int i = getopt.optind;
    if (i == argc) {
        // run them all
        wasSuccessful = runner.run("");
    }
    else {
        while (i < argc) {
            test = string("libdap::NDimArrayTest::") + argv[i++];

            DBG(cerr << endl << "Running test " << test << endl << endl);

            wasSuccessful = wasSuccessful && runner.run(test);
        }
    }

    return wasSuccessful ? 0 : 1;
}
