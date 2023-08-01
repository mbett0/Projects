#ifndef __Main_Test_HPP__
#define __Main_Test_HPP__
#include "gtest/gtest.h"
#include "Player.hpp"
#include "Team.hpp"
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

TEST(TEAM_TEST, GetPlayer){
	
	Player* p1 = new Sg(2, "Bradley Beal",4.2,30.6,6.1,1.2,0.4,22.9,.455,8.4,.353 );
        Player* p2 = new Pg(4, "Trae Young",4.2,29.6,9.3,1.1,0.1,.437,20.8,9.5,.361 );
        Player* p3 = new Pf(2, "Bradley Beal",4.2,30.6,6.1,1.2,0.4,22.9,.455,8.4,.353 );
        Player* p4 = new Cn(10,"Karl-Anthony Towns",10.2,26.5,4.4,0.9,1.2,0.508,17.8,7.9,0.412 );
        Player* p5 =  new Sf(1, "James Harden",6.4, 34.4, 7.4, 1.7, 0.9,.435,22.7, 12.6, .352 );
	
	Team* tp = new Team();

	tp->AddPlayer(p1);
        tp->AddPlayer(p2);
        tp->AddPlayer(p3);
        tp->AddPlayer(p4);
        tp->AddPlayer(p5);		
	
	//std::cout << tp->RemovePlayer(0) << std::endl;
	//Player* pp = new Player();
	//tp->RemovePlayer(0);a
	EXPECT_EQ(tp->GetPlayerName(0),"Bradley Beal");
}


TEST(TEAM_TEST, TeamSize_TeamName_and_rating){
        std::string team_name = "Rockets";      
        Team* t = new Team(team_name);
        EXPECT_EQ(t->GetName(),team_name );
        
        Team* tp = new Team();
        Player* p1 = new Sg(2, "Bradley Beal",4.2,30.6,6.1,1.2,0.4,22.9,.455,8.4,.353 );
        Player* p2 = new Pg(4, "Trae Young",4.2,29.6,9.3,1.1,0.1,.437,20.8,9.5,.361 );
        Player* p3 = new Pf(2, "Bradley Beal",4.2,30.6,6.1,1.2,0.4,22.9,.455,8.4,.353 );
        Player* p4 = new Cn(10,"Karl-Anthony Towns",10.2,26.5,4.4,0.9,1.2,0.508,17.8,7.9,0.412 );
        Player* p5 =  new Sf(1, "James Harden",6.4, 34.4, 7.4, 1.7, 0.9,.435,22.7, 12.6, .352 );
        tp->AddPlayer(p1);
        tp->AddPlayer(p2);
        tp->AddPlayer(p3);
        tp->AddPlayer(p4);
        tp->AddPlayer(p5);
        
        EXPECT_EQ(tp->TeamSize(),5);
        
        ASSERT_LE(tp->rating(), 92.5796);       
}

TEST(TEAM_TEST, Display_Test){

	Player* p1 = new Sg(2, "Bradley Beal",4.2,30.6,6.1,1.2,0.4,22.9,.455,8.4,.353 );
        Player* p2 = new Pg(4, "Trae Young",4.2,29.6,9.3,1.1,0.1,.437,20.8,9.5,.361 );
        Player* p3 = new Pf(2, "Bradley Beal",4.2,30.6,6.1,1.2,0.4,22.9,.455,8.4,.353 );
        Player* p4 = new Cn(10,"Karl-Anthony Towns",10.2,26.5,4.4,0.9,1.2,0.508,17.8,7.9,0.412 );
        Player* p5 =  new Sf(1, "James Harden",6.4, 34.4, 7.4, 1.7, 0.9,.435,22.7, 12.6, .352 );

        Team* tp = new Team();

        tp->AddPlayer(p1);
        tp->AddPlayer(p2);
        tp->AddPlayer(p3);
        tp->AddPlayer(p4);
        tp->AddPlayer(p5);
	
	tp->Display();
	

}
TEST(TEAM_TEST, RemovePlayer){


        Player* p1 = new Sg(2, "Bradley Beal",4.2,30.6,6.1,1.2,0.4,22.9,.455,8.4,.353 );
        Player* p2 = new Pg(4, "Trae Young",4.2,29.6,9.3,1.1,0.1,.437,20.8,9.5,.361 );
        Player* p3 = new Pf(2, "Bradley Beal",4.2,30.6,6.1,1.2,0.4,22.9,.455,8.4,.353 );
        Player* p4 = new Cn(10,"Karl-Anthony Towns",10.2,26.5,4.4,0.9,1.2,0.508,17.8,7.9,0.412 );
        Player* p5 =  new Sf(1, "James Harden",6.4, 34.4, 7.4, 1.7, 0.9,.435,22.7, 12.6, .352 );

        Team* tp = new Team();

        tp->AddPlayer(p1);
        tp->AddPlayer(p2);
        tp->AddPlayer(p3);
        tp->AddPlayer(p4);
        tp->AddPlayer(p5);
        EXPECT_EQ(tp->TeamSize(),5);
        Player* pt = tp->RemovePlayer(2);
         EXPECT_EQ(tp->TeamSize(),4);





	
}
#endif
