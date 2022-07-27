#include "cfood/generic_object_pool.h"

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
  std::shared_ptr<PoolType> pool(new PoolType(std::shared_ptr<FactoryType>(), max_idle));
  for (int i = 0; i < 40; ++i) {
    // some other code
    {
      std::shared_ptr<SomeObject> obj = pool->get_object();
      obj->foo();
      // if some error occur
      // obj->set_reusable(false);
    }
  }
  return 0;
}
