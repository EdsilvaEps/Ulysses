#include <QtTest>

// add necessary includes here

class EventTest : public QObject
{
    Q_OBJECT

public:
    EventTest();
    ~EventTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

EventTest::EventTest()
{

}

EventTest::~EventTest()
{

}

void EventTest::initTestCase()
{

}

void EventTest::cleanupTestCase()
{

}

void EventTest::test_case1()
{

}

QTEST_APPLESS_MAIN(EventTest)

//#include "tst_eventtest.moc"
