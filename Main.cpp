#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <iomanip>


using namespace std;


/**
 * @brief Выводит элементы вектора на консоль
 *
 * @tparam T Тип элементов вектора
 *
 * @param vec Вектор, элементы которого нужно вывести
 *
 * @details Функция проходит по всем элементам вектора и выводит их на консоль.
 */
template<typename T>
void printVector(const vector<T>& vec)
{
	int n = vec.size();
	for (int i = 0; i < n; i += 1) {
		cout << vec[i];
	}
	cout << endl;
}


/**
 * @brief Проверяет, уникален ли заданный вектор среди заданных векторов.
 *
 * @param vec Вектор для проверки на уникальность.
 * @param vecs Вектор векторов, среди которых нужно проверить наличие заданного вектора.
 *
 * @return true, если вектор уникален, иначе false.
 */
template<typename T>
bool isVectorUnique(const vector<T>& vec, const vector<vector<T>>& vecs)
{
	return find_if(vecs.begin(), vecs.end(), [&](const vector<int>& other_vec) {
		return vec.size() == other_vec.size() && equal(vec.begin(), vec.end(), other_vec.begin());
		}) == vecs.end();
}


/**
 * @brief Вычисляет автокорреляционную функцию (ACF) для заданного бинарного сигнала.
 *
 * @param signal Бинарный сигнал, для которого необходимо вычислить ACF.
 *
 * @return Вектор ACF для заданного сигнала.
 */
vector<int> calcAcf(const vector<bool>& signal)
{
	int n = signal.size();
	vector<int> acf(n, 0);
	for (int i = 0; i < n; i += 1) {
		for (int j = 0; j < n - i; j += 1) {
			acf[i] += (signal[j] * 2 - 1) * (signal[j + i] * 2 - 1);
		}
	}
	return acf;
}


/**
 * @brief Структура, содержащая свойства автокорреляционной функции сигнала
 *
 */
struct AcfProps
{
	/**
	 * @brief Максимальная амплитуда бокового лепестка
	 *
	 */
	int mlw;

	/**
	 * @brief Ширина основного лепестка
	 *
	 */
	int mps;
};


/**
 * @brief Функция для вычисления основных характеристик АКФ.
 *
 * @param acf Входной вектор значений АКФ.
 *
 * @return Структура AcfProps, содержащая основную ширину лепестка и максимальную амплитуду бокового лепестка.
 */
AcfProps getAcfProps(vector<int>& acf)
{
	int n = acf.size();
	AcfProps acf_props{ -1, -1 };
	for (int i = 1; i < n; i += 1) {
		int curr = acf[i];
		if (acf_props.mlw == -1 && curr <= 0) {
			acf_props.mlw = curr == 0 && i == 1 ? i : 2 * i;
		}

		if (i < n - 1) {
			curr = abs(curr);
			int prev = abs(acf[i - 1]);
			int next = abs(acf[i + 1]);
			if (curr > prev && curr > next && curr > acf_props.mps) {
				acf_props.mps = curr;
			}
		}
	}
	return acf_props;
}


/**
 * @brief Класс для поиска оптимального сигнала.
 *
 */
class OptimalSignalSearch
{
private:

	/**
	 * @brief Длина сигнала
	 *
	 */
	int _length;

	/**
	 * @brief Заданная максимальная ширина основного лепестка
	 *
	 */
	int _max_mlw;

	/**
	 * @brief Заданная максимальная амплитуда бокового лепестка
	 *
	 */
	int _max_mps;

	/**
	 * @brief Структура для узла поиска сигнала.
	 *
	 */
	struct Node
	{

		/**
		 * @brief Левый полукод
		 *
		 */
		vector<bool> l_code;

		/**
		 * @brief Правый полукод
		 *
		 */
		vector<bool> r_code;

		/**
		 * @brief Уровень глубины узла.
		 *
		 */
		int lvl;

		/**
		 * @brief Конструктор для создания нового узла с заданными параметрами
		 *
		 * @param l Левый полукод
		 * @param r Правый полукод
		 * @param lvl Уровень глубины узла
		 */
		Node(const vector<bool>& l, const vector<bool>& r, int lvl) : l_code(l), r_code(r), lvl(lvl) {}

		/**
		 * @brief Конструктор копирования для создания копии узла
		 *
		 * @param other Узел для копирования
		 */
		Node(const Node& other) : l_code(other.l_code), r_code(other.r_code), lvl(other.lvl) {}

		/**
		 * @brief Деструктор для очистки ресурсов, занятых узлом
		 *
		 */
		~Node()
		{
			l_code.clear();
			r_code.clear();
		}

		/**
		 * @brief Getter для получения сигнала
		 *
		 * @return vector<bool> Сигнал
		 */
		vector<bool> signal() const
		{
			vector<bool> signal = l_code;
			signal.reserve(signal.size() + r_code.size());
			copy(r_code.begin(), r_code.end(), back_inserter(signal));
			return signal;
		}
	};

