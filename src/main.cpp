#include "query5.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>

int main(int argc, char* argv[]) {

    std::string r_name, start_date, end_date, table_path, result_path;
    int num_threads = 1;

    // ---------------- HELP ----------------
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--help") {
            std::cout <<
            "Usage:\n"
            "--r_name <region>\n"
            "--start_date <date>\n"
            "--end_date <date>\n"
            "--threads <num>\n"
            "--table_path <path>\n"
            "--result_path <path>\n";
            return 0;
        }
    }

    // ---------------- PARSE ----------------
    if (!parseArgs(argc, argv, r_name, start_date, end_date,
                   num_threads, table_path, result_path)) {
        std::cerr << "Failed to parse arguments\n";
        return 1;
    }

    // ---------------- DATA ----------------
    std::vector<std::vector<std::string>> customer_data;
    std::vector<std::vector<std::string>> orders_data;
    std::vector<std::vector<std::string>> lineitem_data;
    std::vector<std::vector<std::string>> supplier_data;
    std::vector<std::vector<std::string>> nation_data;
    std::vector<std::vector<std::string>> region_data;

    if (!readTPCHData(table_path,
                      customer_data,
                      orders_data,
                      lineitem_data,
                      supplier_data,
                      nation_data,
                      region_data)) {
        std::cerr << "Failed to read TPCH data\n";
        return 1;
    }

    // ---------------- EXECUTE ----------------
    std::map<std::string, double> results;

    if (!executeQuery5(r_name,
                       start_date,
                       end_date,
                       num_threads,
                       customer_data,
                       orders_data,
                       lineitem_data,
                       supplier_data,
                       nation_data,
                       region_data,
                       results)) {
        std::cerr << "Failed to execute query\n";
        return 1;
    }

    // ---------------- OUTPUT ----------------
    if (!outputResults(result_path, results)) {
        std::cerr << "Failed to write output\n";
        return 1;
    }

    std::cout << "TPCH Query 5 completed successfully\n";
    return 0;
}