#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
using namespace std;

const int ALPHABET_SIZE = 27;

string convertToString(char* a)
{
    string s=a;
    return s;
}

void link(string domainName)
{
    string msg="start http://"+domainName;
    const char* hyper = msg.c_str();
    system(hyper );
}

string randomNumber()
{
    string random="";
    for(int i=0;i<4;i++)
    {
        if(i!=0)
            random=random+".";
        int val=rand()%255;
        random=random+to_string(val);
    }
    return random;
}

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};

struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
    pNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
    return pNode;
}

void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index;
        if(key[i]=='.')
            index=26;
        else
            index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
}

bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index;
        if(key[i]=='.')
            index=26;
        else
            index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl->isEndOfWord);
}

int main()
{
    char line[50];
    char *temp,*temp1,*temp2;
    int count=0,cnt=0,sizes,counter=0;

    struct TrieNode *root = getNode();
    struct TrieNode *root1 = getNode();

    ifstream fin1;
    fin1.open("TTL.csv",ios::in);                                                            //inserting the cache file to trie node
    while(fin1.getline(line,50))
    {
        if(cnt!=0)
        {
            temp=strtok(line,",");
            string finals=convertToString(temp);
            insert(root1,finals);
        }
        else
        {
            cnt++;
        }
    }
    fin1.close();

    ifstream fin;
    fin.open("dns1.csv",ios::in);
    while(fin.getline(line,50))                                                              //inserting domain name server file to trie node
    {
        if(count!=0)
        {
            temp=strtok(line,",");
            string finals=convertToString(temp);
            insert(root,finals);
        }
        else
        {
            count++;
        }
    }
    fin.close();

    cout<<"\n\n\n\n\n\t\t\t***********************************************************************************\n"<<endl;
    char output[][32] = {"Not present in trie", "Present in trie"};                                 //for output
    string domainName,value,ip,value1,value2;
    int count1=0,count2=1;

    cout<<"\t\t\tEnter the domain name server you want to visit through :";
    cout<<"\n\t\t\t-------------------------------------------------------- ";
    cin>>domainName;

    transform(domainName.begin(),domainName.end(),domainName.begin(),::tolower);                    //trasform all the formats to lowercase

    if(strcmp(output[search(root1,domainName)],"Present in trie")==0)
    {
        count1=-1;
    }
    else if(strcmp(output[search(root,domainName)],"Present in trie")==0)
    {
        count1=0;
    }
    else
    {
        count1=1;
    }

//DEPENDING ON THE COUNT THERE ARE THREE CASE
//CASE 1:SINCE IT IS AVAILABLE IN CACHE ,ACCESSING FROM THE CACHE!!!

    if(count1==-1)
    {
        ifstream fin2;
        fin2.open("TTL.csv",ios::in);
        while(fin2.getline(line,50))
        {
            temp=strtok(line,",");
            string finals=convertToString(temp);
            if(finals==domainName)
            {
                temp=strtok(NULL,",");
                string val=convertToString(temp);
                cout<<"\n\t\t\t@WOW!!! YOUR WEBSITE IS FREQUENTLY USED !!!!"<<endl;
                cout<<"\n\t\t\t@YOUR WEBSITE "<<domainName<<" IS READY TO WORK !!!!"<<endl;
                cout<<"\n\t\t\t@IP ADDRESS :"<<val<<" IS A VALID ONE !!!!"<<endl;
                cout<<"\n\n\t\t\t***********************************************************************************"<<endl;
                sleep(5);
                link(domainName);
            }
        }
        fin2.close();
    }

//CASE 2: SINCE IT IS NOT AVAILABLE IN CACHE ACCESING IN MAIN SERVER!!!

    else if(count1==0)
    {
        ifstream fin;
        fin.open("dns1.csv",ios::in);
        while(fin.getline(line,50))
        {
            temp=strtok(line,",");
            string finals=convertToString(temp);
            if(finals==domainName)
            {
                temp=strtok(NULL,",");
                string val=convertToString(temp);
                cout<<"\n\t\t\t@YOUR WEBSITE "<<domainName<<" IS READY TO WORK !!!!"<<endl;
                cout<<"\n\t\t\t@IP ADDRESS :"<<val<<" IS A VALID ONE !!!!"<<endl;
                cout<<"\n\n\t\t\t***********************************************************************************"<<endl;
                sleep(5);
                link(domainName);
            }
        }
        fin.close();
    }

//CASE 3:SINCE IT IS NOT AVAILABLE CREATING A NEW WEBPAGE WITH IP ADDRESS!!!

    else if(count1==1)
    {
        ofstream fout;
        fout.open("dns1.csv",ios::out | ios::app);
        l1:ip=randomNumber();
        ifstream fin;
        fin.open("dns1.csv",ios::in);
        while(fin.getline(line,50))
        {
            temp=strtok(line,",");
            temp=strtok(NULL,",");
            string val=convertToString(temp);
            if(val==ip)
            {
                goto l1;
            }
        }
        fin.close();

        cout<<"\n\t\t\t@NEW WEB PAGE IS CREATED ,EXPLORE IT!!!"<<endl;
        cout<<"\n\t\t\t@YOUR WEBSITE "<<domainName<<" IS READY TO WORK !!!!"<<endl;
        cout<<"\n\t\t\t@IP ADDRESS :"<<ip<<" IS A VALID ONE !!!!"<<endl;
        cout<<"\n\n\t\t\t***********************************************************************************"<<endl;
        sleep(5);
        link(domainName);
        fout << domainName<<","<< ip << endl;
        fout.close();

        ifstream fin1;
        ofstream f1;
        fin1.open("TTL.csv",ios::in);
        f1.open("New.csv",ios::out );
        while(fin1.getline(line,50))
        {
            if(counter==1)
            {
                counter++;
            }
            else
            {
                temp1=strtok(line,",");
                string val1=convertToString(temp1);
                temp2=strtok(NULL,",");
                string val2=convertToString(temp2);
                f1 << val1 << "," << val2 << endl;
                counter++;
            }
        }
        f1<< domainName<<","<< ip << endl;
        fin1.close();
        f1.close();
        remove("TTL.csv");
        rename("New.csv","TTL.csv");

    }
    return 0;
}
