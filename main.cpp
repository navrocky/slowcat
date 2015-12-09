#include <iostream>
#include <fstream>

#include <boost/program_options.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

namespace po = boost::program_options;
namespace bc = boost::chrono;
using namespace std;

void showHelp(const po::options_description& desc)
{
    cout << "\nSlowCat\n\n";
    cout << "Usage: slowcat [options] <input file>\n\n";
    cout << desc << "\n";
}

int main(int argc, char** argv)
{
    po::options_description desc("Options");
    desc.add_options()
            ("help", "this help")
            ("portion,P", po::value<int>(), "portion size in bytes")
            ("rate,R", po::value<float>(), "read rate in portions per second")
            ;

    po::options_description hiddenDesc("Hidden options");
    hiddenDesc.add_options()
            ("input", po::value<string>(), "Input file");

    hiddenDesc.add(desc);

    po::positional_options_description pd;
    pd.add("input", 1);

    po::command_line_parser parser(argc, argv);
    parser.options(hiddenDesc).positional(pd);

    po::variables_map vm;
    try
    {
        po::store(parser.run(), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            showHelp(desc);
            return 0;
        }

        po::variable_value v = vm["input"];
        if (v.empty())
            throw runtime_error("No input file");
        string fileName = v.as<string>();

        int portionSize = 1024;
        v = vm["portion"];
        if (!v.empty())
            portionSize = v.as<int>();

        float rate = 0;
        v = vm["rate"];
        if (!v.empty())
            rate = v.as<float>();

        vector<char> buf(portionSize, 0);

        ifstream s(fileName.c_str(), ios_base::in);

        int iterationMsecs = rate != 0.0 ? 1000.0 / rate : 0;

        while (!s.eof())
        {
            using namespace boost::chrono;

            time_point<high_resolution_clock> startTime = high_resolution_clock::now();

            s.read(buf.data(), portionSize);
            int readed = s.gcount();
            cout.write(buf.data(), readed);

            time_point<high_resolution_clock> endTime = high_resolution_clock::now();

            int msecs = duration_cast<milliseconds>(endTime - startTime).count();
            int waitForMsecs = iterationMsecs - msecs;
            if (waitForMsecs > 0)
                boost::this_thread::sleep_for(milliseconds(waitForMsecs));
        }
    }
    catch (const exception& e)
    {
        cerr << "\nError: " << e.what() << endl;
        showHelp(desc);
        return 1;
    }

    return 0;
}

