
#include <cassert>
#include <list>

#include "DoublyLinkedList.h"
#include "Person.h"

static void testSimplePerson()
{
    Person person("abc", 5);
    Person equalPerson("abc", 5);

    assert(person == equalPerson);

    Person nameDiffPerson("aec", 5);
    Person ageDiffPerson("abc", 4);

    assert(person.operator==(nameDiffPerson) == false);
    assert(person.operator==(ageDiffPerson) == false);

    Person movedPerson(std::move(person));
    assert(person.GetName() == nullptr);
    assert(movedPerson == equalPerson);
}

static void testSimpleDoublyLinkedList()
{
    Person personA("a", 5);
    Person personB("b", 5);
    Person personC("c", 2);
    Person personD("d", 15);
    Person personE("e", 25);
    Person personF("f", 4);

    Person equalPersonA("a", 5);
    Person equalPersonB("b", 5);
    Person equalPersonC("c", 2);
    Person equalPersonD("d", 15);
    Person equalPersonE("e", 25);
    Person equalPersonF("f", 4);

    DoublyLinkedList<Person> doublyLinkedList;

    // Test Add()
    {
        doublyLinkedList.AddFront(std::move(personA));
        assert(doublyLinkedList.HasValue(equalPersonA));
        assert(*doublyLinkedList.GetValue(0) == equalPersonA);

        doublyLinkedList.AddFront(std::move(personB));
        assert(doublyLinkedList.HasValue(equalPersonB));
        assert(*doublyLinkedList.GetValue(0) == equalPersonB);
        assert(*doublyLinkedList.GetValue(1) == equalPersonA);

        doublyLinkedList.AddBack(std::move(personC));
        assert(doublyLinkedList.HasValue(equalPersonC));
        assert(*doublyLinkedList.GetValue(0) == equalPersonB);
        assert(*doublyLinkedList.GetValue(1) == equalPersonA);
        assert(*doublyLinkedList.GetValue(2) == equalPersonC);

        doublyLinkedList.Add(1, std::move(personD));
        assert(doublyLinkedList.HasValue(equalPersonD));
        assert(*doublyLinkedList.GetValue(0) == equalPersonB);
        assert(*doublyLinkedList.GetValue(1) == equalPersonD);
        assert(*doublyLinkedList.GetValue(2) == equalPersonA);
        assert(*doublyLinkedList.GetValue(3) == equalPersonC);

        doublyLinkedList.Add(3, std::move(personE));
        assert(doublyLinkedList.HasValue(equalPersonD));
        assert(*doublyLinkedList.GetValue(0) == equalPersonB);
        assert(*doublyLinkedList.GetValue(1) == equalPersonD);
        assert(*doublyLinkedList.GetValue(2) == equalPersonA);
        assert(*doublyLinkedList.GetValue(3) == equalPersonE);
        assert(*doublyLinkedList.GetValue(4) == equalPersonC);

        doublyLinkedList.Add(5, std::move(personF));
        assert(doublyLinkedList.HasValue(equalPersonD));
        assert(*doublyLinkedList.GetValue(0) == equalPersonB);
        assert(*doublyLinkedList.GetValue(1) == equalPersonD);
        assert(*doublyLinkedList.GetValue(2) == equalPersonA);
        assert(*doublyLinkedList.GetValue(3) == equalPersonE);
        assert(*doublyLinkedList.GetValue(4) == equalPersonC);
        assert(*doublyLinkedList.GetValue(5) == equalPersonF);
    }

    // Test Remove()
    {
        assert(doublyLinkedList.RemoveFront());
        assert(doublyLinkedList.HasValue(equalPersonB) == false);
        assert(*doublyLinkedList.GetValue(0) == equalPersonD);
        assert(*doublyLinkedList.GetValue(1) == equalPersonA);
        assert(*doublyLinkedList.GetValue(2) == equalPersonE);
        assert(*doublyLinkedList.GetValue(3) == equalPersonC);
        assert(*doublyLinkedList.GetValue(4) == equalPersonF);

        assert(doublyLinkedList.RemoveBack());
        assert(doublyLinkedList.HasValue(equalPersonF) == false);
        assert(*doublyLinkedList.GetValue(0) == equalPersonD);
        assert(*doublyLinkedList.GetValue(1) == equalPersonA);
        assert(*doublyLinkedList.GetValue(2) == equalPersonE);
        assert(*doublyLinkedList.GetValue(3) == equalPersonC);

        assert(doublyLinkedList.Remove(equalPersonA));
        assert(doublyLinkedList.HasValue(equalPersonA) == false);
        assert(*doublyLinkedList.GetValue(0) == equalPersonD);
        assert(*doublyLinkedList.GetValue(1) == equalPersonE);
        assert(*doublyLinkedList.GetValue(2) == equalPersonC);

        assert(doublyLinkedList.Remove(equalPersonE));
        assert(doublyLinkedList.HasValue(equalPersonE) == false);
        assert(*doublyLinkedList.GetValue(0) == equalPersonD);
        assert(*doublyLinkedList.GetValue(1) == equalPersonC);

        assert(doublyLinkedList.RemoveRandom());
        assert(doublyLinkedList.RemoveRandom());
        assert(doublyLinkedList.HasValue(equalPersonD) == false);
        assert(doublyLinkedList.HasValue(equalPersonC) == false);

        assert(doublyLinkedList.IsEmpty());
    }
}

int main()
{
    testSimplePerson();
    testSimpleDoublyLinkedList();

    return 0;
}