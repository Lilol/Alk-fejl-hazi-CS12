#include <QString>
#include <QtTest>

// A tömörség kedvéért most itt definiáljuk
//  a tesztelendő osztályt.
class Calculator
{
public:
    int add(int a, int b)
    {
        return a+b;
    }
};

class QTestDemoTest : public QObject
{
    Q_OBJECT

public:
    QTestDemoTest();

private Q_SLOTS:
    void testCase1();
    void testCase2();

private:
    Calculator calculator;
};

QTestDemoTest::QTestDemoTest()
    : calculator()
{
}

void QTestDemoTest::testCase1()
{
    QVERIFY2(1+2 == 0, "test1");
}

void QTestDemoTest::testCase2()
{
    QVERIFY2(1+2 == 0, "test1");
}

QTEST_APPLESS_MAIN(QTestDemoTest)

#include "unitTests.moc"
