#include<iostream>
#include<algorithm>
#include<vector>

int main(){
    int num;cin>>num; //Number of players including the dealer
    vector<int> card_points(n,0);
    unordered_map<char,int> mpp={{'A',1},{'1',1},{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},{'10',10},{'J',10},{'Q',10},{'K',10}} //Point details from the card.

    for(int round=0;round<2;++round){
        for(int player=0;player<n;++player){
            char input;cin>>input;
            card_points[player]+=mpp[input];
        }
    }

    vector<bool> status(n,true); //If the player status is true, he can hit, and change it to false, if select to stand.

    for(int player=1;player<n;++player){
        while(status[player]){
            if(card_points[player]>21){
                status[player]=false;
                break;
            }
            string ip;cin>>ip;
            if(ip=="Hit"){
                char input;cin>>input;
                card_points[player]+=mpp[input];
            }else{
                status[player]=false;
            }
        }
    }

    while(status[0]){
        if(card_points[player]>16){
            status[player]=false;
            break;
        }else{
            char input;cin>>input;
            card_points[player]+=mpp[input];
        }
    }
    
    vector<string> results(n,"");
    for(int player=1;player<n;++player){
        if(card_points[player]>21) results[player]="busted";
        else if(card_points[player]>card_points[0]) results[player]="winner";
        else results[player]="loser";
    }

    for(int player=1;player<n;+=player){
        cout<<results[player]<<endl;
    }

    return 0;
}
