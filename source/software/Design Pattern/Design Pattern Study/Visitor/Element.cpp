#include "stdafx.h"

#include "Visitor.h"
#include "Element.h"

void ConcreteElement1::Accpet(AbstractVisitor *v)
{
	//˫���ɣ�
	// 1��Accept��һ���麯������main�е��á�(*iter)->Accpet(visitor1);��ʱ���һ�η���
	// 2����������v��һ��ָ����VisitConcreteElement1���麯���������ٽ���v����ָ��AbstractVisitor�̳в����ʵ����һ�η���
	// 
	// ע��	Ҳ���Բ�ʹ��˫���ɣ�AbstractVisitorֻ��һ���ӿ�VisitElemtn(AbstractVisitor *);
	//		���������Ļ���̫�˷��ˣ���Ϊ��ConcreteElemtnes��Accept�����п������ֳ������ʵ�����һ��Element
	//		����ʹ�ó������Ľӿ������ʹ�ø���������ض��ӿ������Ͷ�ʧ��һ������Ϣ
	//		����˫������Ȼ�ڱ����ϱȽ��鷳����ҪVisitor֪��Elements�����̳в�Σ������������ڿ���
	//		���ø������������ӿڣ������ɶ��ϸ��󣬿�����Ҳ���ã�
	v->VisitConcreteElement1(this);
}

void ConcreteElement2::Accpet(AbstractVisitor *v)
{
	v->VisitConcreteElement2(this);
}