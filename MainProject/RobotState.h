#pragma once
#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H
#include <QDataStream>
#include <QString>
#include <QVector>

/**
 * @brief
 *
 */
class RobotState : public QObject
{
    Q_OBJECT

public:
    enum class Status
    {
        /** Alapállapot. A robot tartja az aktuális gyorsulást. */
        Default = 0,
        /** Reset. Parancsként használjuk. */
        Reset = 1,
        /** Stop parancs. Ez az állapot akkor is érvényes marad, ha megállt a robot. */
        Stopping = 2,
        /** Gyorsítási parancs a robotnak. A gyorsítás mértékét a robot
         * átveszi a RobotState::a tulajdonságból. */
        Accelerate = 3
    };

    RobotState();

    RobotState(Status status, qint64 timestamp,
        float x, float y, float v_x, float v_y, float a_x, float a_y, qint8 light, QVector<bool> sensors);

    ~RobotState() = default;

    // A NOTIFY signalokat nem implementáljuk, mert nincs rájuk szükség.

    /** Állapot (vagy parancs) */
    Q_PROPERTY(Status status READ status WRITE setStatus MEMBER _status NOTIFY statusChanged)
    Status status() const { return _status; }
    void setStatus(const Status status) { _status = status; }

    /** Időbélyeg (ms) */
    Q_PROPERTY(float timestamp READ timestamp WRITE setTimestamp MEMBER _timestamp NOTIFY timestampChanged)
    qint64 timestamp() const { return _timestamp; }
    void setTimestamp(const qint64 timestamp) { _timestamp = timestamp; }

    /** Pozíció (méter) */
    Q_PROPERTY(float x READ x WRITE setX MEMBER _x NOTIFY xChanged)
    float x() const { return _x; }
    void setX(float x) { _x = x; }

    /** Pozíció (méter) */
    Q_PROPERTY(float y READ y WRITE setY MEMBER _y NOTIFY yChanged)
    float y() const { return _y; }
    void setY(float y) { _y = y; }

    /** Sebesség (m/s) */
    Q_PROPERTY(float v_x READ v_x WRITE setVx MEMBER _v_x NOTIFY vChanged)
    float vx() const { return _v_x; }
    void setVx(float v_x) { _v_x = v_x; }

    /** Sebesség (m/s) */
    Q_PROPERTY(float v_y READ v_y WRITE setVy MEMBER _v_y NOTIFY vChanged)
    float vy() const { return _v_y; }
    void setVy(float v_y) { _v_y = v_y; }

    /** Gyorsulás (m/s2) */
    Q_PROPERTY(float a_x READ a_x WRITE setAx MEMBER _a_x NOTIFY aChanged)
    float ax() const { return _a_x; }
    void setAx(float a_x) { _a_x = a_x; }

    /** Gyorsulás (m/s2) */
    Q_PROPERTY(float a_y READ a_y WRITE setAy MEMBER _a_y NOTIFY aChanged)
    float ay() const { return _a_y; }
    void setAy(float a_y) { _a_y = a_y; }

    /** A robot lámpájának állapota. */
    Q_PROPERTY(bool light READ light WRITE setLight MEMBER _light NOTIFY lightChanged)
    float light() const { return _light; }
    void setLight(float light) { _light = light; }

    /** Szenzorok értéke. */
    Q_PROPERTY(QVector<bool> sensors READ sensors WRITE setSensors MEMBER _sensors NOTIFY sensorsChanges)
    QVector<bool> sensors() const { return _sensors; }
    void setLight(QVector<bool> sensors) { _sensors = sensors; }

    /** Az aktuális állapot QStringként. */
    // In QML, it will be accessible as model.statusName
    Q_PROPERTY(QString statusName READ getStatusName NOTIFY statusChanged)

    /** Sorosítja az objektumot a megadott streambe. */
    void WriteTo(QDataStream& stream) const;

    /** Beolvassa az objektumot a streamből. */
    void ReadFrom(QDataStream& stream);

    /** Másolat készítés. */
    // Erre azért van szükség, mert a QObject-ek másolására speciális szabályok vonatkoznak.
    void CopyFrom(const RobotState& other);

    /** Olvaható formában visszaadja az állapotot. */
    QString getStatusName() const;

signals:
    // Ezeket a signalokat most nem használjuk */
    void statusChanged();
    void timestampChanged();
    void xChanged();
    void vChanged();
    void aChanged();
    void lightChanged();

private:
    Status _status;
    qint64 _timestamp;
    float _x;   /** x irányú pozíció (m) */
    float _y;   /** y irányú pozíció (m) */
    float _v_x;   /** x irányú sebesség (m/s) */
    float _v_y;   /** y irányú sebesség (m/s) */
    float _a_x;   /** x irányú gyorsulás (m/s2) */
    float _a_y;   /** y irányú gyorsulás (m/s2) */
    qint8 _light;
    QVector<bool> _sensors;


    /** Az állapotok és szöveges verziójuk közti megfeleltetés.
     * A getStatusName() használja. */
    static std::map<int,QString> statusNames;

    /** Beállítja a statusNames értékeit. A konstruktor hívja. */
    void initStatusNames();
};

/** Beburkolja a RobotState.WriteTo metódust. */
QDataStream &operator<<(QDataStream &, const RobotState &);

/** Beburkolja a RobotState.ReadFrom metódust. */
QDataStream &operator>>(QDataStream &, RobotState &);

/** Vektor szerializálása a streambe. */
QDataStream &operator<<(QDataStream &, const QVector<bool>& sensors);

/** Vektor kiolvasása a streamből. */
QDataStream &operator>>(QDataStream &, QVector<bool> &);

#endif // ROBOTSTATE_H
