#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <stack>
#include <sstream>
#include <set>
#include <fstream>

using namespace std;
using psi = pair<string, int>;

class RuntimeException
{
private:
    std::string errorMsg;

public:
    RuntimeException(const std::string &err) { errorMsg = err; }
    std::string getMessage() const { return errorMsg; }
};

inline std::ostream &operator<<(std::ostream &out, const RuntimeException &e)
{
    return out << e.getMessage();
};

class PriorityQueueEmptyException : public RuntimeException
{
public:
    PriorityQueueEmptyException(const std::string &err) : RuntimeException(err) {}
};

struct SNode
{
    string strNode;
    int length;
    SNode(string str, int len)
    {
        strNode = str;
        length = len;
    }

    SNode()
    {
        length = 0;
    }
    const bool operator<(const SNode &node) const
    {
        return this->length < node.length;
    }
};

template <typename Object>
class MyPriorityQueue
{
private:
    // fill in private member data here
    std::vector<Object> vecElement;

private:
    void shift_down(int index, int endIndex);
    void shift_up(int index);

public:
    MyPriorityQueue();

    ~MyPriorityQueue();

    size_t size() const noexcept;

    bool isEmpty() const noexcept;

    void insert(const Object &elem);

    // Note:  no non-const version of this one.  This is on purpose because
    // the interior contents should not be able to be modified due to the
    // heap property.  This isn't true of all priority queues but
    // for this project, we will do this.
    // min and extractMin should throw PriorityQueueEmptyException if the queue is empty.
    const Object &min() const;

    void extractMin();
    /*
    void print()
    {
        for(int i = 0;i < vecElement.size(); i++)
            printf("%d ",vecElement[i]);
        printf("\n");
    }
    */
};

template <typename Object>
MyPriorityQueue<Object>::MyPriorityQueue()
{
    vecElement.clear();
}

template <typename Object>
MyPriorityQueue<Object>::~MyPriorityQueue()
{
    vecElement.clear();
}

template <typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
    return vecElement.size();
}

template <typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
    if (vecElement.size() != 0)
        return false;
    return true;
}

template <typename Object>
void MyPriorityQueue<Object>::insert(const Object &elem)
{
    vecElement.push_back(elem);
    if (vecElement.size() == 1)
        return;
    shift_up(vecElement.size() - 1);
}

template <typename Object>
const Object &MyPriorityQueue<Object>::min() const
{
    return vecElement.front();
}

template <typename Object>
void MyPriorityQueue<Object>::extractMin()
{
    int size = vecElement.size();
    if (size == 0)
        return;
    Object o = vecElement[size - 1];
    vecElement.pop_back();
    if (vecElement.size() > 1)
    {
        vecElement[0] = o;
        shift_down(0, vecElement.size() - 1);
    }
}

template <typename Object>
void MyPriorityQueue<Object>::shift_down(int parentIndex, int endIndex)
{
    int left = 2 * parentIndex + 1;
    int right = 2 * parentIndex + 2;
    // 最小值的下标
    int minIndex = parentIndex;
    if (left <= endIndex && vecElement[left] < vecElement[minIndex])
        minIndex = left;
    if (right <= endIndex && vecElement[right] < vecElement[minIndex])
        minIndex = right;

    if (minIndex == parentIndex)
        return;

    Object o = vecElement[parentIndex];
    vecElement[parentIndex] = vecElement[minIndex];
    vecElement[minIndex] = o;
    // 递归调整
    shift_down(minIndex, endIndex);
}

template <typename Object>
void MyPriorityQueue<Object>::shift_up(int childIndex)
{
    int parentIndex = (childIndex - 1) / 2;
    Object parent = vecElement[parentIndex];
    Object child = vecElement[childIndex];

    if (child < parent)
    {
        Object o = vecElement[parentIndex];
        vecElement[parentIndex] = vecElement[childIndex];
        vecElement[childIndex] = o;
        shift_up(parentIndex);
    }
}

