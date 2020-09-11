#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "pugixml.hpp"
#include <iostream>

class ConfigParser {
public:
    pugi::xml_document doc;
    void Parse();
};

#endif
