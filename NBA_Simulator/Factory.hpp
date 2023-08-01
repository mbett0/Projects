#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include "Player.hpp"
#include "Pg.hpp"
#include "Sg.hpp"
#include "Sf.hpp"
#include "Pf.hpp"
#include "Cn.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <list>
//#include "Player_Header.h"

using namespace std;

class Player;
class Pg;
class Sg;
class Sf;
class Pf;
class Cn;
class Factory {
	public:
	Factory(){};
		//void Parser(vector<string>, vector<Player*>);
	void Parser(vector<string>& player, vector<Player*>& playerList){
		string name = " ";
		string last = " ";
    		int rank = 0;
    		string position = " ";
    		double FGA = 0.0;
    		double FG = 0.0;
    		double threePA = 0.0;
    		double threeP = 0.0;
    		double RPG = 0.0;
    		double APG = 0.0;
    		double SPG = 0.0;
    		double BPG = 0.0;
    		double PPG = 0.0;
		int i = 0;
		//while(i < player.size()) {
			if(rank == 0){
				istringstream iss(player.at(i));
				iss >> rank;
				++i;
			}
			if(name == " "){
				istringstream iss(player.at(i));
                                iss >> name;
                                ++i;
			//	string last = " ";
				istringstream isss(player.at(i));
                                isss >> last;
                                ++i;
				name = name + " " + last;
			}
			if(position == " "){
				istringstream iss(player.at(i));
                                iss >> position;
                                ++i;
 			}
			if(FGA == 0){
				istringstream iss(player.at(i));
                                iss >> FGA;
                                ++i;
			}
			if(FG == 0){
				istringstream iss(player.at(i));
                                iss >> FG;
                                ++i;
			}
			if(threePA == 0){
				istringstream iss(player.at(i));
                                iss >> threePA;
                                ++i;
			}
			if(threeP == 0){
				istringstream iss(player.at(i));
                                iss >> threeP;
                                ++i;
			}
			if(RPG == 0){
				istringstream iss(player.at(i));
                                iss >> RPG;
                                ++i;
			}
			if(APG == 0){
				istringstream iss(player.at(i));
                                iss >> APG;
                                ++i;
			}
			if(SPG == 0){
				istringstream iss(player.at(i));
                                iss >> SPG;
                                ++i;
			}
			if(BPG == 0){
				istringstream iss(player.at(i));
                                iss >> BPG;
                                ++i;
			}
			if(PPG == 0) {
				istringstream iss(player.at(i));
                                iss >> PPG;
                                ++i;
			}
		//}
		Player* p = nullptr;
		if(position == "PG"){
			p = new Pg(rank, name, RPG, PPG, APG, SPG, BPG, FG, FGA, threePA, threeP);
		}
		if(position == "SG"){
                        p = new Sg(rank, name, RPG, PPG, APG, SPG, BPG, FG, FGA, threePA, threeP);
                }
		if(position == "SF"){
                        p = new Sf(rank, name, RPG, PPG, APG, SPG, BPG, FG, FGA, threePA, threeP);
                }
		if(position == "PF"){
                        p = new Pf(rank, name, RPG, PPG, APG, SPG, BPG, FG, FGA, threePA, threeP);
                }
		if(position == "CN"){
                        p = new Cn(rank, name, RPG, PPG, APG, SPG, BPG, FG, FGA, threePA, threeP);
                }
		playerList.push_back(p);	
	}

	void ReadPlayers(vector<Player*>& pg, vector<Player*>& sg, vector<Player*>& sf, vector<Player*>& pf, vector<Player*>& cn){
		//Change file name
		ifstream file("All_Positions_Stats.txt");
    		string input;
    		if (file.is_open()) {
     		   	cout << "Loading Players..." << endl;
    		}
    		else{
        		cout << "file was not found" << endl;
    		}
    		while (file >> input) {
       			getline(file,input);
        		//cout << input <<endl;
                	vector<string> player;
    			std::istringstream ss(input);

    			do {
        			string tmp;
        			ss >> tmp;
        			player.push_back(tmp);
        			//cout << tmp << endl;
    			}while (ss);
			if(player.at(3) == "PG"){
				//cout << "Parser pg" << endl;
				Parser(player, pg);
			}else if(player.at(3) == "SG"){
				//cout << "Parser sg" << endl;
				Parser(player, sg);
			}else if(player.at(3) == "SF"){
				Parser(player, sf);
				//cout << "Parser sf" << endl;
			}else if(player.at(3) == "PF"){
				Parser(player, pf);
				//cout << "Parser pf" << endl;
			}else if(player.at(3) == "CN"){
				Parser(player, cn);
				//cout << "Parser Cn" << endl;
			}else{
				cout << "Error loading player: " << player.at(2);
			}
               }
	}

};

#endif
