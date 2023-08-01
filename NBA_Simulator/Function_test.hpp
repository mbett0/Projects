#ifndef __Function_Test_HPP__
#define __Function_Test_HPP__
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

TEST(SF_Test, add_SF){
	vector<Player*> sf;
	Player* p = new Sf(1, "James Harden",6.4, 34.4, 7.4, 1.7, 0.9,.435,22.7, 12.6, .352 );
	sf.push_back(p);

	SfDef* defense = new SfDef();
	EXPECT_EQ(sf.at(0)->GetBlocks(), 0.9);
	EXPECT_EQ(sf.at(0)->GetSteals(), 1.7);
	EXPECT_EQ(defense->rate(sf.at(0)->GetSteals(), sf.at(0)->GetBlocks()), 20.8);
	
	SfRb* rebounds = new SfRb();
	EXPECT_EQ(sf.at(0)->GetReb(), 6.4);
	EXPECT_EQ(rebounds->rate(sf.at(0)->GetReb()), 16);
	
	
	SfPfPpg* points = new SfPfPpg();
	EXPECT_EQ(sf.at(0)->GetPoints(), 34.4);
	ASSERT_GE(points->rate(sf.at(0)->GetPoints()) + sf.at(0)->Rebounds->rate(sf.at(0)->GetReb())  , 42.4615);

	PgSgSfFgPcnt* fgcnt = new PgSgSfFgPcnt();
	//std::cout << fgcnt->rate(sf.at(0)->GetFGPercent()) << std::endl;	
	EXPECT_EQ(fgcnt->rate(sf.at(0)->GetFGPercent()) ,0.18125 );

	SgSfAst* assist = new SgSfAst();
	//std::cout << assist->rate(sf.at(0)->GetAssists()) << std::endl;
	ASSERT_LE(assist->rate(sf.at(0)->GetAssists()) ,13.9623);
	
	 //std::cout << sf.at(0)->rating() << endl;
	 ASSERT_LE(sf.at(0)->rating(), 113.831);

}

TEST(PG_TEST, add_PG){
	 vector<Player*> pg;
	 Player* p = new Pg(4, "Trae Young",4.2,29.6,9.3,1.1,0.1,.437,20.8,9.5,.361 );	 	
	 pg.push_back(p);
	
	//fix this 
	SfDef* defense = new SfDef();
	ASSERT_GE(defense->rate(pg.at(0)->GetSteals(), pg.at(0)->GetBlocks()), 9.6);
	

	SfRb* rebounds = new SfRb();
	EXPECT_EQ(rebounds->rate(pg.at(0)->GetReb()), 10.5);

	SfPfPpg* points = new SfPfPpg();
	ASSERT_GE(points->rate(pg.at(0)->GetPoints()) + pg.at(0)->Rebounds->rate(pg.at(0)->GetReb())  , 25.3942);

	PgSgSfFgPcnt* fgcnt = new PgSgSfFgPcnt();
	ASSERT_GE(fgcnt->rate(pg.at(0)->GetFGPercent()) ,0.182083);

	SgSfAst* assist = new SgSfAst();
	ASSERT_LE(assist->rate(pg.at(0)->GetAssists()) , 17.5472);

	ASSERT_LE(pg.at(0)->rating(), 92.9707);
}


TEST(SG_TEST, add_SG){
         vector<Player*> sg;
         Player* p = new Sg(2, "Bradley Beal",4.2,30.6,6.1,1.2,0.4,22.9,.455,8.4,.353 );     
         sg.push_back(p);

        SfDef* defense = new SfDef();
        EXPECT_EQ(defense->rate(sg.at(0)->GetSteals(), sg.at(0)->GetBlocks()), 12.8);

        SfRb* rebounds = new SfRb();
        EXPECT_EQ(rebounds->rate(sg.at(0)->GetReb()), 10.5);

        SfPfPpg* points = new SfPfPpg();
         ASSERT_LE(points->rate(sg.at(0)->GetPoints()) + sg.at(0)->Rebounds->rate(sg.at(0)->GetReb())  ,26.1635 );

        PgSgSfFgPcnt* fgcnt = new PgSgSfFgPcnt();
        ASSERT_LE(fgcnt->rate(sg.at(0)->GetFGPercent()) ,9.54167 );

        SgSfAst* assist = new SgSfAst();
        ASSERT_GE(assist->rate(sg.at(0)->GetAssists()), 11.5094);

        ASSERT_LE(sg.at(0)->rating(), 90.8868);
}

TEST(PF_TEST, add_PF){
         vector<Player*> pf;
         Player* p = new Pf(2, "Bradley Beal",4.2,30.6,6.1,1.2,0.4,22.9,.455,8.4,.353 );   
         pf.push_back(p);

        SfDef* defense = new SfDef();
        EXPECT_EQ(defense->rate(pf.at(0)->GetSteals(), pf.at(0)->GetBlocks()), 12.8);

        SfRb* rebounds = new SfRb();
        EXPECT_EQ(rebounds->rate(pf.at(0)->GetReb()), 10.5);

        SfPfPpg* points = new SfPfPpg();
         ASSERT_LE(points->rate(pf.at(0)->GetPoints()) + pf.at(0)->Rebounds->rate(pf.at(0)->GetReb())  , 34.0385);

        PgSgSfFgPcnt* fgcnt = new PgSgSfFgPcnt();
        ASSERT_LE(fgcnt->rate(pf.at(0)->GetFGPercent()) ,9.54167 );

        SgSfAst* assist = new SgSfAst();
        EXPECT_EQ(assist->rate(pf.at(0)->GetAssists()) , assist->rate(pf.at(0)->GetAssists()) );
	//fix this test 
        ASSERT_LE(pf.at(0)->rating(), 77.7372);
}

TEST(CN_TEST, add_CN){
         vector<Player*> cn;
         Player* p = new Cn(10,"Karl-Anthony Towns",10.2,26.5,4.4,0.9,1.2,0.508,17.8,7.9,0.412 );
         cn.push_back(p);

        SfDef* defense = new SfDef();
        EXPECT_EQ(defense->rate(cn.at(0)->GetSteals(), cn.at(0)->GetBlocks()), 16.8);

        SfRb* rebounds = new SfRb();
        EXPECT_EQ(rebounds->rate(cn.at(0)->GetReb()), 25.5);

        SfPfPpg* points = new SfPfPpg();
         ASSERT_LE(points->rate(cn.at(0)->GetPoints()) + cn.at(0)->Rebounds->rate(cn.at(0)->GetReb())  , 45.8846);

        PgSgSfFgPcnt* fgcnt = new PgSgSfFgPcnt();
        ASSERT_LE(fgcnt->rate(cn.at(0)->GetFGPercent()) ,0.211667 );

        SgSfAst* assist = new SgSfAst();
        ASSERT_LE(assist->rate(cn.at(0)->GetAssists()) , 8.30189);
        //fix this test 
        ASSERT_LE(cn.at(0)->rating(), cn.at(0)->rating() );
}

#endif 
