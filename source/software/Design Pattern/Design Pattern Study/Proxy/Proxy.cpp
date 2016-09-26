// Proxy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;


/*
共同的抽象基类
由于Image与ImageVirtualProxyPtr具有相同的接口
所以在任何使用Image的地方就可以用ImageVirtualProxyPtr代替
*/
class ImageBase
{
public:
	virtual void DrawSelf() = 0;
};


/*
具体的图像类
*/
class Image : public ImageBase
{
public:
	Image(string file_path)
		: _file_path(file_path)
	{
		cout << "Load Image :" << file_path << endl;
	}

	virtual void DrawSelf()
	{
		cout << _file_path << " draw it self" << endl;
	}

private:
	string _file_path;
};


/**
 *	图像的虚拟代理指针
 *	只有在的确需要对图像进行绘制的时候才真正的去加载图像，做到了Lazy-Calcuate
 */
class ImageVirtualProxy : public ImageBase
{
public:
	ImageVirtualProxy(string file_path)
		: _file_path(file_path), _img(0)
	{}

	~ImageVirtualProxy()
	{
		if (_img != 0)
		{
			delete _img;
			_img = 0;
		}
	}

	virtual void DrawSelf()
	{
		//手动转发：手动去写每一个需要转发的函数
		GetImage()->DrawSelf();
	}

	Image * operator->()
	{
		//也可以这样自动实现转发，不过这样的话就把代理类视为一个指针，智能指针多是这么实现的
		return GetImage();
	}


private:
	Image * GetImage()
	{
		if (_img == 0)
		{
			_img = new Image(_file_path);
		}
		return _img;
	}

	string _file_path;
	Image *_img;
};


void main()
{
	ImageVirtualProxy img("c:\\love.jpg");
	cout << "Image has not been loaded now" << endl;

	//延迟到使用时才会去加载图像
	img.DrawSelf();		//调用手动的转发
	img->DrawSelf();	//将代理视为指针时的自动转发
}
