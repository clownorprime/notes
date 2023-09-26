class Adaptee {
public:
    void specificRequest() {
        // 执行特定的操作
    }
};

// 目标接口
class Target {
public:
    virtual void request() = 0;
};

// 适配器类，通过多重继承同时继承 Adaptee 和 Target
class Adapter : public Adaptee, public Target {
public:
    void request() override {
        specificRequest();  // 调用被适配类的方法
    }
};

int main() {
    Target* target = new Adapter();  // 使用适配器作为目标接口
    target->request();  // 通过目标接口调用被适配类的方法
    // ...
    delete target;
    return 0;
}
