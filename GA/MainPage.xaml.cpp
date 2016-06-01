//
// MainPage.xaml.cpp
// Реализация класса MainPage.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <wchar.h>
#include <ppltasks.h>
#include <wrl.h> 
#include <robuffer.h>
#include <sstream>
#include <string>


#include "Population.h"
#include "Genotype.h"
#include "Selection.h"
#include "Recombination.h"
#include "Mutation.h"

#include "Select_In_Population.h"
#include <algorithm>
#include <random>
#include "Source.h"
#include <fstream>
#include <functional>
#include "Fit_Fun.h"

using namespace GA;

using namespace concurrency;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Graphics::Imaging;
using namespace Microsoft::WRL;
using namespace Windows::Storage::Pickers;

using namespace concurrency;

// Документацию по шаблону элемента "Пустая страница" см. по адресу http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}

void MainPage::SelectSource_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	/*if (!Source::Instance()) {
		auto picker = ref new Windows::Storage::Pickers::FileOpenPicker();
		picker->ViewMode = Windows::Storage::Pickers::PickerViewMode::Thumbnail;

		picker->SuggestedStartLocation = Windows::Storage::Pickers::PickerLocationId::Desktop;
		picker->FileTypeFilter->Append(".txt");

		auto file = picker->PickSingleFileAsync();

		create_task(file).then([this](Windows::Storage::StorageFile^ file)
		{
			if (file != nullptr)
			{
				create_task(Windows::Storage::FileIO::ReadTextAsync(file)).then([this](String^ text)
				{
					int width = 0, height = 0;

					wstring wstr(text->Data());
					vector<string> tokens;
					wistringstream iss(wstr);

					auto pointer_text = text->Begin();
					bool flag = true;
					for (int i = 0; i < text->Length(); i++)
					{
						auto ttr = wstr[i];
						if (pointer_text[i] == '\n')
						{
							height++;
							flag = false;
						}
						else if (flag && pointer_text[i] == ' ')
							width++;
					}

					auto matrix = new double*[height];
					for (size_t i = 0; i < height; i++)
					{
						matrix[i] = new double[width];
					}

					for (int i = 0; i < height; i++)
						for (int j = 0; j < width; j++)
						{
							/*if (i == 86 && j == 71) {
								auto str = (pointer_text + i*width + j);
								auto t = _wtof_l(pointer_text + i*width + j, _get_current_locale());
								matrix[i][j] = t;
							}
							double temp;
							iss >> temp;
							matrix[i][j] = temp; //_wtof_l(pointer_text + i*width + j, _get_current_locale());

						}

					Source::Create(height, width, matrix);

					vector<Genotype<int>>* vec = new vector<Genotype<int>>();

					auto temp_count = Fit_Fun::get_count<int>();
					auto temp_create = Fit_Fun::get_create<int>();

					for (size_t i = 0; i < 100; i++)
					{
						Genotype<int> g(7807, temp_create, temp_count);
						vec->push_back(move(g));
					}

					auto temp_s = Selection::outbreeding<int>();
					auto temp_r = Recombination::primer<int>();
					auto temp_m = nullptr;
					auto temp_sp = Select_In_Population::elite<int>();

					Population<int> p(50, vec, temp_s, temp_r, temp_m, temp_sp);
					delete vec;

					for (size_t i = 0; i < 10; i++)
					{
						for (size_t j = 0; j < 50; j++)
						{
							p.select();
							p.recom();
						}
						//cout << p.get_pop()->at(0).get_fitness() << endl;
						//p.mut();
						p.select_in_population();
					}

					Genotype<int> mini = p.get_pop()->at(0);
					vector<int> mas;

					for_each(mini.get_genotype()->begin(), mini.get_genotype()->end(), [&mas](Gene<int> g) {mas.push_back(g.get_gene()[0]); });

					sort(mas.begin(), mas.end());


					Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ bitmap = ref new Windows::UI::Xaml::Media::Imaging::WriteableBitmap(477, 491);
					auto pixels = new byte[4 * bitmap->PixelWidth*bitmap->PixelHeight];
					auto f = false;

					auto buffer = bitmap->PixelBuffer;
					Microsoft::WRL::ComPtr<Windows::Storage::Streams::IBufferByteAccess> pBufferByteAccess;
					Microsoft::WRL::ComPtr<IUnknown> pBuffer((IUnknown*)buffer);
					pBuffer.As(&pBufferByteAccess);

					pBufferByteAccess->Buffer(&pixels);

					kart->Source = bitmap;

					for (int y = 0; y < bitmap->PixelHeight; y++)
					{
						int xGen = 0;
						for (int x = 0; x < bitmap->PixelWidth; x += 3)
						{
							int index = 4 * (y * bitmap->PixelWidth + x);
							int pointer = y * 159 + xGen;

							for (int k = 0; k < 3; k++)
							{
								if (binary_search(mas.begin(), mas.end(), pointer))
								{

									pixels[index] = 64;
									pixels[index + 1] = 64;
									pixels[index + 2] = 255;
									pixels[index + 3] = 255;
								}
								else
								{
									pixels[index] = 240;
									pixels[index + 1] = 248;
									pixels[index + 2] = 255;
									pixels[index + 3] = 255;
								}
								index += 4;
							}
							xGen++;
						}
					}



					bitmap->Invalidate();


				});
			}
		});
	}*/

	if (!Source::Instance()) {

		auto picker = ref new Windows::Storage::Pickers::FileOpenPicker();
		picker->ViewMode = Windows::Storage::Pickers::PickerViewMode::Thumbnail;

		picker->SuggestedStartLocation = Windows::Storage::Pickers::PickerLocationId::Desktop;
		picker->FileTypeFilter->Append(".txt");

		auto file = picker->PickSingleFileAsync();
		create_task(file).then([this](Windows::Storage::StorageFile^ file)
		{
			if (file != nullptr)
			{
				MainPage::Open(file).then([this](vector<int>* grahics_mas)
				{

					image_vector = grahics_mas;
					MainPage::ImageDown(image_vector[0]);

				}, task_continuation_context::use_current());
			}
		});
	}
}

