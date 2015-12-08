@mainpage
@tableofcontents

@section video Videó
Az alkalmazást bemutató videóért kattints [ide](https://www.aut.bme.hu/) .

@section git Verziókövetés
A fejlesztés verziókövetéséről bővebben: @ref gitleiras .

@section Architektura Architektúra áttekintés

Az alkalmazás fő részei:

   * @ref representation : ez felelős a robot állapotának követéséért, valamint a korábbi állapotok eltárolásáért a későbbi megjelenítéshez.
   * @ref simulator : szimulálja a robot mozgását és válaszait a küldött parancsokra.
   * @ref gui : QML alapú megjelenítése a vezérlő nyomógomboknak, valamint az aktuális és korábbi állapotoknak.
   * @ref communication : TCP/IP alapú kommunikáció a szimulációval. A kommunikációs adatcsomagok a RobotState osztály példányait küldik a qml oldalnak, ebben továbbítódnak a konkrét állapotok, a robotot pedig a RobotCommand osztály példányaival irányíthatjuk.

@subsection Application MainApplication: az alkalmazás osztály

Az MainApplication osztály egyetlen példányát hozza létre a main() függvény. 
A konstruktor létrehozza a további objektum példányokat, összekapcsolja őket. 
A main() függvény ezután elindítja a Qt fő eseménykezelő ciklusát.

Az MainApplication környezetét az alábbi osztálydiagram ábrázolja:

![](diagrams/main_ClassDiagram.png)

A TcpSocketClient példánya felelős minden kommunikációért a kliens irányból (a másik a szimulátor, mely a mélyén tartalmaz egy TcpSocketServer objektumot).

A Simulator egy teljesen önállóan működő objektum, mely egy QTimer időzítő segítségével szimulálja a robot működését és küldi az állapotokat a RobotProxy számára és fogadja az esetleges parancsokat.

A RobotProxy képviseli a kliensben a robotot, annak korábbi és aktuális állapotát is.

A RobotStateHistory-t a RobotProxy használja az aktuális és korábbi állapotok tárolására. 
A RobotStateHistory új állapot érkezése esetén értesíti a felhasználó felületet, hogy frissíteni kell a megjelenítést.

A MainWindowsEventHandling felelős minden a felhasználói felületet érintő esemény lekezeléséért. 
Hozzá futnak be a GUI nyomógombjainak eseményei és a RobotStateHistory változásáról tájékoztató signal is.

