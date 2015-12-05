#include <QString>
#include <QtTest>
#include "../Libraries/Simulator.h"
#include <memory>

class SimulatorTester : public QObject
{
    Q_OBJECT

public:
    SimulatorTester();

private Q_SLOTS:
    void testPosition();
    void testAcceleration();
    void testVelocity();
    void initTestCase();

private slots:
    void dataIn(RobotState state);

signals:
    void dataReady(QDataStream& stream);
    void tick();

private:
    QDataStream testerStream;
    QByteArray buffer;
    RobotCommand command;
    std::unique_ptr<Simulator> simulator;
    RobotState robotState;
    qint64 timeIntervalBeginning;

    void initTesterCommand();
};

SimulatorTester::SimulatorTester():
testerStream(&buffer, QIODevice::ReadWrite)
{
}

void SimulatorTester::initTestCase()
{
    simulator = std::unique_ptr<Simulator>(new Simulator);
    timeIntervalBeginning = -1;
    connect(this, SIGNAL(dataReady(QDataStream&)), simulator.get(), SLOT(dataReady(QDataStream&)));
    connect(this, SIGNAL(tick()), simulator.get(), SLOT(tick()));
    connect(simulator.get(), SIGNAL(stateSet(RobotState)), this, SLOT(dataIn(RobotState)));
    initTesterCommand();

    const qint64 startPos = testerStream.device()->size();
    testerStream << command;
    testerStream.device()->seek(startPos);

    simulator->start(1.0F);

    emit dataReady(testerStream);

    emit tick();
    emit tick();
    emit tick();
    emit tick();
}

void SimulatorTester::dataIn(RobotState state)
{
    qDebug() << "Robot state accepted." << endl;
    robotState = state;

    if(timeIntervalBeginning == -1 && robotState.ax() != 0)
        timeIntervalBeginning = robotState.timestamp();
}

void SimulatorTester::initTesterCommand()
{
    command.setStatus(RobotCommand::Command::Accelerate);
    command.setAccelerationX(1);
    command.setAccelerationY(0);
}

void SimulatorTester::testAcceleration()
{
    RobotState currentState = robotState;
    QVERIFY2(currentState.ax() == command.accelerate_x(), "Acceleration test failed.");
}

void SimulatorTester::testVelocity()
{
    RobotState currentState = robotState;
    int dt = currentState.timestamp() - timeIntervalBeginning;
    qDebug() << "vx: " << currentState.vx() << "dt: " << dt << endl;
    QVERIFY2(currentState.vx() == (float)dt+1.0, "Velocity test failed.");
}

void SimulatorTester::testPosition()
{
    RobotState currentState = robotState;
    int dt = currentState.timestamp() - timeIntervalBeginning;
    qDebug() << "x: " << currentState.x() << "dt: " << dt << endl;

    int distance = 0;
    for(uint i = 0; i <= dt; i++)
        distance += i;
    QVERIFY2(currentState.x() == distance, "Position test failed.");
}

QTEST_APPLESS_MAIN(SimulatorTester)

#include "SimulatorTester.moc"
