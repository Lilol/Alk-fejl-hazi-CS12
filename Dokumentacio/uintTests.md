@page unitTests Unit tesztek

A program unit tesztjei a Simulator működését ellenőrzik.
A teszteket a SimulatorTester osztály fogja össze.
Az osztály és környezete az alábbi diagramon látható:

![](diagrams/unit_tests.png)

Három különböző testcase fut le, amelyek vizsgálják, hogy megfelelő gerjesztés hatására a robot szimulátora megfelelően reagál-e.

A három különböző testcase a következő:

  * testPosition()
  * testVelocity()
  * testAcceleration()
  
A tesztek vizsgálják, hogy adott gerjesztés után, adott idő elteltével a robot megfelelő pozícióban van-e, illetve gyorsulása, sebessége is a bemeneteknek megfelelően, helyesen alakul.

