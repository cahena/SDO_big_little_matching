
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Little;
struct Big;

class Little
{
    private:
//VARIABLES:
    string name;
    vector<string> pref_survey;
    bool free = true;
    string curr_pair = "n/a";

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
    bool get_free()
    {
        return free;
    }
    string get_pair()
    {
        return curr_pair;
    }
    void set_curr_pair(string bigs_name)
    {
        cout<< "\nset_curr_pair() called." <<endl;
        curr_pair = bigs_name; 
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
    string curr_pair1 = "n/a";
    string curr_pair2 = "n/a";

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
    int get_matches()
    {
        return matches;
    }
    string get_pair()
    {
        return curr_pair1;
    }
    void set_curr_pair1(string littles_name)
    {
        cout<< "\nset_curr_pair1() called." <<endl;
        curr_pair1 = littles_name; 
    }
//input: Name that is being searched for.
//output: Preference number of name.
    int get_pref_rank(string little_name){
        for (int i = 0; i < pref_survey.size(); i++)
        {
            if (pref_survey[i] == little_name)
            {
                return i; // Return the ranking of name specified
            }
        }
        // If the little is not found:
        return 99;
    }
//input: 1 or -1 for inc. or dec. matches number. 
//result: Update number of matches.
    void change_matches_status(int x) {
        matches =+ x;
        //cout<<"\nName and matches: " << name << " has " << matches << " matches" << endl;
    }

    int get_curr_pair_position(vector<Little>& littles)
    {
        for (int i = 0; i < littles.size(); i++)
        {
            if (curr_pair1 == littles[i].get_name())
            {
                return i; 
            }
        }
        // If the little is not found:
        return 99;
    }

};

//GENERAL FUNCTIONS:
void clean_data(vector<Big>& bigs, vector<Little>& littles)
{
    //not sure if needed yet
}

void pair_little_big(Little& lil, Big& big)
{
    // Check if the Big is already paired with another little
    if (big.get_pair() != "n/a") {
        cout << "Big is already paired with " << big.get_pair() << ". Cannot pair with " << lil.get_name() << endl;
        return;
    }

    cout<< "\nPAIRED inside pair_little_big func: " << lil.get_name() << " - " << big.get_name() <<endl;

    // Update Little
    lil.change_free_status(false);
    lil.set_curr_pair(big.get_name());

    // Update Big
    big.change_matches_status(1);
    big.set_curr_pair1(lil.get_name()); 

}

void unpair_little_big(Little& lil, Big& big)
{
    cout<< "\nUN-PAIRED inside unpair_little_big func: " << lil.get_name() << " - " << big.get_name() <<endl;
    // Update Little
    lil.change_free_status(true);
    lil.set_curr_pair("n/a");

    // Update Big
    big.change_matches_status(-1);
    big.set_curr_pair1("n/a"); 
}

// Function that matchs Bigs and Littles:
//input: Vector of all Bigs and vector of all Littles. 
void match_bigs_littles(vector<Big>& bigs, vector<Little>& littles)
{
    cout << "\nMatch function working!" << endl;

    bool changes_made = true;
    while (changes_made)
    {
        changes_made = false;

        for (int i = 0; i < littles.size(); i++)
        {// For each Little in vector littles:
            cout << "\n\nLITTLE being iterated: " << littles[i].get_name() << endl;

            if (!littles[i].get_free())
            {
                cout << "\n(1)Little not free, therefore skipped." << endl;
                continue;
            }

            for (int j = 0; j < littles[i].get_pref_survey().size(); j++)
            {// For each Big in Littles[i]'s pref_survey:
                cout << "\nBIG being iterated: " << (littles[i].get_pref_survey())[j] << endl;

                int proposed_big_int;// Keep track of the Big being proposed to:
                string bigs_name = littles[i].get_pref_survey()[j];
                for (int k = 0; k < bigs.size(); k++)
                {
                    if (bigs[k].get_name() == bigs_name)
                    {
                        proposed_big_int = k;
                    }
                }

                if (bigs[proposed_big_int].get_matches() < 1)
                {// If Big has no matches yet, pair them:
                    cout << "\nBig has less than 1 match." << endl;
                    pair_little_big(littles[i], bigs[proposed_big_int]);
                    changes_made = true;
                    break; // Break the loop after pairing so that there's no further iterations for this little
                }
                else
                {// If Big already has a match, compare Big's preferences:
                    int curr_pair_position = bigs[proposed_big_int].get_curr_pair_position(littles);
                    int curr_little_pref_rank = bigs[proposed_big_int].get_pref_rank(littles[i].get_name());
                    int curr_pair_pref_rank = bigs[proposed_big_int].get_pref_rank(bigs[proposed_big_int].get_pair());

                    cout << "Comparing preferences" << endl;
                    if (curr_little_pref_rank < curr_pair_pref_rank)
                    {// If the current little is higher ranked on the Big's pref_survey than the Bigs current pair, unpair the old little, pair the new little:
                        unpair_little_big(littles[bigs[proposed_big_int].get_curr_pair_position(littles)], bigs[proposed_big_int]);
                        pair_little_big(littles[i], bigs[proposed_big_int]);
                        changes_made = true;
                        cout << "The bigs current pair is: " << bigs[proposed_big_int].get_pair() << endl;
                        break; // Break the loop after unpairing and pairing to avoid further iterations for this little
                    }
                }
            }
        }
    }
}


int main()
{
    vector<Big> bigs = {{"Big1", {"Little3", "Little4", "Little2"}},
                        {"Big2", {"Little2", "Little4", "Little3"}},
                        {"Big3", {"Little1", "Little3", "Little2"}},
                        {"Big4", {"Little1", "Little3", "Little2"}},
                        {"Big5", {"Little3", "Little2", "Little1"}}};

    vector<Little> littles = {{"Little1", {"Big5", "Big1", "Big3"}},
                              {"Little2", {"Big5", "Big1", "Big2"}},
                              {"Little3", {"Big5", "Big1", "Big3"}},
                              {"Little4", {"Big2", "Big1", "Big3"}},
                              {"Little5", {"Big2", "Big1", "Big3"}}, 
                              {"Little6", {"Big2", "Big1", "Big3"}}};



    match_bigs_littles(bigs, littles);

    cout<< "\n--LITTLE PAIRS--" <<endl;
    for (int i = 0; i < littles.size(); i++)
    {
        cout<< littles[i].get_name() << "--" << littles[i].get_pair() <<endl;
    }
    cout<< "\n--BIG PAIRS--" <<endl;
    for (int i = 0; i < bigs.size(); i++)
    {
        cout<< bigs[i].get_name() << "--" << bigs[i].get_pair() <<endl;
    }


    return 0; 
}


