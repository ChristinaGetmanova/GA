#pragma once

#include <ppltasks.h>

using namespace Platform;
using namespace concurrency;

//class NativeSource
//{
//public:
//	static NativeSource* Instance()
//	{
//		if (_instance == nullptr)
//		{
//			_instance = new NativeSource();
//			_instance->height = 0;
//			_instance->width = 0;
//		}
//
//		return _instance;
//	}
//
//	static NativeSource *_instance;
//
//	double** get_matrix() const
//	{
//		return matrix;
//	}
//
//private:
//	int height;
//	int width;
//	double **matrix;
//
//};
//
//NativeSource* NativeSource::_instance = nullptr;

class Source {
private:
	Source() {}

	static Source* _instance;

	double **matrix;

public:
	/*static Windows::Foundation::IAsyncOperation<Source^>^ Instance()
	{
		return create_async([]()-> Source^
		{
			if (_instance == nullptr)
			{
				auto picker = ref new Windows::Storage::Pickers::FileOpenPicker();
				picker->ViewMode = Windows::Storage::Pickers::PickerViewMode::Thumbnail;

				picker->SuggestedStartLocation = Windows::Storage::Pickers::PickerLocationId::Desktop;
				picker->FileTypeFilter->Append(".txt");

				auto file = picker->PickSingleFileAsync();


				create_task(file).then([](Windows::Storage::StorageFile^ file)->Source^
				{
					if (file != nullptr)
					{
						create_task(Windows::Storage::FileIO::ReadTextAsync(file)).then([](String^ text)->Source^
						{
							_instance = ref new Source();
							auto pointer_text = text->Begin();
							bool flag = true;

							for (int i = 0; i < text->Length(); i++)
							{
								if (pointer_text[i] == '\n')
								{
									_instance->_source.height++;
									flag = false;
								}
								else if (flag && pointer_text[i] == ' ')
									_instance->_source.width++;
							}

							_instance->_source.matrix = new double*[_instance->_source.height];
							for (size_t i = 0; i < _instance->_source.height; i++)
							{
								_instance->_source.matrix[i] = new double[_instance->_source.width];
							}

							for (int i = 0; i < _instance->_source.height; i++)
								for (int j = 0; j < _instance->_source.width; j++)
								{
									_instance->_source.matrix[i][j] = _wtof_l(pointer_text + i*_instance->_source.width + j, _get_current_locale());
								}

							return _instance;
						});
					}
					return _instance;
				});
				return _instance;
			}
		});
	}
*/
	static Source* Instance()
	{
		return _instance;
	}

	static void Create(double **matr)
	{
		_instance = new Source();
		_instance->matrix = matr;
	}

	int get_height()
	{
		return height;
	}
	int get_width()
	{
		return width;
	}
	double** get_source()
	{
		return matrix;
	}

	static const int line_in_genes = 1;
	static int column_in_genes;
	static int number_of_genes_in_genotype;
	static int total_genes;
	static int number_of_genes_in_line_matrix;
	static int height;
	static int width;
};

Source* Source::_instance = nullptr;
int Source::column_in_genes = 0;
int Source::number_of_genes_in_genotype = 0;
int Source::total_genes = 0;
int Source::number_of_genes_in_line_matrix = 0;
int Source::height = 1;//потому что не getline, чтобы последняя строка не терялась, если там нет \n
int Source::width = 0;


