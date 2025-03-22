Pong
====

Speel pong op de ILI9341 TFT LCD met touchscreen via de Arduino Uno. 

## Voorbeeld setup

Hieronder staat hoe je de voorbeeld applicatie pong draait op het scherm.

1. Zorg dat je de Arduino IDE hebt geïnstalleerd. 

1. Open `Pong/Pong.ino` in de Arduino IDE.

1. Zorg dat je Arduino pins correct zijn aangesloten met de pins van de ILI9341.

   Voor de Arduino Uno zijn de SPI pins: 10(CS), 11(COPI), 12(CIPO), 13(SCK).

   De dataselect en reset pins: 9(dataselect), 8(reset)

   De touchscreen data select pin op 7.

   Zorg dat er 3.3v aan het scherm zijn vcc en led pin staat.

1. Als alles goed staat verbindt dan de Arduino Uno via USB zodat de Arduino IDE hem kan zien. 

1. Druk op upload en gebruik de touch screen om de linker paddle te bewegen. De rechter paddle is de 'bot' die alleen maar de bal volgt en geen voorspellingen doet. 

## Testing 

*Zorg ervoor dat g++ geïnstalleerd is en gebruikt kan worden in je terminal.*

### Windows 

1. Open de `build/` folder en dubbel klik op `build_test_pong.bat`.

2. Nadat het succesvol is gebuild voer je de binary bestand uit in `test/a.out`.

### Mac 

1. `cd` eerst in de `build/` folder en voer `sh build_test_pong.command` uit. 

2. Nadat het succesvol is gebuild voer je de binary bestand uit in `test/a.out`.

## Extra gebruikte libraries 
- [XPT2046 Touch](https://github.com/PaulStoffregen/XPT2046_Touchscreen) voor Pong
