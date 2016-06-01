#pragma once

#include "Population.h"
#include <random>
#include <vector>
#include "Fit_Fun.h"

using namespace std;

class Recombination
{
	Recombination();

	template<typename ValueType>
	static void r_primer(Population<ValueType>&);

	// Операторы рекомбинации (воспроизведения) - дискретная и кроссинговер 
	template<typename ValueType>
	static void r_discrete(Population<ValueType>&);

	//промежуточная рекомбинация
	template<typename ValueType>
	static void r_intermediate(Population<ValueType>&);

	//линейная рекомбинация
	template<typename ValueType>
	static void r_line(Population<ValueType>&);

	// Методы кроссинговера 

	//одноточечный кроссинговер
	template<typename ValueType>
	static void r_singlepoint(Population<ValueType>&);

	//двухточечный кроссинговер
	template<typename ValueType>
	static void r_doublepoint(Population<ValueType>&);

	//многоточечный кроссинговер
	template<typename ValueType>
	static void r_multipoint(Population<ValueType>&);

	//триадный кроссинговер
	template<typename ValueType>
	static void r_triadic(Population<ValueType>&);

	//однородный кроссинговер
	template<typename ValueType>
	static void r_uniform(Population<ValueType>&);

	//перетасовочный кроссинговер
	template<typename ValueType>
	static void r_shuffler(Population<ValueType>&);

	//кроссинговер с уменьшением замены
	template<typename ValueType>
	static void r_crossover_with_reduced_surrogate(Population<ValueType>&);

public:
	template<typename ValueType>
	static function<void(Population<ValueType>&)> primer()
	{
		return [](Population<ValueType>& p) { r_primer(p); };
	}


