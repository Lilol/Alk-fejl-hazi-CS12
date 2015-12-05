---
layout: default
---

## Az Alkalmazásfejlesztés házi feladat tanulságai a 12. csapat szerint

Ez a snippet a 12. csapat szubjektív véleményét tartalmazza. Bármilyen hasonlóság élő vagy holt személyekkel a véletlen műve.

### 1.) Több alprojektből álló projektstruktúra létrehozása a QT Creator fejlesztői környezetben

Legegyszerűbb a File -> New File or Project... -> Other project -> Subdirs project paranccsal létrehozni egy közös főprojektet, közös .pro fájllal az alkalmazásnak, majd a főprojekt nevére jobb gombbal kattintva New Subproject... segítségével adhatunk hozzá új projektfájlokat. Ezeknek saját almappa is generálódik, ezt nem érdemes előre létrehozni.

A létrehozott projektstruktúra a mi esetünkben egy unit testeket tartalmazó projektből és a főprogramból állt, ezek típusát (Application, Library, ...) a létrehozáskor be lehet állítani.

Amit nem érdemes csinálni: először létrehozni a főprojektet, és utána megpróbálni hozzáfűzni a unit testeket tartalmazót. Nehézkes, és nekünk kell megírni a közös .pro fájlt.

A témáról bővebben: http://doc.qt.io/qtcreator/creator-project-creating.html#adding-subprojects-to-projects

### 2.) Clean a Build előtt



### 3.) A shadow buildet érdemes kikapcsolni

A shadow build funkció lényege, hogy a fordítás eredményét a QT Creator egy általunk kijelölt mappába teszi, nem az alapértelmezett Projek/Debug, illetve Projekt/Release mappákba. 
Erre általában nincs szükség, és nagyon megnehezítheti a fejlesztés folyamatát, például ha nem találjuk a kimeneti fájlokat. 
A QT Creator az újonan létrehozott projektekben automatikusan bekapcsolja a shadow build funkciót, ezt azonban érdemes kikapcsolni az első fordítás előtt a bal oldalon lévő Projects fül Build ablakában.

### 4.) QString elérése a qml oldalról

Amikor qml és cpp fájlok dolgoznak együtt, nehézkes a debuggolás. Bizonyos változóértékek, amik a cpp oldalon még jelen vannak és szimpla debuggolással könnyen ellenőrizhetők, a qml oldalon titokzatos módon eltűnnek, sokszor anélkül, hogy a rendszer hibát dobna.

Ennek tipikus esete a cpp oldalról átküldött QString típusú változó. Ha a qml oldalon a stringet egy Text objektum segítségével akarjuk megjeleníteni, minden gond nélkül működik, azonban ha előtte értékül adjuk egy változónak, majd ezt a változót akarjuk kiírni a felületre, ez nem sikerül.

Egy példa:
A cpp oldalon a következő kódrészlettel adjuk át a változót: 
		
		qmlContext.setContextProperty(QStringLiteral("stateName"), QVariant::fromValue(QString("default")));

Ekkor a következő kódrészlet működni fog:
		
		Text { text: "State: " +  ( stateName!=null ? stateName : "?")  }
		
Azonban ez a kód már nem:
	
		property var statusz_qml : stateName;

		Text { text: "State: " +  ( statusz_qml!=null ? statusz_qml : "?")  }
		
Szerencsére a cpp oldali változók látszanak az almodulokon belül is látszanak.


<small>Szerzők: 12. csapat </small>
