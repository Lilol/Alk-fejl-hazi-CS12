#include "Simulator.h"

Simulator::Simulator(int port)
    : communication(port), state()
{
    // Fogadni akarjuk a parancsokat
    connect(&communication, SIGNAL(dataReady(QDataStream&)), this, SLOT(dataReady(QDataStream&)));
    // Periodikusan futnia kell a szimulációnak
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
}

Simulator::Simulator()
    : communication(1234), state()
{
     connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
     qDebug() << "Timer connected" << endl;
}

void Simulator::start(float intervalSec)
{
    dt = intervalSec;
    state.setStatus(RobotState::Status::Default);
    state.setTimestamp(0);
    state.setX(0.0F);
	state.setY(0.0F);
    state.setVx(0.0F);
	state.setVy(0.0F);
    state.setAx(0.0F);
	state.setAy(0.0F);
    state.setLight(false);
    timer.start((long)(intervalSec*1000.0F));
}

void Simulator::tick()
{
    // Fizikai szimuláció
    doPhisicalSimulation();
	
	// szenzor szimuláció
    doSensorSimulation();
	
	// pozíció szaturáció
    saturatePosition();
	
	// sebesség szaturáció
    saturateVelocity();

    // Lámpa bekapcsolása a sebességtől függően
    state.setLight( sqrt((state.vx()*state.vx() + state.vy()*state.vy())) >= 10.0F ? true : false );

    // Magasabb szintű funkciók
    processStateInfo();

    // Debug információ kiírása
    showDebugInfo();

    // Állapot küldése
    sendState();
}

void Simulator::doPhisicalSimulation()
{
    state.setTimestamp(state.timestamp() + dt);
    state.setX(state.x() + state.vx()*dt);
    state.setY(state.y() + state.vy()*dt);
    state.setVx(state.vx() + state.ax()*dt);
    state.setVy(state.vy() + state.ay()*dt);
}

void Simulator::doSensorSimulation()
{
    QList<int> sensorTemp;
    sensorTemp.append(300-state.y());
    sensorTemp.append(400-state.x());
    sensorTemp.append(300+state.y());
    sensorTemp.append(400+state.x());
    state.setSensors(sensorTemp);
}

void Simulator::saturatePosition()
{
    if (state.x() > 375)
    {
        state.setX(375);
    }
    if (state.x() < -375)
    {
        state.setX(-375);
    }
    if (state.y() > 275)
    {
        state.setY(275);
    }
    if (state.y() < -275)
    {
        state.setY(-275);
    }
}

void Simulator::saturateVelocity()
{
    if (state.vx()<-10.0)
    {
        state.setVx( -10.0F );
    }
    if (state.vx()>10.0)
    {
        state.setVx( 10.0F );
    }

    if (state.vy()<-10.0)
    {
        state.setVy( -10.0F );
    }
    if (state.vy()>10.0)
    {
        state.setVy( 10.0F );
    }
}

int Simulator::selfTest()
{
    state.setX(1.0F);
    state.setY(1.0F);
    state.setLight(true);
    if(state.x()-1.0 > 0.001 || state.y()-1.0 > 0.001 || state.light() != true)     // float miatt kell a kivonás
    {
        return -1;
    }
    state.setVx(1.0F);
    state.setVy(1.0F);
    if(state.vx()-1.0 > 0.001 || state.vy()-1.0 > 0.001)
    {
        return -1;
    }
    state.setAx(1.0F);
    state.setAy(1.0F);
    if(state.ax()-1.0 > 0.001 || state.ay()-1.0 > 0.001)
    {
        return -1;
    }

    state.setX(0.0F);
    state.setY(0.0F);
    state.setLight(false);
    state.setVx(0.0F);
    state.setVy(0.0F);
    state.setAx(0.0F);
    state.setAy(0.0F);

    return 1;
}

