#pragma once

#include <string>
#include <msclr\marshal_cppstd.h>

#include "../lib_polynomial/polynomial.cpp"
#include "../lib_table_hash_list/hash_list.h"
#include "../lib_table_hash_vector/hash_vector.h"
#include "../lib_table_linear_array/linear_array.h"
#include "../lib_table_linear_list/linear_list.h"
#include "../lib_table_ordered_array/ordered_array.h"
#include "../lib_table_tree/tree.h"



namespace VisualProgramm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Globalization;

	CTreeTable<std::pair<std::string, CPolynomial>> tree;
	COrderedTableArray<std::pair<std::string, CPolynomial>> orderArray;
	CLinearTableList<std::pair<std::string, CPolynomial>> linearList;
	CLinearTableArray<std::pair<std::string, CPolynomial>> linearArray;
	CHashTableMix<std::pair<std::string, CPolynomial>> mixvector(10);
	CHashTableList<std::pair<std::string, CPolynomial>> mixlist;
	bool needTableUpdate = false;

	// Используется для конвертации System String^ в std::string.
	// Если любите мучаться, см. System::Void button1_Click
	void MarshalString(String^ s, std::string& os) {
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	std::string* stringParser(std::string str, const int size) {
		std::string* arr = new std::string[size];
		std::string buff;
		int index = 0;
		for (int i = 0; i < size; i++) {
			for (int j = index; j < str.size(); j++)
				if (str[j] != '\n') {
					buff += str[j];
					index++;
				}
				else {
					index++;
					break;
				}
			arr[i] = buff;
			buff.clear();
		}
		return arr;
	}

	int GetFindIndex(std::pair<std::string, CPolynomial> pair, int tableindex) {
		int res = 0;
		switch (tableindex) {
		case 0:
		{
			CHashTableList<std::pair<std::string, CPolynomial>> mixfind;
			mixfind.insert(pair);
			std::string tofind = mixfind.printstring();
			tofind.erase(std::remove(tofind.begin(), tofind.end(), '\n'), tofind.cend());
			int size = mixlist.getsize();
			std::string* arrstring = new std::string[size];
			arrstring = stringParser(mixlist.printstring(), size);
			for (int i = 0; i < size; i++) {
				if (arrstring[i] == tofind) {
					res = i;
					break;
				}
			}
			break;
		}
		case 1:
		{
			CHashTableMix<std::pair<std::string, CPolynomial>> mixfind(10);
			mixfind.insert(pair);
			std::string tofind = mixfind.printstring();
			tofind.erase(std::remove(tofind.begin(), tofind.end(), '\n'), tofind.cend());
			int size = mixvector.getsize();
			std::string* arrstring = new std::string[size];
			arrstring = stringParser(mixvector.printstring(), size);
			for (int i = 0; i < size; i++) {
				if (arrstring[i] == tofind) {
					res = i;
					break;
				}
			}
			break;
		}
		case 2:
		{
			CLinearTableArray<std::pair<std::string, CPolynomial>> mixfind;
			mixfind.insert(pair);
			std::string tofind = mixfind.printstring();
			tofind.erase(std::remove(tofind.begin(), tofind.end(), '\n'), tofind.cend());
			int size = linearArray.getsize();
			std::string* arrstring = new std::string[size];
			arrstring = stringParser(linearArray.printstring(), size);
			for (int i = 0; i < size; i++) {
				if (arrstring[i] == tofind) {
					res = i;
					break;
				}
			}
			break;
		}
		case 3:
		{
			CLinearTableList<std::pair<std::string, CPolynomial>> mixfind;
			mixfind.insert(pair);
			std::string tofind = mixfind.printstring();
			tofind.erase(std::remove(tofind.begin(), tofind.end(), '\n'), tofind.cend());
			int size = linearList.getsize();
			std::string* arrstring = new std::string[size];
			arrstring = stringParser(linearList.printstring(), size);
			for (int i = 0; i < size; i++) {
				if (arrstring[i] == tofind) {
					res = i;
					break;
				}
			}
			break;
		}
		case 4:
		{
			COrderedTableArray<std::pair<std::string, CPolynomial>> mixfind;
			mixfind.insert(pair);
			std::string tofind = mixfind.printstring();
			tofind.erase(std::remove(tofind.begin(), tofind.end(), '\n'), tofind.cend());
			int size = orderArray.getsize();
			std::string* arrstring = new std::string[size];
			arrstring = stringParser(orderArray.printstring(), size);
			for (int i = 0; i < size; i++) {
				if (arrstring[i] == tofind) {
					res = i;
					break;
				}
			}
			break;
		}
		case 5:
		{
			CTreeTable<std::pair<std::string, CPolynomial>> mixfind;
			mixfind.insert(pair);
			std::string tofind = mixfind.printstring();
			tofind.erase(std::remove(tofind.begin(), tofind.end(), '\n'), tofind.cend());
			int size = tree.getsize();
			std::string* arrstring = new std::string[size];
			arrstring = stringParser(tree.printstring(), size);
			for (int i = 0; i < size; i++) {
				if (arrstring[i] == tofind) {
					res = i;
					break;
				}
			}
			break;
		}
		}
		return res;
	}


	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:

		Form1(void)
		{
			InitializeComponent();

		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::SplitContainer^ splitContainer1;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBox5;

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->button5);
			this->splitContainer1->Panel1->Controls->Add(this->button4);
			this->splitContainer1->Panel1->Controls->Add(this->label11);
			this->splitContainer1->Panel1->Controls->Add(this->label10);
			this->splitContainer1->Panel1->Controls->Add(this->label9);
			this->splitContainer1->Panel1->Controls->Add(this->textBox8);
			this->splitContainer1->Panel1->Controls->Add(this->textBox7);
			this->splitContainer1->Panel1->Controls->Add(this->textBox6);
			this->splitContainer1->Panel1->Controls->Add(this->comboBox1);
			this->splitContainer1->Panel1->Controls->Add(this->label7);
			this->splitContainer1->Panel1->Controls->Add(this->button3);
			this->splitContainer1->Panel1->Controls->Add(this->button2);
			this->splitContainer1->Panel1->Controls->Add(this->label6);
			this->splitContainer1->Panel1->Controls->Add(this->label5);
			this->splitContainer1->Panel1->Controls->Add(this->textBox5);
			this->splitContainer1->Panel1->Controls->Add(this->button1);
			this->splitContainer1->Panel1->Controls->Add(this->label4);
			this->splitContainer1->Panel1->Controls->Add(this->label3);
			this->splitContainer1->Panel1->Controls->Add(this->label2);
			this->splitContainer1->Panel1->Controls->Add(this->label1);
			this->splitContainer1->Panel1->Controls->Add(this->textBox4);
			this->splitContainer1->Panel1->Controls->Add(this->textBox3);
			this->splitContainer1->Panel1->Controls->Add(this->textBox2);
			this->splitContainer1->Panel1->Controls->Add(this->textBox1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->listBox1);
			this->splitContainer1->Size = System::Drawing::Size(944, 464);
			this->splitContainer1->SplitterDistance = 314;
			this->splitContainer1->TabIndex = 0;
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(226, 214);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(75, 23);
			this->button5->TabIndex = 24;
			this->button5->Text = L"Удалить";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(105, 291);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(123, 23);
			this->button4->TabIndex = 23;
			this->button4->Text = L"Вычислить в точке";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(201, 318);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(14, 13);
			this->label11->TabIndex = 22;
			this->label11->Text = L"Z";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(156, 318);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(14, 13);
			this->label10->TabIndex = 21;
			this->label10->Text = L"Y";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(112, 318);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(14, 13);
			this->label9->TabIndex = 20;
			this->label9->Text = L"X";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(149, 334);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(35, 20);
			this->textBox8->TabIndex = 19;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(193, 334);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(35, 20);
			this->textBox7->TabIndex = 18;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(105, 334);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(35, 20);
			this->textBox6->TabIndex = 17;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"TableHashList", L"TableHashVector", L"TableLinearArray",
					L"TableLinearList", L"TableOrderedArray", L"TableTree"
			});
			this->comboBox1->Location = System::Drawing::Point(180, 264);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 15;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox1_SelectedIndexChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(57, 264);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(117, 13);
			this->label7->TabIndex = 14;
			this->label7->Text = L"Вывести из Таблицы:";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(132, 214);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 13;
			this->button3->Text = L"Найти";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(34, 214);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 12;
			this->button2->Text = L"Создать";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(73, 179);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(192, 13);
			this->label6->TabIndex = 11;
			this->label6->Text = L"Формат: (моном) +-*/ (моном) +-*/ ...";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(108, 136);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(98, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Введите Полином";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(70, 152);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(172, 20);
			this->textBox5->TabIndex = 9;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(70, 106);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(172, 23);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Создать Моном";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(200, 39);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(28, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"ст.Z";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(155, 39);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(28, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"ст.Y";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(111, 39);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(28, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"ст.X";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(70, 39);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(37, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Коэф.";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(70, 58);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(35, 20);
			this->textBox4->TabIndex = 3;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(200, 58);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(42, 20);
			this->textBox3->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(155, 58);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(39, 20);
			this->textBox2->TabIndex = 1;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(111, 58);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(38, 20);
			this->textBox1->TabIndex = 0;
			// 
			// listBox1
			// 
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->listBox1->FormatString = L"std::string";
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 25;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"One", L"Two", L"Three" });
			this->listBox1->Location = System::Drawing::Point(19, 13);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(595, 429);
			this->listBox1->TabIndex = 0;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(944, 464);
			this->Controls->Add(this->splitContainer1);
			this->Name = L"Form1";
			this->Text = L"Калькулятор Полиномов";
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion


		// Это настолько плохо, что я надеюсь, что мне не придется больше никогда писать подобное
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		double coef;
		int deg[3];
		std::string coefstr;
		std::string powstr1;
		std::string powstr2;
		std::string powstr3;
		msclr::interop::marshal_context context;
		System::String^ txtboxstr = textBox4->Text;
		coefstr = context.marshal_as<std::string>(txtboxstr);
		coef = atof(coefstr.c_str());
		txtboxstr = textBox1->Text;
		powstr1 = context.marshal_as<std::string>(txtboxstr);
		deg[0] = stoi(powstr1);
		txtboxstr = textBox2->Text;
		powstr2 = context.marshal_as<std::string>(txtboxstr);
		deg[1] = stoi(powstr2);
		txtboxstr = textBox3->Text;
		powstr3 = context.marshal_as<std::string>(txtboxstr);
		deg[2] = stoi(powstr3);
		CMonomial monom(coef, deg);
		CList<CMonomial> list;
		list.push_back(monom);
		CPolynomial poly(list);
		std::pair<std::string, CPolynomial> pair(std::make_pair(poly.toString(), poly));
		tree.insert(pair);
		orderArray.insert(pair);
		linearList.insert(pair);
		linearArray.insert(pair);
		mixvector.insert(pair);
		mixlist.insert(pair);
		needTableUpdate = true;
	}

	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		int index = comboBox1->SelectedIndex;
		if (needTableUpdate) {
			switch (index)
			{
			case 0:
			{
				listBox1->Items->Clear();
				int size = mixlist.getsize();
				std::string* arrstring = new std::string[size];
				arrstring = stringParser(mixlist.printstring(), size);
				for (int i = 0; i < size; i++) {
					System::String^ sysStr = msclr::interop::marshal_as<System::String^>(arrstring[i]);
					listBox1->Items->Add(sysStr);
				}
				needTableUpdate = false;
				break;
			}
			case 1:
			{
				listBox1->Items->Clear();
				int size = mixvector.getsize();
				std::string* arrstring = new std::string[size];
				arrstring = stringParser(mixvector.printstring(), size);
				std::cout << arrstring;
				for (int i = 0; i < size; i++) {
					System::String^ sysStr = msclr::interop::marshal_as<System::String^>(arrstring[i]);
					listBox1->Items->Add(sysStr);
				}
				needTableUpdate = false;
				break;
			}
			case 2:
			{
				listBox1->Items->Clear();
				int size = linearArray.getsize();
				std::string* arrstring = new std::string[size];
				arrstring = stringParser(linearArray.printstring(), size);
				for (int i = 0; i < size; i++) {
					System::String^ sysStr = msclr::interop::marshal_as<System::String^>(arrstring[i]);
					listBox1->Items->Add(sysStr);
				}
				needTableUpdate = false;
				break;
			}
			case 3:
			{
				listBox1->Items->Clear();
				int size = linearList.getsize();
				std::string* arrstring = new std::string[size];
				arrstring = stringParser(linearList.printstring(), size);
				for (int i = 0; i < size; i++) {
					System::String^ sysStr = msclr::interop::marshal_as<System::String^>(arrstring[i]);
					listBox1->Items->Add(sysStr);
				}
				needTableUpdate = false;
				break;
			}
			case 4:
			{
				listBox1->Items->Clear();
				int size = orderArray.getsize();
				std::string* arrstring = new std::string[size];
				arrstring = stringParser(orderArray.printstring(), size);
				for (int i = 0; i < size; i++) {
					System::String^ sysStr = msclr::interop::marshal_as<System::String^>(arrstring[i]);
					listBox1->Items->Add(sysStr);
				}
				needTableUpdate = false;
				break;
			}
			case 5:
			{
				listBox1->Items->Clear();
				int size = tree.getsize();
				std::string* arrstring = new std::string[size];
				arrstring = stringParser(tree.printstring(), size);
				for (int i = 0; i < size; i++) {
					System::String^ sysStr = msclr::interop::marshal_as<System::String^>(arrstring[i]);
					listBox1->Items->Add(sysStr);
				}
				needTableUpdate = false;
				break;
			}
			}
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string polyString;
		String^ txtbox5string = textBox5->Text;
		MarshalString(txtbox5string, polyString);
		CPolynomial polynom;
		polynom.Parse(polyString);
		std::pair<std::string, CPolynomial> pair(polyString, polynom);
		tree.insert(pair);
		orderArray.insert(pair);
		linearList.insert(pair);
		linearArray.insert(pair);
		mixvector.insert(pair);
		mixlist.insert(pair);
		needTableUpdate = true;
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ txtbox5string = textBox5->Text;
		std::string polyString;
		MarshalString(txtbox5string, polyString);
		CPolynomial polynom;
		polynom.Parse(polyString);
		std::pair<std::string, CPolynomial> pair(polyString, polynom);
		int index = comboBox1->SelectedIndex;
		int found;
		found = GetFindIndex(pair, index);
		listBox1->SelectedIndex = found;
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ txtbox5string = textBox5->Text;
		std::string polyString;
		MarshalString(txtbox5string, polyString);
		CPolynomial polynom;
		polynom.Parse(polyString);
		std::pair<std::string, CPolynomial> pair(polynom.toString(), polynom);
		//tree.remove(pair); TODO: Fix removeMin being undefined.
		orderArray.remove(pair);
		linearList.remove(pair);
		linearArray.remove(pair);
		mixvector.remove(pair);
		mixlist.remove(pair);
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ strx = textBox6->Text;
		String^ stry = textBox8->Text;
		String^ strz = textBox7->Text;

		int x = int::Parse(strx);
		int y = int::Parse(stry);
		int z = int::Parse(strz);

		int indexTable = comboBox1->SelectedIndex;
		int indexList = listBox1->SelectedIndex;

		String^ sItem = listBox1->SelectedItem->ToString();
		std::string ssItem;
		std::string calcItem = "";
		MarshalString(sItem, ssItem);

		for (int i = 0; i < ssItem.size() - 2; i++) {
			if (ssItem[i] == ' ' && ssItem[i + 1] == ' ' && ssItem[i + 2] == ' ') {
				break;
			}
			calcItem.append(1, ssItem[i]);
		}

		double res;

		switch (indexTable) {
		case 0: {
			int size = mixlist.getsize();
			std::string* arrstring = new std::string[size];
			arrstring = stringParser(mixlist.printstring(), size);
			for (int i = 0; i < size; i++) {
				if (arrstring[i] == calcItem) {
					//res = mixlist.find(calcItem).second.findResult(x, y, z, calcItem); TODO: fix find.
					break;
				}
			}
			break;
		}
		case 1:{
			int size = mixvector.getsize();
			std::string* arrstring = new std::string[size];
			arrstring = stringParser(mixlist.printstring(), size);
			for (int i = 0; i < size; i++) {
				if (arrstring[i] == ssItem) {
					res = mixvector.find(calcItem).second.findResult(x, y, z, calcItem);
					MessageBox::Show("Your result is: " + res.ToString());
					break;
				}
			}
			break;
		}
		case 2: {
			int size = linearArray.getsize();
			std::string* arrstring = new std::string[size];
			arrstring = stringParser(linearArray.printstring(), size);
			for (int i = 0; i < size; i++) {
				if (arrstring[i] == ssItem) {
					res = linearArray.find(calcItem).second.findResult(x, y, z, calcItem);
					MessageBox::Show("Your result is: " + res.ToString());
					break;
				}
			}
			break;
		}
		case 3: {
			int size = linearList.getsize();
			std::string* arrstring = new std::string[size];
			arrstring = stringParser(linearList.printstring(), size);
			for (int i = 0; i < size; i++) {
				if (arrstring[i] == ssItem) {
					res = linearList.find(calcItem).second.findResult(x, y, z, calcItem);
					MessageBox::Show("Your result is: " + res.ToString());
					break;
				}
			}
			break;
		}
		case 4: {
			int size = orderArray.getsize();
			std::string* arrstring = new std::string[size];
			arrstring = stringParser(orderArray.printstring(), size);
			for (int i = 0; i < size; i++) {
				if (arrstring[i] == ssItem) {
					//res = orderArray.find(calcItem).second.findResult(x, y, z, calcItem); TODO fix find with [;
					MessageBox::Show("Your result is: " + res.ToString());
					break;
				}
			}
			break;
		}
		case 5: {
			int size = tree.getsize();
			std::string* arrstring = new std::string[size];
			arrstring = stringParser(tree.printstring(), size);
			for (int i = 0; i < size; i++) {
				if (arrstring[i] == ssItem) {
					res = tree.find(calcItem).second.findResult(x, y, z, calcItem);
					MessageBox::Show("Your result is: " + res.ToString());
					break;
				}
			}
			break;
		}
		}
	}
};
}
