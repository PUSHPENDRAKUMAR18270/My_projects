#include<iostream>
#include<string.h>
//#include <bits/stdc++.h>
#include <ctime>
#define ll long long int
using namespace std;
 int flag=0;
const int overs=15;                                                      /* DEFINING NO OF OVERS OF MATCH */
int target=0;                                                          /* TARGET GLOBAL VARIABLE  */
enum teamorder{first=1,second};                                         /* TEAM BATTING FIRST ORDER ENUM */
teamorder ord=first;

class match;                                                            /* MATCH CLASS */

/**************
Players Stats
**************/
struct player{
        int runs_scored;
        int balls_faced;
        int boundaries_scored;
        int wickets_taken;
};
/**************
Team Stats
**************/
struct scorecard{
        int runs;
        int overs;
        int balls;
        int boundaries;
        int wickets;
};
/**************************
Team Data Members & methods
**************************/
class team{
        player players[11];
        scorecard team_scorecard;
        public:
        team(){team_scorecard={0,0,0,0,0};
        for(int i=0;i<11;i++){                                         /* INITIALISING PLAYERS STRUCTURE TO ZERO */
            players[i].runs_scored=0;
            players[i].balls_faced=0;
            players[i].boundaries_scored=0;
            players[i].wickets_taken=0;
        }
    }
    void generate_player_score(player &p,int counter);
    void generate_team_scorecard();
    friend void playmatch(team inn,match m,int chase);
    friend bool chech_win(int runs,int wickets);
    friend void display_the_match_winner();
};
/****************
Players Scorecard
****************/
void team::generate_player_score(player &p,int counter){
        cout<<"PLAYER "<<counter<<": \t\t";
        cout<<p.runs_scored<<" ("<<p. balls_faced<<") "<<"(4's/6's: "<<p.boundaries_scored<<" )"<<endl;
}
/**************
Team Scorecard
**************/
void team::generate_team_scorecard(){
        cout<<"Runs :  "<<team_scorecard.runs<<"\tOvers :  "<<team_scorecard.overs<<"."<<team_scorecard.balls%6<<
        "\tBoundaries :  "<<team_scorecard.boundaries<<endl<<"Wickets :  "<<team_scorecard.wickets<<"\tBalls : "<<team_scorecard.balls<<endl;
        cout<<"*******************************************************************\n"<<endl;

}
/***************************
Match Data Members & methods
***************************/
class match:public team{
        int currentplayer1,currentplayer2;
        int counter;
       
