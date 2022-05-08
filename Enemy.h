#ifndef ENEMY_H
#define ENEMY_H

class Enemy{
    public:

        //position
	    double x;
	    double y;
	    double z;

        //Size of enemy
	    double size;

	    double angle;

        //If keep tracking player
        int tryGoToGoalFlag;

        //find enemy is alive or not  true -> alive
        bool live;
        
        //if attacking
        bool attackFlag;

        //if attack finished
        bool attackFinishFlag;

        //view range of enemy
        double viewRange;

        //enemy and target angle
        double robotToGoalAngle;

        int blood;
        int atk_dmg = 25;

		//Speed of enemy
        double zstep;

		int enemyAtk_interval;

        Enemy(){
		x = 0;
		y = 1;
		z = 1;
		size = 1;
		angle = 0;
		
		tryGoToGoalFlag = 1;
		live = true;
		attackFlag = false;
        attackFinishFlag = false;
		viewRange = 1000;

        zstep = 0.6;
		robotToGoalAngle = 0;
		blood = 100;
		enemyAtk_interval = 120;
	    }

        Enemy(double x, double y, double z, double size, int blood){
		this->x = x;
		this->y = y;
		this->z = z;
		this->size = size;
		this->blood = blood;
		angle = 0;
		tryGoToGoalFlag = 1;
		live = true;
		attackFlag = false;
        attackFinishFlag = false;
		viewRange = 1000;

        zstep = 0.6;
		robotToGoalAngle = 0;

		enemyAtk_interval = 120;
		
	    }

        void drawEnemy();
	    void moveToPlayer(double px, double py, double pz);
        void enemyStartAttack();
        void judgeDamage(int damage);

};
#endif