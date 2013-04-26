#include <iostream>
#include <string>
#include <cstdlib>

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

int GetNumber(string prompt){
    string inp="";
    int num=0;
    while (num==0){
        cout << prompt;
        cin >> inp;
        num = atoi(inp.c_str());
    }
    return num;
}

char* setArray(int arr[]){
    int h=0;
    char dupl[128];
    for (int i=0;i<sizeof(arr);i+=2){
        for (int j=arr[i];j<=arr[i+1];j++){
            dupl[h]=j;
            h++;
        }
    }
    return dupl;
}

char* getCharset(int &len){
    char arr[128];
    cout << "\nType a continuous string of characters without spaces.\nThe characters can repeat but their length must be below 128\n\n";
    string inp;
    cin >> inp;
    len = sizeof(inp);
    if (len>128){
        cout << "Character list is too long.";
        exit(EXIT_FAILURE);
    }
    for (int i=0;i<len;i++){
        arr[i]=inp.at(i);
    }
    return arr;
}

int main(){
    string trash="";

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

    char *cset;
    int len;
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
    int ch=GetNumber("Choose an option : ");

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

    char charset[len];
    for (int i=0;i<len;i++){
        charset[i]=*(cset+i);
    }









    //debug
    for (int i=0;i<sizeof(charset);i++){
        cout << charset[i] << " ";
    }

    return 0;
}
