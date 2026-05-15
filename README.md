# Symulator Układu Automatycznej Regulacji (UAR)

Zaawansowana aplikacja desktopowa przeznaczona do modelowania, symulacji oraz analizy dynamicznych obiektów regulacji w czasie rzeczywistym. Projekt pozwala na badanie interakcji między cyfrowym regulatorem PID a obiektem opisanym modelem ARX w zamkniętej pętli ujemnego sprzężenia zwrotnego.

## 🚀 Kluczowe Funkcjonalności

### 1. Modelowanie i Symulacja Obiektu (ARX)
* **Dyskretny model ARX:** Implementacja równania różnicowego z możliwością zadawania współczynników wielomianów A i B.
* **Opóźnienie transportowe:** Obsługa rzędu opóźnienia $k \ge 1$.
* **Symulacja zakłóceń:** Generowanie szumu o rozkładzie normalnym (wartość oczekiwana 0).

### 2. Zaawansowane Sterowanie (PID)
* **Pełny algorytm PID:** Niezależne nastawy dla części proporcjonalnej (P), całkującej (I) oraz różniczkującej (D).
* **Mechanizmy ochronne:** Implementacja filtra przeciwnasyceniowego (**Anti-Windup**) oraz możliwość wymuszenia resetu pamięci regulatora.
* **Nasycenia:** Możliwość umieszczenia obiektów statycznych realizujących funkcję nasycenia przed lub po obiekcie ARX.

### 3. Interfejs i Analiza (GUI)
* **Wizualizacja w czasie rzeczywistym:** Jednoczesne wyświetlanie wykresów wartości zadanej, uchybu, sterowania (z rozbiciem na składowe) oraz wartości regulowanej.
* **Dynamiczna konfiguracja:** Zmiana parametrów symulacji bez konieczności restartu programu.

### 4. Zarządzanie Danymi
* **Persystencja:** Zapis i odczyt pełnej konfiguracji układu w formacie tekstowym lub binarnym.
* **Eksport wyników:** Zapis przebiegów symulacji do pliku tekstowego wraz ze znacznikami czasu.

## 🏗 Architektura i Wzorce Projektowe

Aplikacja została zaprojektowana w architekturze wielowarstwowej, oddzielającej logikę obliczeniową (**Back-End**) od interfejsu użytkownika (**Front-End/GUI**).

**Zastosowane Wzorce:**
* **Dekorator (Decorator):** Wykorzystany do dynamicznego nakładania ograniczeń nasycenia na sygnały w układzie.
* **Kompozyt (Composite):** Umożliwia budowanie złożonych struktur sygnałowych oraz generatorów.

## 📂 Struktura Projektu

Układ plików źródłowych odzwierciedla modułowy charakter aplikacji:

| Plik | Odpowiedzialność |
| :--- | :--- |
| `arx_model.cpp/h` | Logika matematyczna modelu ARX. |
| `pid_regulator.cpp/h` | Implementacja dyskretnego algorytmu PID. |
| `loopsystem.cpp/h` | Zarządzanie zamkniętą pętlą sprzężenia zwrotnego. |
| `generator.cpp/h` | Generatory sygnałów (skok, sinus, prostokąt). |
| `filemanager.cpp/h` | Obsługa zapisu/odczytu konfiguracji i wyników. |
| `gui.cpp/h/ui` | Warstwa prezentacji i obsługa zdarzeń użytkownika. |
| `simulation.cpp/h` | Kontrola wątku i interwału czasowego symulacji. |
| `io.cpp/h` | Obsługa operacji wejścia-wyjścia. |
| `SignalType.h` | Definicje typów sygnałów krążących w systemie. |

## ⚙️ Podstawy Matematyczne

### Model ARX
System wylicza kolejne próbki sygnału wyjściowego $y_i$ zgodnie z równaniem:
$$y_i = (b_0 u_{i-k} + b_1 u_{i-k-1} + \dots + b_{dB} u_{i-k-dB}) - (a_1 y_{i-1} + a_2 y_{i-2} + \dots + a_{dA} y_{i-dA}) + z_i$$

### Algorytm PID
Sterowanie $u_i$ jest sumą trzech komponentów:
* **P:** $u_i^P = k e_i$
* **I:** $u_i^I = rac{\sum e}{T_I}$ (z obsługą $T_I = 0$ jako wyłączenie części całkującej)
* **D:** $u_i^D = T_D(e_i - e_{i-1})$

## 🛠 Instalacja i Uruchomienie

**Wymagania:**
* Środowisko **Qt Creator**
* Kompilator wspierający standard **C++17/20**

**Instrukcja:**
1.  **Klonowanie:** Pobierz repozytorium na dysk lokalny.
2.  **Konfiguracja:** Otwórz plik `Symulator_UAR.pro` w środowisku Qt Creator.
3.  **Budowanie:** Przeprowadź proces `qmake`, a następnie zbuduj projekt (**Build**).
4.  **Uruchomienie:** Uruchom aplikację; interfejs graficzny pozwoli na wstępną konfigurację parametrów przed startem symulacji.
