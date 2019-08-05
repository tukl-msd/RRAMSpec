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


#include "RramSpec.h"

using namespace std;

RRAMSpec::RRAMSpec(int argc, char** argv)
{
    runRramSpec(argc, argv);
}


//function for writing results in csv file or cout
string
RRAMSpec::arrangeOutput(const string outputType)
{
    int lineWidth;
    string separator;
    // If outputing to csv file, keep the lines as short as possible
    //  and add a comma separator between label and value
    if (outputType == "csv") {
        lineWidth = 0;
        separator = ",";
    }
    // If outputing to terminal, build a more human readable table
    else if (outputType == "stdout") {
        lineWidth = 30;
        separator = "";
    } else {
        std::string exceptionMsgThrown("[ERROR] ");
        exceptionMsgThrown.append("Unexpected behaviour - ");
        exceptionMsgThrown.append("could not decide on output type.");
        throw exceptionMsgThrown;
    }

    ostringstream resultTable;

    resultTable
      //<< BUILD_LINE("tPD              ", bank->getTpd())
      << BUILD_LINE("tCCDR            ", bank->getTccdr())
      << BUILD_LINE("tCCDW            ", bank->getTccdw())
      << BUILD_LINE("tRL              ", bank->getTrl())
      << BUILD_LINE("tWL              ", bank->getTwl())

      //<< BUILD_LINE("ePRE             ", bank->getPrechargeEnergy())
      << BUILD_LINE("eRD              ", bank->getReadEnergy())
      << BUILD_LINE("eWR              ", bank->getWriteEnergy())

      << BUILD_LINE("Leakage Power    ", bank->getLeakagePower())
      
      << BUILD_LINE("Wordlines per Subarray  ", bank->subarray.getNRows())
      << BUILD_LINE("Bitlines per Subarray  ", bank->subarray.getNCols())
      
      << BUILD_LINE("Subarrays per Row  ", bank->getNSubarraysPerRow())
      << BUILD_LINE("Subarrays per Col ", bank->getNSubarraysPerCol())     

      << BUILD_LINE("Subarray height  ",
          SCALE_QUANTITY(bank->subarray.getHeight(), rrs::micrometer_unit))
      << BUILD_LINE("Subarray width   ",
          SCALE_QUANTITY(bank->subarray.getWidth(), rrs::micrometer_unit))
      << BUILD_LINE("Bank height      ",
          SCALE_QUANTITY(bank->getHeight(), rrs::millimeter_unit))
      << BUILD_LINE("Bank width       ",
          SCALE_QUANTITY(bank->getWidth(), rrs::millimeter_unit))
      << BUILD_LINE("Bank area        ",
          SCALE_QUANTITY(bank->getArea(), rrs::square_millimeter_unit))
      ;

    return resultTable.str();
}

void RRAMSpec::runRramSpec(int argc, char** argv)
{
    arg = new ArgumentsParser(argc, argv);

    arg->runArgParser();

    if ( !arg->helpStrStream.str().empty() ) {
        output << arg->helpStrStream.str();
        return;
    }

    output << "_______________________________________________________"
           << "_______________________________________________________"
           << "_______________________________________________________"
           << endl;

    //Loop through all the corresponding inputs (cell, tech and arch files)
    // and fill the array to print in a clean layout
    for(size_t configID = 0; configID < arg->configs.size(); ++configID)
    {
//        ofstream csvResultFile;
//        string csvResultFileName("results_for_config_");
//        csvResultFileName.append(to_string(configID));
//        csvResultFileName.append(".csv");
//        csvResultFile.open(csvResultFileName, ofstream::trunc);

        output << "RRAM Configuration: "
               << configID+1
               << endl;
        output << "\tCell filename: "
               << arg->configs.at(configID).cellFileName
               << endl;
        output << "\tTechnology filename: "
               << arg->configs.at(configID).techFileName
               << endl;
        output << "\tArchitecture filename:  "
               << arg->configs.at(configID).archFileName
               << endl;

        try{
            bank = new Bank(arg->configs.at(configID));
        } catch(string exceptionMsgThrown) {
            throw exceptionMsgThrown;
        }
//        jsonOutputWrite(configID+1);

//        csvResultFile << "Label,"
//                      << "Technology filename: " << arg->technologyFileName[configID]
//                      << "  Parameter filename: " << arg->architectureFileName[configID]
//                      << endl;

//        try {
//            csvResultFile << arrangeOutput("csv");
//        } catch(string exceptionMsgThrown) {
//            throw exceptionMsgThrown;
//        }
//        csvResultFile.close();

        try {
            output << arrangeOutput("stdout") << endl;
        } catch(string exceptionMsgThrown) {
            throw exceptionMsgThrown;
        }

        if (arg->printAllVariables) {
        }

        output  << "_______________________________________________________"
                << "_______________________________________________________"
                << "_______________________________________________________"
                << endl;

    }
}
