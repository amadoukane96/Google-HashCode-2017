#include "CSolver.h"
#include "CReferee.h"
#include "strats/glouton/SGreedy.h"
#include <fstream>
#include <time.h>
#include "strats/steinerTree.h"
#include <string>

#include <filesystem>

namespace fs = std::experimental::filesystem;



int main(int argv, char* argc[]) {

	std::ofstream out;

	
	if (argv >= 3) {
		CInput in(argc[1]);
		CSolver<SGreedy> brute(&in, SGreedy());
		CSolution sln = brute.solve();

		CReferee ref(&in, &sln);
		std::cout << "score: " << ref.score() << std::endl;

		out.open(argc[2]);
		out << sln;
	}
	else {
		std::cout << "Error: missing arguments" << std::endl;
	}
	

	//autre version qui lit tous les map.
	/*
	
	double elapsed = 0;
	std::string path = "../../input/";

	for (auto & p : fs::directory_iterator(path)) {

		CInput in(p.path().string().c_str());
		CSolver<SGreedy> brute(&in, SGreedy());


		std::string out_path("../../output/");
		out_path.append(p.path().stem().string() + ".out");
		out.open(out_path);

		time_t start, end;

		std::cout << p.path().filename().string() << std::endl;

		start = time(NULL);
		CSolution sln = brute.solve();
		end = time(NULL);
		elapsed = difftime(end, start);
	
		out << sln;
	
		CReferee ref(&in, &sln);
		std::cout << "-> time = " << elapsed << "s, score = " << ref.score() << std::endl;
		out.close();


	}
	*/

	return 0;
}