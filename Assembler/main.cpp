// You must use latest MinGW compiler from ( https://nuwen.net/mingw.html ) - mingw-1x.x-without-git.exe
// with C++14 or C++11 enabled in compiler settings

#include <bits/stdc++.h>

using namespace std;


//this function converts a string to number
int toInt(string s){
    int tmp1=0;
    int multiplier=1;

    for(int i=s.length()-1;i>=0;i--){
        if (s[i]=='-')
            break;
        tmp1+=(s[i]-'0')*multiplier;
        multiplier*=10;
    }

    if (s[0]=='-')
        tmp1*=-1;

    return tmp1;
}

// this function converts the decimal number "num" to a binary string with "noOfBits" bits
string toBinary(int num, int noOfBits){
    string s="";
    for(int i=0;i<noOfBits;i++){
        if ((num & (1<<i))!=0){
            s+="1";
        }
        else {
            s+="0";
        }
    }

    reverse(s.begin(),s.end());


    return s;

}


map<string,string> m; //this map relates register names with their corresponding binary codes

/* this function initializes the map which establishes the relation between register name and it's
corresponding binary expression */
void prepare_registers(){
    string tmp1="$ac";
    m[tmp1]=toBinary(0,2);

    tmp1="$s1";
    for(int i=1;i<=3;i++){
        tmp1[2]=(char)(i+'0');
        m[tmp1]=toBinary(i,2);
    }
}


#include "R_type.cpp"
#include "I_type.cpp"


// converts all the characters to lowercase
void toLower(string& instruction){
    int instlen = instruction.length();
    for(int i=0;i<instlen;i++){
        if (instruction[i]>='A' && instruction[i]<='Z'){
            instruction[i]+=8;
        }
    }
}


//splits the input string into to tokens
vector<string> split(string& instruction){

    string s="";
    vector<string> v;
    int start=0;
    int instlen = instruction.length();

    if(instruction[0] == 'j')
    {

        for(int i=0; i<instlen; i++)
        {
            if (instruction[i]==' '){
                start=i;
                break;
            }
            s+=instruction[i];
        }
        v.push_back(s);

        s="";
        for(int i=start+1;i<instlen;i++){
            s+=instruction[i];
        }
        v.push_back(s);
    }
    else{

        for(int i=0;i<instlen;i++){
            if (instruction[i]==' '){
                continue;
            }
            if (instruction[i]=='$'){
                start=i;
                break;
            }
            s+=instruction[i];
        }
        v.push_back(s);

        s="";
        for(int i=start;i<instlen;i++){
            if (instruction[i]==' '){
                continue;
            }
            if (instruction[i]==','){
                if (!s.empty()){
                    v.push_back(s);
                    s="";
                }
                continue;
            }
            s+=instruction[i];
        }

        if (!s.empty()){
            v.push_back(s);
        }
    }
    return v;
}


//prints the output string
string printCode(string s, bool spaces){

    int strleng = s.length();
    string str = "";
    for(int i=0;i<strleng;i++){
        if (s[i]==' ' && !spaces)
            continue;
        //cout << s[i];
        str+=s[i];
    }
    //cout<<endl;

    return str;
}


string binaryToHex(string s)
{
    long long a = toInt(s);
    //cout << "int " << a << endl;
    //long long a2 = toInt(s.substr(5,4));
    long long res = 0;
    //long long res2;
    long long rem;
    //long long res2;
    string str_hex = "";
    //string s2;
    long long base = 1;

    while (a > 0)
    {
        rem = a % 10;
        res =  res  + rem * base;
        base = base * 2;
        a /= 10;
    }
    //cout << "bin to dec " << res << endl;
    while (res > 0) {
        rem = res % 16;
        if (rem > 9) {
            switch (rem) {
               case 10: str_hex += "a"; break;
               case 11: str_hex += "b"; break;
               case 12: str_hex += "c"; break;
               case 13: str_hex += "d"; break;
               case 14: str_hex += "e"; break;
               case 15: str_hex += "f"; break;
            }
        }
        else {
            str_hex += to_string(rem);
        }
        res = res / 16;
    }


    if(str_hex.length()==1)
    {
        //cout << "0"+str_hex;
        str_hex += "0";
        reverse(str_hex.begin(), str_hex.end());
        return str_hex;
    }
    else{
        reverse(str_hex.begin(), str_hex.end());
        return str_hex;
    }

}

int main()
{
    /* if you want to both read the input instructions and write the output binary codes in files then keep both the
    the freopen fuction call open. If you wnat to take the input from the file and print the output in console then keep
    the first freopen and the second one closed .. and so on.....*/


    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);


    prepare_registers();
    bool compilation = true;
    vector<string> pipe;
    //vector<string> errors;
    string instruction;

    while(getline(cin,instruction)){

        toLower(instruction);
        vector<string> v=split(instruction);


        // condition to eliminate empty or any other invalid string
        if (v.size()<2){
            continue;
        }

        //compilation= true;
        bool spaces=false; //if spaces is true there will be spaces in the output string separating the data fields otherwise not


        //if you want to see the instruction be along with the binary code in the output file keep this line
        //cout<<instruction<<endl;

        // In total 8 different instructions are supported by this program
        //R-type

        if (v[0]=="add" || v[0]=="sub" || v[0]=="sll"){
            R_type data(v);
            data.solve();
            if (data.errorMessage.empty()){
                //printCode(data.translated,spaces);
                pipe.push_back(printCode(data.translated,spaces));
                //cout<<data.translated << endl;

            }
            else {
                //cout<<data.errorMessage<<endl;

                compilation = false;
                break;
            }

        }
        // I-type
        else if (v[0]=="addi" || v[0]=="lw" || v[0]=="sw" || v[0]=="beq" || v[0]=="jmp"){
            Itype data(v);
            data.solve();
            if (data.errorMessage.empty()){
                //printCode(data.translated,spaces);
                pipe.push_back(printCode(data.translated,spaces));
                //cout<<data.translated << endl;

            }
            else {
                //cout<<data.errorMessage<<endl;

                compilation = false;
                break;
            }

        }
        else {
            //cout<<"ERROR: Can't recognize the instruction "<<v[0]<<endl;

            compilation = false;
            break;
        }

    }


    // test print
    /*for(int i=0;i<pipe.size(); i++)
    {
        cout << pipe[i] << endl;
    }*/


    if(compilation)
    {
        cout << "v2.0 raw" << endl;

        int psize = pipe.size();
        for(int i=0;i< psize; i++)
        {
            //cout << pipe[i] << endl;
            cout << binaryToHex(pipe[i]) << endl;

        }
    }
    else
        cout << "Compilation failed." << endl;

    pipe.clear();
    m.clear();

    return 0;
}
