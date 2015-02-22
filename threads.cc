// Simple toy thread playing with good vs bad use of threads.
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>

int main(int argc, char **argv)
{
  std::mutex m;
  int x1 = 0;
  const auto f1 = [&x1](std::mutex *m) {
    for (int i = 0; i < 1000000; i++) {
      m->lock();
      x1++;
      m->unlock();
    }
  };
  const auto f2 = [&x1](std::mutex *m) {
    for (int i = 0; i < 1000000; i++) {
      x1++;
    }
  };
  std::thread t1, t2;
  if (argc > 1 && argv[1][0] == 'm') {
    // 5.8 seconds. Mostly in sys. Correct.
    t1 = std::thread(f1, &m);
    t2 = std::thread(f1, &m);
  } else if (argc > 1 && argv[1][0] == 'a') {
    // 0.1 seconds. Correct.
    std::atomic<int> ai(0);
    const auto f = [&ai]() {
      for (int i = 0; i < 1000000; i++) {
        ai++;
      }
    };
    t1 = std::thread(f);
    t2 = std::thread(f);
    t1.join();
    t2.join();
    std::cout << ai << std::endl;
    return 0;
  } else {
    // 0.08s. Wrong.
    t1 = std::thread(f2, &m);
    t2 = std::thread(f2, &m);
  }
  t1.join();
  t2.join();
  std::cout << x1 << std::endl;
}
