#include "query5.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

mutex mtx;

// ---------------- LOAD FILE ----------------
static vector<vector<string>> loadFile(const string& path) {
    vector<vector<string>> data;
    ifstream file(path);
    string line;

    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string val;

        while (getline(ss, val, '|')) {
            row.push_back(val);
        }
        data.push_back(row);
    }
    return data;
}

// ---------------- READ DATA ----------------
bool readTPCHData(const string& table_path,
                  vector<vector<string>>& customer,
                  vector<vector<string>>& orders,
                  vector<vector<string>>& lineitem,
                  vector<vector<string>>& supplier,
                  vector<vector<string>>& nation,
                  vector<vector<string>>& region) {

    customer = loadFile(table_path + "/customer.tbl");
    orders   = loadFile(table_path + "/orders.tbl");
    lineitem = loadFile(table_path + "/lineitem.tbl");
    supplier = loadFile(table_path + "/supplier.tbl");
    nation   = loadFile(table_path + "/nation.tbl");
    region   = loadFile(table_path + "/region.tbl");

    return true;
}

// ---------------- ARG PARSING ----------------
bool parseArgs(int argc, char* argv[],
               string& r_name,
               string& start_date,
               string& end_date,
               int& num_threads,
               string& table_path,
               string& result_path) {

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "--r_name") r_name = argv[++i];
        else if (arg == "--start_date") start_date = argv[++i];
        else if (arg == "--end_date") end_date = argv[++i];
        else if (arg == "--threads") num_threads = stoi(argv[++i]);
        else if (arg == "--table_path") table_path = argv[++i];
        else if (arg == "--result_path") result_path = argv[++i];
    }

    if (num_threads <= 0) num_threads = 1;

    return !(r_name.empty() || table_path.empty() || result_path.empty());
}

// ---------------- EXECUTE QUERY ----------------
bool executeQuery5(const string& r_name,
                   const string& start_date,
                   const string& end_date,
                   int num_threads,
                   const vector<vector<string>>& customer,
                   const vector<vector<string>>& orders,
                   const vector<vector<string>>& lineitem,
                   const vector<vector<string>>& supplier,
                   const vector<vector<string>>& nation,
                   const vector<vector<string>>& region,
                   map<string, double>& results) {

    // Step 1: find region key
    string regionKey = "";
    for (const auto& r : region) {
        if (r[1] == r_name) {
            regionKey = r[0];
            break;
        }
    }

    // Step 2: nation -> region filter
    map<string, string> nationMap; // nationKey -> nationName
    for (const auto& n : nation) {
        if (n[2] == regionKey) {
            nationMap[n[0]] = n[1];
        }
    }

    // Step 3: customer -> nation
    map<string, string> customerMap; // custKey -> nationKey
    for (const auto& c : customer) {
        if (nationMap.count(c[3])) {
            customerMap[c[0]] = c[3];
        }
    }

    // Step 4: orders -> customer + date filter
    map<string, string> orderMap; // orderKey -> nationKey
    for (const auto& o : orders) {
        string orderDate = o[2];

        if (orderDate >= start_date && orderDate <= end_date) {
            if (customerMap.count(o[1])) {
                orderMap[o[0]] = customerMap[o[1]];
            }
        }
    }

    // Step 5: process lineitem
    for (const auto& l : lineitem) {
        string orderKey = l[0];

        if (orderMap.count(orderKey)) {
            string nationKey = orderMap[orderKey];
            string nationName = nationMap[nationKey];

            double extprice = stod(l[5]);
            double discount = stod(l[6]);

            double revenue = extprice * (1 - discount);

            results[nationName] += revenue;
        }
    }

    return true;
}

// ---------------- OUTPUT ----------------
bool outputResults(const string& result_path,
                   const map<string, double>& results) {

    ofstream out(result_path + "/result.txt");
    if (!out.is_open()) return false;

    // Convert map → vector
    vector<pair<string, double>> vec(results.begin(), results.end());

    // Sort by revenue DESC
    sort(vec.begin(), vec.end(),
         [](const pair<string, double>& a, const pair<string, double>& b) {
             return a.second > b.second;
         });

    // Write sorted output
    for (const auto& p : vec) {
        out << p.first << " " << p.second << "\n";
    }

    out.close();
    return true;
}