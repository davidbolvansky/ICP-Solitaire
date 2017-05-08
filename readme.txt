Projekt do ICP 2016/2017 - Solitaire Klondike
Autori: Dávid Bolvanský xbolva00
        Katarína Grešová xgreso00

Zadaní: Navrhněte a implementujte aplikaci Pasians (Solitaire) Klondike, která vychází ze stejnojmenné karetní hry.

Specifikace požadavků
- aplikace bude implementovat základní pravidla hry, která jsou uvedena zde
- řešitelé mohou zvolit variantu uvedených pravidel či rozšíření podle svého uvážení
- další požadavky
     - bude možné rozehrát až 4 hry současně
     - pokud bude rozehrána pouze jedna hra, bude plocha grafického rozhraní obsahovat pouze tuto hru (jedno hrací plátno)
     - pokud bude rozehrána více než jedna hra, bude plocha grafického rozhraní rozdělena do 4 dlaždic, každá pro jednu hru (hrací plátno)
     - nevyužité dlaždice nebudou nic obsahovat
     - počet rozehraných her lze měnit za běhu
   - kdykoliv je možné hru ukončit
   - každá hra umožňuje operaci undo (alespoň pět tahů)
   - rozehranou hru je možné uložit a znovu načíst (historii tahů pro undo není třeba ukládat)
   - aplikaci nabízí možnost nápovědy tahu (na žádost zobrazí vhodným způsobem jaké tahy je možné provést)
- součástí aplikace bude grafické uživatelské rozhraní zobrazující
   - hrací plátno (plátna) s kartami
   - ovládací prvky (uložit, načíst, ukončit hru, založit novou hru, ...)


Kompilácia a spustenie Solitaire Qt Qui na merline:
1. Je potrebné spustiť najskôr tieto príkazy:
export LD_LIBRARY_PATH=/usr/local/share/Qt-5.5.1/5.5/gcc_64/lib:$LD_LIBRARY_PATH
export QT_PLUGIN_PATH=/usr/local/share/Qt-5.5.1/5.5/gcc_64/plugins:$QT_PLUGIN_PATH

2. Následne pomocou "make run" skompilovať a spustiť hru


Ovládanie CLI verzie:
- Po stlačení kláves "h" sa zobrazí pomocník s možnými príkazmi na ovládanie hry
