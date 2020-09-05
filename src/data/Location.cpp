#include "Location.h"

Location::Location(std::string name, std::string desc) {
    this->name = name;
    this->description = desc;
};

Location::~Location() {
    //delete[] this->exits;
}

std::string Location::getName(){
    return this->name;
};

std::string Location::getDesc(){
    return this->description;
};

Connection* Location::getExits(){
    return this->exits;
};

std::list<Entity*> Location::getEntities(){
    return this->entities;
};

ErrorCode Location::connectLocation(Direction d, Location *other, ExitStatus s, bool visible){
    if(other == nullptr) {
        return NULLPTR_INPUT;
    }

    if(this->exits[d].connected) {
        return DUPLICATE_CONNECTION;
    }
    
    this->exits[d].loc = other;
    this->exits[d].status = s;
    this->exits[d].visible = visible;
    this->exits[d].connected = true;
    return SUCCESS;
};

void Location::disconnectLocation(Direction d){
    this->exits[d].connected = false;
};

void Location::addEntity(Entity* e){
    this->entities.push_back(e);
};

void Location::removeEntity(Entity* e){
    this->entities.remove(e);
};