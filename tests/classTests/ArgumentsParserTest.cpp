/*
 * Copyright (c) 2019, University of Kaiserslautern
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Andr'e L. Chinazzo, Deepak M. Mathew, Christian Weis
 */



#ifndef ARGUMENTSPARSERTEST_CPP
#define ARGUMENTSPARSERTEST_CPP

#include <boost/test/included/unit_test.hpp>

#include "../../parser/ArgumentsParser.h"

BOOST_AUTO_TEST_SUITE( testArgumentsParser )

BOOST_AUTO_TEST_CASE( checkInputParametersParser_wrong_first_flag )
{
    int sim_argc = 7;
    char* sim_argv[] = {"./executable",
                        "-xell", // Instead of "-cell", user types "-xell".
                        "../../tests/cells/test_cell.json",
                        "-tech",
                        "../../tests/techs/test_tech.json",
                        "-arch",
                        "../../tests/archs/test_arch.json"};

    ArgumentsParser inputFileName(sim_argc, sim_argv);

    std::string exceptionMsg("No exception.ception.");
    try {
        inputFileName.runArgParser();
    }catch (string exceptionMsgThrown){
        exceptionMsg = exceptionMsgThrown;
    }

    const char* helpMessage =
        "  Mandatory:\n"
        "    OR:\n"
        "    -conf    <path/to/configurationfile.json> "
          "(Specify the configuration file containing cell, tech, "
            "and arch description files path to be used.)\n"
        "    OR:\n"
        "    -cell    <path/to/cellfile.json>          "
          "(Specify which technology description file should be used.)\n"
        "    -tech    <path/to/technologyfile.json>    "
          "(Specify which technology description file should be used.)\n"
        "    -arch    <path/to/architecturefile.json>  "
          "(Specify which architecture description file should be used.)\n"
        "  Optional:\n"
        "    -term                                     "
          "(Include IO termination currents for read and write operations.)\n"
        "    -printAll                                 "
          "(Enable print out of all internal variables.)\n"
        "For more information, see README.md.\n";

    string expectedMsg("[ERROR] ");
    expectedMsg.append("Unexpected argument \'");
    expectedMsg.append("-xell\'\n"); // Same flag error: "-r" instead of "-t".
    expectedMsg.append(helpMessage);
    BOOST_CHECK_MESSAGE( exceptionMsg == expectedMsg,
                        "Error message different from what was expected."
                        << "\nExpected: " << expectedMsg
                        << "\nGot: " << exceptionMsg);

}

BOOST_AUTO_TEST_CASE( checkInputParametersParser_wrong_second_flag1 )
{
    int sim_argc = 7;
    char* sim_argv[] = {"./executable",
                        "-cell",
                        "../../tests/cells/test_cell.json",
                        "-rech", // Instead of "-tech", user types "-rech".
                        "../../tests/techs/test_tech.json",
                        "-arch",
                        "../../tests/archs/test_arch.json"};

    ArgumentsParser inputFileName(sim_argc, sim_argv);

    std::string exceptionMsg("No exception.");
    try {
        inputFileName.runArgParser();
    }catch (string exceptionMsgThrown){
        exceptionMsg = exceptionMsgThrown;
    }

    const char* helpMessage =
        "  Mandatory:\n"
        "    OR:\n"
        "    -conf    <path/to/configurationfile.json> "
          "(Specify the configuration file containing cell, tech, "
            "and arch description files path to be used.)\n"
        "    OR:\n"
        "    -cell    <path/to/cellfile.json>          "
          "(Specify which technology description file should be used.)\n"
        "    -tech    <path/to/technologyfile.json>    "
          "(Specify which technology description file should be used.)\n"
        "    -arch    <path/to/architecturefile.json>  "
          "(Specify which architecture description file should be used.)\n"
        "  Optional:\n"
        "    -term                                     "
          "(Include IO termination currents for read and write operations.)\n"
        "    -printAll                                 "
          "(Enable print out of all internal variables.)\n"
        "For more information, see README.md.\n";

    string expectedMsg("[ERROR] ");
    expectedMsg.append("Unexpected argument \'");
    expectedMsg.append("-rech\'\n"); // Same flag error: "-o" instead of "-t".
    expectedMsg.append(helpMessage);
    BOOST_CHECK_MESSAGE( exceptionMsg == expectedMsg,
                        "Error message different from what was expected."
                        << "\nExpected: " << expectedMsg
                        << "\nGot: " << exceptionMsg);

}

