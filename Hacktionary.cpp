//   **************************************************************************
//   *                                                                        *
//   *  This program is free software: you can redistribute it and/or modify  *
//   *  it under the terms of the GNU General Public License as published by  *
//   *  the Free Software Foundation, either version 3 of the License, or     *
//   * (at your option) any later version.                                    *
//   *                                                                        *
//   *  This program is distributed in the hope that it will be useful,       *
//   *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
//   *  MERCHANTABILITY || FITNESS FOR A PARTICULAR PURPOSE.  See the         *
//   *  GNU General Public License for more details.                          *
//   *                                                                        *
//   *  You should have received a copy of the GNU General Public License     *
//   *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
//   *                                                                        *
//   *         (C) Arvind Kumar 2013 . All rights reserved                    *
//   **************************************************************************

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

void cls(){
    #if defined (__WIN32__)
        system("CLS");
    #else
        #if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
            system("clear");
        #endif
    #endif
}

int getNumber(string prompt){
    string inp="";
    int num;
    do{
        cout << prompt;
        cin >> inp;
        num = atoi(inp.c_str());
    }while(num==0);
    return num;
}

int getInt(string prompt){
    string inp="";
    int num;
    cout << prompt;
    cin >> inp;
    num = atoi(inp.c_str());
    return num;
}

char* setArray(int arr[]){
    int h=0;
    char* dupl=new char[128];
    for (int i=0;i<sizeof(arr);i+=2){
        for (int j=arr[i];j<=arr[i+1];j++){
            dupl[h]=j;
            h++;
        }
    }
    return dupl;
}

char* getCharset(int &len){
    cout << "\nType a continuous string of characters without spaces.\nThe characters may repeat.\n\n";
    string inp;
    cin >> inp;
    len = inp.length();
    char* arr=new char[len];
    for (int i=0;i<len;i++){
        arr[i]=inp[i];
    }
    return arr;
}

void write(FILE *file,char *cset,int len,int i,int level,string word){
    level++;
    for (int j=0;j<len;j++){
        word=string(word)+cset[j];
        if (level<i){
            write(file,cset,len,i,level,word);
        }
        else{
            word=string(word)+"\n";
            fputs(word.c_str(),file);
        }
    }
}

int main(){
    string trash="";
    char *cset;
    int len;
    string append="";
    string prepend="";
    int start;
    int stop;
    long double space=0;
    long double combos=0;

    cout << "                  Hacktionary v1.0\n\n";
    cout << "*******************************************************\n\n";
    cout << "Your portable brute-force dictionary generating tool.\n\n";
    cout << "Note that this project is open source and you can read\n";
    cout << "more about it or access the source code at it's github:\n";
    cout << "       http://github.com/EnKrypt/Hacktionary\n\n";
    cout << "*******************************************************\n\n";

    cout << "Press ENTER to continue : ";
    getline(cin, trash);
    cls();

    cout << "                CHARACTER SETS\n\n";
    cout << "1. Letters (All Caps) : A-Z\n";
    cout << "2. Letters (No Caps) : a-z\n";
    cout << "3. Letters (Both cases) : A-Z & a-z\n";
    cout << "4. Numbers Only : 0-9\n";
    cout << "5. Alphanumeric (Letters in Caps) : A-Z & 0-9\n";
    cout << "6. Alphanumeric (No letter in Caps) : a-z & 0-9\n";
    cout << "7. Alphanumeric (Both cases) : A-Z & a-z & 0-9\n";
    cout << "8. Alphanumeric + Symbols : ASCII(32)-ASCII(126)\n";
    cout << "9. Full ASCII : ASCII(0)-ASCII(127)\n";
    cout << "10. Define Custom Range\n\n";
    int ch=getNumber("Choose an option : ");

    switch(ch){
        case 1:{
            int arr[]={65,90};
            cset=setArray(arr);
            len=26;
            break;
        }
        case 2:{
            int arr[]={97,122};
            cset=setArray(arr);
            len=26;
            break;
        }
        case 3:{
            int arr[]={65,90,97,122};
            cset=setArray(arr);
            len=52;
            break;
        }
        case 4:{
            int arr[]={48,57};
            cset=setArray(arr);
            len=10;
            break;
        }
        case 5:{
            int arr[]={65,90,48,57};
            cset=setArray(arr);
            len=36;
            break;
        }
        case 6:{
            int arr[]={97,122,48,57};
            cset=setArray(arr);
            len=36;
            break;
        }
        case 7:{
            int arr[]={65,90,97,122,48,57};
            cset=setArray(arr);
            len=62;
            break;
        }
        case 8:{
            int arr[]={32,126};
            cset=setArray(arr);
            len=95;
            break;
        }
        case 9:{
            int arr[]={0,127};
            cset=setArray(arr);
            len=128;
            break;
        }
        case 10:{
            cset=getCharset(len);
            break;
        }
        default :{
            cout << "Invalid option.";
            exit(EXIT_FAILURE);
            break;
        }
    }

    start = getInt("\nStart Limit - Enter the size of the first word\nin the dictionary. Default is 0 : ");
    if (start<0){
        cout << "Invalid input. Using default value.\n";
        start=0;
    }
    stringstream ss;
    ss << (start+10);
    stop = getInt("\nStop Limit - Enter the size of the last word\nin the dictionary. Default is " + ss.str() + " : ");
    if (stop<start){
        cout << "Invalid input. Using default value.\n";
        stop=start+10;
    }

    cin.ignore(INT_MAX,'\n');
    cin.clear();
    cout << "\nText to prepend in every word (Press ENTER to Skip) : ";
    getline(cin, prepend);
    cout << "\nText to append in every word (Press ENTER to Skip) : ";
    getline(cin, append);

    cls();
    for (int i=start;i<=stop;i++){
        combos+=pow(len,i);
    }
    for (int i=start;i<=stop;i++){
        space+=append.length()+prepend.length()+((pow(len,i))*i)+1;
    }
    space+=10;
    cout << "\n" << combos << "Words.";
    cout << "\n" << std::fixed << ((space/1024.0d)/1024.0d) << " MB of Disk space required.";
    cout << "\nIt is recommended that you have the available disk space before proceeding.";
    cout << "\n\nPress ENTER to start generating : ";
    getline(cin, trash);

    FILE *file=fopen("dictionary.lst","wb");
    for (int i=start;i<stop;i++){
        write(file,cset,len,i,0,"");
    }

    //debug

    return 0;
}
