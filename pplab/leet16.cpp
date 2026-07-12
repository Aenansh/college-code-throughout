#include <iostream>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

struct Node
{
  int key, value;
  Node *prev;
  Node *next;
  Node(int k, int v)
  {
    key = k;
    value = v;
    prev = nullptr;
    next = nullptr;
  }
  ~Node() {}
};

class LRUCache
{
  Node *head;
  Node *tail;
  unordered_map<int, int> record;
  int capacity;
  int length;

public:
  LRUCache(int capacity)
  {
    this->capacity = capacity;
    head = nullptr;
    tail = nullptr;
    length = 0;
  }

  int get(int key)
  {
    if (record.find(key) == record.end())
      return -1;
    int val = record[key];
    Node *t1 = head;
    if (head->key == key)
    {
      tail->next = head;
      head->prev = tail;
      tail = tail->next;
      head = head->next;
      head->prev = nullptr;
      tail->next = nullptr;
      cout << key << " " << "get: " << val << endl;
      return val;
    }
    else if (tail->key == key)
    cout << key << " " << "get: " << val << endl;
      return val;
    while (t1->key != key)
    {
      t1 = t1->next;
    }
    t1->prev->next = t1->next;
    t1->next->prev = t1->prev;
    t1->next = nullptr;
    t1->prev = tail;
    tail->next = t1;
    tail = t1;
    cout << key << " " << "get: " << val << endl;
    return val;
  }

  void put(int key, int value)
  {
    if (record.find(key) != record.end())
    {
      record[key] = value;
      if (head->key == key)
      {
        tail->next = head;
        head->prev = tail;
        tail = tail->next;
        head = head->next;
        head->prev = nullptr;
        tail->next = nullptr;
        return;
      }
      else if (tail->key == key)
        return;
      Node *t1 = head;
      while (t1->key != key)
      {
        t1 = t1->next;
      }
      t1->prev->next = t1->next;
      t1->next->prev = t1->prev;
      t1->next = nullptr;
      t1->prev = tail;
      tail->next = t1;
      tail = t1;
      return;
    }
    if (!head && !tail)
    {
      record[key] = value;
      Node *newNode = new Node(key, value);
      head = newNode;
      tail = newNode;
      length++;
      return;
    }
    if (length < capacity)
    {
      record[key] = value;
      Node *newNode = new Node(key, value);
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
      length++;
      return;
    }
    record[key] = value;
    Node *newNode = new Node(key, value);
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;

    int k = head->key;
    record.erase(k);
    Node *t = head;
    head = head->next;
    t->next = nullptr;
    head->prev = nullptr;
    delete t;
    return;
  }
  void print() {
    cout << "Record:" << endl;
    for(auto r : record) {
      cout << "Key : " << r.first << " Value : " << r.second << endl;
    }
  }
};

int main(int argc, char const *argv[])
{
  LRUCache l(2);
  l.put(2, 1);
  l.put(1, 1);
  l.put(2, 3);
  l.put(4, 1);
  l.get(1);
  l.get(2);
  l.print();
  return 0;
}