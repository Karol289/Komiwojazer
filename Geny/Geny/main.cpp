#include <iostream>
#include <string>
#include <vector>

#include "funkcje.h"
#include "struct.h"




int main(int ile_param, char * param[]) 
{
    ////wypisywanie zczytanych paramentrow
	//std::cout << std::endl;
	//std::cout << "Liczba parametrow: " << ile_param << std::endl;
	//for (int i = 0; i < ile_param; i++)
	//	std::cout << "[" << i << "] " << param[i] << std::endl;
	//std::cout << std::endl;
	

	std::string plik_wejsciowy = "", plik_wyjsciowy = ""; 
	int liczba_pokolen = -1, liczba_osobnikow = -1, generowanie_miast = 0;

	// sprawdzanie paramterow startowych
	class_error blad = parametry_wejsciowe(ile_param, param, plik_wejsciowy, plik_wyjsciowy, liczba_pokolen, liczba_osobnikow, generowanie_miast);
	
	if (blad == class_error::ok) {

		//odczyt miast
		std::pair<class_error, std::vector<miasto>> czyok_miasta = odczyt_miast(plik_wejsciowy);
		if(czyok_miasta.first==class_error::ok)
		{
			std::vector<miasto> miasta = czyok_miasta.second;

			//wypisywanie miast
			//wypisz_miasta(miasta);
	
			//generowanie losowej trasy
			trasa droga1 = generowanie_trasy(miasta);

			//wypisywanie wygenerowanej trasy
			//wypisz_trase(droga1);
			

			populacja populacja1 = generowanie_populacji(liczba_osobnikow, miasta);

			//wypisz_populacje(populacja1);


			for (int i = 0; i < liczba_pokolen; i++) {

				//std::cout << "Pokolenie: " << populacja1.nr_pokolenia << std::endl;

				//krzyzowanie populacji
				krzyzowanie_pmx(populacja1, miasta);



				//mutacja populacji
				mutacja(populacja1);

				//wypisywanie zkrzyzowanej i zmutowanej populacji
				//std::cout << "mutacja" << std::endl;
				//wypisz_populacje(populacja1);

				//selekcja na populacji
				populacja1 = selekcja_turniejowa(populacja1);

				//wypisywanie wyselekcjonowanej populacji

				//std::cout <<"selekcja" << std::endl;
				//wypisz_populacje(populacja1);

				//zapis do pliku najlepszego z populacji
				zapisz_do_pliku(populacja1, plik_wyjsciowy);

			}
		}
	}
	else if(blad==class_error::error){
		error();
	}
	


	return 0; 
}
