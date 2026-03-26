#ifndef USER_H
#define USER_H

#include <string>

class User
{
    private:
        std::string username;
        // 0:vendor 1:Market Operator 2:System Administrator
        int permission;

    public:
        // Returns string of permission title
        // 0:vendor 1:Market Operator 2:System Administrator
        virtual std::string displayPermission();

        // getters
        std::string getUsername();
        int getPermission();

        //setter
        void setPermission(int x);
        void setUsername(std::string username);



};
#endif // USER_H