BOOST_AUTO_TEST_CASE( checkInputParametersParser_wrong_third_flag )
{
    int sim_argc = 7;
    char* sim_argv[] = {"./executable",
                        "-cell",
                        "../../tests/cells/test_cell.json",
                        "-tech",
                        "../../tests/techs/test_tech.json",
                        "-srch", // Instead of "-arch", user types "-srch".
                        "../../tests/archs/test_arch.json"};

    ArgumentsParser inputFileName(sim_argc, sim_argv);

    std::string exceptionMsg("No exception.");
    try {
        inputFileName.runArgParser();
    }catch (string exceptionMsgThrown){
        exceptionMsg = exceptionMsgThrown;
    }

    const char* helpMessage =
        "  Mandatory:\n"
        "    OR:\n"
        "    -conf    <path/to/configurationfile.json> "
          "(Specify the configuration file containing cell, tech, "
            "and arch description files path to be used.)\n"
        "    OR:\n"
        "    -cell    <path/to/cellfile.json>          "
          "(Specify which technology description file should be used.)\n"
        "    -tech    <path/to/technologyfile.json>    "
          "(Specify which technology description file should be used.)\n"
        "    -arch    <path/to/architecturefile.json>  "
          "(Specify which architecture description file should be used.)\n"
        "  Optional:\n"
        "    -term                                     "
          "(Include IO termination currents for read and write operations.)\n"
        "    -printAll                                 "
          "(Enable print out of all internal variables.)\n"
        "For more information, see README.md.\n";

    string expectedMsg("[ERROR] ");
    expectedMsg.append("Unexpected argument \'");
    expectedMsg.append("-srch\'\n");
    expectedMsg.append(helpMessage);
    BOOST_CHECK_MESSAGE( exceptionMsg == expectedMsg,
                        "Error message different from what was expected."
                        << "\nExpected: " << expectedMsg
                        << "\nGot: " << exceptionMsg);

}

BOOST_AUTO_TEST_CASE( checkInputParametersParser_no_config )
{
  int sim_argc = 2;
  char* sim_argv[] = {"./executable",
                      "-conf"};

    ArgumentsParser inputFileName(sim_argc, sim_argv);

    std::string exceptionMsg("No exception.");
    try {
        inputFileName.runArgParser();
    }catch (string exceptionMsgThrown){
        exceptionMsg = exceptionMsgThrown;
    }

    const char* helpMessage =
        "  Mandatory:\n"
        "    OR:\n"
        "    -conf    <path/to/configurationfile.json> "
          "(Specify the configuration file containing cell, tech, "
            "and arch description files path to be used.)\n"
        "    OR:\n"
        "    -cell    <path/to/cellfile.json>          "
          "(Specify which technology description file should be used.)\n"
        "    -tech    <path/to/technologyfile.json>    "
          "(Specify which technology description file should be used.)\n"
        "    -arch    <path/to/architecturefile.json>  "
          "(Specify which architecture description file should be used.)\n"
        "  Optional:\n"
        "    -term                                     "
          "(Include IO termination currents for read and write operations.)\n"
        "    -printAll                                 "
          "(Enable print out of all internal variables.)\n"
        "For more information, see README.md.\n";

    string expectedMsg("[ERROR] ");
    expectedMsg.append("No input file provided!\n");
    expectedMsg.append(helpMessage);
    BOOST_CHECK_MESSAGE( exceptionMsg == expectedMsg,
                        "Error message different from what was expected."
                        << "\nExpected: " << expectedMsg
                        << "\nGot: " << exceptionMsg);

}

