#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string>
using namespace std;
class socket{
public:
    socket(string ip,int port):ip(ip),port(port){};
    int Connect();
    int Accept();
private:
    string ip;
    int port;
};