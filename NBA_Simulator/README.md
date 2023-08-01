# CS Project Deliverable 

**A**. The complete application use **Factory, Composite, and Stratgey**. The factory is used to create the list of players that the rest of the program relies on by creating Player objects from the text file that was passed in. Composite is used to generate the sub-classes that are composite to the Player Component with the leaves of classes obtaining the individual stats corresponding from the *Rb, Base Def, Ast, FGPercent, and Ppg* classes. The last design pattern that was used was strategy in getting the rating from each player. These were implemented by calling the *Rb, Base Def, Ast, FGPercent, and Ppg* classes which used a different algorithm to rate the players based on the class given to the player.   


![S](https://user-images.githubusercontent.com/43631772/88321104-79b08a00-ccd3-11ea-83fe-b73547148d23.jpg)
![Screenshot (22)_LI](https://user-images.githubusercontent.com/62957652/88324508-a31fe480-ccd8-11ea-9556-45e853656496.jpg)
![Untitled Diagram (1)](https://user-images.githubusercontent.com/43631772/88324831-1d506900-ccd9-11ea-9f3b-b428c0fad0f2.jpg)





**B**. The application generates a menu display. Allowing the user to choose between generated commands to **Create New Team, Resume Old Team, Faceoff and Restart League** 


![First Menu](https://user-images.githubusercontent.com/62957652/88321007-55ed4400-ccd3-11ea-9255-7840a563e517.png)


*Create New Team* allows the user to Enter Team name. The menu will then Prompt the user to **Add Player, Remove Player, Output All Available Players, Output roster, and Back** 

![Screenshot (12)](https://user-images.githubusercontent.com/62957652/88321357-e166d500-ccd3-11ea-83e7-2d9185229ca3.png)



*Add Player* will allow the user to select a player from an individual position consisting from **Pg, Sg, Sf, Pf, C**. Selecting either position will prompt the to select a player from that given position. The players will be displayed along with their overall stat ranking. Players can be chosen by entering the position number and user can select from *Next Page or Previous Page* to obatin players.

![Screenshot (13)](https://user-images.githubusercontent.com/62957652/88321400-f6436880-ccd3-11ea-8233-fb2901421b55.png)


*Remove Player* will allow the user to remove a given player from their team by just entering the position number. 

![Screenshot (14)](https://user-images.githubusercontent.com/62957652/88321437-04918480-ccd4-11ea-8018-00125bf248f5.png)



*Output All Available Players* allows the user to see set roster.

![Screenshot (15)](https://user-images.githubusercontent.com/62957652/88321463-107d4680-ccd4-11ea-8b76-4fcfb0358038.png)


*Output roster* outputs the user's team roster


![Screenshot (16)](https://user-images.githubusercontent.com/62957652/88321484-1a06ae80-ccd4-11ea-873e-5d1e34fd0482.png)


*Resume Old Team* allows the user to make player changes or output roster

![Screenshot (17)](https://user-images.githubusercontent.com/62957652/88321507-2559da00-ccd4-11ea-8bd5-cc481663e1a9.png)



*Faceoff* Allows the user to faceoff two user generated team rosters and will display the overall points scored.\

![Screenshot (18)](https://user-images.githubusercontent.com/62957652/88321537-30146f00-ccd4-11ea-89f0-de61556e287b.png)

![Screenshot (20)](https://user-images.githubusercontent.com/62957652/88322659-e2006b00-ccd5-11ea-959c-dc08ded35fb1.png)

*Restart League* Will reset the teams and exit the program



**C**. The application can be run by entering **c++ -o main main.cpp  and running ./main** 








# CS 100 Programming Project
A. Rahul Katwala rkatw001@ucr.edu

B. NBA Player Rater

C. App gets data from nba player stats websites, rates the players, and helps make an optimal team. User can then faceoff against two generated user teams to compare the optimal team. The application will also store the user's past teams and allow the user to generate a team from a set roster. 

D. This app helps gather information about nba players to create an optimal fantasy team and helps people learn more about basketball. This will familiarize the user to player stats and compare their favorite player to the set roster.  

E. C++. Stats are obtained from https://basketball.realgm.com/nba/stats

F. The input will be a set of commands prompted by a menu. A roster of user chosen players will be displayed. User will also have the options to display the set roster along with the results from the faceoff command. User can save their rosters and use them again after the code is done compiling.  
