#include <iostream>

using namespace std;

template <typename T>
struct Node
{
	T value;
	Node<T>* next;
};

template <typename T>
class List
{
	Node<T>* first;
	Node<T>* last;

public: 
	List()
	{
		first = nullptr;
		last = nullptr;
	}

	~List()
	{
		removeAll();
	}

	void add(T value)
	{
		if (first == nullptr)
		{
			first = new Node<T>;
			first->next = nullptr;
			first->value = value;
			last = first;
		}
		else
		{
			Node<T>* temp = new Node<T>;
			last->next = temp;
			temp->next = nullptr;
			temp->value = value;
			last = temp;
		}

	}

	void remove()
	{
		if (first != nullptr)
		{
			if (first != last)
			{
				Node<T>* temp = first;
				while (temp->next != last)
				{
					temp = temp->next;
				}
				delete last;
				temp->next = nullptr;
				last = temp;
			}
			else
			{
				delete last;
				first = last = nullptr;
			}
			
		} 
		else
		{
			cout << "List empty" << endl;
		}
		
	}

	T search(T value)
	{
		Node<T>* temp = first;
		while (temp->next != nullptr)
		{
			if (temp->value == value) 
			{
				break;
			}
			temp = temp->next;
		}
		return temp->value;
	}

	void removeAll()
	{
		Node<T>* temp = first;
		Node<T>* t;
		while (temp != nullptr)
		{
			t = temp->next;
			delete temp;
			temp = t;
		}
		first = last = nullptr;
	}

	void printAll()
	{
		if (first != nullptr)
		{
			Node<T>* temp = first;
			while (temp != nullptr)
			{
				cout << temp->value << " ";
				temp = temp->next;
			}
		}
		else
		{
			cout << "List empty";
		}
		cout << endl;
	}
};


int main()
{
	List<int> list;
	list.add(5);
	list.add(55);
	list.add(6);
	list.add(13);
	list.printAll();
	list.remove();
	list.remove();
	list.remove();
	list.printAll();
	list.remove();
	list.printAll();
	list.removeAll();
	system("pause");
}