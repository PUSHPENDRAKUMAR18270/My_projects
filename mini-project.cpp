#include<iostream>
#include<string.h>
#include<stdlib.h>
#include <ctime>
#include<iomanip>
#include <ios>
#define ll long long int

using namespace std;

int flag=0;
int overs;                                                      /* DEFINING NO OF OVERS OF MATCH */
int target;                                                          /* TARGET GLOBAL VARIABLE  */
enum teamorder{first=1,second};                                         /* TEAM BATTING FIRST ORDER ENUM */
teamorder ord=first;
class team;
class match;                                                            /* MATCH CLASS */

/**************
Players Stats
**************/
struct player{
        float runs_scored;
        int balls_faced;
        int fours_scored;
        int sixes_scored;
        int wickets_taken;
        float strikerate;
};
/**************
Team Stats
**************/
struct scorecard{
        int runs;
        int overs;
        int balls;
        int fours;
        int sixes;
        int wickets;
};
/**************************
Team Data Members & methods
**************************/
class team{
        player players[12];
        char team_nm[30];
        scorecard team_scorecard;
        public:
        team(){	team_scorecard={0,0,0,0,0}; 
		        for(int i=0;i<12;i++){                                         /* INITIALISING PLAYERS STRUCTURE TO ZERO */
		            players[i].runs_scored=0;
		            players[i].balls_faced=0;
		            players[i].fours_scored=0;
		            players[i].sixes_scored=0;
		            players[i].wickets_taken=0;
		            players[i].strikerate=0;
		       	}
    	}
    void generate_player_score(player &p,int counter);
    void generate_team_scorecard();
    friend void playmatch(team *inn,match *m,int chase,int diff);
    //friend bool chech_win(int runs,int wickets);
    friend void display_the_match_winner(team inn1,team inn2);
};
/****************
Players Scorecard
****************/
void team::generate_player_score(player &p,int counter){
        cout<<setw(20)<<"PLAYER "<<counter<<setw(2)<<":"<<setw(20)<<p.runs_scored<<setw(3)<<" ("<<setprecision(3)<<p. balls_faced;
		cout<<") "<<setw(4)<<"(4's/6's: "<<p.fours_scored<<" / "<<p.sixes_scored<<" )"<<setw(4)<<setprecision(4)<<"  S.rate : "<<p.strikerate<<endl;
}
/**************
Team Scorecard
**************/
void team::generate_team_scorecard(){
		cout<<"\t\tScore   : "<<team_scorecard.runs<<" / "<<team_scorecard.wickets<<"\t\tOvers    : "<<team_scorecard.overs<<"."<<team_scorecard.balls%6<<" / "<<overs<<endl;
		cout<<"\t\t4's/6's : "<<team_scorecard.fours<<" / "<<team_scorecard.sixes<<"\t\tRun-rate : "<<setprecision(4)<<(float)team_scorecard.runs/team_scorecard.overs<<endl;
        cout<<"\t*******************************************************************\n"<<endl;

}
/***************************
Match Data Members & methods
***************************/
class match:public team{
        int currentplayer1,currentplayer2;
        int counter;
       
