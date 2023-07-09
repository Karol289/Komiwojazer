#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <random>
#include <unordered_map>
#include <chrono>
#include <numeric>



#include "funkcje.h"
#include "struct.h"


class_error parametry_wejsciowe(const int ile_param, char* param[], std::string& plik_wejsciowy, std::string& plik_wyjsciowy, int& liczba_pokolen, int& liczba_osobnikow, int& generowanie_miast)
{
	//sczytywanie paramentrow wejsciowych
	const std::string IN {"-i"};
	const std::string OUT{ "-o" };
	const std::string G{ "-g" };
	const std::string N{ "-n" };
	const std::string R{ "-r" };
	
	for (int i = 0; i < ile_param; i++) {
		if (std::string(param[i]) == IN) {
			if (ile_param-1 > i) {
				std::string plik(param[i + 1]);
				plik_wejsciowy = plik;
			}
			//std::cout <<"1: " << plik_wejsciowy << std::endl;
		}
		if (std::string(param[i]) == OUT) {
			if (ile_param-1 > i) {
				std::string plik(param[i + 1]);
				plik_wyjsciowy = plik;
			}
			//std::cout << "2: " << plik_wyjsciowy << std::endl;
		}
		if (std::string(param[i]) == G) {
			if (ile_param-1 > i)
				liczba_pokolen = atoi(param[i + 1]);
			//std::cout << "3: " << liczba_pokolen << std::endl;
		}
		if (std::string(param[i]) == N) {
			if (ile_param-1 > i)
				liczba_osobnikow = atoi(param[i + 1]);
			//std::cout << "4: " << liczba_osobnikow << std::endl;
		}
		if (std::string(param[i]) == R) {

			const int LICZBA_PUNKTOW{ 1000 };
			const double X_MIN{ 10 };  // zakres wspolrzednych punktow
			const double X_MAX{ 800 };
			const double Y_MIN{ 10 };
			const double Y_MAX{ 800 };

			if (ile_param - 1 > i) {
				std::string plik(param[i + 1]);
				generuj_punkty_prostokat(LICZBA_PUNKTOW, X_MIN, X_MAX, Y_MIN, Y_MAX, plik);
				return class_error::koniec;
			}
		}
	}
	if ((liczba_osobnikow == -1) || (liczba_pokolen == -1) || (plik_wejsciowy == "") || (plik_wyjsciowy == "")) {
		return class_error::error;
	}
	else if (liczba_osobnikow == 1) {
		std::cout << "Liczba osobnikow musi byc przynajmniej 2!!!" << std::endl;
		return class_error::koniec;
	}

	return class_error::ok;
}


void error()
{

	//blad przy zlym wpisaniu paramentrow wejsciowych
	std::cout << "--------------------------------------------------------------------" << std::endl;
	std::cout << " Prawidlowe uzycie parametrow wejsciowych genetycznego komiwojazera:" << std::endl;
	std::cout << " -i {plik wejsciowy z miastami} " << std::endl;
	std::cout << " -o {plik wyjsciowy z najlepszymi rozwiazaniami w kolejnych pokoleniach} " << std::endl;
	std::cout << " -g {liczba pokolen} " << std::endl;
	std::cout << " -n {liczba osobnikow w pokoleniu} " << std::endl;
	std::cout << "--------------------------------------------------------------------\n" << std::endl;
	std::cout << " Program posiada generator losowych liczb: " << std::endl;
	std::cout << " -r {plik do zapisy wygenerowanych miast} " << std::endl;
	std::cout << "--------------------------------------------------------------------\n" << std::endl;
}

