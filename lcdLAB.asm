$mod842

;Kamil Piotrowski 122491 ; Michał Lewiński 122505
;Wyswietlacz LCD 4 bitowy

;P2 - wyswietlacz LED
;NA LABOLATORIUM:

;Piny do obsługi LCD
E EQU P2.5
RS EQU P2.7
RW EQU P2.4

;Piny danych wysyłanych do LCD
D4 EQU P2.1
D5 EQU P2.0
D6 EQU P2.3
D7 EQU P2.2

;E - "Enable". Ten pin wskazuje wyświetlaczowi, że zaczynamy wysyłać dane.
;Żeby wysłać dane należy ustawić E wartość 0 i ustawić odpowiednie dane (D4-D7).
;Następnie zmieniamy wartość E na 1 oraz odczekujemy odpowiednią ilość czasu
;Czas oczekiwania różni się w zależności od modelu LCD.
;Na koniec musimy ponownie wysłać E wartość 0, wskazującym tym samym zakończenie instrukcji.

;RS - "Register Select". Kiedy RS ma wartość 0 (sygnał niski)
;to dane wysyłane do LCD traktowane są jako specjalne instrukcje lub komendy
;np. wyczyścić ekran, zmienić pozycje kursora itp.
;Jeżeli RS ma wartość 1 (stan wysoki) to wysyłane dane przedstawiają znak ascii,
;który ma zostać wyświetlony na ekranie.

;RW - "READ/WRITE". Kiedy RW ma wartość 0 (stan niski) to dane (D4-D7) są zapisywane do LCD.
;Kiedy RW ma sygnał wysoki to program czyta z LCD. Istnieje tylko jedna komenda,
;która zczytuje z LCD i jest to "Get LCD status". Wszystkie inne są komendami zapisującymi.
;Z tego powodu zwykle RW ma wartość 0 (stan niski)

;D4-D7 piny służące do wysyłania odpowiednich danyc do LCD.

;POCZĄTEK PROGRAMU
ORG 000H
SJMP START

