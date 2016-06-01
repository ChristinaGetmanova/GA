#pragma once

#include "Source.h"
#include <vector>
#include "Genotype.h"
#include <functional>

using namespace std;

template<typename ValueType>
class Population
{
	int number_of_genotype;//объем попул€ции
	bool die_notigkeit_der_mutation;

	Genotype<ValueType>* parent, *_parent;//особи, которые будут родител€ми
	Genotype<ValueType>* child, *_child;// дети, которые получаютс€ при скрещивании 
	vector<Genotype<ValueType>>* parent_vector;
	vector<Genotype<ValueType>>* childrn_vector;

	//функци€ селекции родителей
	function<void(Population<ValueType>&)> selection;

	//функции рекомбинации (воспроизведени€)
	function<void(Population<ValueType>&)> recombination;

	//функции мутации
	function<void(Population<ValueType>&)> mutation;

	//функции отбора особей в новую попул€цию
	function<void(Population<ValueType>&)> sampling;

	vector<Genotype<ValueType>>* population;
	double** matr;

public:
	Population()
	{
	}

	vector<Genotype<ValueType>>* get_pop()
	{
		return population;
	};

	Population(const int number, vector<Genotype<ValueType>>* gene, function<void(Population<ValueType>&)> select_function,
		function<void(Population<ValueType>&)> rec_function, function<void(Population<ValueType>&)> mut_function,
		function<void(Population<ValueType>&)> samp_function);

	//классы-друзь€ дл€ получени€ доступа к приватным переменным попул€ции и вынесени€ логики работы с особ€ми в отдельные классы
	friend class Selection;
	friend class Recombination;
	friend class Mutation;
	friend class Select_In_Population;

	void select()
	{
		selection(*this);
	}

	void mut()
	{
		mutation(*this);
	}

	void recom()
	{
		recombination(*this);
	}

	void select_in_population()
	{
		sampling(*this);
		delete childrn_vector;
		//delete parent_vector;
		//std::cout << "11";
		//delete parent; delete _parent;
		parent = nullptr;
		_parent = nullptr;
		//parent_vector = new vector<Genotype<ValueType>>();
		childrn_vector = new vector<Genotype<ValueType>>();

	}
//	Population() : number_of_genotype(0), die_notigkeit_der_mutation(false) {};

};

template<typename ValueType>
Population<ValueType>::Population(const int number, vector<Genotype<ValueType>>* gene,
	function<void(Population<ValueType>&)> select_function,
	function<void(Population<ValueType>&)> rec_function,
	function<void(Population<ValueType>&)> mut_function,
	function<void(Population<ValueType>&)> samp_function) : die_notigkeit_der_mutation(false)
{
	number_of_genotype = number;
	population = new vector<Genotype<ValueType>>(move(*gene));
	//	vector<Genotype<ValueType>>(*population).swap(*population);
	selection = select_function;
	recombination = rec_function;
	mutation = mut_function;
	sampling = samp_function;

	matr = Source::Instance()->get_source();
	parent = nullptr;
	_parent = nullptr;

	/*parent = new Genotype<ValueType>();
	_parent = new Genotype<ValueType>();*/

	parent_vector = new vector<Genotype<ValueType>>();
	childrn_vector = new vector<Genotype<ValueType>>();
};