void Simulator::processStateInfo()
{
    switch(state.status())
    {
    case RobotState::Status::Default:
        break;
    case RobotState::Status::Reset:
        qDebug() << "Simulator: Reset";
        state.setStatus(RobotState::Status::Default);
        state.setX(0.0F);
        state.setY(0.0F);
        state.setVx(0.0F);
        state.setVy(0.0F);
        state.setAx(0.0F);
        state.setAy(0.0F);
        state.setLight(false);
        break;
    case RobotState::Status::Stopping:
        if (state.vx() > 1.5F)
        {
            qDebug() << "Simulator: Stop parancs, gyors lassítás X irányban";
            state.setAx(-1.0F);
        }
        else if (state.vx() > 0.1F)
        {
            qDebug() << "Simulator: Stop parancs, lassú lassítás X irányban";
            state.setAx(-0.05F);
        }
        else if (state.vx() < -1.5F)
        {
            qDebug() << "Simulator: Stop parancs, gyorsítás előre X irányban";
            state.setAx(1.0F);
        }
        else if (state.vx() < -0.1F)
        {
            qDebug() << "Simulator: Stop parancs, lassú gyorsítás előre X irányban";
            state.setAx(0.05F);
        }
        else
        {
            // Majdnem megállt
            qDebug() << "Simulator: X irányú sebesség 0-ra csökkent.";
            state.setStatus(RobotState::Status::Default);
            state.setAx(0.0F);
        }

        if (state.vy() > 1.5F)
        {
            qDebug() << "Simulator: Stop parancs, gyors lassítás y irányban";
            state.setAy(-1.0F);
        }
        else if (state.vy() > 0.1F)
        {
            qDebug() << "Simulator: Stop parancs, lassú lassítás y irányban";
            state.setAy(-0.05F);
        }
        else if (state.vy() < -1.5F)
        {
            qDebug() << "Simulator: Stop parancs, gyorsítás y irányban előre";
            state.setAy(1.0F);
        }
        else if (state.vy() < -0.1F)
        {
            qDebug() << "Simulator: Stop parancs, lassú gyorsítás előre y irányban";
            state.setAy(0.05F);
        }
        else
        {
            // Majdnem megállt
            qDebug() << "Simulator: Y irányú sebesség 0-ra csökkent.";
            state.setAy(0.0F);
        }
        break;
    case RobotState::Status::Accelerate:
        // Megjegyzés: a gyorsulás kért értékét már a parancs fogadásakor beállítottuk
        qDebug() << "HIBA: A szimulátor nem kerülhetne a Status::Accelerate állapotba.";
        break;
     case RobotState::Status::Testing:
        if(selfTest() != -1)
        {
            state.setStatus(RobotState::Status::Test_OK);
        }
        else
        {
            state.setStatus(RobotState::Status::Test_Error);
        }
        break;
    case RobotState::Status::Test_OK:
            state.setStatus(RobotState::Status::Reset);
        break;
    case RobotState::Status::Test_Error:
            state.setStatus(RobotState::Status::Reset);
        break;
    default:
        Q_UNREACHABLE();
    }
}

void Simulator::showDebugInfo()
{
    qDebug() << "Simulator: tick (" << state.timestamp()
             << "): állapot=" << state.getStatusName()
             << ", x=" << state.x()
             << ", vx=" << state.vx()
             << ", ax=" << state.ax()
             << ", lámpa:" << state.light();
}

void Simulator::sendState()
{
    RobotState s = state;
    emit stateSet(s);
    if (communication.isConnected())
    {
        communication.send(state);
    }
}

void Simulator::dataReady(QDataStream &inputStream)
{
    RobotCommand receivedCommand;
    receivedCommand.ReadFrom(inputStream);
    qDebug() << "recieved command" << (int)receivedCommand.command() << endl;

    switch(receivedCommand.command())
    {
    case RobotCommand::Command::Default:
        qDebug() << "Simulator: OK parancs. Igen, minden OK, köszönöm!";
        break;
    case RobotCommand::Command::Reset:
        qDebug() << "Simulator: Reset parancs.";
        state.setStatus(RobotState::Status::Reset);
        break;
    case RobotCommand::Command::Stopping:
        qDebug() << "Simulator: Stop parancs.";
        state.setStatus(RobotState::Status::Stopping);
        break;
    case RobotCommand::Command::Accelerate:
        qDebug() << "Simulator: Gyorsítási parancs.";
        state.setStatus(RobotState::Status::Accelerate);
        state.setAx(receivedCommand.accelerate_x()+state.ax());
        state.setAy(receivedCommand.accelerate_y()+state.ay());
        break;
    case RobotCommand::Command::Test:
        qDebug() << "Simulator: Teszt parancs.";
        state.setStatus(RobotState::Status::Testing);
        break;
    default:
        Q_UNREACHABLE();
    }
}

float Simulator::getSumVelocity()
{
    return sqrt(state.vx()*state.vx() + state.vy()*state.vy());
}
