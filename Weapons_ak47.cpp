#include "Weapons_ak47.h"

#include <ctime>

void Weapons_ak47::beginShoot(){

	r = 0;
	step = -3;
	shoot = 1;
}


//Gonna finish reloading after 2 seconds.
void Weapons_ak47::reload(){
	if(changflag == 1){
		if(clock() / 1000000.0 - meg_changing > meg_change){
			changflag = 0;
			bulletNum = bullet_ak;
		}
	}
}