#include <string.h>
#include "Team.hpp"
#include <iostream>
#include "Factory.hpp"
#include <vector>

using namespace std;


static vector<Player*> Point;
static vector<Player*> Shoot;
static vector<Player*> Small;
static vector<Player*> Power;
static vector<Player*> Center;
static vector<Team*> TeamList;

void tourny2();
void CreateRandomTeam();
void DeleteTeam(int);
void Tourny();
void Resume();
void sort( );
void SaveTeam(Team*);
void Versus();
bool is_number(const std::string& );
void selectionSort(vector<Player*>&, vector<Team*> &, string);
void outputRoster( Team*);
void addPlayer(vector<Player*> &, Team*,string);
void removePlayer(Team*);
void menu(Team*);
void  firstmenu();
void  outputAllPlayers( vector<Player*>& ,  Team* );
         
         
         
void  firstmenu(){
         string choice;
         
         cout << "Choose an option" << endl;
         cout << "1. Create New Team"<<endl;
         cout << "2. Resume Old Team" << endl;
         cout << "3. Faceoff" << endl;
	 cout << "4. Delete a Team" << endl;
    cout << "5. Tournament" << endl;
         cout << "6. Restart League"<< endl;

         cin >> choice;
         string tempName;
         if (choice =="1"){
             cout << "Enter Team Name" << endl;
             cin.ignore();
             getline(cin, tempName);
             Team* temp = new Team(tempName);
             TeamList.push_back(temp);
             menu(TeamList.back());
         }
	else if (choice == "5"){
        int lol;
        cout << "4 or 8 teams" << endl;
        cin >> lol;
        if (lol==8){
            Tourny();
        }
        else {
            tourny2();
        }
	//	CreateRandomTeam();
		firstmenu();
	}
         else if (choice == "2"){
        
             if(TeamList.size() == 0){
                 cout<< "No available teams, please create a team" << endl;
                 firstmenu();
             }
             else{
                 cout << "Available Teams: " << endl;
                 for(int i = 0; i < TeamList.size(); ++i){
                     cout << TeamList.at(i)->GetName() << endl;
                 }
                 cout << "Enter team name: " << endl;
                 cin.ignore();
                 getline(cin, tempName);
                 bool check = false;
                 for(int j = 0; j < TeamList.size(); ++j){
                     if(tempName == TeamList.at(j)->GetName()){
                         menu(TeamList.at(j));
                         check = true;
                     }
                 }
                 if(check == false){
                     cout << "Not an available team" << endl;
                     firstmenu();
                 }
             }
         }
         else if(choice =="7"){
             CreateRandomTeam();
             firstmenu();
         }
	else if(choice == "3"){
       		Versus();
    	}

	else if(choice == "4"){
        for (int i=0; i<TeamList.size();i++){
            cout << i+1 << ". " << TeamList.at(i)->GetName() << endl;
        }

        int j=0;
        cout << endl << "Select the number of the team you'd like to delete" << endl;
        cin >> j;
		DeleteTeam(j);
        firstmenu();
	}
    
	else if(choice != "6"){
       		cout << "Invalid input, try again" << endl;
       		firstmenu();
    	}
	else{
      		cout << "Thanks for playing" << endl;
	}
}
         
  
void selectionSort(vector<Player*>&j , Team* r, string pos)
{
    
    int min_idx;
  
   
    for (int i = 0; i < j.size()-1; i++)
    {
       
        min_idx = i;
        for ( int b = i+1; b < j.size(); b++){
            if (j.at(b)->rating() > j.at(min_idx)->rating()){
                min_idx = b;
            }
        }

        Player* u= j.at(i);
        j.at(i) = j.at(min_idx);
        j.at(min_idx)= u;
         
    }
    
    r->Sort();
    
}


int main( ) {

    Factory fact;
   
    fact.ReadPlayers(Point, Shoot, Small, Power, Center);
 
    vector<Player*>pg =  Point;
    vector<Player*>sg = Shoot;
    vector<Player*>sf =  Small;
    vector<Player*> pf =  Power;
    vector<Player*> cn= Center;
    sort();


    string temp="0";
    cout << "Press 1 to resume your last game, press any other button to restart." << endl;
    cin >> temp;
    if (temp =="1" ){
        Resume();
         
    }
    else {

        firstmenu();
    }
   return 0;
}
 
void OutPutPlayers(vector<Player*>&j, Team* r, int counter){
    string x= "hi";
    int beg=0;
          
    while (!(x=="q" || x=="Q")){
        
        int u=j.size();
        while (u%10!=0){
            u--;
        }
        if(counter>(u-5) && counter <u)
            counter =u;
            
        for (unsigned int i=beg; i<counter; i++){
            if(i <j.size())
                cout<<"Position "<< i+1<< ": "<< j.at(i)->GetName()<<", Rating: "<< j.at(i)->rating()<<endl;
            }
            
            cout << "Type N for Next Page, P for Previous Page"<< endl;
                     
            cout<< "Type Q to go back to menu"<<endl;
            cin >> x;
            
            
            if (x == "n" || x=="N"){
                if ((counter>=j.size())){
                        
                    cout << endl<<"End of List. Try again." << endl << endl;
                    
                }
                else {
                    counter=5+counter;
                    beg+=5;
             
                    }
                }
                   
            else  if (x == "p" || x== "P"){
                if (counter <=5){
                    cout << endl<<"Beginning of List. Try again."<< endl << endl;
                    }
                else {
                    counter= counter-5;
                    beg-=5;
                    }
                }
            else if (x=="q"|| x=="Q"){
                    
            }
            else{
                cout << endl<< "Invalid input. Try again" << endl<< endl;
            }
                          
    }
    cout << endl<< endl;
}
         
