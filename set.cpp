// Liam Howes, 5880331

#include <iostream>
#include "set.h"
#include <string>
#include <sstream>
using namespace std;

Set::Set(const bool stuff[256]){
    for(int i=0; i<256; i++){
        elements[i] = stuff[i];
    }
}

Set Set::operator+(const Set &other){
    Set temp;
    for(int i=0; i<256; i++){
        if( elements[i]==true || other.elements[i]==true){
            temp.elements[i]=true;
        }
        else temp.elements[i]=false;
    }
    return temp;
} //Union
Set Set::operator+(const int &other){
    Set temp;
    for(int i=0; i<256; i++){ //set temp Set
        temp.elements[i] = elements[i];
    }
    temp.elements[other]=true; // 'add element'
    return temp;
} //Technically union; effectively 'add element'
Set Set::operator-(const Set &other){
    Set temp;
    for(int i=0; i<256; i++){
        if(elements[i]==true && other.elements[i]==false){
            temp.elements[i]=true;
        }
        else temp.elements[i]=false;
    }
    return temp;
} //Difference
Set Set::operator-(const int &other){
    Set temp;
    for(int i=0; i<256; i++){ //set temp Set
        temp.elements[i] = elements[i];
    }
    temp.elements[other]=false; // 'remove element'
    return temp;
} //Effectively 'remove element if present'
Set Set::operator^(const Set &other){
    Set temp;
    for(int i=0; i<256; i++){
        if( elements[i]==true && other.elements[i]==true){
            temp.elements[i]=true;
        }
        else temp.elements[i]=false;
    }
    return temp;
}//Intersection
Set Set::operator^(const int &other){
    Set temp;
    for(int i=0; i<256; i++){
        temp.elements[i] = false;
    }
    if(elements[other]==true){ // true at element position
        temp.elements[other] = true;
    }
    return temp;
} //Intersection with element
Set Set::operator~(){
    Set temp;
    for(int i=0; i<256; i++){
        if( elements[i]==false){
            temp.elements[i]=true;
        }
        else temp.elements[i]=false;
    }
    return temp;
} //Complement

Set Set::operator+(){
    Set temp;
    for(int i=0; i<256; i++){
        temp.elements[i] = true;
    }
    return temp;
} //Set of universe
Set Set::operator-(){
    Set temp;
    for(int i=0; i<256; i++){
        temp.elements[i] = false;
    }
    return temp;
} //Empty set

bool Set::operator<=(const Set &other){
    for(int i=0; i<256; i++){
        if(elements[i] == true){
            if(other.elements[i]==false)
                return false;
        }
    }
    return true;
} //Subset
bool Set::operator<(const Set &other){
    int same=0;
    for(int i=0; i<256; i++){
        if(elements[i] == true){
            if(other.elements[i]==false)
                return false;
            else same+=1;
        }
    }
    if(same==256) return false;
    else return true;
} //Strict subset
bool Set::operator>=(const Set &other){
    for(int i=0; i<256; i++){
        if(other.elements[i] == true){
            if(elements[i]==false)
                return false;
        }
    }
    return true;
} //Superset
bool Set::operator>(const Set &other){
    int same=0;
    for(int i=0; i<256; i++){
        if(other.elements[i] == true){
            if(elements[i]==false)
                return false;
            else same+=1;
        }
    }
    if(same==256) return false;
    else return true;
} //Strict superset
bool Set::operator==(const Set &other){
    int same=0;
    for(int i=0; i<256; i++){
        if(other.elements[i] == elements[i]){
            same+=1;
        }
    } 
    if(same==256) return true;
    else return false;
} //Test for set equality
bool Set::operator!=(const Set &other){
    int same=0;
    for(int i=0; i<256; i++){
        if(other.elements[i] != elements[i]){
            return true;
        }
    } 
    return false;
} //Test for set inequality
bool Set::operator!(){
    int count = 0;
    for(int i=0; i<256; i++){
        if(elements[i]==true){
            count+=1;
        }
    }
    if(count==0) return true;
    else return false;
} //Test for empty set

