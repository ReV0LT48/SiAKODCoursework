#include <iostream>

class Mystring
{
private:
    char* str;
    unsigned length;
    
public:
    Mystring();
    Mystring(const char* str);
    ~Mystring();
    unsigned get_length();
    char operator[](unsigned index) const;
    Mystring& operator=(const char* str);
    Mystring& operator=(const Mystring& str);
    char* operator+(const Mystring& str);
    Mystring& operator+=(const Mystring& str);
    friend bool operator==(const Mystring& lstr, const Mystring& rstr);
    friend bool operator>(const Mystring& lstr, const Mystring& rstr);
    friend bool operator<(const Mystring& lstr, const Mystring& rstr);
    friend std::ostream& operator<<(std::ostream& out, const Mystring& output);
    friend std::istream& operator>>(std::istream& in, Mystring& input_str);
    
    unsigned shell_sort();
    
};

Mystring::Mystring()
{
    str = nullptr;
    length = 0;
}

Mystring::Mystring(const char* str)
{
    unsigned counter = 0;
    for (int i = 0; str[i] != '\0'; i++) counter++;
    length = counter + 1;
    this->str = new char[length];
    for(int i = 0; i < length; i++) this->str[i] = str[i];
    this->str[length] = '\0';
}

Mystring::~Mystring()
{
    delete[] this->str;
}

unsigned Mystring::get_length()
{
    return length - 1;
}

char Mystring::operator[](unsigned index) const
{
    return str[index];
}

Mystring& Mystring::operator=(const char* str)
{
    delete[] this->str;
    unsigned counter = 0;
    for (int i = 0; str[i] != '\0'; i++) counter++;
    length = counter + 1;
    this->str = new char[length];
    for (int i = 0; i < length; i++) this->str[i] = str[i];
    this->str[length] = '\0';
    return *this;
}

Mystring& Mystring::operator=(const Mystring& str)
{
    delete[] this->str;
    length = str.length;
    this->str = new char[length];
    for (unsigned i = 0; i < length; i++) this->str[i] = str[i];
    this->str[length] = '\0';
    return *this;
}


char* Mystring::operator+(const Mystring& str)
{
    char* temp = new char[this->length + str.length - 1];
    for (int i = 0; i < this->length; i++) temp[i] = this->str[i];
    temp[this->length] = '\0';
    strcat(temp, str.str);
    return temp;
}

Mystring& Mystring::operator+=(const Mystring& str)
{
    *this = *this + str;
    return *this;
}

bool operator==(const Mystring& lstr, const Mystring& rstr)
{
    if (lstr.length == rstr.length) return true;
    else return false;
}

bool operator>(const Mystring& lstr, const Mystring& rstr)
{
    if (lstr.length > rstr.length) return true;
    else return false;
    
}

bool operator<(const Mystring& lstr, const Mystring& rstr)
{
    if (lstr.length < rstr.length) return true;
    else return false;
}

std::ostream& operator<<(std::ostream& out, const Mystring& output)
{
    out << output.str;
    return out;
    
}

std::istream& operator>>(std::istream& in, Mystring& input_str)
{
    unsigned counter = 0;
    char* input_value = nullptr;
    char sym;
    while(1)
    {
        if ((sym = in.get()) != '\n')
        {
            input_value = (char*)realloc(input_value, ++counter);
            input_value[counter - 1] = sym;
        }
        else
        {
            input_value = (char*)realloc(input_value, ++counter);
            input_value[counter - 1] = '\0';
            break;
        }
    }
    input_str.str = new char[counter];
    input_str.length = counter;
    for (int i = 0; i < counter; i++) input_str.str[i] = input_value[i];
    input_str.str[counter] = '\0';
    return in;
}

unsigned Mystring::shell_sort()
{
    int* cti = new int[length - 1];
    for (int i = 0; i < length; i++) cti[i] = str[i]; //Преобразование char в int
    
    ////////////////////////Сортировка
    unsigned counter = 0;
    int step = (length - 1) / 2;
    while (step > 0)
    {
        for (int i = 0; i < ((length - 1) - step); i++)
        {
            if (cti[i] < cti[i + step]) counter++;
            for (int j = i; j >= 0 && cti[j] > cti[j + step]; j--, counter++)
            {
                int temp = cti[j];
                cti[j] = cti[j + step];
                cti[j + step] = temp;
            }
        }
        step /= 2;
    }
    ////////////////////////
    for (int i = 0; i < length; i++) str[i] = cti[i]; //Преобразование int в char
    delete[] cti;
    return counter;
}


int main()
{
    using namespace std;
    setlocale(0, "");
    Mystring str;
    cout << "Введите строку -> ";
    cin >> str;
    cout << "Размер введенной строки -> " << str.get_length() - 1 << endl;
    cout << "Анализ сортировки Шелла.\n";
    cout << "1. Для упорядоченной строки.\n";
    str.shell_sort();
    cout << str;
    cout << "\nКоличество сравнений: " << str.shell_sort();
    cout << "\n2. Для упорядоченной в обратном порядке строки.\n";
    
    return 0;
}
