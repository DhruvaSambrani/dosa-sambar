#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

class MdCheckBox {
    bool checked;
    string value;

public:
    void toggleCheck(){
        checked = !checked;
    }
    string show(){
        string lb = "[";
        string rb = "] ";
        string xb = "x";
        string em = " ";
        return lb+(checked?xb:em)+rb+value;
    }
    MdCheckBox(bool chk, string val){
        this->checked = chk;
        this->value = val;
    }
    MdCheckBox(){
        this->checked = false;
        this->value = "123";
    }
};
int parsefile(char filename[], MdCheckBox mdarr[]){
    ifstream ifile(filename);
    string str;
    string yamlsep = "---";
    int size = 0;
    int yaml = 0;
    while(getline(ifile, str)){
        if(str==yamlsep){
            cout << "yamlblock" << endl;
            yaml++;
        } else {
            if(yaml == 2){
                cout << str << endl;
                mdarr[size++] = MdCheckBox(str[3]=='x', str.substr(6));
            }
        }
    }
    return size;
}


void show(MdCheckBox mdarr[], int size, int active){
    cout << "\e[2J";
    for(int i=0; i<size; ++i){
        if(i==active){
            cout << "\e[1;32m";
        }
        cout << mdarr[i].show() << "\e[0m" << endl;
    }
}

int main(){
    char input;
    int active=0, size;
    bool st=true;
    MdCheckBox mdarr[20];
    char fn[] = "test.md";
    size = parsefile(fn, mdarr);
    while(st){
        show(mdarr, size, active);
        cout << endl << ": ";
        cin >> input; 
        switch(input){
            case 'x':{
                mdarr[active].toggleCheck();
                break;
            }
            case 'k':{
                active=(active+1)%size;
                break;
            }
            case 'l':{
                active-=1;
                break;
            }
            case 'q':{
                st = false;
                break;
            }
            default:
                cout<<"Invalid input"<<endl;             
        }
    }
    return 0;
}
