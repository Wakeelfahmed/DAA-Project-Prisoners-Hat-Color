#include <iostream>
#include <vector>
using namespace std;
enum HatColors { BLACK, WHITE };
class Prisoner {
public:
	HatColors hatColor;
	bool steppedForward;
	Prisoner() : hatColor(WHITE), steppedForward(false) {}
	Prisoner(HatColors color) : hatColor(color), steppedForward(false) {}
};

void passTest(vector<Prisoner>& prisoners) {
	int BlackHats_count = 0, Max_Black_Hat_Founds = 0;
	for (int Prisoners_loop = 0; Prisoners_loop < prisoners.size(); ++Prisoners_loop) {
		BlackHats_count = 0;
		// Count the number of black hats among other prisoners
		for (int scan_loop = 0; scan_loop < prisoners.size(); ++scan_loop)
			if (scan_loop != Prisoners_loop && prisoners[scan_loop].hatColor == BLACK)
				BlackHats_count++;

		if (BlackHats_count > Max_Black_Hat_Founds)
			Max_Black_Hat_Founds = BlackHats_count;

		// Case 1: 1 Black Hat
		if (BlackHats_count == 0) {
			prisoners[Prisoners_loop].steppedForward = true;
			cout << "P" << Prisoners_loop + 1 << "\t";
			return;
		}
	}
	// Case: More than 1 Black Hat
	int currentLineup = 1;  // Start from the second lineup
	while (currentLineup <= Max_Black_Hat_Founds) {
		// Check subsequent lineups
		for (int Prisoners_loop = 0; Prisoners_loop < prisoners.size(); ++Prisoners_loop) {
			int BlackHatsSeen = 0;
			// Count the number of black hats seen by this prisoner in the current lineup
			for (int scan_loop = 0; scan_loop < prisoners.size(); ++scan_loop)
				if (scan_loop != Prisoners_loop && prisoners[scan_loop].hatColor == BLACK)
					BlackHatsSeen++;

			// Check if the current prisoner can deduce the color of their hat
			if (BlackHatsSeen == currentLineup - 1) {
				prisoners[Prisoners_loop].steppedForward = true;
				cout << "P" << Prisoners_loop + 1 << " ";
			}
		}
		currentLineup++;
	}
}
bool Jailer_Test(const vector<Prisoner> prisoners) {
	bool Test = true;
	for (Prisoner p : prisoners)
		if (p.hatColor == WHITE && p.steppedForward)
			Test = false;
		else if (p.hatColor == BLACK && p.steppedForward == false)
			Test = false;

	if (Test)
		cout << "\t\t\t\tESCAPED" << endl;
	else
		cout << "\t\t\t\tFAILED, Excecuted" << endl;
	return Test;
}
int main() {
	const int numPrisoners = 12;
	std::vector<Prisoner> Testprisoners(numPrisoners);
	cout << "\x1b[3;96mPrisoners Combination\t\tStepped Forward\t\t\tWarden Result\033[0m" << endl;
	// Generate all possible combinations
	for (int i = 0; i < (1 << numPrisoners); ++i) {
		for (int j = 0; j < numPrisoners; ++j) {
			Testprisoners[j].hatColor = ((i >> j) & 1) ? BLACK : WHITE;
			Testprisoners[j].steppedForward = false;
		}
		int allwhite = 0;
		for (Prisoner p : Testprisoners)
			if (p.hatColor == WHITE)
				allwhite++;

		int allblack = 0;
		for (Prisoner p : Testprisoners)
			if (p.hatColor == BLACK)
				allblack++;

		if (allblack == 12 || allwhite == 12)
			continue;	//dont run test

		for (Prisoner p : Testprisoners)
			if (p.hatColor == BLACK)
				cout << "B ";
			else
				cout << "W ";
		cout << "   ";

		passTest(Testprisoners);	//The Algo

		Jailer_Test(Testprisoners); //Wardens checks, and Successful (escaped) if & only if ALL BLACKS STEPPED FORWARD
	}
}