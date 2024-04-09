#include <iostream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

int main() {
    /* Clocks */
    time_point t0 = system_clock::now();
    vector<double> v;
    for(size_t i=0; i<1000000; i++)
        v.push_back((double)i*(double)i);
    time_point t1 = system_clock::now();
    cout << duration_cast<milliseconds>(t1-t0).count() << " ms" << endl;

    year_month_day spring_day = April/30/2024;
    // cout << weekday(spring_day) << endl; // need g++13
    // cout << format("{:%A}\n", spring_day); // need g++13
    year_month_day bad_day = April/32/2024;
    if(!bad_day.ok())
        cout << "Invalid Day" << endl;

    sys_days t = sys_days{February/25/2022};
    t += days{7};
    year_month_day d = year_month_day{t};
    // cout << d << endl; // need g++13

    time_point tp = system_clock::now();
    // cout << tp << endl;

}