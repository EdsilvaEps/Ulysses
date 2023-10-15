#ifndef TYPE_H
#define TYPE_H

#include <QObject>

class Type : public QObject
{
    Q_GADGET
public:
    explicit Type(QObject *parent = nullptr);

    enum type {
        link,
        exe,
        script
    };
    Q_ENUM(type);

};

#endif // TYPE_H
