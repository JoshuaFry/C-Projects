#include <iostream>
#include <map>
#include <fstream>

using namespace std;

class State{

public:
    string id;
    map<string, string> transits;

    explicit State(string id){
        this->id = id;
    }
};

int main(int argc, char *argv[]) {
    if(argc != 4){
        cout << "Incorrect # of arguments" << endl;
        exit(0);
    }

    map <string, State *> states;

    //Open user's Spec file
    ifstream input;
    input.open(argv[1], ifstream::in);
    if(!input.is_open()){
        cout << "Spec failed to open." << endl;
        return 0;
    }

    string key;
    string subKey;
    string value;
    map<string, State *>::iterator mit;

    //Build Finite State Machine off Spec File
    while(input >> key >> subKey >> value){
        mit  = states.find(key);
        if(mit == states.end()){
            //cout << "State is new" << endl;
            State *holder = new State(key);
            holder->transits.insert((make_pair(subKey, value)));
            states.insert((make_pair(key, holder)));

        }else{
            //cout << "State is old: " << key << endl;
            mit->second->transits.insert((make_pair(subKey, value)));
        }
    }

    //Closing Spec File
    input.close();

    cout << "STATE MACHINE:" << endl;
    //Prints out State Machine
    for(mit = states.begin(); mit != states.end(); mit++){
        string state = mit->first;
        map<string, string>::iterator it;
        map<string, string> tr = mit->second->transits;

        cout << state << ": ";
        for(it = tr.begin(); it != tr.end(); it++){
            cout << "(" << it->first << ", " << it->second << ")  ";
        }
        cout << endl;
    }

    cout << "==================================" << endl << endl;

    //Grab and test for user starting state
    string start = argv[2];
    mit = states.find(start);
    if(mit == states.end()){
        cout << "Starting State does not exist" << endl;
        return 0;
    }

    //Grab and test for user final state
    string finalState = argv[3];
    mit = states.find(finalState);
    if(mit == states.end()){
        cout << "Final State does not exist" << endl;
        return 0;
    }

    State *currentState = states[start];
    map<string, string>::iterator it;

    string test;
    cout << "Enter Test: ";
    string path;

    //Read in user input and Transition through State Machine
    while(cin >> test){
        //cout << test << endl;
        it  = currentState->transits.find(test);
        if(it == currentState->transits.end()){
            //cout << "State:" << currentState->id << " has no path " << test << endl;
            path += currentState->id  + "* ";
        }else{

            string str = test;
            string nextState = currentState->transits[str];
            mit = states.find(nextState);
            if(mit == states.end()){
                //cout << "Next State is not in Machine." << endl;
                State *ugh = new State(test);
                states.insert((make_pair(test, ugh)));
                currentState = ugh;
            } else{
                currentState = states[nextState];
                path += nextState + " ";
            }
        }
    }
    cout << "PATH: " << path;

    if(currentState->id == finalState){
        cout << endl << "ACCEPTED!" << endl;
    }else{
        cout << endl << "REJECTED!" << endl;
    }

    //DeAllocate map memory of States
    for(mit = states.begin(); mit != states.end(); mit++){
        delete mit->second;
    }

    return 0;
}