std::pair<class_error, std::vector<miasto>> odczyt_miast(const std::string& plik_wejsciowy)
{

	//odczyt z pliku
	std::ifstream plik(plik_wejsciowy);
	std::string linia;
	miasto miasto_wrzucane;
	std::vector < miasto> wektor_miast;

	int numer_linii = 0;
	if (plik) {
		while (std::getline(plik, linia))
		{
			std::stringstream ss;
			ss << linia;
			int kod_m;
			std::string nadmiar;
			double x_m, y_m;
			numer_linii++;

			if (ss >> kod_m >> x_m >> y_m) {
				if (ss >> nadmiar) {//przypadek nadmiaru danych w linii
					std::cout << "Linia " << numer_linii << " ma nadmiar danych" << std::endl;
				}
				else {
					miasto_wrzucane = { kod_m, x_m, y_m };
					wektor_miast.push_back(miasto_wrzucane);
				}
			}
			else { //przypadek nie wczytania danych z linii nadmiarowo
				std::cout << "Linia " << numer_linii << " wczytana nieprawidlowo" << std::endl;
			}
		//	std::cout << numer_lini<<" [" << kod_m <<"] [" << x_m <<"] ["<< y_m <<"]" << std::endl;
		}
	}
	else {
		std::cout << "Blad znalezienia pliku do odczytu!!!!" << std::endl;
		return { class_error::error, wektor_miast };
	}

	return { class_error::ok, wektor_miast };
}

void wypisz_miasta(const std::vector<miasto>& miasta){
	for (size_t i = 0; i < miasta.size(); i++) {
		std::cout << "Miasto " << miasta[i].numer << " x: " << miasta[i].x << " y: " << miasta[i].y << std::endl;
	}
}

trasa generowanie_trasy(std::vector<miasto> miasta) {
	
	//generowanie losowej trasy
	trasa zwracana;
	zwracana.miasta = miasta;

	static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(zwracana.miasta.begin() + 1, zwracana.miasta.end(), generator);
	
	zwracana.miasta.push_back(miasta[0]);

	dlugosc_trasy(zwracana);
	return zwracana;
}

void dlugosc_trasy(trasa& tras) {

	//liczenie dlugosci trasy
	tras.dlugosc = 0;
	size_t dlugosc = tras.miasta.size();

	if (dlugosc % 2 == 1) { // przypadek nieparzystej trasy
		tras.dlugosc += odleglosc_miast(tras.miasta[dlugosc-1], tras.miasta[0]);
		dlugosc -= 1;
	}
	for (size_t i = 0; i < dlugosc; i++) {
			tras.dlugosc += odleglosc_miast(tras.miasta[i], tras.miasta[i + 1]);
	}
	
}

double odleglosc_miast(const miasto& miasto1, const miasto& miasto2) {

	//funkcja zwracajaca odleglosc dwoch miast od siebie
	return std::sqrt((miasto1.x - miasto2.x) * (miasto1.x - miasto2.x) + (miasto1.y - miasto2.y) * (miasto1.y - miasto2.y));
}

void wypisz_trase(const trasa& droga1) {

	//wypisywanie trasy
	std::cout << "Wypisana trasa: " << std::endl;
	for (size_t i = 0; i < droga1.miasta.size(); i++) {
		std::cout << "Miasto " << i + 1 << " --> Nr: " << droga1.miasta[i].numer << " x: " << droga1.miasta[i].x << " y: " << droga1.miasta[i].y << std::endl;
	}
	std::cout << "Dlugosc trasy: " << droga1.dlugosc << std::endl;
}

populacja generowanie_populacji(const int& liczba_osobnikow, const std::vector<miasto> miasta) {

	//generowanie losowej populacji
	populacja populacja_zwracana;
	for (int i = 1; i <= liczba_osobnikow; i++) {
		trasa trasa_generowana = generowanie_trasy(miasta);
		populacja_zwracana.trasy.push_back(trasa_generowana);
	}
	populacja_zwracana.nr_pokolenia = 0;
	
	return populacja_zwracana;
}

void wypisz_populacje(const populacja& populacja1) {

	//wypisywanie populacji
	std::cout << "Wypisywanie populacji!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!: " << std::endl;
	std::cout << "Populacja: " << std::endl;
	for (size_t i = 0;i<populacja1.trasy.size();i++){
		std::cout << "Trasa nr " << i << ": " << std::endl;
		wypisz_trase(populacja1.trasy[i]);
}
	std::cout << "Numer pokolenia: " << populacja1.nr_pokolenia << std::endl;
}