BOOST_AUTO_TEST_CASE( checkInputParametersParser_1cell_1tech_1arch )
{
    int sim_argc = 7;
    char* sim_argv[] = {"./executable",
                        "-cell",
                        "../../tests/cells/test_cell.json",
                        "-tech",
                        "../../tests/techs/test_tech.json",
                        "-arch",
                        "../../tests/archs/test_arch.json"};

    ArgumentsParser inputFileName(sim_argc, sim_argv);

    std::string exceptionMsg("No exception.");
    try {
        inputFileName.runArgParser();
    }catch (string exceptionMsgThrown){
        exceptionMsg = exceptionMsgThrown;
    }

    std::string expectedMsg("No exception.");
    BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedMsg,
                        "Error message different from what was expected."
                        << "\nExpected: " << expectedMsg
                        << "\nGot: " << exceptionMsg);


    BOOST_CHECK_MESSAGE(inputFileName.configs.size()
                        == 1,
                        "Number of configurations different "
                        "from the expected:"
                        << "\nExpected: " << 1
                        << "\nGot:" << inputFileName.configs.size());

    string expectedStr;

    expectedStr = sim_argv[2];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].cellFileName
                        == expectedStr,
                        "Cell file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].cellFileName);

    expectedStr = sim_argv[4];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].techFileName
                        == expectedStr,
                        "Technology file name missmatch!\n"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].techFileName);

    expectedStr = sim_argv[6];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].archFileName
                        == expectedStr,
                        "Architecture file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].archFileName);

    BOOST_CHECK_MESSAGE(inputFileName.IOTerminationCurrentFlag == false,
                        "\nIO termination flag missmatch!"
                        << "\nExpected: " << false
                        << "\nGot:" << inputFileName.IOTerminationCurrentFlag);

}

BOOST_AUTO_TEST_CASE( checkInputParametersParser_1conf )
{
    int sim_argc = 3;
    char* sim_argv[] = {"./executable",
                        "-conf",
                        "../../tests/configs/test_config.txt"};

    ArgumentsParser inputFileName(sim_argc, sim_argv);

    std::string exceptionMsg("No exception.");
    try {
        inputFileName.runArgParser();
    }catch (string exceptionMsgThrown){
        exceptionMsg = exceptionMsgThrown;
    }

    std::string expectedMsg("No exception.");
    BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedMsg,
                        "Error message different from what was expected."
                        << "\nExpected: " << expectedMsg
                        << "\nGot: " << exceptionMsg);

    BOOST_CHECK_MESSAGE(inputFileName.configs.size()
                        == 1,
                        "Number of configurations different "
                        "from the expected:"
                        << "\nExpected: " << 1
                        << "\nGot:" << inputFileName.configs.size());

    string expectedStr;

    expectedStr = "../../tests/cells/test_cell.json";
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].cellFileName
                        == expectedStr,
                        "Cell file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].cellFileName);

    expectedStr = "../../tests/techs/test_tech.json";
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].techFileName
                        == expectedStr,
                        "Technology file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].techFileName);

    expectedStr = "../../tests/archs/test_arch.json";
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].archFileName
                        == expectedStr,
                        "Architecture file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].archFileName);

    BOOST_CHECK_MESSAGE(inputFileName.IOTerminationCurrentFlag == false,
                        "\nIO termination flag missmatch!"
                        << "\nExpected: " << false
                        << "\nGot:" << inputFileName.IOTerminationCurrentFlag);

}

