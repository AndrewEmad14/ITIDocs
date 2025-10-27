#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;
bool is_month_long(int month){
    int long_months[] = {0, 2, 4, 6, 7, 9, 11};
    return find(begin(long_months), end(long_months), month) != end(long_months);
}
bool is_leap_year(int year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
int main(){
    tm fixedYear = {0}; 
    fixedYear.tm_year = 72; // 1972
    fixedYear.tm_mon = 0;    // January
    fixedYear.tm_mday = 1;   // 1st
    tm linux_Date = {0};
    int year, month, day;
    while(1){
        // why 1900? tm_year is defined as years since 1900 so to represent 2023, we need to input 123 , why not 1800?
        // because the tm structure is designed to represent years in a way that is compatible with the C standard library functions, which were established long ago.
        //so 1800 might work in some system like 64 bit system but not in 32 bit system
        cout<<"Enter year (since 1900): ";
        cin>> year; 
        cout<<"Enter month (1-12): ";
        cin>> month;
        cout<<"Enter day (1-31): ";
        cin>> day;
        month--; // Adjust month to 0-11 range
        if(!is_month_long(month)){
            if(month == 2){ // February
                if(is_leap_year(year)){
                    if(day > 29){
                        cout<<"Invalid day for February in a leap year. Please try again."<<endl;
                        continue;
                    }
                } else {
                    if(day > 28){
                        cout<<"Invalid day for February. Please try again."<<endl;
                        continue;
                    }
                }
            } else if(day > 30){
                cout<<"Invalid day for the given month. Please try again."<<endl;
                continue;
            }
        } else {
            if(day > 31){
                cout<<"Invalid day for the given month. Please try again."<<endl;
                continue;
            }
        }
        linux_Date.tm_year = year-1900; // years since 1900
        linux_Date.tm_mon = month;
        linux_Date.tm_mday = day;

        cout<<"Valid date entered: "<< (year) << "-" << (month + 1) << "-" << day << endl;
        cout<<"-------------------------------------"<<endl;
        cout<<"Linux Date: "<< 1972 << "-" << 1 << "-" << 1 << endl;
        cout<<"-------------------------------------"<<endl;
        cout<<"time Difference:"<< difftime(mktime(&linux_Date), mktime(&fixedYear))/(60*60*24) << " days" <<endl;
        cout<<"type 'q' to quit or 'c' to continue: ";
        char choice;
        cin >> choice;
        if(choice == 'q'){
            break;
        }
    }
   
    


    return 0;
}