#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main(){
  auto output_reset = [](){ cout << "\033[2J\033[1;1H"; cout.flush(); };
  output_reset();
  string dc = "You are in a dark dungeon.  If you get torch, You vision more spread.\n";
  string ope = "Openration Move: w,a,s,d Quit: q OpenItembox: i\n";
  for (char c:dc){ cout << c; cout.flush(); usleep(30000); }
  usleep(800000);
  string hml = "How many times larger do you want the map? >> ";
  for (char c:hml){ cout << c; cout.flush(); usleep(30000); } double m; cin >> m;
  usleep(800000);
  string hmt = "How many times more torches do you place on the map? >> ";
  for (char c:hmt){ cout << c; cout.flush(); usleep(30000); } double t; cin >> t;
  usleep(1500000);
  int x=0,y=0,z=1,lv=6; vector<vector<int>> B(1,vector<int>(1,2));
  int n = z*m; n += 6+(1-n%2); B.assign(n,vector<int>(n,0));
  auto draw = [&x,&y,&z,&n,&lv,&B,&dc,&ope](){
    cout << "\033[2J\033[1;1H";
    cout << dc << '(' << x << ',' << y << ") Lv." << z << '-' << lv << endl;
    for (int i(0);i < 7;++i){
      for (int k(0);k < 7;++k){
        if (abs(i-3)+abs(k-3)<=lv){
          if (B[n/2+1+x+i-3][n/2+1+x+k-3]==0) cout << "\e[37m\e[47m  ";
          else if (B[n/2+1+x+i-3][n/2+1+x+k-3]==1) cout << "\e[34m\e[44m  ";
          else cout << "\e[31m\e[41m  ";
        }
        else cout << "\e[30m\e[40m  ";
      }
      cout << endl;
    }
    cout << "\e[0m";
    cout << ope; cout.flush();
  };
  draw();
}