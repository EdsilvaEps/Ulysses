#include "type.h"

QString Type::toString() const{
    if(value == type_en::exe) return "exe";
    if(value == type_en::link) return "link";
    if(value == type_en::script_python) return "script_python";
    if(value == type_en::script_shell) return "script_shell";
    return "exe";
}

QStringList Type::listTypes()
{
    return {"link","exe","script_python", "script_shell"};
}