class heap
{
public:
    heap()
    {
        data.clear();
        len = 0;
    }
    ~heap()
    {
        data.clear();
        len = 0;
    }
    bool cmp(psi a, psi b)
    {
        return a.second < b.second || a.second == b.second && a.first < b.first;
    };
    void swap(vector<psi> data, int i, int j)
    {
        auto temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
    void push(psi ele)
    {
        data.emplace_back(ele);
        int index = len;
        while (cmp(data[index], data[(index - 1) / 2]))
        {
            swap(data, index, (index - 1) / 2);
            index = (index - 1) / 2;
        }
        len++;
    }
    void pop()
    {
        swap(data, 0, data.size() - 1);
        data.pop_back();
        int index = 0;
        int left = index * 2 + 1;
        while (left < len)
        {
            int maxIndex = (left + 1 < len) && cmp(data[left], data[left + 1]) ? left + 1 : left;
            if (cmp(data[maxIndex], data[index]))
                break;
            swap(data, index, maxIndex);
            index = maxIndex;
            left = index * 2 + 1;
        }
        len--;
    }
    psi top()
    {
        if (!empty())
        {
            return data[0];
        }
        return psi();
    }
    bool empty()
    {
        return !len;
    }
    vector<psi> data;
    int len;
};

// You should not need to change this function.
void loadWordsIntoTable(std::unordered_set<std::string> &words, std::istream &in)
{
    std::string line, word;
    std::stringstream ss;

    while (getline(in, line))
    {
        ss.clear();
        ss << line;
        while (ss >> word)
        {
            words.insert(word);
        }
    }
}

// You probably want to change this function.
std::vector<std::string> convert(const std::string &s1, const std::string &s2, const std::unordered_set<std::string> &words)
{
    vector<string> ret;
    std::set<string> sstr;
    map<string, string> mss;
    map<string, int> msi;
    int length = s1.length();
    for (unordered_set<string>::const_iterator itr = words.begin(); itr != words.end(); itr++)
    {
        if ((*itr).length() == length)
            sstr.insert(*itr);
    }
    printf("========---==%d\n", sstr.size());
    for (auto str : sstr)
    {
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] != s2[i])
            {
                msi[str]++;
            }
        }
    }

    MyPriorityQueue<SNode> mpq;
    // heap mpq;
    mpq.insert(SNode(s1, 0));
    // mpq.push(psi(s1, 0));
    mss.emplace(s1, "0");
    while (!mpq.isEmpty())
    // while (!mpq.empty())
    {
        SNode node = mpq.min();
        mpq.extractMin();
        string str = node.strNode;
        int len = node.length;
        cout << str << ": ";
        /*
        auto str = mpq.top().first;
        auto len = mpq.top().second;
        mpq.pop();
        */
        if (str == s2)
        {
            cout << "最短路径步数:" << len << endl;
            string s = str;
            stack<string> sk;
            while (mss.count(s) && s != "0")
            {
                sk.emplace(s);
                s = mss[s];
            }
            while (!sk.empty())
            {
                cout << sk.top();
                sk.pop();
                if (!sk.empty())
                {
                    cout << "->";
                }
                else
                {
                    cout << endl;
                }
            }
            break;
        }
        for (int i = 0; i < str.size(); i++)
        {
            string temp = str;
            for (char c = 'a'; c <= 'z'; c++)
            {
                temp[i] = c;
                if (temp == s2)
                    puts("=============");
                if (sstr.count(temp) && !mss.count(temp))
                {
                    cout << temp << " ";
                    mpq.insert(SNode(temp, len + 1 + msi[temp]));
                    // mpq.push(psi(temp, len + 1 + msi[temp]));
                    mss[temp] = str;
                }
            }
        }
        cout << endl;
    }

    return ret; // stub obviously
}

int main()
{

    std::string WORD_ONE = "boosted";
    std::string WORD_TWO = "classes";
    int CORRECT_LENGTH = 44;
    std::unordered_set<std::string> words;
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);
    convert(WORD_ONE, WORD_TWO, words);
    return 0;

    /*
     MyPriorityQueue<int> mpq;
     mpq.insert(3);
     mpq.insert(5);
     mpq.insert(2);
     mpq.insert(7);
     mpq.insert(1);
     mpq.print();
     while(!mpq.isEmpty())
     {
        printf("=======%d\n",mpq.min());
        mpq.extractMin();
        mpq.print();
     }
     */
    return 0;
}