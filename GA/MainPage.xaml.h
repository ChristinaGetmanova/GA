//
// MainPage.xaml.h
// Объявление класса MainPage.
//

#pragma once

#include "MainPage.g.h"
#include <vector>

namespace GA
{
	/// <summary>
	/// Пустая страница, которую можно использовать саму по себе или для перехода внутри фрейма.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		int count = 0;

		std::vector<int>* image_vector;

		void SelectSource_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		Concurrency::task<std::vector<int>*> Open(Windows::Storage::StorageFile^ file);

		void ImageDown(std::vector<int> grahics_mas);

		Concurrency::task<std::vector<int>*> Compare();

		void Save_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void preview_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void next_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
