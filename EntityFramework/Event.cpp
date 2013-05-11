#include "Event.h"

std::size_t BaseEvent::counter=0;


EntityAddedEvent::EntityAddedEvent(Entity * e_):e(e_){}

EntityRemovedEvent::EntityRemovedEvent(Entity * e_):e(e_){}

EntityChangedEvent::EntityChangedEvent(Entity * e_):e(e_){}

