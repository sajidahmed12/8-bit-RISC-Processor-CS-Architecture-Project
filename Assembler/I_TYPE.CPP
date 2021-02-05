#include "I_type.h"


Itype::Itype(){
}

Itype::Itype(vector<string> a){
    v=a;
}


// deals with the lw and sw type instruction
void Itype::memAccess(){

    if (v.size()<3){
        errorMessage+="ERROR: Not enough data fields. ";
        return;
    }
    else if (v.size()>3){
        errorMessage+="ERROR: Too much data fields. ";
        return;
    }

    if (m.find(v[1])==m.end()){
        errorMessage="ERROR: Register number "+v[1]+" is not valid";
        return;
    }

    if (v[0]=="lw"){
        translated=toBinary(3,3);
    }
    else {
        translated=toBinary(4,3);
    }

    if (toInt(v[2])>7){
        errorMessage="ERROR: Offset value can not be more than 7";
        return;
    }
    if (toInt(v[2])<0){
        errorMessage="ERROR: Offset value can not be negative";
    }

    translated+=" "+m[v[1]]+" "+toBinary(toInt(v[2]),3);


}

// deals with beq and jmp type instruction
void Itype::decision(){

    if(v[0]=="beq"){

        if (v.size()<3){
            errorMessage+="ERROR: Not enough data fields. ";
            return;
        }
        else if (v.size()>3){
            errorMessage+="ERROR: Too much data fields. ";
            return;
        }

        if (toInt(v[2])>7){
            errorMessage="ERROR: jump value can not be more than 7";
            return;
        }

        if (toInt(v[2])<0){
            errorMessage="ERROR: jump value can not be less than 0";
            return;
        }

        if (m.find(v[1])==m.end()){
            errorMessage="ERROR: Register number "+v[1]+" is not valid";
            return;
        }
    }
    else if(v[0]=="addi")
    {
        if (v.size()<3){
            errorMessage+="ERROR: Not enough data fields. ";
            return;
        }
        else if (v.size()>3){
            errorMessage+="ERROR: Too much data fields. ";
            return;
        }


            if (toInt(v[2])>7){
                errorMessage="ERROR: constant value can not be more than 7";
                return;
            }

            if (toInt(v[2])<0){
                errorMessage="ERROR: constant value can not be less than 0";
                return;
            }



        if (m.find(v[1])==m.end()){
            errorMessage="ERROR: Register number "+v[1]+" is not valid";
            return;
        }

    }
    else{
        if (v.size()<2){
            errorMessage+="ERROR: Not enough data fields. ";
            return;
        }
        else if (v.size()>2){
            errorMessage+="ERROR: Too much data fields. ";
            return;
        }

        if (toInt(v[1])>31){
            errorMessage="ERROR: jump value can not be more than 31";
            return;
        }

        if (toInt(v[1])<0){
            errorMessage="ERROR: jump value can not be less than 0";
            return;
        }
    }

    if (v[0]=="beq"){
        translated=toBinary(5,3);
        translated+=" "+m[v[1]]+" "+toBinary(toInt(v[2]),3);
    }
    else if(v[0]=="addi")
    {
         translated+=toBinary(2,3)+" "+m[v[1]]+" "+toBinary(toInt(v[2]),3);
    }
    else{
        translated=toBinary(6,3);
        translated+=" "+toBinary(toInt(v[1]),5);
    }
}


void Itype::solve(){

    if (v[0]=="lw" || v[0]=="sw"){
        return memAccess();
    }
    else if (v[0]=="beq" || v[0]=="jmp"){
        return decision();
    }
    else if (v[0]=="addi"){
        return decision();
    }


}
