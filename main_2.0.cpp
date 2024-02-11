
#include <iostream>
#include <string>
#include <vector> 

using namespace std;

class Little
{
    private:
//VARIABLES:
    string name;
    vector<string> pref_survey;
    bool free = true;
    //Big* curr_pair1;

    public:
//CONSTRUCTOR:
    Little (const string& name_, const vector<string>& pref_survey_)
        : name(name_), pref_survey(pref_survey_) {
            cout<< "\nLittle constructor for " << name <<endl;
        }

//FUNCTIONS:
string get_name()
{
    return name;
}
vector<string> get_pref_survey()
{
    return pref_survey;
}
//input: true or false.
//result: Update free status.
    void change_free_status(bool new_status) {
        free = new_status;
    }

};

class Big
{
    private:
//VARIABLES:
    string name;
    vector<string> pref_survey;
    int matches = 0;
    Little* curr_pair1;
    Little* curr_pair2;

    public:
//CONSTRUCTOR:
    Big (const string& name_, const vector<string>& pref_survey_)
        : name(name_), pref_survey(pref_survey_) {
            cout<< "\nBig constructor for " << name <<endl;
        }
//FUNCTIONS:
string get_name()
{
    return name;
}
//input: Name that is being searched for.
//output: Preference number of name.
    int get_pref_rank(string& little_name){
        for (int i = 0; i < pref_survey.size(); i++)
        {
            if (pref_survey[i] == little_name)
            {
                return i; // Return the ranking of name specified
            }
        }
        // If the little is not found:
        return -1;
    }
 
//result: Update number of matches.
    void change_matches_status() {
        matches++;
    }

};


void clean_data(vector<Big>& bigs, vector<Little>& littles)
{
    //not sure if needed yet
}

// Function that matchs Bigs and Littles:
//input: Vector of all Bigs and vector of all Littles. 
void match_bigs_littles(vector<Big>& bigs, vector<Little>& littles)
{
    cout<< "\nMatch function working!" <<endl;

    bool new_changes_made = 1;
    while(new_changes_made)
    {
        new_changes_made = 0; // Set to no changes have been made yet.

        for (int i = 0; i < littles.size(); i++)
        { // For each Little:
            cout<< "\nLittle: " << littles[i].get_name() <<endl;
            for (int j = 0; j < littles[i].get_pref_survey().size(); j++)
            { // For each Big in Littles pref_survey:
                cout<< "\nBig :" << bigs[j].get_name() <<endl;
            }

        }
    }

}


int main()
{
    vector<Big> bigs = {{"Big1", {"Little3", "Little1", "Little2"}},
                        {"Big2", {"Little2", "Little1", "Little3"}},
                        {"Big3", {"Little1", "Little3", "Little2"}},
                        {"Big4", {"Little1", "Little3", "Little2"}},
                        {"Big5", {"Little1", "Little3", "Little2"}}};

    vector<Little> littles = {{"Little1", {"Big2", "Big1", "Big3"}},
                              {"Little2", {"Big3", "Big1", "Big2"}},
                              {"Little3", {"Big2", "Big1", "Big3"}}};



    match_bigs_littles(bigs, littles);


    return 0; 
}