START:
	CALL SAVE_DATA	;Ustawiamy w RAMie odpowiednie znaki do wyswietlenia.
	CLR RS	;Zerujemy RS aby ustawić odpowiednio wyświetlacz LCD w trybie 4 bitowym
	CALL DELAY2 ;odczekujemy
	CALL INIT ;inicjujemy LCD w trybie 4 bitowym (D4-D7)
	MOV R4, #0 ;Zerujemy rejestr, którym posłużymy się w celu ustawiania odpowiedniej pozycji kursora
	MOV R3, #0;Zerujemy rejestr, który posłuży nam do weryfikacji pozycji kursora

	LOOPST:
		CALL CLEAR
		CALL DELAY
		CALL DISPLAY_DATA ;Wyświetlamy na LCD łańcuchy znaków, które są zapisane w RAMie
		CALL DELAY2
		INC R4
		CJNE R4, #16, skocz ;Doszliśmy do końca wyświetlacza więc wracamy na początek
		MOV R4,#0
		skocz:
		CALL DELAY
	JMP LOOPST;Powtarzamy pętle
	RET

	INIT: ;Inicjalizacja LCD

		MOV R0,#03
		CZEKAJ:
			CALL RESET
			CALL DELAY
		DJNZ R0,CZEKAJ

		CALL FUNC_SET
		CALL DELAY
		CALL FUNC_SET2
		CALL DELAY

		CALL OFF		;Wyłączamy wyświetlacz LCD
		CALL CLEAR		;Czyścimy wyświetlacz LCD

		CALL MODE ;Ustawiamy odpowiednie funkcje, żeby wyświetlacz działa w trybie 4 bitowym
		CALL DELAY
		CALL ON ;Włączamy wyświetlacz LCD
		CALL DELAY
	RET

	OFF: ;0000 1000
		CLR D7
		CLR D6
		CLR D5
		CLR D4
		CALL ZAPIS
		SETB D7
		CLR D6
		CLR D5
		CLR D4
		CALL ZAPIS
	RET

	ON: ;0000 1111
		CLR D7
		CLR D6
		CLR D5
		CLR D4
		CALL ZAPIS
		SETB D7
		SETB D6
		SETB D5
		SETB D4
		CALL ZAPIS
	RET

	CLEAR: ;0000 0001
		CLR D7
		CLR D6
		CLR D5
		CLR D4
		CALL ZAPIS
		CLR D7
		CLR D6
		CLR D5
		SETB D4
		CALL ZAPIS
	RET

	MODE: ;0000 0110
		CLR D7
		CLR D6
		CLR D5
		CLR D4
		CALL ZAPIS
		CLR D7
		SETB D6
		SETB D5			;kursor przesuwa sie w prawo
		CLR D4			;Przesuwanie kursora
		CALL ZAPIS
	RET

	RESET: ;0011
		CLR D7
		CLR D6
		SETB D5
		SETB D4
		CALL ZAPIS
	RET

	FUNC_SET: ;0010
		CLR D7
		CLR D6
		SETB D5
		CLR D4
		CALL ZAPIS
	RET

	FUNC_SET2: ;0010 1000
		CLR D7
		CLR D6
		SETB D5
		CLR D4
		CALL ZAPIS
		SETB D7
		CLR D6
		CLR D5
		CLR D4
		CALL ZAPIS
	RET

	CURSOR_LINE_1: ;1000
		SETB D7
		CLR D6
		CLR D5
		CLR D4
		CALL ZAPIS
	RET

	CURRENT_POSITION:
		MOV A,R4
		MOV C, ACC.3
		MOV D7, C
		MOV C, ACC.2
		MOV D6, C
		MOV C, ACC.1
		MOV D5, C
		MOV C, ACC.0
		MOV D4, C
		CALL ZAPIS
		CALL DELAY
	RET

	POSITION_0: ;0000
		CLR D7
		CLR D6
		CLR D5
		CLR D4
		CALL ZAPIS
		CALL DELAY
	RET

	CURSOR_LINE_2: ;1100
		SETB D7
		SETB D6
		CLR D5
		CLR D4
		CALL ZAPIS
	RET

	ZAPIS:
		CLR RW ;Chcemy zapisywać do LCD
		CLR RS ;Wysyłane jest specjalne polecenie lub komenda
		SETB E ;Wskazujemy, że można już wysyłać naszą komendę
		CLR E ;Zakończenie wysływania komendy
	RET

	SAVE_DATA: ;Tutaj zapisujemy do RAMu co chcemy wyświetlić na LCD

		MOV 30H, #'W'
		MOV 31H, #'Y'
		MOV 32H, #'D'
		MOV 33H, #'Z'
		MOV 34H, #'I'
		MOV 35H, #'A'
		MOV 36H, #'L'
		MOV 37H, #0

		MOV 40H, #'I'
		MOV 41H, #'N'
		MOV 42H, #'F'
		MOV 43H, #'O'
		MOV 44H, #'R'
		MOV 45H, #'M'
		MOV 46H, #'A'
		MOV 47H, #'T'
		MOV 48H, #'Y'
		MOV 49H, #'K'
		MOV 4AH, #'I'
		MOV 4BH, #0	;Adres wskazujący zakończenie wprowdzanego łańcucha znaków

	RET

	DELAY:  MOV     R7,#020 ;Krótszy delay
	DLY1:   MOV     R6,#255
		DJNZ    R6,$
		DJNZ    R7,DLY1
		RET


	DELAY2: MOV     R7,#07h	;Dłuższy delay
	DLY2:   MOV     R6,#0FFh
	DLY3:	  MOV		 R5,#0FFh
		DJNZ	  R5,$
		DJNZ    R6,DLY3
		DJNZ    R7,DLY2
		RET


	DISPLAY_DATA: ;Funkcja wypisujące znaki w odpowiedniej pozycji
		CALL CURSOR_LINE_1 ;Ustawiamy sie na w pierwszej linii
		CALL CURRENT_POSITION ;Ustawiamy sie na nastepnej pozycji
		MOV A, R4 ;Zapamiętujemy do akumulatora bo nie da się zrobić MOV R2,R4
		MOV R2, A ;Zapamiętujemy obecną pozycję, aby w trakcie wypisywania
							;gdy dojdziemy do końca to przeskoczymy na początek
		SETB RS		; CLR RS - wskazuje, że data w postaci tekstu jest wysyłana do LCD
		MOV R1, #30H	;Zapisujemy w rejestrze R1 adres komorki
									;zawierającej znak, który wypiszemy na LCD
	loop:

		INC R2
		CJNE R2, #17, skocz2 ;Jeśli doszliśmy do końca linii to wracamy na początek
		CALL CURSOR_LINE_1
		CALL POSITION_0
		MOV R2,#0
		SETB RS ;Ustawiamy RS aby wskazać, że nowe dane w postaci tekstu mogą być wysyłane
		skocz2:

		MOV A, @R1		;Zapisujemy w A adres rejestry, który zapisany jest pod R1
		JZ finish		; Jeżeli A jest równe adresowi 0 to kończymy wpisywanie znaków
		CALL sendCharacter	; wysyłamy znak zapisany pod adresem A do LCD
		INC R1			;Wskazujemy na następny adres w pamięci
		JMP loop		; wykonujemy ponownie pętle
	finish:

		CALL CURSOR_LINE_2 ;Ustawiamy się na w drugiej linii
		CALL CURRENT_POSITION ;Ustawiamy się na następnej pozycji
		MOV A, R4
		MOV R2, A;Zapamietujemy obecną pozycję, aby w trakcie wypisywania
							;gdy dojdziemy do konca to przeskoczymy na początek
		SETB RS		; CLR RS - wskazuje, że data w postaci tekstu jest wysyłana do LCD
		MOV R1, #40H	;Zapisujemy w rejestrze R1 adres komórki
									;zawierającej  początek łańcucha znaków, który wypiszemy na LCD
	loop2:

		INC R2
		CJNE R2, #17, skocz3;Jeśli doszliśmy do końca linii to wracamy na początek`
		CALL CURSOR_LINE_2
		CALL POSITION_0
		MOV R2,#0
		SETB RS ;Ustawiamy RS aby wskazać, że nowe dane w postaci tekstu mogą być wysyłane
	skocz3:
		MOV A, @R1		;Zapisujemy w A adres rejestry, który zapisany jest pod R1
		JZ finish2		; Jeżeli A jest równe adresowi 0 to kończymy wpisywanie znaków
		CALL sendCharacter	; wysyłamy znak zapisany pod adresem A do LCD
		INC R1			;Wskazujemy na nastepny adres w pamięci
		JMP loop2		; wykonujemy ponownie pętle
	finish2:
	RET

	sendCharacter: ;Znak jest odpowiednio zapisywany, aby został poprawnie wysłany do LCD
		;ASCII więc znak zapisany jest w 1 bajcie.
		MOV C, ACC.7
		MOV D7, C
		MOV C, ACC.6
		MOV D6, C
		MOV C, ACC.5
		MOV D5, C
		MOV C, ACC.4
		MOV D4, C
		;Musimy zapisywać co 4 bity, ze względy na ustawiony tryb
		SETB E;
		CLR E

		MOV C, ACC.3
		MOV D7, C
		MOV C, ACC.2
		MOV D6, C
		MOV C, ACC.1
		MOV D5, C
		MOV C, ACC.0
		MOV D4, C

		SETB E
		CLR E
		CALL DELAY
	RET

END
