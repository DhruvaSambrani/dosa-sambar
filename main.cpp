#include <string>
#include <iomanip>
#include <fstream>
#include <ncurses.h>
#include <vector>

using namespace std;

string getinput(){
    int ch;
    string input;
    while (1){
        ch = getch();
        if (ch == '\n'){
            break;
        }
        if (ch == KEY_BACKSPACE){
            if (!input.empty()){
                input.pop_back();
                addch(' ');
                addch('\b');
            }
        }
        else{
            input.push_back(ch);
        }
    }
    return input;
}


class MdCheckBox {
    bool checked;
    string value;

public:
    void toggleCheck(){
        checked = !checked;
    }
    string show(){
        string lb = "- [";
        string rb = "] ";
        string xb = "x";
        string em = " ";
        return lb+(checked?xb:em)+rb+value;
    }
    static string yamlblock;
    static void insert(vector<MdCheckBox> &mdarr){
        mdarr.push_back(MdCheckBox(false, getinput()));
    }
    static void remove(vector<MdCheckBox> &mdarr, int pos){
        mdarr.erase(mdarr.begin()+pos);
    }
    static void parsefile(char filename[], vector<MdCheckBox> &mdarr){
        ifstream ifile(filename);
        string str, yamlstr;
        string yamlsep = "---";
        string nl = "\n"; 
        int yaml = 0;
        while(getline(ifile, str)){
            if(yaml<2) {
                if(str==yamlsep){
                    yaml++;
                }
                yamlstr += str;
                yamlstr += nl;
            } else if(!str.empty()) {
                mdarr.push_back(MdCheckBox(str[3]=='x', str.substr(6)));
            }
        }
        MdCheckBox::yamlblock = yamlstr;
    }

    static void writefile(char filename[], vector<MdCheckBox> &mdarr){
        ofstream ofile(filename);
        ofile << MdCheckBox::yamlblock;
        ofile << endl;
        for(int i=0; i < mdarr.size(); ++i){
            ofile << mdarr[i].show().c_str();
            ofile << endl;
        }
    }

    MdCheckBox(bool chk, string val){
        this->checked = chk;
        this->value = val;
    }
};

string MdCheckBox::yamlblock = "";

void show(vector<MdCheckBox> &mdarr, int active){
    for(int i=0; i<mdarr.size(); ++i){
        if(i==active){
            attron(A_BOLD);
        } else {
            attron(A_DIM);
        }
        addstr(mdarr[i].show().c_str());
        attroff(A_BOLD | A_DIM);
        addstr("\n");
    }
}

void init(){
    initscr();
    raw();
    cbreak();
    keypad(stdscr, TRUE);
}

int main(){
    init();
    int active=0;
    bool st=true;
    vector<MdCheckBox> mdarr;
    char fn[] = "test.md";
    MdCheckBox::parsefile(fn, mdarr);
    while(st){
        clear();
        show(mdarr, active);
        printw(": ");
        refresh();
        int input = getch();
        switch(input){
            case 'x':{
                mdarr[active].toggleCheck();
                break;
            }
            case KEY_DOWN:
            case 'k':{
                active=(active+1)%mdarr.size();
                break;
            }
            case KEY_UP:
            case 'j':{
                active=(mdarr.size()+active-1)%mdarr.size();
                break;
            }
            case 'd':{
                MdCheckBox::remove(mdarr, active);
                break;
            }
            case 'i':{
                clear();
                addstr("Enter value: ");
                MdCheckBox::insert(mdarr);
                break;
            }
            case 'w':{
                MdCheckBox::writefile(fn, mdarr);
                break;
            }
            case 'g':{
                system("git add . && git commit -m \"test\"");
            }
            case 'q':{
                st = false;
                break;
            }
            default:
                printw("Invalid input");
        }
    }
    endwin();
    return 0;
}
