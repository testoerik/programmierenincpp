# Feedback zum Blatt
## Aufgabe 1:

> -1: Dir fehlen die Docstrings zu allen funktionen in der .h

> Hinweis: Du kannst das hier 
>> attron(COLOR_PAIR(color)); 
>> attron(A_REVERSE);
> 
> auch so schreiben
>> attron(COLOR_PAIR(color) | A_REVERSE);

> -1: in der drawPixel() machst du pos_y / 2, gabs dafür einen genauen grund.
>
> Du malst zwar zwei Leerzeichen für einen Pixel, aber ja dann nur in x Richtung.

> -2: allgemein für fehlende Tests 
> wenn du 4 wände hast mit denen du kollidieren könntest, dann erwarte ich auch 4 Tests dafür.
> 
> wenn deine Schlange in 4 Richtungen laufen könnte, dann erwarte ich auch 4 Tests dafür bzw. so wie du den Code geschrieben hast erwarte ich das.
> 
> Wenn du verschiedene Fälle hast, z.B. wenn ich aktuell nach links laufe, darf ich nicht nach Rechts, oder allgemein wenn ich verschiedene Richtungen drücke dann erwarte ich auch für jeden Fall einen Test
>> Hier bitte merken, für jegliches If oder für jegliches Switch Case... erwarte ich eigentlich einen Test welcher diese Bedingung einmal testet sodass klar ist das auch das erwartete passiert.

Sonst sieht das gut aus, also das Dinge die man mal vergisst, aber achte zukünftig drauf.

Points: 6/10
-----

## Aufgabe 2:
> Du hättest soweit ich das sehe auch einfach "speed += acceleration * speed" machen können.
>
> Du berechnest ja eh "int sleep_time_us = 1'000'000 / speed;" jedes mal neu

> In der letzten Schleife hättest du eventuell eher die handleKey Methode nutzen sollen, das ist aber nicht so genau definiert.

Sieht aber gut aus insgesamt.
 
Points: 5/5
-----

## Aufgabe 3:
Keine Extras.

Points: 0/0
-----

## Aufgabe 4:
> Prinzipiell schon mal die richtige Richtung.
> 
> -2: Sollte aber so aussehen
>> %Main: %Main.o Snake.o => $(CXX) -o $@ $^ -lncurses
> 
>> %Test: %Test.o Snake.o => $(CXX) -o $@ $^ -lgtest -lgtest_main -lncurses
>
> Deine %.o baut ja schon die SnakeMain.o aus der SnakeMain.cpp, das heißt die brauchst du in der SnakeMain nicht mehr, die fordert die dann direkt von der %.o an.

Points: 2/5
-----


> Punkte gesamt: 13/20
