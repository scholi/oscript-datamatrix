#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vii;

  // valid chars
#if 1
const int l = 55;
  const char x[] = "0123456789abcdef"
                   "+-*/%&|^~{}()S<>="
                   "IDCzir#[]@GPpQABEMNZFR";
#else
  const int l = 4;
  const char x[] = "0123";
#endif

const int k = 3;
char res[k];
char com[k];

int level=0;
void combi(int pos) {
  if (pos==k) {
     for (int i=0;i<k;++i)
      cout << com[i];
    cout << ", ";
    return;
  }
  for (int i=0;i<k;++i) {
    com[pos] = res[i];
    combi(pos+1);
  }
}

void subset(const char* c, int set, int pos) {
  if (set==k) {
    for (int i=0;i<k;++i)
      cout << res[i];
    cout << " : ";
    combi(0);
    cout << endl;
    return;
  }
  for (int i=pos;i<l;++i) {
    res[set] = c[i];
    subset(c, set+1, i+1);
  }
}

char r[k];
void rep(const char* c, int pos) {
  if (k==pos) {
    for (int i=0;i<k;++i)
      cout << r[i];
    cout << endl;
    return;
  }
  for (int j=0;j<l;++j) {
    r[pos] = c[j];
    rep(c, pos+1);
  }
}

int main(int argc, char** argv) {
  // subset(x, 0, 0);
  
	//  rep(x, 0);

	ifstream in("opt.this");
	char z;

	int total=0;
	int st[256];
	memset(st, 0, sizeof(st));

	while(in>>z) {
    ++total;
		st[z]++;
	}

	vector<pair<int,char> > v;
	for (int i=0;i<l;++i) {
//    cout << x[i] << " : " << st[x[i]] << endl;
		v.push_back(pair<int,char>(st[x[i]],x[i]));
	}


	const int N = 10;
	cout << "top " << N << endl;
  sort(v.begin(),v.end(),greater<pair<int,int> >());
	for (int i=0;i<N;++i) {
    cout << v[i].second << " : " << v[i].first << endl;
	}
	cout << "tot : " << total << endl;

	cout << "not used : " << endl;
	for (int i=0;i<v.size();++i) {
		if (v[i].first==0)
    cout << v[i].second << " : " << v[i].first << endl;
	}


  return 0;
}

