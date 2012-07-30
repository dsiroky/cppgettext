/// C++ gettext interface
/// @author David Siroky <siroky@dasir.cz>
/// @license see LICENSE.txt
/// @file

#include "cppgettext.h"

//######################################################################
//######################################################################

Translations *g_installed_translations = NULL;

//######################################################################
//######################################################################

char *cppgettext(const char *msgid)
{
  if (g_installed_translations != NULL)
    return g_installed_translations->gettext(msgid);
  return (char *)msgid;
}

//######################################################################
//######################################################################

Translations::Translations()
{
  fallback = NULL;
}

//######################################################################

Translations::~Translations()
{
  fallback = NULL;
  // reset global gettext() function
  if (g_installed_translations == this)
    g_installed_translations = NULL;
}

//######################################################################

void Translations::set_fallback(Translations *tr_fallback)
{
  fallback = tr_fallback;
}

//######################################################################

char *Translations::gettext(const char *original)
{
  auto it = parser.translation_map.find(std::string(original));
  if (it == parser.translation_map.end())
  {
    if (fallback != NULL)
      return fallback->gettext(original);
    else
      return (char *)original;
  }
  return (char *)it->second.c_str();
}

//######################################################################

/// "redirect" global gettext() function to this class
void Translations::install()
{
  g_installed_translations = this;
}
