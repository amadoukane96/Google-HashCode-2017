#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

#include "CReferee.h"
#include "modeles/CSolution.h"
#include "modeles/CInput.h"
#include "CTimer.h"

using namespace std;


// Fonction de comparaison croissante du vector résultat
bool pairCompare(const pair<string, double>& firstElem, const pair<string, double>& secondElem) {
	return firstElem.second < secondElem.second;
}

//// Fonction de comparaison décroissante
bool pairCompare_dec(const pair<string, double>& firstElem, const pair<string, double>& secondElem) {
	return firstElem.second > secondElem.second;
}
// Fonction qui vérifie que le fichier soit un .exe
bool isExe(string ligne, int taille) {
	if (ligne[taille - 1] == 'e' && ligne[taille - 2] == 'x' && ligne[taille - 3] == 'e' && ligne[taille - 4] == '.') {
		return true;
	}
	else { return false; }
}

int main(int argc, char *argv[])
{
	// On vérifie qu'il y a le bon nombre de paramtres
	if (argc != 3) {
		cout << "Error : missing argument" << endl;
		return 0;
	}

	string const nomRepertoire(argv[1]);
	string const nomFichier(argv[2]);
	vector<string> tabFichier; //On créé un tableau pour mettre les noms des fichiers
	vector<pair<string, double> > tabResultat; //Puis le tableau résultat des temps
	vector<pair<string, double> > tabResultat_score; //Puis le tableau résultat des scores

	// On créé le tableau de char pour l'appel system
	string strListeFichier = "dir " + nomRepertoire + " /b >listefichier.txt";
	const char *cstrListeFichier = strListeFichier.c_str();

	system(cstrListeFichier); //On liste les fichiers dans un fichier text

	ifstream listeFichier("listefichier.txt"); // On ouvre le fichier pour lire les lignes
	string ligne;
	int nbreLigne = 0;
	int taille = 0;
	while (getline(listeFichier, ligne)) {
		taille = ligne.size();
		if (isExe(ligne, taille)) {
			tabFichier.push_back(ligne); // Qu'on met dans le tableau si le fichier est un exécutable
			nbreLigne++;
		}
	}
	listeFichier.close();

	// On supprime le fichier texte listeFichier
	system("del listefichier.txt");

	// On prépare les variables de temps
	chrono::time_point<chrono::system_clock> start, end;
	chrono::duration<double> elapsed_seconds;

	string tabIn[4] = { "toy","charleston_road" , "rue_de_londres", "opera" };// , "lets_go_higher"


	//On fait une première boucle pour tester tous les exe
	for (int i = 0; i < nbreLigne; i++) {

		// On fait une deuxième boucle pour tester toutes les map pour chaque exe
		int numMap = 0;
		double temps_tot = 0;
		double score_tot = 0;

		for (int k = 0; k < 4; k++) {
			double moyenne = 0; //variable de temps moyen pour une map
			double score_moy = 0; //variable de score moyen pour une map
			CInput in(string("..\\..\\..\\..\\..\\input\\" + tabIn[numMap] + ".in").c_str());

			// On créé le tableau de char pour l'appel system
			string strFichierAExec = nomRepertoire + "\\" + tabFichier[i]+ " ..\\..\\..\\..\\..\\input" + "\\" + tabIn[numMap] + ".in" + " " + tabIn[numMap] + ".out";
			numMap++;
			const char *cstrFichierAExec = strFichierAExec.c_str();
			for (int j = 0; j < 5; j++) { // On fait une troisième boucle pour calculer le temps d'exécution plusieurs fois et faire une moyenne
				start = chrono::system_clock::now();
				system(cstrFichierAExec); // exécution du fichier
				end = chrono::system_clock::now();
				elapsed_seconds = end - start; // calcul de la durée
				moyenne += elapsed_seconds.count(); // On somme les durées qu'on divisera ensuite pour obtenir la moyenne
				
				// On appelle le referee
				CSolution sln(string(tabIn[numMap] + ".out").c_str());
				CReferee ref(&in, &sln);
				score_moy += ref.score();
			}

			temps_tot += moyenne/5;
			score_tot += score_moy/5;
		}

		tabResultat.push_back(make_pair(tabFichier[i], temps_tot)); // Recopie du temps d'exécution associé son fichier dans le tableau
		tabResultat_score.push_back(make_pair(tabFichier[i], score_tot)); // Recopie du score associé son fichier dans le tableau des scores
	}

	
	string strSuppOut;
	const char *cstrSuppOut;
	// On supprime les fichiers .out
	for (int supp = 0; supp < 4; supp++) {
		strSuppOut = "del " + tabIn[supp] + ".out";
		cstrSuppOut = strSuppOut.c_str();
		system(cstrSuppOut);
	}

	// On trie les tableaux résultats	
	sort(tabResultat.begin(), tabResultat.end(), pairCompare);
	sort(tabResultat_score.begin(), tabResultat_score.end(), pairCompare_dec);

	ofstream monFlux(nomFichier); // Ecriture des tableaux résultats dans le fichier souhaité
	if (monFlux){

		monFlux << "Classement par temps d'exécution totale moyen par map: " << std::endl;

		for (int i = 0; i < nbreLigne; i++) {
			monFlux << i+1 << ")" << tabResultat[i].first << " : " << tabResultat[i].second << "s\n";
		}
		monFlux << "Classement par score totale moyen par map: " << std::endl;

		for (int i = 0; i < nbreLigne; i++) {
			monFlux << i+1 << ")" << tabResultat_score[i].first << " : " << tabResultat_score[i].second << "\n";
		}
	}
	else
	{
		cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
	}
	monFlux.close();
	return 0;
}