void  outputAllPlayers( vector<Player*>& j,  Team* r){
    cout << endl<< endl;
    int counter =5;
    OutPutPlayers(j,r,counter);
        
}

void outputRoster(Team* r){
    cout << endl << endl;
    cout<<"ROSTER"<<endl;
    r->Display();
    cout<<endl;

}

void menu( Team* r){

    cout<<"MENU"<<endl;
 
    cout<<"a - Add player"<<endl;
    cout<<"r - Remove player"<<endl;
    cout<<"u - Output All Available Players"<<endl;
    cout<<"o - Output roster"<<endl;
    cout<<"q - Back"<<endl;
    cout << "s - Save" << endl;
    cout<<endl;
    cout<<"Choose an option:";
    char choice;
    cin>>choice;
    if(choice == 'a'){
        string p;
        cout << "Which position would you like to add? "<< endl << "Pg Sg Sf Pf C" << endl;
        cin >> p;

        if (p == "Sg" || p == "sg")
               addPlayer(Shoot,r,"shoot");

        else if (p == "Pg" || p == "pg")
               addPlayer(Point,r, "pg");
        else if (p == "C" || p == "c")
               addPlayer(Center,r, "cn");
        else if (p == "Pf" || p == "pf")
               addPlayer(Power,r, "pf");
        else if (p =="Sf" || p == "sf")
               addPlayer(Small,r, "sf");
        else
            cout << "Invalid position" << endl;
            menu(r);
        
    }
    else if (choice =='s'){
        SaveTeam(r);
    }
    else if(choice == 'r'){
           
        removePlayer(r);
        menu(r);
    }
    else if(choice == 'u'){
        string p;
        cout <<"Which position would you like to see the available players for?"<< endl << "Pg Sg Sf Pf C" << endl;
        cin>>p;

        if(p=="Sg" || p == "sg")
            outputAllPlayers(Shoot,r);
        if(p=="Pg" || p == "pg")
            outputAllPlayers(Point,r);
        if(p=="Sf" || p == "sf")
            outputAllPlayers(Small,r);
        if(p=="Pf" || p == "pf")
            outputAllPlayers(Power,r);
        if(p=="C" || p == "c")
            outputAllPlayers(Center,r);
            menu(r);
    }
    else if(choice == 'o'){
        outputRoster(r);
        menu(r);
    }
    else if(choice == 'q'){
        firstmenu();
    }
    else {
        cout << endl << "Invalid Input Try Again" << endl;
        menu(r);
    }
}

void removePlayer(Team* r){
    cout << endl << endl;
    cout<<"ROSTER"<<endl;

    
    r->Display();
    cout << endl<< endl;
         
    if(r->TeamSize() == 0){
        return;
    }
    
    cout<<"Enter a position number to remove"<<endl;
    string y;
    cin>>y;
    if(is_number(y) == false){
        return;
    }
    stringstream iss(y);
    int x;
    iss >> x;
    if (x<=r->TeamSize() && x > 0){
        
        Player* temp = r->RemovePlayer(x);
        if(temp->GetPosition() == "Pg"){
            Point.push_back(temp);
            selectionSort(Point,r,"Pg");
        }
        if(temp->GetPosition() == "Sg"){
            Shoot.push_back(temp);
            selectionSort(Shoot, r, "Sg");
        }
        if(temp->GetPosition() == "Sf"){
            Small.push_back(temp);
            selectionSort(Small, r, "Sf");
        }
        if(temp->GetPosition() == "Pf"){
            Power.push_back(temp);
            selectionSort(Power, r, "Pf");
        }
        if(temp->GetPosition() == "Cn"){
            Center.push_back(temp);
            selectionSort(Center, r, "Cn");
        }
    }
    
    else {
        cout << endl << "Invalid Input Try Again" << endl;
        removePlayer(r);
    }
}


void addPlayer(vector<Player*>& j, Team* r, string pos){
   
    if (r->TeamSize()>=5){
        cout << "max players"<< endl;
       // menu(r);
    }
    
    
    else{

            cout << endl<< endl;
            int counter =5;
            string x= "hi";
            int beg = 0;
            while (!is_number(x)){
        
                
                if(counter > j.size())
                    counter = j.size();
                
                int u=j.size();
                while (u%5!=0){
                    u--;
                }
                if(counter>(u-5) && counter <u)
                    counter =u;
    
           
                for (int i=beg; i<counter; i++){
        
                    cout<<"Position "<< i+1<< ": "<< j.at(i)->GetName()<<", Rating: "<< j.at(i)->rating()<<endl;
                }

                
                cout << "Type N for Next Page, P for Previous Page"<< endl;
                         
                cout<< "Enter Player Position number"<<endl;
                cin >> x;
                
                
                if (x == "n" || x=="N"){
                    if ((counter>=j.size())){
                    
                        cout << endl<<"End of List. Try again." << endl << endl;
                
            }
            else {
                counter=5+counter;
                beg+=5;
      
            }
        }
               
            else  if (x == "p" || x== "P"){
                if (counter <=5){
                    cout << endl<<"Beginning of List. Try again."<< endl << endl;
                }
                else {
                    counter= counter-5;
                    beg-=5;
                }
            }
            else if (is_number(x)){
                int u = stoi(x);
                if (counter<u || ((counter-5)>=u)){
                    cout << endl<< "Invalid input. Try again" << endl<< endl;
                    x = "hi";
                    
                }
            }
            else{
                cout << endl<< "Invalid input. Try again" << endl<< endl;
            }
                    
    }

        int b = stoi(x);
        
        if(b<=j.size()){
            for (int i=0; i <j.size(); i++){
                if(i+1==b){
                    r->AddPlayer(j.at(i));
                    j.erase(j.begin()+i);
        }
    }
   selectionSort(j,r,pos);
}
        else {
            cout << endl << "Invalid Input. Try Again" << endl;
            addPlayer(j,r, pos);

        }
    }
}


