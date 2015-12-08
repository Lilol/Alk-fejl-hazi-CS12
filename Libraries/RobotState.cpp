#include <QDebug>
#include "RobotState.h"

std::map<int,QString> RobotState::statusNames;

RobotState::RobotState()
{
    initStatusNames();
}

RobotState::RobotState(Status status, qint64 timestamp,
    float x, float y, float vx, float vy, float ax, float ay, bool light, QList<int> sensors)
    : _status(status), _timestamp(timestamp), _x(x), _y(y), _vx(vx), _vy(vy), _ax(ax), _ay(ay), _light(light), _sensors(sensors)
{
    initStatusNames();
}

RobotState::RobotState(const RobotState& other)
{
    _x = other.x();
    _y = other.y();
    _vx = other.vx();
    _vy = other.vy();
    _ax = other.ax();
    _ay = other.ay();
    _status = other.status();
    _timestamp = other.timestamp();
    _light = other.light();
    _sensors = other.sensors();
}

void RobotState::operator=(const RobotState& other)
{
    _x = other.x();
    _y = other.y();
    _vx = other.vx();
    _vy = other.vy();
    _ax = other.ax();
    _ay = other.ay();
    _status = other.status();
    _timestamp = other.timestamp();
    _light = other.light();
    _sensors = other.sensors();
}

void RobotState::initStatusNames()
{
    if (statusNames.empty())
    {
        // Még nincsen inicializálva.
        statusNames[(int)Status::Accelerate] = QString("acceleration");
        statusNames[(int)Status::Default] = QString("default");
        statusNames[(int)Status::Reset] = QString("reset");
        statusNames[(int)Status::Stopping] = QString("stopping");
    }
}

QString RobotState::getStatusName() const
{
    auto it = statusNames.find((int)_status);
    Q_ASSERT(it != statusNames.end());
    qDebug() << it->second << endl;
    return it->second;
    //return QString("debug");
}

void RobotState::WriteTo(QDataStream& stream) const
{
    stream << (qint32)_status;
    stream << _timestamp;
    stream << _x + 400;
    stream << _y + 300;
    stream << _vx;
	stream << _vy;
    stream << _ax;
	stream << _ay;
    stream << _light;
	stream << _sensors;
}

void RobotState::ReadFrom(QDataStream& stream)
{
    qint32 tmpQint32;
    stream >> tmpQint32;
    _status = (Status)tmpQint32;
    stream >> _timestamp;
    stream >> _x;
	stream >> _y;
    stream >> _vx;
	stream >> _vy;
	stream >> _ax;
    stream >> _ay;
    stream >> _light;
	stream >> _sensors;
}

void RobotState::CopyFrom(const RobotState &other)
{
    _status = other._status;
    _timestamp = other._timestamp;
    _x = other._x;
	_y = other._y;
    _vx = other._vx;
	_vy = other._vy;
    _ax = other._ax;
    _ay = other._ay;
    _light = other._light;
	_sensors = other._sensors;
}

QDataStream &operator<<(QDataStream& stream, const RobotState& state)
{
    state.WriteTo(stream);
    return stream;
}

QDataStream &operator>>(QDataStream& stream, RobotState& state)
{
    state.ReadFrom(stream);
    return stream;
}