        public:
        match(){  currentplayer1=1; currentplayer2=2; counter=2;}
        friend void playmatch(team *inn,match *m,int chase,int diff);
       // friend bool chech_win(int runs,int wickets);
        friend void display_the_match_winner(team inn1,team inn2);
};
/********
PlAYMATCH
*********/
void playmatch(team *inn,match *m,int chase,int diff){
 system("pause >nul");
        int exchange_turns=0;
        int allout=0,flag1=0,flag3=0;
        for(int j=0;j<overs;j++){                                             //INNINGS STARTED
                int r,w;
                //if(inn.team_scorecard.wickets==10) break;                    //All OUT
                /**************
                OVER STARTED
                **************/
                for(int i=0;i<6;i++){
                        r=rand()%7;                                                                   //r=runs scored on each ball
                        
						if(diff==1){
							w=rand()%20;
							r=(r==5||r==3||w==5||w==6||w==8||w==9||w==12||w==16||w==18)?0:r;              //r=0 when r=5 occurs
	                    	if(inn->team_scorecard.wickets>5) r=(r==5||r==3||w==6||w==8||w==9)?0:r;    //r=0 when tailenders bat & score r={3,5} || w={5,6,8,9}
                    	}
                    	else if(diff==2){
                    		 w=rand()%15;
							r=(r==5||r==3||w==5||w==6||w==8||w==9||w==11||w==14||w==0)?0:r;              //r=0 when r=5 occurs
	                    	if(inn->team_scorecard.wickets>5 ) r=(r==5||r==3||w==6||w==8||w==9)?0:r;   //r=0 when tailenders bat & score r={3,5} || w={5,6,8,9}
                    	}
                    	else{
                    		w=rand()%10;
							r=(r==3||r==5||w==6||w==7||w==8||w==9)?0:r;  							      //r=0 when r=5 occurs
	                    	if(inn->team_scorecard.wickets>5) r=(r==5||r==3||w==5||w==6||w==8||w==9)?0:r; //r=0 when tailenders bat & score r={3,5}  w={5,6,8,9}
                    	}
						
						if(r==6 && w==5||w==6)   r=0;
						/**************
                        WICKET FALLEN
                        **************/
                        if(w==7){                                                     //generate wicket at w==7
                                if(exchange_turns==0){                                         //batsman 1 out on random ball
                                    inn->players[ m->currentplayer1 ].strikerate = (float)( inn->players[ m->currentplayer1 ].runs_scored / inn->players[ m->currentplayer1 ].balls_faced ) *100;
									inn->players[ m->currentplayer1 ].balls_faced++;  //players ball faced incremented
                                    inn->generate_player_score( inn->players[ m->currentplayer1 ] ,m->currentplayer1 ); //print score of batsman out
                                    m->currentplayer1 = ++m->counter;                 //increment current batsman
                                }
                                else {                                               //batsman 2 out on random ball
									inn->players[ m->currentplayer1 ].strikerate = (float)( inn->players[ m->currentplayer1 ].runs_scored / inn->players[ m->currentplayer1 ].balls_faced ) *100;
									inn->players[m->currentplayer2].balls_faced++;  //players ball faced incremented
									inn->generate_player_score( inn->players[ m->currentplayer2 ] , m->currentplayer2 );  //print score of batsman out
									m->currentplayer2 = ++m->counter;                 //increment current batsman
                                }
                                inn->team_scorecard.wickets++;                        //increment wickets of team
                                inn->team_scorecard.balls++;
                                
                                if(inn->team_scorecard.wickets>9){ allout=1;  break; }
                                
                                continue;
                        }
                        //count++;

                        /******************
                        RUNNING THE INNINGS
                        *******************/
                        if( exchange_turns==0 ){                                 //First player plays
                        
                                inn->players[ m->currentplayer1 ].runs_scored += r;//run of individual ball added to players account
                                inn->players[ m->currentplayer1 ].balls_faced++;   //run of individual ball added to players account
                                inn->team_scorecard.runs += r;                   //increment runs of team

                                /*****************
                                BOUNDARIES SCORED
                                *****************/
                                if ( r==4 ){
                                        inn->players[ m->currentplayer1 ].fours_scored++;
                                        inn->team_scorecard.fours++;
                                }
                                if ( r==6 ){
                                        inn->players[ m->currentplayer1 ].sixes_scored++;
                                        inn->team_scorecard.sixes++;
                                }

                                if( r%2!=0 )   exchange_turns=!exchange_turns;                        //turns exchanged after scoring odd no of runs

                                if( chase==1 && inn->team_scorecard.runs>target ){
                                        flag=1; break;
                                }
                                
								inn->team_scorecard.balls++;                             //increment balls of team
                                
								if( inn->team_scorecard.balls%6==0)
                                             exchange_turns=!exchange_turns;;  
                        }
                        else{                                                    		//First player plays

                                inn->players[ m->currentplayer2 ].runs_scored += r;		//run of individual ball added to players account
                                inn->players[ m->currentplayer2 ].balls_faced++;   		//run of individual ball added to players account
                                inn->team_scorecard.runs += r;                    		//increment runs of team

                                /****************
                                BOUNDARIES SCORED
                                *****************/
                                if( r==4 ){
                                inn->players[ m->currentplayer2 ].fours_scored++;
                                inn->team_scorecard.fours++;
                                }
                                if ( r==6 ){
                                        inn->players[ m->currentplayer2 ].sixes_scored++;
                                        inn->team_scorecard.sixes++;
                                }

                                if( r%2!=0 )   exchange_turns=!exchange_turns;				//turns exchanged after scoring odd no of run
                                
								if( chase==1 && inn->team_scorecard.runs>target ){
                                        flag=1;break;
                                }
                                
								inn->team_scorecard.balls++;                             	//increment balls of team
                                
								if( inn->team_scorecard.balls%6==0)
                                    exchange_turns=!exchange_turns;
                            }
                }					//over complete
                
				if( flag==1||allout)  {   break;  }
                
				inn->team_scorecard.overs++;                                             //increment overs of team
        }			//overs complete
        if(inn->team_scorecard.wickets<=8){
          cout<<"\t\t*";inn->generate_player_score( inn->players[ m->currentplayer1 ] , m->currentplayer1);
          cout<<"\t\t*";inn->generate_player_score( inn->players[ m->currentplayer2 ] , m->currentplayer2);
        }
        if(chase==0){
            target=inn->team_scorecard.runs;
        }
      	cout<<endl;
      	
      	cout<<setw(20)<<"\n\t******************           INNINGS OVER        ******************"<<endl;
      	
		if( chase==1 ){  //ord=second?ord==first:first; }
			if(ord==first)
	            ord=second;
			else
        		ord=first;
		}
		cout<<"\t\t\t\t    TEAM "<< ord << " SCORE "<<endl;
        inn->generate_team_scorecard();                                        //Team scorecard display
       
}
void display_the_match_winner(team inn1,team inn2)
{
	 if(flag==1)
     {
         if(ord==1)
            cout<<"\t#########"<<setw(20)<<"team "<<1<<" won the match\t\t##########\n";
         else cout<<"\t#########"<<setw(20)<<"team "<<2<<" won the match\t\t##########\n";
     }
     else {
         if(ord==1)
            cout<<"\t#########"<<setw(20)<<"team "<<2<<" won the match\t\t##########\n";
         else cout<<"\t#########"<<setw(20)<<"team "<<1<<" won the match\t\t##########\n";
     }
      /**************
        INNINGS OVER
        *************/
        //cout<<"*";inn.generate_player_score( inn.players[ m.currentplayer1 ] , m.currentplayer1);
        //cout<<"*";inn.generate_player_score( inn.players[ m.currentplayer2 ] , m.currentplayer2);
       

        /*********
        MATCH TIED
        **********
        if(flag1==1){
            inn.team_scorecard.balls++;
            cout<<"\n\n\n******************          SCORES LEVEL         ******************"<<endl;}

        /**************
        Target Defended
        **************
        if(inn.team_scorecard.runs<target){
            inn.team_scorecard.balls++;
            cout<<"Team "<<ord<<" won the match by "<<target-inn.team_scorecard.runs<<" runs"<<endl;
        }

        /************
        Target Chased
        ************
        if(flag3==1){
            inn.team_scorecard.balls++;
            cout<<"\n\nTeam "<<ord<<" won the match by "<<10-inn.team_scorecard.wickets<<
                    " wickets and " <<overs*6-inn.team_scorecard.balls+1<<" balls remaining"<<endl;
            target=inn.team_scorecard.runs;
    	}*/
}
int main(int argc,char *argv[]){
        /**************
        MATCH STARTED
        **************/

        /*FILE *fp;
        if(argc!=2){    cout<<"No file name"<<endl;exit(1);     }
        if((fp=fopen(argv[1],"w"))==NULL){
                cout<<"Cannot open file."<<endl;
        exit(1);}*/
system("pause >nul");        
        cout<<"\t###################################################################"<<endl;
        cout<<"\t################    CRICKET SCORECARD SIMULATOR    ################"<<endl;
system("pause >nul");
        label:
		cout<<"\n\t\tChoose difficulty\n\t\tEasy(1)\t\tMedium(2)\tDifficult(3)\t";
        int diff,d;
        cin>>d;
        cout<<"\t\tEnter the no. of overs you want to play for:\t";
        cin>>overs;
        if(d==1)diff=1;else if(d==2)diff=2;else if(d==3)diff=3; else {cout<<"     Invalid choice...\n";goto label;}
        //diff = 1?d==1:2?d==2:3?d==3;
system("cls");
        match inning1,inning2;                                   //Generating objects of match class
        team team1,team2;                                        //Generating objects of team class
        srand(time(NULL));                                       //seeding random function with time

        /**************
        TOSS
        **************/
        int toss=0;
        toss=rand()%4;
        cout<<"\n\t\t\tThe coin is being tossed...\n";
		system("pause >nul");
		cout<<"\t\t\t...\n"<<endl;
system("pause >nul");
        if(toss==0){   cout<<"\t\tTEAM 1 WON THE TOSS AND ELECTED TO BAT FIRST.\n"<<endl;
                ord=first; }
        else if(toss==1){  cout<<"\t\tTEAM 1 WON THE TOSS AND ELECTED TO BOWL FIRST.\n"<<endl;
                ord=second; }
        else if(toss==2){   cout<<"\t\tTEAM 2 WON THE TOSS AND ELECTED TO BAT FIRST.\n"<<endl;
                ord=second; }
        else if(toss==3){   cout<<"\t\tTEAM 2 WON THE TOSS AND ELECTED TO BOWL FIRST.\n"<<endl;
                ord=first; }
system("pause >nul");
system("cls");
        int chase=0; 
        /*******************/
        cout<<"\n\n\n\n\t******************    CRICKET MATCH SCORECARD    ******************"<<endl;
        cout<<"\t*******************************************************************"<<endl;
        
        if(ord==first){
			cout<<"\n\n\n\n\t************************   TEAM 1 PLAYS   ************************\n";
			playmatch(&team1,&inning1,chase,diff);                         /*INNINGS 1 STARTED*/                                                     /*******************/
			chase=1; 
			cout<<"\n";
			cout<<"\t************************   TEAM 2 PLAYS   ************************\n";
			playmatch(&team2,&inning2,chase,diff);                         /*INNINGS 2 STARTED*/
        }  
        else {
            cout<<"\t************************   TEAM 2 PLAYS   ************************\n";
            playmatch(&team2,&inning1,chase,diff); 
            chase=1;   
            cout<<"\n";
            cout<<"\t************************   TEAM 1 PLAYS   ************************\n";
            playmatch(&team1,&inning2,chase,diff); 
        }

system("pause >nul");
system("cls");
        cout<<"\n\n\n\n\n"<<endl;
        cout<<"\t\tTEAM 1 SCORE"<<endl;
		team1.generate_team_scorecard();
		cout<<"\t\tTEAM 2 SCORE"<<endl;
    	team2.generate_team_scorecard();
        cout<<endl<<"\n\n\n\n\n\n\n\n\t###################################################################"<<endl;
        cout<<"\t#########                                               ###########"<<endl;
        display_the_match_winner( team1,team1);
		//fclose(fp);
		cout<<"\t#########                                               ###########"<<endl;
		cout<<"\t###################################################################"<<endl<<endl;
return 0;
    
}
