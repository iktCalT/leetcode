#include <condition_variable>
#include <functional>
#include <mutex>

class Foo {
private:
  std::mutex mtx;
  std::condition_variable cv;
  bool first_finish;
  bool second_finish;

public:
  Foo() {
    first_finish = false;
    second_finish = false;
  }

  void first(std::function<void()> printFirst) {
      
    // printFirst() outputs "first". Do not change or remove this line.
    {
      std::unique_lock<std::mutex> lock(mtx);
      printFirst();
      first_finish = true;
    }
    cv.notify_all();
  }

  void second(std::function<void()> printSecond) {
      
    // printSecond() outputs "second". Do not change or remove this line.
    {
      std::unique_lock<std::mutex> lock(mtx);
      cv.wait(lock, [this]{return first_finish;});
      printSecond();
      second_finish = true;
    }
    cv.notify_all();
  }

  void third(std::function<void()> printThird) {
      
    // printThird() outputs "third". Do not change or remove this line.
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]{return second_finish;});
    printThird();
  }
};