/**
 * A Tour of C++: Chapter 11: Input and Output
 * 
 * Skipped: 11.6.2 printf()-style formatting, 11.7.3 String streams, 11.7.4 and 11.7.5 C++23 stuff
 * 11.8 C-Style IO
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <filesystem>
#include <cassert>

using namespace std;

vector<int> read_ints(istream& is, const string& terminator) {
    vector<int> res;
    for(int i; is >> i;)
        res.push_back(i);

    if(is.eof())
        return res;
    if(is.fail()) {
        is.clear();
        string s;
        if(is>>s && s==terminator)
            return res;
        is.setstate(ios_base::failbit);
    }
    return res;
}

struct Entry {
    string name;
    int age;
};

ostream& operator<<(ostream& os, const Entry& e) {
    return os << "{\"" << e.name << "\", " << e.age << "}";  
}

istream& operator>>(istream& is, Entry& e) {
    char c, c2;
    if(is>>c && c=='{' && is>>c2 && c2=='"') { // { followed by ""}
        string name;
        while(is.get(c) && c!='"')
            name += c;
        
        if(is >> c && c==',') {
            int number = 0;
            if(is>>number>>c && c=='}') {
                e = {name, number};
                return is;
            }
        }
    }

    is.setstate(ios_base::failbit);
    return is;
}

// p147

/* todo: skipped printf formatting section */

int main(int argc, char* argv[]) {
    /* Cout Number formatting */
    cout << 1234 << ' ' << hex << 1234 << ' ' << oct << 1234 << 
        ' ' << dec << 1234 << endl;
    constexpr double d = 3.1415;
    cout << d << " " << scientific << d << " " << hexfloat << " " << d << " " << fixed << d << " " << defaultfloat << d << endl;

    /* FileIO */
    ofstream ofs("target.txt");
    if(!ofs)
        throw runtime_error("can't open output file");
    /* Print out today's date */
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    cout << ctime(&t) << endl;
    ofs << ctime(&t) << endl;

    ifstream ifs("source.txt");
    if(!ifs)
        throw runtime_error("can't open input file");

    /* File System Library */
    filesystem::path p = "source.txt";
    assert(exists(p));
    if(is_regular_file(p))
        cout << p << "is a file; its size is " << filesystem::file_size(p) << endl;

    /* Cin/Cout */
    cout << "Enter your name:" << endl;
    string str;
    getline(cin, str);
    cout << "Hello " << str << endl;

    cout << "Enter some integers ended with \"stop\"" << endl;
    auto v = read_ints(cin, "stop");
    for(auto i : v)
        cout << i << " ";
    cout << endl;

    cout << "Enter some entries in the format {name, age}" << endl;
    for(Entry ee; cin>>ee;)
        cout << ee << endl;
}