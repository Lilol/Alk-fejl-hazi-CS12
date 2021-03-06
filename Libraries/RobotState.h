#pragma once
#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

#include <QDataStream>
#include <QString>
#include <QList>

/**
 * @brief A robot teljes állapotleírása le egy adott időpillanatban.
 *
 * A kommunikáció során ilyen objektumokat küldünk át a robot és a kliens között.
 * A robottól érkezve az aktuális állapotot képviseli, míg az ellenkező irányba küldve
 *  parancsként a kívánt állapotot írja le.
 *
 * A history ilyen objektumok sorozata.
 */
class RobotState : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief A robot állapota
     */
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
        Accelerate = 3,
        /** Önteszt elindult.*/
        Testing = 4,
        /** A tesztelés véget ért, a robot megfelelő állapotban van.*/
        Test_OK = 5,
        /** A teszt véget ért, a robot nem megfelelő állapotban van.*/
        Test_Error = 6
    };

    /**
     * @brief Konstruktor
     */
    RobotState();

    /**
     * @brief Konstruktor adott értékekkel.
     * @param status    Robot állapot
     * @param timestamp Időbélyeg
     * @param x X-irányú pozíció
     * @param y Y-irányú pozíció
     * @param vx X-irányú sebesség
     * @param vy Y-irányú sebesség
     * @param ax X-irányú gyorsulás
     * @param ay Y-irányú gyorsulás
     * @param sensors Faltávolság-érzékelők állapota
     * @param light Robot lámpájának állapota
     */
    RobotState(Status status, qint64 timestamp,
        float x, float y, float vx, float vy, float ax, float ay, bool light, QList<int> sensors);
    RobotState(const RobotState& other);
    ~RobotState() = default;

    void operator=(const RobotState& other);

    /** Állapot (vagy parancs) */
    Q_PROPERTY(Status status READ status WRITE setStatus MEMBER _status NOTIFY statusChanged)
    Status status() const { return _status; }
    void setStatus(const Status status) { _status = status; }

    /** Időbélyeg (ms) */
    Q_PROPERTY(float timestamp READ timestamp WRITE setTimestamp MEMBER _timestamp NOTIFY timestampChanged)
    qint64 timestamp() const { return _timestamp; }
    void setTimestamp(const qint64 timestamp) { _timestamp = timestamp; }

    /** X Pozíció (méter) */
    Q_PROPERTY(float x READ x WRITE setX MEMBER _x NOTIFY xChanged)
    float x() const { return _x; }
    void setX(float x) { _x = x; }
	
	/** Y Pozíció (méter) */
    Q_PROPERTY(float y READ y WRITE setY MEMBER _y NOTIFY yChanged)
    float y() const { return _y; }
    void setY(float y) { _y = y; }

    /** X irányú Sebesség (m/s) */
    Q_PROPERTY(float vx READ vx WRITE setVx MEMBER _vx NOTIFY vxChanged)
    float vx() const { return _vx; }
    void setVx(float vx) { _vx = vx; }
	
	/** Y irányú Sebesség (m/s) */
    Q_PROPERTY(float vy READ vy WRITE setVy MEMBER _vy NOTIFY vyChanged)
    float vy() const { return _vy; }
    void setVy(float vy) { _vy = vy; }

    /** X irányú Gyorsulás (m/s2) */
    Q_PROPERTY(float ax READ ax WRITE setAx MEMBER _ax NOTIFY axChanged)
    float ax() const { return _ax; }
    void setAx(float ax) { _ax = ax; }
	
	/** Y irányú Gyorsulás (m/s2) */
    Q_PROPERTY(float ay READ ay WRITE setAy MEMBER _ay NOTIFY ayChanged)
    float ay() const { return _ay; }
    void setAy(float ay) { _ay = ay; }

    /** A robot lámpájának állapota. */
    Q_PROPERTY(bool light READ light WRITE setLight MEMBER _light NOTIFY lightChanged)
    bool light() const { return _light; }
    void setLight(bool light) { _light = light; }
	
	/** Szenzorok értéke. 4db faltávolság */
    Q_PROPERTY(QList<int> sensors READ sensors WRITE setSensors MEMBER _sensors NOTIFY sensorsChanged)
    QList<int> sensors() const { return _sensors; }
    void setSensors(QList<int> sensors) { _sensors = sensors; }

    /** Az aktuális állapot QStringként. */
    // In QML, it will be accessible as current.statusName
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
	void yChanged();
    void vxChanged();
	void vyChanged();
    void axChanged();
	void ayChanged();
    void lightChanged();
	void sensorsChanged();

private:
    Status _status;
    qint64 _timestamp;
    float _x;   /** X-irányú pozíció (m) */
    float _y;	/** Y-irányú pozíció */
    float _vx;   /** X-irányú sebesség (m/s) */
    float _vy;  /** Y-irányú sebesség (m/s) */
    float _ax;   /** X-irányú Gyorsulás (m/s2) */
    float _ay;  /** Y-irányú Gyorsulás (m/s2) */
    bool _light;   /** Robot lámpájának állapota */
    QList<int> _sensors;  /** Faltávolság-szenzorok értékei */
	
	
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

/*Vektor szerializálása a streambe.
QDataStream &operator<<(QDataStream &, const QList<float>& sensors);

Vektor kiolvasása a streamből.
QDataStream &operator>>(QDataStream &, QList<float> &);*/

#endif // ROBOT_STATE_H