void Versus(){

        Team *First;
        Team* Second;
        string tempName;
        string line = "________________________________________________________________________";
        if(TeamList.size() < 2){
            cout<< "Not enough available teams, please create a team" << endl;
            firstmenu();
        }
        else{
            cout << "Available Teams: " << endl;
            for(int i = 0; i < TeamList.size(); ++i){
                cout << TeamList.at(i)->GetName() << endl;
            }
            cout << "Enter First Team's name: " << endl;
            cin.ignore();
            getline(cin, tempName);
            bool check = false;
            for(int j = 0; j < TeamList.size(); ++j){
                if(tempName == TeamList.at(j)->GetName()){
                    First = TeamList.at(j);
                    check = true;
                }
            }
            if(check == false){
                cout << "Not an available team" << endl;
                Versus();
            }
            check = false;
            
            while (check==false){
                
                cout << "Available Teams: " << endl;
                for(int i = 0; i < TeamList.size(); ++i){
                    cout << TeamList.at(i)->GetName() << endl;
                }
                cout << "Enter Second Team's name: " << endl;
            
                getline(cin, tempName);
            
                for(int j = 0; j < TeamList.size(); ++j){
                    if(tempName == TeamList.at(j)->GetName()){
                        Second = TeamList.at(j);
                        check = true;
                    }
                }
                if(check == false){
                    cout << "Not an available team" << endl;
                
                    }
                }
    
                vector<int> FirstTeam;
                First->FaceOff(FirstTeam);
                vector<int> SecondTeam;
                Second->FaceOff(SecondTeam);
            

                if(FirstTeam.size()==SecondTeam.size()){
                int u;
                if (FirstTeam.size()>= SecondTeam.size()){
                    u= SecondTeam.size();
                }
                else {
                    u= FirstTeam.size();
                }
                int down = 33+ First->GetName().size() ;
                int FrstScore=0;
                int ScndScore=0;

     //           cout << endl;

                cout << endl << endl << line  << endl <<  "Team " << First->GetName() <<"              vs               " << "Team " << Second->GetName() << endl<< endl;

                for (int i=0 ; i<u;i++){
                    FrstScore+=FirstTeam.at(i);
                    ScndScore+=SecondTeam.at(i);


                    for (int j = 0; j<First->GetPlayerName(i).size(); j++){
                        cout << First->GetPlayerName(i).at(j);
                        down--;
                    }
                    cout << " " << FirstTeam.at(i);
                    while(down>0){
                        cout << " ";
                        down--;
                    }
                    if (down==0){
                        down =33+ First->GetName().size();
                    }
                    cout << Second->GetPlayerName(i) << " " << SecondTeam.at(i) << endl << endl;
            }

            cout << endl<< endl<< endl;
            cout << "          Total" << endl;
            cout << FrstScore << "                   " << ScndScore<< endl;
            if (FrstScore> ScndScore){
                cout <<endl<< "   Team " << First->GetName() << " wins"<< endl;
                cout << endl << endl;
                firstmenu();
            }
            else if (FrstScore< ScndScore){
                cout << endl<<"   Team " << Second->GetName() << " wins"<< endl;
                cout << endl << endl;
                firstmenu();
            }
            
            
            else{
                cout << "Tie" << endl;
                cout<<line  << endl << endl;
                firstmenu();
            }
        }
    
    
        else {
            if (FirstTeam.size()>SecondTeam.size()){
                int p = FirstTeam.size()-SecondTeam.size();
                cout << "Team " << First->GetName() << " has " << p << " more players than Team " << Second->GetName()<<". Please add " << p <<" more players to Team " << Second->GetName()<< " to use face-off." << endl;
                cout << endl;
                firstmenu();
    
            }
            else{
                int p = SecondTeam.size()-FirstTeam.size();
                cout << "Team " << Second->GetName() << " has " << p << " more players than Team " << First->GetName()<<". Please add " << p <<" more players to Team " << First->GetName()<< " to use face-off." << endl;
                cout << endl;
                firstmenu();

            }
        }
    }
}


bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}