        public:
        match(){  currentplayer1=1; currentplayer2=2; counter=2;target=0;}
        friend void playmatch(team inn,match m,int chase);
        friend bool chech_win(int runs,int wickets);
        friend void display_the_match_winner();
};
/********
PlAYMATCH
*********/
void playmatch(team inn,match m,int chase){
        int exchange_turns=0;
        int allout=0;
        for(int j=0;j<overs;j++){                                             //INNINGS STARTED
                int r,w;
                
                
                //if(inn.team_scorecard.wickets==10) break;                    //All OUT
                /**************
                OVER STARTED
                **************/
                for(int i=0;i<6;i++){
                    
                        r=rand()%7;                                             //r=runs scored on each ball
                        r=(r==5)?0:r;                                           //r=0 when r=5 occurs
                        //if(m.counter>6) r=(r==5||r==3||w==5||w==6||w==8||w==9)?0:r;//r=0 when tailenders bat & score r={3,5} || w={5,6,8,9}
                        w=rand()%10;

                        /**************
                        WICKET FALLEN
                        **************/
                        if(w==7){                                                     //generate wicket at w==7
                            if(inn.team_scorecard.wickets==10){
                                allout=1;
                                   break;
                                }
                                if(exchange_turns==0){                                         //batsman 1 out on random ball
                                        inn.players[ m.currentplayer1 ].balls_faced++;  //players ball faced incremented
                                        inn.generate_player_score( inn.players[ m.currentplayer1 ] ,m.currentplayer1 ); //print score of batsman out
                                        m.currentplayer1 = ++m.counter;                 //increment current batsman
                                }
                                else {                                               //batsman 2 out on random ball
                                        inn.players[ m.currentplayer2 ].balls_faced++;  //players ball faced incremented
                                        inn.generate_player_score( inn.players[ m.currentplayer2 ] , m.currentplayer2 );  //print score of batsman out
                                        m.currentplayer2 = ++m.counter;                 //increment current batsman
                                }
                                inn.team_scorecard.wickets++;                        //increment wickets of team
                                inn.team_scorecard.balls++;                          //increment ball count of team
                                continue;
                        }
                        //count++;

                        /******************
                        RUNNING THE INNINGS
                        *******************/
                        if( exchange_turns==0 ){                                 //First player plays

                                inn.players[ m.currentplayer1 ].runs_scored += r;//run of individual ball added to players account
                                inn.players[ m.currentplayer1 ].balls_faced++;   //run of individual ball added to players account
                                inn.team_scorecard.runs += r;                   //increment runs of team

                                /*****************
                                BOUNDARIES SCORED
                                *****************/
                                if ( r==4 || r==6 ){
                                        inn.players[ m.currentplayer1 ].boundaries_scored++;
                                        inn.team_scorecard.boundaries++;
                                }

                                if( r%2!=0 )   exchange_turns=1;                        //turns exchanged after scoring odd no of runs

                                 if(chase==1&&inn.team_scorecard.runs>target){
                                        flag=1; break;
                                }
                                inn.team_scorecard.balls++;                             //increment balls of team
                                 if( inn.team_scorecard.balls%6==0)
                                             exchange_turns=1;  
                        }
                        else{                                                    //First player plays

                                inn.players[ m.currentplayer2 ].runs_scored += r;//run of individual ball added to players account
                                inn.players[ m.currentplayer2 ].balls_faced++;   //run of individual ball added to players account
                                inn.team_scorecard.runs += r;                    //increment runs of team

                                /****************
                                BOUNDARIES SCORED
                                *****************/
                                if( r==4 || r==6 ){
                                inn.players[ m.currentplayer2 ].boundaries_scored++;
                                inn.team_scorecard.boundaries++;
                                }

                                if( r%2!=0 )   exchange_turns=0;                //turns exchanged after scoring odd no of run
                                if(chase==1&&inn.team_scorecard.runs>target){
                                        flag=1;break;
                                }
                                inn.team_scorecard.balls++;                             //increment balls of team
                                if( inn.team_scorecard.balls%6==0)
                                            exchange_turns=0;
                            }
                }
                  
                if( flag==1||allout)
                {
                    break;
                }
                inn.team_scorecard.overs++;                                             //increment overs of team
                
        }
        if(inn.team_scorecard.wickets<=8)
        {
          cout<<"*";inn.generate_player_score( inn.players[ m.currentplayer1 ] , m.currentplayer1);
          cout<<"*";inn.generate_player_score( inn.players[ m.currentplayer2 ] , m.currentplayer2);
            
        }
        if(chase==0)
            {
                target=inn.team_scorecard.runs;
            }
      inn.generate_team_scorecard();
      cout<<endl;
}
void display_the_match_winner()
{
     if(flag==1)
     {
         if(ord==1)
         {cout<<"team "<<2<<"won the match\n";
            
 }
         else cout<<" team "<<1<<"won the match\n";
     }
     else {
         if(ord==1)
         cout<<"team "<<1<<"won the match\n";
         else cout<<" team "<<2<<"won the match\n";
     }
     
     
     
     
     
     
     
     
    /* 
     
      /**************
        INNINGS OVER
        *************
        cout<<"*";inn.generate_player_score( inn.players[ m.currentplayer1 ] , m.currentplayer1);
        cout<<"*";inn.generate_player_score( inn.players[ m.currentplayer2 ] , m.currentplayer2);
        cout<<"\n******************           INNINGS OVER        ******************\n"<<endl;
        cout<<"TEAM "<< ord << " SCORE :\t";
        inn.generate_team_scorecard();                                        //Team scorecard display

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
                        " wickets and " <</*overs*6-ball-inn.team_scorecard.balls+1<<" balls remaining"<<endl;
            target=inn.team_scorecard.runs;*/
    
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
        cout<<"###################################################################"<<endl;
        cout<<"******************    CRICKET MATCH SCORECARD    ******************\n"<<endl;

        match inning1,inning2;                                   //Generating objects of match class
        team team1,team2;                                        //Generating objects of team class

        srand(time(NULL));                                       //seeding random function with time

        /**************
        TOSS
        **************/
        int toss=0;
        toss=rand()%4;
        if(toss==0){   cout<<"TEAM 1 WON THE TOSS AND ELECTED TO BAT FIRST.\n"<<endl;
                ord=first; }
        else if(toss==1){  cout<<"TEAM 1 WON THE TOSS AND ELECTED TO BOWL FIRST.\n"<<endl;
                ord=second; }
        else if(toss==2){   cout<<"TEAM 2 WON THE TOSS AND ELECTED TO BAT FIRST.\n"<<endl;
                ord=second; }
        else if(toss==3){   cout<<"TEAM 2 WON THE TOSS AND ELECTED TO BOWL FIRST.\n"<<endl;
                ord=first; }

        int chase=0; 
        /*******************/
        if(ord==first)
        {  playmatch(team1,inning1,chase);                         /*INNINGS 1 STARTED*/                                                     /*******************/
           chase=1; 
           cout<<endl;
           playmatch(team2,inning2,chase);                         /*INNINGS 2 STARTED*/
        }  
        else {
            playmatch(team2,inning1,chase); 
            chase=1;   
            cout<<endl;
            playmatch(team1,inning2,chase); 
        }
        display_the_match_winner();
        //fclose(fp);

        cout<<endl<<endl<<"###################################################################"<<endl<<endl;
return 0;
    
}