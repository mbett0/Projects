#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__
#include "Base.hpp"
#include <string>
#include <iostream>
#include "AstBase.hpp"
#include "DefBase.hpp"
#include "FgPcntBase.hpp"
#include "PpgBase.hpp"
#include "RbBase.hpp"
#include "PgAst.hpp"
#include "SgSfAst.hpp"
#include "PfCnAst.hpp"
#include "PgSgDef.hpp"
#include "SfDef.hpp"
#include "PfCnDef.hpp"
#include "PgSgSfFgPcnt.hpp"
#include "PfCnFgPcnt.hpp"
#include "PgPpg.hpp"
#include "SgPpg.hpp"
#include "SfPfPpg.hpp"
#include "CnPpg.hpp"
#include "PgSgRb.hpp"
#include "SfRb.hpp"
#include "PfCnRb.hpp"

class RbBase;
class AstBase;
class DefBase; 
class FgPcntBase;
class PpgBase;
class PgAst;
class SgSfAst;
class PfCnAst;
class PgSgDef;
class SfDef;
class PfCnDef;
class PgSgSfFgPcnt;
class PfCnFgPcnt;
class PgPpg;
class SgPpg;
class SfPfPpg;
class CnPpg;
class PgSgRb;
class SfRb;
class PfCnRb;

using namespace std;

class Player: public Base {
	public: 
	string name;
	double rebounds;
	double points, assists, steals, blocks, FGPercent, FGA, threePA, threeP, rank;
	AstBase* Assist;
        DefBase* Defense;
        FgPcntBase* FGPcnt;
        PpgBase* Points;
        RbBase* Rebounds;

        /* Constructors */
        //public:
	/* Constructors */
        Player() { };
        /* Pure Virtual Functions */
        double rating(){
		rank = this->Assist->rate(this->GetAssists()) + this->Defense->rate(this->GetSteals(), this->GetBlocks()) + this->FGPcnt->rate(this->GetFGPercent()) + this->Points->rate(this->GetPoints()) + this->Rebounds->rate(this->GetReb());
		return rank;
	}
	virtual string GetPosition()=0;
	double GetRank(){
		return rating();
	}
        string GetName(){return name;};
	double  GetAssists(){return assists;};
	double GetReb(){return rebounds;};
	double GetPoints(){return points;};
	double GetSteals(){return steals;};
	double GetBlocks(){return blocks;};
	double GetFGPercent(){return FGPercent;};
	double GetFGA(){return FGA;};
	double GetThreePA() {return threePA;};
	double getThreeP(){return threeP;};
	void Display(){
		rating();
		cout << GetPosition() << " " << name << " Rating: " << rank << endl;
	} 
	
};

#endif