int losowa(const int pocz, const int koniec){

	//zwracanie losowej liczby z podanego przedia�u

	std::uniform_int_distribution<int> distrybucja(pocz, koniec); 
	//static std::random_device rd;
	//static std::default_random_engine generator(rd());

	static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

	return distrybucja(generator);
	

}

void krzyzowanie_pmx(populacja& popula, std::vector<miasto> miasta) {

	//std::cout << "kzyzowanie pmx" << std::endl;
	
	std::pair<int, int> pocz_kon = losowa2(1, miasta.size() - 1);
	int poczatek = pocz_kon.first;
	int koniec = pocz_kon.second;

	//std::cout << "Poczatek i koniec:" << poczatek << " i " << koniec << std::endl;
	
	if (poczatek > koniec) { // poczatek jest poczatkowym miastem pmx
		std::swap(poczatek, koniec);
	}


	//wybieranie dwoch losowych tras
	std::pair<int, int> id_1i2 = losowa2(0, popula.trasy.size());

	int trasa1_id = id_1i2.first;
	int trasa2_id = id_1i2.second;
	//std::cout << "id1 i id2 :" << trasa1_id << " i " << trasa2_id << std::endl;
	
	trasa trasa1 = popula.trasy[trasa1_id];
	trasa trasa2 = popula.trasy[trasa2_id];

	double dlugosc_trasa1 = trasa1.dlugosc;
	double dlugosc_trasa2 = trasa2.dlugosc;


	// PMX
	std::unordered_map<int, int> slownik_dolny;
	std::unordered_map<int, int> slownik_gorny;

	//zamiana pmx i tworzenie slownika
	for (int i = poczatek; i <= koniec; i++) {	
		
		slownik_dolny[trasa2.miasta[i].numer] = trasa1.miasta[i].numer;
		slownik_gorny[trasa1.miasta[i].numer] = trasa2.miasta[i].numer;
		//std::cout << trasa2.miasta[i].numer << " dolny " << trasa1.miasta[i].numer << std::endl;

		std::swap(trasa1.miasta[i], trasa2.miasta[i]);
		
	}

	//wypisywanie slownika
	/*
	std::cout << "slownik dolny" << std::endl;
	for (const auto& i : slownik_dolny) {
		std::cout << i.first << " i " << i.second << std::endl;
	}

	std::cout << "slownik gorny" << std::endl;
	for (const auto& i : slownik_gorny) {
		std::cout << i.first << " i " << i.second << std::endl;
	}
	*/
	
	
	
	for (std::vector<miasto>::iterator it = trasa1.miasta.begin() + 1; it != trasa1.miasta.end() - 1; it++) {//petla biegnaca po wartosciach trasy
		if (it == trasa1.miasta.begin() + poczatek) {//warunek pomijajacy przeniesione pmx
			it = trasa1.miasta.begin() + koniec +1;
		}
		std::pair<int, int> zliaczanie = { it->numer, 0 }; 
		while (slownik_dolny[it->numer]) {//zmienianie z slownika
			if (it->numer == zliaczanie.first) {//niepopadanie w petle
				zliaczanie.second++;
				if (zliaczanie.second == 2) {
					break;
				}
			}
			it->numer = slownik_dolny[it->numer];
		}
	}


	for (std::vector<miasto>::iterator it = trasa2.miasta.begin() + 1; it != trasa2.miasta.end() - 1; it++) {
		if (it == trasa2.miasta.begin() + poczatek) {
			it = trasa2.miasta.begin() + koniec+1;
		}
		std::pair<int, int> zliaczanie = { it->numer, 0 };
		while (slownik_gorny[it->numer]) {
			if (it->numer == zliaczanie.first) {
				zliaczanie.second++;
				if (zliaczanie.second == 2) {
					break;
				}
			}
			it->numer = slownik_gorny[it->numer];
		}
	}

	dlugosc_trasy(trasa1);
	dlugosc_trasy(trasa2);

	popula.trasy[trasa1_id] = trasa1;
	popula.trasy[trasa2_id] = trasa2;

}

