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
��ͬ�ĳ������
����Image��ImageVirtualProxyPtr������ͬ�Ľӿ�
�������κ�ʹ��Image�ĵط��Ϳ�����ImageVirtualProxyPtr����
*/
class ImageBase
{
public:
	virtual void DrawSelf() = 0;
};


/*
�����ͼ����
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
 *	ͼ����������ָ��
 *	ֻ���ڵ�ȷ��Ҫ��ͼ����л��Ƶ�ʱ���������ȥ����ͼ��������Lazy-Calcuate
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
		//�ֶ�ת�����ֶ�ȥдÿһ����Ҫת���ĺ���
		GetImage()->DrawSelf();
	}

	Image * operator->()
	{
		//Ҳ���������Զ�ʵ��ת�������������Ļ��ͰѴ�������Ϊһ��ָ�룬����ָ�������ôʵ�ֵ�
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

	//�ӳٵ�ʹ��ʱ�Ż�ȥ����ͼ��
	img.DrawSelf();		//�����ֶ���ת��
	img->DrawSelf();	//��������Ϊָ��ʱ���Զ�ת��
}
