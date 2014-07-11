#pragma once
#include "common.h"

#include <string>
#include <vector>
using namespace std;

struct productInfo
{
	string subject;
	string body;
	string price;
};

extern vector<productInfo> aliProduct;

class alipay
{
public:
	int alipayProfuct( productInfo info );
protected:
private:
};