void mutacja(populacja& popula) {

	//wybieranie losowej trasy z populacji
	int trasa1_id = losowa(0, popula.trasy.size()-1);
	trasa trasa1 = popula.trasy[trasa1_id];

	//wybieranie dwoch losowych miast z trasy
	std::pair<int, int> para = losowa2(1, trasa1.miasta.size() - 2);

	//podmiana kolejnosci miast
   std::swap(trasa1.miasta[para.first], trasa1.miasta[para.second]);

	dlugosc_trasy(trasa1);

	popula.trasy[trasa1_id] = trasa1;
	
}

std::pair<int, int> losowa2(const int& poczatek, const int& koniec) {

	std::vector<int> kolejnosc(koniec - poczatek);
	std::iota(kolejnosc.begin(), kolejnosc.end(), poczatek);

	static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(kolejnosc.begin(), kolejnosc.end(), generator);

	return { kolejnosc[0], kolejnosc[1] };
}

populacja selekcja_turniejowa(populacja& popula) {

	populacja zwracana;
	std::vector<int> kolejnosc(popula.trasy.size());
	std::iota(kolejnosc.begin(), kolejnosc.end(), 0);
	static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	int ile_shuffle = 0;
	int e;
	while (zwracana.trasy.size() < popula.trasy.size()) {
		if (ile_shuffle == 0) {
			ile_shuffle = (kolejnosc.size() - (kolejnosc.size() % 2)) / 2;
			std::shuffle(kolejnosc.begin(), kolejnosc.end(), generator);  ///@todo wiecej z jednego shuffle
			e = 0;
		}
	
		if (popula.trasy[kolejnosc[e]].dlugosc < popula.trasy[kolejnosc[e+1]].dlugosc) {
			zwracana.trasy.push_back(popula.trasy[kolejnosc[e]]);
		}
		else {
			zwracana.trasy.push_back(popula.trasy[kolejnosc[e+1]]);
		}
		ile_shuffle--;
		e = e + 2;

	}

	zwracana.nr_pokolenia = popula.nr_pokolenia+1;
    
	return zwracana;
	
}

void zapisz_do_pliku(const populacja& popula, const std::string wyjsciowy) {

	//otwieranie pliku pustego lub dodawanie
	std::ofstream plik;
	if (popula.nr_pokolenia != 1) {
		plik.open(wyjsciowy, std::ios::app);
	}
	else {
		plik.open(wyjsciowy);
	}
	trasa min_trasa = popula.trasy[0];
	if (plik) {
		//wyznaczanie min trasy

		for (const auto& i : popula.trasy) {
			if (min_trasa.dlugosc > i.dlugosc) {
				min_trasa = i;
			}
		}

		//wypisywanie min_trasy
		plik << "pokolenie " << popula.nr_pokolenia << std::endl;
		for (const auto& i : min_trasa.miasta) {
			plik << i.numer << " ";
		}
		plik << std::endl << "Dlugosc trasy: " << min_trasa.dlugosc << std::endl;
		plik << std::endl << std::endl;
	}
}

void generuj_punkty_prostokat(const int LICZBA_PUNKTOW, const double X_MIN, const double X_MAX, const double Y_MIN, const double Y_MAX, std::string& wejscie)
{
	static std::default_random_engine silnik(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> distro_X{ X_MIN, X_MAX };
	std::uniform_real_distribution<double> distro_Y{ Y_MIN, Y_MAX };

	std::ofstream plik(wejscie);


	if (plik) {
		for (int i = 0; i < LICZBA_PUNKTOW; i++)
		{
			plik << i << " " << distro_X(silnik) << " " << distro_Y(silnik) << std::endl;
		}
	}
	else {
		std::cout << "plik zle otwarty" << std::endl;
	}
}





