#include <iostream>
using namespace std;

class HitCounter
{
private:
  int *times;
  int *hits;

public:
  HitCounter()
  {
    times = new int[300];
    hits = new int[300];

    for (int i = 0; i < 300; i++)
    {
      times[i] = 0;
      hits[i] = 0;
    }
  }

  void hit(int timestamp)
  {
    int index = timestamp % 300;
    if (times[index] != timestamp)
    {
      times[index] = timestamp;
      hits[index] = 1;
    }
    else
    {
      hits[index]++;
    }
    return;
  }
  int getHits(int timestamp)
  {
    int totalHits = 0;
    for (int i = 0; i < 300; i++)
    {
      int timeDiff = timestamp - times[i];
      if (timeDiff < 300 && timeDiff >= 0)
        totalHits += hits[i];
    }
    return totalHits;
  }
  ~HitCounter()
  {
    delete[] times;
    delete[] hits;
  }
};

int main(int argc, char const *argv[])
{
  HitCounter c;
  c.hit(0);
  c.hit(605);
  c.hit(660);

  cout << c.getHits(700);
  return 0;
}