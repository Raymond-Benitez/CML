#ifndef MBLIST_H
#define MBLIST_H

#include "DAG.h" // Needed for true_DAG

using std::map;
using std::pair;
using std::sort;
using std::endl;

class MBList{
public:
  // Sample version constructor with vector of nodes and matrix of nodes in MB
  // Matrix contains information regarding the MBs for all targets and first-order nbhrs
  MBList(NumericVector node_vec,NumericMatrix mb_mat,bool verbose=false); // tested
  
  // Population version constructor with true DAG
  MBList(NumericVector node_vec,DAG* true_DAG,bool verbose=false); // tested
  
  // Accessors
  // Obtains the MB for node i
  NumericVector getMB(size_t i){ // tested
   if (mb_list.count(i)==0){
       
      stop("%i is not an element of the map.Failing in MBlist.h \n",i);
    }
    return mb_list.find(i)->second;
  }
  //My attempt to bypass error by not full stopping  
//  NumericVector getMB(size_t i){
//    auto it = mb_list.find(i);
//    if (it == mb_list.end()) {
//      return NumericVector();  // empty MB
//    }
//    return it->second;
//  }
  
  
  /*
   * include_targets argument specifies that we will return targets U nbhd(targets)
   * exclude_targets argument specifies that we will remove any targets which appear
   * in the neighborhood of another target
   * exclude_targets will take precedence
   */
  NumericVector getMBMultipleTargets(NumericVector targets,
                                     bool include_targets=false,
                                     bool exclude_targets=false); // tested
  
  size_t getSize(){
    return size;
  }
  
  // Determine whether a node is in another node's MB
  bool inMB(size_t target,size_t i); // tested
  
  // Print Markov Blankets
  void printMBs();
  
  // Silences output
  bool silencer(){
    bool tmp = verbose;
    verbose = false;
    return tmp;
  }
  
  void removeSilencer(bool v){
    verbose = v;
  }
  
private:
  map<size_t,NumericVector> mb_list;
  size_t size;
  bool verbose;
};

#endif
