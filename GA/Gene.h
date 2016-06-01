#pragma once

using namespace std;

template <typename ValueType> struct Gene
{
	Gene();
	explicit Gene(int);
	//Конструктор копирования для работы с обычными ссылками lvalue
	Gene(const Gene<ValueType>& other);
	//Конструктор перемещения для move и работы с типами ссылок rvalue, часто применяется при работе с векторами
	Gene(Gene<ValueType>&& other);
	~Gene();

	ValueType* gene;
	ValueType* get_gene();
	ValueType get_gen()
	{
		auto t = *gene;
		return t;
	}

	friend bool operator== (const Gene<ValueType>& left, const Gene<ValueType>& right);

	Gene<ValueType>& operator=(const Gene<ValueType>& other);
	Gene<ValueType>& operator=(Gene<ValueType>&& other);
	//inline ValueType* operator[](int index); закомменчено для работы в 2010 студии
	//inline ValueType operator[](int index) const;

	int get_size() const;

private:
	int _size;
};

template<typename ValueType>
Gene<ValueType>::Gene()
{
	//_gene = new vector<ValueType>(1);
}

template<typename ValueType>
Gene<ValueType>::Gene(int size)
{
	//_gene = new vector<ValueType>(size);
	_size = size;
	gene = new ValueType[size];
}

template <typename ValueType>
Gene<ValueType>::Gene(const Gene<ValueType>& other)
{
	//copy(other._gene->begin(), other._gene->end(), _gene->begin());
	gene = new ValueType[other._size];
	_size = other._size;
	for (size_t i = 0; i < _size; i++)
	{
		gene[i] = other.gene[i];
	}
}

template <typename ValueType>
Gene<ValueType>::Gene(Gene<ValueType>&& other)
{
	//_gene = new vector<ValueType>(move(*other._gene));
	//other._gene = nullptr;
	_size = other._size;
	gene = other.gene;
	other.gene = nullptr;
}

template<typename ValueType>
Gene<ValueType>::~Gene()
{
	/*if (_gene == nullptr)
	cout << "can't dest" << endl;*/
	delete gene;
	//cout << "Destructor gene" << endl;
}

template<typename ValueType>
ValueType* Gene<ValueType>::get_gene()
{
	return gene;
}

template <typename ValueType>
int Gene<ValueType>::get_size() const
{
	return _size;
}

template<typename ValueType>
bool operator==(const Gene<ValueType>& left, const Gene<ValueType>& right);

template <typename ValueType>
bool operator==(const Gene<ValueType>& left, const Gene<ValueType>& right)
{
	//return equal(left.get_gene()->begin(), left.get_gene()->end(), right.get_gene()->begin());
	for (size_t i = 0; i < left._size; i++)
	{
		if (left.gene[i] != right.gene[i])
			return false;
	}
	return true;

	/*auto size = left.get_size();
	for (int i = 0; i < left.get_size(); i++)
	{
	if (left[i] != right[i])
	return false;
	}*/
}

template <typename ValueType>
Gene<ValueType>& Gene<ValueType>::operator=(const Gene<ValueType>& other)
{
	/*if (this != &other)
	{
	delete _gene;
	this->_gene = new vector<ValueType>(other._gene->size());
	copy(other._gene->begin(), other._gene->end(), this->_gene->begin());
	}*/

	if (this != &other)
	{
		//delete this->gene;
		this->_size = other._size;
		this->gene = new ValueType[other.get_size()];
		for (size_t i = 0; i < this->_size; i++)
		{
			this->gene[i] = other.gene[i];
		}
	}

	return *this;
}

template <typename ValueType>
Gene<ValueType>& Gene<ValueType>::operator=(Gene<ValueType>&& other)
{
	if (this != &other)
	{
		///delete gene;
		*this = move(other);
	}
	return *this;
}

