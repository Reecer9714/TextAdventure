#include "ConfigParser.h"

void ConfigParser::Parse(){
    pugi::xml_parse_result result = doc.load_file("config/data.xml");

    if (result)
    {
        std::cout << "Config loaded without errors \n\n";
    }
    else
    {
        std::cout << "XML parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << result.offset << "]\n\n";
    }

    pugi::xml_node entities = doc.child("Entities");

    for (pugi::xml_node entity = entities.child("Entity"); entity; entity = entity.next_sibling("Entity"))
    {
        std::cout << "Entity " << entity.attribute("name").value() << ":\n";
        for (pugi::xml_node component = entity.first_child(); component; component = component.next_sibling())
        {
            std::cout << "\t" << component.name();
            if( component.attribute("value") ){
                std::cout << " = " << component.attribute("value").value();
            }
            std::cout << "\n";
        }
    }
}