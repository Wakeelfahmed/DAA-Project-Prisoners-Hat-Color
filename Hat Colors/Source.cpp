#include <iostream>
#include <vector>
using namespace std;
enum HatColors { BLACK, WHITE };
class Tester;
class Prisoner {
	friend class Tester;
public:
	HatColors hatColor;
	bool steppedForward;	//bool caused_testfail;
	Prisoner() : hatColor(WHITE), steppedForward(false) {}
	Prisoner(HatColors color) : hatColor(color), steppedForward(false) {}
};
class Tester
{
private:
	void BlackHat(vector<Prisoner>& prisoners);
public:
};

void passTest(vector<Prisoner>& prisoners) {
	int BlackHats_count = 0, Max_Black_Hat_Founds = 0;
	for (int Prisoners_loop = 0; Prisoners_loop < prisoners.size(); ++Prisoners_loop) {
		BlackHats_count = 0;
		// Count the number of black hats among other prisoners
		for (int scan_loop = 0; scan_loop < prisoners.size(); ++scan_loop) {
			if (scan_loop != Prisoners_loop && prisoners[scan_loop].hatColor == BLACK)
				BlackHats_count++;
		}
		if (BlackHats_count > Max_Black_Hat_Founds)
			Max_Black_Hat_Founds = BlackHats_count;
		// Case 1: 1 Black Hat
		if (BlackHats_count == 0) {
			prisoners[Prisoners_loop].steppedForward = true;
			//cout << "Smart Prisoners ESCAPED !!!" << endl;
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
			for (int scan_loop = 0; scan_loop < prisoners.size(); ++scan_loop) {
				if (scan_loop != Prisoners_loop && prisoners[scan_loop].hatColor == BLACK) {
					BlackHatsSeen++;
				}
			}

			// Check if the current prisoner can deduce the color of their hat
			if (BlackHatsSeen == currentLineup - 1) {
				prisoners[Prisoners_loop].steppedForward = true;
				//break;
			}
		}
		currentLineup++;
	}
}
bool Jailer_Test(const vector<Prisoner> prisoners) {
	bool Test = true;
	for (Prisoner p : prisoners)
	{
		if (p.hatColor == WHITE && p.steppedForward)
			Test = false;
		if (p.hatColor == BLACK && p.steppedForward == false)
			Test = false;
	}
	if (Test)
		cout << "ESCAPED" << endl;
	else
		cout << "FAILED, Excecuted" << endl;
	return Test;
}
int main() {
	const int numPrisoners = 12;
	std::vector<Prisoner> Testprisoners(numPrisoners);

	// Generate all possible combinations
	for (int i = 0; i < (1 << numPrisoners); ++i) {
		for (int j = 0; j < numPrisoners; ++j) {
			Testprisoners[j].hatColor = ((i >> j) & 1) ? BLACK : WHITE;
			Testprisoners[j].steppedForward = false;
		}
		for (Prisoner p : Testprisoners)
			if (p.hatColor == BLACK)
				cout << "B ";
			else
				cout << "W ";
		cout << endl;
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

		//prisoners[0].hatColor = BLACK;
		//prisoners[1].hatColor = BLACK;
		//prisoners[2].hatColor = BLACK;
		//prisoners[3].hatColor = BLACK;
		//prisoners[4].hatColor = BLACK;
		//prisoners[5].hatColor = BLACK;
		//prisoners[6].hatColor = BLACK;
		//prisoners[7].hatColor = BLACK;
		//prisoners[8].hatColor = BLACK;
		//prisoners[9].hatColor = BLACK;
		//prisoners[10].hatColor = BLACK;
		//prisoners[11].hatColor = BLACK;
		passTest(Testprisoners);

		//passTest(prisoners);

		// Check results
		//for (int i = 0; i < prisoners.size(); ++i) {
		//	cout << "Prisoner " << i << ": " << (prisoners[i].steppedForward ? "Stepped FORWARD" : "Stayed in line");
		//	if (prisoners[i].steppedForward && prisoners[i].hatColor == WHITE)
		//		cout << "  but color white";
		//	else
		//		cout << endl;
		//}
		Jailer_Test(Testprisoners);
	}
}