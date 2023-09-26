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

// 适配器类，通过组合关系引入 Adaptee 对象，并实现目标接口
class Adapter : public Target {
public:
    Adapter(Adaptee* adaptee) : adaptee_(adaptee) {}

    void request() override {
        adaptee_->specificRequest();  // 调用被适配类的方法
    }

private:
    Adaptee* adaptee_;
};

int main() {
    Adaptee* adaptee = new Adaptee();
    Target* target = new Adapter(adaptee);  // 使用适配器作为目标接口
    target->request();  // 通过目标接口调用被适配类的方法
    // ...
    delete target;
    delete adaptee;
    return 0;
}
