#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

//This is to print the final solved sudoku grid.
void print_final_grid(vector<vector<int>> soduku_grid){
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            cout<<soduku_grid[i][j]<<" ";
        }
        cout<<endl;
    }
}

//Here we will be checking the validity along each row.
bool checking_row(vector<vector<int>> sudoku_grid){
    int num=sudoku_grid.size();
    for(int i=0;i<num;++i){
        vector<int> hsh(num+1,0);
        for(int j=0;j<num;++j){
            int value=sudoku_grid[i][j];
            if(value>0) hsh[value]++;
            if(hsh[value]>1) return false;
        }
    }
    return true;
}

//Here we will be checking the validity along each column.
bool checking_column(vector<vector<int>> sudoku_grid){
    int num=sudoku_grid.size();
    for(int i=0;i<num;++i){
        vector<int> hsh(num+1,0);
        for(int j=0;j<num;++j){
            int value=sudoku_grid[j][i];
            if(value>0) hsh[value]++;
            if(hsh[value]>1) return false;
        }
    }
    return true;
}

//Here we will be checking the validity along each box.
bool checking_box(vector<vector<int>> sudoku_grid){
    int num=sudoku_grid.size();
    for(int i=0;i<num;++i){
        vector<int> hsh(num+1,0);
        for(int j=0;j<num;++j){
            int value=sudoku_grid[((i/3)*3)+(j/3)][((i%3)*3)+(j%3)];
            if(value>0) hsh[value]++;
            if(hsh[value]>1) return false;
        }
    }
    return true;
}

//Calling all the validating functions of row, column and box.
bool check_rules(vector<vector<int>> sudoku_grid){
    if(checking_box(sudoku_grid) && checking_column(sudoku_grid) && checking_row(sudoku_grid)) return true;
    else return false;
}

//To check whether we can insert n at x position in grid.
bool can_insert_num(vector<vector<int>> sudoku_grid,int num,int x,int n){
    sudoku_grid[x/num][x%num]=n;
    if(check_rules(sudoku_grid)) return true;
    else return false;
}

//Finds the first place, where we have to fit a number.
int find_the_place(vector<vector<int>> sudoku_grid,int num){
    for(int i=0;i<num*num;++i){
        if(sudoku_grid[i/num][i%num]==0) return i;
    }
    return -1;
}

//This functions solves and checks whether the given grid can be solved or not.
bool solve_the_grid(vector<vector<int>>& sudoku_grid){
    int num=sudoku_grid.size();
    int x=find_the_place(sudoku_grid,num);
    if(x==-1) return true;
    else{
        for(int n=1;n<=num;++n){
            if(can_insert_num(sudoku_grid,num,x,n)){
                sudoku_grid[x/num][x%num]=n;
                if(solve_the_grid(sudoku_grid)) return true;
                else sudoku_grid[x/num][x%num]=0;
            }
        }
        return false;
    }
}

int main(){
    vector<vector<int>> sudoku_grid(9,vector<int> (9,0));
    //Taking the input of the initial state of grid.
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            int num;
            cin>>num;
            //Checks whether the provided input is valid or not.
            if(num>=0 && num<=9) sudoku_grid[i][j]=num;
            else{
                cout<<"Invalid Input!!!"<<endl;
                return 0;
            }
        }
    }

    //Here we make ensure that the sudoku grid is solvable or not.
    if(solve_the_grid(sudoku_grid))
        print_final_grid(sudoku_grid);
    else 
        cout<<"This grid cannot be solved!!! \nTry with other input grid."<<endl;
}
