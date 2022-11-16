#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>


using namespace std;

class Process
{
protected:
    string name;
    int ID;
    int memUse;
public:
    Process(){};
    Process(string n , int id , int mem);
    string getName(){return name;}
    int getId(){return ID;}
    int getMem(){return memUse;}
};
Process :: Process(string n, int id , int mem)
{
    name = n;
    ID = id ;
    memUse = mem;
}
class TaskManager
{
protected:
    vector<Process> list;
    fstream  file;
public:
    void print();
    void loadProcesses();
    void nameSorting();
    void idSorting();
    void memSorting();
};
void TaskManager :: print()
{
    for(auto it : list)
    {
        cout << left << setw(30) << it.getName()
             << right << setw(10) << it.getId()
             << right << setw(10) << it.getMem() << '\n';
    }
}
void TaskManager :: loadProcesses()
{
    string pName , temp, pId , pMem;
    vector<string> words;
    int id , Mem;

    file.open("tl.txt", ios:: out);
    file.close();
    system("tasklist >> tl.txt");
    file.open("tl.txt", ios:: in);

    while(file >> temp)
    {
        words.push_back(temp);
    }
    for(int i = 15  ;i < words.size() - 1; i += 6)
    {
        pName = words[i];
        if(pName == "Memory")
        {
            pName += words[i+1];
            i++;
        }
        pId = words[i+1];
        pMem = words[i+4];
        int pos = pMem.find(',');
        if(pMem.find(',') != string:: npos)
        {
            temp = pMem.substr(0 , pos);
            pMem = temp + pMem.substr(pos+1 , pMem.size()-1);
        }
        stringstream s;
        s << pId;
        s >> id;
        stringstream ss;
        ss << pMem;
        ss >> Mem;
        Process pr(pName , id , Mem);
        list.push_back(pr);
    }
    file.close();
}

void TaskManager :: nameSorting()
{
    sort(list.begin(),list.end() , [](Process a , Process b){return a.getName() < b.getName();});
}
void TaskManager :: idSorting()
{
    sort(list.begin(),list.end() , [](Process a , Process b){return a.getId() < b.getId();});
}
void TaskManager :: memSorting()
{
    sort(list.begin(),list.end() , [](Process a , Process b){return a.getMem() < b.getMem();});
}
int main() {
    TaskManager t;
    t.loadProcesses();
    t.nameSorting();
    t.idSorting();
    t.memSorting();
    t.print();

    return 0;
}