	/**
	 * @brief Функция для добавления в очередь поиска нового узла последовательности
	 *
	 * @param node Узел для обработки
	 * @param q Очередь поиска
	 * @param l Левое значение
	 * @param r Правое значение
	 * @param pass Флаг для добавления правого значения
	 */
	void _processNode(const Node* node, queue<Node*>& q, bool l, bool r, bool pass = false)
	{
		bool flag = !pass && _isOdd() && _max_lvl() == node->lvl + 1;
		Node* new_node = new Node(node->l_code, node->r_code, flag ? node->lvl : node->lvl + 1);
		new_node->l_code.push_back(l);
		if (!pass) {
			new_node->r_code.insert(new_node->r_code.begin(), r);
		}
		if (flag) {
			_processNode(new_node, q, 0, 0, true);
			_processNode(new_node, q, 1, 0, true);
			delete new_node;
		}
		else {
			q.push(new_node);
		}
	}

	/**
	 * @brief Getter для нечетности сигнала
	 *
	 * @return true, если сигнал нечетный, иначе false.
	 */
	bool _isOdd() const
	{
		return _length % 2 == 1;
	}

	/**
	 * @brief Getter для максимальной глубины дерева поиска
	 *
	 * @return int Максимальную глубину дерева поиска
	 */
	int _max_lvl() const
	{
		return _length / 2 - 1;
	}

	/**
	 * @brief Функция для поиска оптимальных сигналов
	 *
	 */
	void _search()
	{
		queue<Node*> q;
		vector<vector<int>> uniq_acfs;
		int cur_lvl = 0;
		bool fst_found = false;

		q.push(new Node({ 0 }, { 0 }, 0));
		q.push(new Node({ 0 }, { 1 }, 0));

		while (!q.empty()) {
			Node* node = q.front();
			q.pop();

			if (cur_lvl != node->lvl) {
				cur_lvl = node->lvl;
				uniq_acfs.clear();
			}

			vector<int> new_acf = calcAcf(node->signal());

			if (isVectorUnique(new_acf, uniq_acfs)) {
				uniq_acfs.push_back(new_acf);

				AcfProps new_acf_props = getAcfProps(new_acf);

				if (new_acf_props.mps > _max_mps || new_acf_props.mlw > _max_mlw) {
					goto skip;
				}

				if (_max_lvl() == cur_lvl) {
					if (new_acf_props.mps == -1 || new_acf_props.mlw == -1) {
						goto skip;
					}

					if (!fst_found || new_acf_props.mps < acf_props.mps || (new_acf_props.mps == acf_props.mps && new_acf_props.mlw < acf_props.mlw)) {
						acf_props = new_acf_props;
						acf = new_acf;
						signal = node->signal();
						fst_found = true;
					}
				}
				else {
					_processNode(node, q, 0, 0);
					_processNode(node, q, 0, 1);
					_processNode(node, q, 1, 0);
					_processNode(node, q, 1, 1);
				}
			}

		skip:
			delete node;
		}
	}

public:

	/**
	 * @brief Вектор, содержащий найденный оптимальный сигнал
	 *
	 */
	vector<bool> signal;

	/**
	 * @brief Вектор, содержащий АКФ сигнала
	 *
	 */
	vector<int> acf;

	/**
	 * @brief Структура, содержащая свойства АКФ сигнала
	 *
	 */
	AcfProps acf_props;

	/**
	 * @brief Конструктор класса OptimalSignalSearch
	 *
	 * @param length Длина сигнала
	 * @param max_mlw Максимальное значение ширины основного лепестка
	 * @param max_mps Максимальное значение амплитуды бокового лепестка
	 */
	OptimalSignalSearch(int length, int max_mlw, int max_mps)
	{
		_length = length;
		_max_mlw = max_mlw;
		_max_mps = max_mps;
		_search();
	}
};


/**
 * @brief для вывода информации о найденном оптимальном сигнале.
 *
 * @param oss Объект класса OptimalSignalSearch, содержащий информацию о найденном оптимальном сигнале.
 *
 * @return void
 */
void printOptimalSignalSearch(const OptimalSignalSearch& oss)
{
	cout << "signal: [ ";
	for (int i = 0; i < oss.signal.size(); i += 1) {
		cout << oss.signal[i] << " ";
	}
	cout << "]" << endl;
	cout << "acf: [ ";
	for (int i = 0; i < oss.acf.size(); i += 1) {
		cout << oss.acf[i] << " ";
	}
	cout << "]" << endl;
	cout << "mlw: " << oss.acf_props.mlw << endl;
	cout << "mps: " << oss.acf_props.mps << endl;
}


int main()
{
	auto start = chrono::high_resolution_clock::now();

	OptimalSignalSearch* oss = new OptimalSignalSearch(5, 2, 2);

	auto stop = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

	printOptimalSignalSearch(*oss);

	delete oss;

	cout << "Time: " << fixed << setprecision(2) << duration.count() / 1000.0 << " sec" << endl;

	return 0;
}