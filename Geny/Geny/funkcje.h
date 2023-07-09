/**
* @file funkcje.h
*/
#include <string>
#include <vector>

#include "struct.h"

/** 
* @brief Funkcja zczytuje i sprawdza poprawnosc paramentrow wejsciowych
* @param ile_param liczba parametrow wejsciowych
* @param param[] tablica parametrow wejsciowych
* @param plik_wejsciowy plik z danymi wejsciowymi
* @param plik_wyjsciowy plik z danymi wyjsciowymi (najlepszymi osobnikami kazdej populacji)
* @param liczba_pokolen ilosc pokolen algorytmu genetycznego
* @param liczba_osobnikow ilosc osobnikow w kazdym pokoleniu
* @return zwraca czy paramentry wejsciowe zostawy podane prawidlowo
*/
class_error parametry_wejsciowe(const int ile_param, char * param[], std::string& plik_wejsciowy, std::string& plik_wyjsciowy, int& liczba_pokolen, int& liczba_osobnikow, int& generowanie_miast);

/** 
* @brief Funkcja wyswietla blad zlego wprowadzenia paramentorw wejsciowych
* @return Funkcja void - nie zwraca
*/
void error();

/**
* @brief Funkcja zczytuje miasta podane w pliku wejsciowym
* @param plik_wejsciowy nazwa pliku z lista miast
* @return zwraca pare: czy nastapil blad i vektor odczytanych miast
*/
std::pair<class_error, std::vector<miasto>> odczyt_miast(const std::string& plik_wejsciowy);

/** 
* @brief Funkcja wypisuje zczytane miasta
* @param miasta wektor miast ktore beda wyswietlane
* @return Funkcja void - nie zwraca
*/
void wypisz_miasta (const std::vector<miasto>& miasta);

/** 
* @brief Funkcja generuje losowa trase
* @param miasta miasta z ktorych trasa bedzie generowana
* @return funkcja zwraca wygenerowana trase
*/
trasa generowanie_trasy(std::vector<miasto> miasta);

/**
* @brief Funkcja wypisuje podana trase
* @param droga1 wypisywana trasa
* @return Funkcja void - nie zwraca
*/
void wypisz_trase(const trasa& droga1);

/** 
* @brief Funkcja generuje losowa populacje
* @param liczba_osobnikow ilosc osobnikow w generowanej populacji
* @param miasta miasta z ktorych beda generowane osobniki do trasy
* @return zwraca generowana populacje
*/
populacja generowanie_populacji(const int& liczba_osobnikow, const std::vector<miasto> miasta);

/**
* @brief Funkcja wypisuje podana populacje
* @param populacja1 wypisywana populacja
* @return Funkcja void - nie zwraca
*/
void wypisz_populacje(const populacja& populacja1);

/** 
* @brief Funkcja oblicza i aktualizuje dlugosc trasy
* @param tras trasa ktorej dlugosc bedzie obliczana
* @return Funkcja void - nie zwraca
*/
void dlugosc_trasy(trasa& tras);

/**
* @brief Funkcja oblicza odleglosc od siebie podanych dwoch miast
* @param miasto1 pierwsze miasto
* @param miasto 2 drugie miasto
* @return zwraca obliczona odleglosc
*/
double odleglosc_miast(const miasto& miasto1, const miasto& miasto2);

int losowa(const int pocz, const int koniec);

/** 
* @brief Funkcja krzyzujaca dwie losowe trasy w podanej populacji
* @param popula populacja poddawana krzyzowaniu
* @param miasta miasta zczytana z pliku
* @return Funkcja void - nie zwraca
*/
void krzyzowanie_pmx(populacja& popula, std::vector<miasto> miasta);

/** 
* @brief Funkcja mutujaca losowa trase w populacji
* @param popula populacja na ktorej bedzie wykonbywana mutacja
* @return Funkcja void - nie zwraca
*/
void mutacja(populacja& poplua);

/**
* @brief Funkcja losujaca dwie unikalne liczby z podanego zakresu
* @param poczatek poczatek losowanego zakresu
* @param koniec koniec losowanego zakresu
* @return para unikalnych liczb int
*/
std::pair<int, int> losowa2(const int& poczatek, const int& koniec);

/** 
* @brief Funkcja wykonujaca selekcje turniejowa na danej populacji
* @param popula populacja na ktorej bedzie wykonywana selekcja
* @return zwraca populacje po selekcji 
*/
populacja selekcja_turniejowa(populacja& popula);

/** 
* @brief Funkcja zapisuje najlepszy osobnik danej populacji do podanego pliku
* @param popula populacja z ktorej zapisujemy najlepszy osobnik
* @param wyjsciowy nazwa pliku do ktorego bedzie zapisany wynik
* @return Funkcja void - nie zwraca
*/
void zapisz_do_pliku(const populacja& popula, const std::string wyjsciowy);

/**
* @brief Funkcja generujaca losowe miasta
* @param LICZBA_PUNKTOW ilosc punktow ktore maja sie wygenerowac
* @param X_MIN minimalna wartosc x
* @param X_MAX maksymalna wartosc x
* @param Y_MIN minimalna wartosc y
* @param Y_MAX maksymalna wartosc y
* @param wejscie plik wejsciowy do ktorego sa generowane miasta
* @return Funkcja void - nie zwraca
*/
void generuj_punkty_prostokat(const int LICZBA_PUNKTOW, const double X_MIN, const double X_MAX, const double Y_MIN, const double Y_MAX, std::string& wejscie);

