#pragma once


/**
* @file struct.h
*/

/** 
* @brief Struktura miasta
* @param numer numer miasta
* @param x wspolrzedne x
* @param y wspolrzedne y
*/
struct miasto {
	int numer;
	double x, y;
};

/** 
* @brief Struktura trasy
* @param miasta wektor miast bedacych trasa
* @param dlugosc dlugosc trasy
*/
struct trasa {
	std::vector <miasto> miasta; // std::vector<miasto> miasta;
	double dlugosc;
};
/**
* @brief Ftruktura populacji
* @param nr_pokolenia numer pokolenia
* @param trasy wektor tras / osobnikow
*/
struct populacja {
	int nr_pokolenia;
	std::vector<trasa> trasy; // std::vector<trasa> trasy;
};

/**
* @brief enum class do zwracania bledow
* @param error zwracany kiedy chce sie wyswietlic error i zakonczyc program
* @param ok zwracany kiedy program ma dzialac dalej
* @param koniec zwracany kiedy program ma sie zakonczyc
*/
enum class class_error 
{
   error, ok, koniec
};
