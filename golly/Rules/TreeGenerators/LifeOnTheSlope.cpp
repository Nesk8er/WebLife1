#include <vector>
#include <map>
#include <string>
#include <cstdio>
using namespace std ;
/**
 *   Set the state count, neighbor count, and put your function here.
 */
const int numStates = 3 ;
const int numNeighbors = 8 ;
/**
    0:  (nothing set)
    1:  \
    2:  /
*/
/* order for nine neighbors is nw, ne, sw, se, n, w, e, s, c */
int f(int *a) {
  int on1 = (a[0] & 1) + (a[3] & 1) + (a[4] >> 1) + (a[5] >> 1) +
    (a[6] >> 1) + (a[7] >> 1) + (a[8] & 1) ;
  int on2 = (a[1] >> 1) + (a[2] >> 1) + (a[4] & 1) + (a[5] & 1) +
    (a[6] & 1) + (a[7] & 1) + (a[8] >> 1) ;
  if (on1 == 2)
    if (on2 == 2)
      return 0 ;
    else
      return 1 ;
  else if (on2 == 2)
    return 2 ;
  else
    return 0 ;
}
const int numParams = numNeighbors + 1 ;
map<string,int> world ;
vector<string> r ;
int nodeSeq, params[9] ;
int getNode(const string &n) {
   map<string,int>::iterator it = world.find(n) ;
   if (it != world.end())
      return it->second ;
   world[n] = nodeSeq ;
   r.push_back(n) ;
   return nodeSeq++ ;
}
int recur(int at) {
   if (at == 0) {
      return f(params) ;
   } else {
      char buf[256*10] ;
      sprintf(buf, "%d", at) ;
      for (int i=0; i<numStates; i++) {
         params[numParams-at] = i ;
         sprintf(buf+strlen(buf), " %d", recur(at-1)) ;
      }
      return getNode(buf) ;
   }
}
void writestring() {
   printf("num_states=%d\n", numStates) ;
   printf("num_neighbors=%d\n", numNeighbors) ;
   printf("num_nodes=%d\n", r.size()) ;
   for (unsigned int i=0; i<r.size(); i++)
      printf("%s\n", r[i].c_str()) ;
}
int main(int argc, char *argv[]) {
   recur(numParams) ;
   writestring() ;
}