BOOST_AUTO_TEST_CASE( checkInputParametersParser_2cell_2tech_2arch )
{
    int sim_argc = 10;
    char* sim_argv[] = {"./executable",
                        "-cell",
                        "../../tests/cells/test_cell.json",
                        "../../tests/cells/test_cell2.json",
                        "-tech",
                        "../../tests/techs/test_tech.json",
                        "../../tests/techs/test_tech2.json",
                        "-arch",
                        "../../tests/archs/test_arch.json",
                        "../../tests/archs/test_arch2.json"};

    ArgumentsParser inputFileName(sim_argc, sim_argv);

    std::string exceptionMsg("No exception.");
    try {
        inputFileName.runArgParser();
    }catch (string exceptionMsgThrown){
        exceptionMsg = exceptionMsgThrown;
    }

    std::string expectedMsg("No exception.");
    BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedMsg,
                        "Error message different from what was expected."
                        << "\nExpected: " << expectedMsg
                        << "\nGot: " << exceptionMsg);

    BOOST_CHECK_MESSAGE(inputFileName.configs.size()
                        == 2,
                        "Number of configurations different "
                        "from the expected:"
                        << "\nExpected: " << 2
                        << "\nGot:" << inputFileName.configs.size());

    string expectedStr;

    expectedStr = sim_argv[2];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].cellFileName
                        == expectedStr,
                        "\nCell file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].cellFileName);

    expectedStr = sim_argv[3];
    BOOST_CHECK_MESSAGE(inputFileName.configs[1].cellFileName
                        == expectedStr,
                        "\nCell file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[1].cellFileName);

    expectedStr = sim_argv[5];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].techFileName
                        == expectedStr,
                        "\nTechnology file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].techFileName);

    expectedStr = sim_argv[6];
    BOOST_CHECK_MESSAGE(inputFileName.configs[1].techFileName
                        == expectedStr,
                        "\nTechnology file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[1].techFileName);

    expectedStr = sim_argv[8];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].archFileName
                        == expectedStr,
                        "\nArchitecture file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].archFileName);

    expectedStr = sim_argv[9];
    BOOST_CHECK_MESSAGE(inputFileName.configs[1].archFileName
                        == expectedStr,
                        "\nArchitecture file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[1].archFileName);

    BOOST_CHECK_MESSAGE(inputFileName.IOTerminationCurrentFlag == false,
                        "\nIO termination flag missmatch!"
                        << "\nExpected: " << false
                        << "\nGot:" << inputFileName.IOTerminationCurrentFlag);

}

BOOST_AUTO_TEST_CASE( checkInputParametersParser_1each )
{
    int sim_argc = 9;
    char* sim_argv[] = {"./executable",
                        "-cell",
                        "../../tests/cells/test_cell2.json",
                        "-conf",
                        "../../tests/configs/test_config.txt",
                        "-tech",
                        "../../tests/techs/test_tech2.json",
                        "-arch",
                        "../../tests/archs/test_arch2.json"};

    ArgumentsParser inputFileName(sim_argc, sim_argv);

    std::string exceptionMsg("No exception.");
    try {
        inputFileName.runArgParser();
    }catch (string exceptionMsgThrown){
        exceptionMsg = exceptionMsgThrown;
    }

    std::string expectedMsg("No exception.");
    BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedMsg,
                        "Error message different from what was expected."
                        << "\nExpected: " << expectedMsg
                        << "\nGot: " << exceptionMsg);

    BOOST_CHECK_MESSAGE(inputFileName.configs.size()
                        == 2,
                        "Number of configurations different "
                        "from the expected:"
                        << "\nExpected: " << 2
                        << "\nGot:" << inputFileName.configs.size());

    string expectedStr;

    expectedStr = sim_argv[2];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].cellFileName
                        == expectedStr,
                        "\nCell file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].cellFileName);

    expectedStr = "../../tests/cells/test_cell.json";
    BOOST_CHECK_MESSAGE(inputFileName.configs[1].cellFileName
                        == expectedStr,
                        "\nCell file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[1].cellFileName);

    expectedStr = sim_argv[6];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].techFileName
                        == expectedStr,
                        "\nTechnology file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].techFileName);

    expectedStr = "../../tests/techs/test_tech.json";
    BOOST_CHECK_MESSAGE(inputFileName.configs[1].techFileName
                        == expectedStr,
                        "Technology file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[1].techFileName);

    expectedStr = sim_argv[8];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].archFileName
                        == expectedStr,
                        "Architecture file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].archFileName);

    expectedStr = "../../tests/archs/test_arch.json";
    BOOST_CHECK_MESSAGE(inputFileName.configs[1].archFileName
                        == expectedStr,
                        "\nArchitecture file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[1].archFileName);

    BOOST_CHECK_MESSAGE(inputFileName.IOTerminationCurrentFlag == false,
                        "\nIO termination flag missmatch!"
                        << "\nExpected: " << false
                        << "\nGot:" << inputFileName.IOTerminationCurrentFlag);

}

