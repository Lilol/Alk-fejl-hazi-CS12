#include "Simulator.h"

Simulator::Simulator(int port)
    : communication(port), state()
{
    // Fogadni akarjuk a parancsokat
    connect(&communication, SIGNAL(dataReady(QDataStream&)), this, SLOT(dataReady(QDataStream&)));
    // Periodikusan futnia kell a szimulációnak
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
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
    state.setLight(0);
    timer.start((long)(intervalSec*1000.0F));
}

void Simulator::tick()
{
    // Fizikai szimuláció
    state.setTimestamp(state.timestamp() + dt);
    state.setX(state.x() + state.vx()*dt);
	state.setY(state.y() + state.vy()*dt);
    state.setVx(state.vx() + state.ax()*dt);
	state.setVy(state.vy() + state.ay()*dt);
	
	// szenzor szimuláció
    QList<float> sensorTemp;
    sensorTemp.append(300-state.y());
    sensorTemp.append(400-state.x());
    sensorTemp.append(300+state.y());
    sensorTemp.append(400+state.x());
	state.setSensors(sensorTemp);
	
	// pozíció szaturáció
	if (state.x() > 400)
	{
		state.setX(400);
	}
	if (state.x() < -400)
	{
		state.setX(-400);
	}
	if (state.y() > 300)
	{
		state.setY(300);
	}
	if (state.y() < -300)
	{
		state.setY(-300);
	}
	
	// sebesség szaturáció
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

    state.setLight( state.vx()==10.0F ? true : false );

    // Magasabb szintű funkciók
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
        state.setLight(0);
        break;
    case RobotState::Status::Stopping:
        if (state.vx() > 1.5F)
        {
            qDebug() << "Simulator: Stop parancs, gyors lassítás";
            state.setAx(-1.0F);
        }
        else if (state.vx() > 0.1F)
        {
            qDebug() << "Simulator: Stop parancs, lassú lassítás";
            state.setAx(-0.05F);
        }
        else if (state.vx() < -1.5F)
        {
            qDebug() << "Simulator: Stop parancs, gyorsítás előre";
            state.setAx(1.0F);
        }
        else if (state.vx() < -0.1F)
        {
            qDebug() << "Simulator: Stop parancs, lassú gyorsítás előre";
            state.setAx(0.05F);
        }
        else
        {
            // Majdnem megállt
            qDebug() << "Simulator: Megállt.";
            state.setStatus(RobotState::Status::Default);
            state.setAx(0.0F);
        }
        break;
    case RobotState::Status::Accelerate:
        // Megjegyzés: a gyorsulás kért értékét már a parancs fogadásakor beállítottuk
        qDebug() << "HIBA: A szimulátor nem kerülhetne a Status::Accelerate állapotba.";
        break;
    default:
        Q_UNREACHABLE();
    }

    qDebug() << "Simulator: tick (" << state.timestamp()
             << "): állapot=" << state.getStatusName()
             << ", x=" << state.x()
             << ", vx=" << state.vx()
             << ", ax=" << state.ax()
             << ", lámpa:" << state.light();

    // Állapot küldése
    if (communication.isConnected())
    {
        communication.send(state);
    }
}

void Simulator::dataReady(QDataStream &inputStream)
{
    RobotCommand receivedCommand;
    receivedCommand.ReadFrom(inputStream);

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
        state.setStatus(RobotState::Status::Default);
        state.setAx(receivedCommand.accelerate_x()+state.ax());
        state.setAy(receivedCommand.accelerate_y()+state.ay());
        break;
    default:
        Q_UNREACHABLE();
    }
}
