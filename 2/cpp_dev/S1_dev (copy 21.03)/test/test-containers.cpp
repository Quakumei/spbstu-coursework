#include "../src/Stack.hpp"
#include "../src/Queue.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("List works as Stack", "[Containers]")
{
    List<int> stack;

    // Undeflow excpetion expected.
    REQUIRE_THROWS_AS(stack.dropFront(), std::logic_error);
    REQUIRE_THROWS_AS(stack.dropBack(), std::logic_error);
    REQUIRE(stack.isEmpty());

    stack.pushBack(5);
    REQUIRE(stack.dropFront() == 5);

    stack.pushBack(5);
    stack.pushBack(2);
    stack.pushBack(57);
    stack.pushBack(10);
    stack.pushBack(7);
    stack.pushBack(8);
    stack.pushBack(22);
    // INFO("The stack is " << stack);
    REQUIRE(stack.dropFront() == 22);
    REQUIRE(stack.dropFront() == 8);
    REQUIRE(stack.dropFront() == 7);
    REQUIRE(stack.dropFront() == 10);
    stack.pushBack(89);
    stack.pushBack(15);
    REQUIRE(stack.dropFront() == 15);
    REQUIRE(stack.dropFront() == 89);
    REQUIRE(stack.dropFront() == 57);
}

TEST_CASE("List as queue", "[Containers]")
{
    List<int> queue;

    // добавляем в очередь элементы
    REQUIRE(queue.isEmpty());
    queue.pushFront(8);
    queue.pushFront(15);
    queue.pushFront(16);
    queue.pushFront(100);
    queue.pushFront(-8);

    // выводим
    //    INFO("The queue is " << queue);

    // проверяем метод drop, должно вернуться число, помещённое в очередь первым
    REQUIRE(queue.dropFront() == 8);

    // ещё раз выводим
    //    INFO("The queue after first taking is " << queue);

    List<int> queue2 = queue; // здесь вызывается конструктор копирования (эквивалентно Queue queue2(queue);)

    // извлекаем ещё один элемент из исходной очереди
    REQUIRE(queue.dropFront() == 15);

    // и выводим, чтобы показать, что очереди разные
    //    INFO("After second taking from first queue:\n"
    //       << "queue: " << queue << "\nqueue2: " << queue2);
    REQUIRE(queue2.dropFront() == 15);
    REQUIRE(queue2.dropFront() == 16);

    queue2 = queue; // а вот здесь уже вызывается оператор присваивания
    REQUIRE((queue.dropFront() == 16 && queue2.dropFront() == 16));

    // извлекаем оставшиеся элементы и "лишний"
    REQUIRE(queue.dropFront() == 100);
    REQUIRE(queue.dropFront() == -8);
    REQUIRE_THROWS_AS(queue.dropFront(), std::logic_error);
}

TEST_CASE("Stack contains data as intended", "[Containers]")
{
    Stack<int> stack;

    // Undeflow excpetion expected.
    REQUIRE_THROWS_AS(stack.drop(), std::logic_error);
    REQUIRE(stack.isEmpty());

    stack.push(5);
    stack.push(2);
    stack.push(57);
    stack.push(10);
    stack.push(7);
    stack.push(8);
    stack.push(22);
    // INFO("The stack is " << stack);
    REQUIRE(stack.drop() == 22);
    REQUIRE(stack.drop() == 8);
    REQUIRE(stack.drop() == 7);
    REQUIRE(stack.drop() == 10);
    stack.push(89);
    stack.push(15);
    REQUIRE(stack.drop() == 15);
    REQUIRE(stack.drop() == 89);
    REQUIRE(stack.drop() == 57);
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

    // проверяем метод drop, должно вернуться число, помещённое в очередь первым
    REQUIRE(queue.drop() == 8);

    // ещё раз выводим
    //    INFO("The queue after first taking is " << queue);

    Queue<int> queue2 = queue; // здесь вызывается конструктор копирования (эквивалентно Queue queue2(queue);)

    // извлекаем ещё один элемент из исходной очереди
    REQUIRE(queue.drop() == 15);

    // и выводим, чтобы показать, что очереди разные
    //    INFO("After second taking from first queue:\n"
    //       << "queue: " << queue << "\nqueue2: " << queue2);
    REQUIRE(queue2.drop() == 15);
    REQUIRE(queue2.drop() == 16);

    queue2 = queue; // а вот здесь уже вызывается оператор присваивания
    REQUIRE((queue.drop() == 16 && queue2.drop() == 16));

    // извлекаем оставшиеся элементы и "лишний"
    REQUIRE(queue.drop() == 100);
    REQUIRE(queue.drop() == -8);
    REQUIRE_THROWS_AS(queue.drop(), std::logic_error);
}
