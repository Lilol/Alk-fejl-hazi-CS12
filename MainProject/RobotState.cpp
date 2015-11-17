#include <QDebug>
#include <QVector>
#include "RobotState.h"

std::map<int,QString> RobotState::statusNames;

RobotState::RobotState()
{
    initStatusNames();
}

RobotState::RobotState(Status status, qint64 timestamp,
                       float x, float y, float v_x, float v_y, float a_x, float a_y, qint8 light, QVector<bool> sensors)
    : _status(status), _timestamp(timestamp), _x(x), _y(y), _v_x(v_x), _v_y(v_y), _a_x(a_x), _a_y(a_y), _light(light), _sensors(sensors)
{
    initStatusNames();
}

void RobotState::initStatusNames()
{
    if (statusNames.empty())
    {
        // Még nincsen inicializálva.
        statusNames[(int)Status::Accelerate] = QString("Gyorsítás");
        statusNames[(int)Status::Default] = QString("Alap");
        statusNames[(int)Status::Reset] = QString("Reset");
        statusNames[(int)Status::Stopping] = QString("Megállás");
    }
}

QString RobotState::getStatusName() const
{
    auto it = statusNames.find((int)_status);
    Q_ASSERT(it != statusNames.end());
    return it->second;
}

void RobotState::WriteTo(QDataStream& stream) const
{
    stream << (qint32)_status;
    stream << _timestamp;
    stream << _x;
    stream << _y;
    stream << _v_x;
    stream << _v_y;
    stream << _a_x;
    stream << _a_y;
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
    stream >> _v_x;
    stream >> _v_y;
    stream >> _a_x;
    stream >> _a_y;
    stream >> _light;
    stream >> _sensors;
}

void RobotState::CopyFrom(const RobotState &other)
{
    _status = other._status;
    _timestamp = other._timestamp;
    _x = other._x;
    _y = other._y;
    _v_x = other._v_x;
    _v_y = other._v_y;
    _a_x = other._a_x;
    _a_y = other._a_y;
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

QDataStream &operator<<(QDataStream& stream, const QVector<bool>& sensors)
{
    stream << sensors.size();
    for(const auto sensorValue : sensors)
    {
        stream << sensorValue;
    }
    return stream;
}

QDataStream &operator>>(QDataStream& stream, QVector<bool>& sensors)
{
    uint size;
    sensors.clear();
    stream >> size;
    for(uint i = 0; i < size; i++)
    {
        int sensorValue;
        stream >> sensorValue;
        sensors << sensorValue;
    }
    return stream;
}
