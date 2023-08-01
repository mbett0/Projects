#ifndef __CN_HPP__
#define __CN_HPP__

#include "Player.hpp"

class Cn : public Player{
	public: 
	
	Cn(){}
	Cn(int rank, string name, double rebounds, double points, double assists, double steals, double blocks, double FGPercent, double FGA, double threePA, double threeP){
        this->rank = rank;
        this->name = name;
        //this->team = team;
        this->rebounds = rebounds;
        this->points = points;
        this->assists = assists;
        this->steals = steals;
        this->blocks = blocks;
        this->FGPercent = FGPercent;
        this->FGA = FGA;
        this->threePA = threePA;
        this->threeP = threeP;
        Assist = new PfCnAst();
        Defense = new PfCnDef();
        Points = new CnPpg();
        Rebounds = new PfCnRb();
        FGPcnt = new PfCnFgPcnt();

}
string GetPosition(){
	return "Cn";
}
double rating(){
		rank = 100*(this->Assist->rate(this->GetAssists()) + this->Defense->rate(this->GetSteals(), this->GetBlocks()) + this->FGPcnt->rate(this->GetFGPercent()) + this->Points->rate(this->GetPoints()) + this->Rebounds->rate(this->GetReb()))/84;
		return rank;
}
};

#endif

