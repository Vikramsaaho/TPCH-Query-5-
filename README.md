# 🚀 TPCH Query 5 - C++ Multithreading

## 📌 Overview
This project implements **TPC-H Query 5** using **C++ with multithreading**.  
It processes TPCH `.tbl` datasets and calculates revenue grouped by nation.

The goal of this project is to demonstrate:
- Efficient data processing
- Multithreading using `std::thread`
- File handling and parsing
- CMake-based build system

---

## 🛠 Tech Stack
- **C++ (C++11)**
- **Multithreading (std::thread, mutex)**
- **CMake**
- **File I/O (CSV/TBL parsing)**

---

## 📂 Project Structure
tpch-query5/
├── src/
│ ├── main.cpp
│ └── query5.cpp
├── include/
│ └── query5.hpp
├── data/ # TPCH .tbl files (not included)
├── output/ # result output
├── CMakeLists.txt
└── README.md


---

## ⚙️ Build Instructions

```bash
mkdir build
cd build
cmake ..
cmake --build .

./tpch_query5.exe \
  --r_name ASIA \
  --start_date 1995-01-01 \
  --end_date 1996-01-01 \
  --threads 4 \
  --table_path ../data \
  --result_path ../output

📥 Input Data

You must provide TPCH .tbl files inside the data/ folder:

data/
├── customer.tbl
├── orders.tbl
├── lineitem.tbl
├── supplier.tbl
├── nation.tbl
├── region.tbl

📊 Output

Results are written to:

output/result.txt

Example:

CHINA 1800
INDIA 950

⚡ Features
Parallel processing using multiple threads
Efficient file parsing using streams
Configurable thread count
Command-line argument support
Cross-platform build using CMake

🧠 Concepts Demonstrated
Multithreading & synchronization (mutex)
Data aggregation
File-based database processing
Build automation (CMake)
CLI design in C++
🚀 Future Improvements
Full TPCH Query 5 join logic (region → nation → customer → orders → lineitem)
Performance optimization using thread-local storage
Sorting results by revenue
Large dataset benchmarking
👨‍💻 Author

Prabhash Nutakki

⭐ Acknowledgements
TPC-H Benchmark Specification
C++ Standard Library


