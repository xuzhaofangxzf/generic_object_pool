#include "cfood/generic_object_pool.h"
#include <vector>
#include <time.h>
#include <chrono>
class SomeObject : public cfood::PoolableObject {
public:
  SomeObject() {
    std::cout << "SomeObject::SomeObject()" << std::endl;
  }
  ~SomeObject() {
    std::cout << "SomeObject::~SomeObject()" << std::endl;
  }
  void foo() {
    std::cout << "SomeObject::foo()" << std::endl;
  }
};
int main(int argc, const char** argv) {
  typedef cfood::GenericObjectPool<SomeObject> PoolType;
  typedef cfood::PoolableObjectFactory<SomeObject> FactoryType;
  size_t max_idle = 5;
  std::shared_ptr<PoolType> pool(new PoolType(std::shared_ptr<FactoryType>()));
  std::vector<std::thread> thread_pools;
  for (int i = 0; i < 40; ++i) {
    // some other code
    std::thread obj_thread([&](std::shared_ptr<PoolType> pool) { 
      std::shared_ptr<SomeObject> obj = pool->get_object();
      obj->foo();
      std::this_thread::sleep_for(std::chrono::seconds(10));
    }, pool);
    thread_pools.emplace_back(std::move(obj_thread));
      // if some error occur
      // obj->set_reusable(false);
  }
    for (auto iter = thread_pools.begin(); iter != thread_pools.end(); ++iter) {
        iter->join();
    }
  return 0;
}
