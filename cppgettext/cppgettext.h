/// C++ gettext interface
/// @author David Siroky <siroky@dasir.cz>
/// @license see LICENSE.txt
/// @file

#ifndef __CPPGETTEXT_H
#define __CPPGETTEXT_H

#include <deque>

#include "moparser.h"

//##########################################################################
//##########################################################################

char *cppgettext(const char *msgid);

//##########################################################################
//##########################################################################

class Translations
{
  public:
    MoParser parser;
    Translations *fallback;

    Translations();
    virtual ~Translations();
    void set_fallback(Translations *tr_fallback);
    virtual char *gettext(const char *original);
    void install();
};

#endif
