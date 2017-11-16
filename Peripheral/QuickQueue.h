#ifndef __QUICK__QUEUE__H__
#define __QUICK__QUEUE__H__

#include <list>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>

#ifndef NODE_BUFFER_SIZE
#define NODE_BUFFER_SIZE 512
#endif // NODE_BUFFER_SIZE

class QuickQueue {
private:
    struct DataNode {
        int start_offset = 0;
        int buf_size = 0;
        char buf[NODE_BUFFER_SIZE];

        DataNode(void) {
            start_offset = 0;
            buf_size = 0;
        }

        // no error checking
        void addChar(char c) {
            buf[buf_size] = c;
            buf_size++;
        }

        // no error checking
        char getChar(void) {
            char c = buf[start_offset];
            start_offset++;
            return c;
        }
    };

    // hold temporary chunks of memory
    std::list<DataNode> __list;

    void addCharToQueue(char c);

    // retrieving character from empty queue results in undefined behavior
    char getCharFromQueue(void);

    int overall_buffer_size = 0;

    char peekQueue(void);

public:

    QuickQueue() {
        __list.push_back(DataNode()); // put one
    }

    int size(void);
    int pageLength(void);

    void clear(void);

    // add data to input vector
    void getData(std::vector<char>& vec);

    // overloaded methods for pushing data into the queue
    void push(const char c);
    void push(const char* cArr, int buf_size);
    void push(std::vector<char>& vec);
    void push(std::string& str);

    // overloaded methods for popping from the queue
    void pop(char* c);
    void pop(char* cArr, int buf_size);
    void pop(std::vector<char>& vec, int buf_size);
    void pop(std::string& str);

    static int nodeBufferSize(void);

    template<typename T>
    bool canHold(void) {
        if(overall_buffer_size >= sizeof(T))
            return true;
        return false;
    }

    friend QuickQueue& operator>>(QuickQueue& qq, int32_t& i) { qq.pop((char*)&i, 4); return qq; }
    friend QuickQueue& operator>>(QuickQueue& qq, int64_t& i) { qq.pop((char*)&i, 8); return qq; }
    friend QuickQueue& operator>>(QuickQueue& qq, double& d)  { qq.pop((char*)&d, 8); return qq; }
    friend QuickQueue& operator>>(QuickQueue& qq, float& f)   { qq.pop((char*)&f, 4); return qq; }
    friend QuickQueue& operator>>(QuickQueue& qq, std::string& str) { qq.pop(str); return qq; }

    friend QuickQueue& operator<<(QuickQueue& qq, const int32_t& i) { qq.push((char*)&i, 4);   return qq; }
    friend QuickQueue& operator<<(QuickQueue& qq, const int64_t& i) { qq.push((char*)&i, 8);   return qq; }
    friend QuickQueue& operator<<(QuickQueue& qq, const double& d)  { qq.push((char*)&d, 8);   return qq; }
    friend QuickQueue& operator<<(QuickQueue& qq, const float& f)   { qq.push((char*)&f, 4);   return qq; }
    friend QuickQueue& operator<<(QuickQueue& qq, const char* c)    { qq.push(c, strlen(c)+1); return qq; }

    // VEERY special cases for vectors of numbers
    friend QuickQueue& operator<<(QuickQueue& qq, const std::vector<int32_t>& i32vec) {
        int32_t s = i32vec.size();
        //std::cout << "Vector size storing: " << s << std::endl;
        qq << s;
        for(int32_t i : i32vec)
            qq << i;
        return qq;
    }

    friend QuickQueue& operator>>(QuickQueue& qq, std::vector<int32_t>& i32vec) {
        i32vec.clear();
        int32_t s, t;
        qq >> s;

        //std::cout << "Vector size retrieving: " << s << std::endl;

        for(int i = 0; i < s; i++) {
            qq >> t;
            i32vec.push_back(t);
        }

        return qq;
    }

};

void QuickQueue::getData(std::vector<char>& vec) {
    for(DataNode dn : __list) {
        for(int i = dn.start_offset; i < dn.buf_size; i++)
            vec.push_back(dn.buf[i]);
    }
}

void QuickQueue::clear(void) {
    __list.clear();
    __list.push_back(DataNode());
    overall_buffer_size = 0;
}

void QuickQueue::pop(std::string& str) {
    std::vector<char> tmp_vec;
    char c;

    do {
        c = getCharFromQueue();
        tmp_vec.push_back(c);
    } while(c != 0x00); // null-terminated string

    str = &tmp_vec[0];
}

void QuickQueue::pop(std::vector<char>& vec, int buf_size) {
    for(int i = 0; i < buf_size; i++)
        vec.push_back(getCharFromQueue());
}

char QuickQueue::peekQueue(void) {
    DataNode& dn = __list.front();
    return dn.buf[dn.start_offset];
}

void QuickQueue::push(std::string& str) {
    int s = str.length();
    for(int i = 0; i < s; i++)
        addCharToQueue(str[i]);
    addCharToQueue((char)0x00);
}

void QuickQueue::push(std::vector<char>& vec) {
    int s = vec.size();
    for(int i = 0; i < s; i++)
        addCharToQueue(vec[i]);
}

void QuickQueue::push(const char* cArr, int buf_size) {
    for(int i = 0; i < buf_size; i++)
        addCharToQueue(cArr[i]);
}

void QuickQueue::push(char c) {
    addCharToQueue(c);
}

void QuickQueue::pop(char* c) {
    *c = getCharFromQueue();
}

void QuickQueue::pop(char* cArr, int buf_size) {
    for(int i = 0; i < buf_size; i++)
        cArr[i] = getCharFromQueue();
}

int QuickQueue::pageLength(void) {
    return __list.size();
}

void QuickQueue::addCharToQueue(char c) {
    if(__list.back().buf_size == NODE_BUFFER_SIZE)
        __list.push_back(DataNode());

    __list.back().addChar(c);
    overall_buffer_size++;
}

char QuickQueue::getCharFromQueue(void) {
    DataNode& dn = __list.front();
    char ch;

    if(dn.start_offset < dn.buf_size) {
        ch = dn.getChar();
    }

    if(dn.start_offset == NODE_BUFFER_SIZE && dn.buf_size == NODE_BUFFER_SIZE) {
        __list.pop_front();

        if(__list.size() == 0) // list can never be empty
            __list.push_back(DataNode());
    }

    overall_buffer_size--;
    return ch;
}

int QuickQueue::size(void) {
    return overall_buffer_size;
}

int QuickQueue::nodeBufferSize(void) {
    return NODE_BUFFER_SIZE;
}

#endif // __QUICK__QUEUE__H__
