//
// Project 1 - DNA Profiling
// Created by Hsien-Hao Chang
// Email: hchan34@uic.edu
// UIN: 653351746

// Creative Component:
// I desgined a function called "add_info"
// This function allows the user to input and store
// additional name/numbers and DNA bases to  in the end of
// their corresponding ourvectors.
// WARNING! please load a database and dna in order for this
// feature to work!

#include <iostream>

#include <fstream>

#include <string>

#include "ourvector.h"

using namespace std;

// This struct holds a name and an ourvector that can store
// many values, and this is a good way to organize a person
// and the numbers.

struct DNA_Profile {
    string name;
    ourvector < int > DNA_Number;
};

// This function is used in load_Db to find out
// what is the ammount of DNA variation we are
// interested in.

int calculate_Numseq(string & tmp_DNA);

// Store the first line of db's text file into a tmp string,
// parse the DNA sequence, and push back the char into ourvector
// DNA_Seq accordingly.

void seq_Pushback(string & tmp_DNA, string & tmp_subDNA, int & DNA_number,
    ourvector < char > & DNA_Seq, ourvector < ourvector < char >> & All_Se);

// Read the name and numbers, use the information to create
// a struct DNA_Profile, and push DNA_Profile into ourvector Profiles,
// and continue the process until reaching the end of line of the text file.

void name_number_Pushback(string & tmp_str, string & tmp_substr,
    DNA_Profile & person, int & DNA_number);

// Open the text file using ifstream. and then use the above 3 functions
// to help completing the loading of database.

void load_Db(ourvector < ourvector < char >> & All_Seq,
    ourvector < DNA_Profile > & Profiles);

// Display name and numbers from ourvector profiles.

void display_Db(ourvector < DNA_Profile > & Profiles);

// Display DNA strand from ourvector DNA_Sample.

void display_Dna(ourvector < char > & DNA_Sample);

// Display the number results from ourvector process_Numbers

void display_ProcessNumbers(ourvector < ourvector < char >> & All_Seq,
    ourvector < int > & process_Numbers);

// Display all the information from above 3 functions.
// Noted that if the corresponding ourvector is empty,
// it will not display anything but an error message.

void display(ourvector < ourvector < char >> & All_Seq,
    ourvector < DNA_Profile > & Profiles, ourvector < char > & DNA_Sample,
    ourvector < int > & process_Numbers);

// This function loads the chars of DNA_Strand from a text,
// and then it will push each char into  ourvector DNA_Sample.

void load_Dna(ourvector < char > & DNA_Sample);

// Check if charactor count is equal to the length of the DNA sequence,
// and if the length is matched, increment str_count so we know how many DNA
// seq is found consecutively.

void check_Charcount(ourvector < ourvector < char >> & All_Seq,
    int & char_count, int & str_count, int & i, int & j);

// Comparing DNA Seq to the long DNA strand, and if the char is matched,
// increment char_count by 1.

void match_Char(ourvector < ourvector < char >> & All_Seq,
    ourvector < char > & DNA_Sample,
    ourvector < int > & process_Numbers,
    int & char_count, int & str_count, int & max_str, int & i);

// After each iteration of a specific DNA variation,
// if the str_count is greater than max_count then
// replace it, finally push back the conseutive
// found (max_count) into ourvector process_Numbers.

void create_ProcessNumbers(ourvector < ourvector < char >> & All_Seq,
    ourvector < char > & DNA_Sample,
    ourvector < int > & process_Numbers);

// Check if All_Seq and DNA_Sample is empty,
// if yes, display error message.
// Then, call create_ProcoessNumbers and
// start the comparing of the 2 ourvectors.

void process_Dna(ourvector < ourvector < char >> & All_Seq,
    ourvector < char > & DNA_Sample, ourvector < int > & process_Numbers);

// Compare DNA_Number in Profiles with
// process_Numbers from previous function.
// If the number of matching equal to the number
// of dna variation. Print out the
// the name in the specific struct DNA_Profile.

void compare_Numbers(ourvector < DNA_Profile > & Profiles,
    ourvector < int > & process_Numbers);

// Output error messages if ourvectors Profiles, DNA_Sample,
// and process_Numbers are empty. If not, call the compare_Numbers
// function and display the name of the
// result. If not numbers are match,
// display the message no result found.

void search_Person(ourvector < DNA_Profile > & Profiles,
    ourvector < char > & DNA_Sample, ourvector < int > & process_Numbers);

// This function print out the creative component function's menu,
// and it teaches you what to input.

void print_Infomenu();

// Ask the user to enter a name with certain ammount of numbers
// depended on the number of dna variation. Then store the information
// in the end of the according ourvectors.