BOOST_AUTO_TEST_CASE( checkInputParametersParser_2cell_2tech_2arch_mixed )
{
    int sim_argc = 11;
    char* sim_argv[] = {"./executable",
                        "-cell",
                        "../../tests/cells/test_cell.json",
                        "-tech",
                        "../../tests/techs/test_tech.json",
                        "../../tests/techs/test_tech2.json",
                        "-cell",
                        "../../tests/cells/test_cell2.json",
                        "-arch",
                        "../../tests/archs/test_arch.json",
                        "../../tests/archs/test_arch2.json"};

    ArgumentsParser inputFileName(sim_argc, sim_argv);

    std::string exceptionMsg("No exception.");
    try {
        inputFileName.runArgParser();
    }catch (string exceptionMsgThrown){
        exceptionMsg = exceptionMsgThrown;
    }

    std::string expectedMsg("No exception.");
    BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedMsg,
                        "Error message different from what was expected."
                        << "\nExpected: " << expectedMsg
                        << "\nGot: " << exceptionMsg);

    BOOST_CHECK_MESSAGE(inputFileName.configs.size()
                        == 2,
                        "Number of configurations different "
                        "from the expected:"
                        << "\nExpected: " << 2
                        << "\nGot:" << inputFileName.configs.size());

    string expectedStr;

    expectedStr = sim_argv[2];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].cellFileName
                        == expectedStr,
                        "\nCell file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].cellFileName);

    expectedStr = sim_argv[7];
    BOOST_CHECK_MESSAGE(inputFileName.configs[1].cellFileName
                        == expectedStr,
                        "\nCell file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[1].cellFileName);

    expectedStr = sim_argv[4];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].techFileName
                        == expectedStr,
                        "\nTechnology file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].techFileName);

    expectedStr = sim_argv[5];
    BOOST_CHECK_MESSAGE(inputFileName.configs[1].techFileName
                        == expectedStr,
                        "\nTechnology file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[1].techFileName);

    expectedStr = sim_argv[9];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].archFileName
                        == expectedStr,
                        "\nArchitecture file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].archFileName);

    expectedStr = sim_argv[10];
    BOOST_CHECK_MESSAGE(inputFileName.configs[1].archFileName
                        == expectedStr,
                        "\nArchitecture file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[1].archFileName);

    BOOST_CHECK_MESSAGE(inputFileName.IOTerminationCurrentFlag == false,
                        "\nIO termination flag missmatch!"
                        << "\nExpected: " << false
                        << "\nGot:" << inputFileName.IOTerminationCurrentFlag);

}