void MainPage::ImageDown(vector<int> grahics_mas)
{
	Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ bitmap = ref new Windows::UI::Xaml::Media::Imaging::WriteableBitmap(Source::width, Source::height);
	auto pixels = new byte[4 * bitmap->PixelWidth * bitmap->PixelHeight];
	auto f = false;

	auto buffer = bitmap->PixelBuffer;
	Microsoft::WRL::ComPtr<Windows::Storage::Streams::IBufferByteAccess> pBufferByteAccess;
	Microsoft::WRL::ComPtr<IUnknown> pBuffer((IUnknown*)buffer);
	pBuffer.As(&pBufferByteAccess);

	pBufferByteAccess->Buffer(&pixels);

	kart->Source = bitmap;

	for (int y = 0; y < bitmap->PixelHeight; y++)
	{
		int xGen = 0;
		//for (int x = 0; x < bitmap->PixelWidth; x += Source::column_in_genes)
		for (int x = bitmap->PixelWidth - 1; x >= 0; x -= Source::column_in_genes)
		{
			int index = 4 * (y * bitmap->PixelWidth + x);
			int pointer = y * Source::number_of_genes_in_line_matrix + xGen;

			for (int k = 0; k < Source::column_in_genes; k++) // границы проверить
			{
				if (binary_search(grahics_mas.begin(), grahics_mas.end(), pointer))
				{
					pixels[index] = 64;
					pixels[index + 1] = 64;
					pixels[index + 2] = 255;
					pixels[index + 3] = 255;
				}
				else
				{
					pixels[index] = 255;
					pixels[index + 1] = 255;
					pixels[index + 2] = 255;
					pixels[index + 3] = 255;
				}
				index += 4;
			}
			xGen++;
		}
	}
	bitmap->Invalidate();
}

const int num_iteration = 40;

Concurrency::task<std::vector<int>*> MainPage::Open(Windows::Storage::StorageFile^ file)
{
	return create_task([this, file]()-> std::vector<int>* {

		auto task_graphics = create_task(Windows::Storage::FileIO::ReadTextAsync(file)).then([this](String^ text) -> std::vector<int>*
		{
			wstring wstr(text->Data());
			vector<string> tokens;
			wistringstream iss(wstr);

			auto pointer_text = text->Begin();
			bool flag = true;
			for (int i = 0; i < text->Length(); i++)
			{
				auto ttr = wstr[i];
				if (pointer_text[i] == '\n')
				{
					Source::height++;
					flag = false;
				}
				else if (flag && pointer_text[i] == ' ')
					Source::width++;
			}

			auto matrix = new double*[Source::height];
			for (int i = 0; i < Source::height; i++)
			{
				matrix[i] = new double[Source::width];
				for (int j = 0; j < Source::width; j++)
				{
					double temp;
					iss >> temp;
					matrix[i][j] = temp;
				}
			}

			auto matrix2 = new double*[Source::height];
			for (int i = 0; i < Source::height; i++)
			{
				matrix2[i] = new double[Source::width - 1];
				for (int j = 0; j < Source::width - 1; j++)
				{
					matrix2[i][j] = matrix[i][j + 1] - matrix[i][j];
				}
			}

			if (Source::width % 2 == 0) Source::column_in_genes = 2;
			else if (Source::width % 3 == 0) Source::column_in_genes = 3;
			else if (Source::width % 5 == 0) Source::column_in_genes = 5;
			else if (Source::width % 7 == 0) Source::column_in_genes = 7;

			Source::number_of_genes_in_line_matrix = Source::width / Source::column_in_genes;
			Source::total_genes = Source::number_of_genes_in_line_matrix * Source::height;
			Source::number_of_genes_in_genotype = Source::total_genes / 10;

			Source::Create(matrix2);

			vector<Genotype<int>>* vec = new vector<Genotype<int>>();

			auto temp_count = Fit_Fun::get_count<int>();
			auto temp_create = Fit_Fun::get_create<int>();

			for (size_t i = 0; i < 50; i++)
			{
				Genotype<int> g(Source::number_of_genes_in_genotype, temp_create, temp_count);
				vec->push_back(move(g));
			}

			auto temp_s = Selection::outbreeding<int>();
			auto temp_r = Recombination::primer<int>();
			auto temp_m = Mutation::muta<int>();
			auto temp_sp = Select_In_Population::elite<int>();

			Population<int> p(10, vec, temp_s, temp_r, temp_m, temp_sp);
			delete vec;

			Genotype<int> arr[num_iteration];
			for (size_t i = 0; i < num_iteration; i++)
			{
				for (size_t j = 0; j < p.get_pop()->size(); j++)
				{
					p.select();
					p.recom();
				}
				//p.mut();
				p.select_in_population();
				arr[i] = p.get_pop()->at(0);
			}

			//Genotype<int> mini = p.get_pop()->at(0);

			vector<int> *mas = new vector<int>[num_iteration];
			for (int i = 0; i < num_iteration; i++)
			{
				auto temp = &mas[i];
				for_each(arr[i].get_genotype()->begin(), arr[i].get_genotype()->end(), [temp](Gene<int> g)
				{
					temp->push_back(g.get_gene()[0]);
				});
				sort(temp->begin(), temp->end());
			}

			return mas;

		}, task_continuation_context::use_arbitrary());

		task_graphics.wait();
		return task_graphics.get();
	});
}

