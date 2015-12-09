@page representation Robot reprezentáció

A robot reprezentációját az alábbi osztály diagram foglalja össze:

![](diagrams/robotProy_kornyezete.png)

A RobotProxy felelős a kliens többi része felé a kapcsolattartásért.
A RobotProxy egy **proxy típusú tervezési mintát** valósít meg, mert a qml oldal felé a távoli robotot képviseli.

A robot pillanatnyi állapotát a RobotState osztály írja le. 
(A szimulátornak egyetlen RobotState osztály példánya van és mindent az alapján szimulál.) 
Feladata csak az információ tárolás.

A RobotStateHistory három formában is tárol RobotState-et:

  * container: egy std::vector<unique_ptr>, mely az összes tárolt állapot (aktuális és korábbiak is) tárolásáért felelős. Övé az "ownership", vagyis ennek a unique_ptr miatt ennek a vektornak a megszűnésekor szűnnek meg az állapotok is.
  * currentState: egy pointer az aktuális állapotra. Mivel az ownership a containeré, ezért ha változik az aktuális állapot, ezt a pointert nyugodtan át lehet állítani bármi egyéb teendő nélkül.
  * stateList: egy pointer lista a container minden elemére. Erre azért van szükség, mert a QML megjelenítés csak ilyen listához tud adatkötést felépíteni, a unique_ptr vectorhoz nem. 

