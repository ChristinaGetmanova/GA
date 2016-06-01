#pragma once
#include "random"
#include "algorithm"
#include "functional"
#include "Genotype.h"
#include "Source.h"

class Fit_Fun
{
public:
	template<typename ValueType>
	static function<double(Genotype<ValueType>&)> get_count()
	{
		return[](Genotype<ValueType>& temp) {return _count(temp); };
	}

	/*template<typename ValueType>
	static function<double(Genotype<ValueType>&, double**)> get_count_thread()
	{
		return[](Genotype<ValueType>& temp, double** matr) {return _count_thread(temp, matr); };
	}*/

	template<typename ValueType>
	static  function<void(Genotype<ValueType>&)> get_create()
	{
		return [](Genotype<ValueType>& temp) {_create(temp); };
	}

private:

	static const int line_in_genes = 1;
	static const int column_in_genes = 3;

	template<typename ValueType>
	static double _count(Genotype<ValueType>& g)
	{
		int n_l, n_c;
		double fitness = 0;
		auto matr = Source::Instance()->get_source();
		for (Gene<ValueType>& gen : *g.genotype)
		{
			for (size_t i = 0; i < gen.get_size(); i++)
			{
				int num_of_gene = gen.get_gene()[i];
				num_of_gene--;
				n_l = Source::line_in_genes * (num_of_gene / Source::number_of_genes_in_line_matrix);
				n_c = Source::column_in_genes * (num_of_gene % Source::number_of_genes_in_line_matrix);

				for (size_t j = n_c; j < n_c + Source::column_in_genes; j++)
				{
					fitness += matr[n_l][j];
				}
			}
			/*for (auto item : *gen.get_gene())
			{
			int num_of_gene = --item;
			n_l = line_in_genes * (num_of_gene / 159);
			n_c = column_in_genes * (num_of_gene % 159);

			for (size_t i = n_c; i < n_c + column_in_genes; i++)
			{
			fitness += matr[n_l][i];
			}
			}*/
		}
		return fitness;
	}

	template<typename ValueType>
	static void _create(Genotype<ValueType>& gg)
	{
		Distr distribution(1, Source::total_genes);
		gg.genotype = new vector<Gene<ValueType>>();
		vector<int> gList;
		for (size_t i = 0; i < Source::number_of_genes_in_genotype; i++)
		{
			Gene<ValueType> g(1);
			g.get_gene()[0] = distribution();
			gg.genotype->push_back(move(g));
			//gList.push_back(g);
		}
		/*gList = distribution.get_chisla();
		for (size_t i = 0; i < gList.size(); i++)
		{
		int count = -1;
		for (int item : gList)
		{
		if (item == gList[i])
		count++;
		}
		cout << count << endl;
		}*/
		/*for (size_t i = 0; i < gg._number_of_genes; i++)
		{
		Gene<int> g;
		g.get_gene()->push_back(distribution());
		gg.genotype->at(i) = g;
		}*/
	}

	class Distr
	{
		random_device rd;
		mt19937 generator;
		uniform_int_distribution<> distrib;

		int a, b;
		vector<int> chisla;

	public:
		Distr(int a, int b) : a(a), b(b)
		{
			generator = mt19937(rd());
			distrib = uniform_int_distribution<>(a, b);
		}

		vector<int> get_chisla() const
		{
			return chisla;
		}

		int operator() () {

			while (true)
			{
				auto temp = distrib(generator);
				/*if (!binary_search(chisla.begin(), chisla.end(), temp))
				{
				chisla.push_back(temp);
				return temp;
				}*/
				auto flag = true;
				for (size_t i = 0; i < chisla.size(); i++)
				{
					if (temp == chisla[i])
					{
						flag = false;
						break;
					}
				}
				if (flag)
				{
					chisla.push_back(temp);
					return temp;
				}
			}
		}
	};
};

