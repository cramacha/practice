#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/*
 * We represent the animals in 3 different queues in this problem.
 * Queue 1: all - represents all the animals residing in order
 * from longest.
 * Queue 2: cats - only cats.
 * Queue 3: dogs - only dogs.
 *
 * Push(Insert) operation pushes an animal to queue 1 and queue 2
 * or 3 depending on type.
 *
 * Pop operation removes an animal from queue 1 and queue 2
 * or 3 depending on type.
 */
typedef enum animal_type
{
	DOG,
	CAT
}animal_type_t;

/*  Represents a single animal. */
class animal
{
public:
	animal();
	animal(animal_type_t);
	~animal();

	animal_type_t type;
};

/*  Represents the entire shelter of animals. */
class animals
{
public:
	animals();
	~animals();

	/*  Public accessors. */
	void insert(animal *);
	animal pop(void);
	animal pop_type(animal_type_t);

	/*  Friends */
	friend ostream& operator <<(ostream &, const vector<animal> &);

	vector<animal> all;
	vector<animal> cats;
	vector<animal> dogs;	
};

animal::animal()
{}

animal::~animal()
{}

animal::animal(animal_type_t input)
{
	type = input;
}

animals::animals()
{}

animals::~animals()
{
	for (int i = 0; i < all.size(); i++)
		all.erase(all.begin() + i);
}

void
animals::insert(animal *input)
{
	all.push_back(*input);

	if (DOG == input->type)
		dogs.push_back(*input);
	else
		cats.push_back(*input);
}

animal
animals::pop(void)
{
	assert (all.size() > 0);
	animal top = all.front();
	all.erase(all.begin());

	if (DOG == top.type)
		dogs.erase(dogs.begin());
	else
		cats.erase(cats.begin());
	return (top);
}

animal
animals::pop_type(animal_type_t input)
{
	vector<animal>::iterator it; 
	animal to_pop;
	assert (all.size() > 0);

	if (DOG == input)
		dogs.erase(dogs.begin());
	else
		cats.erase(cats.begin());
	for (it = all.begin(); it != all.end(); it++) {
		to_pop = *it;
		all.erase(it);	
	}
	return (to_pop);
}

ostream&
operator<< (ostream &out, animal &a)
{
	out << a.type;
	return (out);
}

ostream&
operator << (ostream &out, const vector<animal> &v)
{
	for (int i = 0; i < v.size(); i++)
		out << v.at(i).type << " ";
	out << endl;
	return (out);
}

animal *
get_animal(int num)
{
	if (num == 0)
		return (new animal(DOG));
	else
		return (new animal(CAT));
}

int
main(int argc, char **argv)
{
	int i;
	animals shelter;
	int n = atoi(argv[1]);

	for (i = 0; i < n; i++)
		shelter.insert(get_animal(rand() % 2));
	cout << shelter.all << endl;
	cout << shelter.cats << endl;
	cout << shelter.dogs << endl;

	animal top = shelter.pop();
	cout << top << endl;
	cout << shelter.all << endl;
	cout << shelter.cats << endl;
	cout << shelter.dogs << endl;

	top = shelter.pop();
	cout << top << endl;
	cout << shelter.all << endl;
	cout << shelter.cats << endl;
	cout << shelter.dogs << endl;

	top = shelter.pop();
	cout << top << endl;
	cout << shelter.all << endl;
	cout << shelter.cats << endl;
	cout << shelter.dogs << endl;

	top = shelter.pop();
	cout << top << endl;
	cout << shelter.all << endl;
	cout << shelter.cats << endl;
	cout << shelter.dogs << endl;


	return (0);
}
