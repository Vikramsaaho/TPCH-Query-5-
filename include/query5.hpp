#ifndef QUERY5_HPP
#define QUERY5_HPP

#include <vector>
#include <map>
#include <string>

// Argument parsing
bool parseArgs(int argc, char* argv[],
               std::string& r_name,
               std::string& start_date,
               std::string& end_date,
               int& num_threads,
               std::string& table_path,
               std::string& result_path);

// Load TPCH tables
bool readTPCHData(const std::string& table_path,
                  std::vector<std::vector<std::string>>& customer,
                  std::vector<std::vector<std::string>>& orders,
                  std::vector<std::vector<std::string>>& lineitem,
                  std::vector<std::vector<std::string>>& supplier,
                  std::vector<std::vector<std::string>>& nation,
                  std::vector<std::vector<std::string>>& region);

// Execute query
bool executeQuery5(const std::string& r_name,
                   const std::string& start_date,
                   const std::string& end_date,
                   int num_threads,
                   const std::vector<std::vector<std::string>>& customer,
                   const std::vector<std::vector<std::string>>& orders,
                   const std::vector<std::vector<std::string>>& lineitem,
                   const std::vector<std::vector<std::string>>& supplier,
                   const std::vector<std::vector<std::string>>& nation,
                   const std::vector<std::vector<std::string>>& region,
                   std::map<std::string, double>& results);

// Output results
bool outputResults(const std::string& result_path,
                   const std::map<std::string, double>& results);

#endif