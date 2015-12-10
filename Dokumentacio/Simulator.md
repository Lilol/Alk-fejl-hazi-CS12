@page simulator Robot szimulátor

A szimulátort a Simulator osztály foglalja magába, mely belül egy TcpSocketServer és egy RobotState objektumra támaszkodik. 
A szimulátor és környezete a következő diagramon látható:

![](diagrams/simulator_kornyezete.png)

Minden bejövő üzenetet azonnal feldolgoz és egy QTimer segítségével periodikusan lefuttatja a szimulációt. 
A bejövő üzenetek a RobotCommand osztály példányai.
A RobotCommand kódolja a robotnak küldött parancsokat (gyorsítás, megállás, teszt üzem, reset).

A szimulátor minden szimulációs lépés után elküldi az állapotát, ami a megelőző állapota, illetve a neki küldött parancs alapján alakul ki.
A Simulator osztály így egy **state típusú tervezési mintát valósít** meg.

A robot öntesztelő funkcióval rendelkezik, azaz a Test gomb megnyomásakor ellenőrzi a szimulátor beállításait, majd visszaküldi az eredményt a felhasználói felületnek.
A tesztelési fázis után a robot automatikusan reseteli magát.

