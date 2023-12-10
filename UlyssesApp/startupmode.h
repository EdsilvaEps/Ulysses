#ifndef STARTUPMODE_H
#define STARTUPMODE_H

#include <QString>

/* enum class for listing the different startup modes for events
 * the startup modes refer to ways the event can be triggered,
 * either manually, at startup of the computer or by using a
 * previously set date and time
*/
class StartupMode
{
public:

    enum Mode{ manual, atStartup, date };

    StartupMode(Mode mode) : currentMode(mode) {};

    StartupMode(QString mode);

    StartupMode() : currentMode(manual) {};

    QString toString() const;

    bool operator==(const StartupMode::Mode& rhs) const{
         return (this->currentMode == rhs);
    }


private:
    Mode currentMode;

};

#endif // STARTUPMODE_H
