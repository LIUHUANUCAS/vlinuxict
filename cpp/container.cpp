#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;
template<class T>
T cmerge (T a, T b) { T t(a); t.insert(b.begin(),b.end()); return t; }

int main ()
{
  unordered_set<string > first;                                // empty
  unordered_set<string > second ( {"red","green","blue"} );    // init list
  unordered_set<string > third ( {"orange","pink","yellow"} ); // init list
  unordered_set<string > fourth ( second );                    // copy
  unordered_set<string > fifth ( cmerge(third,fourth) );       // move
  unordered_set<string > sixth ( fifth.begin(), fifth.end() ); // range

  cout << "sixth contains:";
  for (const string& x: sixth) cout << " " << x;
  cout << endl;

  return 0;
}
