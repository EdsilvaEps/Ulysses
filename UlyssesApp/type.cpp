#include "type.h"

QString Type::toString() const{
    if(value == type_en::exe) return "exe";
    if(value == type_en::link) return "link";
    if(value == type_en::script) return "script";
    return "exe";
}
