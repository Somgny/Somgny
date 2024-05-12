#include <iostream>
#include <algorithm>

// ��������ڵ�
struct Node 
{
    int arrivalTime; 										// ����ʱ��
    int burstTime;   										// ִ��ʱ��
    int waitingTime; 										// �ȴ�ʱ�� 
    int completionTime; 									// ���ʱ�� 
    Node* next;      										// ָ����һ�������ָ��
};

// ������������
struct TaskList 
{
    Node* head; 											// ��������ͷָ��
};

// ��������ڵ�
Node* createNode(int arrival, int burst) 					// ����"����"��"ִ��"���� 
{
    Node* newNode = new Node;
    newNode -> arrivalTime = arrival;
    newNode -> burstTime = burst;
    newNode -> next = NULL;									// ��ʼ��"����"��"ִ��"�����ʱ��  
    return newNode;
}

// ������������
TaskList* createTaskList() 
{
    TaskList* taskList = new TaskList;
    taskList -> head = NULL;
    return taskList;
}

// �����������
void addTask(TaskList* taskList, int arrival, int burst) 	// ����������ӵ����������ĩβ 
{
    Node* newNode = createNode(arrival, burst);
    if (taskList -> head == NULL) 
	{
        taskList -> head = newNode;
    } 
	else 
	{
        Node* current = taskList -> head;
        while (current -> next != NULL) 
		{
            current = current -> next;
        }
        current -> next = newNode;
    }
}

// ���ݵ���ʱ������
void sortByArrivalTime(TaskList* taskList) 					// ��ð��������㷨�������б����� 
{
    Node* current = taskList -> head;
    Node* next = NULL;
    int count = 0;

    // �������������нڵ�ĵ�ַ�洢��һ��������
    while (current != NULL) 
	{
        count++;
        current = current -> next;
    }

    Node** arr = new Node*[count];
    current = taskList -> head;
    for (int i = 0; i < count; i++) 
	{
        arr[i] = current;
        current = current -> next;
    }

    // �������еĽڵ���ݵ���ʱ���������
    for (int i = 0; i < count - 1; i++) 
	{
        for (int j = 0; j < count - 1 - i; j++) 
		{
            if (arr[j] -> arrivalTime > arr[j + 1] -> arrivalTime) 
			{
                Node* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // ���¹�����������������˳�����ӽڵ�
    current = taskList -> head;
    for (int i = 0; i < count - 1; i++) 
	{
        arr[i] -> next = arr[i + 1];
    }
    arr[count - 1] -> next = NULL;

    delete[] arr;
}

// ����ִ��ʱ������
void sortByBurstTime(TaskList* taskList) 					// ��ð��������㷨�������б����� 
{
    Node* current = taskList -> head;
    Node* next = NULL;
    int count = 0;

    // �������������нڵ�ĵ�ַ�洢��һ��������
    while (current != NULL) 
	{
        count++;
        current = current -> next;
    }

    Node** arr = new Node*[count];
    current = taskList -> head;
    for (int i = 0; i < count; i++) 
	{
        arr[i] = current;
        current = current -> next;
    }

    // �������еĽڵ���ݵ���ʱ���������
    for (int i = 0; i < count - 1; i++) 
	{
        for (int j = 0; j < count - 1 - i; j++) 
		{
            if (arr[j] -> arrivalTime > arr[j + 1] -> arrivalTime) 
			{
                Node* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

   // ���¹�����������������˳�����ӽڵ�
    current = taskList -> head;
    for (int i = 0; i < count - 1; i++) 
	{
        arr[i] -> next = arr[i + 1];
    }
    arr[count - 1] -> next = NULL;

    delete[] arr;
}

// SJF�����㷨
void SJF(TaskList* taskList) 								// ���Ȱ��յ���ʱ���������Ȼ����ִ��ʱ��������� 
{
    sortByArrivalTime (taskList); 							// ���յ���ʱ������
    sortByBurstTime (taskList);   							// ����ִ��ʱ������
    int currentTime = 0;
    Node* currentTask = taskList -> head;

    // �����������񣬼���ÿ������ĵȴ�ʱ������ʱ��
    while (currentTask != NULL) 
	{
        if (currentTime < currentTask -> arrivalTime) 
		{
            currentTime = currentTask -> arrivalTime;
        }

        currentTask -> waitingTime = currentTime - currentTask -> arrivalTime;
        currentTask -> completionTime = currentTime + currentTask -> burstTime;
        currentTime += currentTask -> burstTime;

        currentTask = currentTask -> next;
    }
}

// ������ 
int main() 
{
    TaskList* taskList = createTaskList();					// ������������ 
    addTask(taskList, 0, 3); 								// ����1������ʱ��0��ִ��ʱ��3
    addTask(taskList, 2, 6); 								// ����2������ʱ��2��ִ��ʱ��6
    addTask(taskList, 4, 4); 								// ����3������ʱ��4��ִ��ʱ��4
    addTask(taskList, 6, 5); 								// ����4������ʱ��6��ִ��ʱ��5
    addTask(taskList, 8, 2); 								// ����5������ʱ��8��ִ��ʱ��2

    SJF(taskList);

    // ���ÿ������ĵȴ�ʱ������ʱ��
    Node* currentTask = taskList -> head;
    while (currentTask != NULL) 
	{
        std::cout << "���񵽴�ʱ�䣺" << currentTask -> arrivalTime << "\n";
        std::cout << "����ִ��ʱ�䣺" << currentTask -> burstTime << "\n";
        std::cout << "����ȴ�ʱ�䣺" << currentTask -> waitingTime << "\n";
        std::cout << "�������ʱ�䣺" << currentTask -> completionTime << "\n";
        std::cout << "-----------------------\n";
        currentTask = currentTask -> next;
    }

    return 0;
}