int Set::operator()(){
    int count =0;
    for(int i=0; i<256; i++){
        if(elements[i] == true) 
        count+=1;
    }
    return count;
} //Cardinality of set. i.e. |Set|
bool Set::operator[](const int &pos){
    if(elements[pos] ==true) return true;
    else return false;
} //Test for 'is element of'

//   STREAM EXTRACTION   //
std::istream& operator>>(std::istream &in, Set &set) {
    bool arr[256] = {false};
    char open;
    in>>open;
    if (in.fail() || open!='{') {
        in.setstate(std::ios::failbit);
        return in;
    }
    std::string buff;
    std::getline(in,buff,'}');
    std::stringstream ss(buff);
    std::string field;
    while (true) {
        std::getline(ss,field,',');
        if (ss.fail()) break;
        int el;
        std::stringstream se(field);
        se>>el;
        if (el>=0&&el<256)
            arr[el]=true;
    }
    set=Set(arr);
    
}
//   STREAM INSERTION   //
std::ostream& operator<<(std::ostream &out, const Set &set) {
    int count=0;
    cout<<"{";
    for (int i=0;i<256;i++){
        if(set.elements[i]==true){
            if(count==0){
                cout<<i;
                count++;
            }
            else{
                cout<<",";
                cout<<i;
                count++;
            }
        }
    }
    cout<<"}";
}

int main(){
    Set set;
    Set otherSet;
    int value;

    Set universal;

    cout<<"Enter a set (ex: {1,2,3})\n";
    cin>>set;
    cout<<"your set: "<<set<<endl;
    cout<<endl;

    cout<<"Enter a second set (ex: {1,2,3})\n";
    cin>>otherSet;
    cout<<"your second set: "<<otherSet<<endl;
    cout<<endl;

    cout<<"Enter an element value from 0-255\n";
    cin>>value;
    cout<<"your element value: "<<value<<endl;
    cout<<endl;

    // union //
    cout<<"union of your two sets: ";
    cout<<set+otherSet<<endl;

    // element union //
    cout<<"union of your set one and your single element: ";
    cout<<set+value<<endl;

    //difference //
    cout<<"difference of first and second set (first-second): ";
    cout<<set-otherSet<<endl;

    // element difference //
    cout<<"difference of first set and element (first-element): ";
    cout<<set-value<<endl;

    // intersection //
    cout<<"intersection of first set and second sets: ";
    cout<<(set^otherSet)<<endl;

    // element intersection //
    cout<<"intersection of first set and element: ";
    cout<<(set^value)<<endl;

    // set of universe //
    cout<<"set of the universe: ";
    cout<<+universal<<endl;

    // empty set //
    cout<<"empty set: ";
    cout<<-universal<<endl;
    
    // subset //
    cout<<"is first a subset of second: ";
    cout<<(set<=otherSet)<<endl;

    // strict subset //
    cout<<"is first a strict subset of second: ";
    cout<<(set<otherSet)<<endl;

    // superset //
    cout<<"is first a superset of second: ";
    cout<<(set>=otherSet)<<endl;

    // strict superset //
    cout<<"is first a strict superset of second: ";
    cout<<(set>otherSet)<<endl;

    // test for equality //
    cout<<"are first and second the same: ";
    cout<<(set==otherSet)<<endl;

    // test for inequality //
    cout<<"is first and second different: ";
    cout<<(set!=otherSet)<<endl;

    // test for empty set //
    cout<<"is first set empty: ";
    cout<<!set<<endl;

    // cardinality //
    cout<<"cardinality of first set: ";
    cout<<set()<<endl;

    // element of //
    cout<<"is the element entered an element of the first set: ";
    cout<<set[value]<<endl;

    return 0;
}