void GA::MainPage::Save_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto savePicker = ref new Windows::Storage::Pickers::FileSavePicker();
	savePicker->SuggestedStartLocation = Windows::Storage::Pickers::PickerLocationId::Desktop;
	savePicker->FileTypeChoices->Insert("JPEG files", ref new Vector<String^>{ ".jpg" });
	savePicker->SuggestedFileName = "GA";

	create_task(savePicker->PickSaveFileAsync()).then([this](Windows::Storage::StorageFile^ file)
	{
		if (file) {
			Windows::Storage::CachedFileManager::DeferUpdates(file);

			create_task(file->OpenAsync(FileAccessMode::ReadWrite)).then([this](IRandomAccessStream^ stream)
			{
				create_task(BitmapEncoder::CreateAsync(BitmapEncoder::JpegEncoderId, stream)).then([this](BitmapEncoder^ encoder)
				{ //477, 491

					auto writebleBitmap = static_cast<WriteableBitmap^>(kart->Source);
					SoftwareBitmap^ outputBitmap = SoftwareBitmap::CreateCopyFromBuffer(
						writebleBitmap->PixelBuffer,
						BitmapPixelFormat::Bgra8,
						writebleBitmap->PixelWidth,
						writebleBitmap->PixelHeight
					);

					encoder->SetSoftwareBitmap(outputBitmap);
					encoder->BitmapTransform->ScaledWidth = 477;
					encoder->BitmapTransform->ScaledHeight = 491;
					encoder->BitmapTransform->Rotation = BitmapRotation::None;
					encoder->BitmapTransform->InterpolationMode = BitmapInterpolationMode::Fant;
					encoder->IsThumbnailGenerated = true;

					try
					{
						create_task(encoder->FlushAsync()).then([this] {
							auto message = ref new Windows::UI::Popups::MessageDialog("Успешно сохранено");
							create_task(message->ShowAsync());
						});
					}
					catch (Exception^ err)
					{
						switch (err->HResult)
						{
						case ((int)0x88982F81):
							encoder->IsThumbnailGenerated = false;
						default:
							throw err;
						}
					}
					if (!encoder->IsThumbnailGenerated)
						create_task(encoder->FlushAsync());
				});
			});

			/*create_task(Windows::Storage::FileIO::WriteBufferAsync(file, kart->g)).then([this, file] {
				create_task(Windows::Storage::CachedFileManager::CompleteUpdatesAsync(file)).then([this] (Windows::Storage::Provider::FileUpdateStatus status) {

					Windows::UI::Popups::MessageDialog^ message;
					if (status == Windows::Storage::Provider::FileUpdateStatus::Complete)
						message = ref new Windows::UI::Popups::MessageDialog("Успешно сохранено");
					else
						message = ref new Windows::UI::Popups::MessageDialog("Проблемы с сохранением");



				});
			});*/
		}
	});
}

void GA::MainPage::preview_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (count > 0)
		count--;
	ImageDown(image_vector[count]);
}

void GA::MainPage::next_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (count < num_iteration - 1)
		count++;
	vector<int> t = image_vector[count];
	ImageDown(image_vector[count]);
}

