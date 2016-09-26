/*
 * chapter4.cc
 *
 *  Created on: 2012-7-15
 *      Author: chuanqi
 */


#include <exception>
#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include <ctime>
#include <loki/SmallObj.h>
using namespace std;
using namespace Loki;


struct MySmallObj : public Loki::SmallObject<> {
	int value;
};

struct OriginSmallObj{
	int value;
};


void chapter4(){
	int const k_obj_size = 100000;
	time_t t0 = clock();

	OriginSmallObj *origin_objs[k_obj_size];
	for (int i = 0; i < k_obj_size; ++i) {
		origin_objs[i] = new OriginSmallObj;
	}

	time_t t1 = clock();

	MySmallObj *small_objs[k_obj_size];
	for (int i = 0; i < k_obj_size; ++i) {
		small_objs[i] = new MySmallObj;
	}

	time_t t2 = clock();

	cout << (t1-t0) << ", " << (t2-t1) << endl;

	for (int i = 0; i < k_obj_size; ++i) {
		delete origin_objs[i];
		delete small_objs[i];
	}
}

