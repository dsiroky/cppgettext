/// C++ gettext interface
/// @author David Siroky <siroky@dasir.cz>
/// @license see LICENSE.txt
/// @file

#include "cppgettext.h"

//######################################################################

Translations::Translations()
{
  fallback = NULL;
}

//######################################################################

Translations::~Translations()
{
  fallback = NULL;
}

//######################################################################

void Translations::set_fallback(Translations *tr_fallback)
{
  fallback = tr_fallback;
}

//######################################################################

const std::string &Translations::gettext(const std::string &original)
{
  auto it = parser.translation_map.find(original);
  if (it == parser.translation_map.end())
  {
    if (fallback != NULL)
      return fallback->gettext(original);
    else
      return original;
  }
  return it->second;
}
