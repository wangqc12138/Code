#include <sys/stat.h>
#include <iostream>
using namespace std;
int main(){
    struct stat s;
    stat("./1",&s);
    cout<<(int)s.st_size<<endl;
    return 0;
}