#include <list>
#include <string>
#include <iostream>
using namespace std;

typedef enum
{
    LOW,
    NORMAL,
    HIGH } ElementPriority;


struct QueueElement
{

    ElementPriority priority;

    string name;

    QueueElement(string _name, ElementPriority _priority);

    QueueElement(char _name[], ElementPriority _priority);

    friend bool operator<(const QueueElement &leftel, const QueueElement &rightel);

    friend ostream& operator<<( ostream &ostr, const QueueElement &L );
};


typedef list<QueueElement> __queue_type;

typedef __queue_type::iterator __queue_iterator_type;

typedef __queue_type::reverse_iterator __queue_reverse_iterator_type;


class QueueWithPriority
{
private:
    __queue_type __queue;
public:
 
    QueueWithPriority(void);

    ~QueueWithPriority(void);

    void putElement(const QueueElement &element);

    void putElement(const char name[], ElementPriority priority);

    QueueElement getElement(void);
    int size(void){
        return __queue.size();
    }

    void print_queue(void);

};



QueueElement::QueueElement(string _name, ElementPriority _priority)
{
    name=_name;
    priority=_priority;
}

QueueElement::QueueElement(char _name[], ElementPriority _priority)
{
    name = string(_name),
    priority = _priority;
}

bool operator<(const QueueElement &leftel, const QueueElement &rightel)
{
    return (leftel.priority < rightel.priority);
}

ostream& operator<<( ostream &ostr, const QueueElement &L )
{
    char *priority_name;
    switch (L.priority)
    {
    case LOW: priority_name = "LOW";
        break;
    case NORMAL: priority_name = "NORMAL";
        break;
    case HIGH: priority_name = "HIGH";
        break;
    default: priority_name = "None";
    }

    ostr << "Q("<< L.name << "," << priority_name << ")";
    return ostr;
}


QueueWithPriority::QueueWithPriority()
{

}

QueueWithPriority::~QueueWithPriority()
{

}

void QueueWithPriority::putElement(const QueueElement &element)
{
    __queue_iterator_type iter;
    int check;
    bool insert = false;
    if ((!__queue.empty()) & (element.priority != LOW))
    {
        for(iter=__queue.begin(); iter != __queue.end(); iter++)
        {
            check = iter->priority - element.priority;
            if (check == -1)
            {
                __queue.insert(iter, element);
                insert = true;
                break;
            }
        }
        if (!insert)
        {
            __queue.push_front(element);
        }
    } else {
        __queue.push_back(element);
    }
}

void QueueWithPriority::putElement(const char name[], ElementPriority priority)
{
    putElement(QueueElement(name, priority));
}

QueueElement QueueWithPriority::getElement()
{
    if (!__queue.empty())
    {
        QueueElement qe = __queue.front();
        __queue.pop_front();
        return qe;
    } else {
        cerr << "No more QueueElement in QueueWithPriority!"<< endl;
        throw "fail";
    }

}

void QueueWithPriority::print_queue()
{
    __queue_iterator_type iter;
    for(iter=__queue.begin(); iter != __queue.end();iter++)
    {
        cout<< *iter<< "\n";
    }
}