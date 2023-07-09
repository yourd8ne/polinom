#include <iostream>
#include <string>

using namespace std;

/*
����������� 
������ 
����������
*/
template<typename T>
class List
{
public:
	 List();
	~ List();
	void push_back(T data);
private:
	
	template<typename T>
	class Node 
	{
	public:
		Node* pNext;// ��������� �� ���� ����� 
		T data;
		Node(T data=T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		 }
		
	
	private:

	};

	Node<T> * head;
};
