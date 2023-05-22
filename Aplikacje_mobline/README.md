## Lab 1
1. Przepisz i uruchom prostą grę napisaną w Kotlinie na wykładzie pierwszym. Zrób dodatkowo taką samą grę w Javie.
2. W tym zadaniu jest duża możliwość wyboru. Proszę napisać dowolną aplikację w systemie Android w Javie i Kotlinie z następującymi ograniczeniami:
* aplikacja zawiera co najmniej cztery widgety na ekranie co najmniej dwóch rodzajów np. TextView, EditView
* aplikacja powinna odpowiadać na co najmniej dwa zdarzenia np. dwa przyciski
* aplikacja powinna zmieniać dowolny aspekt wyglądu np. textview ma większe i grubsze czcionki
* aplikacja powinna dostosowywać się do wielkość ekranu (różne telefony i rozdzielczości)
* nie może to być aplikacja z zadania 1
### Sugestie:
* Zgadywanie liczby. Komputer losuje liczbę np. 1 do 100, a użytkownik próbuje zgadywać liczbę z podpowiedziami komputera, czy liczba jest większa czy mniejsza od aktualnie podanej.
* Zgadywanie słowa. Komputer podaje słowo (na początku zasłonięte), a użytkownik próbuje zgadnąć jakie to słowo w najmniejszej liczbę odsłanianych liter.
* Papier-kamień-nożyczki. Gra z komputerem (który wybiera losowo). Śledź rozgrywkę człowieka i komputera podając kto wygrał ile partii.
* ...

## Lab 2
1. Napisz klasyczną grę Saper (Minesweeper), gdzie wypełniamy siatkę 9x9 polami które na początku są zakryte następnie odkrywamy je w taki sposób aby nie natrafić na minę. Na każdym odkrytym polu dodatkowo wypisywana jest liczba odkrytych min, które stykają się z danym polem. Możemy też zabezpieczyć dane pole flagą. Jeśli gracz odkryje wszystkie pola i zaznaczy flagami wszystkie miny, to wygrywa. Wykorzystaj odpowiedni Layout do rozłożenia przycisków i zrób tak aby przyciski wypełniały odpowiednio ekran oraz czcionka była odpowiednio duża (możesz to przetestować na emulatorze dla różnych rozdzielczości ekranów).
2. Napisz aplikację "Wisielec", która wyświetla po kolei obrazek wisielca oraz słowo które gracz próbuje zgadnąć. Słowo wybierane jest losowo z dostępnego słownika. Oczywiście cały czas wyświetlane jest słowo z prawidłowo zgadniętymi literami np. dla słowa komputer jeśli gracz zgadł prawidłowo litery o, m i e, słowo będzie wyglądało mniej więcej tak ?om???e?. Do utworzenia obrazków wykorzystaj np. program GIMP nazwij je odpowiednio wisielec0.png, wisielec1.png i tak dalej. Do wyświetlania obrazków wykorzystaj ImageView. Do przechowywania słownika wykorzystaj plik strings.xml.

## Lab 3
1. Napisz aplikacje typu "Calendar", czyli kalendarz i listę wydarzeń. Proszę wzorować się na innych aplikacjach tego typu i zobaczyć jakie mają funkcjonalności. Tutaj naprawdę niebanalnych pomysłów jest dużo!. Minimalne wymagania to możliwość przeglądania kalendarza i dodawania wydarzeń w danym dniu (oraz usuwania). W aplikacji należy wykorzystać RecyclerView i co najmniej dwie aktywności z komunikacją przez intencje. Zrób też tak, aby aplikacja pamiętała kalendarz i listę wydarzeń po rotacji ekranu, czyli po zmianie z portrait na landscape i odwrotnie. Tutaj należy wykorzystać tylko onSaveInstanceState i onRestoreInstanceState. Uwaga: W tym zadaniu aplikacja powinna być w pełni funkcjonalna. Uwzględniana będzie też wygoda i użyteczność aplikacji.
