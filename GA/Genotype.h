#pragma once

#include "vector"
#include "Gene.h"
#include "Source.h"
#include "algorithm"
#include <functional>

using namespace std;

template<typename ValueType>
class Genotype
{

protected:
	int _number_of_genes;
	vector<Gene<ValueType>>* genotype;
	double _fitness;

	function<void(Genotype<ValueType>&)> create_function;
	function<double(Genotype<ValueType>&, double**)> count_function_thread;
	function<double(Genotype<ValueType>&)> count_function;

	double** matrix_source;

	void create()
	{
		create_function(*this);
	}

	double count_fitness11(Gene<int> g)
	{
		int n_l, n_c;
		double fitness = 0;
		auto matr = Source::get_single_source();

		int num_of_gene = --g.get_gene()[0];
		n_l = Source::line_in_genes * (num_of_gene / Source::number_of_genes_in_line_matrix);
		n_c = Source::column_in_genes * (num_of_gene % Source::number_of_genes_in_line_matrix);

		for (size_t j = n_c; j < n_c + Source::column_in_genes; j++)
				{
			fitness += matr[n_l][j];
		}
		return fitness;
	}
public:
	Genotype() : _number_of_genes(0), _fitness(0), matrix_source(nullptr)
	{};

	Genotype(int number, function<double(Genotype<ValueType>&)> count_fun) : _number_of_genes(number), _fitness(0), matrix_source(nullptr)
	{
		genotype = new vector<Gene<ValueType>>();
		count_function = count_fun;
	}

	Genotype(int number, double** matr, function<double(Genotype<ValueType>&)> count_fun) : _number_of_genes(number), _fitness(0), matrix_source(matr)
	{
		genotype = new vector<Gene<ValueType>>();
		//count_function_thread = count_fun;
		count_function = count_fun;
	}

	Genotype(const Genotype& other) : _number_of_genes(other._number_of_genes), _fitness(other._fitness)
	{
		auto lenght = other.genotype->size();
		genotype = new vector<Gene<ValueType>>(lenght);

		copy(other.genotype->begin(), other.genotype->end(), genotype->begin());

		create_function = other.create_function;
		count_function_thread = other.count_function_thread;
	}

	Genotype(Genotype&& other) : _number_of_genes(other._number_of_genes), _fitness(other._fitness)
	{
		genotype = new vector<Gene<ValueType>>(move(*other.genotype));
		//genotype = other.genotype;
		create_function = other.create_function;
		count_function_thread = other.count_function_thread;

		//delete other.genotype;
		//other.genotype = nullptr;
	}

	Genotype(int number, function<void(Genotype<ValueType>&)> _create, function<double(Genotype<ValueType>&)> _count) :
		_number_of_genes(number), _fitness(0)
	{
		create_function = _create;
		count_function = _count;

		genotype = new vector<Gene<ValueType>>();

		create();
		count_fitness();
	}

	Genotype<ValueType>& operator=(const Genotype<ValueType>& other);
	Genotype<ValueType>& operator=(Genotype<ValueType>&& other);

	void sort_gen()
	{
		for_each(genotype->begin(), genotype->end(), [](Gene<ValueType> item)
		{
			cout << item.get_gene()[0] << endl;
		});

		sort(genotype->begin(), genotype->end(), [this](Gene<ValueType>& g1, Gene<ValueType>& g2)
		{
			return count_fitness11(g1) < count_fitness11(g2);
		});
	}

	~Genotype()
	{
		/*if (genotype->capacity() != 0)
			delete genotype;*/
	};

	double get_fitness() const
	{
		return _fitness;
	}

	void count_fitness()
	{
		_fitness = count_function(*this);
	}

	void count_fitness_thread()
	{
		_fitness = count_function_thread(*this, matrix_source);
	};

	vector<Gene<ValueType>>* get_genotype();
	int get_number_of_genes() const;

private:
	friend class Fit_Fun;

public:
};

template <typename ValueType>
Genotype<ValueType>& Genotype<ValueType>::operator=(const Genotype<ValueType>& other)
{
	genotype = new vector<Gene<ValueType>>(*other.genotype);

	_number_of_genes = other._number_of_genes;
	_fitness = other._fitness;
	create_function = other.create_function;
	count_function_thread = other.count_function_thread;

	return *this;
};

template <typename ValueType>
Genotype<ValueType>& Genotype<ValueType>::operator=(Genotype<ValueType>&& other)
{
	if (this != &other)
	{
		genotype = new vector<Gene<ValueType>>(move(*other.genotype));

		_number_of_genes = other._number_of_genes;
		_fitness = other._fitness;
		create_function = other.create_function;
		count_function_thread = other.count_function_thread;

		delete other.genotype;
	}
	return *this;
};

template<typename ValueType>
vector<Gene<ValueType>>* Genotype<ValueType>::get_genotype()
{
	return genotype;
};

template<typename ValueType>
int Genotype<ValueType>::get_number_of_genes() const
{
	return _number_of_genes;
};


