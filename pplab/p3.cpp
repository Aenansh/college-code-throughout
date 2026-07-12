#include <iostream>
#include <cstring>
using namespace std;

class Node
{
public:
  string site;
  Node *prev;
  Node *next;
  Node(string s)
  {
    site = s;
    prev = nullptr;
    next = nullptr;
  }
};

class BrowserHistory
{
private:
  Node *currentTab;

public:
  BrowserHistory(string site)
  {
    currentTab = new Node(site);
  }
  void visit(string url)
  {
    Node *newNode = new Node(url);
    if (currentTab->next != nullptr)
    {
      Node *temp = currentTab->next;
      while (temp != nullptr)
      {
        Node *removedUrl = temp;
        temp = temp->next;
        delete removedUrl;
      }
    }
    currentTab->next = newNode;
    newNode->prev = currentTab;
    currentTab = newNode;
    cout << "On: " << currentTab->site << endl;
    return;
  }

  string back(int steps)
  {
    if (steps <= 0)
      return currentTab->site;
    while (steps > 0 && currentTab->prev)
    {
      currentTab = currentTab->prev;
      steps--;
    }
    return currentTab->site;
  }

  string forward(int steps)
  {
    if (steps <= 0)
      return currentTab->site;
    while (steps > 0 && currentTab->next)
    {
      currentTab = currentTab->next;
      steps--;
    }
    return currentTab->site;
  }
};
int main(int argc, char const *argv[])
{
  BrowserHistory b("www.google.com");
  b.visit("www.facebook.com");
  b.visit("www.youtube.com");
  cout << b.back(3);
  b.visit("www.linkedIn.com");
  cout << b.forward(1);
  return 0;
}