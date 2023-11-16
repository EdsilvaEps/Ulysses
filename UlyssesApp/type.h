#ifndef TYPE_H
#define TYPE_H

#include <QObject>

class Type
{
    Q_GADGET
public:
    int value;

    enum type_en {
        link,
        exe,
        script_python,
        script_shell
    };
    Q_ENUM(type_en);


    Type(type_en tp){
        this->value = tp;
    }

    Type(){this->value = type_en::exe; };

    static Type::type_en strToTypeEnum(QString str){
        if(str == "exe") return  type_en::exe;
        if(str == "link") return  type_en::link;
        if(str == "script_python") return  type_en::script_python;
        if(str == "script_shell") return type_en::script_shell;
        return  type_en::exe;
    };

    static QStringList listTypes();

    bool operator==(const Type::type_en& rhs) const{
         return (this->value == rhs);
    }

    QString toString() const;

};



//Type& Type::operator=(const QString& other){
//   Type tp;
//   if(other == "exe") return ;


//}

#endif // TYPE_H
