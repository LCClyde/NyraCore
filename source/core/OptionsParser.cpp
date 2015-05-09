/******************************************************************************
 * The MIT License(MIT)
 *
 * Copyright(c) 2015 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/
#include <unordered_map>
#include <iostream>
#include <vector>
#include <core/OptionsParser.h>
#include <core/StringUtils.h>
#include <core/Exception.h>

namespace nyra
{
namespace core
{
/*****************************************************************************/
OptionsParser::Option::Option(const std::string& key,
                              const std::string& dest,
                              const std::string& help) :
    mKeys(key.empty() ? std::vector<std::string>() : split(key, " ")),
    mDest(dest),
    mHelp(help)
{
}

/*****************************************************************************/
OptionsParser::Option& OptionsParser::addOption(const std::string& key,
                                                const std::string& dest,
                                                const std::string& help)
{
    mOptions.push_back(Option(key, dest, help));
    return mOptions.back();
}

/*****************************************************************************/
void OptionsParser::parse(int argc, char** argv)
{
    typedef std::unordered_map<std::string, Option*> KeyMap;
    KeyMap keyMap;
    std::vector<Option*> positionalArguments;
    size_t currentPositional = 0;

    for (size_t ii = 0; ii < mOptions.size(); ++ii)
    {
        if (mOptions[ii].mKeys.empty())
        {
            positionalArguments.push_back(&mOptions[ii]);
        }
        else
        {
            for (size_t jj = 0; jj < mOptions[ii].mKeys.size(); ++jj)
            {
                // Make sure this key was not already assigned
                KeyMap::const_iterator iter = keyMap.find(mOptions[ii].mKeys[jj]);
                if (iter != keyMap.end())
                {
                    throw Exception("Error when parsing command line: Key " +
                            mOptions[ii].mKeys[jj] + " already exists.");
                }

                // Add the key
                keyMap[mOptions[ii].mKeys[jj]] = &mOptions[ii];
            }
        }
    }

    // Loop through argv
    for (size_t ii = 1; ii < static_cast<size_t>(argc); ++ii)
    {
        const std::string argument(argv[ii]);
        KeyMap::const_iterator iter = keyMap.find(argument);

        // Check if for help
        if (argument == "-h" || argument == "--help")
        {
            // Print help
            std::cout << "\nKeyword Arguments:\n";

            // Print non-positional arguments
            for (size_t jj = 0; jj < mOptions.size(); ++jj)
            {
                if (!mOptions[jj].mKeys.empty())
                {
                    for (size_t kk = 0; kk < mOptions[jj].mKeys.size(); ++kk)
                    {
                        std::cout << mOptions[jj].mKeys[kk] << ", ";
                    }
                    std::cout << mOptions[jj].mHelp << "\n";
                }
            }

            std::cout << "-h, --help, Prints this message and exits\n";

            if (!positionalArguments.empty())
            {
                // Print the positional arguments
                std::cout << "\nPositional Arguments:\n";

                for (size_t jj = 0; jj < positionalArguments.size(); ++jj)
                {
                    std::cout << positionalArguments[jj]->mDest << ", "
                              << positionalArguments[jj]->mHelp << "\n";
                }
            }

            // Quit the program
            std::exit(EXIT_SUCCESS);
        }
        else if (iter != keyMap.end())
        {
            // Check if this is a valid keyword
            if (++ii >= static_cast<size_t>(argc))
            {
                throw Exception("No argument provided for: " + argument);
            }

            // Make sure we didn't already set this value
            KeyValueMap::const_iterator destIter =
                    mKeyValues.find(iter->second->mDest);
            if (destIter != mKeyValues.end())
            {
                throw Exception("Unable to reassign argument: " + argument);
            }

            // Add this argument to the list of found values
            mKeyValues[iter->second->mDest] = argv[ii];
        }
        else
        {
            // This is a positional argument
            if (currentPositional < positionalArguments.size())
            {
                mKeyValues[positionalArguments[currentPositional]->mDest] =
                        argument;
                ++currentPositional;
            }
            else
            {
                throw Exception("Unknown command line argument: " + argument);
            }
        }
    }
}
}
}
