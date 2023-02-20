#ifndef MY_MYSAFESTACK_HPP
#define MY_MYSAFESTACK_HPP

#include <deque>
#include <stack>
#include <stdexcept>
#include <string>

namespace {
    using namespace std::string_literals;

    template <typename T, typename Container=std::deque<T>>
    class MySafeStack : public std::stack<T, Container> {
    public:
        // inherit all original constructors.
        using std::stack<T, Container>::stack;

        // Constructor with iterators, this will appear in c++23, but not c++17
        template<typename Iter>
        MySafeStack(Iter firstIter, Iter lastIter) : std::stack<T, Container>(Container(firstIter, lastIter)) {}

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
        auto getUnderlyingContainer() -> Container {
            return this->c;
        }
        auto begin() {
            return this->c.begin();
        }
        auto end() {
            return this->c.end();
        }
        auto cbegin() const {
            return this->c.cbegin();
        }
        auto cend() const {
            return this->c.cend();
        }
    };
    template<class Container> MySafeStack(Container)->MySafeStack<typename Container::value_type, Container>;

}

#endif
