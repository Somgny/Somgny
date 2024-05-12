#include <iostream>
#include <algorithm>

// 定义任务节点
struct Node 
{
    int arrivalTime; 										// 到达时间
    int burstTime;   										// 执行时间
    int waitingTime; 										// 等待时间 
    int completionTime; 									// 完成时间 
    Node* next;      										// 指向下一个任务的指针
};

// 创建任务链表
struct TaskList 
{
    Node* head; 											// 创建链表头指针
};

// 创建任务节点
Node* createNode(int arrival, int burst) 					// 创建"到达"，"执行"任务 
{
    Node* newNode = new Node;
    newNode -> arrivalTime = arrival;
    newNode -> burstTime = burst;
    newNode -> next = NULL;									// 初始化"到达"，"执行"任务的时间  
    return newNode;
}

// 创建任务链表
TaskList* createTaskList() 
{
    TaskList* taskList = new TaskList;
    taskList -> head = NULL;
    return taskList;
}

// 添加任务到链表
void addTask(TaskList* taskList, int arrival, int burst) 	// 讲新任务添加到任务链表的末尾 
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

// 根据到达时间排序
void sortByArrivalTime(TaskList* taskList) 					// 用冒泡排序的算法对任务列表排序 
{
    Node* current = taskList -> head;
    Node* next = NULL;
    int count = 0;

    // 遍历链表，将所有节点的地址存储在一个数组中
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

    // 对数组中的节点根据到达时间进行排序
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

    // 重新构建链表，按照排序后的顺序链接节点
    current = taskList -> head;
    for (int i = 0; i < count - 1; i++) 
	{
        arr[i] -> next = arr[i + 1];
    }
    arr[count - 1] -> next = NULL;

    delete[] arr;
}

// 根据执行时间排序
void sortByBurstTime(TaskList* taskList) 					// 用冒泡排序的算法对任务列表排序 
{
    Node* current = taskList -> head;
    Node* next = NULL;
    int count = 0;

    // 遍历链表，将所有节点的地址存储在一个数组中
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

    // 对数组中的节点根据到达时间进行排序
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

   // 重新构建链表，按照排序后的顺序链接节点
    current = taskList -> head;
    for (int i = 0; i < count - 1; i++) 
	{
        arr[i] -> next = arr[i + 1];
    }
    arr[count - 1] -> next = NULL;

    delete[] arr;
}

// SJF调度算法
void SJF(TaskList* taskList) 								// 首先按照到达时间进行排序，然后按照执行时间进行排序 
{
    sortByArrivalTime (taskList); 							// 按照到达时间排序
    sortByBurstTime (taskList);   							// 按照执行时间排序
    int currentTime = 0;
    Node* currentTask = taskList -> head;

    // 遍历所有任务，计算每个任务的等待时间和完成时间
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

// 主函数 
int main() 
{
    TaskList* taskList = createTaskList();					// 创建任务链表 
    addTask(taskList, 0, 3); 								// 任务1：到达时间0，执行时间3
    addTask(taskList, 2, 6); 								// 任务2：到达时间2，执行时间6
    addTask(taskList, 4, 4); 								// 任务3：到达时间4，执行时间4
    addTask(taskList, 6, 5); 								// 任务4：到达时间6，执行时间5
    addTask(taskList, 8, 2); 								// 任务5：到达时间8，执行时间2

    SJF(taskList);

    // 输出每个任务的等待时间和完成时间
    Node* currentTask = taskList -> head;
    while (currentTask != NULL) 
	{
        std::cout << "任务到达时间：" << currentTask -> arrivalTime << "\n";
        std::cout << "任务执行时间：" << currentTask -> burstTime << "\n";
        std::cout << "任务等待时间：" << currentTask -> waitingTime << "\n";
        std::cout << "任务完成时间：" << currentTask -> completionTime << "\n";
        std::cout << "-----------------------\n";
        currentTask = currentTask -> next;
    }

    return 0;
}