	template<typename ValueType>
	static function<void(Population<ValueType>&)> discrete()
	{
		return [](Population<ValueType>& p) { r_discrete(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> intermediate()
	{
		return [](Population<ValueType>& p) { r_intermediate(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> line()
	{
		return [](Population<ValueType>& p) { r_line(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> singlepoint()
	{
		return [](Population<ValueType>& p) { r_singlepoint(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> doublepoint()
	{
		return [](Population<ValueType>& p) { r_doublepoint(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> multipoint()
	{
		return [](Population<ValueType>& p) { r_multipoint(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> triadic()
	{
		return [](Population<ValueType>& p) { r_triadic(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> uniform()
	{
		return [](Population<ValueType>& p) { r_uniform(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> shuffler()
	{
		return [](Population<ValueType>& p) { r_shuffler(p); };
	}

	template<typename ValueType>
	static function<void(Population<ValueType>&)> crossover_with_reduced_surrogate()
	{
		return [](Population<ValueType>& p) { r_crossover_with_reduced_surrogate(p); };
	}
};

template<typename ValueType>
double count_fitness11(Gene<ValueType> g)
{
	int n_l, n_c;
	double fitness = 0;
	auto matr = Source::Instance()->get_source();

	int num_of_gene = g.get_gene()[0];
	num_of_gene--;
	n_l = Source::line_in_genes * (num_of_gene / Source::number_of_genes_in_line_matrix);
	n_c = Source::column_in_genes * (num_of_gene % Source::number_of_genes_in_line_matrix);

	for (size_t j = n_c; j < n_c + Source::column_in_genes; j++)
	{
		fitness += matr[n_l][j];
	}
	return fitness;
}

template<typename ValueType>
void Recombination::r_primer(Population<ValueType>& p)
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_int_distribution(1, Source::total_genes);

	Genotype<ValueType> ch(Source::number_of_genes_in_genotype, p.matr, Fit_Fun::get_count<ValueType>());

	//p.parent->sort_gen();
	//p._parent->sort_gen();

	for (size_t i = 0; i < Source::number_of_genes_in_genotype; i++)
	{
		auto t1 = count_fitness11(p.parent->get_genotype()->at(i));
		auto t2 = count_fitness11(p._parent->get_genotype()->at(i));

		if (p.parent->get_genotype()->at(i).get_gene()[0] == p._parent->get_genotype()->at(i).get_gene()[0])
		{
			auto temp = Gene<int>(1);
			temp.get_gene()[0] = p.parent->get_genotype()->at(i).get_gene()[0];//uniform_int_distribution(generator);
			ch.get_genotype()->push_back(move(temp));
		}
		else
		{
			if (t1 < t2)
			{
				vector<Gene<int>>::iterator it = p.parent->get_genotype()->begin();
				Gene<ValueType> g = it[i];
				/*if (g.get_gen() < 0)
				{
					g.get_gene()[0] = uniform_int_distribution(generator);;
					ch.get_genotype()->push_back(g);
				}
				else*/
				ch.get_genotype()->push_back(g);
			}
			else
			{
				vector<Gene<int>>::iterator it = p._parent->get_genotype()->begin();
				Gene<ValueType> g = it[i];
				/*if (g.get_gen() < 0)
				{
					g.get_gene()[0] = uniform_int_distribution(generator);;
					ch.get_genotype()->push_back(g);
				}
				else */
				ch.get_genotype()->push_back(g);
			}
		}
	}

	//ch.count_fitness();
	//cout << ch.get_fitness() << endl;

	//vector<int> genotype;

	//for_each(ch.get_genotype()->begin(), ch.get_genotype()->end(), [&genotype](Gene<ValueType> item)
	//{
	//	genotype.push_back(item.get_gen());
	//});

	//sort(genotype.begin(), genotype.end());
	//bool flag = true;
	//for (size_t i = 0; i < genotype.size(); i++)
	//{
	//	while (flag) {
	//		flag = false;
	//		if (binary_search(genotype.begin() + i + 1, genotype.end(), genotype[i]))
	//		{
	//			genotype[i] = uniform_int_distribution(generator);
	//			flag = true;
	//		}
	//	}
	//}

	//ch.get_genotype()->clear();

	//for_each(genotype.begin(), genotype.end(), [&genotype, &ch](int item)
	//{
	//	Gene<ValueType> g(1);
	//	g.get_gene()[0] = item;
	//	ch.get_genotype()->push_back(move(g));
	//});

	for (size_t i = 0; i < ch.get_genotype()->size(); i++)
	{
		for (size_t j = i + 1; j < ch.get_genotype()->size(); j++)
		{
			if (ch.get_genotype()->at(j).get_gene()[0] == ch.get_genotype()->at(i).get_gene()[0])
			{
				ch.get_genotype()->at(i).get_gene()[0] = uniform_int_distribution(generator);
				j = i + 1;
			}
		}
	}

	for (size_t i = 0; i < ch.get_genotype()->size(); i++)
	{
		for (size_t j = i + 1; j < ch.get_genotype()->size(); j++)
		{
			if (ch.get_genotype()->at(j).get_gene()[0] == ch.get_genotype()->at(i).get_gene()[0])
			{
				ch.get_genotype()->at(i).get_gene()[0] = uniform_int_distribution(generator);
				j = i + 1;
			}
		}
	}

	ch.count_fitness();
	//cout << ch.get_fitness();
	p.childrn_vector->push_back(move(ch));
}


template <typename ValueType>
void Recombination::r_discrete(Population<ValueType>& p)
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_int_distribution(0, 1);
	/*int count = p.parent_vector->size();
	count--;*/
	/*vector<Gene<ValueType>> parents[] = { *p.parent_vector->at(count).get_genotype(),
	*p.parent_vector->at(--count).get_genotype() };*/

	vector<Gene<ValueType>> parents[] = { *p.parent->get_genotype(), *p._parent->get_genotype() };

	/*p.child = new Genotype<ValueType>(7807, Fit_Fun::get_count<ValueType>());
	p._child = new Genotype<ValueType>(7807, Fit_Fun::get_count<ValueType>());*/

	Genotype<ValueType> ch(7807, Fit_Fun::get_count<ValueType>());
	Genotype<ValueType> ch2(7807, Fit_Fun::get_count<ValueType>());
	for (size_t i = 0; i < 7807; i++)
	{
		auto n = static_cast<bool>(uniform_int_distribution(generator));
		//p.child->get_genotype()->push_back(parents[n][i]);
		ch.get_genotype()->push_back(parents[n][i]);
		//p._child->get_genotype()->push_back(parents[!n][i]);
		ch2.get_genotype()->push_back(parents[!n][i]);
	}

	//перенести в выз.функцию
	/*p.child->count_fitness();
	p._child->count_fitness();*/

	ch.count_fitness();
	ch2.count_fitness();

	p.childrn_vector->push_back(move(ch));
	p.childrn_vector->push_back(move(ch2));

	//delete p.child;
	//delete p._child;
}

template <typename ValueType>
void Recombination::r_intermediate(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_line(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_singlepoint(Population<ValueType>& p)
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_int_distribution(0, *p.parent->get_number_of_genes());
	auto point = uniform_int_distribution(generator);

	for (size_t i = 0; i < point; i++)
	{
		*p.child->get_genotype()->push_back(p.parent[i]);
		*p._child->get_genotype()->push_back(p._parent[i]);
	}

	for (size_t i = point; i < *p.parent->get_number_of_genes(); i++)
	{
		*p.child->get_genotype()->push_back(p._parent[i]);
		*p._child->get_genotype()->push_back(p.parent[i]);
	}
	p.childrn_vector.push_back(p.child);
	p.childrn_vector.push_back(p._child);
}

template <typename ValueType>
void Recombination::r_doublepoint(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_multipoint(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_triadic(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_uniform(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_shuffler(Population<ValueType>&)
{
}

template <typename ValueType>
void Recombination::r_crossover_with_reduced_surrogate(Population<ValueType>&)
{
}
