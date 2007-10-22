Seit Version 0.65 k�nnen Sie mit DOSBox Videoclips aus der Bildschirmausgabe
erstellen (Screen-Capturing).

Dr�cken Sie Strg-Alt-F5, um die Aufnahme zu starten.
Um die Aufnahme anzuhalten/zu beenden, dr�cken Sie erneut Strg-Alt-F5.

Um den aufgenommenen Clip abspielen zu k�nnen, ben�tigen Sie einen Movie
Player und den installierten ZMBV-Codec. Windows-Anwender finden diesen Codec
im Startmen�-Ordner von DOSBox. Anwender von Linux und anderen Betriebs-
systemen sollten einen Movie Player benutzen, der auf der ffmpeg-Bibliothek
aufbaut (unter Umst�nden ben�tigen Sie ein Update oder ihre Distribution muss
upgegraded werden).

FAQ:

F: Beim Abspielen der Clips sind Bild und Ton asynchron ("der Ton h�ngt").
A: �berpr�fen Sie, ob in Ihren Anzeige-Einstellungen die Bildschirmaktuali-
   sierungsrate auf mindestens 70 Hertz eingestellt ist. Versuchen Sie, den
   Clip mit virtualdub abzuspielen (http://virtualdub.sf.net).

F: Warum wird der Clip in mehreren Dateien abgespeichert?
A: Wenn sich die Aufl�sung �ndert, muss DOSBox jedesmal eine neue Datei
   anlegen, weil innerhalb eines Clips immer dieselbe Aufl�sung vorliegen
   muss.

F: Kann ich w�hrend der Aufnahme mehr Cycles einstellen, als mein Rechner
   verarbeiten kann?
A: Ja. Auch wenn das Spiel w�hrend der Aufnahme langsam l�uft oder stottert,
   sollte sich der aufgenommene Clip ohne Stottern in der beabsichtigten
   Geschwindigkeit abspielen lassen.

F: Unter Linux wird mit der Kombination Strg-Alt-F5 die Konsole gestartet...
A: Gehen Sie folgenderma�en vor:
    1. Starten Sie DOSBox mit: dosbox -startmapper
    2. Klicken Sie auf "Video" und "Add"
    3. Dr�cken Sie die gew�nschte Taste (z.B. "Rollen" oder "Druck")
    4. Klicken Sie auf "Exit"
    5. Erstellen Sie Ihre Clips durch Dr�cken der eingestellten Taste.

F: Die Farbdarstellung ist fehlerhaft. Ich benutze eine 64-bit-Version von
   Windows.
A: Versuchen Sie das: http://vogons.zetafleet.com/viewtopic.php?t=12133
