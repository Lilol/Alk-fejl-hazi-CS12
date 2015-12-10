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

    /** Pozíció tesztelő függvény. */
    void testPosition();
	/** Gyorsulás tesztelő függvény. */
    void testAcceleration();
	/** Sebesség tesztelő függvény. */
    void testVelocity();

	/** A teszteléshez szükséges parancs elküldése, a szimulátor indítása. */
    void initTestCase();
	
private:
    QDataStream testerStream; /** Adatküldő stream, amivel a szimulátornak adott parancsot küldjük. */
	QByteArray buffer;     /** Ebbe a bufferbe írjuk a @see SimulatorTester::command parancsot a küldés előtt. */
    RobotCommand command; 	/** Kiadott parancs */
    std::unique_ptr<Simulator> simulator;
    RobotState robotState; 	/** A szimulátor aktuális állapota, aminek helyességét az osztály vizsgálja. */
    qint64 timeIntervalBeginning; 	/** Mely pillanattól kezdődik az időmérés, amihez képest a sebesség- és pozícióváltozást mérjük. */
    const int sentTickCount = 4; 	/** A szimulátorban ennyi időegység telik el a tesztek ellenőrzése előtt.*/

    void initTesterCommand();

private slots:
    /** A szimulátor ezen a bemeneten jelzi, hogy lezajlott a szimuláció, elérhetőek az adatok.*/
    void dataIn(RobotState state);

signals:
    /** Gyorsítási parancsot küld a szimulátornak.*/
    void dataReady(QDataStream& stream);
    /** Szól a szimulátornak, hogy letelt egységnyi idő.*/
    void sendTick();
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
