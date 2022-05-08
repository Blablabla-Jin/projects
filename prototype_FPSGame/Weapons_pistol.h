#ifndef WEAPONS_PISTOL_H
#define WEAPONS_PISTOL_H

class Weapons_pistol{

    public:
        
		//find weapon
		int weap = 2;
        float r;
	    float step;
	    int shoot = 0;
	    int damage_pis = 50;
	    int bullet_pis = 7, bulletNum = 7;
	    float meg_changing, meg_change = 1.0, changflag = 0;
        
        void beginShoot();
        void reload();
};
#endif