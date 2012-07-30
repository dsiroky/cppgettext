/// gettext MO files parser
/// @author David Siroky <siroky@dasir.cz>
/// @license see LICENSE.txt
/// @file

#ifndef __MOPARSER_H
#define __MOPARSER_H

#include <string>
#include <map>
#include <exception>

//########################################################################
//########################################################################

class MoParserError: public std::exception
{
  public:
    const char *m;
    MoParserError(const char *msg) {m = msg;}
    virtual const char* what() const throw() {return m;}
};

class MoParserErrorFormat: public MoParserError
{
  public:
    MoParserErrorFormat(const char *msg): MoParserError(msg) {}
};

//########################################################################
//########################################################################

class MoParser
{
  public:
    std::map<std::string, std::string> translation_map;

    void parse_file(const char *filename);
    void parse_data(const char *data, size_t length);
};

#endif
