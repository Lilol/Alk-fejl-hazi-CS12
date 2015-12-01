#include <QString>
#include <QtTest>
#include <Simulator.h>

class SimulatorTester : public QObject
{
    Q_OBJECT

public:
    SimulatorTester();

private Q_SLOTS:
    void testWallDistance();
    void testAccelerationX();
    void testAccelerationY();

private:
    //Simulator simulator;
};

SimulatorTester::SimulatorTester()
{
}

void SimulatorTester::testWallDistance()
{
    //Simulator simulator;
    QVERIFY2(true, "Failure");
}

void SimulatorTester::testAccelerationX()
{
    QVERIFY2(true, "Failure");
}

void SimulatorTester::testAccelerationY()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SimulatorTester)

#include "SimulatorTester.moc"
