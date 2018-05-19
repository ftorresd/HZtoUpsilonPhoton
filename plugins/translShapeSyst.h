#include <iostream>

int translRocCor(string shapeSystMask) {
	if      (shapeSystMask == "statRocCorError_UP") return 1;
	// else if (shapeSystMask == "statRocCorError_DOWN") return 2;
	// else if (shapeSystMask == "refRocCorError_UP") return 3;
	// else if (shapeSystMask == "refRocCorError_DOWN") return 4;
	// else if (shapeSystMask == "profMassRocCorError_UP") return 5;
	// else if (shapeSystMask == "profMassRocCorError_DOWN") return 6;
	// else if (shapeSystMask == "fitMassRocCorError_UP") return 7;
	// else if (shapeSystMask == "fitMassRocCorError_DOWN") return 8;
	else if (shapeSystMask == "RocCorError_UP") return 7;
	else if (shapeSystMask == "RocCorError_DOWN") return 8;
	else return 0;
}


// int translPhoScaleResol(string shapeSystMask) {
// 	if      (shapeSystMask == "phoScale_stat_UP") return 1;
// 	else if (shapeSystMask == "phoScale_stat_DOWN") return 2;
// 	else if (shapeSystMask == "phoScale_syst_UP") return 3;
// 	else if (shapeSystMask == "phoScale_syst_DOWN") return 4;
// 	else if (shapeSystMask == "phoScale_gain_UP") return 5;
// 	else if (shapeSystMask == "phoScale_gain_DOWN") return 6;
// 	else if (shapeSystMask == "phoResol_rho_UP") return 7;
// 	else if (shapeSystMask == "phoResol_rho_DOWN") return 8;
// 	else if (shapeSystMask == "phoResol_phi_UP") return 9;
// 	else if (shapeSystMask == "phoResol_phi_DOWN") return 10;
// 	else return 0;
// }


// phoScale_stat_up
// phoScale_stat_dn
// phoScale_syst_up
// phoScale_syst_dn
// phoScale_gain_up
// phoScale_gain_dn
// phoResol_rho_up
// phoResol_rho_dn
// phoResol_phi_up
// phoResol_phi_dn