void sort(){
    
    int min_idx;

    for (int i = 0; i < Point.size()-1; i++)
    {

        min_idx = i;
        for ( int b = i+1; b < Point.size(); b++){
            if (Point.at(b)->rating() > Point.at(min_idx)->rating()){
                min_idx = b;
            }
        }

        Player* u= Point.at(i);
        Point.at(i) = Point.at(min_idx);
        Point.at(min_idx)= u;

    }
    for (int i = 0; i < Shoot.size()-1; i++)
    {

        min_idx = i;
        for ( int b = i+1; b < Shoot.size(); b++){
            if (Shoot.at(b)->rating() > Shoot.at(min_idx)->rating()){
                min_idx = b;
            }
        }

        Player* u= Shoot.at(i);
        Shoot.at(i) =Shoot.at(min_idx);
        Shoot.at(min_idx)= u;

        }
        for (int i = 0; i < Small.size()-1; i++)
        {

            min_idx = i;
            for ( int b = i+1; b < Small.size(); b++){
                if (Small.at(b)->rating() > Small.at(min_idx)->rating()){
                    min_idx = b;
                }
            }

        Player* u= Small.at(i);
        Small.at(i) = Small.at(min_idx);
        Small.at(min_idx)= u;

        }
        for (int i = 0; i < Power.size()-1; i++)
        {

        min_idx = i;
        for ( int b = i+1; b < Power.size(); b++){
            if (Power.at(b)->rating() > Power.at(min_idx)->rating()){
                min_idx = b;
            }
        }
        Player* u= Power.at(i);
        Power.at(i) = Power.at(min_idx);
        Power.at(min_idx)= u;
        }
        for (int i = 0; i < Center.size()-1; i++)
        {
            min_idx = i;
            for ( int b = i+1; b < Center.size(); b++){
                if (Center.at(b)->rating() > Center.at(min_idx)->rating()){
                    min_idx = b;
                }
            }
            Player* u= Center.at(i);
            Center.at(i) = Center.at(min_idx);
            Center.at(min_idx)= u;

        }
}



