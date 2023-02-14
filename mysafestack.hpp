#include <deque>
#include <stack>
#include <stdexcept>
#include <string>


using namespace std::string_literals;

template <typename T, typename Container=std::deque<T>>
class MySafeStack : public std::stack<T, Container> {
public:
    // inherit all original constructors.
    using std::stack<T, Container>::stack;

    // top() and pop() are not safe when stack is empty. They cause Undefined Behavior.
    // So, I defined safePop() and delete original top() and pop().
    void pop() = delete;
    T & top() = delete;
    auto safePop() -> T {
        if(this->empty()) {
            throw std::out_of_range("out of range: in MysafeStack::safePop()"s);
        }
        auto tmpEl = std::stack<T, Container>::top();
        std::stack<T, Container>::pop();
        return tmpEl;
    }

    // add to access underlying container and it's iterator.
    auto getUnderlyingContainer() -> const Container {
        return this->c;
    }
    auto begin() {
        return this->c.begin();
    }
    auto end() {
        return this->c.end();
    }
    auto cbegin() {
        return this->c.cbegin();
    }
    auto cend() {
        return this->c.cend();
    }
};
template<class Container> MySafeStack(Container)->MySafeStack<typename Container::value_type, Container>;

