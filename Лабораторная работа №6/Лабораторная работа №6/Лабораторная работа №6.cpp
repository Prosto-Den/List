#include <iostream>
#include <cassert>

template <typename type>
struct Node //структура узла списка
{
	type data;
	Node* next;
};

template <typename type>
class List //класс список
{
private:
	Node<type>* head;

	void deleteNode(Node<type>* node) //удаление узла по его адресу. Для пользователя это не нужно, а мне пригодиться
	{
		Node<type>* p = head;

		while (p->next != node)
			p = p->next;

		p->next = node->next;

		delete node;
	}

public:
	List() //создание пустого списка
	{
		head = NULL;
	}

	List(int amount, float value = 0) //создание списка из amount элементов значения value
	{
		assert(amount > 0); //для пустого списка есть друой конструктор. Проверяем, чтобы вставлялся хотя бы один элемент (или что пользователь не ввёл значение < 0)

		int i;

		for (i = 0; i < amount - 1; i++) //и в конец все остальные
			addNodeEnd(value);
	}

	~List() //деструктор
	{
		while (head != NULL)
			deleteNodeTop();

		head = nullptr;
	}

	//блок добавления узлов
	void addNodeTop(float value) //метод добавления узла в начало списка
	{
		Node<type>* tmp = new Node<type>;

		tmp->data = value;
		tmp->next = head;
		head = tmp;
	}

	void addNodeEnd(float value) //метод добавления узла в конец списка
	{
		if (head == NULL)
		{
			addNodeTop(value);
			return;
		}

		Node<type>* tmp = new Node<type>;
		Node<type>* p = head;

		tmp->data = value;
		tmp->next = NULL;

		while (p->next != NULL)
			p = p->next;

		p->next = tmp;
	}

	void addNode(int index, float value) //добавление узла после узла индекса index
	{
		assert(index >= 0); //проверяем корректность индекса

		if (index == 0 || head == NULL)
		{
			addNodeTop(value);
			return;
		}

		Node<type>* tmp = new Node<type>;
		Node<type>* p = head;
		int count = 0;

		tmp->data = value;

		while (count < index && p->next != NULL)
		{
			p = p->next;
			count++;
		}

		tmp->next = p->next;
		p->next = tmp;
	}
	//конец блока добавления узлов

	//блок удаления узлов
	void deleteNodeTop() //удаляет узел в начале списка
	{
		Node<type>* p = head->next;

		delete head;

		head = p;
	}

	void deleteNodeEnd() //удаляет узел в конце списка
	{
		Node<type>* p = head;
		Node<type>* current = head;

		while (p->next != NULL)
			p = p->next;

		while (current->next != p)
			current = current->next;

		current->next = NULL;

		delete p;
	}

	void deleteNode(int index) //удаляет узел по индексу
	{
		Node<type>* p = head;
		Node<type>* current = head;
		int count = 0;

		assert(index >= 0 && index < lengthList());

		if (index == 0)
		{
			deleteNodeTop();
			return;
		}

		while (count < index && p->next != NULL)
		{
			p = p->next;
			count++;
		}

		while (current->next != p)
			current = current->next;

		current->next = p->next;

		delete p;
	}
	//конец блока удаления узлов

	//блок прочих методов работы со списком
	int lengthList() //возвращает длину списка
	{
		Node<type>* p = head;
		int count = 0;

		while (p != NULL)
		{
			p = p->next;
			count++;
		}

		return count;
	}

	void unique() //удаляет се повторяющиеся элементы в списке
	{
		Node<type>* p = head;
		Node<type>* current;
		int flag = 0;

		while (p != NULL)
		{
			current = p;

			while (current->next != NULL)
			{
				if (current->next->data == p->data)
				{
					deleteNode(current->next);
					flag = 1;
				}

				if (flag == 0)
					current = current->next;

				flag = 0;
			}

			p = p->next;
		}
	}

	void merge(const List& list) //добавляет список в конец данного списка
	{
		Node<type>* p = list.head;

		while (p != NULL)
		{
			addNodeEnd(p->data);
			p = p->next;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const List& list) //перегрузка оператора <<. Для удобного вывода
	{
		Node<type>* p = list.head;

		os << "[";

		while (p != NULL)
		{
			if (p->next != NULL)
				os << p->data << "; ";
			else
				os << p->data;
			p = p->next;
		}
		os << "]";

		return os;
	}
};

int main()
{
	List<int> list;
	List<int> list1;
	List<int> list2;

	int i;
	int var;

	for (i = 0; i < 10; i++)
	{
		std::cout << "Enter " << i + 1 << " element of the list1: ";
		std::cin >> var;
		std::cout << "\n";
		list1.addNodeEnd(var);

		std::cout << "Enter " << i + 1 << " element of the list2: ";
		std::cin >> var;
		std::cout << "\n";
		list2.addNodeEnd(var);
	}

	std::cout << "list1: " << list1 << std::endl;
	std::cout << "list2: " << list2 << std::endl;

	list.merge(list1);
	list.merge(list2);

	std::cout << "Merged list: " << list << std::endl;

	list.unique();

	std::cout << "Result: " << list << std::endl;

	return 0;
}