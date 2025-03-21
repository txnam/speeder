#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

#define CNT 1000        // number of runs

void log(const std::string& s, std::ofstream& logFile) {
    std::cout << s << std::endl;
    logFile << s << std::endl;
}

int main() {
    std::ofstream logFile("speeder.log", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open speeder.log" << std::endl;
        return 1;
    }

    double m0 = 100000000.0, m1 = -1.0, s = 0.0;    // min, max, total

    logFile << std::setw(19) << "min" << " | "
            << std::setw(19) << "max" << " | "
            << std::setw(19) << "avg" << " | step" << std::endl;

    for (int r = 0; r < CNT; ++r) {
        auto start = std::chrono::high_resolution_clock::now();

        long long a = 1, b = 0;
        double c = 1.1, d = 1.01;

        for (int i = 0; i < 50000; ++i) {
            a = (a * 123456789) % 987654321;
            if (a % 2) b = b + 1;
            c = c / d;
            if (c < 0.1) d = 0.99;
            if (c > 9.9) d = 1.01;
        }

        std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;

        double t = elapsed.count();     // Get elapsed time in seconds
        s += t;
        if (t < m0) m0 = t;
        if (t > m1) m1 = t;

        logFile << std::fixed << std::setprecision(15)
                << std::setw(19) << m0 << " | "
                << std::setw(19) << m1 << " | "
                << std::setw(19) << s / (r + 1) << " | " << r + 1 << std::endl;
    }
    
    logFile << std::endl;
    logFile.close();

    std::ofstream fineTestFile("finetest.py", std::ios::app);
    if (!fineTestFile.is_open()) {
        std::cerr << "Failed to open finetest.py" << std::endl;
        return 1;
    }

    fineTestFile << "SCALE_C = " 
                 << (s - m0 - m1) / (CNT - 2) * 1000 << std::endl;

    fineTestFile.close();
}