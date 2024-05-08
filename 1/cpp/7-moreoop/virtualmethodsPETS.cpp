#include <string>
#include <iostream>

class Pet
{
public:
	Pet() :
		name_("")
	{}
	Pet(const std::string& name) :
		name_(name)
	{}
	std::string name() const 
	{
		return name_;
	}
	virtual std::string voice() const = 0;
	virtual ~Pet() = default;
private:
	std::string name_;
};

class Cat : public Pet
{
public:
	Cat() 
	{}
	Cat(const std::string& name):
		Pet(name)
	{}
	virtual std::string voice() const override 
	{
		return "miau";
	}
};

class Dog : public Pet
{
public:
	Dog()
	{}
	Dog(const std::string& name) :
		Pet(name)
	{}
	virtual std::string voice() const override 
	{
		return "bark";
	}
};

class FamilyPets {
public:
	FamilyPets() :
		size_(0),
		capacity_(1),
		array_(new Pet*[1])
	{}

	void add(Pet* p) 
	{
		if(capacity_ == size_)
		{
			capacity_ *= MULTIPLIER;
			Pet** a = new Pet*[capacity_];
			for (int i = 0; i < size_; i++) 
			{
				a[i] = array_[i];
			}
			delete[] array_;
			array_ = a;
		}
		array_[size_] = p;
		++size_;
	}
	
	void voice(std::ostream& os) {
		for (int i = 0; i < size_; i++) {
			os << array_[i]->name() << " says " << array_[i]->voice() << '\n';
		}
	}

private:
	static const int MULTIPLIER = 2;
	int size_;
	int capacity_;
	Pet** array_;
};

int main() 
{
	Cat ob1("Charlie");
	Pet* pob1 = &ob1;
	std::cout << ob1.voice() << '\n';
	std::cout << pob1->voice() << '\n';

	Dog ob2("Doran");
	Pet* pob2 = &ob2;
	std::cout << ob2.voice() << '\n';
	std::cout << pob2->voice() << '\n';

	Cat ob3("Lora");
	Cat ob4("Neeko");
	
	FamilyPets pets;
	pets.add(&ob1);
	pets.add(&ob2);
	pets.add(&ob3);
	pets.add(&ob4);
	std::cout << "\nFamily voice:\n";
	pets.voice(std::cout);
		
	//Задание на dynamic_cast
	//Проверить, есть ли кошка с указанным именем
	//Если успешно прикастился к Cat* то сравниваем

	return 0;
}