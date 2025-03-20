#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono> // Use std::chrono for high-precision timing

#define CNT 1000 // number of runs

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

    double m0 = 100000000.0, m1 = -1.0, s = 0.0; // min, max, total

    logFile << std::setw(19) << "min" << " | "
            << std::setw(19) << "max" << " | "
            << std::setw(19) << "avg" << " | step" << std::endl;

    for (int r = 0; r < CNT; ++r) {
        // Start high-precision timer
        auto start = std::chrono::high_resolution_clock::now();

        double a = 1, b = 0, c = 1.1, d = 1.01;

        for (int i = 0; i < 50000; ++i) {
            a = static_cast<long long>(a * 123456789) % 987654321;
            if (static_cast<long long>(a) % 2) b = b + 1;
            c = c / d;
            if (c < 0.1) d = 0.99;
            if (c > 9.9) d = 1.01;
        }

        // Stop high-precision timer
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        double t = elapsed.count(); // Get elapsed time in seconds
        s += t;
        if (t < m0) m0 = t;
        if (t > m1) m1 = t;

        logFile << std::fixed << std::setprecision(15)
                << std::setw(19) << m0 << " | "
                << std::setw(19) << m1 << " | "
                << std::setw(19) << s / (r + 1) << " | " << r + 1 << std::endl;
    }

    std::ofstream fineTestFile("finetest.py", std::ios::app);
    if (!fineTestFile.is_open()) {
        std::cerr << "Failed to open finetest.py" << std::endl;
        return 1;
    }

    fineTestFile << "SCALE_C = " 
                 << (s - m0 - m1) / (CNT - 2) * 100 << ";" << std::endl;

    logFile.close();
    fineTestFile.close();

    return 0;
}