#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main(){
  auto output_reset = [](){ cout << "\033[2J\033[1;1H"; cout.flush(); };
  output_reset();
  string dc = "You are in a dark dungeon.  If you get torch, You vision more spread.\n";
  string ope = "Openration Move: w,a,s,d Quit: q OpenItembox: i\n";
  for (char c:dc){ cout << c; cout.flush(); usleep(30000); }
  usleep(1500000);
  cout << "(0,0) Lv.1-0" << endl;
  for (int i(0);i < 7;++i) cout << endl;
  cout << ope;
}