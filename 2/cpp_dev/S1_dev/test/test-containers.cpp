#include "../src/Stack.hpp"
#include "../src/Queue.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace tampio;

TEST_CASE("Stack contains data as intended", "[Containers]")
{
    Stack<int> stack;

    // Undeflow excpetion expected.
    REQUIRE_THROWS_AS(stack.rm_back(), std::logic_error);
    REQUIRE(stack.isEmpty());

    stack.push(5);
    stack.push(2);
    stack.push(57);
    stack.push(10);
    stack.push(7);
    stack.push(8);
    stack.push(22);
    // INFO("The stack is " << stack);
    REQUIRE(stack.peek() == 22);
    stack.rm_back();
    REQUIRE(stack.peek() == 8);
    stack.rm_back();
    REQUIRE(stack.peek() == 7);
    stack.rm_back();
    REQUIRE(stack.peek() == 10);
    stack.rm_back();
    stack.push(89);
    stack.push(15);
    REQUIRE(stack.peek() == 15);
    stack.rm_back();
    REQUIRE(stack.peek() == 89);
    stack.rm_back();
    REQUIRE(stack.peek() == 57);
    stack.rm_back();
}

TEST_CASE("Queue contains data as intended", "[Containers]")
{
    Queue<int> queue;

    // добавляем в очередь элементы
    REQUIRE(queue.isEmpty());
    queue.push(8);
    queue.push(15);
    queue.push(16);
    queue.push(100);
    queue.push(-8);

    // выводим
    //    INFO("The queue is " << queue);

    // проверяем метод peek, должно вернуться число, помещённое в очередь первым
    REQUIRE(queue.peek() == 8);
    queue.rm_back();

    

    // ещё раз выводим
    //    INFO("The queue after first taking is " << queue);

    Queue< int > queue2 = queue; // здесь вызывается конструктор копирования (эквивалентно Queue queue2(queue);)

    // извлекаем ещё один элемент из исходной очереди
    REQUIRE(queue.peek() == 15);
    queue.rm_back();


    // и выводим, чтобы показать, что очереди разные
    //    INFO("After second taking from first queue:\n"
    //       << "queue: " << queue << "\nqueue2: " << queue2);
    REQUIRE(queue2.peek() == 15);
    queue2.rm_back();

    REQUIRE(queue2.peek() == 16);
    queue2.rm_back();


    queue2 = queue; // а вот здесь уже вызывается оператор присваивания
    REQUIRE((queue.peek() == 16 && queue2.peek() == 16));
    queue.rm_back();
    queue2.rm_back();


    // извлекаем оставшиеся элементы и "лишний"
    REQUIRE(queue.peek() == 100);
    queue.rm_back();

    REQUIRE(queue.peek() == -8);
    queue.rm_back();

    REQUIRE_THROWS_AS(queue.rm_back(), std::logic_error);
}
