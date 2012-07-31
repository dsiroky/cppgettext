/// gettext MO files parser
/// @author David Siroky <siroky@dasir.cz>
/// @license see LICENSE.txt
/// @file

#include <iostream>
#include <fstream>
#include <memory>
#include <stdint.h>

#include "moparser.h"

//########################################################################
//########################################################################

#define LE_MAGIC 0x950412de
#define BE_MAGIC 0xde120495

//########################################################################
//########################################################################

// TODO correct endianess

uint32_t swap_le(const char *buf, size_t ofs)
{
  return *((uint32_t *)(buf + ofs));
}

uint32_t swap_be(const char *buf, size_t ofs)
{
  return *((uint32_t *)(buf + ofs));
}

//########################################################################
//########################################################################

void MoParser::parse_file(const char *filename)
{
  std::ifstream fr(filename, std::iostream::in | std::iostream::binary);
  if (!fr.is_open()) throw MoParserError("can't open file for reading");
  fr.seekg(0, std::iostream::end);
  size_t size = fr.tellg();
  fr.seekg(0, std::iostream::beg);

  std::unique_ptr<char[]> buf(new char[size]);
  fr.read(buf.get(), size);
  parse_data(buf.get(), size);
}

//########################################################################

#define check_range(ofs) if (ofs >= length) throw MoParserErrorFormat("wrong address");

//########################################################################

void MoParser::parse_data(const char *data, size_t length)
{
  translation_map.clear();

  uint32_t (*swap)(const char *, size_t);
  if (((uint32_t *)data)[0] == LE_MAGIC) {
    swap = &swap_le;
  } else if (((uint32_t *)data)[0] == BE_MAGIC) {
    swap = &swap_be;
  } else
    throw MoParserError("unknown magic number");
  
  uint32_t number_of_strings = swap(data, 8);
  uint32_t ofs_original = swap(data, 12);
  uint32_t ofs_translated = swap(data, 16);
  check_range(ofs_original + 8);
  check_range(ofs_translated + 8);
  for (unsigned i = 0; i < number_of_strings; i++)
  {
    uint32_t original_len = swap(data, ofs_original + i * 8);
    uint32_t original_ofs = swap(data, ofs_original + 4 + i * 8);
    uint32_t translated_len = swap(data, ofs_translated + i * 8);
    uint32_t translated_ofs = swap(data, ofs_translated + 4 + i * 8);
    check_range(original_ofs + original_len);
    check_range(translated_ofs + translated_len);
    std::string original(&(data[original_ofs]), original_len);
    std::string translated(&(data[translated_ofs]), translated_len);
    translation_map[original] = translated;
  }
}
