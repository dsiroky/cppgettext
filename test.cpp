#include <iostream>
#include <string>

#include "cppgettext/cppgettext.h"

#define _(msg) cppgettext(msg)

int main()
{
  Translations c, c2;
  c.parser.parse_file("catalog.mo");
  c2.parser.parse_file("catalog_2.mo");
  c.set_fallback(&c2);
  std::cout << c.gettext("hello original") << std::endl;
  std::cout << c.gettext("a") << std::endl;
  std::cout << c.gettext("c") << std::endl; // this is not in catalog
  std::cout << c.gettext("not translated") << std::endl;

  std::cout << std::endl;
  std::cout << cppgettext("hello original") << std::endl;
  c.install();
  std::cout << cppgettext("hello original") << std::endl;
  std::cout << _("hello original") << std::endl;

  return 0;
}