void SaveTeam(Team* r){
    std::ofstream ofs;
    ofs.open("LastGame.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    ofs.open("LastGame.txt");

    for (int i=0;i<TeamList.size();i++){

        ofs << TeamList.at(i)->GetName() << endl;

        int six = 5;

        for (int j=0; j<TeamList.at(i)->TeamSize();j++){

            ofs << TeamList.at(i)->GetPlayerName(j)<< endl;
            six--;
        }
        while(six>0){
            ofs << "Empty" <<endl;
            six--;
        }
    }
    ofs.close();
    cout<<endl;
    menu(r);

}


void Resume(){
    ifstream inFile;
    inFile.open("LastGame.txt");

    string u = "hi";
    int x=0;
    int counter=0;
    while(getline(inFile,u)){
        if (x==0){
            Team* temp = new Team(u);
            TeamList.push_back(temp);

        }

        else {

            for (int i=0; i<Point.size();i++){
        
                if (u==Point.at(i)->GetName()){
                    TeamList.at(counter)->AddPlayer(Point.at(i));
                    Point.erase(Point.begin()+i);
                    }
                }

            for (int i=0; i<Center.size();i++){
                if (u==Center.at(i)->GetName()){
                    TeamList.at(counter)->AddPlayer(Center.at(i));
                    Center.erase(Center.begin()+i);
                }
            }
            for (int i=0; i<Shoot.size();i++){
                if (u==Shoot.at(i)->GetName()){
                    TeamList.at(counter)->AddPlayer(Shoot.at(i));
                    Shoot.erase(Shoot.begin()+i);

                }
            }

            for (int i=0; i<Small.size();i++){
                if (u==Small.at(i)->GetName()){
                    TeamList.at(counter)->AddPlayer(Small.at(i));
                    Small.erase(Small.begin()+i);

                }
            }

            for (int i=0; i<Power.size();i++){
                if (u==Power.at(i)->GetName()){
                    TeamList.at(counter)->AddPlayer(Power.at(i));
                    Power.erase(Power.begin()+i);
   
                }
            }
        }
        
        x++;

        if (x==6){
            x=0;
            counter++;
        }
    }
    inFile.close();
    firstmenu();
}


void DeleteTeam(int j){



        TeamList.erase(TeamList.begin()+(j-1));
	//firstmenu();
}

void CreateRandomTeam(){
	int j = TeamList.size()+1;	
	string TeamName ="Team " +  to_string(j);
	Team* NewTeam = new Team(TeamName);
	TeamList.push_back(NewTeam);
	
	int RandomPlayerPos = rand() % Point.size();
	TeamList.at(TeamList.size()-1)->AddPlayer(Point.at(RandomPlayerPos));
     Point.erase(Point.begin()+RandomPlayerPos);
	 RandomPlayerPos = rand() % Shoot.size();
    TeamList.at(TeamList.size()-1)->AddPlayer(Shoot.at(RandomPlayerPos));
    Shoot.erase(Shoot.begin()+RandomPlayerPos);
        RandomPlayerPos = rand() % Small.size();
        TeamList.at(TeamList.size()-1)->AddPlayer(Small.at(RandomPlayerPos));
         Small.erase(Small.begin()+RandomPlayerPos);
         RandomPlayerPos = rand() % Power.size();
        TeamList.at(TeamList.size()-1)->AddPlayer(Power.at(RandomPlayerPos));
         Power.erase(Power.begin()+RandomPlayerPos);
        RandomPlayerPos = rand() % Center.size();
        TeamList.at(TeamList.size()-1)->AddPlayer(Center.at(RandomPlayerPos));
     Center.erase(Center.begin()+RandomPlayerPos);
	
	return;
	
	
}
int total(vector<int>);

int total(vector<int> TeamScore){
	int total=0;
	for (int i=0; i < TeamScore.size();i++){
		total+=TeamScore.at(i);
     //   cout << TeamScore.at(i) << " ";
	}
   // cout << endl;
	return total;
}




void Print(string, int);
void Print(string x, int p){
    if (p==1){
        int Total = 22;

        Total = Total - x.size();
        cout << x;

        while(Total!=0){
            cout << " ";
            Total--;

        }
        cout << "|                                         Winner!                                                      | ";
    }
    else {
    int Total = 22;

    Total = Total - x.size();
    cout << x;

    while(Total!=0){
        cout << " ";
        Total--;

    }
    cout << "|";
    Total = 77;
    while(Total != 0){
        
        cout << " ";
        Total--;
    }
    cout << "| ";
    }
    
        
}
void Print(string);
void Print(string x){

	int Total = 22;

	Total = Total - x.size(); 
	cout << x;

	while(Total!=0){
		cout << " ";
		Total--;

	}
	cout << "|";
	Total = 77+25;
	while(Total != 0){
		
		cout << " ";
		Total--;
	}
	cout << "| ";
		
}




void Tourny(){
    cout << endl << endl;
    
    
    vector<Team*> TeamsList;
	int TeamCount = 0;

    for(int i=0;i<TeamList.size();i++){
        
        if(TeamList.at(i)->TeamSize()==5){
            //TeamsList.push_back(TeamList.at(i));
            TeamCount++;
        }
    }
   
    int TeamRemaining = 8-TeamCount;
    if(TeamCount>8){
          int count=8;
          while(count!=0){
              cout << "Select which teams you would like to choose:" << endl;
              int choice;
              cin >> choice;
          
              for(int i=0; i<TeamList.size();i++){
                  cout << i+1 << ". " << TeamList.at(i)->GetName() << endl;
              }
              if (TeamList.at(choice-1)->TeamSize()==5){
                  TeamsList.push_back(TeamList.at(choice-1));
                  count--;
              }
              else {
                  cout << "Incorrect input. Try again." << endl;
              }
          
          }
    }
    
   

    else {
        while(TeamCount!=8){
            CreateRandomTeam();
            TeamCount++;
        }
    
    
        for(int i=0;i<TeamList.size();i++){
                  if(TeamList.at(i)->TeamSize()==5){
                      TeamsList.push_back(TeamList.at(i));
            //TeamCount++;
                  }
        }
        for(int i=TeamRemaining; i>0;i--){
            int pos = TeamList.size();
            DeleteTeam(pos);
        }
    }
    std::random_shuffle(TeamsList.begin(), TeamsList.end());

	vector<int> score;
        
        vector<int>Team1;
        vector<int>Team2;
        vector<int> Team3;
        vector <int> Team4;
        vector<int>Team5;
        vector<int>Team6;
        vector<int> Team7;
        vector <int> Team8;
        vector <int> totals;
        TeamsList.at(0)->FaceOff(Team1);
        TeamsList.at(1)->FaceOff(Team2);

        if (total(Team1) > total(Team2)){
            totals.push_back(0);
        }
        else{
            totals.push_back(1);
        }
        
        score.push_back(total(Team1));
        score.push_back(total(Team2));
        
        
        TeamsList.at(4)->FaceOff(Team3);
        TeamsList.at(5)->FaceOff(Team4);

            if (total(Team3) > total(Team4)){
                    totals.push_back(4);
            }
            else{
                    totals.push_back(5);
            }
        
        score.push_back(total(Team3));
        score.push_back(total(Team4));
        
        TeamsList.at(2)->FaceOff(Team5);
            TeamsList.at(3)->FaceOff(Team6);
            TeamsList.at(6)->FaceOff(Team7);
            TeamsList.at(7)->FaceOff(Team8);
            if (total(Team5) > total(Team6)){
                    totals.push_back(2);
            }
            else{
                    totals.push_back(3);
            }

           if (total(Team7) > total(Team8)){
                    totals.push_back(6);
            }
            else{
                    totals.push_back(7);
            }
        
        score.push_back(total(Team5));
        score.push_back(total(Team6));
        score.push_back(total(Team7));
        score.push_back(total(Team8));
        
        
        
        TeamsList.at(totals.at(0))->FaceOff(Team1);
         TeamsList.at(totals.at(2))->FaceOff(Team2);

            if (total(Team1) > total(Team2)){
                    totals.push_back(totals.at(0));
            }
            else{
                    totals.push_back(totals.at(2));
            }
        score.push_back(total(Team1));
         score.push_back(total(Team2));
        
            TeamsList.at(totals.at(1))->FaceOff(Team1);
             TeamsList.at(totals.at(3))->FaceOff(Team2);

            if (total(Team1) > total(Team2)){
                    totals.push_back(totals.at(1));
            }
            else{
                    totals.push_back(totals.at(3));
            }
        score.push_back(total(Team1));
         score.push_back(total(Team2));

        vector<int> one;
        vector<int> two;
        
         TeamsList.at(totals.at(4))->FaceOff(one);
             TeamsList.at(totals.at(5))->FaceOff(two);

            if (total(one) > total(two)){
                    totals.push_back(totals.at(4));
            }
            else{
                    totals.push_back(totals.at(5));
            }
        score.push_back(total(one));
         score.push_back(total(two));

   
        


        
        Print(TeamsList.at(0)->GetPlayerName(0) );
        cout  << TeamsList.at(4)->GetPlayerName(0) << endl;
        Print( TeamsList.at(0)->GetPlayerName(1));
        cout  << TeamsList.at(4)->GetPlayerName(1) << endl;
        
        int temp = 22 - TeamsList.at(0)->GetPlayerName(2).size();
        cout << TeamsList.at(0)->GetPlayerName(2);
        while(temp!=0){
            cout << " ";
            temp--;
        }
        cout << "| " << TeamsList.at(0)->GetName() << " - " << score.at(0);
    
     if (score.at(0) >99 && score.at(2)>99){
         temp = 88 - TeamsList.at(0)->GetName().size() - TeamsList.at(4)->GetName().size();
     }
    else  if (score.at(0) >99 || score.at(2)>99){
           temp = 89 - TeamsList.at(0)->GetName().size() - TeamsList.at(4)->GetName().size();
       }
    else {
            temp = 90 - TeamsList.at(0)->GetName().size() - TeamsList.at(4)->GetName().size();
    }
    
    
        while(temp!=0){
            cout << " ";
            temp--;
        }
        
        cout << score.at(2) << " - " << TeamsList.at(4)->GetName() << " | " << TeamsList.at(4)->GetPlayerName(2) << endl;
        
        //cout << TeamList.at(0)->GetPlayerName(2) <<" | " << TeamList.at(0)->GetName() << "-" << total(Team1) <<  "                                                                             "<< total(Team3) << " - " << TeamList.at(4)->GetName() << " | " << TeamList.at(4)->GetPlayerName(2) << endl;
        Print(TeamsList.at(0)->GetPlayerName(3));

        cout << TeamsList.at(4)->GetPlayerName(3) << endl;

        Print(TeamsList.at(0)->GetPlayerName(4));

     cout << TeamsList.at(4)->GetPlayerName(4) << endl;

        temp = 35;
        while(temp!=0){
            cout << " ";
            temp--;
        }
        temp = 67 - TeamsList.at(totals.at(0))->GetName().size() - TeamsList.at(totals.at(1))->GetName().size();
        cout  << TeamsList.at(totals.at(0))->GetName() <<" - " << score.at(8);
        while(temp!=0){
            cout << " ";
            temp--;
        }
        
        cout << score.at(10) << " - " <<  TeamsList.at(totals.at(1))->GetName()<< endl;
          
        Print( TeamsList.at(1)->GetPlayerName(0));

        cout << TeamsList.at(5)->GetPlayerName(0) << endl;

        Print( TeamsList.at(1)->GetPlayerName(1));

    cout<< TeamsList.at(5)->GetPlayerName(1) << endl;

        temp = 22 - TeamsList.at(1)->GetPlayerName(2).size();
           cout << TeamsList.at(1)->GetPlayerName(2);
           while(temp!=0){
               cout << " ";
               temp--;
           }
           cout << "| " << TeamsList.at(1)->GetName() << " - " << score.at(1);
    if (score.at(1) >99 && score.at(3)>99){
        temp = 88 - TeamsList.at(1)->GetName().size() - TeamsList.at(5)->GetName().size();
    }
   else  if (score.at(1) >99 || score.at(3)>99){
          temp = 89 - TeamsList.at(1)->GetName().size() - TeamsList.at(5)->GetName().size();
      }
   else {
           temp = 90 - TeamsList.at(1)->GetName().size() - TeamsList.at(5)->GetName().size();
   }
           while(temp!=0){
               cout << " ";
               temp--;
           }
           
           cout << score.at(3) << " - " << TeamsList.at(5)->GetName() << " | " << TeamsList.at(4)->GetPlayerName(2) << endl;
     

            Print(TeamsList.at(1)->GetPlayerName(3));

         cout << TeamsList.at(5)->GetPlayerName(3) << endl;
            
        Print(TeamsList.at(1)->GetPlayerName(4),1);

         cout  << TeamsList.at(5)->GetPlayerName(4) << endl;
        
        cout << "                                              " << TeamsList.at(totals.at(4))->GetName() << " - " << score.at(12)<< "             " << TeamsList.at(totals.at(6))->GetName() << "                " << score.at(13) << " - " <<TeamsList.at(totals.at(5))->GetName() << endl;
        



        Print(TeamsList.at(2)->GetPlayerName(0));

     cout << TeamsList.at(6)->GetPlayerName(0) << endl;

            Print(TeamsList.at(2)->GetPlayerName(1));

     cout << TeamsList.at(6)->GetPlayerName(1) << endl;

         temp = 22 - TeamsList.at(2)->GetPlayerName(2).size();
           cout << TeamsList.at(2)->GetPlayerName(2);
           while(temp!=0){
               cout << " ";
               temp--;
           }
           cout << "| " << TeamsList.at(2)->GetName() << " - " << score.at(4);
        if (score.at(4) >99 && score.at(6)>99){
            temp = 88 - TeamsList.at(2)->GetName().size() - TeamsList.at(6)->GetName().size();
        }
        else  if (score.at(4) >99 || score.at(6)>99){
           temp = 89 - TeamsList.at(2)->GetName().size() - TeamsList.at(6)->GetName().size();
        }
        else {
            temp = 90 - TeamsList.at(2)->GetName().size() - TeamsList.at(6)->GetName().size();
        }
    
           while(temp!=0){
               cout << " ";
               temp--;
           }
           
           cout << score.at(6) << " - " << TeamsList.at(6)->GetName() << " | " << TeamsList.at(6)->GetPlayerName(2) << endl;
        
        
        
        Print(TeamsList.at(2)->GetPlayerName(3));

     cout<< TeamsList.at(6)->GetPlayerName(3) << endl;

            Print( TeamsList.at(2)->GetPlayerName(4));

    cout  << TeamsList.at(6)->GetPlayerName(4) << endl;
        
        
        temp = 35;
        while(temp!=0){
            cout << " ";
            temp--;
        }
        temp = 67 - TeamsList.at(totals.at(2))->GetName().size() - TeamsList.at(totals.at(3))->GetName().size();
        cout  << TeamsList.at(totals.at(2))->GetName() <<" - " << score.at(9);
        while(temp!=0){
            cout << " ";
            temp--;
        }
        
        cout << score.at(11) << " - " <<  TeamsList.at(totals.at(3))->GetName()<< endl;
        
        

      //      cout << "                    " << TeamList.at(totals.at(2))->GetName() << " - " << score.at(9) <<  "                                     " << score.at(11) << " - "<< TeamList.at(totals.at(3))->GetName()<< endl;

        Print(TeamsList.at(3)->GetPlayerName(0));
       cout << TeamsList.at(7)->GetPlayerName(0) << endl;
        Print(TeamsList.at(3)->GetPlayerName(1));
       cout << TeamsList.at(7)->GetPlayerName(1) << endl;
        
        temp = 22 - TeamsList.at(3)->GetPlayerName(2).size();
           cout << TeamsList.at(3)->GetPlayerName(2);
           while(temp!=0){
               cout << " ";
               temp--;
           }
    
           cout << "| " << TeamsList.at(3)->GetName() << " - " << score.at(5);
    
     if (score.at(5) >99 && score.at(7)>99){
         temp = 88 - TeamsList.at(3)->GetName().size() - TeamsList.at(7)->GetName().size();
     }
    else  if (score.at(5) >99 || score.at(7)>99){
           temp = 89 - TeamsList.at(3)->GetName().size() - TeamsList.at(7)->GetName().size();
       }
    else {
            temp = 90 - TeamsList.at(3)->GetName().size() - TeamsList.at(7)->GetName().size();
    }
           
           while(temp!=0){
               cout << " ";
               temp--;
           }
           
           cout << score.at(7) << " - " << TeamsList.at(7)->GetName() << " | " << TeamsList.at(4)->GetPlayerName(2) << endl;
        //    cout << TeamList.at(3)->GetPlayerName(2) <<" | " << TeamList.at(1)->GetName() << "-" << total(Team1) <<  "                                                                             "<< total(Team3) << "-" << TeamList.at(7)->GetName() << " | " << TeamList.at(7)->GetPlayerName(2) << endl;

            Print( TeamsList.at(3)->GetPlayerName(3));
     cout << TeamsList.at(7)->GetPlayerName(3) << endl;
            Print(TeamsList.at(3)->GetPlayerName(4));
     cout  << TeamsList.at(7)->GetPlayerName(4) << endl;
         

      //  while(TeamRemaining!=0){
        //    TeamList.erase(TeamList.size()-1);
        //}

        //firstmenu();
    cout << endl;
    //    return;
    }




void tourny2(){
    cout << endl << endl;
    vector<Team*> TeamsList;
    int TeamCount = 0;
    
    
    for(int i=0;i<TeamList.size();i++){
         
         if(TeamList.at(i)->TeamSize()==5){
             //TeamsList.push_back(TeamList.at(i));
             TeamCount++;
         }
     }
    
     int TeamRemaining = 4-TeamCount;
     if(TeamCount>4){
           int count=4;
           while(count!=0){
            
           
               for(int i=0; i<TeamList.size();i++){
                   cout << i+1 << ". " << TeamList.at(i)->GetName() << endl;
               }
               cout << "Select which teams you would like to choose:" << endl;
                int choice;
                cin >> choice;
               if (TeamList.at(choice-1)->TeamSize()==5){
                   TeamsList.push_back(TeamList.at(choice-1));
                   count--;
               }
               else {
                   cout << "Incorrect input. Try again." << endl;
               }
           
           }
     }
     
    
     
   
     else {
         while(TeamCount!=4){
             CreateRandomTeam();
             TeamCount++;
         }
         
     
         for(int i=0;i<TeamList.size();i++){
                   if(TeamList.at(i)->TeamSize()==5){
                       TeamsList.push_back(TeamList.at(i));
             //TeamCount++;
                   }
         }
         
         for(int i=TeamRemaining; i>0;i--){
             int pos = TeamList.size();
             DeleteTeam(pos);
         }
     }
    std::random_shuffle(TeamsList.begin(), TeamsList.end());
    vector<int> score;
    vector<int> pos;
    vector<int> Team1;
    vector<int> Team2;
                 
                 TeamsList.at(0)->FaceOff(Team1);
                 TeamsList.at(1)->FaceOff(Team2);
                 
                    if (total(Team1) > total(Team2)){
                        pos.push_back(0);
                    }
                    else{
                        pos.push_back(1);
                    }
                    
                    score.push_back(total(Team1));
                    score.push_back(total(Team2));
                    
                    
                    TeamsList.at(2)->FaceOff(Team1);
                    TeamsList.at(3)->FaceOff(Team2);

                        if (total(Team1) > total(Team2)){
                                pos.push_back(2);
                        }
                        else{
                                pos.push_back(3);
                        }
                    
                    score.push_back(total(Team1));
                    score.push_back(total(Team2));
    
                    TeamsList.at(pos.at(0))->FaceOff(Team1);
                    TeamsList.at(pos.at(1))->FaceOff(Team2);

                        if (total(Team1) > total(Team2)){
                                pos.push_back(pos.at(0));
                        }
                        else{
                                pos.push_back(pos.at(0));
                        }
                    
                    score.push_back(total(Team1));
                    score.push_back(total(Team2));
                 
                 
                 Print(TeamsList.at(0)->GetPlayerName(0),0 );
                    cout  << TeamsList.at(2)->GetPlayerName(0) << endl;
                    Print( TeamsList.at(0)->GetPlayerName(1),0);
                    cout  << TeamsList.at(2)->GetPlayerName(1) << endl;
                    
                    int temp = 22 - TeamsList.at(0)->GetPlayerName(2).size();
                    cout << TeamsList.at(0)->GetPlayerName(2);
                    while(temp!=0){
                        cout << " ";
                        temp--;
                    }
                    cout << "| " << TeamsList.at(0)->GetName() << " - " << score.at(0);
                    if (score.at(0)>99 && score.at(2)>99){
                        temp = 63- TeamsList.at(0)->GetName().size() - TeamsList.at(2)->GetName().size();
                    }
                    else if (score.at(0)>99 || score.at(2)>99){
                        temp = 64-  TeamsList.at(0)->GetName().size() - TeamsList.at(2)->GetName().size();
                    }
                    else {
                    temp = 65 - TeamsList.at(0)->GetName().size() - TeamsList.at(2)->GetName().size();
                    }
                    while(temp!=0){
                        cout << " ";
                        temp--;
                    }
                    
                    cout << score.at(2) << " - " << TeamsList.at(2)->GetName() << " | " << TeamsList.at(2)->GetPlayerName(2) << endl;
                    
                    //cout << TeamList.at(0)->GetPlayerName(2) <<" | " << TeamList.at(0)->GetName() << "-" << total(Team1) <<  "                                                                             "<< total(Team3) << " - " << TeamList.at(4)->GetName() << " | " << TeamList.at(4)->GetPlayerName(2) << endl;
                    Print(TeamsList.at(0)->GetPlayerName(3),0);

                    cout << TeamsList.at(2)->GetPlayerName(3) << endl;

                    Print(TeamsList.at(0)->GetPlayerName(4),0);

                 cout << TeamsList.at(2)->GetPlayerName(4) << endl;
                 
                 
                 
                 cout << "                                        " << TeamsList.at(pos.at(0))->GetName() << " - " << score.at(4)<< "             " << TeamsList.at(pos.at(2))->GetName() << "              " << score.at(5) << " - " <<TeamsList.at(pos.at(1))->GetName() << endl;
         
         
                        Print(TeamsList.at(1)->GetPlayerName(0),0 );
                            cout  << TeamsList.at(3)->GetPlayerName(0) << endl;
                            Print( TeamsList.at(1)->GetPlayerName(1),0);
                            cout  << TeamsList.at(3)->GetPlayerName(1) << endl;
                            
                            temp = 22 - TeamsList.at(1)->GetPlayerName(2).size();
                            cout << TeamsList.at(1)->GetPlayerName(2);
                            while(temp!=0){
                                cout << " ";
                                temp--;
                            }
                            cout << "| " << TeamsList.at(1)->GetName() << " - " << score.at(1);
                            if (score.at(1)>99 && score.at(3)>99){
                                temp = 63- - TeamsList.at(1)->GetName().size() - TeamsList.at(3)->GetName().size();
                            }
                            else if (score.at(1)>99 || score.at(3)>99){
                                temp = 64- - TeamsList.at(1)->GetName().size() - TeamsList.at(3)->GetName().size();
                            }
                            else {
                            temp = 65 - TeamsList.at(1)->GetName().size() - TeamsList.at(3)->GetName().size();
                            }
    
                            while(temp!=0){
                                cout << " ";
                                temp--;
                            }
                            
                            cout << score.at(3) << " - " << TeamsList.at(3)->GetName() << " | " << TeamsList.at(3)->GetPlayerName(2) << endl;
                            
                            //cout << TeamList.at(0)->GetPlayerName(2) <<" | " << TeamList.at(0)->GetName() << "-" << total(Team1) <<  "                                                                             "<< total(Team3) << " - " << TeamList.at(4)->GetName() << " | " << TeamList.at(4)->GetPlayerName(2) << endl;
                            Print(TeamsList.at(1)->GetPlayerName(3),0);

                            cout << TeamsList.at(3)->GetPlayerName(3) << endl;

                            Print(TeamsList.at(1)->GetPlayerName(4),0);

                         cout << TeamsList.at(3)->GetPlayerName(4) << endl << endl;
    
}



