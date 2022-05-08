#ifndef WEAPONS_AK47_H
#define WEAPONS_AK47_H

class Weapons_ak47{

    public:
        
		//Find weapon
		int weap = 1;
        float r;
	    float step;
	    int damage_ak = 25;
	    //if ak auto mode
	    int shooting = 0;
	    //Ak shooting interval 
	    float shot_interval = 0.07;
	    float shot_before;
	    int bullet_ak = 30, bulletNum = 30;
	    float meg_changing, meg_change = 2.0, changflag = 0;
	    int shoot = 0;
        void beginShoot();
        void reload();
};
#endif