#include "../UlyssesApp/event.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <memory>

using namespace testing;

// constructor test for Event class
TEST(EventClassTest, ConstructorTest)
{
    std::unique_ptr<Event> event = std::make_unique<Event>();
    EXPECT_EQ(event->id(), -1);
}

// test for json transformation of an event object
// function getAsJsonObj()
TEST(EventClassTest, JsontTest)
{
    // setup test days of the week list
    QList<Qt::DayOfWeek> daystst;
    daystst.append(Qt::DayOfWeek::Monday);
    std::unique_ptr<Event> event = std::make_unique<Event>(1,"testevent",Type::script,"01:02",daystst);

    // test if received json object is coincides with the specified event obj
    QJsonObject obj = event->getAsJsonObj();
    EXPECT_EQ(obj["id"].toInt(), 1);
    EXPECT_EQ(obj["time"].toString(), "01:02");
    EXPECT_EQ(obj["type"].toString(), "script");

}

