#include <iostream>
#include <string>

#include "cppgettext/cppgettext.h"

int main()
{
  Translations c, c2;
  c.parser.parse_file("catalog.mo");
  c2.parser.parse_file("catalog_2.mo");
  c.set_fallback(&c2);
  std::cout << c.gettext(std::string("hello original")) << std::endl;
  std::cout << c.gettext(std::string("a")) << std::endl;
  std::cout << c.gettext(std::string("c")) << std::endl;
  std::cout << c.gettext(std::string("not translated")) << std::endl;
  return 0;
}
