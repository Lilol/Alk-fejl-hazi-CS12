@page communication Kommunikáció

A kommunikációért felelős osztályok egy általános TCP kommunikációt megvalósító interfészre (TcpCommunication osztály) épülnek. 

A TcpCommunication osztály egy **strategy típusú tervezési mintát valósít meg**, mert egységes interfészt biztosít a kommunikáció két irányát megvalósító TcpSocketServer és TcpSocketClient osztályoknak.
A kliens és a szerver gyakorlatilag csak a kapcsolat felépítésében és lebontásában különbözik, ezeknek az eltéréseknek a megvalósításával egészíti ki az ősosztályt.

A TCP/IP interfészen keresztül küldhetünk adatokat a TcpSocketServer osztály és fogadhatunk adatokat a TcpSocketClient osztály segítségével. 
Ezt az alábbi osztály diagram szemlélteti:

![](diagrams/communication_and_kornyezet.png)

A működési alapelve, hogy a TcpCommunication::send() metódussal bármilyen objektumot ki lehet írni a küldési bufferbe, amire értelmezett az operator<< QDataStream-re. 
A TcpCommunication::send() metúdus ennek segítségével sorosítja az üzenet objektumot, majd a TcpCommunication::sendBufferContent() metódussal elküldi azt.

Adatok fogadása esetén minden adat egy általános streambe érkezik (TcpCommunication::receiveStream) és egy signal (TcpCommunication::dataReady) jelzi, ha egy teljes üzenet megérkezett. 
Erre a TcpCommunication::dataReady() signalra iratkozik fel a RobotProxy, hogy fogadni tudja az üzeneteket.

Az adatküldés szekvencia diagramja a következő:

![Data sending sequence diagram](diagrams/send_SequenceDiagram.png)

A küldéshez a TcpCommunication::send() elkéri a küldési adatstreamet (TcpCommunication::getSendStream hívása), ebbe sorosítja a küldendő objektumot, majd a sendBufferContent() hívásával elküldi az adatokat.

Adatok fogadása esetén az alábbi szekvencia diagram foglalja össze az eseményeket:

![Data reception sequence diagram](diagrams/receive_SequenceDiagram.png)

A kommunikáció mélyén lévő QTcpSocket a kliens dataReceived slotján kereszül jelzi, hogy érkezett adat. 
Mivel ilyenkor nem biztos, hogy a bufferben már egy egész üzenet benne van, így a kommunikáció csak akkor szól tovább a RobotProxynak (a TcpCommunication::dataReady signaljával), ha elegendő adat összegyűlt. 

Amennyiben egy teljes adatcsomag átjött, a RobotProxy ezt kiolvassa (ehhez létrehoz egy új RobotState példányt), majd azt továbbítja a RobotStateHistory példányának. 
A history pedig ezt egyrészt elmenti, másrészt a historyChanged() signal segítségével jelez a felhasználói felületnek, hogy frissíteni kell a megjelenítést.

Végezetül még a kommunikációval kapcsolatos signal-slot hálózat képe az alábbi:

![](diagrams/StvSignalMap_Comm.png)

(Az ábrán négyzetekben láthatók az érintett objektumok, bal oldalukon a slotjaik, jobb oldalon pedig a signaljaik, valamint ezek kapcsolatai.)