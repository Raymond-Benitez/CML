#ifndef CML_H
#define CML_H

#include "ConstrainedAlgo.h"

using namespace std::chrono;

class CML : public ConstrainedAlgo {
public:
  CML(NumericMatrix true_dag,arma::mat df,
           NumericVector targets,
           NumericVector nodes_interest,
           StringVector names,
           int lmax,
           double signif_level,
           bool verbose,
           std::string test="testIndFisher",
           bool estDAG=false); // tested
  
  CML(NumericMatrix true_dag, // population version
           NumericVector targets,
           NumericVector nodes_interest,
           StringVector names,
           int lmax,
           bool verbose); // tested
  
  void getSkeletonTotal(); // tested
  void updateVariables();
  void getSkeletonTarget(const size_t &t); // tested
  void removeExcessNodes();
  int getVStructures(bool FCI); // tested
  
  // Accessors
  std::vector<double> getTargetSkeletonTimes() { 
    return target_skeleton_times; 
  };
  double getTotalSkeletonTime() { return total_skeleton_time; };
  NumericVector getRulesCount() { return rules_used; };
  NumericVector getPCRulesCount() { return rules_used_PC; };
  
  // Orientation Rules (tested)
  // Rule 1
  void rule1search(size_t beta,size_t alpha,bool &track_changes);
  bool rule1(bool &track_changes); 
  // Rule 2
  void rule2search(size_t beta,size_t alpha,
                   bool condition1,bool condition2,bool &track_changes);
  bool rule2(bool &track_changes);
  // Rule 3
  List rule3asearch(size_t beta,size_t alpha);
  void rule3bsearch(const size_t &alpha,const size_t &beta,const size_t &gamma,
                    bool &track_changes);
  bool rule3(bool &track_changes);
  // Rule 4
  bool check_sep_r4(size_t beta,NumericVector md_path);
  bool rule4(bool &track_changes);
  //Rule 8
  bool rule8(bool &track_changes);
  // Rule 9
  bool rule9(bool &track_changes);
  // Rule 10
  bool rule10simple(const size_t &alpha,
                              const size_t &beta,
                              const size_t &gamma,
                              const size_t &d);
  bool rule10(bool &track_changes);
  // All rules
  void allRules();
  
  //Implement PC alg rules after 2nd stage skeleton recovery
  //Rule 1 PC
  void rule1search_PC(size_t beta,size_t alpha,bool &track_changes);
  bool rule1_PC(bool &track_changes);
  
  //Rule 2 PC
  void rule2search_PC(size_t beta,size_t alpha,bool &track_changes);
  bool rule2_PC(bool &track_changes);
  //Rule 3 PC
  List rule3asearch_PC(size_t beta,size_t alpha);
  void rule3bsearch_PC(const size_t &alpha,const size_t &beta,const size_t &gamma,
                    bool &track_changes);
  bool rule3_PC(bool &track_changes);
  //Rule 4 PC
  List rule4asearch_PC(size_t beta,size_t alpha);
  void rule4bsearch_PC(const size_t &alpha,const size_t &beta,const size_t &gamma,
                       bool &track_changes);
  bool rule4_PC(bool &track_changes);
  void allPCRules();
  
  // Function to run the algorithm
  void run(); // tested in wrapper test
  void run_mag(); // TODO: NOT TESTED
  
  // Graph conversion
  void convertMixedGraph(); // tested
  void deleteBetweenNeighborhood();
  void convertFinalGraph(); // tested
  // Ensures we are using proper notation for each pair of nodes
  void checkNotation(); // tested 

  
private:
  std::map<int,int> node_numbering;
  NumericVector rules_used = NumericVector(11); 
  NumericVector rules_used_PC = NumericVector(5); //No need to test for v structures again I think, just adapt R1-4 of PC
  std::vector<double> target_skeleton_times;
  double total_skeleton_time;
};

#endif