void add_Db(ourvector < DNA_Profile > & Profiles);

// Ask the user to enter a string of DNA strand,
// then the string will be convered to one char and be
// bush into the end of ourvector DNA_Sample.

void add_Dna(ourvector < char > & DNA_Sample);

// This is the main creative component
// function that will be called in main.
// In this function you can choose to input name/numbers or dna.

void add_Info(ourvector < DNA_Profile > & Profiles,
    ourvector < char > & DNA_Sample);
int main() {
    string command;
    ourvector < char > DNA_Seq;
    ourvector < ourvector < char >> All_Seq;
    ourvector < DNA_Profile > Profiles;
    ourvector < char > DNA_Sample;
    ourvector < int > process_Numbers;
    cout << "Welcome to the DNA Profiling Application." << endl;
    cout << "Enter command or # to exit: ";
    cin >> command;
    while (command != "#") {
        if (command == "load_db") {
            load_Db(All_Seq, Profiles);
        } else if (command == "display") {
            display(All_Seq, Profiles, DNA_Sample, process_Numbers);
        } else if (command == "load_dna") {
            load_Dna(DNA_Sample);
        } else if (command == "process") {
            process_Dna(All_Seq, DNA_Sample, process_Numbers);
        } else if (command == "search") {
            search_Person(Profiles, DNA_Sample, process_Numbers);
        } else if (command == "add_info") {
            add_Info(Profiles, DNA_Sample);
        }
        cout << "Enter command or # to exit: ";
        cin >> command;
    }
    return 0;
}
int calculate_Numseq(string & tmp_DNA) {
    int DNA_number = 0;
    for (unsigned int i = 0; i < tmp_DNA.size(); i++) {
        if (tmp_DNA.at(i) == ',') {
            DNA_number = DNA_number + 1;
        }
    }
    DNA_number = DNA_number + 1;
    return DNA_number;
}
void seq_Pushback(string & tmp_DNA, string & tmp_subDNA, int & DNA_number,
    ourvector < char > & DNA_Seq, ourvector < ourvector < char >> & All_Seq) {
    for (int i = 0; i < DNA_number; i++) {
        if (tmp_DNA.find(',') != string::npos) {
            tmp_subDNA = tmp_DNA.substr(0, tmp_DNA.find(','));
        } else {
            tmp_subDNA = tmp_DNA;
        }
        for (unsigned int j = 0; j < tmp_subDNA.size(); j++) {
            DNA_Seq.push_back(tmp_subDNA.at(j));
        }
        All_Seq.push_back(DNA_Seq);
        if (tmp_DNA.find(',') != string::npos) {
            tmp_DNA.erase(0, tmp_DNA.find(',') + 1);
        } else {
            tmp_DNA.erase();
        }
        DNA_Seq.clear();
        tmp_subDNA.clear();
    }
}
void name_number_Pushback(string & tmp_str, string & tmp_substr,
    DNA_Profile & person, int & DNA_number) {
    for (int i = 0; i < DNA_number; i++) {
        if (tmp_str.find(',' != string::npos)) {
            tmp_substr = tmp_str.substr(0, tmp_str.find(','));
        } else {
            tmp_substr = tmp_str;
        }
        person.DNA_Number.push_back(stoi(tmp_substr));
        if (tmp_str.find(',' != string::npos)) {
            tmp_str.erase(0, tmp_str.find(',') + 1);
        } else {
            tmp_substr = tmp_str;
        }
    }
}
void create_Profiles(ourvector < DNA_Profile > & Profiles,
    ifstream & inFS, string & tmp_str, string & tmp_substr,
    DNA_Profile & person, int & DNA_number) {
    name_number_Pushback(tmp_str, tmp_substr, person, DNA_number);
    // Push the profile into an ourvector of profiles
    Profiles.push_back(person);
    while (!inFS.eof()) {
        person.name = "";
        person.DNA_Number.clear();
        getline(inFS, person.name, ',');
        if (person.name == "") {
            break;
        }
        getline(inFS, tmp_str);
        name_number_Pushback(tmp_str, tmp_substr, person, DNA_number);
        Profiles.push_back(person);
    }
}
void load_Db(ourvector < ourvector < char >> & All_Seq,
    ourvector < DNA_Profile > & Profiles) {
    cout << "Loading database..." << endl;
    // Clearing All_Seq and Profiles to be ready for second call.
    All_Seq.clear();
    Profiles.clear();
    string filename;
    cin >> filename;
    ifstream inFS;
    inFS.open(filename);
    if (!inFS.good()) {
        cout << "Error: unable to open '" << filename << "'" << endl;
        return;
    }
    string tmp_garbage = "";
    // tmp_garbage holds "name"
    getline(inFS, tmp_garbage, ',');
    string tmp_DNA;
    string tmp_subDNA;
    getline(inFS, tmp_DNA);
    // tracking how many DNA variation.
    int DNA_number = calculate_Numseq(tmp_DNA);
    ourvector < char > DNA_Seq;
    seq_Pushback(tmp_DNA, tmp_subDNA, DNA_number, DNA_Seq, All_Seq);
    DNA_Profile person;
    string tmp_str;
    string tmp_substr;
    getline(inFS, person.name, ',');
    getline(inFS, tmp_str);
    // Push back name, num into ourvec
    create_Profiles(Profiles, inFS, tmp_str, tmp_substr, person, DNA_number);
}
void display_Db(ourvector < DNA_Profile > & Profiles) {
    cout << "Database loaded: " << endl;
    for (int i = 0; i < Profiles.size(); i++) {
        cout << Profiles.at(i).name << " ";
        for (int j = 0; j < Profiles.at(i).DNA_Number.size(); j++) {
            if (j == Profiles.at(i).DNA_Number.size() - 1) {
                cout << Profiles.at(i).DNA_Number.at(j);
            } else {
                cout << Profiles.at(i).DNA_Number.at(j) << " ";
            }
        }
        cout << endl;
    }
}
void display_Dna(ourvector < char > & DNA_Sample) {
    cout << "DNA loaded: " << endl;
    for (int i = 0; i < DNA_Sample.size(); i++) {
        cout << DNA_Sample.at(i);
    }
    cout << endl;
}
void display_ProcessNumbers(ourvector < ourvector < char >> & All_Seq,
    ourvector < int > & process_Numbers) {
    cout << "DNA processed, STR counts: " << endl;
        for (int i = 0; i < process_Numbers.size(); i++) {
            for (int j = 0; j < All_Seq.at(i).size(); j++) {
                cout << All_Seq.at(i).at(j);
            }
            cout << ": " << process_Numbers.at(i) << endl;
        }
}
void display(ourvector < ourvector < char >> & All_Seq,
    ourvector < DNA_Profile > & Profiles,
    ourvector < char > & DNA_Sample,
    ourvector < int > & process_Numbers) {
    if (Profiles.size() > 0) {
        display_Db(Profiles);
    } else {
        cout << "No database loaded.";
    }
    cout << endl;
    if (DNA_Sample.size() > 0) {
        display_Dna(DNA_Sample);
    } else {
        cout << "No DNA loaded." << endl;
    }
    cout << endl;
    if (process_Numbers.size() > 0) {
        display_ProcessNumbers(All_Seq, process_Numbers);
    } else {
        cout << "No DNA has been processed." << endl;
    }
}
void load_Dna(ourvector < char > & DNA_Sample) {
    cout << "Loading DNA..." << endl;
    DNA_Sample.clear();
    string filename;
    cin >> filename;
    ifstream inFS;
    inFS.open(filename);
    if (!inFS.good()) {
        cout << "Error: unable to open '" << filename << "'" << endl;
    }
    string tmp_str;
    getline(inFS, tmp_str);
    for (unsigned int i = 0; i < tmp_str.size(); i++) {
        DNA_Sample.push_back(tmp_str.at(i));
    }
}
void check_Charcount(ourvector < ourvector < char >> & All_Seq,
    int & char_count, int & str_count, int & i, int & j) {
    if (char_count == All_Seq.at(i).size()) {
        str_count = str_count + 1;
        j = j + All_Seq.at(i).size() - 1;
    }
}
void match_Char(ourvector < ourvector < char >> & All_Seq,
    ourvector < char > & DNA_Sample,
    ourvector < int > & process_Numbers,
    int & char_count, int & str_count, int & max_str, int & i) {
    for (int j = 0; j < DNA_Sample.size(); j++) {
        int tmp_index = j;
            for (int k = 0; k < All_Seq.at(i).size(); k++) {
                if (tmp_index < DNA_Sample.size() &&
                DNA_Sample.at(tmp_index) == All_Seq.at(i).at(k)) {
                    char_count = char_count + 1;
                    // tmp_index is an independ value that
                    // keeps track for next if a char is match.
                    tmp_index = tmp_index + 1;
                } else {
                    if (str_count > max_str) {
                        max_str = str_count;
                    }
                    str_count = 0;
                    char_count = 0;
                    break;
                }
            }
            check_Charcount(All_Seq, char_count, str_count, i, j);
            char_count = 0;  // Reset char_count after k iteration
        }
}
void create_ProcessNumbers(ourvector < ourvector < char >> & All_Seq,
    ourvector < char > & DNA_Sample,
    ourvector < int > & process_Numbers) {
    int char_count = 0;
    int str_count = 0;
    int max_str = 0;
    cout << "Processing DNA..." << endl;
    for (int i = 0; i < All_Seq.size(); i++) {
        match_Char(All_Seq, DNA_Sample, process_Numbers,
        char_count, str_count, max_str, i);
        if (char_count == All_Seq.at(i).size()) {  // Counting last Sample
            str_count = str_count + 1;
        }
        if (str_count > max_str) {
            max_str = str_count;
        }
        str_count = 0;
        process_Numbers.push_back(max_str);
        max_str = 0;
    }
}
void process_Dna(ourvector < ourvector < char >> & All_Seq,
    ourvector < char > & DNA_Sample,
    ourvector < int > & process_Numbers) {
    if (All_Seq.size() == 0) {
        cout << "No database loaded." << endl;
        return;
    }
    if (DNA_Sample.size() == 0) {
        cout << "No DNA loaded." << endl;
        return;
    }
    process_Numbers.clear();
    create_ProcessNumbers(All_Seq, DNA_Sample, process_Numbers);
}
void compare_Numbers(ourvector < DNA_Profile > & Profiles,
    ourvector < int > & process_Numbers) {
    int correct_count = 0;
    cout << "Searching database..." << endl;
    for (int i = 0; i < Profiles.size(); i++) {
        for (int j = 0; j < Profiles.at(i).DNA_Number.size(); j++) {
            if (Profiles.at(i).DNA_Number.at(j) == process_Numbers.at(j)) {
                correct_count = correct_count + 1;
            } else {
                correct_count = 0;
                break;
            }
        }
        if (correct_count == Profiles.at(i).DNA_Number.size()) {
            cout << "Found in database!  DNA matches: "
            << Profiles.at(i).name << endl;
            return;
        }
    }
    cout << "Not found in database." << endl;
}
void search_Person(ourvector < DNA_Profile > & Profiles,
    ourvector < char > & DNA_Sample,
    ourvector < int > & process_Numbers) {
    if (Profiles.size() == 0) {
        cout << "No database loaded." << endl;
        return;
    }
    if (DNA_Sample.size() == 0) {
        cout << "No DNA loaded." << endl;
        return;
    }
    if (process_Numbers.size() == 0) {
        cout << "No DNA processed." << endl;
        return;
    }
    compare_Numbers(Profiles, process_Numbers);
}
void print_Infomenu() {
    cout << "WARNING! You must load a database and dna first in order"
    "for this feature to work!" << endl;
    cout << "----------------" << endl;
    cout << "Welcome, you are allowed to add additional"
    "Name/Numbers and DNA here!" << endl;
    cout << "Enter \"nn\" to input additional people, \"dna\" to input"
    "additional DNA bases (ACGT), and # to quit." << endl;
    cout << "Enter a command to add manually: ";
}
void add_Db(ourvector < DNA_Profile > & Profiles) {
    cout << "Please enter a valid name and"
    "correct number of numbers." << endl;
    DNA_Profile person;
    string person_name;
    int num_DNA;
    cout << "Enter a name: ";
    cin.ignore();
    getline(cin, person_name);
    cout << "This is person_name: " << person_name << endl;
    person.name = person_name;
    cout << endl;
    for (int i = 0; i < Profiles.at(0).DNA_Number.size(); i++) {
        cout << "Enter a number: ";
        cin >> num_DNA;
        person.DNA_Number.push_back(num_DNA);
    }
    Profiles.push_back(person);
    cout << "Name and numbers are added sucessfully!" << endl;
}
void add_Dna(ourvector < char > & DNA_Sample) {
    string bases_DNA;
    cout << "Enter DNA bases(ex. ACGTTAGCATGCAT........): ";
    cin >> bases_DNA;
    for (unsigned int i = 0; i < bases_DNA.size(); i++) {
        char tmp_char;
        tmp_char = bases_DNA.at(i);
        DNA_Sample.push_back(tmp_char);
    }
    cout << "Additional DNA are added successfully!" << endl;
}
void add_Info(ourvector < DNA_Profile > & Profiles,
    ourvector < char > & DNA_Sample) {
    print_Infomenu();
    string command;
    cin >> command;
    cout << endl;
    while (command != "#") {
        if (command == "nn") {
            add_Db(Profiles);
        } else if (command == "dna") {
            add_Dna(DNA_Sample);
        }
        cout << "What else do you want to do (# to quit): ";
        cin >> command;
        cout << endl;
    }
}

