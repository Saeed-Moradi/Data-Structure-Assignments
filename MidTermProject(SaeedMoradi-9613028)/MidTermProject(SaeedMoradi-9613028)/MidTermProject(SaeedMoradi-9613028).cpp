#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
string Heap[100][3];//3 Dimensional array for saving orders
int imLevelTime[100][2];//For immediacy level
int index = 1;
class Agency;
class Services;
class SubServices;
class CarCampony;
///////////////////
class Agency
{
public:
	string agencyName;
	Agency* firstAgency;
	Agency* lastAgency;
	Agency* nextAgency;
	Agency* nextProvider;
	Services* activeService;
	Agency()
	{
		firstAgency = NULL;
		lastAgency = NULL;
	}
};
///////////////
class Services
{
public:
	string serviceName;
	Services* firstService;
	Services* lastService;
	Services* nextService;
	Agency* FirstProvider;
	Agency* LastProvider;
	SubServices* FirstContainer;
	SubServices* LastContainer;
	Services()
	{
		firstService = NULL;
		lastService = NULL;
		FirstProvider = NULL;
		LastProvider = NULL;
		FirstContainer = NULL;
		LastContainer = NULL;
	}
};
////////////////
class SubServices {
public:
	string SubServiceName;
	SubServices* firstSubService;
	SubServices* lastSubService;
	SubServices* nextSubService;
	SubServices* nextContainer;
	int NumberOfItems;
	SubServices()
	{
		firstSubService = NULL;
		lastSubService = NULL;
	}
};
////////////////
class CarCampony :public Agency, public Services, public SubServices {
public:
	void AddService(string s)//OK
	{
		Services* temp = new Services;
		if (firstService == NULL)
		{
			temp->serviceName = s;
			firstService = temp;
			lastService = firstService;
			lastService->nextService = NULL;
		}
		else
		{
			temp->serviceName = s;
			lastService->nextService = temp;
			lastService = temp;
			lastService->nextService = NULL;
		}
	}
	void AddAgency(string a)//OK
	{
		Agency* temp = new Agency;
		if (firstAgency == NULL)
		{
			temp->agencyName = a;
			firstAgency = temp;
			lastAgency = firstAgency;
			lastAgency->nextAgency = NULL;
		}
		else
		{
			temp->agencyName = a;
			lastAgency->nextAgency = temp;
			lastAgency = temp;
			lastAgency->nextAgency = NULL;
		}
	}
	void listAgencies()//OK
	{
		cout << "All Agencies" << endl;
		cout << "____________" << endl << endl;
		int i = 1;
		Agency* temp = new Agency;
		temp = firstAgency;
		while (temp != NULL)
		{
			cout << "Agency" << i << ":" << temp->agencyName << endl;
			temp = temp->nextAgency;
			i++;
		}
		cout << endl;
	}
	void listServices()//OK
	{
		cout << "All Services" << endl;
		cout << "____________" << endl << endl;
		Services* temp = new Services;
		temp = firstService;
		int i = 1;
		while (temp != NULL)
		{
			cout << "Service " << i << ":" << temp->serviceName << endl;
			temp = temp->nextService;
			i++;
		}
		cout << endl;

	}
	void deleteService(string ServiceName, string AgencyName)//OK
	{
		int value = 1;
		Services* temp = new Services;
		temp = firstService;
		while (temp->serviceName != ServiceName)
		{
			temp = temp->nextService;
		}
		Agency* temp2 = temp->FirstProvider;
		Agency* temp3 = temp->LastProvider;
		if (temp2 == temp3)
		{
			cout << "You cannot delete this service!" << endl;
			value = 0;
		}
		while (temp2->nextAgency->agencyName != AgencyName && value != 0)
		{
			temp2 = temp2->nextAgency;
		}
			temp3 = temp2->nextAgency;
		temp2->nextAgency = temp3->nextAgency;
		temp3->nextAgency = NULL;
	}
	void addSubService(string ss, string s)//Ok
	{
		if (firstSubService == NULL)
		{
			SubServices* temp = new SubServices;
			temp->SubServiceName = ss;
			firstSubService = temp;
			lastSubService = firstSubService;
			lastSubService->nextSubService = NULL;
		}
		else
		{
			SubServices* temp = new SubServices;
			temp->SubServiceName = ss;
			lastSubService->nextSubService = temp;
			lastSubService = temp;
			lastSubService->nextSubService = NULL;
		}
		Services* temp2 = new Services;
		while (temp2->serviceName != s)
		{
			temp2 = temp2->nextService;
		}
		SubServices* temp3 = new SubServices;
		if (temp2->FirstContainer == NULL)
		{
			temp3->SubServiceName = ss;
			FirstContainer = temp3;
			LastContainer = FirstContainer;
			LastContainer->nextSubService = NULL;
		}
		else
		{
			temp3->SubServiceName = ss;
			LastContainer->nextSubService = temp3;
			LastContainer = temp3;
			LastContainer->nextSubService = NULL;
		}
	}
	void AddOffer(string a, string s)
	{
		Services* temp1 = new Services;
		temp1 = firstService;
		while (temp1->serviceName != s)
		{
			temp1 = temp1->nextService;
		}
		if (temp1->FirstProvider == NULL)
		{
			Agency* temp2 = new Agency;
			temp2->agencyName = a;
			temp1->FirstProvider = temp2;
			temp1->LastProvider = temp1->FirstProvider;
			temp1->LastProvider->nextProvider = NULL;
		}
		else
		{
			Agency* temp2 = new Agency;
			temp2->agencyName = a;
			temp1->LastProvider->nextProvider = temp2;
			temp1->LastProvider = temp2;
			temp1->LastProvider->nextProvider = NULL;
		}
	}
	void listServices_SubServices(string s)
	{
		Services* temp1 = new Services;
		temp1 = firstService;
		while (temp1->serviceName != s)
		{
			temp1 = temp1->nextService;
		}
		cout << "Name of service : " << temp1->serviceName << endl;
		SubServices* temp2 = new SubServices;
		temp2 = temp1->FirstContainer;
		while (temp2)
		{
			cout << temp2->SubServiceName << endl;
			temp2 = temp2->nextContainer;
		}

	}
	void MaxHeapOrder(int InnerIndex)
	{
		string Stemp;
		int Itemp;
		if (index != 1)
		{
			if (imLevelTime[index][0] > imLevelTime[InnerIndex / 2][0])
			{
				Stemp = Heap[index][0];
				Heap[index][0] = Heap[InnerIndex / 2][0];
				Heap[InnerIndex / 2][0] = Stemp;
				///////////////////////
				Stemp = Heap[index][1];
				Heap[index][1] = Heap[InnerIndex / 2][1];
				Heap[InnerIndex / 2][1] = Stemp;
				///////////////////////
				Stemp = Heap[index][2];
				Heap[index][2] = Heap[InnerIndex / 2][2];
				Heap[InnerIndex / 2][2] = Stemp;
				///////////////////////
				Itemp = imLevelTime[index][0];
				imLevelTime[index][0] = imLevelTime[InnerIndex / 2][0];
				imLevelTime[InnerIndex / 2][0] = Itemp;
				///////////////////////
				Itemp = imLevelTime[index][1];
				imLevelTime[index][1] = imLevelTime[InnerIndex / 2][1];
				imLevelTime[InnerIndex / 2][1] = Itemp;
				InnerIndex /= 2;
				MaxHeapOrder(InnerIndex);
			}
			if (imLevelTime[index][0] == imLevelTime[InnerIndex / 2][0])
			{
				if (imLevelTime[index][1] > imLevelTime[InnerIndex / 2][1])
				{
					Stemp = Heap[index][0];
					Heap[index][0] = Heap[InnerIndex / 2][0];
					Heap[InnerIndex / 2][0] = Stemp;
					///////////////////////
					Stemp = Heap[index][1];
					Heap[index][1] = Heap[InnerIndex / 2][1];
					Heap[InnerIndex / 2][1] = Stemp;
					///////////////////////
					Stemp = Heap[index][2];
					Heap[index][2] = Heap[InnerIndex / 2][2];
					Heap[InnerIndex / 2][2] = Stemp;
					///////////////////////
					Itemp = imLevelTime[index][0];
					imLevelTime[index][0] = imLevelTime[InnerIndex / 2][0];
					imLevelTime[InnerIndex / 2][0] = Itemp;
					///////////////////////
					Itemp = imLevelTime[index][1];
					imLevelTime[index][1] = imLevelTime[InnerIndex / 2][1];
					imLevelTime[InnerIndex / 2][1] = Itemp;
					InnerIndex /= 2;
					MaxHeapOrder(InnerIndex);
				}
			}
		}
	}
	void order(string s, string a, string c, int im, int t)
	{
		Heap[index][0] = s;
		Heap[index][1] = a;
		Heap[index][2] = c;
		imLevelTime[index][0] = im;
		imLevelTime[index][1] = t;
		MaxHeapOrder(index);
	}
	void listOrders(string a)
	{
		for (int InnerIndex = 0; InnerIndex < index; InnerIndex++)
		{
			if (Heap[InnerIndex][1] == a)
			{
				cout << "Service name: " << Heap[InnerIndex][0] << endl;
				cout << "Agency name: " << Heap[InnerIndex][1] << endl;
				cout << "Customer name: " << Heap[InnerIndex][2] << endl;
				cout << "Immediacy level: " << imLevelTime[InnerIndex][0] << endl;
				cout << "Time of order: " << imLevelTime[InnerIndex][1] << endl;
			}
		}
	}
};
int main()
{
	CarCampony obj;
	Agency A;
	Services S;
	SubServices SS;
	obj.AddService("Chnage tyre");
	obj.AddAgency("Markaz");
	obj.AddAgency("Qarb");
	obj.AddAgency("Shomal");
	obj.AddAgency("Jonoub");
	obj.listAgencies();
	obj.listServices();
	obj.AddOffer("Markaz", "Chnage tyre");
	obj.AddOffer("Qarb", "Change tyre");
	obj.AddOffer("Shomal", "Change tyre");
	obj.AddOffer("Jonoub", "Change tyre");
}