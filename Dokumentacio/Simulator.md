@page simulator Robot szimulátor

A szimulátort a Simulator osztály foglalja magába, mely belül egy TcpSocketServer és egy RobotState objektumra támaszkodik. 
Minden bejövő üzenetet azonnal feldolgoz és egy QTimer segítségével periodikusan lefuttatja a szimulációt. 
A bejövő üzenetek a RobotCommand osztály példányai.
A RobotCommand kódolja a robotnak küldött parancsokat. 

A szimulátor minden szimulációs lépés után elküldi az állapotát, ami a megelőző állapota, illetve a neki küldött parancs alapján alakul ki.
A Simulator osztály így egy **state típusú tervezési mintát valósít** meg.

A kapcsolódó signal-slot hálózat az alábbi:

![](diagrams/StvSignalMap_Sim.png)