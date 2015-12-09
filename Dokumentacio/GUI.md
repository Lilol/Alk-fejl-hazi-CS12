@page gui Felhasználói felület

Az alkalmazás felhasználói felülete egy QML alapú GUI, melyben a QML oldal felelős az adatkötésért a RobotStateHistory felé, az ottani változások esetén a megjelenítés frissítéséért (RobotStateHistory.historyChanged signal), valamint a menük és nyomógombok kezeléséért.

A felhasználói felület áll egy felsorolásszerű robotállapot-megjelenítésből, egy vezérlő részből, amivel a robotot irányíthatjuk (Reset, Stop és Test gombok), valamint a grafikus megjelenítésekből.
A grafikus megjelenítés két része a robot helyzetét mutató térkép, és egy grafikon, amelyen követhetjük a robot aktuális sebességét és gyorsulását.
A grafikus feleület az alábbi ábrán látható:

![GUI](images/gui.png)

A nyomógombok azonos elven működnek.
A Reset nyomógomb megnyomása esetét mutatja be a következő szekvencia diagram:

![Reset button sequence diagram](diagrams/reset_btn_sequence.png)

A QML oldalon a resetBtn nyomógomb eseményét a mainFormControl resetCommand slotja kapja meg (onResetCommand), mely tovább küldi azt a resetCommandCpp signal formájában, ami már a C++ oldalon van bekötve a MainWindowsEventHandling::resetCommand slotjába. 
Az itteni eseménykezelő meghívja a robotProxy.reset() metódust, ami pedig összeállítja a reset parancsot a robot számára és elküldi a TcpCommunication::send() metódusával.

A többi nyomógomb ehhez hasonlóan működik.