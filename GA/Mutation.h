#pragma once
class Mutation
{
	Mutation() { }

	template<typename ValueType>
	static void m_mutation(Population<ValueType>&);
public:
	template<typename ValueType>
	static function<void(Population<ValueType>&)> muta()
	{
		return [](Population<ValueType>& p) { m_mutation(p); };
	}
};

template <typename ValueType>
void Mutation::m_mutation(Population<ValueType>& p)
{
	sort(p.population->begin(), p.population->end(), [](Genotype<ValueType>& g1, Genotype<ValueType>& g2) {return (g1.get_fitness() < g2.get_fitness()); });
	auto begin = p.population->size() - 1;
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> uniform_genotype(1, Source::number_of_genes_in_genotype);
	uniform_int_distribution<> uniform_gen(1, Source::total_genes);

	for (int i = begin; i >= 0; i--)
	{
		for (size_t j_t = 0; j_t < 4000; j_t++)//была мысль по половине особи зачищать, но пусть будет 2000 генов
		{
			vector<Gene<ValueType>>* t = p.population->at(i).get_genotype();
			//Gene<ValueType> g(1);
			//g.get_gene()[0] = uniform_gen(generator);
			*(t->at(uniform_genotype(generator)).get_gene()) = uniform_gen(generator);// = g;//на случайное место в особи поставить новый случайный ген
		}

	}
}
