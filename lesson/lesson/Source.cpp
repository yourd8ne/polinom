#include <iostream>
#include "Source.h"


template<typename T>
List<T>::List()
{

}


template<typename T>
List<T>::~List()
{
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data)
	}
	else
	{
		Node<T>* tmp = this->head;
		while (tmp->pNext != nullptr)
		{
			tmp = tmp->pNext;
		}
		tmp->pNext = new Node<T>(data);
	}
}
