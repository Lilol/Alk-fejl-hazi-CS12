#include <QString>
#include <QtTest>

class UnitTests : public QObject
{
    Q_OBJECT

public:
    UnitTests();

private Q_SLOTS:
    void testCase1();
};

UnitTests::UnitTests()
{
}

void UnitTests::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(UnitTests)

#include "tst_UnitTests.moc"
