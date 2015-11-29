#include <QString>
#include <QtTest>

class CommunicationTester : public QObject
{
    Q_OBJECT

public:
    CommunicationTester();

private Q_SLOTS:
    void testPortNumIsSame();
};

CommunicationTester::CommunicationTester()
{
}

void CommunicationTester::testPortNumIsSame()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(CommunicationTester)

#include "CommunicationTester.moc"
