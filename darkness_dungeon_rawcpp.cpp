#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

// Union-Find amortized O(log N)
pair<int,int> root(vector<vector<pair<int,int>>>& UF,pair<int,int> x) noexcept {
  if (UF[x.first][x.second].first==-1) return x;
  return UF[x.first][x.second] = root(UF,UF[x.first][x.second]);
}

int main(){
  auto output_reset = [](){ cout << "\033[2J\033[1;1H"; cout.flush(); };
  output_reset();
  string dc = "You are in a dark dungeon.  If you get torch, You vision more spread.\n";
  string ope = "Openration Move: w,a,s,d Quit: q\n";
  for (char c:dc){ cout << c; cout.flush(); usleep(30000); }
  usleep(800000);
  string hml = "How many times larger do you want the map? >> ";
  for (char c:hml){ cout << c; cout.flush(); usleep(30000); } double m; cin >> m;
  usleep(800000);
  string hmt = "How many times more torches do you place on the map? >> ";
  for (char c:hmt){ cout << c; cout.flush(); usleep(30000); } double t; cin >> t;
  usleep(800000);
  string hmw = "How many times more walls do you place on the map? >> ";
  for (char c:hmw){ cout << c; cout.flush(); usleep(30000); } double w; cin >> w;
  usleep(1500000);
  int x=0,y=0,z=0,lv=1,n; vector<vector<int>> B;
  auto draw = [&x,&y,&z,&n,&lv,&B,&dc,&ope](){
    cout << "\033[2J\033[1;1H";
    cout << dc << '(' << x << ',' << y << ") Lv." << z << '-' << lv << endl;
    for (int i(0);i < 7;++i){
      for (int k(0);k < 7;++k){
        if (abs(i-3)+abs(k-3)<=lv){
          if (B[n/2+x+i-3][n/2+y+k-3]==0) cout << "\e[47m  ";
          else if (B[n/2+x+i-3][n/2+y+k-3]==1) cout << "\e[44m  ";
          else if (B[n/2+x+i-3][n/2+y+k-3]==2) cout << "\e[42m  ";
          else cout << "\e[41m  ";
        }
        else cout << "\e[40m  ";
      }
      cout << endl;
    }
    cout << "\e[0m";
    cout << ope << "Operation? >> "; cout.flush();
  };
  vector<vector<pair<int,int>>> UF;
  auto cant = [&UF,&B,&n](int x,int y) -> bool {
    set<pair<int,int>> s; int z = 0;
    if (x!=0&&y!=0&&B[x-1][y-1]==1) ++z,s.emplace(root(UF,make_pair(x-1,y-1)));
    if (x!=0&&B[x-1][y]==1) ++z,s.emplace(root(UF,make_pair(x-1,y)));
    if (x!=0&&y!=n-1&&B[x-1][y+1]==1) ++z,s.emplace(root(UF,make_pair(x-1,y+1)));
    if (y!=0&&B[x][y-1]==1) ++z,s.emplace(root(UF,make_pair(x,y-1)));
    if (y!=n-1&&B[x][y+1]==1) ++z,s.emplace(root(UF,make_pair(x,y+1)));
    if (x!=n-1&&y!=0&&B[x+1][y-1]==1) ++z,s.emplace(root(UF,make_pair(x+1,y-1)));
    if (x!=n-1&&B[x+1][y]==1) ++z,s.emplace(root(UF,make_pair(x+1,y)));
    if (x!=n-1&&y!=n-1&&B[x+1][y+1]==1) ++z,s.emplace(root(UF,make_pair(x+1,y+1)));
    return z!=s.size();
  };
  auto connect = [&UF,&B,&n](int x,int y) -> void {
    B[x][y] = 1;
    if (x!=0&&y!=0&&B[x-1][y-1]==1){
      auto a = root(UF,make_pair(x-1,y-1)),b = root(UF,make_pair(x,y));
      if (a!=b) UF[a.first][a.second] = b;
    }
    if (x!=0&&B[x-1][y]==1){
      auto a = root(UF,make_pair(x-1,y)),b = root(UF,make_pair(x,y));
      if (a!=b) UF[a.first][a.second] = b;
    }
    if (x!=0&&y!=n-1&&B[x-1][y+1]==1){
      auto a = root(UF,make_pair(x-1,y+1)),b = root(UF,make_pair(x,y));
      if (a!=b) UF[a.first][a.second] = b;
    }
    if (y!=0&&B[x][y-1]==1){
      auto a = root(UF,make_pair(x,y-1)),b = root(UF,make_pair(x,y));
      if (a!=b) UF[a.first][a.second] = b;
    }
    if (y!=n-1&&B[x][y+1]==1){
      auto a = root(UF,make_pair(x,y+1)),b = root(UF,make_pair(x,y));
      if (a!=b) UF[a.first][a.second] = b;
    }
    if (x!=n-1&&y!=0&&B[x+1][y-1]==1){
      auto a = root(UF,make_pair(x+1,y-1)),b = root(UF,make_pair(x,y));
      if (a!=b) UF[a.first][a.second] = b;
    }
    if (x!=n-1&&B[x+1][y]==1){
      auto a = root(UF,make_pair(x+1,y)),b = root(UF,make_pair(x,y));
      if (a!=b) UF[a.first][a.second] = b;
    }
    if (x!=n-1&&y!=n-1&&B[x+1][y+1]==1){
      auto a = root(UF,make_pair(x+1,y+1)),b = root(UF,make_pair(x,y));
      if (a!=b) UF[a.first][a.second] = b;
    }
  };
  srand(time(NULL));
  auto create = [&x,&y,&z,&lv,&n,&m,&t,&w,&B,&cant,&UF,&connect](){
    lv = 1,x = 0,y = 0,++z;
    n = z*m; n += 6+(1-n%2); B.assign(n,vector<int>(n,0));
    UF.assign(n,vector<pair<int,int>>(n,make_pair(-1,-1)));
    for (int i(0);i < 3;++i) for (int k(0);k < n;++k){
      connect(i,k),connect(n-i-1,k),connect(k,i),connect(k,n-i-1);
    }
    while(true){
      int x = 3+rand()%(n-6),y = 3+rand()%(n-6);
      if (x==n/2&&y==n/2) continue;
      B[x][y] = 2;
      break;
    }
    for (int i(0);i < max((int)((n-6)*(n-6)*t),5);++i){
      int x = 3+rand()%(n-6),y = 3+rand()%(n-6);
      --i;
      if (x==n/2&&y==n/2) continue;
      if (B[x][y]) continue;
      ++i,B[x][y] = 3;
    }
    for (int i(0);i < (n-6)*(n-6)*w;++i){
      int x = 3+rand()%(n-6),y = 3+rand()%(n-6);
      --i;
      if (x==n/2&&y==n/2) continue;
      if (B[x][y]) continue;
      if (cant(x,y)) continue;
      ++i,B[x][y] = 1;
    }
  };
  create();
  while(true){
    draw(); string c; cin >> c;
    if (c.size()!=1) continue;
    if (c[0]=='q') break;
    int tx = x,ty = y;
    if (c[0]=='w') --x;
    if (c[0]=='a') --y;
    if (c[0]=='s') ++x;
    if (c[0]=='d') ++y;
    if (B[n/2+x][n/2+y]==1) x = tx,y = ty;
    if (B[n/2+x][n/2+y]==2) create();
    if (B[n/2+x][n/2+y]==3) ++lv,B[n/2+x][n/2+y] = 0;
  }
}