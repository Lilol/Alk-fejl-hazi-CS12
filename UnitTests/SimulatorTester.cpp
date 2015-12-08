#include <QString>
#include <QtTest>
#include "../Libraries/Simulator.h"
#include <memory>

/** @brief
    A szimulátor tesztelésére alkalmas osztály.*/
class SimulatorTester : public QObject
{
    Q_OBJECT

public:
    SimulatorTester();

private Q_SLOTS:

    /** \addtogroup test A szimulátor tesztfüggvényei
     * A pozíció, sebesség és gyorsulás teszteléséhez.
     *  @{
     */
    void testPosition();
    void testAcceleration();
    void testVelocity();
    /** @}*/

    void initTestCase();

private slots:
    /** A szimulátor ezen a bemeneten jelzi, hogy lezajlott a szimuláció, elérhetőek az adatok.*/
    void dataIn(RobotState state);

signals:
    /** Gyorsítási parancsot küld a szimulátornak.*/
    void dataReady(QDataStream& stream);
    /** Szól a szimulátornak, hogy letelt egységnyi idő.*/
    void sendTick();

private:
    QDataStream testerStream;
    QByteArray buffer;
    RobotCommand command;
    std::unique_ptr<Simulator> simulator;
    RobotState robotState;
    qint64 timeIntervalBeginning;
    const int sentTickCount = 4;

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
    connect(this, SIGNAL(sendTick()), simulator.get(), SLOT(tick()));
    connect(simulator.get(), SIGNAL(stateSet(RobotState)), this, SLOT(dataIn(RobotState)));
    initTesterCommand();

    const qint64 startPos = testerStream.device()->size();
    testerStream << command;
    testerStream.device()->seek(startPos);

    simulator->start(1.0F);

    emit dataReady(testerStream);

    for(uint i = 0; i < sentTickCount; i++)
    {
        emit sendTick();
    }
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
    for(int i = 0; i <= dt; i++)
        distance += i;
    QVERIFY2(currentState.x() == distance, "Position test failed.");
}

QTEST_APPLESS_MAIN(SimulatorTester)

#include "SimulatorTester.moc"