BOOST_AUTO_TEST_CASE( checkInputParametersParser_1each_term_mixed )
{
    int sim_argc = 10;
    char* sim_argv[] = {"./executable",
                        "-cell",
                        "../../tests/cells/test_cell2.json",
                        "-conf",
                        "../../tests/configs/test_config.txt",
                        "-term",
                        "-tech",
                        "../../tests/techs/test_tech2.json",
                        "-arch",
                        "../../tests/archs/test_arch2.json"};

    ArgumentsParser inputFileName(sim_argc, sim_argv);

    std::string exceptionMsg("No exception.");
    try {
        inputFileName.runArgParser();
    }catch (string exceptionMsgThrown){
        exceptionMsg = exceptionMsgThrown;
    }

    std::string expectedMsg("No exception.");
    BOOST_REQUIRE_MESSAGE( exceptionMsg == expectedMsg,
                        "Error message different from what was expected."
                        << "\nExpected: " << expectedMsg
                        << "\nGot: " << exceptionMsg);

    BOOST_CHECK_MESSAGE(inputFileName.configs.size()
                        == 2,
                        "Number of configurations different "
                        "from the expected:"
                        << "\nExpected: " << 2
                        << "\nGot:" << inputFileName.configs.size());

    string expectedStr;

    expectedStr = sim_argv[2];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].cellFileName
                        == expectedStr,
                        "\nCell file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].cellFileName);

    expectedStr = "../../tests/cells/test_cell.json";
    BOOST_CHECK_MESSAGE(inputFileName.configs[1].cellFileName
                        == expectedStr,
                        "\nCell file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[1].cellFileName);

    expectedStr = sim_argv[7];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].techFileName
                        == expectedStr,
                        "\nTechnology file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].techFileName);

    expectedStr = "../../tests/techs/test_tech.json";
    BOOST_CHECK_MESSAGE(inputFileName.configs[1].techFileName
                        == expectedStr,
                        "\nTechnology file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[1].techFileName);

    expectedStr = sim_argv[9];
    BOOST_CHECK_MESSAGE(inputFileName.configs[0].archFileName
                        == expectedStr,
                        "\nArchitecture file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[0].archFileName);

    expectedStr = "../../tests/archs/test_arch.json";
    BOOST_CHECK_MESSAGE(inputFileName.configs[1].archFileName
                        == expectedStr,
                        "\nArchitecture file name missmatch!"
                        << "\nExpected: " << expectedStr
                        << "\nGot:" << inputFileName.configs[1].archFileName);

    BOOST_CHECK_MESSAGE(inputFileName.IOTerminationCurrentFlag == true,
                        "\nIO termination flag missmatch!"
                        << "\nExpected: " << true
                        << "\nGot:" << inputFileName.IOTerminationCurrentFlag);

}

BOOST_AUTO_TEST_CASE( checkInputParametersParser_different_number )
{
    int sim_argc = 8;
    char* sim_argv[] = {"./executable",
                        "-conf",
                        "../../tests/configs/test_config.txt",
                        "-term",
                        "-tech",
                        "../../tests/techs/test_tech2.json",
                        "-arch",
                        "../../tests/archs/test_arch2.json"};

    ArgumentsParser inputFileName(sim_argc, sim_argv);

    std::string exceptionMsg("No exception.");
    try {
        inputFileName.runArgParser();
    }catch (string exceptionMsgThrown){
        exceptionMsg = exceptionMsgThrown;
    }

    string expectedMsg("[ERROR] ");
    expectedMsg.append("Number of cell files (");
    expectedMsg.append("1");
    expectedMsg.append(") is different from ");
    expectedMsg.append("the number of technology files (");
    expectedMsg.append("2");
    expectedMsg.append(") or the number of architecture files (");
    expectedMsg.append("2");
    expectedMsg.append("). Could not proceed.");
    BOOST_CHECK_MESSAGE( exceptionMsg == expectedMsg,
                        "Error message different from what was expected."
                        << "\nExpected: " << expectedMsg
                        << "\nGot: " << exceptionMsg);

}

BOOST_AUTO_TEST_CASE( checkInputParametersParser_wrong_config_file )
{
    int sim_argc = 3;
    char* sim_argv[] = {"./executable",
                        "-conf",
                        "../../tests/configs/wrong_config.txt"};

    ArgumentsParser inputFileName(sim_argc, sim_argv);

    std::string exceptionMsg("No exception.");
    try {
        inputFileName.runArgParser();
    }catch (string exceptionMsgThrown){
        exceptionMsg = exceptionMsgThrown;
    }

    string expectedMsg("[ERROR] ");
    expectedMsg.append("Could not find the configuration file: ");
    expectedMsg.append(sim_argv[2]);
    expectedMsg.append("\n");
    BOOST_CHECK_MESSAGE( exceptionMsg == expectedMsg,
                        "Error message different from what was expected."
                        << "\nExpected: " << expectedMsg
                        << "\nGot: " << exceptionMsg);

}


BOOST_AUTO_TEST_SUITE_END()

#endif // ARGUMENTSPARSERTEST_CPP
