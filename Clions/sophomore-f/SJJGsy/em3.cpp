#include <iostream>
#include <string>
#include <iterator>
using namespace std;
template<typename T>
class linearList
{
public:
    virtual ~linearList() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int Idx) const = 0;
    virtual int idxOf(const T& Elmt) const = 0;
    virtual bool erase(int Idx) = 0;
    virtual bool inseart(int Idx, const T& Elmt) = 0;
    virtual bool output() = 0;
};

template<typename T>
class myVector :public linearList<T>
{
private:
    T* parr;
    int N;
    int lenth;
    void copyTo(T* newParr);
    void multiplySize();
    bool checkIdx(int Idx) const;
public:
    myVector(int n = 1) :N(n),lenth(0) { parr = new T[N]; }
    ~myVector() { delete[] parr; }
    bool empty() const { return lenth == 0; }
    int size() const { return lenth; }
    T& get(int Idx) const;
    int idxOf(const T& Elmt) const;
    bool erase(int Idx);
    bool inseart(int Idx, const T& Elmt);
    bool output();
    bool push_back(const T& Ele);
    T& operator[](int& Idx) { return parr[Idx]; }
};

template<typename T>
void myVector<T>::copyTo(T* newParr)
{
    for (int i = 0; i < lenth; ++i)
        newParr[i] = parr[i];
}

template<typename T>
bool myVector<T>::checkIdx(int Idx) const
{
    if (Idx < 0 || Idx >= lenth)
    {
        string s;
        if (Idx < 0)
            s = "负数下标";
        if (Idx >= lenth)
            s = "数组越界";
        throw s;
        return false;
    }
    return true;
}

template<typename T>
void myVector<T>::multiplySize()
{
    N *= 2;
    T* newParr = new T[N];
    copyTo(newParr);
    delete[] parr;
    parr = newParr;
}

template<typename T>
T& myVector<T>::get(int Idx) const
{
    checkIdx(Idx);
    return parr[Idx];
}

template<typename T>
int myVector<T>::idxOf(const T& Elmt) const
{
    for (int i = 0; i < lenth; ++i)
        if (parr[i] == Elmt)
            return i;
    return -1;
}

template<typename T>
bool myVector<T>::erase(int Idx)
{
    checkIdx(Idx);
    for (int i = Idx; i < lenth - 1; ++i)
        parr[i] = parr[i + 1];
    lenth--;
    return true;
}

template<typename T>
bool myVector<T>::inseart(int Idx, const T& Elmt)
{
    checkIdx(Idx);
    push_back(Elmt);
    for (int i = lenth - 1; i > Idx; --i)
        parr[i] = parr[i - 1];
    parr[Idx] = Elmt;
    return true;
}

template<typename T>
bool myVector<T>::push_back(const T& Ele)
{
    if (lenth == N)
        multiplySize();
    lenth++;
    parr[lenth - 1] = Ele;
    return true;
}

template<typename T>
bool myVector<T>::output()
{
    copy(parr, parr + lenth, ostream_iterator<T>(cout, " "));
    return true;
}



int main()
{
    myVector<string> name;
    myVector<string> phone;
    myVector<int> cls;
    myVector<int> domi;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int op;
        cin >> op;
        if (op == 0)
        {
            string sn, sp;
            int c, d;
            cin >> sn >> sp >> c >> d;
            name.push_back(sn);
            phone.push_back(sp);
            cls.push_back(c);
            domi.push_back(d);
        }
        if (op == 1)
        {
            string sn;
            cin >> sn;
            int idx = name.idxOf(sn);
            name.erase(idx);
            phone.erase(idx);
            cls.erase(idx);
            domi.erase(idx);
        }
        if (op == 2)
        {
            string sn;
            cin >> sn;
            int idx = name.idxOf(sn);
            int xm;
            cin >> xm;
            if (xm == 1)
            {
                string sp;
                cin >> sp;
                phone[idx] = sp;
            }
            if (xm == 2)
            {
                int ic;
                cin >> ic;
                cls[idx] = ic;
            }
            if (xm == 3)
            {
                int id;
                cin >> id;
                domi[idx] = id;
            }
        }
        if (op == 3)
        {
            string sn;
            cin >> sn;
            if (name.idxOf(sn) == -1)
                cout << 0 << endl;
            else
                cout << 1 << endl;
        }
        if (op == 4)
        {
            int cs;
            cin >> cs;
            int xxor = 0;
            for (int i = 0; i < cls.size(); ++i)
                if (cls[i] == cs)
                    xxor ^= domi[i];
            xxor ^= 0;
            cout << xxor << endl;
        }
    }
    return 0;
}