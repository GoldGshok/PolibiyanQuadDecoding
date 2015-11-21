#include <iostream>
#include <fstream>
#include <locale.h>
#include <vector>
#include <string>

using namespace std;

vector<int> readKeyFile(char **quad, string &d, int &m, int &n);
void readFile(string &text);
void writeFile(string &text);
void createQuad(char **quad, string d, vector<int> v, int m, int n);
string decoding(char **quad, string &text, int m, int n);


void main() {
	setlocale(LC_ALL, "rus");
	
	//������ ��������� ����������
	string dictionary;
	char **quad;
	int m, n;
	vector<int> v;
	string text;

	//��������� ����������� ��������, ����, � �������
	ifstream f("key.txt");

	f >> m >> n;

	for (int i = 0; i < m * n; i++) {
		int temp;
		f >> temp;
		v.push_back(temp);
	}

	f.seekg(3, ios_base::cur);
	dictionary.resize(35);
	f.read((char*)dictionary.data(), dictionary.size());
	f.close();

	quad = new char*[m];
	for (int i = 0; i < m; i++) {
		quad[i] = new char[n];
	}

	//��������� ����������� �����
	readFile(text);

	//��������� �������
	createQuad(quad, dictionary, v, m, n);

	//�������������� �����
	text = decoding(quad, text, m, n);

	//���������� ���������
	writeFile(text);

	system("pause");
}

vector<int> readKeyFile(char **quad, string &d, int &m, int &n) {
	vector<int> v;
	ifstream f("key.txt");
	
	f >> m >> n;
	
	for (int i = 0; i < m * n; i++) {
		int temp;
		f >> temp;
		v.push_back(temp);
	}

	f.seekg(3,ios_base::cur);
	d.resize(35);
	f.read((char*)d.data(), d.size());
	f.close();

	quad = new char*[m];
	for (int i = 0; i < m; i++) {
		quad[i] = new char[n];
	}

	return v;
}

void createQuad(char **quad, string d, vector<int> v, int m, int n) {
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++) {
			quad[i][j] = d[v[i * n + j]];
		}
	}
}

void readFile(string &text) {
	// read text
	ifstream f("input.txt");
	f.seekg(0, ios_base::end);
	text.resize(f.tellg());
	f.seekg(0, ios_base::beg);

	f.read((char*)text.data(), text.size());
	f.close();
}

string decoding(char **quad, string &text, int m, int n) {
	string temp;
	int k = 0;
	while (k < text.length()) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (quad[i][j] == text[k]) {
					if (i != 0) {
						temp += quad[i - 1][j];
						break;
					}
					else {
						temp += quad[m - 1][j];
						break;
					}
				}
			}
		}
		k++;
	}
	return temp;
}

void writeFile(string &text) {
	ofstream of("output.txt");
	of << text;
	of.close();
}