#include "RobotStateHistory.h"
#include "../Libraries/RobotState.h"

RobotStateHistory::RobotStateHistory()
    : QObject(nullptr), currentState(nullptr)
{
}

void RobotStateHistory::Add(const RobotState& state)
{
    // TODO Add history cleanup function!
    std::unique_ptr<RobotState> newState = std::make_unique<RobotState>();
    newState->CopyFrom(state);
    stateList.append(newState.get());
    currentState = (RobotState*)newState.get(); // This has to be done before moving ownership
    container.push_back(std::move(newState));

    // Összeállítjuk a grafikon számára az adatszerkezetet.
    // Ezek a listák QList<int> típusú listák, amiket direkt arra hozunk létre, hogy a QML elemek
    //  ezekből olvassák ki az adatokat, mivel erre a fenti container nem alkalmas. (Az std::vector
    //  nem támogatja a Qt metaobject rendszerét.)
    graphTimestamps.clear();
    graphVelocitiesX.clear();
    graphVelocitiesY.clear();
    graphAccelerationsX.clear();
    graphAccelerationsY.clear();
    graphPositionsX.clear();
    graphPositionsY.clear();
    int graphStateNumber = stateList.size() < shownStateNumber ? stateList.size() : shownStateNumber;
    auto it = container.end()-graphStateNumber;
    for(;it!=container.end();++it)
    {
        RobotState *currentState = it->get();
        graphTimestamps.append(currentState->timestamp());
        graphVelocitiesX.append(currentState->vx());
        graphVelocitiesY.append(currentState->vy());
        graphAccelerationsX.append(currentState->ax());
        graphAccelerationsY.append(currentState->ay());
        graphPositionsY.append(currentState->y());
        graphPositionsX.append(currentState->x());
    }

    // Jelezzük a history változását.
    emit historyChanged();
}
