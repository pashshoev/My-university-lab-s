#include <iostream>
#include <ctime>
using namespace std;
bool isSign(char ch)
{
    switch (ch)
    {
    case ',':
        return true;
    case '.':
        return true; 
    case '?':
        return true; 
    case '!':
        return true;
    case '"':
        return true; 
    case '(':
        return true;
    case ')':
        return true;
    case '-':
        return true;
    case ':':
        return true;
    case ';':
        return true;
    default :
        return false;
    }
}
bool check(char* str, int len)
{
    bool res = 1;
    for (int i = 0; i < len-1; i++)
    {
        if (isSign(str[i]))
        {
            if (str[i + 1] != ' ')
            {
                cout << "Нет пробела после знака \""<<str[i]<<"\"\n";
                return 0;
            }
            cout << endl;
        }
    }
    return res;
}
int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "ru");

     int len = 100;

    char characters[42] = { 'q','w',' ',' ',' ',' ', ' ' ,'e','r','t',' ' ,'y','u',' ','i','k','!','"','(',')','-',',','.','?' 
        ,'d','f','a','s','b','f','h',' ', 'j','k','l',';',':','z','x','v','b','n'
        };
    char* str = new char[len+1];
    for (int i = 0; i < len; i++)
    {
      str[i]=characters[rand()%42];
    }
    str[len] = '\0';
    cout << "Наша строка \n"<<str << endl;
    
    check(str, len);

    delete[] str;
    str = nullptr;
}
